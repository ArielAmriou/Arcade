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
#include "ILibrary.hpp"
// #include "IDisplayModule.hpp"
// #include "IGameModule.hpp"

namespace arc {

    template<typename T>
    concept BaseILibrary = std::is_base_of<ILibrary, T>::value;

    class DLLoader {
        public:
            DLLoader(const std::string &path);
            ~DLLoader();

            void reset(const std::string &path);

            template<BaseILibrary T>
            std::optional<std::unique_ptr<T>> makeInstance();

            template<BaseILibrary T>
            bool isType();

        private:
            void *_handle = nullptr;
        
            ILibrary *getInstance();
    };

}

#endif /* !DLLOADER_HPP_ */
