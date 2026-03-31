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

arc::ILibrary *arc::DLLoader::getInstance() {
    void *ret = dlsym(_handle, "makeInstance");
    if (ret == nullptr)
        throw arc::exceptions::NoEntryPoint();
    auto f = reinterpret_cast<ILibrary *(*)(void)>(ret);
    if (f == nullptr)
        throw arc::exceptions::NoEntryPoint();
    return f();
}

void arc::DLLoader::reset(const std::string &path) {
    _handle = dlopen(path.data(), RTLD_LAZY);
}
