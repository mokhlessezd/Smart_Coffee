#include <gui/screen2_screen/Screen2View.hpp>
#include <cstring>
#include <string.h>
#include <stm32f7xx_hal.h>

Screen2View::Screen2View()
{

}

void Screen2View::setupScreen()
{
    Screen2ViewBase::setupScreen();
}

void Screen2View::tearDownScreen()
{
    Screen2ViewBase::tearDownScreen();
}

void Screen2View::updateTextInTextArea(const char* texte)
{
    Unicode::strncpy(textAreaHistoryBuffer, texte, sizeof(textAreaHistoryBuffer));
    textAreaHistory.setWildcard(textAreaHistoryBuffer);
    textAreaHistory.invalidate();
}
