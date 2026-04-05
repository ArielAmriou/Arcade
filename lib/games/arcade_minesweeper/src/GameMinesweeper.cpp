/*
** EPITECH PROJECT, 2026
** Arcade
** File description:
** GameMinesweeper
*/

#include <ctime>
#include <chrono> 
#include "GameMinesweeper.hpp"
#include "Sound.hpp"
#include "Entity.hpp"

#include <iostream>
#define DEBUG(value) std::cout << "\e[0;35m" << "DEBUG: " <<  "\e[0;37m" << "\t" << value << std::endl;

arc::GameMinesweeper::GameMinesweeper()
    : _lastTime(std::chrono::steady_clock::now())
{
    srand((unsigned)time(0));
    for (auto &box: _showGrid)
        box = MSAsset::Cover;
    for (auto &box: _actualGrid)
        box = MSAsset::Empty;
    for (auto &sound: _play)
        sound = false;
}

void arc::GameMinesweeper::simulate(const Event event) noexcept
{
    updateClock();
    if (event.first == Action::Tab) {
        exit(Signal::BackToMenu, {}, false);
        return;
    }
     if (event.first == Action::Enter) {
        exit(Signal::RestartGame, {}, false);
        return;
    }
    if (_totalTime <= 0)
        _lost = true;
    if (_win)
        return;
    if (!_win && _score >= MAXSCORE) {
        _win = true;
        _score *= MAXTIME - _totalTime;
        _play[static_cast<size_t>(MSSound::Winner)] = true;
        std::vector<std::string> argsScore = {std::to_string(_score)};
        _commands.push_back(std::make_pair(Signal::LoadScore, argsScore));
        return;
    }
    if (_lost)
        return bombDiscovery();
    if (event.first == Action::LeftMouse) {
        auto tmp = getTileClick(event.second);
        if (tmp.has_value()) {
            auto idx = tmp.value();
            if (!_start) {
                _start = true;
                initGrid(idx);
            }
            auto tile = discoverTile(idx % GRIDX, idx / GRIDX, 0, 0);
            if (tile == MSAsset::Bomb) {
                _lost = true;
                _bombClock = 0;
                _play[static_cast<size_t>(MSSound::Explosion)] = true;
                _score = 0;
            }
            else if (tile != MSAsset::None)
                _play[static_cast<size_t>(MSSound::Digging)] = true;
        }
    }
    if (event.first == Action::RightMouse && _start) {
        auto tmp = getTileClick(event.second);
        if (tmp.has_value()) {
            auto idx = tmp.value();
            if (_showGrid[idx] == MSAsset::Cover) {
                if (_flag == 0) {
                    _play[static_cast<size_t>(MSSound::Error)] = true;
                    return;
                }
                _showGrid[idx] = MSAsset::Flag;
                _play[static_cast<size_t>(MSSound::Hammer)] = true;
                _score += FLAGSCORE;
                _flag--;
            } else if (_showGrid[idx] == MSAsset::Flag) {
                _showGrid[idx] = MSAsset::Cover;
                _play[static_cast<size_t>(MSSound::Hammer)] = true;
                _flag++;
                _score -= FLAGSCORE;
            }
        }
    }
}

arc::Assets arc::GameMinesweeper::getAssets() noexcept
{
    _play[static_cast<size_t>(MSSound::Background)] = true;
    return _assets;
}

