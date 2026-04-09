/*
** EPITECH PROJECT, 2026
** Arcade
** File description:
** Game
*/

#ifndef GAME_HPP
    #define GAME_HPP

#include <string_view>
#include <unordered_map>
#include "Arcade.hpp"
#include "IGameModule.hpp"
#include "Score.hpp"
#include "Utils.hpp"

namespace arc {

    constexpr std::size_t LIBMAXSIZE = 25;
    constexpr Vector2f TEXTSIZE = {0.25, 0.075};
    constexpr Vector2f TITLETEXTSIZE = {0.2, 0.1};
    constexpr Vector2f LIBTEXTSIZE = {0.25, 0.05};
    constexpr Vector2f SCORETEXTSIZE = {0.25, 0.04};
    constexpr Vector2f TITLETEXTPOS = {0.4, 0.05};

    constexpr float LIBGAPY = 0.075;
    constexpr float LIBPOSY = 0.3;
    constexpr float DISPLAYPOSX = 0.05;
    constexpr float SUBTITLEPOSY = 0.2;
    constexpr float TEXTPOSXMID = 0.375;
    constexpr float NAMEPOSX = 0.7;
    constexpr float NAMEPOSY = 0.3;
    constexpr float SCORETEXTPOSY = 0.625;

    constexpr std::size_t NBSHOWLIBS = 4;
    constexpr std::size_t TEXTWIDTH = 15;

    constexpr std::size_t NBSCORE = 9;
    constexpr float SCOREPOSX = 0.05;
    constexpr float SCOREPOSY = 0.725;
    constexpr float SCOREGAPX = 0.325;
    constexpr float SCOREGAPY = 0.1;
    constexpr std::size_t SCOREBYCOLUMN = 3;

    class GameMenu : public IGameModule {
        public:
            GameMenu();
            ~GameMenu() {};

            enum Column {
                Display,
                Game,
                Name,
            };

            void simulate(const Event) noexcept;
            Assets getAssets() noexcept {return _assets;}
            std::pair<Entities, Sounds> getElements() noexcept;
            bool isOpen() noexcept {return _open;}
            std::vector<Command> loadCommand() noexcept;

        private:
            static const Assets _assets;
            static const std::unordered_map<Action, std::string> _letter;
            bool _open = true;
            std::vector<Command> _commands;
            bool _loadBackground = true;
            SplitLibs _splitLibs;
            std::size_t _selectLibType = 0;
            std::vector<LibType> _libType =
                {LibType::Display, LibType::Game, LibType::None};
            std::string _name = "___";
            std::set<size_t, std::greater<size_t>> _userScore;
            Score _score;
            std::pair<std::size_t, std::size_t> _idxs = std::make_pair(0, 0);

            std::string formatPath(std::string str);
            std::string formatLen(std::string, std::size_t);
            void changeSelectLib(Action, std::size_t,
                std::reference_wrapper<std::size_t>);
            void showNLibs(std::vector<std::string>, float posx, size_t n,
                size_t idx, std::reference_wrapper<Entities> entities);
            void showScore(std::reference_wrapper<Entities> entities);
            void changeName(Action);
            void printString(std::reference_wrapper<Entities> entities,
                std::vector<RGBA>);
    };
}

#endif
