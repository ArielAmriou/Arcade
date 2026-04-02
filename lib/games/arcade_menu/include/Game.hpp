/*
** EPITECH PROJECT, 2026
** Arcade
** File description:
** Game
*/

#ifndef GAME_HPP
    #define GAME_HPP

#include "Arcade.hpp"
#include "IGameModule.hpp"

namespace arc {
    class Game : public IGameModule {
        public:
            Game() {};
            ~Game() {};

            void simulate(const Event) noexcept;
            Assets getAssets() noexcept {return _assets;}
            std::pair<Entities, Sounds> getElements() noexcept;
            bool isOpen() noexcept {return _open;}
            std::vector<Command> loadCommand() noexcept;

        private:
            static const Assets _assets;
            bool _open = true;
            std::vector<Command> _commands;
            bool _loadBackground = true;
    };
}

#endif
