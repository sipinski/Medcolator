/*
*  serialcontroller.h
*  Instructograph
*
*  Created by Felix Jodoin.
*/

#pragma once

#include <string>
#include "SDL/SDL.h"
#include "SDL/SDL_thread.h"

#include <SerialStream.h>

extern bool g_bQuit;

class SerialReader
{
public:
  SerialReader(const std::string &strPath);
  ~SerialReader();

  bool IsActive(std::string m_input);

private:
  void ThreadMain();
  static int ThreadDispatch(void *pClass);

  std::string m_strPath;
  //char m_cInput;
  bool m_bActive;

  SDL_mutex *m_pMutex;
  SDL_Thread *m_pThread;
  LibSerial::SerialStream *m_pSerialStream;
};
