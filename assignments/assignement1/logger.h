#ifndef SENECA_LOGGER_H
#define SENECA_LOGGER_H

#include "event.h"
#include <ostream>

namespace seneca {

    class Logger {
        Event* m_events{};
        size_t m_size{};
        size_t m_capacity{};

    public:
        Logger() = default;

        ~Logger();

        Logger(const Logger&) = delete;
        Logger& operator=(const Logger&) = delete;

        Logger(Logger&& other) noexcept;
        Logger& operator=(Logger&& other) noexcept;

        void addEvent(const Event& event);

        friend std::ostream& operator<<(std::ostream& os,
            const Logger& logger);
    };

}

#endif