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

namespace Alfred
{
    class Random
    {
    public:
        static const std::string string(const size_t max)
        {
            auto randchar = []() -> char
            {
                const char charset[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
                const size_t max_index = (sizeof(charset) - 1);
                return charset[ rand() % max_index ];
            };
            std::string str(max, 0);
            std::generate_n( str.begin(), max, randchar );
            return str;
        }

        static int randint(size_t min, size_t max)
        {
            std::random_device rd;
            std::mt19937 rng(rd());
            std::uniform_int_distribution<int> uni(min, max);
            return(uni(rng));
        }
    };
}

#endif //ALFRED_RANDOM_HPP
