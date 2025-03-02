#include "game.h"
#include <iostream>

int main() {
    try {
        Game game;
        game.Run();
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Unknown exception occurred" << std::endl;
    }

    return 0;
}
