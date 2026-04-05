/*
** EPITECH PROJECT, 2026
** Arcade
** File description:
** GameMinesweeper
*/

#ifndef GAME_MINESWEEPER_HPP
    #define GAME_MINESWEEPER_HPP

#include "IGameModule.hpp"

namespace arc {
    class GameMinesweeper : public IGameModule {
        public:
            GameMinesweeper() {};
            ~GameMinesweeper() {};

            enum class MSAsset {
                Empty,
                One,
                Two,
                Three,
                Four,
                Five,
                Six,
                Seven,
                Height,
                Cover,
                Flag,
                Bomb
            };

            enum class MSSound {
                Background,
                Digging,
                Hammer,
                Explosion,
            };

            void simulate(const Event) noexcept;
            Assets getAssets() noexcept;
            std::pair<Entities, Sounds> getElements() noexcept;
            bool isOpen() noexcept {return _open;}
            std::vector<Command> loadCommand() noexcept;
    
            void exit(Signal, std::vector<std::string>);

        private:
            static const Assets _assets;
            bool _open = true;
            std::vector<Command> _commands;
            bool _loadBackground = false;
    };
}

#endif
