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
#include "ILibrary.hpp"

namespace arc {
    class IDisplayModule: public ILibrary {
        public:
            virtual ~IDisplayModule() = default;

            virtual Event getEvent() = 0;
            virtual int setAssets(Assets) = 0;
            virtual void drawGame(std::reference_wrapper<
                std::pair<Entities, Sounds>>) = 0;
    };
}

#endif
