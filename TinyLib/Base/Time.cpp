#include "Time.h"


namespace tl
{
    /// @brief Time value gets set right away upon creation.
    Time::Time()
    {
        update();
    }


    /// @brief Probably avoid this for now lol. - I plan to change it later.
    /// @param timeValue What number you want the internal time data as.
    Time::Time(u64 timeValue)
    {
        time = timeValue;
    }


    /// @brief Nothing to clean up here for now.
    Time::~Time()
    {

    }


    /// @brief Get the current time data from this object.
    /// @return Time data.
    u64 Time::getTime()
    {
        return time;
    }


    /// @brief Update the time data to what it should be right now.
    void Time::update()
    {
        time = GetTickCount();
    }


    /// @brief Static way to get a current time value.
    /// @return Current time value.
    u64 Time::currentTime()
    {
        return GetTickCount();
    }
}