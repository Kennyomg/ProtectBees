#include "stdafx.h"
#include "Game.h"

int main(int argc, char** argv)
{
	/*
	 * I made Game static because there should only exist 1 instance of it anyway
	 */
	Game::start();

	return 0;
}