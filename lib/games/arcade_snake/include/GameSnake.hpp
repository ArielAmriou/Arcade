/*
** EPITECH PROJECT, 2026
** Arcade
** File description:
** Game
*/

#ifndef GAME_HPP
    #define GAME_HPP

#include <array>
#include <chrono>
#include "Arcade.hpp"
#include "IGameModule.hpp"

namespace arc {

    constexpr int GRIDX = 16;
    constexpr int GRIDY = 9;
    constexpr int SIZE = GRIDX * GRIDY;
    constexpr std::array<float, 4> ANGLE = {0, 90, 180, 270};
    constexpr std::size_t GAIN = 10;
    constexpr double MOVETIME = 0.15;
    constexpr std::size_t STARTBODYSIZE = 3;

    class GameSnake : public IGameModule {
        public:
            GameSnake();
            ~GameSnake() {};

            enum SnakeAsset {
                Head,
                Tail,
                Body,
                Turn,
                Apple,
                None,
            };

            enum Direction {
                Top,
                Right,
                Bottom,
                Left,
            };

            enum SnakeSound {
                Background,
                PickUp,
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
            std::vector<Event> _events;
            std::vector<std::size_t> _snake;
            float _eat = false;
            bool _open = true;
            std::vector<Command> _commands;
            bool _loadBackground = false;
            size_t _score = 0;
            std::chrono::_V2::steady_clock::time_point _lastTime;
            double _totalTime = 0;

            void drawSnakePart(
                std::reference_wrapper<Entities> entities, size_t idx);
            void drawBody(
                std::reference_wrapper<Entities> entities, size_t idx);
            void drawTurnBody(
                std::reference_wrapper<Entities> entities, size_t idx);
            void drawTail(
                std::reference_wrapper<Entities> entities, size_t idx);
            Vector2f getPartPos(size_t part);
            float getAngle(Direction turn) {return ANGLE[turn];}
            void spawnApple();
            bool checkSnakeCollision(size_t idx);
            bool moveHead(float angle, bool condition, int newPos,
                std::reference_wrapper<size_t> head);
            void changeDir();
            bool prevCheck(Event);
            void moveSnake(size_t);
            void updateClock();
    };
}

#endif
