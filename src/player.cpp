#include "headers/player.h"

Player::Player()
{
  if(!Init())
  {
    std::cerr << "Unable to initialize audio and video!" << std::endl;
  }

  m_audioFormat.frequency = 44100;
  m_audioFormat.format = AUDIO_S16SYS;
  m_audioFormat.channels = 1;
  m_audioFormat.buffer = 1024;
  m_channelsNum = 5;
  m_channels = new int[m_channelsNum];
  m_width = 225;
  m_height = 225;
  m_window = NULL;
  m_screen = NULL;
  m_bgImage = NULL;
}

Player::~Player()
{
  Mix_FreeChunk( m_soundRhodes );
  Mix_FreeChunk( m_soundCB );
  Mix_FreeChunk( m_soundBD );
  Mix_FreeChunk( m_soundHH );
  Mix_FreeChunk( m_soundCL );
  delete [] m_channels;
  Mix_CloseAudio();
  SDL_FreeSurface( m_bgImage );
  SDL_FreeSurface( m_screen );
  SDL_DestroyWindow( m_window );
  SDL_Quit();
}

bool Player::Init()
{
  if(SDL_Init( SDL_INIT_AUDIO | SDL_INIT_VIDEO ) < 0)
  {
    std::cout << "Initialization error: " << SDL_GetError() << std::endl;
    return false;
  }
  return true;
}

bool Player::CreateAudioDevice()
{
  if(Mix_OpenAudio(m_audioFormat.frequency, m_audioFormat.format, m_audioFormat.channels, m_audioFormat.buffer) < 0)
  {
    std::cout << "Error with creating an audio device: " << Mix_GetError() << std::endl;
    return false;
  }
  return true;
}

bool Player::CreateWindow(int width, int height)
{
  m_window = SDL_CreateWindow( "SimpleKeyboardPlayer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
  
  if(!m_window)
  {
    std::cout << "Creating window error: " << SDL_GetError() << std::endl;
    return false;
  }
  m_screen = SDL_GetWindowSurface( m_window );

  return true;
}

bool Player::LoadBackground()
{
  m_bgImage = SDL_LoadBMP("../PublicEnemy.bmp");
  
  if(!m_bgImage)
  {
    std::cout << "Error with loading the background image: " << SDL_GetError() << std::endl;
    return false;
  }

  return true;
}

void Player::LoadSounds()
{
  // TO DO better method of giving sound_paths
  m_soundRhodes = Mix_LoadWAV("../sounds/rhodes.wav");
  m_soundCB = Mix_LoadWAV("../sounds/808-cowbell.wav");
  m_soundBD = Mix_LoadWAV("../sounds/808-bassdrum.wav");
  m_soundHH = Mix_LoadWAV("../sounds/808-hihat.wav");
  m_soundCL = Mix_LoadWAV("../sounds/808-clap.wav");
}

void Player::RefreshWindow()
{
  SDL_BlitSurface( m_bgImage, NULL, m_screen, NULL);
  SDL_UpdateWindowSurface( m_window );
}

void Player::LoadChannels()
{
  Mix_AllocateChannels( m_channelsNum );
  for(int i = 0; i < m_channelsNum; i++)
  {
    m_channels[i] = 0;
  }
}

void Player::HandleEvents()
{
  SDL_Event e;
  bool quit = false;
  while(!quit)
  {
    while(SDL_PollEvent( &e ))
    {
      switch( e.type )
      {
        case SDL_QUIT:
          quit = true;
          break;
        case SDL_KEYDOWN:
          switch( e.key.keysym.sym )
          {
            case SDLK_g:
              m_channels[0] = Mix_PlayChannel(0, m_soundRhodes, 0);
              while(!Mix_Playing( m_channels[0] ));
              break;
            case SDLK_h:
              m_channels[1] = Mix_PlayChannel(1, m_soundCB, 0);
              while(!Mix_Playing( m_channels[1] ));
              break;
            case SDLK_j:
              m_channels[2] = Mix_PlayChannel(2, m_soundBD, 0);
              while(!Mix_Playing( m_channels[2] ));
              break;
            case SDLK_k:
              m_channels[3] = Mix_PlayChannel(3, m_soundHH, 0);
              while(!Mix_Playing( m_channels[3] ));
              break;
            case SDLK_l:
              m_channels[4] = Mix_PlayChannel(4, m_soundCL, 0);
              while(!Mix_Playing( m_channels[4] ));
              break;
            case SDLK_q:
              quit = true;
              break;
          }
          break;
      }
    }
  }
}

void Player::Play()
{
  if(!CreateAudioDevice())
  {
    std::cerr << "Unable to create an audio device!" << std::endl;
  }

  LoadSounds();

  if(!CreateWindow(m_width, m_height))
  {
    std::cerr << "Unable to create a window!" << std::endl;
  }

  if(!LoadBackground())
  {
    std::cerr << "Unable to load a background!" << std::endl;
  }

  RefreshWindow();
  LoadChannels();
  HandleEvents();
}
