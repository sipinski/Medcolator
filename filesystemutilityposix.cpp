/*
 *  filesystemutilityposix.cpp
 *  Instructograph
 *
 *  Created by Felix Jodoin on 12-04-14.
 */

#include "filesystemutilityposix.h"

#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <errno.h>
#include <string.h>

FilesystemUtilityPosix::FilesystemUtilityPosix(const std::vector<std::string> & vecFilters, const std::string & strDirectory)
{
	m_vecFilters = vecFilters;
  m_strDirectory = strDirectory;

  PrepareList();
}

FilesystemUtilityPosix::~FilesystemUtilityPosix()
{

}

void FilesystemUtilityPosix::PrepareList()
{
	DIR *dir;
	struct dirent *entry;

	dir = opendir(m_strDirectory.c_str());
	
	if (dir == NULL)
	{
		// This error commonly occurs when PrepareList() is called over and over, when a valid file can't be found in the list
		// This means that the files had filenames that looked okay but ffmpeg would not load them
		fprintf(stderr, "Couldn't open directory for read: (%d) %s for %s\n", errno, strerror(errno), m_strDirectory.c_str());
		exit(2);
	}

	while( (entry = readdir(dir)) != NULL)
	{
		std::string strEntry(entry->d_name);
		
		if(PassesFilter(strEntry))
		{
			m_vecAvailableFiles.push_back(m_strDirectory + "/" + strEntry);
    }
	}

	if(m_vecAvailableFiles.size() == 0)
	{
		fprintf(stderr, "No suitable video files in directory: %s. TODO: Make this nonfatal\n", m_strDirectory.c_str());
		exit(2);
	}

	std::random_shuffle(m_vecAvailableFiles.begin(), m_vecAvailableFiles.end());

	closedir(dir);
}

std::string FilesystemUtilityPosix::PickRandomFile()
{
	if(m_vecAvailableFiles.size() == 0)
	{
		PrepareList(); // regenerate the list and start again
	}

	// right now PrepareList exits if there weren't any suitable files, so this call is "safe"
	std::string randFile = m_vecAvailableFiles.back();
	m_vecAvailableFiles.pop_back();

	return randFile;
}

unsigned int FilesystemUtilityPosix::FileCount()
{
	unsigned int uRet = 0;
	DIR *dir;
	struct dirent *entry;
	
	dir = opendir(m_strDirectory.c_str());
	
	while( (entry = readdir(dir)) != NULL)
	{
		std::string strEntry(entry->d_name);
		
		if(PassesFilter(strEntry)) 
		{
			uRet++;
    }
	}
	
	closedir(dir);
	
	return uRet;
}

bool FilesystemUtilityPosix::PassesFilter(const std::string & strFile)
{
	bool bRet = false;
	
	// todo: replace with auto when compiling only on gcc-4.4
	for(std::vector<std::string>::iterator it = m_vecFilters.begin(); it != m_vecFilters.end(); it++)
	{
		std::string strFileLower = strFile;
		std::transform(strFileLower.begin(), strFileLower.end(), strFileLower.begin(), ::tolower);
		size_t pos = strFileLower.rfind(*it);
    
    if (pos!=std::string::npos && pos==strFileLower.length()-(*it).length()) 
    {
			bRet = true;
			break;
    }
	}
	
	return bRet;
}
