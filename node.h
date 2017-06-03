#ifndef NODE_H_
#define NODE_H_
//#include "global.h"


namespace dim {
	const int SPAN = 8;
	const int SIZE = SPAN * SPAN;
	const int MAX_ADJ = 4;
}


//	TODO BIG IDEAS for the NODE
//
//
//		initialize alpha/beta with +INFINITY and -INFINITY ?
//			which, in this case, lowest int vs highest int
//			perhaps better to have alpha beta outside node?
//				could be passed as parameters
//
//		player and opponent score
//			indicates score of node
//				related to alpha/beta, not same
//			utility = player_score_ - opponent_score_;
//				in minimax, end if winner found or use
//				the node which has the highest utility value
//


enum SYMBOL {
	EMPTY = '.',
	PLAYER = 'X',
	OPPONENT = 'O'
};


struct Node {

	// this ctor is only really necessary for first node
	Node() :
		config_(new char[dim::SIZE]),
		alpha_(0), beta_(0), 

		// TODO remove
		//row_score_(new int[dim::SPAN]),
		//col_score_(new int[dim::SPAN]),
		
		
		row_player_(new int[dim::SPAN]),
		col_player_(new int[dim::SPAN]),
		row_opponent_(new int[dim::SPAN]),
		col_opponent_(new int[dim::SPAN]),
		parent_(nullptr)
	{
		for (int i = 0; i < dim::SIZE; ++i)
			this->config_[i] = SYMBOL::EMPTY;
		for (int i = 0; i < dim::SPAN; ++i) {

			// TODO remove
			//this->row_score_[i] = this->col_score_[i] = 0;

			this->row_player_[i] = this->col_player_[i] = 
				this->row_opponent_[i] = this->col_opponent_[i] = 0;
		}
	}

	
	Node(Node* node) :
		config_(new char[dim::SIZE]),
		
		// TODO remove
		//row_score_(new int[dim::SPAN]),
		//col_score_(new int[dim::SPAN]),

		row_player_(new int[dim::SPAN]),
		col_player_(new int[dim::SPAN]),
		row_opponent_(new int[dim::SPAN]),
		col_opponent_(new int[dim::SPAN]),
		parent_(node)
	{
		for (int i = 0; i < dim::SIZE; ++i)
			this->config_[i] = node->config_[i];
		for (int i = 0; i < dim::SPAN; ++i) {
			
			// TODO remove
			//this->row_score_[i] = node->row_score_[i];
			//this->col_score_[i] = node->col_score_[i];


			this->row_player_[i] = node->row_player_[i];
			this->col_player_[i] = node->col_player_[i];
			this->row_opponent_[i] = node->row_opponent_[i];
			this->col_opponent_[i] = node->col_opponent_[i];

		}
		this->player_score_ = node->player_score_;
		this->opponent_score_ = node->opponent_score_;


		// init alpha beta with lowest int vs highest int
		// could calculate alpha / beta here ?
		// perhaps better outside due to alpha / beta conflict
		this->alpha_ = node->alpha_;
		this->beta_ = node->beta_;
	}


	~Node() {
		if (this->config_ != nullptr) {
			delete[] config_;
			config_ = nullptr;
		}


		// TODO delete
		//if (this->row_score_ != nullptr) {
		//	delete[] row_score_;
		//	row_score_ = nullptr;
		//}
		//if (this->col_score_ != nullptr) {
		//	delete[] col_score_;
		//	col_score_ = nullptr;
		//}


		this->clear_ptrs(row_player_);
		this->clear_ptrs(col_player_);
		this->clear_ptrs(row_opponent_);
		this->clear_ptrs(col_opponent_);

	}


	void clear_ptrs(int* ptr) {
		if (ptr != nullptr) {
			delete[] ptr;
			ptr = nullptr;
		}
	}

	char* config_;


	// is this merely passed into the minimax method ?
	int alpha_;
	int beta_;

	// you need both per each config !
	int player_score_;
	int opponent_score_;


	// could implement this
	// the score of the column
	// indicates which move is most dire
	// could check which row/col is the highest
	// then iterate to find which col/row is highest
	// move there next
	
	// should this be a opponent/player row/col scores?
	//int* row_score_;
	//int* col_score_;


	// this is better
	int* row_player_;
	int* col_player_;

	int* row_opponent_;
	int* col_opponent_;


	Node* parent_;

};


#endif

