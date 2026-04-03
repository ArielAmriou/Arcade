/*
** EPITECH PROJECT, 2026
** arcade
** File description:
** DisplayNcurses
*/

#include <fstream>
#include "DisplayNcurses.hpp"
#include <iostream>
#include<unistd.h>

namespace arc {
    const std::unordered_map<mmask_t, arc::Action> arc::DisplayNcurses::_mouseButtonMapNcurses = {
        {BUTTON1_RELEASED, Action::LeftMouse},
        {BUTTON2_RELEASED, Action::MiddleMouse},
        {BUTTON3_RELEASED, Action::RightMouse},
        {BUTTON1_PRESSED, Action::LeftMouse},
        {BUTTON1_PRESSED, Action::MiddleMouse},
        {BUTTON1_PRESSED, Action::RightMouse},
    };

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
        {KEY_RIGHT, Action::Right},
        {KEY_LEFT, Action::Left},
        {KEY_DOWN, Action::Down},
        {KEY_UP, Action::Up},
        {'/', Action::Divide},
        {'*', Action::Multiply},
        {'-', Action::Subtract},
        {'+', Action::Add},
        {'.', Action::Period},
        {'=', Action::Equal}
    };

    DisplayNcurses::~DisplayNcurses()
    {
        delwin(_window);
        endwin();
    }

    DisplayNcurses::DisplayNcurses()
    {
        initscr();
        noecho();
        cbreak();
        mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, nullptr);
        mouseinterval(0);
        _window = newwin(getmaxy(stdscr), getmaxx(stdscr), 0, 0);
        nodelay(_window, TRUE);
        keypad(_window, TRUE);
        curs_set(0);
    }

    void DisplayNcurses::drawGame(std::reference_wrapper<std::pair<Entities, Sounds>> elements)
    {
        usleep(FRAMERATE);
        wclear(_window);
        for (const auto &entity: elements.get().first) {
            Vector2f pos = entity->getPos();
            mvwprintw(_window, static_cast<int>(pos.second * getmaxy(_window)),
                static_cast<int>(pos.first * getmaxx(_window)), "%c",
                _assets[entity->getIdx()]);
        }
        wrefresh(_window);
    }

    int DisplayNcurses::setAssets(Assets assets)
    {
        char character;

        _assets.clear();
        for (auto path: assets.first) {
            path = "assets/" + path + ".txt";
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
        std::ofstream MyFile("filename.txt", std::ios::app);
        const int getInput = wgetch(_window);
        Vector2f mousePos = {0, 0};
        const auto key = _keyMap.find(getInput);
        MEVENT eventMouse = {0};
        int isMouse = getmouse(&eventMouse);

        if (isMouse == OK) {
            mousePos.first  = static_cast<float>(eventMouse.x) / getmaxx(_window);
            mousePos.second = static_cast<float>(eventMouse.y) / getmaxy(_window);
        }
        if (getInput == KEY_MOUSE && isMouse == OK) {
            const auto buttonPressed = _mouseButtonMapNcurses.find(eventMouse.bstate);
                if (buttonPressed != _mouseButtonMapNcurses.end())
                    return {buttonPressed->second, mousePos};
        }
        if (key != _keyMap.end())
            return {key->second, mousePos};
        return {Action::None, mousePos};
    }
}

extern "C"
{

    arc::ILibrary *makeInstance()
    {
        return new arc::DisplayNcurses();
    }

}
