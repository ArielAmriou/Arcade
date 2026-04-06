/*
** EPITECH PROJECT, 2026
** Arcade
** File description:
** GameMinesweeper
*/

#ifndef GAME_MINESWEEPER_HPP
    #define GAME_MINESWEEPER_HPP

#include <array>
#include <ctime>
#include "IGameModule.hpp"

namespace arc {

    constexpr int GRIDX = 16;
    constexpr int GRIDY = 16;
    constexpr int GRIDTOTAL = GRIDX * GRIDY;
    constexpr int DISPLAYY = GRIDY;
    constexpr int DISPLAYX = GRIDY * 16 / 9;
    constexpr int OFFSETX = (DISPLAYX - GRIDX) / 2;
    constexpr std::size_t NB_BOMB = 40;
    constexpr int MAXTIME = 3 * 60;
    constexpr std::size_t MAXTIMELEN = 3;
    constexpr std::size_t MAXSCORELEN = 7;
    constexpr std::size_t MAXFLAGLEN = 2;
    constexpr std::size_t TILESCORE = 10;
    constexpr std::size_t FLAGSCORE = 100;
    constexpr std::size_t MAXSCORE = TILESCORE * (GRIDTOTAL - NB_BOMB)
                                        + (FLAGSCORE * NB_BOMB);

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
                Bomb,
                None
            };

            enum class MSSound {
                Background,
                Digging,
                Hammer,
                Explosion,
                Winner,
                Error,
                NBSound,
            };

            void simulate(const Event) noexcept;
            Assets getAssets() noexcept;
            std::pair<Entities, Sounds> getElements() noexcept;
            bool isOpen() noexcept {return _open;}
            std::vector<Command> loadCommand() noexcept;
    
            void exit(Signal, std::vector<std::string>, bool);

        private:
            static const Assets _assets;
            bool _open = true;
            std::vector<Command> _commands;
            std::array<MSAsset, GRIDTOTAL> _showGrid;
            std::array<MSAsset, GRIDTOTAL> _actualGrid;
            bool _start = false;
            bool _lost = false;
            bool _win = false;
            size_t _score = 0;
            size_t _flag = NB_BOMB;
            std::array<bool, static_cast<size_t>(MSSound::NBSound)> _play;
            std::chrono::_V2::steady_clock::time_point _lastTime;
            double _totalTime = MAXTIME;
            double _bombClock = 0;
            
            Vector2f getTilePos(std::size_t idx);
            std::optional<std::size_t> getTileClick(Vector2f);
            void initGrid(std::size_t start);
            MSAsset getNBBomb(std::size_t idx);
            bool isAsset(int dx, int dy, int x, int y, MSAsset asset);
            void discoverNextTile(std::size_t idx);
            MSAsset discoverTile(int dx, int dy, int x, int y);
            void bombDiscovery();
            void updateClock();
            std::string nbTostring(std::size_t nb, std::size_t len);
            void displayInfo(std::reference_wrapper<Entities>);
            void mouseEvent(Event);
            void revealTile(std::size_t idx);
            void placeFlag(std::size_t idx);
            bool preCheck(Event);
    };
}

#endif
