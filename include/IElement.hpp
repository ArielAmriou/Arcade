/*
** EPITECH PROJECT, 2026
** Arcade
** File description:
** IElement
*/

#ifndef IELEMENT_HPP
    #define IELEMENT_HPP

#include <tuple>
#include <optional>
#include <string>
#include "Arcade.hpp"

namespace arc {

    using RGBA = std::tuple<unsigned char, unsigned char,
        unsigned char, unsigned char>;

    class IElement {
        public:
            ~IElement() = default;

            virtual int getIdx() = 0;
            virtual Vector2f getPos() = 0;
            virtual RGBA getColor() = 0;
            virtual std::optional<std::string> getStr() = 0;
            virtual float getRotation() = 0;
    };
}

#endif
