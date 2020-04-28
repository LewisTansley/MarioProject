#include "Player.h"
#include "Texture2D.h"
#include "Constants.h"


Player::Player(SDL_Renderer* renderer, string imagePath, Vector2D startPosition) {

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

Player::~Player() {

    delete mTexture;
    mRenderer = NULL;
    mTexture = NULL;

}

 void Player::Update(float deltaTime, SDL_Event e) {

         switch (e.type) {
         case SDL_KEYDOWN:
             switch (e.key.keysym.sym) {
             case SDLK_a:
                 mMovingLeft = true;
                 if (mFacingDirection != FACING_LEFT) {
                     mFacingDirection = FACING_LEFT;
                 }
                 break;
             case SDLK_d:
                 mMovingRight = true;
                 if (mFacingDirection != FACING_RIGHT) {
                     mFacingDirection = FACING_RIGHT;
                 }
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

     

     if (mMovingLeft) {
         MoveLeft(deltaTime);
     }
     else if (mMovingRight) {
         MoveRight(deltaTime);
     }

 }

 void Player::Render() {

     if (mFacingDirection == FACING_RIGHT) {
         mTexture->Render(mPosition, SDL_FLIP_NONE);
     }
     else {
         mTexture->Render(mPosition, SDL_FLIP_HORIZONTAL);
     }

 }

 void Player::MoveLeft(float deltaTime) {

     mPosition.x -= 0.1f;

     SetPosition(mPosition);

 }

 void Player::MoveRight(float deltaTime) {

     mPosition.x += 0.1f;

     SetPosition(mPosition);

 }

 void Player::SetPosition(Vector2D newPosition) {

     mPosition = newPosition;
     
     
 }

 Vector2D Player::GetPosition() {

     return mPosition;

 }