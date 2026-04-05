/*
** EPITECH PROJECT, 2026
** Arcade
** File description:
** GameMinesweeper
*/

#ifndef GAME_MINESWEEPER_HPP
    #define GAME_MINESWEEPER_HPP

#include <array>
#include "IGameModule.hpp"

namespace arc {

    constexpr int GRIDX = 16;
    constexpr int GRIDY = 16;
    constexpr int GRIDTOTAL = GRIDX * GRIDY;
    constexpr int DISPLAYY = GRIDY;
    constexpr int DISPLAYX = GRIDY * 16 / 9;
    constexpr int OFFSETX = (DISPLAYX - GRIDX) / 2;
    constexpr size_t NB_BOMB = 40;

    class GameMinesweeper : public IGameModule {
        public:
            GameMinesweeper();
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
            std::array<MSAsset, GRIDTOTAL> _showGrid;
            std::array<MSAsset, GRIDTOTAL> _actualGrid;
            bool _start = false;
            
            Vector2f getTilePos(std::size_t idx);
            std::optional<std::size_t> getTileClick(Vector2f);
            void initGrid(std::size_t start);
            MSAsset getNBBomb(std::size_t idx);
            bool isAsset(int dx, int dy, int x, int y, MSAsset asset);
    };
}

#endif
