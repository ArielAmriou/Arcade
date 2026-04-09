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
    LibType type = arc::LibType::None;

    for (auto lib: libs) {
        try {
            DLLoader loader(lib);
            type = loader.getLibType();
        } catch (...) {}
        if (type == arc::LibType::Display)
            split.first.push_back(lib);
        else if (type == arc::LibType::Game)
            split.second.push_back(lib);
    }
    return split;
}

arc::SplitLibs arc::Utils::getSplitLibs() noexcept
{
    return splitLibs(getLibsPath());
}

std::size_t arc::Utils::findLib(std::vector<std::string> list, std::string lib)
{
    std::size_t i = 0;
    for (auto iter: list) {
        if (iter == lib)
            return i;
        ++i;
    }
    throw arc::exceptions::NoSuchLib(lib);
}
