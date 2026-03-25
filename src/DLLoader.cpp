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

void arc::DLLoader::reset(const std::string &path) {
    dlclose(_handle);
    _handle = dlopen(path.data(), RTLD_LAZY);
}

arc::ILibrary *arc::DLLoader::getInstance() {
    void *ret = dlsym(_handle, "makeInstance");
    auto f
        = reinterpret_cast<ILibrary *(*)(void)>(ret);
    if (f == nullptr)
        return nullptr;
    return f();
}

template<arc::BaseILibrary T>
std::optional<std::unique_ptr<T>> arc::DLLoader::makeInstance() {
    auto tmp = dynamic_cast<T *>(getInstance());
    if (tmp == nullptr)
        return {};
    std::unique_ptr<T> obj(tmp);
    return obj;
}

template<arc::BaseILibrary T>
bool arc::DLLoader::isType() {
    return makeInstance<T>().has_value();
}
