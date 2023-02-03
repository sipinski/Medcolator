/*
 *  applicationcontroller.cpp
 *  Instructograph
 *
 *  Created by Felix Jodoin on 12-04-15.
 */

#include "applicationcontroller.h"
#include "filesystemutilityposixfactory.h"
#include "vlcvideoutilitymanager.h"

#include <vector>
#include <string>
#include <iostream>

#define CONFIG_FILENAME "config.ini"

bool g_bQuit = false;
std::string g_strTTY = "";
SerialReader *g_pSerialReader;

ApplicationController::ApplicationController() :
m_pFilesystemUtilityFactory(NULL),
m_pVideoUtility(NULL),
m_pConfigController(NULL),
m_pScreen(NULL),
m_pSDLManager(NULL),
m_iScreenWidth(0),
m_iScreenHeight(0),
m_vecBehaviours()
{
	// Prepare SDL
	m_pSDLManager = SDLManager::CreateInstance();
	
	m_pScreen = SDL_SetVideoMode(0,0,0,SDL_HWSURFACE|SDL_ANYFORMAT/*|SDL_FULLSCREEN*/);
	m_iScreenWidth = m_pScreen->w;
	m_iScreenHeight = m_pScreen->h;
	
	if (!m_pScreen) {
		SDL_Quit();
		exit(2);
	}
	//g_pSerialReader = new SerialReader("/dev/ttyS0");

    m_pConfigController = new ConfigController(CONFIG_FILENAME);

	std::vector<std::string> extensions;
	FillAllowedExtensions(extensions);
    
  m_pFilesystemUtilityFactory = new FilesystemUtilityPosixFactory(extensions);

  m_pConfigController->Parse(m_vecBehaviours, m_pFilesystemUtilityFactory);




	m_pVideoUtility = VLCVideoUtilityManager::CreateUtility(m_iScreenWidth, m_iScreenHeight);


}

ApplicationController::~ApplicationController()
{
  delete m_pConfigController;
	delete m_pVideoUtility;
	delete m_pFilesystemUtilityFactory;
	//delete m_pSDLManager;
}

void ApplicationController::FillAllowedExtensions(std::vector<std::string>& vecAllowedExtensions)
{
	// TODO - use config
	vecAllowedExtensions.push_back("mkv");
	vecAllowedExtensions.push_back("fla");
	vecAllowedExtensions.push_back("mpg");
	vecAllowedExtensions.push_back("avi");
	vecAllowedExtensions.push_back("mp4");
}

void ApplicationController::Run()
{
	SDL_Event event;

	while ( !g_bQuit ) {
	  for(std::vector<Behaviour*>::iterator it = m_vecBehaviours.begin(); it != m_vecBehaviours.end(); it++)
    {
    	if((*it)->Process(m_pVideoUtility))
    	{
    		break;
    	}
    }	

    // this thread waits until there is an event, and then PollEvent takes care of all queued events
    //SDL_WaitEvent(NULL);
		while(SDL_PollEvent(&event))
		{
			switch (event.type) {
				case IS_STOP_PLAYING_EVENT:
					break;
				
				case IS_START_PLAYING_EVENT:
					break;

				case IS_REFRESH_EVENT:
					m_pVideoUtility->RefreshVideo();
					break;

				case SDL_KEYDOWN:
				case SDL_QUIT:
					printf("Quitting..\n");
					m_pVideoUtility->Stop();
					g_bQuit = true;
					break;
				default:
					break;
			}
		}

		SDL_Delay(1); // no need for this thread to hog 100% of CPU
	}

	SDL_Quit();
}

