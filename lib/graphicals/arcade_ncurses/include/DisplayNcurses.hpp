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
#define FRAMERATE (1000000/30)
#define ESC_CHARACTER 27
#define DOWN_ARROW 0x42
#define UP_ARROW 0x41
#define RIGHT_ARROW 0x43
#define LEFT_ARROW 0x44

namespace arc {

    class DisplayNcurses : public IDisplayModule {
    public:
        DisplayNcurses();
        ~DisplayNcurses() override;

        [[nodiscard]] Event getEvent() noexcept;
        int setAssets(const Assets assets) noexcept;
        void drawGame(const std::pair<Entities, Sounds> elements) noexcept;

    private:
        bool _quit = false;
        WINDOW* _window;
        std::vector<std::string> _assets;
        static const std::unordered_map<mmask_t, Action> _mouseButtonMapNcurses;
        static const std::unordered_map<int, Action> _keyMap;
    };
}

#endif

