#include "ggraph.h"
#include <iostream>

int main(){

	ggraph g1;
	ggraph g2(4, 'm');
	ggraph g3(5, 'l');

	g1.set_graph_len(10);
	g2.set_graph_len(20);
	g3.set_graph_len(30);

	std::cout << "g1: " << g1.len() << "  g2: " << g2.len() << "  g3: " << g3.len() << std::endl;

	g2.add_edge(0, 1, 5);
	g2.add_edge(1, 2, 3);
	g2.add_edge(3, 2, 2);

	g3.print();
	g2.print();

	g2.add_node();
	g3.add_node();

	g3.print();
	g2.print();

	g3.complete_und_unw();
	g2.complete_und_unw();

	g3.print();
	g2.print();

	return 0;
}