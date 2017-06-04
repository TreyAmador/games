#ifndef CORE_H_
#define CORE_H_
#include <vector>
struct Node;
class Game;
class IO;


class Core {


public:
	Core();
	~Core();

	int run();


private:
	//void set_board_between_turn(Node* node);
	void determine_move_order(Game& game, Node*& node, IO& io);
	void set_time_allowed(Game& game, IO& io);
	void opponent_turn(Node*& node, IO& io);
	void computer_turn(Game& game, Node*& node, IO& io);
	bool has_won(Game& game, Node* node, char symbol);
	int complete(Node*& node, char symbol, IO& io);

	void clear_nodes(std::vector<Node*>& nodes);

	void print_nodes(Node* node, IO& io);

	void determine_moves(std::vector<Node*>& nodes, IO& io);


};


#endif

