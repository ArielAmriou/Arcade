/*
** EPITECH PROJECT, 2026
** Arcade
** File description:
** Core
*/

#include <fstream>
#include <iostream>
#include "Core.hpp"
#include "Exceptions.hpp"

arc::Core::Core(const std::string &path): _loader(path) {
    auto disp = _loader.makeInstance<IDisplayModule>();
    if (!disp.has_value())
        throw arc::exceptions::NotGraphical();
    _display = std::unique_ptr<IDisplayModule>(disp.value().release());

    _loader.reset(DEFAULT_GAME_PATH);
    auto game = _loader.makeInstance<IGameModule>();
    if (!game.has_value())
        throw arc::exceptions::LibraryLoadError();
    _game = std::unique_ptr<IGameModule>(game.value().release());
}

void arc::Core::play() {

}

void arc::Core::help() noexcept {
    std::ifstream helpfile("src/help.txt");
    std::string line;

    while (std::getline(helpfile, line))
        std::cerr << line;
}

