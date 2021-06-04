#include "game.hpp"

bool Game::init()
{
	//Initialization flag
	bool success = true;
	//Initialize SDL
	if (TTF_Init() < 0) {
		printf("SDL could not initialize sound: %s\n", SDL_GetError());
		success = false;
	}
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		gWindow = SDL_CreateWindow( "Mario", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
			if( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}
				if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
				{
					printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
					success = false;
				}
			}
		}
	}

	return success;
}

bool Game::loadMedia()

{
	//Loading success flag
	bool success = true;
	//Load Mario texture
	mario_img = loadTexture(".\\images\\mario_small.png");
	//Load textures for blocks, enemies and other items
	assets[0] = loadTexture(".\\images\\brick.png");
	assets[1] = loadTexture(".\\images\\itemblock.png");
	assets[2] = loadTexture(".\\images\\other_sprites.gif");
	assets[3] = loadTexture(".\\images\\coin.png");
	assets[4] = loadTexture(".\\images\\heart.png");
	//Load background textures for start screen, win screen, lose screen and in-game backgrounds
    gTextures[0] = loadTexture(".\\images\\day_bg.png");
	gTextures[1] = loadTexture(".\\images\\night_bg.png");
	gTextures[2] = loadTexture(".\\images\\castle_bg.png");
	startTexture = loadTexture(".\\images\\startscreen.png");
	endTexture = loadTexture(".\\images\\endscreen.png");
	wonTexture = loadTexture(".\\images\\winscreen.png");
	if(assets[0]==NULL || assets[1]==NULL || assets[2]==NULL || assets[3]==NULL || assets[4]==NULL || gTextures[0]==NULL || gTextures[1]==NULL || gTextures[2]==NULL || startTexture==NULL || mario_img==NULL)
    {
        printf("Unable to run due to error: %s\n",SDL_GetError());
        success =false;
    }
	
	bgMusic = Mix_LoadMUS(".\\music\\mario_sound.mp3");

	if(bgMusic == NULL){
		printf("Unable to load music: %s \n", Mix_GetError());
		success = false;
	}

	die = Mix_LoadWAV( ".\\music\\die.wav" );

    if( die == NULL ) {
        printf( "Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
    }

	return success;
}

void Game::close()
{
	//Free loaded images
	SDL_DestroyTexture(mario_img);
	SDL_DestroyTexture(startTexture);
	mario_img=NULL; 
	startTexture=NULL;
	for (int i = 0; i<5; i++) {
		SDL_DestroyTexture(assets[i]);
		assets[i]=NULL;
	}
	for (int i = 0; i<3; i++) {
		SDL_DestroyTexture(gTextures[i]);
		gTextures[i] = NULL;
	}
	
	//Destroy window
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	Mix_FreeMusic(bgMusic);
	Mix_FreeChunk( die );
	bgMusic = NULL;
	die = NULL;

	//Free Mario and Level object
	delete level;
	Mario::resetMario();
	level = nullptr;
	mario = nullptr;

	//Quit SDL subsystems
	IMG_Quit();
	Mix_Quit();
	SDL_Quit();
}

SDL_Texture* Game::loadTexture( std::string path )
{
	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
	else
	{
		//Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
		if( newTexture == NULL )
		{
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}

		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}

	return newTexture;
}

void Game::drawAllObjects(){
	level->display(gRenderer); //Draw level
	mario->draw(); //Draw mario
}

void Game::run( )
{
	SDL_RenderClear( gRenderer );
	//Main loop flag
	bool quit = false;
	//Event handler
	SDL_Event e;
	//While application is running
	while( !quit )
	{
		//Handle events on queue
		while( SDL_PollEvent( &e ) != 0 )
		{
			//User requests quit
			if( e.type == SDL_QUIT )
			{
				quit = true;
			}
			if(e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT){ // Check left-mouse-button pressed
				if (gameState == "start") {	
					int xMouse, yMouse;
					SDL_GetMouseState(&xMouse,&yMouse);
					if ((xMouse>=344 && xMouse<=344+112) && (yMouse>=204 && yMouse<=204+36)){ //Check start button clicked
						gameState = "newgame";
					}
					else if ((xMouse>=344 && xMouse<=344+112) && (yMouse>=244 && yMouse<=244+36)){ //Check load button clicked
						gameState = "loadgame";
					}
				}
				else if(gameState == "endwaiting" || gameState == "wonwaiting") { //Check if game ended and waiting for restart
					gameState = "start";
				}
			}
		}


		if( Mix_PlayingMusic() == 0 )
		{
			//Play the music
			Mix_PlayMusic( bgMusic, 2 );
		}

		SDL_RenderClear(gRenderer); //removes everything from renderer
		
		if (gameState == "start") {
			SDL_RenderCopy(gRenderer, startTexture, NULL, NULL); //Display start screen
		}
		if (gameState == "newgame" || gameState == "loadgame"){
			if (gameState == "newgame") {level = new Level(gRenderer, assets, gTextures, 1);} //Load new game
			if (gameState == "loadgame") { //Load level with data from savegame.txt file
				ifstream saveFile(".\\levels\\savegame.txt");
				string data; 
				getline(saveFile, data);
				int loadedLevel = stoi(data);
				getline(saveFile, data);
				int loadedLives = stoi(data);
				getline(saveFile, data);
				int loadedCoins = stoi(data);
				level = new Level(gRenderer, assets, gTextures, loadedLevel, loadedLives, loadedCoins);
			}
			mario = Mario::getMario(gRenderer, mario_img, level); //Create mario with reference to level
			gameState = "playing"; //Now game has started
		}
		if (gameState == "playing") {
			drawAllObjects();	//draws all objects
			if (level->isMarioDead()) { //Game ends if mario dies (lives = 0)
				gameState = "end";
				Mix_PlayChannel( -1, die, 0 );
			}
			if (level->hasGameWon()) { //Win if mario reaches end
				gameState = "won";
			}
		}
		if (gameState=="end" || gameState=="won") { //Free mario and level once game won or ended, and wait for player to click on screen with relevant backgrounf
			delete level;
			Mario::resetMario();
			level = nullptr;
			mario = nullptr;
			if (gameState=="end") gameState = "endwaiting";
			if (gameState=="won") gameState = "wonwaiting";
		}
		if (gameState == "endwaiting") {
			SDL_RenderCopy(gRenderer, endTexture, NULL, NULL); //display YOU LOST background
		}
		if (gameState == "wonwaiting") {
			SDL_RenderCopy(gRenderer, wonTexture, NULL, NULL); //display YOU WON background
		}
		SDL_RenderPresent(gRenderer); //displays the updated renderer
		SDL_Delay(10);	//causes sdl engine to delay for specified miliseconds 
	}		
}
