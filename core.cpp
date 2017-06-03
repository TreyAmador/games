#include "core.h"
#include "test.h"
#include "node.h"
#include "game.h"
#include "io.h"


Core::Core() {
	
}


Core::~Core() {

}


int Core::run() {

	Game game;
	IO io;

	//test_max_row_col();

	//test_next_move_choice();

	time_next_choice();

	return 0;

}

