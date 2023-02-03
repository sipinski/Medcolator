/*
 *  vlcvideoutility.h
 *  Instructograph
 *
 *  Created by Felix Jodoin.
 */

#pragma once

#include "SDL/SDL.h"
#include <string>
#include <stdint.h>

extern "C" {
};

#include <vlc/vlc.h>

#include "ivideoutility.h"

extern bool g_bQuit;

#define IS_ALLOC_EVENT          (SDL_USEREVENT)
#define IS_REFRESH_EVENT        (SDL_USEREVENT + 1)
#define IS_STOP_PLAYING_EVENT   (SDL_USEREVENT + 2)
#define IS_START_PLAYING_EVENT  (SDL_USEREVENT + 3)

class VLCVideoUtilityManager;

class VLCVideoUtility : public IVideoUtility
{
public:
  ~VLCVideoUtility();
  
  void RefreshVideo();
  bool LoadFile(const std::string &strFile);
  void UnloadFile();
  
  int GetWidth() { return m_iWidth; }
  int GetHeight() { return m_iHeight; }

  inline bool IsPlaying();
  void Play();
  void Stop();
  
  friend class VLCVideoUtilityManager;
  
private:
  VLCVideoUtility(int iScreenWidth, int iScreenHeight, uint32_t uVLCDrawable, libvlc_instance_t *pVLCInstance);

  bool m_bLoading;

  int m_iWidth;
  int m_iHeight;
  int m_iScreenWidth;
  int m_iScreenHeight;
  SDL_Rect m_rScaleDimensions;

  libvlc_instance_t *m_pVLCInstance;
  libvlc_media_player_t *m_pVLCPlayer;
  uint32_t m_uVLCDrawable;
};
