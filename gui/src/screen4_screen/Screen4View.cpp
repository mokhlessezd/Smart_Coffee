#include <gui/screen4_screen/Screen4View.hpp>

Screen4View::Screen4View()
{

}

void Screen4View::setupScreen()
{
    Screen4ViewBase::setupScreen();
}

void Screen4View::tearDownScreen()
{
    Screen4ViewBase::tearDownScreen();
}
void Screen4View::updateTime(uint8_t hour, uint8_t minute, uint8_t second)
{
    analogClock1.setTime24Hour(hour, minute, second);

}
