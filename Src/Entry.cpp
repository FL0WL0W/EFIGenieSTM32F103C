#include "usbd_cdc_if.h"
#include "EmbeddedIOServiceCollection.h"
#include "Stm32HalDigitalService.h"
#include "Stm32HalTimerService.h"
#include "Stm32HalAnalogService.h"
#include "Stm32HalPwmService.h"
#include "EngineMain.h"

using namespace EmbeddedIOServices;
using namespace Stm32;
using namespace Engine;

extern char _config;

extern "C"
{
  // int tickDiff = 0;
  // int maxTickDiff = 0;
  // int minTickDiff = 0;
  EmbeddedIOServiceCollection _embeddedIOServiceCollection;
  EngineMain *_engineMain;
  void Setup() 
  {
    const char responseText1[34] = "Initializing EmbeddedIOServices\n\r";
    CDC_Transmit_FS((uint8_t*)responseText1, strlen(responseText1));
    _embeddedIOServiceCollection.DigitalService = new Stm32HalDigitalService();
    _embeddedIOServiceCollection.AnalogService = new Stm32HalAnalogService();
    _embeddedIOServiceCollection.TimerService = new Stm32HalTimerService(1);
    _embeddedIOServiceCollection.PwmService = new Stm32HalPwmService();
    const char responseText2[33] = "EmbeddedIOServices Initialized\n\r";
    CDC_Transmit_FS((uint8_t*)responseText2, strlen(responseText2));

    const char responseText3[26] = "Initializing EngineMain\n\r";
    CDC_Transmit_FS((uint8_t*)responseText3, strlen(responseText3));
		unsigned int _configSize = 0;
    _engineMain = new EngineMain(reinterpret_cast<void*>(&_config), _configSize, &_embeddedIOServiceCollection);
    const char responseText4[25] = "EngineMain Initialized\n\r";
    CDC_Transmit_FS((uint8_t*)responseText4, strlen(responseText4));

    const char responseText5[24] = "Setting Up EngineMain\n\r";
    CDC_Transmit_FS((uint8_t*)responseText5, strlen(responseText5));
    _engineMain->Setup();
    const char responseText6[19] = "EngineMain Setup\n\r";
    CDC_Transmit_FS((uint8_t*)responseText6, strlen(responseText6));
  }
  void Loop() 
  {
    char responseText[50] = "Looping EngineMain\n\r";
    //sprintf(responseText, "%d\t:%d\t:\t%d\n\r", minTickDiff, tickDiff, maxTickDiff);
    CDC_Transmit_FS((uint8_t*)responseText, strlen(responseText));
    _engineMain->Loop();
  }
}