/*
 *  sdlmanager.cpp
 *  Instructograph
 *
 *  Created by Felix Jodoin on 12-04-15.
 */

#include "sdlmanager.h"

SDLManager* SDLManager::m_pSDLManager = NULL;

SDLManager::SDLManager()
{
	if ( SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) < 0 ) {
		fprintf(stderr, "Couldn't initialize SDL: %s\n",
				SDL_GetError());
		exit(1);
	}
}

SDLManager::~SDLManager()
{
	SDL_Quit();
}

SDLManager* SDLManager::CreateInstance()
{
	m_pSDLManager = new SDLManager();
	return m_pSDLManager;
}

void SDLManager::DestroyInstance()
{
	if(m_pSDLManager)
	{
		delete m_pSDLManager;
		m_pSDLManager = NULL;
	}
}

void SDLManager::PushEvent(Uint8 uType, void *pExtra)
{
	SDL_Event event;
	event.type = uType;
	event.user.data1 = pExtra;
	SDL_PushEvent(&event);
}
