/*
** EPITECH PROJECT, 2026
** Arcade
** File description:
** Entity
*/

#ifndef ENTITY_HPP
    #define ENTITY_HPP

#include <utility> 
#include <optional>
#include <string>
#include "Arcade.hpp"
#include "IEntity.hpp"

namespace arc {

    constexpr RGBA WHITE = std::make_tuple(255, 255, 255, 255);
    constexpr RGBA RED = std::make_tuple(255, 0, 0, 255);
    constexpr RGBA BLUE = std::make_tuple(0, 0, 255, 255);
        constexpr RGBA GREEN = std::make_tuple(0, 255, 0, 255);

    class Entity : public IEntity {
        public:
            Entity(int idx, Vector2f pos, Vector2f size, float rotation)
                : _idx(idx), _pos(pos), _size(size), _rotation(rotation) {};
            Entity(int idx, Vector2f pos, Vector2f size, std::string str, RGBA color)
                : _idx(idx), _pos(pos), _size(size), _color(color), _str(str) {};
            Entity(int idx, Vector2f pos, Vector2f size, std::string str)
                : _idx(idx), _pos(pos), _size(size), _str(str) {};
            Entity(int idx, Vector2f pos, Vector2f size)
                : _idx(idx), _pos(pos), _size(size) {};
            ~Entity() {};

            int getIdx() noexcept {return _idx;}
            Vector2f getPos() noexcept {return _pos;}
            Vector2f getSize() noexcept {return _size;}
            float getRotation() noexcept {return _rotation;}
            RGBA getColor() noexcept {return _color;}
            std::optional<std::string> getStr() noexcept {return _str;}
            
        private:
            int _idx;
            Vector2f _pos;
            Vector2f _size;
            float _rotation = 0;
            RGBA _color = WHITE;
            std::optional<std::string> _str = std::nullopt;
    };
}

#endif
