/*
** EPITECH PROJECT, 2026
** Arcade
** File description:
** ISound
*/

#ifndef ISOUND_HPP
#define ISOUND_HPP

#include <vector>
#include <memory>

namespace arc {
    class ISound {
        public:
            virtual ~ISound() = default;

            virtual int getIdx() = 0;
            virtual bool isLoop() = 0;
    };

    using Sounds = std::vector<std::unique_ptr<arc::ISound>>;
}

#endif
