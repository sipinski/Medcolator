/*
 *  filesystemutilityposixfactory.cpp
 *  Instructograph
 *
 *  Created by Felix Jodoin on 3-06-2012.
 */


#include "filesystemutilityposixfactory.h"

#include <vector>
#include <string>

FilesystemUtilityPosixFactory::FilesystemUtilityPosixFactory(const std::vector<std::string>& vecFilters)
{
    m_vecFilters = vecFilters;
}

FilesystemUtilityPosixFactory::~FilesystemUtilityPosixFactory()
{

}

IFilesystemUtility* FilesystemUtilityPosixFactory::Spawn(const std::string & strDirectory) const
{
    return new FilesystemUtilityPosix(m_vecFilters, strDirectory);
}
