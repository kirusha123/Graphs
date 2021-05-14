#pragma once
#include<iostream>
#include<List> 
#include"Connection.h"
#include"logClass.h"
#include <random>
#include <cstdlib>
#include <ctime>

using namespace std;

template<typename DATA>
struct Point
{
public:
	Point() {
		id = -1;
	}

	Point(DATA _d, int _id, list<Connection> nC = list<Connection>()) :data(_d), id(_id), connections(nC){}

	//Point(DATA _d, int _id) :data(_d), id(_id), connections(new list<Connection>()) {}

	int add_connection(Connection newConn) {
		if (is_connection_exist(newConn.id) != connections.end()) {
			//cout << "Message Point " << this->id << ":Cannot add connection id = " << newConn.id << "\nReason: connection already exists\n";
			Log::send_message(sender, "Cannot add connection id = " + to_string(newConn.id), 1,this->id, "Reason: connection already exists");
			return -1;
		}
		connections.push_back(newConn);
		//cout << "Message Point " << this->id << " connection added successfully\n";
		Log::send_message(sender, "connection id = "+to_string(newConn.id)+" was added successfully", 0, this->id);
		return 0;
	}

	int add_connection(list<Connection> newConnections) {
		connections = newConnections;
		return 0;
	}

	int change_connection_weight(int id, int weight) {
		list<Connection>::iterator it_conn = is_connection_exist(id);
		if (it_conn == connections.end()) {
			//cout << "Message Point " << this->id << ": Connection id = " << id << " doesn't exist\n";
			Log::send_message(sender, "Cannot change connection id = " + to_string(id), 1, this->id, "Reason: connection doesn't exist");
			return -1;
		}
		it_conn->weight = weight;
		//cout << "Message Point " << this->id << ": Connection id = " << id << " was changed\n";
		Log::send_message(sender, "connection id = " + to_string(id) + " was changed", 0, this->id);
		return 1;
	}
	
	int change_connection(int id, Connection newConn) {
		list<Connection>::iterator it_conn = is_connection_exist(id);

		if (it_conn == connections.end()) {
			//cout << "Message Point " << this->id << ": Connection id = " << id << " doesn't exist\n";
			Log::send_message(sender, "Cannot change connection id = " + to_string(newConn.id), 1, this->id, "Reason: connection doesn't exist");
			return -1;
		}
		else {
			*it_conn = newConn;
			Log::send_message(sender, "connection id = " + to_string(newConn.id) + " was changed", 0, this->id);
			return 1;
		}
	}

	int delete_connection(int id) {
		list<Connection>::iterator it_conn = is_connection_exist(id);
		if (it_conn == connections.end()) {
			//cout << "Message Point "<< this->id <<":It is not possible to delete a connection with id = " << id << ". \nReason: this connection is missing or has been deleted earlier.\n";
			Log::send_message(sender, "It is not possible to delete a connection with id = " + to_string(id), 1, this->id, "Reason: this connection is missing or has been deleted earlier.");
			return -1;
		}
		connections.erase(it_conn);
		//cout << "Message Point " << this->id << ":Connection with id = " << id << " was successful deleted\n";
		Log::send_message(sender, "connection id = " + to_string(id) + " was deleted", 0, this->id);
		return 1;
	}

	int create_random_connections(int numPoints, int min_weight, int max_weight) {
		//cout << "\nCreation random connections in Point with id = " << this->id << endl;
		int weight;
		for (size_t i = 0; i < numPoints; i++){
			if (i != this->id) {
				weight = min_weight + rand() % (max_weight + 1);
			
				if (weight != 0) {
					//cout << "Message from point with id = " << this->id << ": Connection id = " << i << " & Weight = " << weight << " Was added\n";
					this->add_connection(Connection(i, weight));
				}
			}

		}
		//cout << "Creating connections completed\n";
		return 0;
	}

	list<Connection>::iterator is_connection_exist(int id) {
		list<Connection> :: iterator it_conn = connections.begin();
		Connection conn;
		while (it_conn != connections.end()) {
			conn = *it_conn;
			if (id == conn.id) {
				return it_conn;
			}
			it_conn++;
		}
		return connections.end();
	}

	DATA data;
	int id;

	list<Connection> connections;
	Sender sender = point;
};

