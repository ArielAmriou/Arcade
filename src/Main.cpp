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
        } catch (const arc::exceptions::NotGraphical &e) {
            std::cerr << "Error: '" << av[1] << "' not a graphical library" << std::endl;
            std::cerr << "Exit code: 84" << std::endl;
            status = EPIERROR;
        } catch (const arc::exceptions::LibraryLoadError &e) {
            std::cerr << e.what() << std::endl;
            status = EPIERROR;
        } catch (const arc::exceptions::NoSuchLib &e) {
            std::cerr << e.what() << std::endl;
            status = EPIERROR;
        } catch (const arc::exceptions::AssetLoadError &e) {
            std::cerr << e.what() << std::endl;
            status = EPIERROR;
        }
    }
    return status;
}
