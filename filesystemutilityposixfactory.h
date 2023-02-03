/*
 *  filesystemutilityposixfactory.h
 *  Instructograph
 *
 *  Created by Felix Jodoin on 3-06-2012.
 */

#pragma once

#include "ifilesystemutilityfactory.h"
#include "filesystemutilityposix.h"

#include <vector>
#include <string>

class FilesystemUtilityPosixFactory : public IFilesystemUtilityFactory
{
public:
    FilesystemUtilityPosixFactory(const std::vector<std::string>& vecFilters);
    virtual ~FilesystemUtilityPosixFactory();
    virtual IFilesystemUtility* Spawn(const std::string & strDirectory) const;

private:
    std::vector<std::string> m_vecFilters;
};

