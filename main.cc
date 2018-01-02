#include <iostream>
#include <stdlib.h>
#include "game.h"

#ifdef WIN32
#include <windows.h>
#endif

using namespace std;

#ifdef WIN32
int WINAPI WinMain(HINSTANCE h,	HINSTANCE h1, LPSTR s, int i)
#else
int main(int argc, char *argv[])
#endif
{
    try {
        Game *game = new Game();
        game->run();
        delete game;
    } catch(...) {
        cout << "Erro desconhecido!" << endl;
    }
    return EXIT_SUCCESS;
}
