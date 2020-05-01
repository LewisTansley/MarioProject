#include <Windows.h>
#include "HUD.h"
#include <SDL.h>
#include <iostream>
#include <string>

void renderText(int score) {

	/*std::string score_text = "score: " + std::to_string(score);
	SDL_Color textColor = { 255, 255, 255, 0 };
	SDL_Surface* textSurface = TTF_RenderText_Solid(font, score_text.c_str(), textColor);
	SDL_Texture* text = SDL_CreateTextureFromSurface(renderer, textSurface);
	int text_width = textSurface->w;
	int text_height = textSurface->h;
	SDL_FreeSurface(textSurface);
	SDL_Rect renderQuad = { 20, win_height - 30, text_width, text_height };
	SDL_RenderCopy(renderer, text, NULL, &renderQuad);
	SDL_DestroyTexture(text);*/

}
