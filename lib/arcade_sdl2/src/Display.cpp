/*
** EPITECH PROJECT, 2026
** Arcade
** File description:
** Display
*/

#include <iostream>
#define DEBUG(value) std::cout << "\e[0;35m" << "DEBUG: " <<  "\e[0;37m" << "\t" << value << std::endl;

#include "Display.hpp"

arc::Display::Display()
{
    SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
    Mix_Init(MIX_INIT_MP3 | MIX_INIT_WAVPACK);
    _window = SDL_CreateWindow("SDL2 Displaying Image", SDL_WINDOWPOS_UNDEFINED,
    SDL_WINDOWPOS_UNDEFINED, WINX, WINY, 0);
    _renderer = SDL_CreateRenderer(_window, -1, 0);
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
}

arc::Display::~Display()
{
    freeAsset();
    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);
    Mix_Quit();
    IMG_Quit();
    SDL_Quit();
}

arc::Event arc::Display::getEvent()
{
    int x = 0;
    int y = 0;
    SDL_GetGlobalMouseState(&x, &y);
    Vector2f pos = {x, y};
    Event value = {Action::None, pos};
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT)
            value = {Action::Close, pos};
        if (event.type == SDL_KEYDOWN) {
            auto tmp = _keyMap.find(event.key.keysym.sym);
            if (tmp != _keyMap.end())
                value = {tmp->second, pos};
        }
        if(event.type == SDL_MOUSEBUTTONDOWN){
            auto tmp = _mouseButtonMap.find(event.button.button);
            if (tmp != _mouseButtonMap.end())
                value = {tmp->second, pos};
        }
    }
    return value;
}

int arc::Display::setAssets(Assets assets)
{
    freeAsset();
    for (auto path: assets.first) {
        path = "assets/" + path + ".png";
        SDL_Surface *image = IMG_Load(path.c_str());
        if (!image) {
            std::cerr << "IMG_Load failed for '" << path << "': " << IMG_GetError() << std::endl;
            return -1;
        }
        SDL_Texture *texture = SDL_CreateTextureFromSurface(_renderer, image);
        if (!texture) {
            std::cerr << "CreateTexture failed: " << SDL_GetError() << std::endl;
            return -1;
        }
        _images.push_back({image, texture});
    }
    for (auto path: assets.second) {
        Mix_Chunk *music = Mix_LoadWAV(std::string("assets/" + path).c_str());
        if (!music)  {
            std::cerr << "Mix_LoadMUS failed for '" << path << "': " << Mix_GetError() << std::endl;
            return -1;
        }
        _musics.push_back(music);
    }
    return 0;
}

void arc::Display::drawGame(std::reference_wrapper<
                std::pair<Entities, Sounds>> elements)
{
    SDL_SetRenderDrawColor(_renderer, 255, 0, 0, 255);
    SDL_RenderClear(_renderer);
    for (auto &entity: elements.get().first) {
        Vector2f pos = entity->getPos();
        Vector2f size = entity->getSize();
        SDL_Rect rect = {static_cast<int>(pos.first * WINX), static_cast<int>(pos.second * WINY), static_cast<int>(size.first * WINX), static_cast<int>(size.second * WINY)};
        SDL_RenderCopyEx(_renderer, _images[entity->getIdx()].second, NULL, &rect, entity->getRotation(), NULL, SDL_FLIP_NONE);
    }
    for (auto& sound : elements.get().second) {
        int idx = sound->getIdx();
        int loop = sound->isLoop() ? -1 : 0;
        Mix_PlayChannel(-1, _musics[idx], loop);
    }
    SDL_RenderPresent(_renderer);
    SDL_Delay(1000 / 5);
}

void arc::Display::freeAsset()
{
    for (auto image: _images) {
        SDL_DestroyTexture(image.second);
        SDL_FreeSurface(image.first);
    }
    _images.clear();
    for (auto music: _musics) {
        Mix_FreeChunk(music);
    }
    _musics.clear();
}

