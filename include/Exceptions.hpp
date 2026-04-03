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

        class NotGraphical : public std::exception {
            public:
                const char* what() const throw() { return "Not a graphical library"; }
        };

        class LibraryLoadError : public std::exception {
            public:
                const char* what() const throw() { return "Unexpected error while loading library"; }
        };

        class NoEntryPoint : public std::exception {
            public:
                const char* what() const throw() { return "No entry point in dynamic library"; }
        };

        class AssetLoadError : public std::exception {
            public:
                const char* what() const throw() { return "Error while loading assets"; }
        };
    }

}

#endif /* !EXCEPTIONS_HPP_ */
