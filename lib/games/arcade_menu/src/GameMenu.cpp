/*
** EPITECH PROJECT, 2026
** Arcade
** File description:
** Game
*/

#include <filesystem>
#include <string>
#include "DLLoader.hpp"
#include "GameMenu.hpp"
#include "Entity.hpp"
#include "Sound.hpp"

arc::GameMenu::GameMenu()
{
    _splitLibs = arc::utils::getSplitLibs();
}

void arc::GameMenu::simulate(const Event event) noexcept
{
    if (event.first == Action::Enter) {
        std::vector<std::string> userArgs;
        userArgs.push_back(_name);
        _commands.push_back(std::make_pair(Signal::LoadUser, userArgs));
        std::vector<std::string> displayArgs;
        displayArgs.push_back(_splitLibs.first[_idxs.first]);
        _commands.push_back(std::make_pair(Signal::LoadDisplay, displayArgs));
        std::vector<std::string> gameArgs;
        gameArgs.push_back(_splitLibs.second[_idxs.second]);
        _commands.push_back(std::make_pair(Signal::LoadGame, gameArgs));
        return;
    }
    if (event.first == Action::Right) {
        if (_selectLibType == _libType.size() - 1)
            _selectLibType = 0;
        else
            _selectLibType++;
    }
    if (event.first == Action::Left) {
        if (_selectLibType == 0)
            _selectLibType = _libType.size() - 1;
        else
            _selectLibType--;
    }
    if (_libType[_selectLibType] == LibType::Display)
        changeSelectLib(event.first, _splitLibs.first.size(), _idxs.first);
    else if (_libType[_selectLibType] == LibType::Game) {
        changeSelectLib(event.first, _splitLibs.second.size(), _idxs.second);
        _userScore = _score.getScores(_name, _splitLibs.second[_idxs.second]);
    } else
        changeName(event.first);
}

std::pair<arc::Entities, arc::Sounds> arc::GameMenu::getElements() noexcept
{
    Entities entities;
    Sounds sounds;

    std::vector<RGBA> selectLibsColor;
    for (std::size_t i = 0; i < _libType.size(); i++) {
        if (i == _selectLibType)
            selectLibsColor.push_back(RED);
        else
            selectLibsColor.push_back(WHITE);
    }
    printString(entities, selectLibsColor);
    showScore(entities);
    if (_loadBackground) {
        Sound background(0, true);
        sounds.push_back(std::make_unique<arc::Sound>(background));
        _loadBackground = false;
    }
    return std::make_pair(std::move(entities), std::move(sounds));
}

std::vector<arc::Command> arc::GameMenu::loadCommand() noexcept
{
    std::vector<Command> cpy(_commands);

    _commands.clear();
    return cpy;
}

std::string arc::GameMenu::formatPath(std::string str)
{
    std::string format(str);
    size_t pos = format.find(LIBPATH);
    if (pos != std::string::npos)
        format.replace(pos, LIBPATH.length() - pos, "\0");
    pos = format.find(LIBEXT);
    if (pos != std::string::npos)
        format.replace(pos, LIBEXT.length() - pos, "\0");
    return format;
}
std::string arc::GameMenu::formatLen(std::string str, std::size_t len)
{
    std::string format(str);
    if (format.size() >= len)
        return format;
    size_t add = (len - format.size()) / 2;
    for (size_t i = 0; i < add; i++)
        format = " " + format + " ";
    return format;
}

void arc::GameMenu::changeSelectLib(
    Action action, std::size_t size, std::reference_wrapper<std::size_t> idx)
{
    if (action == Action::Down) {
        if (size - 1 == idx.get())
            idx.get() = 0;
        else
            idx.get()++;
    }
    if (action == Action::Up) {
        if (0 == idx.get())
            idx.get() = size - 1;
        else
            idx.get()--;
    }
}

void arc::GameMenu::showNLibs(std::vector<std::string> list, float posx,
    size_t n, size_t idx, std::reference_wrapper<Entities> entities)
{
    auto start = idx;
    if (list.size() < n) {
        n = list.size();
        start = 0;
    }
    if (list.size() - idx < n) {
        start = list.size() - n;
    }
    for (size_t i = start; i < n + start; i++) {
        auto str = formatLen(formatPath(list[i]), LIBMAXSIZE);
        RGBA color = idx == i ? BLUE : WHITE; 
        Entity entity(-1, {posx, LIBPOSY + (LIBGAPY * (i - start))},
            LIBTEXTSIZE, str, color);
        entities.get().push_back(std::make_unique<arc::Entity>(entity));
    }
}

