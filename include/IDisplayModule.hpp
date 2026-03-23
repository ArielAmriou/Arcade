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
#include "IElement.hpp"

namespace arc {
    class IDisplayModule {
        public:
            ~IDisplayModule() = default;

            virtual Event getEvent() = 0;
            virtual int setAsset(std::vector<std::string>) = 0;
            virtual void drawGame(std::vector<IElement>) = 0;
    };
}

#endif
