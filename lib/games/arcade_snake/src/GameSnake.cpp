/*
** EPITECH PROJECT, 2026
** Arcade
** File description:
** Game
*/

#include <cstdlib> 
#include <ctime>
#include <chrono> 
#include "GameSnake.hpp"
#include "Entity.hpp"
#include "Sound.hpp"
#include "IGameModule.hpp"

arc::GameSnake::GameSnake() : _rotation(getAngle(Direction::Right))
{
    srand((unsigned)time(0));
    int head = rand() % SIZE;
    if (head % GRIDX <= STARTBODYSIZE)
        head += STARTBODYSIZE;
    for (std::size_t i = head; i >= head - STARTBODYSIZE; i--)
        _snake.push_back(i);
    spawnApple();
}

arc::Assets arc::GameSnake::getAssets() noexcept
{
    _loadBackground = true;
    return _assets;
}

void arc::GameSnake::simulate(const Event event) noexcept
{
    size_t head = _snake[0];
    
    if (prevCheck(event)
        || moveHead(getAngle(Direction::Top), (head >= GRIDX), -GRIDX, head)
        || moveHead(getAngle(Direction::Right),
            (head % GRIDX != GRIDX - 1), 1, head)
        || moveHead(getAngle(Direction::Bottom), (head < SIZE - GRIDX), GRIDX, head)
        || moveHead(getAngle(Direction::Left), (head % GRIDX != 0), -1, head))
        return;
    moveSnake(head);
}

std::pair<arc::Entities, arc::Sounds> arc::GameSnake::getElements() noexcept
{
    Entities entities;
    Sounds sounds;

    for (size_t i = 0; i < _snake.size(); i++)
        drawSnakePart(entities, i);
    Entity tmp(SnakeAsset::Apple, getPartPos(_apple),
        {1.0 / GRIDX, 1.0 / GRIDY}, 0);
    entities.push_back(std::make_unique<arc::Entity>(tmp));
    if (_loadBackground) {
        Sound background(SnakeSound::Background, true);
        sounds.push_back(std::make_unique<arc::Sound>(background));
        _loadBackground = false;
    }
    if (_eat) {
        Sound pickUp(SnakeSound::PickUp, false);
        sounds.push_back(std::make_unique<arc::Sound>(pickUp));
        _eat = false;
    }
    return std::make_pair(std::move(entities), std::move(sounds));
}

std::vector<arc::Command> arc::GameSnake::loadCommand() noexcept
{
    std::vector<Command> cpy(_commands);

    _commands.clear();
    return cpy;
}

void arc::GameSnake::exit(Signal signal, std::vector<std::string> args)
{
    if (_score != 0) {
        std::vector<std::string> argsScore;
        argsScore.push_back(std::to_string(_score));
        _commands.push_back(std::make_pair(Signal::LoadScore, argsScore));
    }
    _commands.push_back(std::make_pair(signal, args));
}

void arc::GameSnake::drawSnakePart(
    std::reference_wrapper<Entities> entities, size_t idx)
{
    if (idx == 0) {
        auto snake = _snake[idx];
        Entity part(SnakeAsset::Head, getPartPos(snake),
            {1.0 / GRIDX, 1.0 / GRIDY}, _rotation);
        entities.get().push_back(std::make_unique<arc::Entity>(part));
    } else if (idx == _snake.size() - 1)
        drawTail(entities, idx);
    else
        drawBody(entities, idx);
}

void arc::GameSnake::drawBody(
    std::reference_wrapper<Entities> entities, size_t idx)
{
    auto snake = _snake[idx];
    auto before = _snake[idx - 1];
    auto after = _snake[idx + 1];
    float rotation = 0;

    if (abs(before - after) != 2 && abs(before - after) != GRIDX * 2)
        return drawTurnBody(entities, idx);
    if (before == snake - 1)
        rotation = getAngle(Direction::Left);
    if (before == snake + 1)
        rotation = getAngle(Direction::Right);
    Entity part(SnakeAsset::Body, getPartPos(snake),
            {1.0 / GRIDX, 1.0 / GRIDY}, rotation);
    entities.get().push_back(std::make_unique<arc::Entity>(part));
}

void arc::GameSnake::drawTurnBody(
    std::reference_wrapper<Entities> entities, size_t idx)
{
    auto snake = _snake[idx];
    auto before = _snake[idx - 1];
    auto after = _snake[idx + 1];
    float rotation = 0;

    if ((before % GRIDX == snake % GRIDX && before > snake
        && after + 1 == snake) || (after % GRIDX == snake % GRIDX
        && after > snake && before + 1 == snake))
        rotation = getAngle(Direction::Right);
    if ((before % GRIDX == snake % GRIDX && before < snake
        && after + 1 == snake) || (after % GRIDX == snake % GRIDX
        && after < snake && before + 1 == snake))
        rotation = getAngle(Direction::Bottom);
    if ((before % GRIDX == snake % GRIDX && before < snake
        && after - 1 == snake) || (after % GRIDX == snake % GRIDX
        && after < snake && before - 1 == snake))
        rotation = getAngle(Direction::Left);
    Entity part(SnakeAsset::Turn, getPartPos(snake),
            {1.0 / GRIDX, 1.0 / GRIDY}, rotation);
    entities.get().push_back(std::make_unique<arc::Entity>(part));
}

