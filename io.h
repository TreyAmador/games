#ifndef IO_H_
#define IO_H_
#include <string>
struct Node;


class IO {


public:
	IO();
	~IO();

	bool player_moves_first();
	int time_allowed();
	bool valid_move();


	void print_node(Node* node);
	void print_config(Node* node);
	void print_node_and_vec_score(Node* node);



private:



};

#endif

