/*
 *  ivideoutility.h
 *  Instructograph
 *
 *  Created by Felix Jodoin on 12-04-14.
 */

#pragma once

#include "SDL/SDL.h"

class IVideoUtility
{
public:
	virtual void RefreshVideo() = 0;
	virtual bool LoadFile(const std::string &strFile) = 0;
	virtual void UnloadFile() = 0;
	virtual int GetWidth() = 0;
	virtual int GetHeight() = 0;
  virtual bool IsPlaying() = 0;
  virtual void Play() = 0;
  virtual void Stop() = 0;
	
};
