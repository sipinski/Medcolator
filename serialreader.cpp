/*
*  serialreader.cpp
*  Instructograph
*
*  Created by Felix Jodoin.
*/

#include "serialreader.h"
#include "SDL/SDL.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>

#include <SerialStream.h>

using namespace LibSerial;

char cNext = 0;

SerialReader::SerialReader(const std::string& strPath) :
m_strPath(strPath),
m_bActive(false),
m_pMutex(NULL),
m_pThread(NULL),
m_pSerialStream(NULL)
{
  m_pSerialStream = new SerialStream();
  m_pSerialStream->Open(m_strPath);
  m_pSerialStream->SetBaudRate(SerialStreamBuf::BAUD_1200);
  m_pSerialStream->SetCharSize(SerialStreamBuf::CHAR_SIZE_8);
  m_pSerialStream->SetNumOfStopBits(1);
  m_pSerialStream->SetParity(SerialStreamBuf::PARITY_NONE);
  m_pSerialStream->SetFlowControl(SerialStreamBuf::FLOW_CONTROL_NONE);
  m_pMutex = SDL_CreateMutex();
  m_pThread = SDL_CreateThread(ThreadDispatch, (void*)this);
}

SerialReader::~SerialReader()
{
  //SDL_DestroyMutex(m_pMutex);
  //m_pSerialStream->Close();
}

int SerialReader::ThreadDispatch(void *pClass)
{
  ((SerialReader*)pClass)->ThreadMain();
  return(0);
}

void SerialReader::ThreadMain()
{
  while(!g_bQuit)
  {
   // SDL_LockMutex(m_pMutex);
    //m_bActive = (cNext == m_cInput);
    m_pSerialStream->get(cNext);
   //std::cout << "-" << cNext;
   // SDL_UnlockMutex(m_pMutex);

    SDL_Delay(1);
  }
}

bool SerialReader::IsActive(std::string m_input)
{
  bool ret;

 // SDL_LockMutex(m_pMutex);
 // ret = m_bActive;
  ret = (cNext == m_input[0]);
  cNext = 0;
 // std::cout << "Cnext: " << cNext << " m_input: " << m_input[0] << std::endl;
 //SDL_UnlockMutex(m_pMutex);

  return ret;
}

