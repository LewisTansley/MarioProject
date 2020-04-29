#include "Player.h"
#include "Texture2D.h"
#include "Constants.h"

float velocity;
float acceleration = 0.02f;

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

void Player::Collision(float deltaTime) {

    /*if (mCollidingBottom || mCollidingTop || mCollidingLeft || mCollidingRight) {
        mColliding = true;
    }
    else {
        mColliding = false;
    }*/
    if (mCollidingBottom) {
        mCanJump = true;
    }
    else {
        mCanJump = false;
    }
}

void Player::Jump(float deltaTime) {

    if (!mJumping) {
        mJumpForce = 22.5f;
        mCanJump = false;
    }
    if (mJumping) {
        mPosition.y -= mJumpForce * (deltaTime / 16);
        mJumpForce -= 0.05f * deltaTime;
        if (mJumpForce <= 0.0f) {
            mJumping = false;
        }
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
                       mJumping = true;
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
 
    if (mMovingLeft || mMovingRight) {
        Movement(deltaTime);
    }
    else {
        if (velocity > 0.0f) {
            velocity -= acceleration * (deltaTime / 16);
        }
    }
        
    Jump(deltaTime);
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

void Player::Movement(float deltaTime) {

    if (mMovingLeft) {

        if (velocity < 0.5f) {
            velocity += acceleration * (deltaTime / 16);
        }

        mPosition.x -= velocity * deltaTime;
    }

    if (mMovingRight) {

        if (velocity < 0.5f) {
            velocity += acceleration * (deltaTime / 16);
        }

        mPosition.x += velocity * deltaTime;

    }
    
    SetPosition(mPosition);

}

 void Player::SetPosition(Vector2D newPosition) {

     mPosition = newPosition;
     
 }

 Vector2D Player::GetPosition() {

     return mPosition;

 }