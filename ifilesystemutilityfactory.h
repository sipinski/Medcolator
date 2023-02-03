/*
 *  ifilesystemutilityfactory.h
 *  Instructograph
 *
 *  Created by Felix Jodoin on 3-06-2012.
 */

#pragma once

#include "ifilesystemutility.h"

class IFilesystemUtilityFactory
{
public:
    virtual IFilesystemUtility* Spawn(const std::string & strDirectory) const = 0;
};

