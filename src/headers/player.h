#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include "audio.h"

class Player
{
private:
  Audio m_audioFormat;
  SDL_Window* m_window;
  SDL_Surface* m_screen, *m_bgImage;
  Mix_Chunk* m_soundRhodes, *m_soundCB, *m_soundBD, *m_soundHH, *m_soundCL;
  int m_channelsNum;
  int* m_channels;
  int m_width, m_height;

  bool Init();
  bool CreateAudioDevice();
  bool CreateWindow(int width, int height);
  bool LoadBackground();
  void LoadSounds();
  void RefreshWindow();
  void LoadChannels();
  void HandleEvents();

public:
  Player();
  ~Player();
  void Play();
};
