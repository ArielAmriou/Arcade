/*
** EPITECH PROJECT, 2026
** Arcade
** File description:
** Game
*/

#ifndef GAME_HPP
    #define GAME_HPP

#include <array>
#include "Arcade.hpp"
#include "IGameModule.hpp"

namespace arc {

    constexpr int GRIDX = 16;
    constexpr int GRIDY = 9;
    constexpr int SIZE = GRIDX * GRIDY;

    class GameSnake : public IGameModule {
        public:
            GameSnake();
            ~GameSnake() {};

            enum class Box {
                Head,
                Tail,
                Body,
                Turn,
                Apple,
                None,
            };

            void simulate(const Event) noexcept;
            Assets getAssets() noexcept;
            std::pair<Entities, Sounds> getElements() noexcept;
            bool isOpen() noexcept {return _open;}
            std::vector<Command> loadCommand() noexcept;
    
            void exit(Signal, std::vector<std::string>);

        private:
            static const Assets _assets;
            int _apple;
            int _rotation;
            std::size_t _tick;
            std::vector<Event> _events;
            std::vector<std::size_t> _snake;
            float _eat = false;
            bool _open = true;
            bool _tab = false;
            bool _shift = false;
            std::vector<Command> _commands;
            bool _loadBackground = false;
            size_t _score = 0;

            void drawSnakePart(
                std::reference_wrapper<Entities> entities, size_t idx);
            void drawBody(
                std::reference_wrapper<Entities> entities, size_t idx);
            void drawTurnBody(
                std::reference_wrapper<Entities> entities, size_t idx);
            void drawTail(
                std::reference_wrapper<Entities> entities, size_t idx);
            Vector2f getPartPos(size_t part);
    };
}

#endif
