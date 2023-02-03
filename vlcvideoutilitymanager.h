/*
 *  vlcvideoutilitymanager.h
 *  Instructograph
 *
 *  Created by Felix Jodoin.
 */

#pragma once

#include "vlcvideoutility.h"
#include "SDL/SDL.h"

extern bool g_bQuit;

class VLCVideoUtilityManager {
public:
  static VLCVideoUtility* CreateUtility(int iScreenWidth, int iScreenHeight);
  static void DestroyUtility();
  
  static VLCVideoUtility* GetUtility();
  
private:
  VLCVideoUtilityManager() { };
  
  static VLCVideoUtility *m_pUtility;
  static libvlc_instance_t *m_pVLCInstance;
};