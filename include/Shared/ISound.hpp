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

            [[nodiscard]] virtual int getIdx() noexcept = 0;
            [[nodiscard]] virtual bool isLoop() noexcept = 0;
    };

    using Sounds = std::vector<std::unique_ptr<arc::ISound>>;
}

#endif
