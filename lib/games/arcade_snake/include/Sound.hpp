/*
** EPITECH PROJECT, 2026
** Arcade
** File description:
** Sound
*/

#ifndef SOUND_HPP
#define SOUND_HPP

#include "ISound.hpp"

namespace arc {
    class Sound : public ISound {
        public:
            Sound(int idx, bool loop)
                : _idx(idx), _loop(loop) {};
            ~Sound() {};

            int getIdx() {return _idx;}
            bool isLoop() {return _loop;}

        private:
            int _idx;
            bool _loop;
    };
}

#endif
