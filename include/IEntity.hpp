/*
** EPITECH PROJECT, 2026
** Arcade
** File description:
** IEntity
*/

#ifndef IENTITY_HPP
    #define IENTITY_HPP

#include <utility> 
#include <optional>
#include <string>
#include <memory>
#include <vector>
#include "Arcade.hpp"

namespace arc {

    using RGBA = std::tuple<unsigned char, unsigned char,
        unsigned char, unsigned char>;
        
    class IEntity {
        public:
            virtual ~IEntity() = default;
            
            virtual int getIdx() = 0;
            virtual Vector2f getPos() = 0;
            virtual Vector2f getSize() = 0;
            virtual float getRotation() = 0;
            virtual RGBA getColor() = 0;
            virtual std::optional<std::string> getStr() = 0;
    };
    
    using Entities = std::vector<std::unique_ptr<arc::IEntity>>;
}

#endif
