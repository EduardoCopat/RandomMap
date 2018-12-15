#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <cmath>
#include <vector>
#include <stdexcept>
#include <iostream>
#include <cstdlib>
#include <ctime>

//Screen dimension constants
const int SCREEN_WIDTH = 400;
const int SCREEN_HEIGHT = 400;

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

int* tileAt(int i, int j);
int* oppositeTileAt(int i, int j);

//The window we'll be rendering to
SDL_Window *gWindow = NULL;

//The window renderer
SDL_Renderer *gRenderer = NULL;
std::vector<std::vector<int> > matrix_a(100);
std::vector<std::vector<int> > matrix_b(100);
char currentMatrix = 'a';

int ZERO = 0;
int MAX_RANDOM_TERRAINS = 4;

void reset(){
    int terrainCount = 0;
    srand(time(0));
    for (int i = 0; i < 100; i++)
        matrix_a[i].resize(100);
    for (int i = 0; i < 100; i++)
        matrix_b[i].resize(100);


    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 100; j++) {
            matrix_a[i][j] = 0;
            matrix_b[i][j] = 0;
        }
    }

    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 100; j++) {
            int terrainChance = rand() % 10000;
            if(terrainChance < 10){
                int terrainType = rand() % 3;
                matrix_a[i][j] = terrainType;
            }
            else{
                matrix_a[i][j] = 0;
                matrix_b[i][j] = 0;
            }

        }
    }

}

bool init() {
    //Initialization flag
    bool success = true;

    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        success = false;
    } else {
        //Set texture filtering to linear
        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
            printf("Warning: Linear texture filtering not enabled!");
        }

        //Create window
        gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                                   SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (gWindow == NULL) {
            printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
            success = false;
        } else {
            //Create renderer for window with vSync
            gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            if (gRenderer == NULL) {
                printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
                success = false;
            } else {
                //Initialize renderer color
                SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0x00);

                //Initialize PNG loading
                int imgFlags = IMG_INIT_PNG;
                if (!(IMG_Init(imgFlags) & imgFlags)) {
                    printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
                    success = false;
                }
            }
        }
    }

    return success;
}

bool loadMedia() {
    //Loading success flag
    bool success = true;

    //Nothing to load
    return success;
}

void close() {
    //Destroy window
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    gRenderer = NULL;

    //Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}

int main(int argc, char *args[]) {

    //Start up SDL and create window
    if (!init()) {
        printf("Failed to initialize!\n");
    } else {
        //Load media
        if (!loadMedia()) {
            printf("Failed to load media!\n");
        } else {
            //Main loop flag
            bool quit = false;

            //Event handler
            SDL_Event e;


            reset();



            //While application is running
            while (!quit) {
                //Handle events on queue
                while (SDL_PollEvent(&e) != 0) {
                    //User requests quit
                    if (e.type == SDL_QUIT) {
                        quit = true;
                    }
                    if(e.type == SDL_KEYDOWN) {
                        reset();
                    }

                }

                //Clear screen
                SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0x00);
                SDL_RenderClear(gRenderer);


                std::vector<int*> neighbors(8);
                for (int i = 0; i < 100; i++) {
                    for (int j = 0; j < 100; j++) {
                        neighbors.clear();
                        int* tile = tileAt(i, j);


                        neighbors.push_back(oppositeTileAt(i, j+1));
                        neighbors.push_back(oppositeTileAt(i, j-1));
                        neighbors.push_back(oppositeTileAt(i+1, j));
                        neighbors.push_back(oppositeTileAt(i+1, j-1));
                        neighbors.push_back(oppositeTileAt(i+1, j+1));
                        neighbors.push_back(oppositeTileAt(i-1, j));
                        neighbors.push_back(oppositeTileAt(i-1, j-1));
                        neighbors.push_back(oppositeTileAt(i-1, j+1));


                        if(*tile == 0)
                            continue;


                        for(int* neighbor : neighbors){
                            if(*neighbor == 0 )
                                *neighbor = *tile;
                        }

                    }
                }

                if(currentMatrix == 'a'){
                    currentMatrix = 'b';
                }
                else{
                    currentMatrix = 'a';
                }

                const int* tile = NULL;
                //Render red filled quad
                for (int i = 0; i < 100; i++) {
                    for (int j = 0; j < 100; j++) {
                        SDL_Rect fillRect = {i * 4, j * 4, 4, 4};
                            tile = &matrix_a.at(i).at(j);


                        switch (*tile) {
                            case 1 :
                                SDL_SetRenderDrawColor(gRenderer, 0x00, 0xFF, 0x00, 0xFF);
                                SDL_RenderFillRect(gRenderer, &fillRect);
                                break;

                            case 2 :
                                SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0xFF, 0xFF);
                                SDL_RenderFillRect(gRenderer, &fillRect);
                                break;
                        }
                    }
                }



                //Update screen
                SDL_RenderPresent(gRenderer);
                SDL_Delay(1);
            }
        }
    }

    //Free resources and close SDL
    close();

    return 0;
}

int* tileAt(int i, int j) {
    try {
        if( currentMatrix == 'a')
            return &matrix_a.at(i).at(j);
        else
            return &matrix_b.at(i).at(j);
    }
    catch (const std::out_of_range &e) {
        return &ZERO;
    }
}

int* oppositeTileAt(int i, int j) {
    try {
        if( currentMatrix == 'b')
            return &matrix_a.at(i).at(j);
        else
            return &matrix_b.at(i).at(j);
    }
    catch (const std::out_of_range &e) {
        return &ZERO;
    }
}

