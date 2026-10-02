#ifndef SENECA_EVENT_H
#define SENECA_EVENT_H

#include <chrono>
#include <ostream>
#include <string>

namespace seneca {

    class Event {
        std::string m_name{};
        std::chrono::nanoseconds m_duration{};

    public:
        Event() = default;

        Event(const char* name,
            const std::chrono::nanoseconds& duration);

        friend std::ostream& operator<<(
            std::ostream& out,
            const Event& event);
    };

}

#endif