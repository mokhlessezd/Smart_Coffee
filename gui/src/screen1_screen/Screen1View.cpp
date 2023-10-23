#include <gui/screen1_screen/Screen1View.hpp>
extern uint16_t counterValue; // Déclaration de la variable externe
#include <cstdio>
#include <cstring>
#include "stm32f7xx_hal.h"


;
#ifndef SIMULATOR
#include "stm32f7xx_hal.h"
#endif
Screen1View::Screen1View()
{

}

void Screen1View::setupScreen()
{
    Screen1ViewBase::setupScreen();
}

void Screen1View::tearDownScreen()
{
    Screen1ViewBase::tearDownScreen();
}
void Screen1View::upClicked()
{
    counter++;
    //counterValue = counter;
    Unicode::snprintf(textArea1Buffer, TEXTAREA1_SIZE, "%u", counter);
    textArea1.invalidate();
    presenter->saveButton(counter);
    presenter->sendDateTime();

}
void Screen1View::setCounterValue(uint16_t value)
{
    counter = value;
    //counterValue = value;
    Unicode::snprintf(textArea1Buffer, TEXTAREA1_SIZE, "%u", counter);
    textArea1.invalidate();
}
void Screen1View::updateTime(uint8_t hour, uint8_t minute, uint8_t second)
{
    digitalClock2.setTime24Hour(hour, minute, second);
    if (hour == 0 && minute == 0 && second == 0)
            {
                resetCounter(); // Réinitialiser le compteur
                HAL_Delay(1000);

            }

}

void Screen1View::updateDate(uint8_t date, uint8_t month, uint8_t year)
{
    char dateBuffer[11]; // Buffer pour stocker la date au format "jj/mm/aaaa"
    snprintf(dateBuffer, sizeof(dateBuffer), "%02d/%02d/20%02d", date, month, year);
    //textArea5.invalidate();
    //textArea5.setWildcard(dateBuffer);
    Unicode::strncpy(textAreaDateBuffer, dateBuffer, TEXTAREADATE_SIZE);
    textAreaDate.invalidate();
}
void Screen1View::resetCounter()
{
    counter = 0;
    //counterValue = counter;
    Unicode::snprintf(textArea1Buffer, TEXTAREA1_SIZE, "%u", counter);
    textArea1.invalidate();
    presenter->saveButton(counter); // Appel de la fonction saveButton() avec la valeur du compteur
}
void Screen1View::count(bool state)
{
    counter++;
    //counterValue = counter;
    Unicode::snprintf(textArea1Buffer, TEXTAREA1_SIZE, "%u", counter);
    textArea1.invalidate();
}
