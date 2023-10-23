#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>
#ifndef SIMULATOR
#include "stm32f7xx_hal.h"
#include "main.h"
#include "cstdio"
#include "string.h"
#include <cstdio>

char histoBuffer[700];
extern "C"
{
    extern UART_HandleTypeDef huart6;
}
extern RTC_HandleTypeDef hrtc;
extern RTC_TimeTypeDef RTC_Time;
extern RTC_DateTypeDef RTC_Date;
#endif
Model::Model() : modelListener(0), button_State(false), counterValue(0)
{

}
static int i = 1;
void Model::tick()
{
	HAL_RTC_GetTime(&hrtc, &RTC_Time, FORMAT_BIN);
	HAL_RTC_GetDate(&hrtc, &RTC_Date, FORMAT_BIN);
	const char* texteDuBuffer = getTextFromBuffer();
	modelListener->updateTime(RTC_Time.Hours, RTC_Time.Minutes, RTC_Time.Seconds);
	modelListener->updateDate(RTC_Date.Date, RTC_Date.Month, RTC_Date.Year);
	modelListener->updateTextFromBuffer(texteDuBuffer);
	if (HAL_GPIO_ReadPin(GPIOG, GPIO_PIN_7) )
	    {
	        button_State = true;
	        HAL_Delay(500);
	        modelListener->count(true);
	        saveButton(counterValue);
	        sendDateTime(); // Envoyez la date et l'heure actuelles via UART
	        char uartBuffer[20]; // Créer un tampon pour stocker la valeur
	        snprintf(uartBuffer, sizeof(uartBuffer), "compt%d\n", counterValue);
	        HAL_UART_Transmit(&huart6, (uint8_t *)uartBuffer, strlen(uartBuffer), 10);
	    }
	    else
	    {
	        button_State = false;
	    }
	if (RTC_Time.Hours == 23 && RTC_Time.Minutes == 59 && RTC_Time.Seconds == 55) {
		    char buffer[50];
		    char historbuffer[50];
	        snprintf(buffer, sizeof(buffer), "Date:%02d\n", 1 + RTC_Date.Date);
	        snprintf(historbuffer, sizeof(historbuffer), "histo 20%02d-%02d-%02d\n", RTC_Date.Year, RTC_Date.Month, RTC_Date.Date);
	        HAL_UART_Transmit(&huart6, (uint8_t *)buffer, strlen(buffer), 100);
	        HAL_Delay(1500);
	        HAL_UART_Transmit(&huart6, (uint8_t *)historbuffer, strlen(historbuffer), 100);
	        HAL_Delay(1000);


	    }
	if (RTC_Time.Hours == 23 && RTC_Time.Minutes == 59 && RTC_Time.Seconds == 59) {
	    char tempBuffer[50];

	    if (i % 3 == 0) {
	        snprintf(tempBuffer, sizeof(tempBuffer), "%02d-%02d-20%02d N=%d \n",
	                 RTC_Date.Date, RTC_Date.Month, RTC_Date.Year, counterValue);
	    } else {

	        snprintf(tempBuffer, sizeof(tempBuffer), "%02d-%02d-20%02d N=%d   ",
	                 RTC_Date.Date, RTC_Date.Month, RTC_Date.Year, counterValue);
	    }

	    // Utilisez strcat pour ajouter le contenu de tempBuffer à histoBuffer
	    strcat(histoBuffer, tempBuffer);

	    HAL_Delay(1000);

	    // Incrémentez le compteur i
	    i++;
	}



}
void Model::saveButton(int counterValue)
{
	HAL_Delay(100);
    this->counterValue = counterValue;
    char countBuffer[20]; // Créer un tampon pour stocker la valeur
    snprintf(countBuffer, sizeof(countBuffer), "compt%d\n", counterValue);
    HAL_UART_Transmit(&huart6, (uint8_t *)countBuffer, strlen(countBuffer), 10);
}

int Model::getCounterValue() const
{
    return counterValue;
}


void Model::sendData (char *data)
{
	HAL_UART_Transmit(&huart6, (uint8_t *)data, strlen(data), 100);

}
const char* Model::getTextFromBuffer()
{
    // Copier le contenu du buffer dans une chaîne de caractères
    static char texte[700];
    strncpy(texte, histoBuffer, sizeof(texte));

    // Assurez-vous que la chaîne est terminée par un caractère nul
    texte[sizeof(texte) - 1] = '\0';

    return texte;
}
void Model::sendDateTime() {
    HAL_RTC_GetTime(&hrtc, &RTC_Time, FORMAT_BIN);
    HAL_RTC_GetDate(&hrtc, &RTC_Date, FORMAT_BIN);
	HAL_Delay(100);


    char dateTimeBuffer[50]; // Créez un tampon pour stocker la date et l'heure
    //char historbuffer[50];
    snprintf(dateTimeBuffer, sizeof(dateTimeBuffer), "times20%02d-%02d-%02dT%02d:%02d:%02dt\n",
             RTC_Date.Year, RTC_Date.Month, RTC_Date.Date,
             RTC_Time.Hours, RTC_Time.Minutes, RTC_Time.Seconds);
    //HAL_Delay(200);
    //snprintf(historbuffer, sizeof(historbuffer), "20%02d-%02d-%02d\n", RTC_Date.Year, RTC_Date.Month, RTC_Date.Date);
    //HAL_UART_Transmit(&huart6, (uint8_t *)historbuffer, strlen(historbuffer), 100);
   // HAL_Delay(200);
    HAL_UART_Transmit(&huart6, (uint8_t *)dateTimeBuffer, strlen(dateTimeBuffer), 100);
    //HAL_Delay(300);
    //char historbuffer[50];
    //snprintf(historbuffer, sizeof(historbuffer), "key20%02d-%02d-%02d\n", RTC_Date.Year, RTC_Date.Month, RTC_Date.Date);
    //HAL_UART_Transmit(&huart6, (uint8_t *)historbuffer, strlen(historbuffer), 100);
}
