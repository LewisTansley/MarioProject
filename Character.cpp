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

    mFacingDirection = FACING_RIGHT;

}

Character::~Character() {

    delete mTexture;
    mRenderer = NULL;
    mTexture = NULL;

}

 void Character::Update(float deltaTime, SDL_Event e) {

     SDL_PollEvent(&e);

     while (SDL_PollEvent(&e)) {

         switch (e.type) {
             case SDL_KEYDOWN:
                 switch (e.key.keysym.sym) {
                     case SDLK_a:
                         mMovingLeft = true;
                         if (mFacingDirection != FACING_LEFT) {
                             mFacingDirection = FACING_LEFT;
                         }
                         cout << "left" << endl;
                     break;
                     case SDLK_d:
                         mMovingRight = true;
                         if (mFacingDirection != FACING_RIGHT) {
                             mFacingDirection = FACING_RIGHT;
                         }
                         cout << "right" << endl;
                     break;
                 }
             break;
             case SDL_KEYUP:
                 switch (e.key.keysym.sym) {
                     case SDLK_a:
                         mMovingLeft = false;
                     break;
                     case SDLK_d:
                         mMovingRight = false;
                     break;
                 }
             break;
         }

     }

     if (mMovingLeft) {
         MoveLeft(deltaTime);
     }
     else if (mMovingRight) {
         MoveRight(deltaTime);
     }

 }

 void Character::Render() {

     if (mFacingDirection == FACING_RIGHT) {
         mTexture->Render(mPosition, SDL_FLIP_NONE);
     }
     else {
         mTexture->Render(mPosition, SDL_FLIP_HORIZONTAL);
     }

 }

 void Character::MoveLeft(float deltaTime) {

     mPosition.x -= 1.0f * deltaTime;

     SetPosition(mPosition);

 }

 void Character::MoveRight(float deltaTime) {

     mPosition.x += 1.0f * deltaTime;

     SetPosition(mPosition);

 }

 void Character::SetPosition(Vector2D newPosition) {

     mPosition = newPosition;
     
     
 }

 Vector2D Character::GetPosition() {

     return mPosition;

 }