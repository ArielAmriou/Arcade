/*
** EPITECH PROJECT, 2026
** Arcade
** File description:
** GameMinesweeper
*/

#include <ctime> 
#include "GameMinesweeper.hpp"
#include "Sound.hpp"
#include "Entity.hpp"

#include <iostream>
#define DEBUG(value) std::cout << "\e[0;35m" << "DEBUG: " <<  "\e[0;37m" << "\t" << value << std::endl;

arc::GameMinesweeper::GameMinesweeper()
{
    srand((unsigned)time(0));
    for (auto &box: _showGrid)
        box = MSAsset::Cover;
    for (auto &box: _actualGrid)
        box = MSAsset::Empty;
}

void arc::GameMinesweeper::simulate(const Event event) noexcept
{
    if (event.first == Action::Tab) {
        std::vector<std::string> args;
        exit(Signal::BackToMenu, args);
        return;
    }
    if (event.first == Action::LeftMouse) {
        auto tmp = getTileClick(event.second);
        if (tmp.has_value()) {
            if (!_start) {
                _start = true;
                initGrid(tmp.value());
            }
            _showGrid[tmp.value()] = _actualGrid[tmp.value()];
        }
    }
}

arc::Assets arc::GameMinesweeper::getAssets() noexcept
{
    _loadBackground = true;
    return _assets;
}

std::pair<arc::Entities, arc::Sounds> arc::GameMinesweeper::getElements() noexcept
{
    Entities entities;
    Sounds sounds;

    for (std::size_t i = 0; i < GRIDTOTAL; i++) {
        auto tmp = MSAsset::Empty;
        if (_start)
            tmp = _actualGrid[i];
        else
            tmp = _showGrid[i];
        Entity box(static_cast<size_t>(tmp), getTilePos(i), {1.0 / DISPLAYX, 1.0 / DISPLAYY});
        entities.push_back(std::make_unique<arc::Entity>(box));
    }
    if (_loadBackground) {
        Sound background(static_cast<size_t>(MSSound::Background), true);
        sounds.push_back(std::make_unique<arc::Sound>(background));
        _loadBackground = false;
    }
    return std::make_pair(std::move(entities), std::move(sounds));
}

std::vector<arc::Command> arc::GameMinesweeper::loadCommand() noexcept
{
    std::vector<Command> cpy(_commands);

    _commands.clear();
    return cpy;
}

void arc::GameMinesweeper::exit(Signal signal, std::vector<std::string> args)
{
    // if (_score != 0) {
    //     std::vector<std::string> argsScore;
    //     argsScore.push_back(std::to_string(_score));
    //     _commands.push_back(std::make_pair(Signal::LoadScore, argsScore));
    // }
    _commands.push_back(std::make_pair(signal, args));
}

arc::Vector2f arc::GameMinesweeper::getTilePos(std::size_t idx)
{
    float x = (float)(idx % GRIDX + OFFSETX) / DISPLAYX;
    float y =  (idx - (float)(idx % GRIDX)) / GRIDX / DISPLAYY;

    return std::make_pair(x, y);
}

std::optional<std::size_t> arc::GameMinesweeper::getTileClick(Vector2f pos)
{
    float x = pos.first;
    float y = pos.second;
    std::optional<std::size_t> idx = std::nullopt;

    if (x >= (float)OFFSETX / DISPLAYX && x <= (float)(OFFSETX + GRIDX) / DISPLAYX
        &&  y >= 0 && y <= (float)GRIDY / DISPLAYY) {
        size_t col = (size_t)(x * DISPLAYX - OFFSETX);
        size_t row = (size_t)(y * DISPLAYY);
        idx = row * GRIDX + col;
    }

    return idx;
}

void arc::GameMinesweeper::initGrid(size_t start)
{
    size_t i = 0;

    while (i < NB_BOMB) {
        auto nb = rand() % GRIDTOTAL;
        if (_actualGrid[nb] == MSAsset::Bomb)
            continue;
        _actualGrid[nb] = MSAsset::Bomb;
        if (getNBBomb(start) != MSAsset::Empty) {
            _actualGrid[nb] = MSAsset::Empty;
            continue;
        }
        i++;
    }
    for (std::size_t i = 0; i < GRIDTOTAL; i++) {
        if (_actualGrid[i] != MSAsset::Bomb)
            _actualGrid[i] = getNBBomb(i);
    }
}

arc::GameMinesweeper::MSAsset arc::GameMinesweeper::getNBBomb(std::size_t idx)
{
    size_t count = 0;
    int x = idx % GRIDX;
    int y = idx / GRIDX;

    for (int dy = -1; dy <= 1; dy++) {
        for (int dx = -1; dx <= 1; dx++) {
            count += isAsset(dx, dy, x, y, MSAsset::Bomb);
        }
    }
    return static_cast<MSAsset>(count);
}

bool arc::GameMinesweeper::isAsset(int dx, int dy, int x, int y, MSAsset asset)
{
    bool value = false;
    int nx = x + dx;
    int ny = y + dy;

    if (nx >= 0 && nx < GRIDX && ny >= 0 && ny < GRIDY
        && _actualGrid[ny * GRIDX + nx] == asset)
        value = true;
    return value;
}

const std::pair<std::vector<std::string>, std::vector<std::string>> arc::GameMinesweeper::_assets = {
    {
        "assets/minesweeper/empty",
        "assets/minesweeper/one",
        "assets/minesweeper/two",
        "assets/minesweeper/three",
        "assets/minesweeper/four",
        "assets/minesweeper/five",
        "assets/minesweeper/six",
        "assets/minesweeper/seven",
        "assets/minesweeper/height",
        "assets/minesweeper/cover",
        "assets/minesweeper/flag",
        "assets/minesweeper/bomb",
    }, {
        "assets/minesweeper/background.wav",
        "assets/minesweeper/digging.wav",
        "assets/minesweeper/hammer.wav",
        "assets/minesweeper/explosion.wav",
    }
};

extern "C"
{
    std::unique_ptr<arc::IGameModule> makeInstance()
    {
        return std::make_unique<arc::GameMinesweeper>();
    }
    arc::LibType getLibType()
    {
        return arc::LibType::Game;
    }
}
