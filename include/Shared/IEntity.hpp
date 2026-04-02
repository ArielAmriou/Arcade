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
            
            [[nodiscard]] virtual int getIdx() noexcept = 0;
            [[nodiscard]] virtual Vector2f getPos() noexcept = 0;
            [[nodiscard]] virtual Vector2f getSize() noexcept = 0;
            [[nodiscard]] virtual float getRotation() noexcept = 0;
            [[nodiscard]] virtual RGBA getColor() noexcept = 0;
            [[nodiscard]] virtual
                std::optional<std::string> getStr() noexcept = 0;
    };
    
    using Entities = std::vector<std::unique_ptr<arc::IEntity>>;
}

#endif
