/*
** EPITECH PROJECT, 2026
** Arcade
** File description:
** IDisplayModule
*/

#ifndef IDISPLAYMODULE_HPP
    #define IDISPLAYMODULE_HPP

#include <vector>
#include <string>
#include <optional>
#include <memory>
#include "Arcade.hpp"
#include "IEntity.hpp"
#include "ISound.hpp"

namespace arc {
    class IDisplayModule {
        public:
            virtual ~IDisplayModule() = default;

            virtual Event getEvent() noexcept = 0;
            virtual int setAssets(const Assets) noexcept = 0;
            virtual void drawGame(const std::pair<Entities, Sounds>) noexcept = 0;
    };
}

#endif
