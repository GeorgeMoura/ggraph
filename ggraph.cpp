#include "ggraph.h"


bool ggraph::allocate_matrix(int vertex_num){ //this function will allocate the adj_matrix by vertex_num space

	if(!this->V){ 

		this->V = vertex_num;
		std::vector<int> aux(vertex_num);
		this->adj_matrix.reserve(vertex_num); //reserve method makes sure that the allocation happens only 1 time, push_backs are cheaper now

		for(int i=0; i<vertex_num; i++){

			for(int j=0; j<vertex_num; j++)
				if(i==j)
					aux[j] = 0;
				else
					aux[j] = INT_MAX;

			this->adj_matrix.push_back(aux);
		}

		return true;
	}else{
		std::cout << "ERROR: adj_matrix alredy allocated." << std::endl;
		return false;
	}
}

bool ggraph::allocate_list(int vertex_num){	//this function will allocate the adj_list by vertex_num space

	if(!this->V){

		this->V = vertex_num;
		std::list<std::pair<int, int> > aux;
		this->adj_list.reserve(vertex_num);

		for(int i=0; i<vertex_num; i++)
			this->adj_list.push_back(aux);

		return true;
	}else{
		std::cout << "ERROR: adj_list alredy allocated." << std::endl;
		return false;
	}
}

ggraph::ggraph(){  //constructor 1 (nothing), matrix is ever setted as default storage type
	this->storage_type = 'm';
	this->V = 0;

	std::cout << "graph created: " << std::endl;
	std::cout << "size: " << this->V << std::endl;
	std::cout << "graph storage: " << this->storage_type << std::endl;
	std::cout << std::endl;
}

ggraph::ggraph(int vertex_num){ //constructor 2 (only size), matrix is ever setted as default storage type

	this->V = 0;

	if(vertex_num < 0)
		std::cout << "Can't have a negative size.\n" << std::endl;
	else{
		this->storage_type = 'm';

		this->allocate_matrix(vertex_num);

		std::cout << "graph created: " << std::endl;
		std::cout << "size: " << this->V << std::endl;
		std::cout << "graph storage: " << this->storage_type << std::endl;
		std::cout << std::endl;
	}

}

ggraph::ggraph(int vertex_num, char storage){ // constructor 3 (size and storage type)

	this->V = 0;

	if(vertex_num<0)
		std::cout << "cannot have a negative size.\n" << std::endl;
	else{
		this->storage_type = ((storage!='l' && storage!='L') && (storage!='m' && storage!='M')?'m':storage); //no wrong storage type can entry, set matrix as default

		if(storage_type=='l')
			this->allocate_list(vertex_num);
		else
			this->allocate_matrix(vertex_num);

		std::cout << "graph created: " << std::endl;
		std::cout << "size: " << this->V << std::endl;
		std::cout << "graph storage: " << this->storage_type << std::endl;
		std::cout << std::endl;
	}
}

void ggraph::set_graph_len(int vertex_num){  //initiate the graph lenght if you didn't in the constructor
	
	if(this->storage_type=='m')

		if(this->allocate_matrix(vertex_num)){  // allocate func returns false if matrix or list (according to storage type) have alredy been allocated
			std::cout << "matrix length setted: " << std::endl;
			std::cout << "size: " << this->V << std::endl;
			std::cout << std::endl;
		}
	
	else

		if(this->allocate_list(vertex_num)){
			std::cout << "list length setted: " << std::endl;
			std::cout << "size: " << this->V << std::endl;
			std::cout << std::endl;
		}	
}

int ggraph::len(){	//returns the length of the graph
	return this->V;
}

void ggraph::print(){ //prints the graph

	if(this->storage_type=='m'){

		std::cout << "Matrix:" << std::endl;

		for(int i=0; i<this->V; i++){
			for(int j=0; j<this->V; j++)
				std::cout<< this->adj_matrix[i][j] << " ";
			
		std::cout << std::endl;
		}

	}else{

		int len = adj_list.size();
		typename std::list<std::pair<int, int> >::iterator it;

		std::cout << "List(node, cost):" << std::endl;

		for(int i=0; i<len; i++){

			std::cout << "[" << i << "] -> ";
			
			for(it=adj_list[i].begin(); it!=adj_list[i].end(); it++)
					std::cout << "(" << it->first << " , " << it->second << ") -> ";
			
			std::cout << std::endl;
		}
	}
}

void ggraph::add_edge(int v1, int v2, int cost){ //add an edge weight to the graph, all edge wights are initially setted as infinite

	if(v1 >= this->V || v2 >= this->V || v1 < 0 || v2 < 0)
			std::cout << "This node doesn't exist. " << std::endl;
	
	else
		if(this->storage_type=='m')
			this->adj_matrix[v1][v2] = cost;
		else
			this->adj_list[v1].push_back(std::make_pair(v2, cost));		
}

void ggraph::add_node(){ // add an node to the grap by resizing the matrix or the list, matrix case will set all edge weights of the new node as infite

	if(this->storage_type=='m'){

		this->adj_matrix.resize(this->V+1);
		this->adj_matrix[this->V].resize(this->V+1);

		for(int i=0; i<this->V; i++){
			this->adj_matrix[i].resize(this->V+1);

			adj_matrix[i][this->V] = INT_MAX;
			adj_matrix[this->V][i] = INT_MAX;
		}

	}else
		this->adj_list.resize(this->V+1);
	
	this->V++;
}

void ggraph::complete_und_unw(){ //turns the graph into a complete undirected unweighted graph (all nodes conected by 0 value edges)

	for(int i=0; i<this->V; i++){

		if(this->storage_type == 'l')
			this->adj_list[i].resize(0);

		for(int j=0; j<this->V; j++)
			this->add_edge(i, j, 0);

	}	
}
