#include "Texture2D.h"
#include <SDL_image.h>
#include <iostream>
#include <string>


Texture2D::Texture2D(SDL_Renderer* renderer) {

	mRenderer = renderer;
	mTexture = NULL;
	mHeight = 0;
	mWidth = 0;

}

Texture2D::~Texture2D() {

	Free();
	SDL_RenderClear(mRenderer);
	mRenderer = NULL;

}

void Texture2D::Free() {

	SDL_DestroyTexture(mTexture);
	mTexture = NULL;
	mHeight = 0;
	mWidth = 0;

}

void Texture2D::Render(Vector2D newPosition, SDL_RendererFlip flip, double angle){

	//SDL_RenderClear(mRenderer);

	//SDL_SetRenderDrawColor(mRenderer, 0x00, 0x00, 0x00, 0x00);

	SDL_Rect renderLocation = { newPosition.x,newPosition.y,mWidth,mHeight };

	SDL_RenderCopyEx(mRenderer, mTexture, NULL, &renderLocation, angle, NULL, flip);

	//SDL_RenderPresent(mRenderer);


}
void Texture2D::Render(SDL_Rect srcRect, SDL_Rect destRect, SDL_RendererFlip flip, double angle) {

	//SDL_RenderClear(mRenderer);

	//SDL_SetRenderDrawColor(mRenderer, 0x00, 0x00, 0x00, 0x00);

	SDL_RenderCopyEx(mRenderer, mTexture, &srcRect, &destRect, angle, NULL, flip);

	//SDL_RenderPresent(mRenderer);


}

bool Texture2D::LoadFromFile(string path) {



	SDL_Surface* pSurface = IMG_Load(path.c_str());

	if (pSurface != NULL) {

		mWidth = pSurface->w;
		mHeight = pSurface->h;


		mTexture = SDL_CreateTextureFromSurface(mRenderer, pSurface);

		if (mTexture == NULL) {
			cout << "failed to create texture from surface. ERROR: " << SDL_GetError() << endl;
		}

		SDL_FreeSurface(pSurface);
		return mTexture;

	}
	else {
		cout << " failed to create texture from surface. ERROR: " << IMG_GetError() << endl;
	}

	SDL_SetColorKey(pSurface, SDL_TRUE, SDL_MapRGB(pSurface->format, 0, 0xFF, 0xFF));
	return mTexture != NULL;

}

