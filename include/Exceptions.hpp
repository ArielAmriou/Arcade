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
                const char* what() const throw() { return "Not a graphical library."; }
        };

        class LibraryLoadError : public std::exception {
            public:
                LibraryLoadError() = default;
                LibraryLoadError(const std::string &msg): _msg(msg) {};
                const char* what() const throw() {
                    if (_msg.empty())
                        return "Unexpected error while loading library.";
                    return _msg.c_str();
                }
            private:
                std::string _msg;
            
        };

        class AssetLoadError : public std::exception {
            public:
                const char* what() const throw() { return "Error while loading assets."; }
        };

        class NoSuchLib : public std::exception {
            public:
                NoSuchLib(const std::string &path): _msg(path + ": no such dynamic library.") {};
                const char* what() const throw() { return _msg.c_str(); }
            private:
                std::string _msg;
        };
    }

}

#endif /* !EXCEPTIONS_HPP_ */
