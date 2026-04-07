/*
** EPITECH PROJECT, 2026
** arcade
** File description:
** DisplayNcurses
*/

#include "DisplayNcurses.hpp"

#include <fstream>
#include <iostream>
#include <unistd.h>
#include "DisplayNcurses.hpp"

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
    {'0', Action::Num0},
    {'1', Action::Num1},
    {'2', Action::Num2},
    {'3', Action::Num3},
    {'4', Action::Num4},
    {'5', Action::Num5},
    {'6', Action::Num6},
    {'7', Action::Num7},
    {'8', Action::Num8},
    {'9', Action::Num9},
    {ESC_CHARACTER, Action::Escape},
    {KEY_SLEFT, Action::LShift},
    {KEY_SRIGHT, Action::RShift},
    {'[', Action::LBracket},
    {']', Action::RBracket},
    {';', Action::Semicolon},
    {',', Action::Comma},
    {'.', Action::Period},
    {'\'', Action::Apostrophe},
    {'/', Action::Slash},
    {'\\', Action::Backslash},
    {'`', Action::Grave},
    {'=', Action::Equal},
    {'-', Action::Hyphen},
    {' ', Action::Space},
    {'\n', Action::Enter},
    {KEY_BACKSPACE, Action::Backspace},
    {'\t', Action::Tab},
    {KEY_PPAGE, Action::PageUp},
    {KEY_NPAGE, Action::PageDown},
    {KEY_END, Action::End},
    {KEY_HOME, Action::Home},
    {KEY_IC, Action::Insert},
    {KEY_DC, Action::Delete},
    {'+', Action::Add},
    {'*', Action::Multiply},
    {KEY_RIGHT, Action::Right},
    {KEY_LEFT, Action::Left},
    {KEY_UP, Action::Up},
    {KEY_DOWN, Action::Down},
    {KEY_F(1), Action::F1},
    {KEY_F(2), Action::F2},
    {KEY_F(3), Action::F3},
    {KEY_F(4), Action::F4},
    {KEY_F(5), Action::F5},
    {KEY_F(6), Action::F6},
    {KEY_F(7), Action::F7},
    {KEY_F(8), Action::F8},
    {KEY_F(9), Action::F9},
    {KEY_F(10), Action::F10},
    {KEY_F(11), Action::F11},
    {KEY_F(12), Action::F12},
    {KEY_F(13), Action::F13},
    {KEY_F(14), Action::F14},
    {KEY_F(15), Action::F15},
    {KEY_SUSPEND, Action::Pause},
    };

    const std::unordered_map<DisplayNcurses::Colors, std::tuple<int, int, int, int>> DisplayNcurses::_color {
        {DisplayNcurses::Colors::Red, RED},
        {DisplayNcurses::Colors::Blue, BLUE},
        {DisplayNcurses::Colors::Green, GREEN},
        {DisplayNcurses::Colors::White, WHITE},
    };


    DisplayNcurses::~DisplayNcurses()
    {
        delwin(_window);
        endwin();
    }


    DisplayNcurses::Colors DisplayNcurses::getColorId(const std::unique_ptr<IEntity> &entity)
    {
        for (auto i : _color) {
            if (i.second == entity->getColor())
                return i.first;
        }
        return Colors::Red;
    }

    void DisplayNcurses::initColors()
    {
        if (has_colors()) {
            start_color();
            init_pair(1, COLOR_WHITE, COLOR_BLACK);
            init_pair(2, COLOR_RED, COLOR_BLACK);
            init_pair(3, COLOR_GREEN, COLOR_BLACK);
            init_pair(4, COLOR_BLUE, COLOR_BLACK);
        }
    }

    DisplayNcurses::DisplayNcurses()
    {
        initscr();
        noecho();
        cbreak();
        initColors();
        mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, nullptr);
        mouseinterval(0);
        _window = newwin(getmaxy(stdscr), getmaxx(stdscr), 0, 0);
        nodelay(_window, TRUE);
        keypad(_window, TRUE);
        curs_set(0);
    }
//Blanc = 256, noir = 000, sinon faire red green blue
    void DisplayNcurses::drawGame(const std::pair<Entities, Sounds> elements) noexcept
    {
        usleep(FRAMERATE);
        werase(_window);
        /*beep();*/
        for (auto &entity: elements.first) {
            Colors color =  getColorId(entity);
            Vector2f pos = entity->getPos();
            wattron(_window, COLOR_PAIR(color));
            if (entity->getIdx() >= 0 && entity->getIdx() < _assets.size())
                mvwprintw(_window, static_cast<int>(pos.second * getmaxy(_window)),
                    static_cast<int>(pos.first * getmaxx(_window)), "%s",
                    _assets[entity->getIdx()].data());
            if (entity->getStr())
                mvwprintw(_window, static_cast<int>(pos.second * getmaxy(_window)),
                    static_cast<int>(pos.first * getmaxx(_window)), "%s",
                    entity->getStr()->data());
            wattroff(_window, COLOR_PAIR(color));
        }
        wrefresh(_window);
    }

    int DisplayNcurses::setAssets(const Assets assets) noexcept
    {
        std::string asset;

        _assets.clear();
        for (auto path: assets.first) {
            path += ".txt";
            std::ifstream validPath (path, std::ifstream::binary);
            if (!validPath) {
                std::cerr << "Error : " << path << " invalid path" << std::endl;
                return ERROR;
            }
            std::getline(validPath, asset);
            if (!validPath) {
                std::cerr << "Error : " << path << " could not read this file" << std::endl;
                return ERROR;
            }
            _assets.push_back(asset);
        }
        return SUCCES;
    }

    Event DisplayNcurses::getEvent() noexcept
    {
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
    std::unique_ptr<arc::IDisplayModule> makeInstance()
    {
        return std::make_unique<arc::DisplayNcurses>();
    }
    arc::LibType getLibType()
    {
        return arc::LibType::Display;
    }

}
