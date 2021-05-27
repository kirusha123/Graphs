#pragma once
#include<iostream>
#include<list>
#include "Point.h"
#include <fstream>
#include <string>

#include <limits.h>
#include <stdio.h>


using namespace std;





int len = 0;

int minDistance(int* dist, bool* sptSet)
{
	int min = INT_MAX, min_index;

	for (int v = 0; v < len; v++)
		if (sptSet[v] == false && dist[v] <= min)
			min = dist[v], min_index = v;

	return min_index;
}

void printSolution(int* dist)
{
	printf("Vertex \t\t Distance from Source\n");
	for (int i = 0; i < len; i++)
		printf("%d \t\t %d\n", i, dist[i]);
}


int* dijkstra(int** graph, int src, int glen)
{
	len = glen;
	

	int* dist = new int[len];

	bool* sptSet = new bool[len];

	for (int i = 0; i < len; i++)
		dist[i] = INT_MAX, sptSet[i] = false;

	dist[src] = 0;

	for (int count = 0; count < len - 1; count++) {
		int u = minDistance(dist, sptSet);
		sptSet[u] = true;
		for (int v = 0; v < len; v++)
			if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX
				&& dist[u] + graph[u][v] < dist[v])
				dist[v] = dist[u] + graph[u][v];
	}
	//printSolution(dist);

	return dist;
}






template<typename DATA>
class Graph
{
public:
#define Points list<Point<DATA>> //Обратить Внимание!!!!
	Graph() :points(Points()) { }

	Graph(list<Point<DATA>> nP) :points(nP) { }

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
			Log::send_message(sender, "Point id = " + to_string(id) + " was deleted", 0, -1);
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
		Log::send_message(sender, " Creation random graph began\n q_points = " + to_string(q_points) + " min_weight = " + to_string(min_weight) + " max_weight = " + to_string(max_weight), 0, -1);
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

	int* djikstra_alg(int src) {
		int** arr = generate_arr_for_dji();
		return dijkstra(arr, src, points.size());
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
	
	int** generate_arr_for_dji() {
		int n = points.size();
		int** arr = new int* [n];
		for (size_t i = 0; i < n; i++)
		{
			arr[i] = new int[n];
			for (size_t j = 0; j < n; j++)
			{
				arr[i][j] = 0;
			}
		}

		typename Points::iterator point_it = get_points_begin();
		Point<DATA> point;
		Connection conn;
		if (point_it != get_points_end()) {
			Log::send_message(sender, "STARTING CREATING WEIGHT MATRIX", 0);
			while (point_it != get_points_end()) {
				point = *point_it;
				auto conn_it = point.connections.begin();

				while (conn_it != point.connections.end())
				{
					conn = *conn_it;

					arr[point.id][conn.id] = conn.weight;
					conn_it++;
				}
				point_it++;
			}
		}

		for (size_t i = 0; i < len; i++)
		{
			cout << endl;
			for (size_t j = 0; j < len; j++)
			{
				cout << arr[i][j] << "\t";
			}
		}

		return arr;
	}

	Sender sender = graph;
	Points points; //Вершины графа
};

