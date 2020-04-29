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

    mCollidingBottom = false;
    mCollidingTop = false;
    mCollidingLeft = false;
    mCollidingRight = false;

    mFacingDirection = FACING_RIGHT;

}

Player::~Player() {

    delete mTexture;
    mRenderer = NULL;
    mTexture = NULL;

}

void Player::AddGravity(float deltaTime) {

    if (mPosition.y < 342) {
        mPosition.y += 0.5f * deltaTime;
        mCollidingBottom = false;
    }
    else {
        mCollidingBottom = true;
    }
}

void Player::ViewportCollision(float deltaTime) {

    //Checks if Mario is trying to dissapear
    //if (mPosition.x > Graphics::GetViewportWidth()) {
    //    mPosition.x -= _pacman->pacmanSpeed * deltaTime;
    //}

}
void Player::Collision(float deltaTime) {

    if (mCollidingBottom || mCollidingTop || mCollidingLeft || mCollidingRight) {
        mColliding = true;
    }
    else {
        mColliding = false;
    }
    if (mCollidingBottom) {
        mCanJump = true;
    }
    else {
        mCanJump = false;
    }
}

void Player::Jump() {

    if (!mJumping) {
        mJumpForce = INITIAL_JUMP_FORCE;
        mJumping = true;
        mCanJump = false;
    }


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
               case SDLK_SPACE:
                   if (mCanJump) {
                       Jump();
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

    if (mJumping) {
        mPosition.y -= mJumpForce * deltaTime;
        mJumpForce -= JUMP_FORCE_DECREMENT * deltaTime;
        if (mJumpForce <= 0.0f) {
            mJumping = false;
        }
    }

    if (mMovingLeft) {
        MoveLeft(deltaTime);
    }
    else if (mMovingRight) {
        MoveRight(deltaTime);
    }
    
    AddGravity(deltaTime);
    Collision(deltaTime);

}

 void Player::Render() {

     if (mFacingDirection == FACING_RIGHT) {
         mTexture->Render(mPosition, SDL_FLIP_NONE,0);
     }
     else {
         mTexture->Render(mPosition, SDL_FLIP_HORIZONTAL,0);
     }

 }

 void Player::MoveLeft(float deltaTime) {

     mPosition.x -= MOVEMENTSPEED;

     SetPosition(mPosition);

 }

 void Player::MoveRight(float deltaTime) {

     mPosition.x += MOVEMENTSPEED;

     SetPosition(mPosition);

 }

 void Player::SetPosition(Vector2D newPosition) {

     mPosition = newPosition;
     
     
 }

 Vector2D Player::GetPosition() {

     return mPosition;

 }