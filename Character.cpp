#include "Character.h"
#include "Texture2D.h"
#include "Constants.h"

Character::Character(SDL_Renderer* renderer, string imagePath, Vector2D startPosition) {

    mRenderer = renderer;
	mTexture = new Texture2D(mRenderer);
    if (!mTexture->LoadFromFile(imagePath)) {
        cout << "Failed to load character texture!" << endl;
    }

    mPosition = startPosition;

    mMovingLeft = false;
    mMovingRight = false;

}

Character::~Character() {

    delete mTexture;
    mRenderer = NULL;
    mTexture = NULL;

}

 void Character::Render(){
 
     mTexture->Render(Vector2D(), SDL_FLIP_NONE);

 }

 void Character::MoveLeft(float deltaTime) {

     mPosition.x -= 1.0f;

     SetPosition(mPosition);

 }

 void Character::MoveRight(float deltaTime) {

     mPosition.x += 1.0f;

     SetPosition(mPosition);

 }

 void Character::Update(float deltaTime, SDL_Event e) {

     if (mMovingLeft) {
         MoveLeft(deltaTime);
     }
     else if (mMovingRight) {
         MoveRight(deltaTime);
     }

     SDL_PollEvent(&e);

     while (SDL_PollEvent(&e)) {
         switch (e.type) {
             case SDL_KEYDOWN:
                 switch (e.key.keysym.sym) {
                     case SDLK_LEFT:
                         mMovingLeft = true;
                         cout << "left" << endl;
                     break;
                     case SDLK_RIGHT:
                         mMovingRight = true;
                         cout << "right" << endl;
                     break;
                 }
             break;
             case SDL_KEYUP:
                 switch (e.key.keysym.sym) {
                     case SDLK_LEFT:
                         mMovingLeft = false;
                     break;
                     case SDLK_RIGHT:
                         mMovingRight = false;
                     break;
                 }
             break;
         }

     }

 }

 void Character::SetPosition(Vector2D newPosition) {

     mPosition = newPosition;
     
 }

 Vector2D Character::GetPosition() {

     return mPosition;

 }