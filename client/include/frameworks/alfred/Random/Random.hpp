/*
** Random.hpp for Alfred in /home/wyzlic_a/delivery/Alfred/Random.hpp
**
** Made by Dimitri Wyzlic
** Login   <dimitri1.wyzlic@epitech.eu>
**
** Started on  Mon Sep 18 01:18:28 2017 Dimitri Wyzlic
** Last update Mon Sep 18 01:18:28 2017 Dimitri Wyzlic
*/

#ifndef ALFRED_RANDOM_HPP
#define ALFRED_RANDOM_HPP

#include <algorithm>
#include <random>
#include <string>

namespace Alfred
{
    class Random
    {
    public:
        static const std::string &string(const unsigned int max)
        {
            const std::string VALID_CHARS = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
            std::default_random_engine generator;
            std::uniform_int_distribution<int> distribution(0, VALID_CHARS.size() - 1);
            auto out = new std::string();
            std::generate_n(std::back_inserter(*out), max, [&]() {
                return VALID_CHARS[distribution(generator)];
            });
            return *out;
        }

        static const int randint(unsigned int min, unsigned int max)
        {
            std::random_device rd;
            std::mt19937 rng(rd());
            std::uniform_int_distribution<int> uni(min, max);
            return(uni(rng));
        }
    };
}

#endif //ALFRED_RANDOM_HPP
