/*
** Timer.hpp for Alfred in /home/wyzlic_a/delivery/Alfred/Timer.hpp
**
** Made by Dimitri Wyzlic
** Login   <dimitri1.wyzlic@epitech.eu>
**
** Started on  Wed Apr 26 03:17:28 2017 Dimitri Wyzlic
** Last update Wed Apr 26 03:17:28 2017 Dimitri Wyzlic
*/

#ifndef ALFRED_TIMER_HPP
#define ALFRED_TIMER_HPP

#include <chrono>
#include <functional>
#include <string>
#include <unordered_map>
#include <utility>
#include <cassert>

namespace Alfred
{

    /**
     * Exception for Timer trigerred when the user want to add a checkpoint which already exist
     */
    class TimerCheckpointAlreadyExist : public std::exception
    {
        const char *what() const throw() override
        { return "Checkpoint already exist.\n"; }
    };

    /**
     * WARNING: The _onTick and _onEnd callback will be called only if they both exist (!= nullptr)
     * You can create them via the constructor or via the setXXXCallback function
     */
    class Timer
    {
        int max = -1;
        long precTime = -1;
        std::chrono::time_point<std::chrono::system_clock> timeStart;
        std::function<void(const std::string &)> _onTick;
        std::function<void()> _onEnd;
        std::function<bool()> _update;
        std::unordered_map<int, std::unordered_map<std::string, std::function<void()>>> _checkpoint;

    public:

        explicit Timer() = default;

        /**
         * Create a Timer from max seconds
         * @param max max seconds
         */
        explicit Timer(int max) :
            max(max),
            _update([this]() -> bool { return (updateWithoutCallback()); })
        {};

        /**
         * Create a Timer from max seconds
         * @param max max seconds
         * @param _onTick Callback called each second. Signature must be std::function<void(const std::string &)> string is the time beautified
         * @param _onEnd Callback called at the end of the time
         */
        explicit Timer(int max, std::function<void(const std::string &)> _onTick,
                       std::function<void()> _onEnd = nullptr) :
            max(max),
            _onTick(std::move(_onTick)),
            _onEnd(std::move(_onEnd)),
            _update([this]() -> bool { return (updateWithCallback()); })
        {};

        /**
         * Set max time
         * @param time
         */

        Timer &operator=(const Timer &other)
        {
            max = other.max;
            precTime = other.precTime;
            timeStart = other.timeStart;
            _onTick = other._onTick;
            _onEnd = other._onEnd;
            _update = other._update;
            _checkpoint = other._checkpoint; //not sure about this one
            return *this;
        }

        void setTime(int time)
        {
            max = time;
            precTime = -1;
        }

        /*
         * Start the timer
         */
        void start()
        {
            assert(max > 0 && "Alfred - Timer: You have not set time before calling start (timer.setTime)");
            timeStart = std::chrono::system_clock::now();
            precTime = -1;
        }

        /*
         * Restart the timer
         */
        void restart()
        { start(); };

        /**
         * Update the timer
         * @return return true if time is over. false otherwise
         */
        bool update() const
        { return (_update()); };

        /**
         * Add a checkpoint to the timer. Raise exception if a checkpoint with this name already exist at time time
         * @param time Triggered at Time seconds
         * @param name Name of the breakpoint
         * @param func Callback in form std::function<void()>
         */
        void addCheckpoint(int time, const std::string &name, std::function<void()> func)
        {
            if (_onTick != nullptr)
                _update = [this]() -> bool { return (updateWithCallbackWithCheckpoint()); };
            else
                _update = [this]() -> bool { return (updateWithoutCallbackWithCheckpoint()); };

            if (_checkpoint[time].count(name))
                throw TimerCheckpointAlreadyExist();
            _checkpoint[time][name] = std::move(func);
        }

        /**
         * Delete a checkpoint with name name.
         * @param name Name of the checkpoint
         */
        void deleteCheckpoint(const std::string &name)
        {
            for (auto &it : _checkpoint) {
                it.second.erase(name);
                if (it.second.empty())
                    _checkpoint.erase(it.first);
            }
            defUpdateFonction();
        }

