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

    class GameMenu : public IGameModule {
        public:
            GameMenu();
            ~GameMenu() {};

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
            void changeSelectLib(Action, std::size_t, std::reference_wrapper<std::size_t>);
            void showNLibs(std::vector<std::string>, float posx, size_t n,
                size_t idx, std::reference_wrapper<Entities> entities);
            void showScore(std::reference_wrapper<Entities> entities);
            void changeName(Action);
    };
}

#endif
