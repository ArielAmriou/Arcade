/*
** EPITECH PROJECT, 2026
** Arcade
** File description:
** DLLoarder
*/

#include "DLLoader.hpp"

arc::DLLoader::DLLoader(const std::string &path):
    _handle(dlopen(path.data(), RTLD_LAZY)), _path(path)
{
    auto err = dlerror();
    if (err)
        throw arc::exceptions::LibraryLoadError(err);
}

arc::DLLoader::~DLLoader()
{
    if (_handle != nullptr)
        dlclose(_handle);
}

arc::LibType arc::DLLoader::getLibType()
{
    if (_handle == nullptr)
        throw arc::exceptions::LibraryLoadError();
    void *symbol = dlsym(_handle, "getLibType");
    if (symbol == nullptr)
        throw arc::exceptions::LibraryLoadError();
    auto err = dlerror();
    if (err)
        throw arc::exceptions::LibraryLoadError(err);
    auto getLibType = reinterpret_cast<arc::LibType (*)(void)>(symbol);
    if (getLibType() == arc::LibType::None)
        throw arc::exceptions::LibraryLoadError();
    return getLibType();
}

std::string arc::DLLoader::getLibPath()
{
    return _path;
}

arc::DLLoader::DLLoader(DLLoader&& obj)
{
    _handle = obj._handle;
    _path = obj._path;
    obj._handle = nullptr;
    obj._path.clear();
}
