/*
 *  sdlmanager.h
 *  Instructograph
 *
 *  Created by Felix Jodoin on 12-04-15.
 */

#pragma once

#include "SDL/SDL.h"

class SDLManager {
public:
	
	~SDLManager();
	
	static SDLManager* CreateInstance();
	static SDLManager* GetInstance() { return m_pSDLManager; }
	static void DestroyInstance();

  void PushEvent(Uint8 uType, void *pExtra);

private:
	SDLManager();
	
	static SDLManager *m_pSDLManager;
};
