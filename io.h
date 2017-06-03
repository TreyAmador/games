#ifndef IO_H_
#define IO_H_
#include <string>
struct Node;


class IO {


public:
	IO();
	~IO();

	void print_node(Node* node);
	void print_config(Node* node);
	void print_node_and_vec_score(Node* node);



private:



};

#endif //IO_H_