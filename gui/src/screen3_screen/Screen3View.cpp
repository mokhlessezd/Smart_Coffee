#include <gui/screen3_screen/Screen3View.hpp>
#ifndef SIMULATOR
#include "stdio.h"
#include <cstring>
#include "main.h"
#endif
extern "C"
{
    extern UART_HandleTypeDef huart6;
}
Screen3View::Screen3View()
{
	keyboard.setPosition (77,25,434,238);
	add(keyboard);
	keyboard.setVisible (false);
	keyboard.invalidate();

}

void Screen3View::setupScreen()
{
    Screen3ViewBase::setupScreen();
}

void Screen3View::tearDownScreen()
{
    Screen3ViewBase::tearDownScreen();
}
void Screen3View::NameClicked()
{
	keyboard.setVisible (true);
	keyboard.invalidate();
	flexButtonOk.setVisible(true);
	flexButtonOk.invalidate();
	flexButtonExit.setVisible(true);
	flexButtonExit.invalidate();
	buttonWithLabelSend.setVisible(false);
	buttonWithLabelSend.invalidate();
	namemod = 1;
	mdpmod = 0;
	idmod = 0;
}
void Screen3View::MdpClicked()
{
	keyboard.setVisible (true);
	keyboard.invalidate();
	flexButtonOk.setVisible(true);
	flexButtonOk.invalidate();
	flexButtonExit.setVisible(true);
	flexButtonExit.invalidate();
	buttonWithLabelSend.setVisible(false);
	buttonWithLabelSend.invalidate();
	namemod = 0;
	mdpmod = 1;
	idmod = 0;
}
void Screen3View::IdClicked()
{
	keyboard.setVisible (true);
	keyboard.invalidate();
	flexButtonOk.setVisible(true);
	flexButtonOk.invalidate();
	flexButtonExit.setVisible(true);
	flexButtonExit.invalidate();
	buttonWithLabelSend.setVisible(false);
	buttonWithLabelSend.invalidate();
	namemod = 0;
	mdpmod = 0;
	idmod = 1;
}
void Screen3View::ExitClicked()
{
	keyboard.setVisible (false);
	keyboard.invalidate();
	flexButtonOk.setVisible(false);
	flexButtonOk.invalidate();
	flexButtonExit.setVisible(false);
	flexButtonExit.invalidate();
	buttonWithLabelSend.setVisible(true);
	buttonWithLabelSend.invalidate();
	namemod = mdpmod = idmod = 0;
}
void Screen3View::OkClicked()
{
	keyboard.setVisible (false);
	keyboard.invalidate();
	flexButtonOk.setVisible(false);
	flexButtonOk.invalidate();
	flexButtonExit.setVisible(false);
	flexButtonExit.invalidate();
	buttonWithLabelSend.setVisible(true);
	buttonWithLabelSend.invalidate();
	if (namemod)
	{
		Unicode::strncpy(textAreaNameBuffer, keyboard.getBuffer(), TEXTAREANAME_SIZE);
		textAreaName.invalidate();



	}
	if (mdpmod)
		{
			Unicode::strncpy(textAreaMdpBuffer, keyboard.getBuffer(), TEXTAREAMDP_SIZE);
			textAreaMdp.invalidate();



		}
	if (idmod)
			{
				Unicode::strncpy(textAreaIdBuffer, keyboard.getBuffer(), TEXTAREAID_SIZE);
				textAreaId.invalidate();

			}
	keyboard.clearBuffer();


}

void Screen3View::SendClicked()
{

	int i=0;
	do
	{
		nameBuf[i] = (char) textAreaNameBuffer[i];
		i++;
		//textAreaNon.setVisible(true);
		//textAreaNon.invalidate();
	}while (textAreaNameBuffer[i]!=0);
	    i=0;
		do
		{
			mdpBuf[i] = (char) textAreaMdpBuffer[i];
			i++;
			//textAreaNon.setVisible(true);
			//textAreaNon.invalidate();
		}while (textAreaMdpBuffer[i]!=0);
		i=0;
		do
		{
			idBuf[i] = (char) textAreaIdBuffer[i];
			i++;
			//textAreaNon.setVisible(true);
			//textAreaNon.invalidate();
		}while (textAreaIdBuffer[i]!=0);

	sprintf (dataBuf, "%s,%s,%s\r\n", nameBuf,mdpBuf, idBuf);
	presenter->sendData(dataBuf);
	memset (nameBuf, '\0', TEXTAREANAME_SIZE);
	memset (mdpBuf, '\0', TEXTAREAMDP_SIZE);
	memset (idBuf, '\0', TEXTAREAID_SIZE);
	HAL_Delay(2000);
	flexButtonId.setVisible(false);
	flexButtonId.invalidate();



    //textAreaNon.setVisible(true);
    //textAreaNon.invalidate();

    //uint8_t rxData[2]; // Vous pouvez ajuster la taille du tampon en fonction de votre besoin
   // HAL_StatusTypeDef rxStatus = HAL_UART_Receive(&huart6, rxData, 2, HAL_MAX_DELAY);






}

