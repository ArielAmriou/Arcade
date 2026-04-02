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

namespace arc {

    using SelectLibs = std::pair<std::optional<std::string>,
        std::optional<std::string>>;
    using Libs = std::pair<std::vector<std::string>, std::vector<std::string>>;

    class IGameModule {
        public:
            virtual ~IGameModule() = default;

            virtual void simulate(Event) = 0;
            virtual Assets getAssets() = 0;
            virtual std::pair<Entities, Sounds> getElements() = 0;
            virtual bool isOpen() = 0;
            virtual SelectLibs libChanges(Libs) = 0;
    };
}

#endif
