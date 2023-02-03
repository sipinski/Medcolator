/*
 *  behaviour.cpp
 *  Instructograph
 *
 *  Created by Felix Jodoin.
 */

#include "behaviour.h"
#include <iostream>

Behaviour::Behaviour(const std::string& strName, const std::string& strPath,
    bool bIdleActive, const std::string& strTTY, const std::string& strTTYInput,
    IFilesystemUtility *pFilesystemUtility) :
m_strName(strName),
m_strPath(strPath),
m_bIdleActive(bIdleActive),
m_strTTY(strTTY),
m_strTTYInput(strTTYInput),
m_pFilesystemUtility(pFilesystemUtility),
m_pSerialReader(NULL),
m_bActiveLastTick(false)
{
    if(!m_bIdleActive)
      {
    	// m_pSerialReader = new SerialReader(m_strTTY, m_strTTYInput[0]);
    	m_pSerialReader= g_pSerialReader;

    }
}

Behaviour::~Behaviour()
{
    delete m_pFilesystemUtility;
}

void Behaviour::SetTTY(const std::string& strTTY)
{
    m_strTTY = strTTY;
}

void Behaviour::SetTTYInput(const std::string& strTTYInput)
{
    m_strTTYInput = strTTYInput;
}

bool Behaviour::Process(IVideoUtility *pVideoUtility)
{
    bool bRet = false;
    bool bActive = false;

    if(m_pSerialReader)
    {
        bActive = m_pSerialReader->IsActive(m_strTTYInput);

        if(!bActive)
        {
            m_bActiveLastTick = false;
        }
    }

    if(!pVideoUtility->IsPlaying() || (!m_bActiveLastTick && bActive))
    {
        if(m_bIdleActive || bActive)
        {
            while(!bRet)
            {
                // pick a new video
                std::string fname = m_pFilesystemUtility->PickRandomFile();
                bRet = pVideoUtility->LoadFile(fname);
                if(bRet)
                {
                    pVideoUtility->Play();
                    m_bActiveLastTick = bActive;
                }
            }
        }
    }

    return bRet;
}