void arc::GameSnake::drawTail(
    std::reference_wrapper<Entities> entities, size_t idx)
{
    auto snake = _snake[idx];
    auto before = _snake[idx - 1];
    float rotation = 0;

    if (before == snake - 1)
        rotation = getAngle(Direction::Left);
    if (before > snake)
        rotation = getAngle(Direction::Bottom);
    if (before == snake + 1)
        rotation = getAngle(Direction::Right);
    Entity part(SnakeAsset::Tail, getPartPos(snake),
            {1.0 / GRIDX, 1.0 / GRIDY}, rotation);
    entities.get().push_back(std::make_unique<arc::Entity>(part));
}

arc::Vector2f arc::GameSnake::getPartPos(size_t part)
{ 
    float x = (float)(part % GRIDX) / GRIDX;
    float y = (part - (float)(part % GRIDX)) / GRIDX / GRIDY;
    return std::make_pair(x, y);
}

void arc::GameSnake::spawnApple()
{
    if (_snake.size() == GRIDX * GRIDY) {
        exit(Signal::RestartGame, {});
        return;
    }
    while (true) {
        int nb = rand() % SIZE;
        if (checkSnakeCollision(nb))
            continue;
        _apple = nb;
        break;
    }
}

bool arc::GameSnake::checkSnakeCollision(size_t idx)
{
    bool collision = false;

    for (auto snake: _snake) {
        if (snake == idx) {
            collision = true;
            continue;
        }
    }
    return collision;
}

bool arc::GameSnake::moveHead(float angle, bool condition, int newPos,
    std::reference_wrapper<size_t> head)
{
    bool quit = false;

    if (_rotation == angle) {
        if (condition)
            head.get() += newPos;
        else {
            exit(Signal::RestartGame, {});
            quit = true;
        }
    }
    return quit;
}

void arc::GameSnake::changeDir()
{
    auto prev = _rotation;

    for (auto myevent: _events) {
        auto action = myevent.first;
        if ((action == Action::Z || action == Action::Up)
            && _rotation != getAngle(Direction::Bottom))
            _rotation = getAngle(Direction::Top);
        if ((action == Action::S || action == Action::Down)
            && _rotation != getAngle(Direction::Top))
            _rotation = getAngle(Direction::Bottom);
        if ((action == Action::Q || action == Action::Left)
            && _rotation != getAngle(Direction::Right))
            _rotation = getAngle(Direction::Left);
        if ((action == Action::D || action == Action::Right)
            && _rotation != getAngle(Direction::Left))
            _rotation = getAngle(Direction::Right);
    }
    if (prev != _rotation && (int)(prev / getAngle(Direction::Right)) % 2
        == (int)(_rotation / getAngle(Direction::Right)) % 2)
        _rotation = prev;
    _events.clear();
}

bool arc::GameSnake::prevCheck(Event event)
{
    bool quit = false;

    if (!quit) {
        _events.push_back(event);
        updateClock();
        if (_totalTime >= MOVETIME) {
            _totalTime = 0;
            changeDir();
        } else
            quit = true;
    }
    return quit;
}

void arc::GameSnake::moveSnake(size_t head)
{
    int tail = _snake.back();
    for (int i = _snake.size() - 1; i > 0; i--)
        _snake[i] = _snake[i - 1];
    _snake[0] = head;
    if (head == _apple) {
        _score += GAIN;
        _eat = true;
        _snake.push_back(tail);
        spawnApple();
    }
    for (std::size_t i = 1; i < _snake.size(); i++) {
        if (_snake[0] == _snake[i]) {
            exit(Signal::RestartGame, {});
            break;
        }
    }
}

void arc::GameSnake::updateClock()
{
    auto now = std::chrono::steady_clock::now();
    auto diff = std::chrono::duration<double>(now - _lastTime).count();

    _totalTime += diff;
    _lastTime = now;
}

const std::pair<std::vector<std::string>, std::vector<std::string>> arc::GameSnake::_assets = {
    {
        "assets/snake/snakeHead",
        "assets/snake/snakeTail",
        "assets/snake/snakeBody",
        "assets/snake/snakeTurn",
        "assets/snake/apple",
    }, {
        "assets/snake/background.wav",
        "assets/snake/pickUp.wav"
    }
};

extern "C"
{
    std::unique_ptr<arc::IGameModule> makeInstance()
    {
        return std::make_unique<arc::GameSnake>();
    }
    arc::LibType getLibType()
    {
        return arc::LibType::Game;
    }
}
