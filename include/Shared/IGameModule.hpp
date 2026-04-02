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
#include "IEntity.hpp"
#include "ISound.hpp"
#include "ILibrary.hpp"

namespace arc {

    class IGameModule: public ILibrary {
        public:
            virtual ~IGameModule() = default;

            virtual void simulate(const Event) noexcept = 0;
            virtual Assets getAssets() noexcept = 0;
            virtual std::pair<Entities, Sounds> getElements() noexcept = 0;
            virtual bool isOpen() noexcept = 0;
            virtual std::vector<Command> loadCommand() noexcept = 0;
    };
}

#endif
