/*
** EPITECH PROJECT, 2026
** Arcade
** File description:
** DLLoarder
*/

#include "DLLoader.hpp"
#include "Exceptions.hpp"

arc::DLLoader::DLLoader(const std::string &path) noexcept {
    _handle = dlopen(path.data(), RTLD_LAZY);
}

arc::DLLoader::~DLLoader() {
    if (_handle != nullptr)
        dlclose(_handle);
}

void arc::DLLoader::reset(const std::string &path) noexcept {
    _handle = dlopen(path.data(), RTLD_LAZY);
}
