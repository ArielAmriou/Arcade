/*
** EPITECH PROJECT, 2026
** Arcade
** File description:
** IGameModule
*/

#ifndef IGAMEMODULE_HPP
    #define IGAMEMODULE_HPP

#include <vector>
#include <memory>
#include "IElement.hpp"

namespace arc {

    class IGameModule {
        public:
            virtual ~IGameModule() = default;

            virtual void simulate(Event) = 0;
            virtual std::vector<std::string> getAsset() = 0;
            virtual Elements getElements() = 0;
    };
}

#endif
