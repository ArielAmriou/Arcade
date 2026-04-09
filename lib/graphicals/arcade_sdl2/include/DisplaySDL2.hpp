/*
** EPITECH PROJECT, 2026
** Arcade
** File description:
** Display
*/

#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#include <ncurses.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <unordered_map>
#include <utility> 
#include <string_view>
#include "IDisplayModule.hpp"

namespace arc {

    constexpr int WINX = 960;
    constexpr int WINY = 540;
    constexpr SDL_Color WHITE = {0, 0, 0, 255};
    constexpr int FREQUENCY = 44100;
    constexpr int CHANELS = 2;
    constexpr int CHUNKSIZE = 2048;
    constexpr std::string_view FONT = "assets/SDL2/font.ttf";
    constexpr int FONTSIZE = 25;
    constexpr float FPS = 1000 / 60;

    using SDL_Entity =
        std::reference_wrapper<const std::unique_ptr<arc::IEntity>>;

    class DisplaySDL2 : public IDisplayModule {
        public:
            DisplaySDL2();
            ~DisplaySDL2();

            Event getEvent() noexcept;
            int setAssets(const Assets assets) noexcept;
            void drawGame(const std::pair<Entities, Sounds>) noexcept;

            void freeAsset();

            void drawText(SDL_Rect rect, SDL_Color color,
                std::string str, float rotation);
            void drawImage(
                SDL_Rect rect, SDL_Color color, int idx, float rotation);

            void drawEntity(SDL_Entity entity, SDL_Rect rect, SDL_Color color);

        private:
            bool _quit = false;
            SDL_Window *_window;
            SDL_Renderer *_renderer;
            TTF_Font *_font;
            static const std::unordered_map<SDL_Keycode, Action> _keyMap;
            static const std::unordered_map<int, Action> _mouseButtonMap;
            std::vector<std::pair<SDL_Surface *, SDL_Texture *>> _images;
            std::vector<Mix_Chunk *> _musics;
        };
}

#endif
