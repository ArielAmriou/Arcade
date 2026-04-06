/*
** EPITECH PROJECT, 2026
** Arcade
** File description:
** Display
*/

#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#include <ncurses.h>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <unordered_map>
#include <utility> 
#include "IDisplayModule.hpp"

namespace arc {

    constexpr int WINX = 960;
    constexpr int WINY = 540;
    static const sf::Color WHITE(0, 0, 0, 255);

    constexpr std::string_view FONT_PATH = "assets/SFML/font.ttf";

    using SFML_Entity =
        std::reference_wrapper<const std::unique_ptr<arc::IEntity>>;

    class DisplaySFML : public IDisplayModule {
        public:
            DisplaySFML();
            ~DisplaySFML();

            Event getEvent() noexcept;
            int setAssets(const Assets assets) noexcept;
            void drawGame(const std::pair<Entities, Sounds>) noexcept;

        private:
            bool _quit = false;
            sf::RenderWindow _renderWindow;
            sf::Font _font;
            static const std::unordered_map<sf::Keyboard::Key, Action> _keyMap;
            static const std::unordered_map<int, Action> _mouseButtonMap;
            std::vector<sf::Texture> _textures;
            std::vector<sf::SoundBuffer> _musics;
            
            void freeAsset();
            void drawText(Vector2f pos, Vector2f size, std::string str, RGBA color);
            void drawImage(Vector2f pos, Vector2f size, int idx, float rotation, RGBA color);
            void drawRect(Vector2f pos, Vector2f size, float rotation, RGBA color);
        };
}

#endif
