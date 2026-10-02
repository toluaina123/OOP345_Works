#include "logger.h"

namespace seneca {

    Logger::~Logger()
    {
        delete[] m_events;
    }

    Logger::Logger(Logger&& other) noexcept
        : m_events(other.m_events),
        m_size(other.m_size),
        m_capacity(other.m_capacity)
    {
        other.m_events = nullptr;
        other.m_size = 0;
        other.m_capacity = 0;
    }

    Logger& Logger::operator=(Logger&& other) noexcept
    {
        if (this != &other)
        {
            delete[] m_events;

            m_events = other.m_events;
            m_size = other.m_size;
            m_capacity = other.m_capacity;

            other.m_events = nullptr;
            other.m_size = 0;
            other.m_capacity = 0;
        }

        return *this;
    }

    void Logger::addEvent(const Event& event)
    {
        if (m_size == m_capacity)
        {
            std::size_t newCapacity =
                (m_capacity == 0) ? 1 : m_capacity * 2;

            Event* newEvents = new Event[newCapacity];

            for (std::size_t i = 0; i < m_size; ++i)
            {
                newEvents[i] = m_events[i];
            }

            delete[] m_events;

            m_events = newEvents;
            m_capacity = newCapacity;
        }

        m_events[m_size] = event;
        ++m_size;
    }

    std::ostream& operator<<(std::ostream& out,
        const Logger& logger)
    {
        for (std::size_t i = 0; i < logger.m_size; ++i)
        {
            out << logger.m_events[i] << '\n';
        }

        return out;
    }

}