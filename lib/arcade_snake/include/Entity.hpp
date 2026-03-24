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

    class Entity : public IEntity {
        public:
            Entity(int idx, Vector2f pos, Vector2f size, float rotation)
                : _idx(idx), _pos(pos), _size(size), _rotation(rotation) {};
            ~Entity() {};

            int getIdx() {return _idx;}
            Vector2f getPos() {return _pos;}
            Vector2f getSize() {return _size;}
            float getRotation() {return _rotation;}
            RGBA getColor() {return _color;}
            std::optional<std::string> getStr() {return _str;}
            
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
