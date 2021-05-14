#pragma once
#include<iostream>
#include<list>
#include "Point.h"
#include <fstream>
#include <string>

using namespace std;

template<typename DATA>
class Graph
{
public:
#define Points list<Point<DATA>> //Обратить Внимание!!!!
	Graph() :points(Points()) {}

	Graph(list<Point<DATA>> nP) :points(nP) {}

	/*
	* function for printing graph to console
	*/
	void print_console() {
		typename Points::iterator it = points.begin();
		Point<DATA> point;
		list<Connection> ::iterator it_con;
		Connection con;
		cout << "\n";
		while (it != points.end()) {
			point = *it;
			it_con = point.connections.begin();
			cout << "Point " << point.id << " :: ";
			if (it_con == point.connections.end()) {
				cout << "UNCONNECTED";
			}
			else {
				while (it_con != point.connections.end())
				{
					con = *it_con;
					cout << con.id << " : " << con.weight << "\t";
					it_con++;
				}
			}
			cout << endl;
			it++;
		}
	}

	/*
	* _points - graph points
	*/
	void set_points(list<Point<DATA>> _points) {
		points = _points;
	}

	int add_Point(Point<DATA> p) {
		typename Points::iterator it_point = is_point_exist(p.id);
		if (it_point != points.end()) {
			//cout << "Message from Graph: Cannot add Point id = " << p.id << "\nReason: Point already exists\n";
			Log::send_message(sender, "Cannot add point id = " + to_string(p.id), 1, -1, "Reason: point already exists");
			return -1;
		}
		else {
			points.push_back(p);
			//cout << "Message from Graph:  Point id = " << p.id << " was added\n";
			Log::send_message(sender, "Point id = " + to_string(p.id) + " was added", 0, -1);
			return 1;
		}
	}

	/*
	* id - point id
	*/
	int delete_point(int id) {
		//cout << "\nMessage from Graph:DELETE POINT WITH ID = " << id << endl;
		typename Points::iterator it_point = is_point_exist(id);
		if (it_point == points.end()) {
			//cout << "Message from Graph: Point id = " << id << " cannot be deleted" << "\nReason: Point does't exist\n";
			Log::send_message(sender, "It is not possible to delete a point with id = " + to_string(id), 1, -1, "Reason: this point is missing or has been deleted earlier.");
			return -1;
		}
		else {
			Point<DATA> Point;

			points.erase(it_point);

			it_point = points.begin();
			while (it_point != points.end())
			{
				Point = *it_point;
				Point.delete_connection(id);
				*it_point = Point;
				it_point++;
			}
			//cout << "Message from Graph: POINT ID = " << id << " WAS SUCCESSFUL DELETED\n";
			Log::send_message(sender, "Point id = " + to_string(id) + " was deleted", 0,-1);
		}
		return 1;
	}

	/*
	* fname - file output name
	*/
	int foutput(string fname) {
		ofstream f(fname);
		typename Points::iterator it = points.begin();
		Point<DATA> point;
		list<Connection> ::iterator it_con;
		Connection con;

		while (it != points.end()) {
			point = *it;
			it_con = point.connections.begin();
			f << "Point " << point.id << " :: Connections => ";
			if (it_con == point.connections.end()) {
				f << "UNCONNECTED";
			}
			else {
				while (it_con != point.connections.end())
				{
					con = *it_con;
					f << con.id << " : " << con.weight << "\t";
					it_con++;
				}
			}
			f << endl;
			it++;
		}
		//cout << "\nGraph was printed in file " << fname << "\n";
		Log::send_message(sender, "Graph was printed in file: " + fname, 0);
		return 1;
	}

	/*
	* q_points - quantity of points
	* min_weight - min
	* amx_weight - max
	*/
	int create_random_graph(int q_points, int min_weight, int  max_weight, list<DATA> data) {
		srand(time(NULL));
		if (data.size() != q_points) {
			//cout << "\nMessage from Graph: Cannot create graph!\nReason: q_points != data.size\n";
			Log::send_message(sender, "Cannot create graph!", 1, -1, "Reason: q_points != data.size");
			return -1;
		}
		//cout << "\nMessage from Graph: Creation random graph began\n q_points = " << q_points << " min_weight = " << min_weight << " max_weight = " << max_weight << "\n";
		Log::send_message(sender, " Creation random graph began\n q_points = " + to_string(q_points) + " min_weight = " + to_string(min_weight) + " max_weight = " + to_string(max_weight),0,-1);
		typename list<DATA> ::iterator it_data = data.begin();
		Point<DATA> point;
		for (size_t i = 0; i < q_points; i++)
		{
			point = Point<DATA>(*it_data, i);
			point.create_random_connections(q_points, min_weight, max_weight);
			this->add_Point(point);
			it_data++;
		}
		//cout << "Message from Graph: Creation random graph ended\n";
		Log::send_message(sender, "Creation random graph ended", 0, -1);
		return 0;
	}

	/*
	* pid - point id
	* cid - connection id
	* weight - connection weight
	*/
	int change_point_connection(int pid, int cid, int weight) {
		typename Points::iterator it_point = is_point_exist(pid);
		//cout << "\nCHANGING CONNECTION WITH ID = " << cid << " TO A POINT WITH ID = " << pid << endl;
		if (it_point == points.end()) {
			//cout << "Message from Graph: Point id = " << pid << " cannot be cahnged" << "\nReason: Point doesn't exist\n";
			Log::send_message(sender, "Point id = " + to_string(pid) + " cannot be cahnged", 1, -1, "Reason: Point doesn't exist");
			return -1;
		}
		else {
			/*Point<DATA> point = *it_point;
			list<Connection>::iterator  it_conn = point.is_connection_exist(cid);
			if (it_conn == point.connections.end()) {
				cout << "\nMessage from Point id = " << pid << ": Connection id = " << cid << " doesn't exist\n";
				return -2;
			}
			else {
				*it_conn = conn;
				*it_point = point;
				cout << "\nMessage from Point id = " << pid << ": Connection id = " << cid << " was changed\n";
				return 1;
			}*/
			Point<DATA> point = *it_point;
			point.change_connection(cid, Connection(cid, weight));
			*it_point = point;
			//cout << "CHANGING CONNECTION WITH ID = " << cid << " TO A POINT WITH ID = " << pid << " was complited successful\n";
			Log::send_message(sender, "CHANGING CONNECTION WITH ID = " + to_string(cid) + " TO A POINT WITH ID = " + to_string(pid) + " was complited successful", 0, -1);
			return 1;
		}
	}

	list<Point<DATA>> get_points() {
		return points;
	}
	typename Points::iterator get_points_begin() {
		return points.begin();
	}
	typename Points::iterator get_points_end() {
		return points.end();
	}

private:
	typename Points::iterator  is_point_exist(int id) {
		typename Points::iterator it_point = points.begin();
		while (it_point != points.end())
		{
			if (id == it_point->id) {

				return it_point;
			}
			it_point++;
		}
		return points.end();
	}

	Sender sender = graph;
	Points points; //Вершины графа
};

