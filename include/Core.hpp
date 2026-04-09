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
#include "Utils.hpp"

#define DEFAULT_GAME_PATH "lib/arcade_menu.so"

namespace arc {
    
    class Core {
        public:
            Core(const std::string &);
            ~Core() = default;
            void play();

            static void help() noexcept;
        private:
            std::vector<DLLoader> _gameLoader;
            std::vector<DLLoader> _displayLoader;
            std::unique_ptr<IGameModule> _game;
            std::unique_ptr<IDisplayModule> _display;
            std::string _user = "___";
            std::unordered_map<arc::Signal, std::function<void(std::vector<std::string>)>> _commands;
            std::unordered_map<arc::Action, std::function<void()>> _builtins;
            SplitLibs _splitLibs;
            std::size_t _gameIdx;
            std::size_t _displayIdx;

            void loadGameModule(const std::string &);
            void loadDisplayModule(const std::string &);
            void execCommand(const std::vector<Command>);
            void execBuiltin(const Action);
        
            void loadDisplay(std::vector<std::string> = std::vector<std::string>());
            void loadGame(std::vector<std::string> = std::vector<std::string>());
            void restartGame(std::vector<std::string> = std::vector<std::string>());
            void BackToMenu(std::vector<std::string> = std::vector<std::string>());
            void loadUser(std::vector<std::string> = std::vector<std::string>());
            void loadScore(std::vector<std::string> = std::vector<std::string>());

            void iterDisplay();
            void iterGame();

            void loadAssets();

            void setFunctions();

    };
}

#endif /* !CORE_HPP_ */
