#include "usbd_cdc_if.h"
#include "EmbeddedIOServiceCollection.h"
#include "Stm32HalDigitalService.h"
#include "Stm32HalTimerService.h"
#include "Stm32HalAnalogService.h"
#include "Stm32HalPwmService.h"
#include "EngineMain.h"
#include "Variable.h"

using namespace OperationArchitecture;
using namespace EmbeddedIOServices;
using namespace Stm32;
using namespace Engine;

extern char _config;

extern "C"
{
  uint32_t Commands[32];
  uint8_t CommandReadPointer = 0;
  bool secondCommand = false;
  EmbeddedIOServiceCollection _embeddedIOServiceCollection;
  EngineMain *_engineMain;
  Variable *loopTime;
  uint32_t prev;
  uint16_t degree = 0;
  uint32_t ticksPerDegree = 1000;
  void Setup() 
  {
    _embeddedIOServiceCollection.DigitalService = new Stm32HalDigitalService();
    _embeddedIOServiceCollection.AnalogService = new Stm32HalAnalogService();
    _embeddedIOServiceCollection.TimerService = new Stm32HalTimerService(TimerIndex::Index1);
    _embeddedIOServiceCollection.PwmService = new Stm32HalPwmService();


    _embeddedIOServiceCollection.DigitalService->InitPin(0, Out);
    _embeddedIOServiceCollection.DigitalService->InitPin(1, Out);
    prev = DWT->CYCCNT;
    __disable_irq();
  }
  void Loop() 
  {

    uint32_t degree360 = degree % 360;
    
    if(degree == 0)
    {
      while(prev - DWT->CYCCNT < ticksPerDegree) ;
      _embeddedIOServiceCollection.DigitalService->WritePin(0, true);
      _embeddedIOServiceCollection.DigitalService->WritePin(1, false);
    }
    else if(degree == 360)
    {
      while(prev - DWT->CYCCNT < ticksPerDegree) ;
      _embeddedIOServiceCollection.DigitalService->WritePin(0, false);
      _embeddedIOServiceCollection.DigitalService->WritePin(1, false);
    }
    else if(degree % 15 == 0)
    {
      while(prev - DWT->CYCCNT < ticksPerDegree) ;
      _embeddedIOServiceCollection.DigitalService->WritePin(1, false);
    }
    else if(
      degree360 == 12 ||
      degree360 == 18 ||
      degree360 == 33 ||
      degree360 == 48 ||
      degree360 == 63 ||
      degree360 == 78 ||
      degree360 == 102 ||
      degree360 == 108 ||
      degree360 == 123 ||
      degree360 == 138 ||
      degree360 == 162 ||
      degree360 == 177 ||
      degree360 == 183 ||
      degree360 == 198 ||
      degree360 == 222 ||
      degree360 == 237 ||
      degree360 == 252 ||
      degree360 == 258 ||
      degree360 == 282 ||
      degree360 == 288 ||
      degree360 == 312 ||
      degree360 == 327 ||
      degree360 == 342 ||
      degree360 == 357
      )
    {
      while(prev - DWT->CYCCNT < ticksPerDegree) ;
      _embeddedIOServiceCollection.DigitalService->WritePin(1, true);
    }
    else
    {
      while(prev - DWT->CYCCNT < ticksPerDegree) ;
    }

    degree++;
    if(degree >= 720)
      degree = 0;

    prev += ticksPerDegree;
  }
}