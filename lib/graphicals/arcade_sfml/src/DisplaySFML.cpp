/*
** EPITECH PROJECT, 2026
** Arcade
** File description:
** Display
*/

#include <iostream>
#include <unistd.h>
#include "DisplaySFML.hpp"

arc::DisplaySFML::DisplaySFML(): _renderWindow(sf::VideoMode({WINX, WINY}), "SFML graphical library")
{
    _font.loadFromFile(FONT_PATH.data());
}

arc::DisplaySFML::~DisplaySFML()
{
    freeAsset();
}

arc::Event arc::DisplaySFML::getEvent() noexcept
{
    sf::Vector2i mouspos = sf::Mouse::getPosition(_renderWindow);
    Vector2f pos = {(float)(mouspos.x) / WINX, (float)(mouspos.y) / WINY};
    Event value = {Action::None, pos};
    sf::Event event;

    while (_renderWindow.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            value = {Action::Close, pos};
        if (event.type == sf::Event::KeyPressed) {
            auto tmp = _keyMap.find(event.key.code);
            if (tmp != _keyMap.end())
                value = {tmp->second, pos};
        }
        if(event.type == sf::Event::MouseButtonPressed){
            auto tmp = _mouseButtonMap.find(event.mouseButton.button);
            if (tmp != _mouseButtonMap.end())
                value = {tmp->second, pos};
        }
    }
    return value;
}

int arc::DisplaySFML::setAssets(const Assets assets) noexcept
{
    freeAsset();
    for (auto path: assets.first) {
        path += ".png";
        sf::Texture texture;
        if (!texture.loadFromFile(path)) {
            std::cerr << "loadFromFile failed for '" << path << "." << std::endl;
            return -1;
        }
        _textures.push_back(texture);
    }
    for (auto path: assets.second) {
        sf::SoundBuffer music;
        try {
            music.loadFromFile(path);
        } catch (...) {
            std::cerr << "loadFromFile failed for '" << path << "." << std::endl;
            return -1;
        }
        _musics.push_back(music);
    }
    return 0;
}


void arc::DisplaySFML::drawRect(
    Vector2f pos, Vector2f size, float rotation, RGBA color)
{
    sf::RectangleShape rect;
    rect.setOrigin(sf::Vector2f{
        (float)size.first / 2,
        (float)size.second / 2}
    );
    rect.setRotation(rotation);
    rect.setPosition(sf::Vector2f{
        (pos.first * WINX) + ((float)size.first / 2),
        (pos.second * WINY) + ((float)size.second / 2)
    });
    rect.setScale(sf::Vector2f{
        (size.first * WINX) / (float)size.first,
        (size.second * WINY) / (float)size.second
    });
    rect.setFillColor(sf::Color(std::get<0>(color), std::get<1>(color), std::get<2>(color), std::get<3>(color)));
    _renderWindow.draw(rect);
}

void arc::DisplaySFML::drawText(
    Vector2f pos, Vector2f size, std::string str, RGBA color)
{
    sf::Text text;
    text.setFont(_font);
    text.setFillColor(sf::Color(std::get<0>(color), std::get<1>(color), std::get<2>(color), std::get<3>(color)));
    text.setPosition(sf::Vector2f{
        pos.first * WINX,
        pos.second * WINY
    });
    text.setString(str);
    text.setScale(sf::Vector2f{
        (size.first * WINX) / text.getLocalBounds().getSize().x,
        (size.second * WINY) / text.getLocalBounds().getSize().y});
    _renderWindow.draw(text);
}

void arc::DisplaySFML::drawImage(Vector2f pos, Vector2f size, int idx, float rotation, RGBA color)
{
    sf::Sprite sprite;
    auto texture_size = _textures[idx].getSize();
    sprite.setTexture(_textures[idx]);
    sprite.setOrigin(sf::Vector2f{
        (float)texture_size.x / 2,
        (float)texture_size.y / 2}
    );
    sprite.setRotation(rotation);
    sprite.setPosition(sf::Vector2f{
        (pos.first * WINX) + ((float)texture_size.x / 2),
        (pos.second * WINY) + ((float)texture_size.y / 2)
    });
    sprite.setScale(sf::Vector2f{
        (size.first * WINX) / _textures[idx].getSize().x,
        (size.second * WINY) / _textures[idx].getSize().y
    });
    sprite.setColor(sf::Color(std::get<0>(color), std::get<1>(color), std::get<2>(color), std::get<3>(color)));
    _renderWindow.draw(sprite);
}