std::pair<arc::Entities, arc::Sounds> arc::GameMinesweeper::getElements() noexcept
{
    Entities entities;
    Sounds sounds;

    Entity timeStr(-1, {0.05, 0.15}, {0.1, 0.05}, "Timer:");
    entities.push_back(std::make_unique<arc::Entity>(timeStr));
    Entity time(-1, {0.075, 0.25}, {0.05, 0.05}, nbTostring((std::size_t)_totalTime, MAXTIMELEN));
    entities.push_back(std::make_unique<arc::Entity>(time));
    Entity flagStr(-1, {0.05, 0.45}, {0.1, 0.05}, "Flags:");
    entities.push_back(std::make_unique<arc::Entity>(flagStr));
    Entity flag(-1, {0.08, 0.55}, {0.04, 0.05}, nbTostring(_flag, MAXFLAGLEN));
    entities.push_back(std::make_unique<arc::Entity>(flag));
    Entity scoreStr(-1, {0.05, 0.7}, {0.1, 0.05}, "Score:");
    entities.push_back(std::make_unique<arc::Entity>(scoreStr));
    Entity score(-1, {0.05, 0.8}, {0.1, 0.05}, nbTostring(_score, MAXSCORELEN));
    entities.push_back(std::make_unique<arc::Entity>(score));
    for (std::size_t i = 0; i < GRIDTOTAL; i++) {
        Entity box(static_cast<size_t>(_showGrid[i]), getTilePos(i), {1.0 / DISPLAYX, 1.0 / DISPLAYY});
        entities.push_back(std::make_unique<arc::Entity>(box));
    }
    if (_play[static_cast<size_t>(MSSound::Background)]) {
        Sound background(static_cast<size_t>(MSSound::Background), true);
        sounds.push_back(std::make_unique<arc::Sound>(background));
        _play[static_cast<size_t>(MSSound::Background)] = false;
    }
    for (std::size_t i = 1; i < _play.size(); i++) {
        if (_play[i]) {
            Sound sound(i, false);
            sounds.push_back(std::make_unique<arc::Sound>(sound));
            _play[i] = false;
        }
    }
    return std::make_pair(std::move(entities), std::move(sounds));
}

std::vector<arc::Command> arc::GameMinesweeper::loadCommand() noexcept
{
    std::vector<Command> cpy(_commands);

    _commands.clear();
    return cpy;
}

void arc::GameMinesweeper::exit(
    Signal signal, std::vector<std::string> args, bool score)
{
    if (_score != 0 && score) {
        std::vector<std::string> argsScore;
        argsScore.push_back(std::to_string(_score));
        _commands.push_back(std::make_pair(Signal::LoadScore, argsScore));
    }
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

void arc::GameMinesweeper::discoverNextTile(std::size_t idx)
{
    int x = idx % GRIDX;
    int y = idx / GRIDX;

    for (int dy = -1; dy <= 1; dy++) {
        for (int dx = -1; dx <= 1; dx++) {
            discoverTile(dx, dy, x, y);
        }
    }
}

arc::GameMinesweeper::MSAsset arc::GameMinesweeper::discoverTile(
    int dx, int dy, int x, int y)
{
    int nx = x + dx;
    int ny = y + dy;
    auto idx = ny * GRIDX + nx;
    MSAsset value = MSAsset::None;

    if (nx >= 0 && nx < GRIDX && ny >= 0 && ny < GRIDY
        && _showGrid[idx] != _actualGrid[idx]
        && _showGrid[idx] != MSAsset::Flag) {
        _showGrid[idx] = _actualGrid[idx];
        _score += 10;
        value = _showGrid[idx];
        if (_showGrid[idx] == MSAsset::Empty)
            discoverNextTile(idx);
    }
    return value;
}

void arc::GameMinesweeper::bombDiscovery()
{
    if (_bombClock < 0.4)
        return;
    _bombClock = 0;
    for (size_t i = 0; i < GRIDTOTAL; i++) {
        if (_actualGrid[i] == MSAsset::Bomb && _showGrid[i] != MSAsset::Bomb
            && _showGrid[i] != MSAsset::Flag) {
            _showGrid[i] = MSAsset::Bomb;
            _play[static_cast<size_t>(MSSound::Explosion)] = true;
            break;
        }
        if (_actualGrid[i] != MSAsset::Bomb && _showGrid[i] == MSAsset::Flag) {
            _showGrid[i] = MSAsset::Cover;
            _play[static_cast<size_t>(MSSound::Hammer)] = true;
            break;
        }
    }
}

void arc::GameMinesweeper::updateClock()
{
    auto now = std::chrono::steady_clock::now();
    auto diff = std::chrono::duration<double>(now - _lastTime).count();
    if (_lost)
        _bombClock += diff;
    else if (!_win && _start)
        _totalTime -= diff;
    _lastTime = now;
}

std::string arc::GameMinesweeper::nbTostring(size_t nb, size_t len)
{
    std::string str = std::to_string(nb);

    while (str.size() < len)
        str = "0" + str;
    return str;
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
        "assets/minesweeper/winner.wav",
        "assets/minesweeper/error.wav",
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