void arc::GameMenu::changeName(Action action)
{
    bool change = false;
    if (_letter.find(action) != _letter.end()) {
        std::string c = _letter.find(action)->second;
        auto pos = _name.find("_");
        if (pos != std::string::npos) {
            _name.replace(pos, 1, c);
            change = true;
        }
    }
    if (action == Action::Backspace) {
        auto pos = _name.find("_");
        if (pos != std::string::npos && pos != 0)
            _name.replace(pos - 1, 1, "_");
        if (pos == std::string::npos) {
            _name.replace(_name.size() - 1, 1, "_");
            change = true;
        }
    }
    if (change)
        _userScore = _score.getScores(_name, _splitLibs.second[_idxs.second]);
}

void arc::GameMenu::showScore(std::reference_wrapper<Entities> entities)
{
    auto iter = _userScore.begin();
    for (size_t i = 0; i < NBSCORE; i++) {
        std::string rang = std::to_string(i + 1);
        std::string score = "N/A";
        if (iter != _userScore.end()) {
            score = std::to_string(*iter);
            iter++;
        }
        Entity scores(-1, {SCOREPOSX + (i / SCOREBYCOLUMN * SCOREGAPX),
            SCOREPOSY + (i % SCOREBYCOLUMN * SCOREGAPY)},
            SCORETEXTSIZE, formatLen("##" + rang + ": " + score, LIBMAXSIZE));
        entities.get().push_back(std::make_unique<arc::Entity>(scores));
    }
}

void arc::GameMenu::printString(std::reference_wrapper<Entities> entities,
    std::vector<RGBA> selectLibsColor)
{
    Entity title(-1, TITLETEXTPOS, TITLETEXTSIZE, "Arcade", WHITE);
    entities.get().push_back(std::make_unique<arc::Entity>(title));
    Entity display(-1, {DISPLAYPOSX, SUBTITLEPOSY}, TEXTSIZE,
        formatLen("Display", TEXTWIDTH), selectLibsColor[Column::Display]);
    entities.get().push_back(std::make_unique<arc::Entity>(display));
    showNLibs(_splitLibs.first, DISPLAYPOSX, NBSHOWLIBS,
        _idxs.first, entities);
    Entity game(-1, {TEXTPOSXMID, SUBTITLEPOSY}, TEXTSIZE,
        formatLen("Game", TEXTWIDTH), selectLibsColor[Column::Game]);
    entities.get().push_back(std::make_unique<arc::Entity>(game));
    showNLibs(_splitLibs.second, TEXTPOSXMID, NBSHOWLIBS,
        _idxs.second, entities);
    Entity name(-1, {NAMEPOSX, SUBTITLEPOSY}, TEXTSIZE,
        formatLen("Name", TEXTWIDTH), selectLibsColor[Column::Name]);
    entities.get().push_back(std::make_unique<arc::Entity>(name));
    Entity user_name(-1, {NAMEPOSX, NAMEPOSY}, TEXTSIZE,
        formatLen(_name, TEXTWIDTH));
    entities.get().push_back(std::make_unique<arc::Entity>(user_name));
    Entity score(-1, {TEXTPOSXMID, SCORETEXTPOSY}, TEXTSIZE,
        formatLen("Score", TEXTWIDTH));
    entities.get().push_back(std::make_unique<arc::Entity>(score));
}

const std::pair<std::vector<std::string>, std::vector<std::string>>
    arc::GameMenu::_assets = {
    {

    }, {
        "assets/menu/background.wav",
    }
};

const std::unordered_map<arc::Action, std::string> arc::GameMenu::_letter = {
    {Action::A, "A"},
    {Action::B, "B"},
    {Action::C, "C"},
    {Action::D, "D"},
    {Action::E, "E"},
    {Action::F, "F"},
    {Action::G, "G"},
    {Action::H, "H"},
    {Action::I, "I"},
    {Action::J, "J"},
    {Action::K, "K"},
    {Action::L, "L"},
    {Action::M, "M"},
    {Action::N, "N"},
    {Action::O, "O"},
    {Action::P, "P"},
    {Action::Q, "Q"},
    {Action::R, "R"},
    {Action::S, "S"},
    {Action::T, "T"},
    {Action::U, "U"},
    {Action::V, "V"},
    {Action::W, "W"},
    {Action::X, "X"},
    {Action::Y, "Y"},
    {Action::Z, "Z"},
};

extern "C"
{
    std::unique_ptr<arc::IGameModule> makeInstance()
    {
        return std::make_unique<arc::GameMenu>();
    }
    arc::LibType getLibType()
    {
        return arc::LibType::Game;
    }
}