void arc::DisplaySFML::drawGame(const std::pair<Entities, Sounds> elements) noexcept
{
    _renderWindow.clear();
    for (auto &entity: elements.first) {
        Vector2f pos = entity->getPos();
        Vector2f size = entity->getSize();
        int idx = entity->getIdx();
        if (idx >= 0 && idx < _textures.size()) {
            drawImage(pos, size, idx, entity->getRotation(), entity->getColor());
        } else if (entity->getStr().has_value()) {
            drawText(pos, size, entity->getStr().value(), entity->getColor());
        } else {
            drawRect(pos, size, entity->getRotation(), entity->getColor());
        }
    }
    for (auto& elem : elements.second) {
        int idx = elem->getIdx();
        if (idx >= 0 && idx < _musics.size()) {
            sf::Sound sound(_musics[idx]);
            auto isLoop = elem->isLoop();
            sound.setLoop(isLoop);
            sound.play();
        }
    }
    usleep(1000000 / 60);
    _renderWindow.display();
}

void arc::DisplaySFML::freeAsset()
{
    _textures.clear();
    _musics.clear();
}

const std::unordered_map<sf::Keyboard::Key, arc::Action> arc::DisplaySFML::_keyMap = {
    {sf::Keyboard::Key::Unknown, Action::None},
    {sf::Keyboard::Key::A, Action::A},
    {sf::Keyboard::Key::B, Action::B},
    {sf::Keyboard::Key::C, Action::C},
    {sf::Keyboard::Key::D, Action::D},
    {sf::Keyboard::Key::E, Action::E},
    {sf::Keyboard::Key::F, Action::F},
    {sf::Keyboard::Key::G, Action::G},
    {sf::Keyboard::Key::H, Action::H},
    {sf::Keyboard::Key::I, Action::I},
    {sf::Keyboard::Key::J, Action::J},
    {sf::Keyboard::Key::K, Action::K},
    {sf::Keyboard::Key::L, Action::L},
    {sf::Keyboard::Key::M, Action::M},
    {sf::Keyboard::Key::N, Action::N},
    {sf::Keyboard::Key::O, Action::O},
    {sf::Keyboard::Key::P, Action::P},
    {sf::Keyboard::Key::Q, Action::Q},
    {sf::Keyboard::Key::R, Action::R},
    {sf::Keyboard::Key::S, Action::S},
    {sf::Keyboard::Key::T, Action::T},
    {sf::Keyboard::Key::U, Action::U},
    {sf::Keyboard::Key::V, Action::V},
    {sf::Keyboard::Key::W, Action::W},
    {sf::Keyboard::Key::X, Action::X},
    {sf::Keyboard::Key::Y, Action::Y},
    {sf::Keyboard::Key::Z, Action::Z},
    {sf::Keyboard::Key::Num1, Action::Num1},
    {sf::Keyboard::Key::Num2, Action::Num2},
    {sf::Keyboard::Key::Num3, Action::Num3},
    {sf::Keyboard::Key::Num4, Action::Num4},
    {sf::Keyboard::Key::Num5, Action::Num5},
    {sf::Keyboard::Key::Num6, Action::Num6},
    {sf::Keyboard::Key::Num7, Action::Num7},
    {sf::Keyboard::Key::Num8, Action::Num8},
    {sf::Keyboard::Key::Num9, Action::Num9},
    {sf::Keyboard::Key::Num0, Action::Num0},
    {sf::Keyboard::Key::Return, Action::Enter},
    {sf::Keyboard::Key::Escape, Action::Escape},
    {sf::Keyboard::Key::BackSpace, Action::Backspace},
    {sf::Keyboard::Key::Tab, Action::Tab},
    {sf::Keyboard::Key::Space, Action::Space},
    {sf::Keyboard::Key::Subtract, Action::Subtract},
    {sf::Keyboard::Key::Equal, Action::Equal},
    {sf::Keyboard::Key::LBracket, Action::LBracket},
    {sf::Keyboard::Key::RBracket, Action::RBracket},
    {sf::Keyboard::Key::BackSlash, Action::Backslash},
    {sf::Keyboard::Key::SemiColon, Action::Semicolon},
    {sf::Keyboard::Key::Quote, Action::Apostrophe},
    {sf::Keyboard::Key::Comma, Action::Comma},
    {sf::Keyboard::Key::Period, Action::Period},
    {sf::Keyboard::Key::Slash, Action::Slash},
    {sf::Keyboard::Key::F1, Action::F1},
    {sf::Keyboard::Key::F2, Action::F2},
    {sf::Keyboard::Key::F3, Action::F3},
    {sf::Keyboard::Key::F4, Action::F4},
    {sf::Keyboard::Key::F5, Action::F5},
    {sf::Keyboard::Key::F6, Action::F6},
    {sf::Keyboard::Key::F7, Action::F7},
    {sf::Keyboard::Key::F8, Action::F8},
    {sf::Keyboard::Key::F9, Action::F9},
    {sf::Keyboard::Key::F10, Action::F10},
    {sf::Keyboard::Key::F11, Action::F11},
    {sf::Keyboard::Key::F12, Action::F12},
    {sf::Keyboard::Key::Pause, Action::Pause},
    {sf::Keyboard::Key::Insert, Action::Insert},
    {sf::Keyboard::Key::Home, Action::Home},
    {sf::Keyboard::Key::PageUp, Action::PageUp},
    {sf::Keyboard::Key::Delete, Action::Delete},
    {sf::Keyboard::Key::End, Action::End},
    {sf::Keyboard::Key::PageDown, Action::PageDown},
    {sf::Keyboard::Key::Right, Action::Right},
    {sf::Keyboard::Key::Left, Action::Left},
    {sf::Keyboard::Key::Down, Action::Down},
    {sf::Keyboard::Key::Up, Action::Up},
    {sf::Keyboard::Key::Divide, Action::Divide},
    {sf::Keyboard::Key::Multiply, Action::Multiply},
    {sf::Keyboard::Key::Subtract, Action::Subtract},
    {sf::Keyboard::Key::Add, Action::Add},
    {sf::Keyboard::Key::Enter, Action::Enter},
    {sf::Keyboard::Key::Numpad1, Action::Numpad1},
    {sf::Keyboard::Key::Numpad2, Action::Numpad2},
    {sf::Keyboard::Key::Numpad3, Action::Numpad3},
    {sf::Keyboard::Key::Numpad4, Action::Numpad4},
    {sf::Keyboard::Key::Numpad5, Action::Numpad5},
    {sf::Keyboard::Key::Numpad6, Action::Numpad6},
    {sf::Keyboard::Key::Numpad7, Action::Numpad7},
    {sf::Keyboard::Key::Numpad8, Action::Numpad8},
    {sf::Keyboard::Key::Numpad9, Action::Numpad9},
    {sf::Keyboard::Key::Numpad0, Action::Numpad0},
    {sf::Keyboard::Key::Period, Action::Period},
    {sf::Keyboard::Key::F13, Action::F13},
    {sf::Keyboard::Key::F14, Action::F14},
    {sf::Keyboard::Key::F15, Action::F15},
    {sf::Keyboard::Key::LShift, Action::LShift},
    {sf::Keyboard::Key::RShift, Action::RShift},
};

const std::unordered_map<int, arc::Action> arc::DisplaySFML::_mouseButtonMap = {
    {sf::Mouse::Left, Action::LeftMouse},
    {sf::Mouse::Middle, Action::MiddleMouse},
    {sf::Mouse::Right, Action::RightMouse},
};

extern "C"
{
    std::unique_ptr<arc::IDisplayModule> makeInstance()
    {
        return std::make_unique<arc::DisplaySFML>();
    }
    arc::LibType getLibType()
    {
        return arc::LibType::Display;
    }
}
