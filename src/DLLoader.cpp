/*
** EPITECH PROJECT, 2026
** Arcade
** File description:
** DLLoarder
*/

#include "DLLoader.hpp"
#include "Exceptions.hpp"

arc::DLLoader::DLLoader(const std::string &path) {
    _handle = dlopen(path.data(), RTLD_LAZY);
}

arc::DLLoader::~DLLoader() {
    if (_handle != nullptr)
        dlclose(_handle);
}

void arc::DLLoader::reset(const std::string &path) {
    _handle = dlopen(path.data(), RTLD_LAZY);
}

arc::LibType arc::DLLoader::getLibType()
{
    void *symbol = dlsym(_handle, "getLibType");
    if (symbol == nullptr)
        throw arc::exceptions::NoEntryPoint();
    auto getLibType = reinterpret_cast<arc::LibType (*)(void)>(symbol);
    if (getLibType() == arc::LibType::None)
        throw arc::exceptions::NoEntryPoint();
    return getLibType();
}
