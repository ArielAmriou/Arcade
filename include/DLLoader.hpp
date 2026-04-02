/*
** EPITECH PROJECT, 2026
** Arcade
** File description:
** DLLoader
*/

#ifndef DLLOADER_HPP_
#define DLLOADER_HPP_

#include <optional>
#include <concepts>
#include <type_traits>
#include <dlfcn.h>
#include <string>
#include <optional>
#include <memory>
#include "Arcade.hpp"
#include "Exceptions.hpp"
#include <iostream>

namespace arc {
    class DLLoader;

    class DLLoader {
        public:
            DLLoader(const std::string &path);
            ~DLLoader();

            void reset(const std::string &path);

            template<typename T>
            [[nodiscard]] std::optional<std::unique_ptr<T>> makeInstance(arc::LibType expected) {
                void *symbol = dlsym(_handle, "getLibType");
                auto getLibType = reinterpret_cast<arc::LibType (*)(void)>(symbol);
                if (getLibType == nullptr || getLibType() != expected)
                    return {};

                symbol = dlsym(_handle, "makeInstance");
                if (symbol == nullptr)
                    throw arc::exceptions::NoEntryPoint();
                auto makeInstance = reinterpret_cast<std::unique_ptr<T> (*)(void)>(symbol);
                if (makeInstance == nullptr)
                    throw arc::exceptions::LibraryLoadError();
                auto tmp = makeInstance();
                if (tmp == nullptr)
                    throw arc::exceptions::NoEntryPoint();
                return tmp;
            }
        private:
            void *_handle = nullptr;
    };

}

#endif /* !DLLOADER_HPP_ */
