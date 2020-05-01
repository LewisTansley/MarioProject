#include "Player.h"
#include "Texture2D.h"
#include "Constants.h"
#include "SoundEffect.h"



using namespace::std;

Player::Player(SDL_Renderer* renderer, string imagePath, Vector2D startPosition,LevelMap* map) : Character(renderer, imagePath, startPosition, map) {

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

    mCurrentLevelMap = map;

    mCollisionRadius = 15.0f;

}

Player::~Player() {

    delete mTexture;
    mRenderer = NULL; 
    mTexture = NULL;


}

void Player::Collision(float deltaTime) {

    if (mCollidingBottom) {
        mCanJump = true;
    }
    else {
        mCanJump = false;
    }
}

void Player::AddGravity(float deltaTime) {

    mPosition.y += 0.5f * deltaTime;
    mCollidingBottom = false;

}

void Player::Jump(float deltaTime) {

    if (!mJumping) {
        mJumpForce = 20.0f;
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

float Player::GetCollisionRadius() {

    return mCollisionRadius;

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
                       PlaySound("Audio/Jump.wav",0);
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
        

    int centralXPosition = (int)(mPosition.x + (mTexture->GetWidth() * 0.5f)) / TILE_WIDTH;
    int footPosition = (int)(mPosition.y - 2 + mTexture->GetHeight()) / TILE_HEIGHT;

    if (mCurrentLevelMap->GetTileAt(footPosition, centralXPosition) == 0) {
        AddGravity(deltaTime);
    }
    else {
        mCollidingBottom = true;
    }

    Jump(deltaTime);

    Collision(deltaTime);

    //cout << GetPosition().x << " " << GetPosition().y << endl;

    if ((mPosition.x + (mTexture->GetWidth() / 2)) < 0) {
        mPosition.x = SCREEN_WIDTH - (mTexture->GetWidth() / 2);
        SDL_Delay(1);
    }
    if ((mPosition.x + (mTexture->GetWidth() / 2)) > SCREEN_WIDTH) {
        mPosition.x = 0 - (mTexture->GetWidth() / 2);
        SDL_Delay(1);
    }
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