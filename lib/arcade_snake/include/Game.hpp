/*
** EPITECH PROJECT, 2026
** Arcade
** File description:
** Game
*/

#ifndef GAME_HPP
    #define GAME_HPP

#include <array>
#include "IGameModule.hpp"

namespace arc {

    constexpr int GRIDX = 16;
    constexpr int GRIDY = 9;
    constexpr int SIZE = GRIDX * GRIDY;

    class Game : public IGameModule {
        public:
            Game();
            ~Game() {};

            enum class Box {
                None,
                Ariel,
                Ilias,
            };

            void simulate(Event);
            Assets getAssets() {return _assets;}
            std::pair<Entities, Sounds> getElements();
            bool isOpen() {return _open;}
            SelectLibs libChanges(Libs);

        private:
            static const Assets _assets;
            int _apple;
            int _rotation;
            std::vector<std::size_t> _snake;
            float _eat = false;
            bool _open = true;
            // SelectLibs _libsSelected = std::make_pair(std::nullopt, std::nullopt);
            bool _tab = false;
            bool _shift = false;
    };
}

#endif
