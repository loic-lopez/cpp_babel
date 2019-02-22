/*
** NonCopyable.hpp for Alfred in /home/wyzlic_a/delivery/Alfred/NonCopyable.hpp
**
** Made by Dimitri Wyzlic
** Login   <dimitri1.wyzlic@epitech.eu>
**
** Started on  Thu Jun 01 02:16:43 2017 Dimitri Wyzlic
** Last update Thu Jun 01 02:16:43 2017 Dimitri Wyzlic
*/

#ifndef ALFRED_NONCOPYABLE_HPP
#define ALFRED_NONCOPYABLE_HPP

namespace Alfred
{
    class NonCopyable
    {
    public:
        NonCopyable() = default;
        virtual ~NonCopyable() = default;

        NonCopyable(NonCopyable const &) = delete;

        NonCopyable(NonCopyable &&) = delete;

        NonCopyable &operator=(const NonCopyable &) = delete;

        NonCopyable &operator=(NonCopyable &&) = delete;
    };
}
#endif //ALFRED_NONCOPYABLE_HPP
