/*
 *  configcontroller.h
 *  Instructograph
 *
 *  Created by Felix Jodoin.
 */

#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include "behaviour.h"
#include "ifilesystemutility.h"
#include "ifilesystemutilityfactory.h"

extern std::string g_strTTY;

/*
    * File format for configuration:
    * [active]
    * path=Videos/Active
    * tty=/dev/tty0
    * idle=0
    * ttyinput=1
    *
    * [inactive]
    * path=Videos/Inactive
    * idle=1
    *
    * [inactive-secondary]
    * path=Videos/Inactive2
    * idle=1
*/

class ConfigController {
public:
    ConfigController(const std::string& strFileName);
    ~ConfigController();

    void Parse(std::vector<Behaviour*>& vecBehaviours, const IFilesystemUtilityFactory *pFilesystemUtilityFactory);

private:
    std::ifstream m_ifFile;
};
