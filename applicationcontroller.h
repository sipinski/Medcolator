/*
 *  applicationcontroller.h
 *  Instructograph
 *
 *  Created by Felix Jodoin on 12-04-15.
 */

#pragma once
#include "SDL/SDL.h"
#include "ifilesystemutility.h"
#include "filesystemutilityposix.h"
#include "ifilesystemutilityfactory.h"
#include "ivideoutility.h"
#include "sdlmanager.h"
#include "configcontroller.h"
#include "behaviour.h"
#include "serialreader.h"

#include <vector>
#include <string>

extern bool g_bQuit;

class ApplicationController {
public:
	ApplicationController();
	~ApplicationController();
	
	void Run();
	
private:
	void FillAllowedExtensions(std::vector<std::string>& vecAllowedExtensions);
	
	IFilesystemUtilityFactory *m_pFilesystemUtilityFactory;
	IVideoUtility *m_pVideoUtility;
    ConfigController *m_pConfigController;

	SDL_Surface *m_pScreen;
	SDLManager *m_pSDLManager;
	int m_iScreenWidth;
	int m_iScreenHeight;
  std::vector<Behaviour*> m_vecBehaviours;
};

