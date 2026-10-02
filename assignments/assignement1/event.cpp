#include "event.h"
#include "settings.h"

#include <iomanip>

namespace seneca {

    Event::Event(const char* name,
        const std::chrono::nanoseconds& duration)
        : m_name(name), m_duration(duration) {
    }

    std::ostream& operator<<(std::ostream& os,
        const Event& event) {

        static int counter = 0;
        ++counter;

        long long duration = 0;
        int width = 11;

        if (g_settings.m_time_units == "seconds") {
            duration = std::chrono::duration_cast<
                std::chrono::seconds
            >(event.m_duration).count();

            width = 2;
        }
        else if (g_settings.m_time_units == "milliseconds") {
            duration = std::chrono::duration_cast<
                std::chrono::milliseconds
            >(event.m_duration).count();

            width = 5;
        }
        else if (g_settings.m_time_units == "microseconds") {
            duration = std::chrono::duration_cast<
                std::chrono::microseconds
            >(event.m_duration).count();

            width = 8;
        }
        else {
            duration = event.m_duration.count();
            width = 11;
        }

        os << std::right
            << std::setw(2) << counter
            << ": "
            << std::setw(40) << event.m_name
            << " -> "
            << std::setw(width) << duration
            << " " << g_settings.m_time_units;

        return os;
    }

}