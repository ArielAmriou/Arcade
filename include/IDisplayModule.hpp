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
#include "IElement.hpp"

namespace arc {
    class IDisplayModule {
        public:
            virtual ~IDisplayModule() = default;

            virtual Event getEvent() = 0;
            virtual int setAsset(std::vector<std::string>) = 0;
            virtual void drawGame(Elements) = 0;
    };
}

#endif
