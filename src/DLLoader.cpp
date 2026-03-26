/*
** EPITECH PROJECT, 2026
** Arcade
** File description:
** DLLoarder
*/

#include "DLLoader.hpp"

arc::DLLoader::DLLoader(const std::string &path) {
    _handle = dlopen(path.data(), RTLD_LAZY);
}

arc::DLLoader::~DLLoader() {
    dlclose(_handle);
}

arc::ILibrary *arc::DLLoader::getInstance() {
    void *ret = dlsym(_handle, "makeInstance");
    auto f = reinterpret_cast<ILibrary *(*)(void)>(ret);
    if (f == nullptr)
        return nullptr;
    return f();
}

void arc::DLLoader::reset(const std::string &path) {
    _handle = dlopen(path.data(), RTLD_LAZY);
}
