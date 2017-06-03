#ifndef GLOBAL_H_
#define GLOBAL_H_


namespace dim {
	const int SPAN = 8;
	const int SIZE = SPAN * SPAN;
	const int MAX_ADJ = 4;
}


namespace util {


	void clear_ptrs(int* ptr) {
		if (ptr != nullptr) {
			delete[] ptr;
			ptr = nullptr;
		}
	}



}



#endif

