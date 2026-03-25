/*
** EPITECH PROJECT, 2026
** Arcade
** File description:
** Display
*/

#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <unordered_map>
#include <utility> 
#include "IDisplayModule.hpp"

namespace arc {

    constexpr int WINX = 960;
    constexpr int WINY = 540;

    class Display : public IDisplayModule {
        public:
            Display();
            ~Display();

            Event getEvent();
            int setAssets(Assets assets);
            void drawGame(std::reference_wrapper<std::pair<Entities, Sounds>>);

            void freeAsset();

        private:
            bool _quit = false;
            SDL_Window *_window;
            SDL_Renderer *_renderer;
            static const std::unordered_map<SDL_Keycode, Action> _keyMap;
            static const std::unordered_map<int, Action> _mouseButtonMap;
            std::vector<std::pair<SDL_Surface *, SDL_Texture *>> _images;
            std::vector<Mix_Chunk *> _musics;
        };
}

#endif