        /**
         * Delete all checkpoint with time time
         * @param time Time at wich delete all checkpoint
         */
        void deleteCheckpoint(int time)
        {
            _checkpoint.erase(time);
            defUpdateFonction();
        }

        /**
         * Set callback called each tick
         */
        void setOnTickCallback(std::function<void(const std::string &)> func)
        {
            _onTick = func;
            defUpdateFonction();
        }

        /**
         * Set callback called at the end
         */
        void setEndCallback(std::function<void()> func)
        {
            _onEnd = func;
            defUpdateFonction();
        }

    private:

        /**
         * Beautify from seconde to min
         * @param sec
         * @return string in form of -> MIN:SEC like 1:42
         */
        std::string beautifySec(long sec) const
        {
            std::string out;

            auto minute = sec / 60;
            if (minute < 10)
                out += "0";
            out += std::to_string(minute) + ":";
            sec = sec - minute * 60;
            if (sec < 10)
                out += "0";
            out += std::to_string(sec);
            return out;
        }

        //All the above updateXXX function are here to prevent if branch and optimise for the CPU (avoid lot of JMP)

        /**
         * Check if time is over and return the result
         * Call _onTick or _onEnd depending of the situation
         * @return return true if time is over. false otherwise
         */
        bool updateWithCallback()
        {
            auto now = std::chrono::system_clock::now();
            auto remaining_time = max - std::chrono::duration_cast<std::chrono::seconds>(now - timeStart).count();

            if (remaining_time > 0) {
                if (remaining_time != precTime) {
                    precTime = remaining_time;
                    _onTick(beautifySec(remaining_time));
                }
            } else {
                if (_onEnd != nullptr)
                    _onEnd();
                _update = [this]() -> bool { return (nothing()); };
            }
            return remaining_time <= 0;
        }

        /**
         * Check if time is over and return the result
        * @return return true if time is over. false otherwise
        */
        bool updateWithoutCallback() const
        {
            auto now = std::chrono::system_clock::now();
            auto remaining_time = max - std::chrono::duration_cast<std::chrono::seconds>(now - timeStart).count();
            return remaining_time <= 0;
        }

        bool updateWithoutCallbackWithCheckpoint()
        {
            auto now = std::chrono::system_clock::now();
            auto remaining_time = max - std::chrono::duration_cast<std::chrono::seconds>(now - timeStart).count();
            if (precTime != remaining_time) {
                for (const auto &it : _checkpoint[remaining_time])
                    it.second();
                precTime = remaining_time;
            }
            return remaining_time <= 0;
        }

        bool updateWithCallbackWithCheckpoint()
        {
            auto now = std::chrono::system_clock::now();
            auto remaining_time = max - std::chrono::duration_cast<std::chrono::seconds>(now - timeStart).count();

            if (remaining_time > 0) {
                if (remaining_time != precTime) {
                    precTime = remaining_time;
                    _onTick(beautifySec(remaining_time));
                    for (const auto &it : _checkpoint[remaining_time])
                        it.second();
                }
            } else {
                if (_onEnd != nullptr)
                    _onEnd();
                _update = [this]() -> bool { return (nothing()); };
            }
            return remaining_time <= 0;
        }

        static bool nothing()
        {
            return true;
        }

        inline void defUpdateFonction()
        {
            if (_checkpoint.empty()) {
                if (_onTick != nullptr)
                    _update = [this]() -> bool { return (updateWithCallback()); };
                else
                    _update = [this]() -> bool { return (updateWithoutCallback()); };
            } else {
                if (_onTick != nullptr)
                    _update = [this]() -> bool { return (updateWithCallbackWithCheckpoint()); };
                else
                    _update = [this]() -> bool { return (updateWithoutCallbackWithCheckpoint()); };
            }
        }
    };
}

#endif //ALFRED_TIMER_HPP
