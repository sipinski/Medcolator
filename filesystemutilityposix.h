/*
 *  filesystemutilityposix.h
 *  Instructograph
 *
 *  Created by Felix Jodoin on 12-04-14.
 */

#pragma once

#include "ifilesystemutility.h"

#include <dirent.h>
#include <map>
#include <set>
#include <string>
#include <vector>

class FilesystemUtilityPosix : public IFilesystemUtility {
public:
	FilesystemUtilityPosix(const std::vector<std::string> & vecFilters, const std::string & strDirectory);
	virtual ~FilesystemUtilityPosix();
	
	virtual std::string PickRandomFile();
	virtual unsigned int FileCount();
	
private:
  void PrepareList();
	bool PassesFilter(const std::string & strFile);

  std::vector<std::string> m_vecAvailableFiles;
	std::vector<std::string> m_vecFilters;
  std::string m_strDirectory;
};
