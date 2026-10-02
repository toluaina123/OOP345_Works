#include "event.h"
#include "settings.h"

#include <iomanip>

namespace seneca {

    Event::Event(const char* name,
        const std::chrono::nanoseconds& duration)
        : m_name(name),
        m_duration(duration)
    {
    }

    std::ostream& operator<<(std::ostream& out,
        const Event& event)
    {
        static int counter = 0;

        ++counter;

        out << std::setw(2) << counter
            << ": "
            << std::setw(40) << event.m_name
            << " -> ";

        if (g_settings.m_time_units == "seconds")
        {
            out << std::setw(2)
                << std::chrono::duration_cast<
                std::chrono::seconds>(
                    event.m_duration)
                .count()
                << " seconds";
        }
        else if (g_settings.m_time_units == "milliseconds")
        {
            out << std::setw(5)
                << std::chrono::duration_cast<
                std::chrono::milliseconds>(
                    event.m_duration)
                .count()
                << " milliseconds";
        }
        else if (g_settings.m_time_units == "microseconds")
        {
            out << std::setw(8)
                << std::chrono::duration_cast<
                std::chrono::microseconds>(
                    event.m_duration)
                .count()
                << " microseconds";
        }
        else
        {
            out << std::setw(11)
                << event.m_duration.count()
                << " nanoseconds";
        }

        return out;
    }

}