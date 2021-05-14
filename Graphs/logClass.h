#pragma once
#include<iostream>
#include<string>
#include<fstream>
#include<ctime>

using namespace std;

enum Sender {
	graph,
	point,
	connection
};

static class Log {
public:
	Log() {
	}

	/*
	* status --  0-OK, 1-Warning,
	* Object - sending object,
	* id - object id. if doesn't exist = -1,
	* mess - message to print,
	* reson - reason of warning. Can be empty if status = 0
	*/
	static void send_message(Sender object,string mess, short int status, int id = -1, string reason = "") {
		string mes = "";
		
		switch (object)
		{
		case graph:
			if (status == 0){
				mes = create_report_message("Graph",mess,id);
			}
			else {
				mes = create_warning_message("Graph", mess, reason,id);
			}

			break;

		case point:
			if (status == 0) {
				mes = create_report_message("Point", mess, id);
			}
			else {
				mes = create_warning_message("Point", mess, reason, id);
			}
			break;

		case connection:
			if (status == 0) {
				mes = create_report_message("Connection", mess, id);
			}
			else {
				mes = create_warning_message("Connection", mess, reason, id);
			}
			break;

		default:
			return;
		}
		add_message(mes);
	}

private :
	//Message if Warning
	static string create_warning_message(string sender, string mess, string reason, int id = -1) {
		string message;

		if (id == -1) {
			message = "Message " + sender + ": " + mess + "\n" + reason + "\n";
		}
		else {
			message = "Message " + sender + to_string(id) + ": " + mess + "\n" + reason + "\n";
		}
		return message;
	}
	
	//Message if OK
	static string create_report_message(string sender, string mess, int id = -1) {
		string message;
		if (id == -1) {
			message = "Message " + sender + ": " + mess + "\n";
		}
		else {
			message = "Message " + sender + " " + to_string(id) + ": " + mess + "\n";
		}
		return message;
	}

	//print message to file log.txt
	static void add_message(string message) {
		ofstream fout("Log.txt", ios::app);
		fout << time(NULL) <<":\t"<< message<<"\n";
	}
};