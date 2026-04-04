/*
** EPITECH PROJECT, 2026
** Arcade
** File description:
** Core
*/

#ifndef CORE_HPP_
#define CORE_HPP_

#include <string>
#include <list>
#include <functional>
#include "DLLoader.hpp"
#include "IDisplayModule.hpp"
#include "IGameModule.hpp"
#include "Exceptions.hpp"

#define DEFAULT_GAME_PATH "lib/arcade_menu.so"

namespace arc {
    class Core {
        public:
            Core(const std::string &);
            ~Core() = default;
            void play();

            static void help() noexcept;
            void loadGameModule(const std::string &,
                const std::exception &e=arc::exceptions::LibraryLoadError());
            void loadDisplayModule(const std::string &,
                const std::exception &e=arc::exceptions::LibraryLoadError());
            void execCommand(const std::vector<Command>);
        
            void loadDisplay(std::vector<std::string>);
            void loadGame(std::vector<std::string>);
            void restartGame(std::vector<std::string>);
            void BackToMenu(std::vector<std::string>);
            void loadUser(std::vector<std::string>);
            void loadScore(std::vector<std::string>);

            void loadAssets();
        private:
            DLLoader _loader;
            std::unique_ptr<IGameModule> _game;
            std::unique_ptr<IDisplayModule> _display;
            std::string _gamePath = DEFAULT_GAME_PATH;
            std::string _user = "___";

            std::unordered_map<arc::Signal, std::function<void(std::vector<std::string>)>> _commands;

    };
}

#endif /* !CORE_HPP_ */
