#include <SDL2/SDL.h>

int main( int argc, char** argv )
{
	const unsigned int texWidth = 1024;
	const unsigned int texHeight = 1024;
	Uint8 *pixels = malloc(sizeof(*(pixels)) * texWidth * texHeight * 4);

	SDL_Init(SDL_INIT_EVERYTHING);
	atexit(SDL_Quit);
	SDL_Window* window = SDL_CreateWindow("SDL2", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 600, 600, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, texWidth, texHeight);

	SDL_Event event;
	int running = 1;
	while(running)
	{
		//Check for keyboard event ESC key down
		while(SDL_PollEvent(&event))
			if((SDL_QUIT == event.type) || (SDL_KEYDOWN == event.type && SDL_SCANCODE_ESCAPE == event.key.keysym.scancode))
				running = 0;

		// splat down some random pixels
		for( unsigned int i = 0; i < 1000; i++ )
		{
			const unsigned int x = rand() % texWidth;
			const unsigned int y = rand() % texHeight;

			const unsigned int offset = ( texWidth * 4 * y ) + x * 4;
			pixels[ offset + 0 ] = rand() % 256;        // b
			pixels[ offset + 1 ] = rand() % 256;        // g
			pixels[ offset + 2 ] = rand() % 256;        // r
			pixels[ offset + 3 ] = SDL_ALPHA_OPAQUE;    // a
		}

		// Clear window
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
		SDL_RenderClear(renderer);

		//Update texture anbd window
		SDL_UpdateTexture(texture, NULL, &pixels[0], texWidth * 4);
		SDL_RenderCopy(renderer, texture, NULL, NULL );
		SDL_RenderPresent(renderer);
	}
	SDL_DestroyRenderer( renderer );
	SDL_DestroyWindow( window );
	SDL_Quit();
}
