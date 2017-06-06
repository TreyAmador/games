#ifndef IO_H_
#define IO_H_
#include <string>
#include <vector>
struct Node;


class IO {


public:
	IO();
	~IO();

	void salutations();
	bool computer_moves_first();
	int time_allowed();
	int enter_next_move(Node* node);
	int next_move_validity(Node* node, std::string& input);
	void complete(std::vector<Node*>& nodes, char symbol);

	void print_node(Node* node);
	

private:



};


#endif

