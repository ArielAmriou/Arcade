/*
** EPITECH PROJECT, 2026
** Arcade
** File description:
** Main
*/

#include <iostream>
#include "Arcade.hpp"
#include "Core.hpp"
#include "Exceptions.hpp"

int main(const int ac, const char **av)
{
    if (ac != 2)
        return EPIERROR;
    
    try {
        arc::Core core(av[1]);
        core.play();
    } catch (const arc::exceptions::NotGraphical &e) {
        arc::Core::help(av[1]);
        return EPIERROR;
    } catch (const arc::exceptions::LibraryLoadError &e) {
        std::cerr << e.what() << std::endl;
        return EPIERROR;
    }
}
