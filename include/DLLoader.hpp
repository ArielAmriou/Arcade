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
#include <iostream>
#include "Arcade.hpp"
#include "Exceptions.hpp"

namespace arc {
    class DLLoader {
        public:
            DLLoader(const std::string &path) noexcept;
            ~DLLoader();

            DLLoader(DLLoader&& obj);

            template<typename T>
            [[nodiscard]] std::optional<std::unique_ptr<T>> makeInstance(arc::LibType expected) {
                try {
                    if (getLibType() != expected)
                        return {};
                } catch (...) {
                    return {};
                }

                void *symbol = dlsym(_handle, "makeInstance");
                if (symbol == nullptr)
                    throw arc::exceptions::LibraryLoadError(dlerror());
                auto makeInstance = reinterpret_cast<std::unique_ptr<T> (*)(void)>(symbol);
                if (makeInstance == nullptr)
                    throw arc::exceptions::LibraryLoadError();
                auto tmp = makeInstance();
                if (tmp == nullptr)
                    throw arc::exceptions::LibraryLoadError(dlerror());
                return tmp;
            }

            [[nodiscard]] arc::LibType getLibType();
            std::string getLibPath();
        private:
            void *_handle = nullptr;
            std::string _path;
    };

}

#endif /* !DLLOADER_HPP_ */
