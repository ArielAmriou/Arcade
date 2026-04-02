/*
** EPITECH PROJECT, 2026
** Arcade
** File description:
** Core
*/

#include <fstream>
#include <iostream>
#include "Core.hpp"
#include "DLLoader.hpp"
#include "Exceptions.hpp"
#define DEBUG(value) std::cout << "\e[0;35m" << "DEBUG: " <<  "\e[0;37m" << "\t" << value << std::endl;

arc::Core::Core(const std::string &path): _loader(path) {
    try {
        auto disp = _loader.makeInstance<IDisplayModule>(arc::LibType::Display);
        if (!disp.has_value())
            throw arc::exceptions::NotGraphical();
        disp.value().swap(_display);

        _loader.reset(DEFAULT_GAME_PATH);
        auto game = _loader.makeInstance<IGameModule>(arc::LibType::Game);
        if (!game.has_value())
            throw arc::exceptions::LibraryLoadError();
        game.value().swap(_game);
    } catch (...) {
        throw arc::exceptions::LibraryLoadError();
    }
}

void arc::Core::loadGameModule(const std::string &path, const std::exception &e) {
    _loader.reset(path);
    auto game = _loader.makeInstance<IGameModule>(arc::LibType::Game);
    if (!game.has_value())
        throw e;
    game.value().swap(_game);
}

void arc::Core::loadDisplayModule(const std::string &path, const std::exception &e) {
    _loader.reset(path);
    auto disp = _loader.makeInstance<IDisplayModule>(arc::LibType::Display);
    if (!disp.has_value())
        throw e;
    disp.value().swap(_display);
}

void arc::Core::play() {
    Event event = {arc::Action::None, {0, 0}};

    auto assets = _game->getAssets();
    _display->setAssets(assets);
    while (event.first != arc::Action::Close) {
        event = _display->getEvent();
        auto elements = _game->getElements();
        _game->simulate(event);
        _display->drawGame(elements);
    }
}

void arc::Core::help() noexcept {
    std::ifstream helpfile("src/help.txt");
    std::string line;

    while (std::getline(helpfile, line))
        std::cerr << line << std::endl;
}

