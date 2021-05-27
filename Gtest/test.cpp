#include "pch.h"
#include "../Graphs/Graph.h"

TEST(Graph, Testdijkstra) {
	Graph<int> graph;
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



	for (int i = 0; i < 6; i++)
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


	int* d = graph.djikstra_alg(0);

	EXPECT_EQ(d[0],0);
	EXPECT_EQ(d[1], 10);
	EXPECT_EQ(d[2], 20);
	EXPECT_EQ(d[3], 23);
	EXPECT_EQ(d[4], 20);
	EXPECT_EQ(d[5], 21);
}

TEST(Graph, Testadd) {
	Graph<int> g = Graph<int>();
	Point<int> p = Point<int>(1,1);
	int res = g.add_Point(p);
	EXPECT_EQ(res, 1);
	res = g.add_Point(p);
	EXPECT_EQ(res, -1);
}

TEST(Graph, Pointrm) {
	Graph<int> g = Graph<int>();
	Point<int> p = Point<int>(1, 1);
	g.add_Point(p);
	int res = g.delete_point(1);
	EXPECT_EQ(res, 1);
	res = g.delete_point(-1);
	EXPECT_EQ(res, -1);
}