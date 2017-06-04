#ifndef CORE_H_
#define CORE_H_
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
	void determine_move_order(Game& game, IO& io, Node* node);


	//bool has_won(Node* node, char player);
	//bool has_tied(Node* node, char player);


};


#endif

