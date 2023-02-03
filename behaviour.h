/*
 *  behaviour.h
 *  Instructograph
 *
 *  Created by Felix Jodoin.
 */

#pragma once

#include <string>

#include "ifilesystemutility.h"
#include "ivideoutility.h"
#include "serialreader.h"

extern SerialReader *g_pSerialReader;

class ConfigController;

class Behaviour {
public:
    Behaviour(const std::string& strName, 
              const std::string& strPath, 
              const bool bIdleActive, 
              const std::string& strTTY, 
              const std::string& strTTYInput,
              IFilesystemUtility *pFilesystemUtility);

    ~Behaviour();

    void SetTTY(const std::string& strTTY);
    void SetTTYInput(const std::string& strTTYInput);

    // returns true when no more behaviours should be examined (for example, a
    // movie was just loaded)
    bool Process(IVideoUtility *pVideoUtility);

    friend class ConfigController;    

private:
    std::string m_strName;
    std::string m_strPath;
    bool m_bIdleActive;
    std::string m_strTTY;
    std::string m_strTTYInput;
    IFilesystemUtility *m_pFilesystemUtility;
    SerialReader *m_pSerialReader;
    bool m_bActiveLastTick;
};
