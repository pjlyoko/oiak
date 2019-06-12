
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "SDL.h"
#include "SDL_image.h"

#include <mmintrin.h>

void Filter(unsigned char * in, unsigned char * out, int width, int height) {
	int x, y;
	char matrix[8] = {-1, 1, /*0, */-1, 0, 1, 0, 1, 1};
	__m64 a, b, wynik;
	for(x = 0; x < width * height; ++x) {
		out[x] = in[x];
	}
	for(y = 1; y < height - 2; ++y) {
		for(x = 1; x < width - 2; ++x) {
			int _row = y * width + x;
			char values1[8] = { 0x0, in[_row], 0x0, in[_row + 1], /*in[_row + 2],*/
					    0x0, in[_row + width], 0x0, in[_row + width + 1] };
			char values2[8] = { 0x0, in[_row + width + 2], 0x0, in[_row + width + width],
					    0x0, in[_row + width + width +2], 0x0, in[_row + width + width + 2] };
			asm(
				"movq %2, %%mm0;"
				"movq %4, %%mm1;"
				"pmullw %%mm0, %%mm1;"
				"movq %%mm0, %0;"
				"movq %3, %%mm0;"
				"movq %4, %%mm1;"
				"pmullw %%mm0, %%mm1;"
				"movq %%mm0, %1;"
				"emms;"
				: "=r" (values1), "=r" (values2)
				: "r" (values1), "r" (values2), "r" (matrix)
			);
			/*__m64 *av, *bv, *cv;
			av = (__m64*) values1;
			bv = (__m64*) values1;
			cv = (__m64*) matrix;
			
			av = _mm_mul_pi8(bv, cv);*/
			
			int sum = values1[0] + values1[1] + values1[2] + values1[3] 
				  + values2[0] + values2[1] + values2[2] + values2[3];
			sum += 3 * 255;
			sum /= 6;
			out[_row + width + 1] = sum;
		}
	}
}


SDL_Surface* Load_image(char *file_name)
{
		/* Open the image file */
		SDL_Surface* tmp = IMG_Load(file_name);
		if ( tmp == NULL ) {
			fprintf(stderr, "Couldn't load %s: %s\n",
			        file_name, SDL_GetError());
				exit(0);
		}
		return tmp;	
}

void Paint(SDL_Surface* image, SDL_Surface* screen)
{
		SDL_BlitSurface(image, NULL, screen, NULL);
		SDL_UpdateRect(screen, 0, 0, 0, 0);
};





int main(int argc, char *argv[])
{
	Uint32 flags;
	SDL_Surface *screen, *image;
	int depth, done;
	SDL_Event event;

	/* Check command line usage */
	if ( ! argv[1] ) {
		fprintf(stderr, "Usage: %s <image_file>, (int) size\n", argv[0]);
		return(1);
	}

	if ( ! argv[2] ) {
		fprintf(stderr, "Usage: %s <image_file>, (int) size\n", argv[0]);
		return(1);
	}

	/* Initialize the SDL library */
	if ( SDL_Init(SDL_INIT_VIDEO) < 0 ) {
		fprintf(stderr, "Couldn't initialize SDL: %s\n",SDL_GetError());
		return(255);
	}

	flags = SDL_SWSURFACE;
	image = Load_image( argv[1] );
	printf( "\n\nImage properts:\n" );
	printf( "BitsPerPixel = %i \n", image->format->BitsPerPixel );
	printf( "BytesPerPixel = %i \n", image->format->BytesPerPixel );
	printf( "width %d ,height %d \n\n", image->w, image->h );	

	unsigned nPixels = image->w * image->h ;
	unsigned nBytes = nPixels * image->format->BytesPerPixel ;
	unsigned char * tmpBuf = calloc(nPixels, image->format->BytesPerPixel) ;

	SDL_WM_SetCaption(argv[1], "showimage");

	/* Create a display for the image */
	depth = SDL_VideoModeOK(image->w, image->h, 32, flags);
	/* Use the deepest native mode, except that we emulate 32bpp
	   for viewing non-indexed images on 8bpp screens */
	if ( depth == 0 ) {
		if ( image->format->BytesPerPixel > 1 ) {
			depth = 32;
		} else {
			depth = 8;
		}
	} else
	if ( (image->format->BytesPerPixel > 1) && (depth == 8) ) {
    		depth = 32;
	}
	if(depth == 8)
		flags |= SDL_HWPALETTE;
	screen = SDL_SetVideoMode(image->w, image->h, depth, flags);
	if ( screen == NULL ) {
		fprintf(stderr,"Couldn't set %dx%dx%d video mode: %s\n",
			image->w, image->h, depth, SDL_GetError());
	}

	/* Set the palette, if one exists */
	if ( image->format->palette ) {
		SDL_SetColors(screen, image->format->palette->colors,
	              0, image->format->palette->ncolors);
	}


	/* Display the image */
	Paint(image, screen);

	done = 0;
	int size =atoi( argv[2] );
	printf("Actual size is: %d\n", size);
	while ( ! done ) {
		if ( SDL_PollEvent(&event) ) {
			switch (event.type) {
			    case SDL_KEYUP:
				switch (event.key.keysym.sym) {
				    case SDLK_ESCAPE:
				    case SDLK_TAB:
				    case SDLK_q:
					done = 1;
					break;
				    case SDLK_SPACE:
				    case SDLK_f:
					SDL_LockSurface(image);
					
					printf("Start filtering...  ");
					Filter(image->pixels, tmpBuf, image->w, image->h) ;
					printf("Done.\n");

					memcpy (image->pixels, tmpBuf, nBytes) ;
					SDL_UnlockSurface(image);
					
					printf("Repainting after filtered...  ");
					Paint(image, screen);
					printf("Done.\n");
					
					break;
				    case SDLK_r:
					printf("Reloading image...  ");
					image = Load_image( argv[1] );
					Paint(image,screen);
					printf("Done.\n");
					break;
				    case SDLK_PAGEDOWN:
				    case SDLK_DOWN:
				    case SDLK_KP_MINUS:
					size--;
					if (size==0) size--;
					printf("Actual size is: %d\n", size);
				        break;
				    case SDLK_PAGEUP:
				    case SDLK_UP:
				    case SDLK_KP_PLUS:
					size++;
					if (size==0) size++;
					printf("Actual size is: %d\n", size);
					break;		
				   case SDLK_s:
					printf("Saving surface at nowy.bmp ...");
					SDL_SaveBMP(image, "nowy.bmp" ); 
					printf("Done.\n");
				    default:
					break;
				}
				break;
//			    case  SDL_MOUSEBUTTONDOWN:
//				done = 1;
//				break;
                            case SDL_QUIT:
				done = 1;
				break;
			    default:
				break;
			}
		} else {
			SDL_Delay(10);
		}
	}
	SDL_FreeSurface(image);
	free (tmpBuf) ;
	/* We're done! */
	SDL_Quit();
	return(0);
}

