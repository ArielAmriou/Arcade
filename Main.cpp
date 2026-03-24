/*
** EPITECH PROJECT, 2026
** Arcade
** File description:
** main
*/

#include <iostream>
#define DEBUG(value) std::cout << "\e[0;35m" << "DEBUG: " <<  "\e[0;37m" << "\t" << value << std::endl;

#include "Game.hpp"
#include "Display.hpp"

int main()
{
    arc::Game game;
    arc::Display display;
    if (display.setAssets(game.getAssets()) != 0) {
        DEBUG("setAssets failed");
        return 84;
    }
    while (game.isOpen()) {
        game.simulate(display.getEvent());
        arc::SelectLibs libs = game.libChanges({{"Snake"}, {"SDL2"}});
        if (libs.first.has_value())
            DEBUG("request gameLib change " + libs.first.value());
        if (libs.second.has_value())
            DEBUG("request displayLib change " + libs.second.value());
        auto tmp = game.getElements();
        display.drawGame(tmp);
    }
}