/*
** EPITECH PROJECT, 2026
** Arcade
** File description:
** Exceptions
*/

#ifndef EXCEPTIONS_HPP_
#define EXCEPTIONS_HPP_

#include <exception>

namespace arc {

    namespace exceptions {

        class CoreException : public std::exception {
            public:
                CoreException(std::string str) : _str(str) {};

                virtual const char *what() const noexcept override
                    { return _str.c_str(); };
            private:
                std::string _str;
        };

        class NotGraphical : public CoreException {
            public:
                NotGraphical(const std::string &path): CoreException("'" + path + "': not a graphical library") {};
        };

        class LibraryLoadError : public CoreException {
            public:
                LibraryLoadError(): CoreException("Unexpected error while loading library.") {};
                LibraryLoadError(const std::string &msg): CoreException(msg) {};
        };

        class AssetLoadError : public CoreException {
            public:
                AssetLoadError(): CoreException("Error while loading assets.") {};
        };

        class NoSuchLib : public CoreException {
            public:
                NoSuchLib(const std::string &path): CoreException("'" + path + "': no such dynamic library.") {};
        };
    }

}

#endif /* !EXCEPTIONS_HPP_ */
