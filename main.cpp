#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>

bool init();

int main()
{
  int audioFreq = 44100;
  Uint16 audioFormat = AUDIO_S16SYS;
  int audioChannels = 1;
  int audioBuffer = 2048;

  if(!init())
  {
    return -1;
  }

  if(Mix_OpenAudio(audioFreq, audioFormat, audioChannels, audioBuffer) < 0)
  {
    std::cout << "Error with audio device: " << Mix_GetError() << std::endl;
    SDL_Quit();
    return -1;
  }
  
  //LOAD Sounds
  Mix_Chunk* soundCB = NULL;
  soundCB = Mix_LoadWAV("../sounds/808-cowbell.wav");

  Mix_Chunk* soundCL = NULL;
  soundCL = Mix_LoadWAV("../sounds/808-clap.wav");
  
  Mix_Chunk* soundHH = NULL;
  soundHH = Mix_LoadWAV("../sounds/808-hihat.wav");

  Mix_Chunk* soundBD = NULL;
  soundBD = Mix_LoadWAV("../sounds/808-bassdrum.wav");

  Mix_Chunk* soundRhodes = NULL;
  soundRhodes = Mix_LoadWAV("../sounds/rhodes.wav");
  ///////////////////////////

  SDL_Window* window = NULL;
  SDL_Surface* screen = NULL;
  window = SDL_CreateWindow("Audio Playback", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 225, 225, SDL_WINDOW_SHOWN);
  if(window)
  {
    screen = SDL_GetWindowSurface( window );
  }

  Mix_AllocateChannels(5);
  int channel1 = 0, channel2 = 0, channel3 = 0, channel4 = 0, channel5 = 0;
 
  SDL_Surface* backgroundImage = NULL;
  backgroundImage = SDL_LoadBMP("../PublicEnemy.bmp");

  SDL_BlitSurface( backgroundImage, NULL, screen, NULL);

  SDL_UpdateWindowSurface( window );
  
  SDL_Event e;
  bool quit = false;
  while(!quit)
  {
    while(SDL_PollEvent( &e ))
    {
      switch(e.type)
      {
        case SDL_QUIT:
          quit = true;
          break;
        case SDL_KEYDOWN:
          switch(e.key.keysym.sym)
          {
            case SDLK_h:
              channel1 = Mix_PlayChannel(0, soundCB, 0);
              while(!Mix_Playing( channel1 ));
              break;
            case SDLK_j:
              channel2 = Mix_PlayChannel(1, soundBD, 0);
              while(!Mix_Playing( channel2 ));
              break;
            case SDLK_k:
              channel3 = Mix_PlayChannel(2, soundHH, 0);
              while(!Mix_Playing( channel3 ));
              break;
            case SDLK_l:
              channel4 = Mix_PlayChannel(3, soundCL, 0);
              while(!Mix_Playing( channel4 ));
              break;
            case SDLK_g:
              channel5 = Mix_PlayChannel(4, soundRhodes, 0);
              while(!Mix_Playing( channel5 ));
              break;
            case SDLK_q:
              quit = true;
              break;
          }
        break;
      }
    }
  }  
  
  Mix_FreeChunk( soundBD );
  Mix_FreeChunk( soundHH );
  Mix_FreeChunk( soundCL );
  Mix_FreeChunk( soundCB );
  Mix_CloseAudio();
  SDL_FreeSurface( backgroundImage );
  SDL_FreeSurface( screen );
  SDL_DestroyWindow( window );
  SDL_Quit();
  return 0;
}

bool init()
{
  if(SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO) < 0)
  {
    std::cout << "Initialization error: " << SDL_GetError() << std::endl;
    return false;
  }

  return true;
}
