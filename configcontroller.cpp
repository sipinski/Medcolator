/*
 *  configcontroller.cpp
 *  Instructograph
 *
 *  Created by Felix Jodoin.
 */

#include "configcontroller.h"
#include <algorithm>

ConfigController::ConfigController(const std::string& strFileName)
{
    m_ifFile.open(strFileName.c_str(), std::ios::in);
}

ConfigController::~ConfigController()
{
    m_ifFile.close();
}

// This is anything but robust.
void ConfigController::Parse(std::vector<Behaviour*>& vecBehaviours,
                             const IFilesystemUtilityFactory *pFilesystemUtilityFactory)
{
    std::string strKey, strValue;
    std::string strLine;
    char cPeek;
    bool bInsertBehaviour = false;

    // Behaviour properties
    std::string strName, strPath, strTTY, strTTYInput;
    bool bIdleActive;

    while(m_ifFile.good())
    {
        std::getline(m_ifFile, strLine);
        std::istringstream issStream(strLine);
        cPeek = issStream.peek();

        // starting a new section, restart stream and save last behaviour if
        // possible
        if(cPeek == '[' || m_ifFile.eof())
        {
            bInsertBehaviour = true;
        }

        if(bInsertBehaviour)
        {
            bInsertBehaviour = false;
            if(strPath != "" && strName != "")
            {
            	if(strTTY != "" ) {
            		if(!g_pSerialReader)
            		{
            			g_pSerialReader = new SerialReader(strTTY);
            		}
            	}

                Behaviour *behaviour = new Behaviour(strName, strPath,
                                                     bIdleActive, strTTY, strTTYInput,
                                                     pFilesystemUtilityFactory->Spawn(strPath));
                vecBehaviours.push_back(behaviour);
                std::cout << "Added behaviour: [" << strName << "], path=" << strPath
                          << ", bIdleActive=" << bIdleActive << ", strTTY=" << strTTY << ", strTTYInput="
                          << strTTYInput << std::endl;
            }
        }

        if(cPeek == '[')
        {
            issStream.ignore(1, ' ');
            std::getline(issStream, strName, ']');
            strPath = "";
            strTTY = "";
            strTTYInput = "";
            bIdleActive = true;
        }
        else if(cPeek == ' ' || cPeek == 0 || cPeek == '\n')
        {
            continue;
        }
        else
        {
            // accumulate key-value pairs
            std::getline(issStream, strKey, '=');
            std::getline(issStream, strValue);
            std::transform(strKey.begin(), strKey.end(), strKey.begin(), ::tolower);
 
            if(strKey == "tty")
            {
                strTTY = strValue;
                g_strTTY = strValue;
            }
            else if(strKey == "ttyinput")
            {
                strTTYInput = strValue;
            }
            else if(strKey == "path")
            {
                strPath = strValue;
            }
            else if(strKey == "idle")
            {
                bIdleActive = (strValue == "1");            
            }
        }
    } 
}
