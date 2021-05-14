#pragma once


struct Connection
{
public:
	Connection() :id(-1), weight(-1) {}
	Connection(int _id, int _weight) :id(_id), weight(_weight) {}

	int id;
	int weight;
};

