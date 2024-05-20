#include <iostream>
#include <windows.h>

#include "BlockGameEngine.h"

int main() {
#ifdef NDEBUG
	ShowWindow(GetConsoleWindow(), SW_HIDE);
#else
	ShowWindow(GetConsoleWindow(), SW_SHOW);
#endif
	auto gameEngine = BlockGameEngine();

	if (!gameEngine.StartEngine()) {
		return -1;
	}

	gameEngine.StartRenderLoop();
	gameEngine.ShutdownEngine();

	return 1;
}
