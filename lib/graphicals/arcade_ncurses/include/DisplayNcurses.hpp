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
#define WHITE std::tuple(255, 255, 255, 255)
#define RED std::tuple(255, 0, 0, 255)
#define BLUE std::tuple(0, 0, 255, 255)
#define GREEN std::tuple(0, 255, 0, 255)

namespace arc {

    class DisplayNcurses : public IDisplayModule {
    public:
        DisplayNcurses();
        ~DisplayNcurses() override;
        [[nodiscard]] Event getEvent() noexcept;
        int setAssets(const Assets assets) noexcept;
        void drawGame(const std::pair<Entities, Sounds> elements) noexcept;
        enum class Colors
        {
            White = 1,
            Red = 2,
            Green = 3,
            Blue = 4,
        };

    private:
        bool _quit = false;
        WINDOW* _window;
        std::vector<std::string> _assets;
        static const std::unordered_map<mmask_t, Action> _mouseButtonMapNcurses;
        static const std::unordered_map<int, Action> _keyMap;
        static const std::unordered_map<Colors, std::tuple<int, int, int, int>> _color;
        void initColors();
        Colors getColorId(const std::unique_ptr<IEntity> &entity);
    };
}

#endif

