#ifndef NODE_H_
#define NODE_H_
#include "global.h"


// indicates the symbol of each tile space
// we should clarify the syntax
// here I'm assuming the 'player' is your machine
// and the 'opponent' would be the other machine
// 
enum SYMBOL {
	EMPTY = '.',
	PLAYER = 'X',
	OPPONENT = 'O'
};


//struct Coordinate {
//	int row_;
//	int col_;
//};


// token is how each tile is filled
// player is 'O', opponents is 'X', empty is '.'
// as shown from TOKEN enum above


// a node represents each part of a tree
// ptr to parent_ may be necessary to prune tree
// 

struct Node {

	// TODO initialize node with +INFINITY and -INFINITY ?
	// only really necessary for first node
	Node() :
		config_(new char[dim::SIZE]),
		alpha_(0), beta_(0), 
		row_score_(new int[dim::SPAN]),
		col_score_(new int[dim::SPAN]),
		parent_(nullptr)
	{
		for (int i = 0; i < dim::SIZE; ++i)
			this->config_[i] = SYMBOL::EMPTY;
		for (int i = 0; i < dim::SPAN; ++i) {
			this->row_score_[i] = 0;
			this->col_score_[i] = 0;
		}
	}

	
	Node(Node* node) :
		config_(new char[dim::SIZE]),
		row_score_(new int[dim::SPAN]),
		col_score_(new int[dim::SPAN]),
		parent_(node)
	{
		for (int i = 0; i < dim::SIZE; ++i)
			this->config_[i] = node->config_[i];
		for (int i = 0; i < dim::SIZE; ++i) {
			this->row_score_[i] = node->row_score_[i];
			this->col_score_[i] = node->col_score_[i];
		}
		this->alpha_ = node->alpha_;
		this->beta_ = node->beta_;
	}


	/*
	Node(Node* node) :
		config_(new char[dim::SIZE]),
		row_score_(new int[dim::SPAN]),
		col_score_(new int[dim::SPAN]),
		parent_(node)
	{
		for (int i = 0; i < dim::SIZE; ++i)
			this->config_[i] = node->config_[i];
		for (int i = 0; i < dim::SIZE; ++i) {
			this->row_score_[i] = node->row_score_[i];
			this->col_score_[i] = node->col_score_[i];
		}
		this->alpha_ = node->alpha_;
		this->beta_ = node->beta_;
	}
	*/


	~Node() {
		if (this->config_ != nullptr) {
			delete[] config_;
			config_ = nullptr;
		}
		if (this->row_score_ != nullptr) {
			delete[] row_score_;
			row_score_ = nullptr;
		}
		if (this->col_score_ != nullptr) {
			delete[] col_score_;
			col_score_ = nullptr;
		}
	}

	char* config_;
	int alpha_;
	int beta_;

	// could implement this
	// the score of the column
	// indicates which move is most dire
	// could check which row/col is the highest
	// then iterate to find which col/row is highest
	// move there next
	int* row_score_;
	int* col_score_;


	Node* parent_;

	// NOTE: may not need this with row/col paradigm
	// TODO implement this
	//		tracks next moves
	//		put adjacent moves on vector
	//		then iterate through them
	//Coordinate* nearby_space_;


};


#endif

