/*
** EPITECH PROJECT, 2026
** Arcade
** File description:
** utils
*/

#include "Utils.hpp"
#include "DLLoader.hpp"
#include <filesystem>

std::vector<std::string> arc::Utils::getLibsPath() noexcept
{
    std::vector<std::string> list;

    for (auto &entry : std::filesystem::directory_iterator(LIBDIR)) {
        std::string path = entry.path().string();
        if (path.starts_with(LIBPATH) && path.ends_with(LIBEXT)) {
            list.push_back(path);
        }
    }
    return list;
}

arc::SplitLibs arc::Utils::splitLibs(std::vector<std::string> libs) noexcept
{
    SplitLibs split;

    for (auto lib: libs) {
        DLLoader loader(lib);
        if (loader.getLibType() == arc::LibType::Display)
            split.first.push_back(lib);
        else
            split.second.push_back(lib);
    }
    return split;
}

arc::SplitLibs arc::Utils::getSplitLibs() noexcept
{
    return splitLibs(getLibsPath());
}

int arc::Utils::findLib(std::vector<std::string> list, std::string lib) noexcept
{
    int i = 0;
    for (auto iter: list) {
        if (iter == lib)
            return i;
        ++i;
    }
    return -1;
}
