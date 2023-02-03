/*
 *  vlcvideoutilitymanager.cpp
 *  Instructograph
 *
 *  Created by Felix Jodoin.
 */

#include "vlcvideoutilitymanager.h"

#include <vlc/vlc.h>
#include "SDL/SDL.h"
#include "SDL/SDL_syswm.h"

#include <vector>

libvlc_instance_t* VLCVideoUtilityManager::m_pVLCInstance = NULL;
VLCVideoUtility* VLCVideoUtilityManager::m_pUtility = NULL;

VLCVideoUtility* VLCVideoUtilityManager::CreateUtility(int iScreenWidth, int iScreenHeight)
{
  if(!m_pUtility)
  {
    // Get XWindows XID
    SDL_SysWMinfo xwin;
    SDL_VERSION(&xwin.version);
    SDL_GetWMInfo(&xwin);
    uint32_t uDrawable = xwin.info.x11.window;

    // Perform vlc initialization
    std::vector<const char*> vecVLCArgs;
    vecVLCArgs.push_back("--no-osd");
    VLCVideoUtilityManager::m_pVLCInstance = libvlc_new(vecVLCArgs.size(), &vecVLCArgs[0]);

    // Create utility
    VLCVideoUtilityManager::m_pUtility = new VLCVideoUtility(iScreenWidth, iScreenHeight, uDrawable, m_pVLCInstance);
  }
  
  return m_pUtility;
}

void VLCVideoUtilityManager::DestroyUtility()
{
  if(m_pUtility)
  {
    delete m_pUtility;
    m_pUtility = NULL;
  }

  libvlc_release(m_pVLCInstance);
}

VLCVideoUtility* VLCVideoUtilityManager::GetUtility()
{
  return m_pUtility;
}
