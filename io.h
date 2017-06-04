#ifndef IO_H_
#define IO_H_
#include <string>
struct Node;


class IO {


public:
	IO();
	~IO();

	bool computer_moves_first();
	int time_allowed();
	int enter_next_move(Node* node);
	int next_move_validity(Node* node, std::string& input);


	void print_node(Node* node);
	

private:



};


#endif

