/*
** EPITECH PROJECT, 2026
** Arcade
** File description:
** utils
*/

#ifndef UTILS_HPP_
#define UTILS_HPP_

#include "string"
#include "vector"

namespace arc {
    constexpr std::string_view LIBDIR = "lib";
    constexpr std::string_view LIBPATH = "lib/arcade_";
    constexpr std::string_view LIBEXT = ".so";

    using SplitLibs = std::pair<std::vector<std::string>,
        std::vector<std::string>>;

    class utils {
        public:
            static SplitLibs getSplitLibs();
        private:
            static std::vector<std::string> getLibsPath();
            static SplitLibs splitLibs(std::vector<std::string> libs);
    };
}

#endif /* !UTILS_HPP_ */
