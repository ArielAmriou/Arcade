/*
** EPITECH PROJECT, 2026
** Arcade
** File description:
** Core
*/

#ifndef CORE_HPP_
#define CORE_HPP_

#include <string>
#include "DLLoader.hpp"
#include "IDisplayModule.hpp"
#include "IGameModule.hpp"

#define DEFAULT_GAME_PATH "lib/libarcade_snake.so"

namespace arc {

    class Core {
        public:
            Core(const std::string &);
            void play();

            static void help() noexcept;
        private:
            DLLoader _loader;
            std::unique_ptr<IGameModule> _game;
            std::unique_ptr<IDisplayModule> _display;
    };
}

#endif /* !CORE_HPP_ */
