/*
** EPITECH PROJECT, 2026
** Arcade
** File description:
** Score
*/

#ifndef SCORE_HPP
    #define SCORE_HPP

#include <tuple>
#include <string>
#include <vector>
#include <set>
#include "Arcade.hpp"

namespace arc {

    using CSV = std::vector<std::tuple<std::string, std::string, int>>;

    class Score {
        public:
            Score();
            ~Score() {};

            std::set<size_t, std::greater<size_t>> getScores(std::string, std::string);

        private:
            void parseLine(std::string line);

            CSV _csv;
    };
}

#endif