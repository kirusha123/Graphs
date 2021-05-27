#include <iostream>
#include "Graph.h"
#include "Struct_Data.h"

int main()
{
	/*list<Connection> l1;
	l1.push_back(Connection(2, 5));
	l1.push_back(Connection(3, 7));
	Point<Data> p1 = Point<Data>(Data(1),1,l1);
	list<Connection> l2;
	l2.push_back(Connection(1, 5));
	l2.push_back(Connection(3, 10));
	Point<Data> p2 = Point<Data>(Data(2), 2, l2);
	list<Connection> l3;
	//l3.push_back(Connection(1, 7));
	//l3.push_back(Connection(2, 10));
	Point<Data> p3 = Point<Data>(Data(3), 3);
	list<Connection> l4;
	l4.push_back(Connection(1, 8));
	Point<Data> p4 = Point<Data>(Data(1), 4, l4);

	list<Point<Data>> points;
	points.push_back(p1);
	points.push_back(p2);
	points.push_back(p3);
	Graph<Data> Graph(points);
	Graph.add_Point(p4);
	Graph.print_console();
	Graph.foutput("Graph_1.0.txt");

	list< Point<Data> > ::iterator it_point = Graph.get_points_begin();
	Point<Data> point = *it_point;
	point.change_connection_weight(1,8);
	point.change_connection_weight(2,4);
	*it_point = point;
	Graph.print_console();

	it_point->delete_connection(1);
	it_point->delete_connection(2);
	Graph.print_console();

	Graph.delete_point(1);
	Graph.print_console();

	Graph.change_point_connection(2, 3, 5);
	Graph.print_console();
	Graph.foutput("Graph_2.0.txt");*/

	/*Graph<int> graph;
	//list<int> data = { 5,4,4,2,1,3 };
	//graph.create_random_graph(6, 0, 10, data);
	//graph.print_console();
	//graph.foutput("test_rand.txt");

	int g[6][6] = {
		{0, 10, 20, 0, 0, 0},
		{10, 0, 0, 50, 10, 0},
		{20, 0, 0, 20, 33, 0},
		{0, 50, 20, 0, 20, 2},
		{0, 10, 33, 20, 0, 1},
		{0, 0, 0, 2, 1, 0} 
	};
	list<Point<int>> points;
	
	Point<int> pts[6];

	

	for(int i = 0; i<6; i++)
	{
		//cout << "\n";
		for (int j = 0; j < 6; j++)
		{
			pts[i].id = i;
			Connection conn = Connection(j, g[i][j]);
			pts[i].add_connection(conn);
			//cout << "N: " << j << "\tweigth: " << g[i][j]<<"\t";
		}
	}

	points.push_back(pts[0]);
	points.push_back(pts[1]);
	points.push_back(pts[2]);
	points.push_back(pts[3]);
	points.push_back(pts[4]);
	points.push_back(pts[5]);

	graph = Graph<int>(points);
	//graph.print_console();


	int* d = graph.djikstra_alg(0);*/

}


