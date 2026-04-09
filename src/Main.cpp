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
    int status = SUCCESS;

    if (ac != 2) {
        arc::Core::help();
        status = EPIERROR;
    } else {
        try {
            arc::Core core(av[1]);
            core.play();
        } catch (const arc::exceptions::CoreException &e) {
            std::cerr << "Error: " << e.what() << std::endl;
            std::cerr << "Exit code: 84" << std::endl;
            status = EPIERROR;
        }
    }
    return status;
}
