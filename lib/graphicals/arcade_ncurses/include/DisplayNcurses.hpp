/*
** EPITECH PROJECT, 2026
** Arcade
** File description:
** Display
*/

#ifndef DISPLAYNCURSES_HPP
#define DISPLAYNCURSES_HPP
#include <ncurses.h>
#include <unordered_map>
#include "IDisplayModule.hpp"
#include "Arcade.hpp"

#define ERROR (-1)
#define SUCCES 0
#define ESC_CHARACTER (-27)
#define DOWN_ARROW 0x42
#define UP_ARROW 0x41
#define RIGHT_ARROW 0x43
#define LEFT_ARROW 0x44

namespace arc {

    class DisplayNcurses : public IDisplayModule {
    public:
        DisplayNcurses();
        ~DisplayNcurses() override;

        [[nodiscard]] Event getEvent() override;
        int setAssets(Assets assets) override;
        void drawGame(std::reference_wrapper<std::pair<Entities, Sounds>> elements) override;

    private:
        bool _quit = false;
        WINDOW* _window;
        std::vector<char> _assets;
        static const std::unordered_map<int, Action> _mouseButtonMap;
        static const std::unordered_map<int, Action> _keyMap;
    };
}

#endif

