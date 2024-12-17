#include <Arduino.h>
#include <LiquidCrystal.h>



/// @brief Returns true every TIME * 100ms
/// @param Time 
/// @return 
bool LcdRefresh(int Time)
{
    if ((int(millis()/100) % Time) == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}
