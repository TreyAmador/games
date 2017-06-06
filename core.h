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
	void computer_turn(Game& game, Node*& node, IO& io);
	void opponent_turn(Node*& node, IO& io);
	
	void retroactive_moves(std::vector<Node*>& nodes, IO& io);
	void determine_move_order(Game& game, Node*& node, IO& io);
	void set_time_allowed(Game& game, IO& io);
	
	bool has_won(Game& game, Node* node, char symbol);
	int complete(Game& game, Node*& node, char symbol, IO& io);
	void clear_nodes(std::vector<Node*>& nodes);


	void opponent_turn_test(Node*& node, IO& io);

};


#endif

