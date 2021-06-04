#include "fx.hpp"
#include <iostream>

using namespace std;

void FX::initialize()
{
    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 ) {
        printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
    }
}

void FX::load() //Loading FX audio files from music folder
{
    jump = Mix_LoadWAV( ".\\music\\jump.wav" );
    if( jump == NULL ) {
        printf( "Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
    }
    touch = Mix_LoadWAV( ".\\music\\touch.wav" );
    if( touch == NULL ) {
        printf( "Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
    }
    stomp = Mix_LoadWAV( ".\\music\\stomp.wav" );
    if( stomp == NULL ) {
        printf( "Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
    }    
    coin = Mix_LoadWAV( ".\\music\\coin.mp3" );
    if( coin == NULL ) {
        printf( "Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
    }    
}

void FX::destroy() //Freeing FX audio files
{
    Mix_FreeChunk( jump);
    Mix_FreeChunk( touch );
    Mix_FreeChunk( stomp );
    Mix_FreeChunk( coin );
    jump = NULL;
    stomp = NULL;
    touch = NULL;
    coin = NULL;
}

void FX::effect(char choice) // Play a sound (j for jump, t for touch enemy, s for stomp enemy, d for mario dying)
{
    if (choice == 'j') {
        Mix_PlayChannel( -1, jump, 0 ); 
    }
    if (choice == 't') {
        Mix_PlayChannel( -1, touch, 0 );
    }
    if (choice == 's') {
        Mix_PlayChannel( -1, stomp, 0 );
    }
    if (choice == 'c') {
        Mix_PlayChannel( -1, coin, 0 );
    }
}


