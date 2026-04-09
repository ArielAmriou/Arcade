/*
** EPITECH PROJECT, 2026
** Arcade
** File description:
** score
*/

#include <iostream>
#include <sstream>
#include <fstream>
#include "Score.hpp"


arc::Score::Score()
{
    std::string scorePath(SCORE_PATH);
    std::ifstream infile(scorePath);
    std::string line;
    while (std::getline(infile, line))
        parseLine(line);    
}

void arc::Score::parseLine(std::string line)
{
    std::istringstream tmp(line);
    std::string name;
    std::string game;
    std::string strScore;
    size_t score = 0;

    if (std::getline(tmp, name, ',')
        && std::getline(tmp, game, ',')
        && std::getline(tmp, strScore)) {
        std::istringstream issScore(strScore);
        issScore >> score;
        if (!issScore.fail())
            _csv.push_back(std::make_tuple(name, game, score));
    }
}

std::set<size_t, std::greater<std::size_t>>
    arc::Score::getScores(std::string name, std::string game)
{
    std::set<size_t, std::greater<std::size_t>> list;

    for (auto line: _csv) {
        if (std::get<0>(line) == name && std::get<1>(line) == game)
            list.insert(std::get<2>(line));
    }
    return list;
}