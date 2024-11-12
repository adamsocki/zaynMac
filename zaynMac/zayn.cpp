//
//  zayn.cpp
//  zaynMac
//
//  Created by socki on 11/12/24.
//

#include "zayn.hpp"


#include "render_triangle.hpp"


#include <iostream>

void initializeGame() {
    // Initialize game state, load resources, etc.
    std::cout << "Game initialized!" << std::endl;
    InitTriangle();
}

void updateGame() {
    // Update game state, handle input, etc.
    std::cout << "Game updated!" << std::endl;
    RenderTriangle();
}
