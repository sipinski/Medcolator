/*
 *  ifilesystemutility.h
 *  Instructograph
 *
 *  Created by Felix Jodoin on 12-04-14.
 */

#pragma once

#include <string>

class IFilesystemUtility {
public:
	virtual std::string PickRandomFile() = 0;
	virtual unsigned int FileCount() = 0;
};
