/*
** EPITECH PROJECT, 2026
** arcade
** File description:
** DisplayNcurses
*/

#include <fstream>
#include "DisplayNcurses.hpp"

#include <iostream>

namespace arc {
    const std::unordered_map<int, arc::Action> DisplayNcurses::_keyMap = {
        {ERR, Action::None},
        {'a', Action::A},
        {'b', Action::B},
        {'c', Action::C},
        {'d', Action::D},
        {'e', Action::E},
        {'f', Action::F},
        {'g', Action::G},
        {'h', Action::H},
        {'i', Action::I},
        {'j', Action::J},
        {'k', Action::K},
        {'l', Action::L},
        {'m', Action::M},
        {'n', Action::N},
        {'o', Action::O},
        {'p', Action::P},
        {'q', Action::Q},
        {'r', Action::R},
        {'s', Action::S},
        {'t', Action::T},
        {'u', Action::U},
        {'v', Action::V},
        {'w', Action::W},
        {'x', Action::X},
        {'y', Action::Y},
        {'z', Action::Z},
        {'1', Action::Num1},
        {'2', Action::Num2},
        {'3', Action::Num3},
        {'4', Action::Num4},
        {'5', Action::Num5},
        {'6', Action::Num6},
        {'7', Action::Num7},
        {'8', Action::Num8},
        {'9', Action::Num9},
        {'0', Action::Num0},
        {'\n', Action::Enter},
        {ESC_CHARACTER, Action::Escape},
        {'\t', Action::Tab},
        {' ', Action::Space},
        {'-', Action::Subtract},
        {'=', Action::Equal},
        {'{', Action::LBracket},
        {'}', Action::RBracket},
        {'\\', Action::Backslash},
        {';', Action::Semicolon},
        {'\'', Action::Apostrophe},
        {',', Action::Comma},
        {'.', Action::Period},
        {'/', Action::Slash},
        {'`', Action::Hyphen},
        {RIGHT_ARROW, Action::Right},
        {LEFT_ARROW, Action::Left},
        {DOWN_ARROW, Action::Down},
        {UP_ARROW, Action::Up},
        {'/', Action::Divide},
        {'*', Action::Multiply},
        {'-', Action::Subtract},
        {'+', Action::Add},
        {'.', Action::Period},
        {'=', Action::Equal}
    };



    // AJOUTER KEYPAD OPTION À LA WINDOW POUR HANDLE CERTAIN CARACTERES + les ajouter à la map de caracteres

    DisplayNcurses::~DisplayNcurses()
    {
        delwin(_window);
    }

    DisplayNcurses::DisplayNcurses()
    {
        initscr();
        cbreak();
        noecho();
        mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, nullptr);
        _window = newwin(getmaxy(stdscr), getmaxx(stdscr), 0, 0);
        keypad(_window, true);
    }

    void DisplayNcurses::drawGame(std::reference_wrapper<std::pair<Entities, Sounds>> elements)
    {
        timeout(100);
        wrefresh(_window);
        for (const auto &entity: elements.get().first) {
            Vector2f pos = entity->getPos();
            mvwprintw(_window, static_cast<int>(pos.first), static_cast<int>(pos.second), "%c", _assets.at(entity->getIdx()));
        }
    }

    int DisplayNcurses::setAssets(Assets assets)
    {
        char character;

        for (auto path: assets.first) {
            path += ".txt";
            std::ifstream is_path_valid (path, std::ifstream::binary);
            if (!is_path_valid) {
                std::cerr << "Error : " << path << " invalid path" << std::endl;
                return ERROR;
            }
            is_path_valid.read(&character, 1);
            if (!is_path_valid) {
                std::cerr << "Error : " << path << " could not read the file" << std::endl;
                return ERROR;
            } else
                _assets.push_back(character);
        }
        return SUCCES;
    }

    Event DisplayNcurses::getEvent()
    {
        const int getInput = wgetch(_window);
        Vector2f mousePos = {0, 0};
        Event value{Action::None, mousePos};
        const auto tmp = _keyMap.find(getInput);
        MEVENT eventMouse = {0};

        getmouse(&eventMouse);
        mousePos.first = static_cast<float>(eventMouse.x);
        mousePos.second = static_cast<float>(eventMouse.y);
        if (tmp != _keyMap.end())
            value = {tmp->second, mousePos};
        else
            value = {Action::None, mousePos};
        return value;
    }
}

extern "C"
{
    std::unique_ptr<arc::IDisplayModule> makeInstance()
    {
        return std::make_unique<arc::DisplayNcurses>();
    }
    arc::LibType getLibType()
    {
        return arc::LibType::Display;
    }
}
