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
#include "Exceptions.hpp"

#define DEFAULT_GAME_PATH "lib/libarcade_snake.so"

namespace arc {

    class Core {
        public:
            Core(const std::string &);
            ~Core() = default;
            void play();

            static void help(const std::string &path) noexcept;
            void loadGameModule(const std::string &,
                const std::exception &e=arc::exceptions::LibraryLoadError());
            void loadDisplayModule(const std::string &,
                const std::exception &e=arc::exceptions::LibraryLoadError());
        private:
            DLLoader _loader;
            std::unique_ptr<IGameModule> _game;
            std::unique_ptr<IDisplayModule> _display;
    };
}

#endif /* !CORE_HPP_ */
