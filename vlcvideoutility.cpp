/*
 *  vlcvideoutility.cpp
 *  Instructograph
 *
 *  Created by Felix Jodoin.
 */

#include "vlcvideoutility.h"
#include "sdlmanager.h"

#include <vlc/vlc.h>

#define MAX(A, B) (A > B) ? A : B

VLCVideoUtility::VLCVideoUtility(int iScreenWidth, int iScreenHeight, 
                                 uint32_t uVLCDrawable, libvlc_instance_t *pVLCInstance) :
m_iWidth(0),
m_iHeight(0),
m_bLoading(false),
m_iScreenWidth(iScreenWidth),
m_iScreenHeight(iScreenHeight),
m_pVLCInstance(pVLCInstance),
m_rScaleDimensions(),
m_pVLCPlayer(NULL),
m_uVLCDrawable(uVLCDrawable)
{
}

VLCVideoUtility::~VLCVideoUtility()
{
  UnloadFile();
}

void VLCVideoUtility::UnloadFile()
{
  if(m_pVLCPlayer)
  {
    libvlc_media_player_stop(m_pVLCPlayer);
    libvlc_media_player_release(m_pVLCPlayer);
  }
}

bool VLCVideoUtility::LoadFile(const std::string &strFile)
{
  if(m_pVLCPlayer)
  {
    UnloadFile();
  }
  
  libvlc_media_t *pMedia = libvlc_media_new_path(m_pVLCInstance, strFile.c_str());
  m_pVLCPlayer = libvlc_media_player_new_from_media(pMedia);
  libvlc_media_release(pMedia);

  libvlc_media_player_set_xwindow(m_pVLCPlayer, m_uVLCDrawable);

  SDLManager::GetInstance()->PushEvent(IS_START_PLAYING_EVENT, NULL);

  return true;
}

bool VLCVideoUtility::IsPlaying()
{
  bool ret = false;

  if(m_pVLCPlayer)
  {
    ret = libvlc_media_player_is_playing(m_pVLCPlayer);
    if(ret)
    {
      m_bLoading = false;
    }
  }

  return ret || m_bLoading;
}

void VLCVideoUtility::Play()
{
  m_bLoading = true;

  if(m_pVLCPlayer)
  {
    libvlc_audio_set_mute(m_pVLCPlayer, false);
    libvlc_audio_set_volume(m_pVLCPlayer, 100);
    libvlc_media_player_play(m_pVLCPlayer);
  }
}

void VLCVideoUtility::Stop()
{
  if(m_pVLCPlayer)
  {
    libvlc_media_player_stop(m_pVLCPlayer);
  }

  m_bLoading = false;
}

void VLCVideoUtility::RefreshVideo()
{
}