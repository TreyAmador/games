#ifndef NODE_H_
#define NODE_H_


namespace dim {
	const int SPAN = 8;
	const int SIZE = SPAN * SPAN;
	const int MAX_ADJ = 4;
}


enum SYMBOL {
	EMPTY = '.',
	PLAYER = 'X',
	OPPONENT = 'O'
};


struct Node {

	Node() :
		config_(new char[dim::SIZE]),
		parent_(nullptr)
	{
		for (int i = 0; i < dim::SIZE; ++i)
			this->config_[i] = SYMBOL::EMPTY;
	}

	Node(Node* node) :
		config_(new char[dim::SIZE]), 
		parent_(node)
	{
		for (int i = 0; i < dim::SIZE; ++i)
			this->config_[i] = node->config_[i];
	}

	~Node() {
		if (this->config_ != nullptr) {
			delete[] config_;
			config_ = nullptr;
		}
	}

	char* config_;
	Node* parent_;

};


#endif

