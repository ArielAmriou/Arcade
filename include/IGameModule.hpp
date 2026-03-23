/*
** EPITECH PROJECT, 2026
** Arcade
** File description:
** IGameModule
*/

#ifndef IGAMEMODULE_HPP
    #define IGAMEMODULE_HPP

#include <vector>
#include "IElement.hpp"

namespace arc {
    class IGameModule {
        public:
            ~IGameModule() = default;

            virtual void simulate(Event) = 0;
            virtual std::vector<std::string> getAsset() = 0;
            virtual std::vector<IElement> getElements() = 0;
    };
}

#endif