const std::unordered_map<SDL_Keycode, arc::Action> arc::Display::_keyMap = {
    {SDLK_UNKNOWN, Action::None},
    {SDLK_a, Action::A},
    {SDLK_b, Action::B},
    {SDLK_c, Action::C},
    {SDLK_d, Action::D},
    {SDLK_e, Action::E},
    {SDLK_f, Action::F},
    {SDLK_g, Action::G},
    {SDLK_h, Action::H},
    {SDLK_i, Action::I},
    {SDLK_j, Action::J},
    {SDLK_k, Action::K},
    {SDLK_l, Action::L},
    {SDLK_m, Action::M},
    {SDLK_n, Action::N},
    {SDLK_o, Action::O},
    {SDLK_p, Action::P},
    {SDLK_q, Action::Q},
    {SDLK_r, Action::R},
    {SDLK_s, Action::S},
    {SDLK_t, Action::T},
    {SDLK_u, Action::U},
    {SDLK_v, Action::V},
    {SDLK_w, Action::W},
    {SDLK_x, Action::X},
    {SDLK_y, Action::Y},
    {SDLK_z, Action::Z},
    {SDLK_1, Action::Num1},
    {SDLK_2, Action::Num2},
    {SDLK_3, Action::Num3},
    {SDLK_4, Action::Num4},
    {SDLK_5, Action::Num5},
    {SDLK_6, Action::Num6},
    {SDLK_7, Action::Num7},
    {SDLK_8, Action::Num8},
    {SDLK_9, Action::Num9},
    {SDLK_0, Action::Num0},
    {SDLK_RETURN, Action::Enter},
    {SDLK_ESCAPE, Action::Escape},
    {SDLK_BACKSPACE, Action::BackSpace},
    {SDLK_TAB, Action::Tab},
    {SDLK_SPACE, Action::Space},
    {SDLK_MINUS, Action::Subtract},
    {SDLK_EQUALS, Action::Equal},
    {SDLK_LEFTBRACKET, Action::LBracket},
    {SDLK_RIGHTBRACKET, Action::RBracket},
    {SDLK_BACKSLASH, Action::BackSlash},
    {SDLK_SEMICOLON, Action::SemiColon},
    {SDLK_QUOTE, Action::Quote},
    {SDLK_COMMA, Action::Comma},
    {SDLK_PERIOD, Action::Period},
    {SDLK_SLASH, Action::Slash},
    {SDLK_CAPSLOCK, Action::None},
    {SDLK_F1, Action::F1},
    {SDLK_F2, Action::F2},
    {SDLK_F3, Action::F3},
    {SDLK_F4, Action::F4},
    {SDLK_F5, Action::F5},
    {SDLK_F6, Action::F6},
    {SDLK_F7, Action::F7},
    {SDLK_F8, Action::F8},
    {SDLK_F9, Action::F9},
    {SDLK_F10, Action::F10},
    {SDLK_F11, Action::F11},
    {SDLK_F12, Action::F12},
    {SDLK_PRINTSCREEN, Action::None},
    {SDLK_SCROLLLOCK, Action::None},
    {SDLK_PAUSE, Action::Pause},
    {SDLK_INSERT, Action::Insert},
    {SDLK_HOME, Action::Home},
    {SDLK_PAGEUP, Action::PageUp},
    {SDLK_DELETE, Action::Delete},
    {SDLK_END, Action::End},
    {SDLK_PAGEDOWN, Action::PageDown},
    {SDLK_RIGHT, Action::Right},
    {SDLK_LEFT, Action::Left},
    {SDLK_DOWN, Action::Down},
    {SDLK_UP, Action::Up},
    {SDLK_NUMLOCKCLEAR, Action::None},
    {SDLK_KP_DIVIDE, Action::Divide},
    {SDLK_KP_MULTIPLY, Action::Multiply},
    {SDLK_KP_MINUS, Action::Subtract},
    {SDLK_KP_PLUS, Action::Add},
    {SDLK_KP_ENTER, Action::Enter},
    {SDLK_KP_1, Action::Numpad1},
    {SDLK_KP_2, Action::Numpad2},
    {SDLK_KP_3, Action::Numpad3},
    {SDLK_KP_4, Action::Numpad4},
    {SDLK_KP_5, Action::Numpad5},
    {SDLK_KP_6, Action::Numpad6},
    {SDLK_KP_7, Action::Numpad7},
    {SDLK_KP_8, Action::Numpad8},
    {SDLK_KP_9, Action::Numpad9},
    {SDLK_KP_0, Action::Numpad0},
    {SDLK_KP_PERIOD, Action::Period},
    {SDLK_APPLICATION, Action::None},
    {SDLK_POWER, Action::None},
    {SDLK_KP_EQUALS, Action::Equal},
    {SDLK_F13, Action::F13},
    {SDLK_F14, Action::F14},
    {SDLK_F15, Action::F15},
    {SDLK_LSHIFT, Action::LShift},
    {SDLK_RSHIFT, Action::RShift},
};

const std::unordered_map<int, arc::Action> arc::Display::_mouseButtonMap = {
    {SDL_BUTTON_LEFT, Action::LeftMouse},
    {SDL_BUTTON_MIDDLE, Action::MiddleMouse},
    {SDL_BUTTON_RIGHT, Action::RightMouse},
};

extern "C"
{

    arc::ILibrary *makeInstance()
    {
        return new arc::Display();
    }

}
