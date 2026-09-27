#include "Bullet.h"
#include "Player.h"
Bullet::Bullet(CMPUT350::Point2D location, CMPUT350::Point2D heading, bool player):
mLocation(location), mPreviousLocation(location),
mHeading(heading),mPlayer(player),
mAlive(true), mBounds(location, location)
{
}

bool Bullet::IsPlayerBullet()
{
    // TODO: Update
    return mPlayer;
}

void Bullet::Initialize(CMPUT350::GameContext* context)
{
}

void Bullet::Update(CMPUT350::GameContext* context)
{
    mPreviousLocation = mLocation;
    mLocation += mHeading;
    mBounds = CMPUT350::Rect(mPreviousLocation, mLocation);
}

void Bullet::LateUpdate(CMPUT350::GameContext* context)
{
}

bool Bullet::HandleKeyEvent(CMPUT350::GameContext* context, char key)
{
    return false;
}

void Bullet::RenderBackground(CMPUT350::GameContext* context)
{
}

void Bullet::RenderForeground(CMPUT350::GameContext* context)
{
    context->ScreenContext->DrawLine( mPreviousLocation, mLocation, 2.0f, CMPUT350::Colors::white );
}

void Bullet::CollisionEnter(const std::shared_ptr<CMPUT350::CollisionObject>& obj)
{
    std::shared_ptr<Player> player = std::dynamic_pointer_cast<Player>(obj);
    if (mPlayer && player){
        return;
    }
    Kill();
}

void Bullet::Kill()
{
    mAlive = false;
}

bool Bullet::IsAlive() const
{
    // TODO: Update code
    return mAlive;
}

const CMPUT350::Rect& Bullet::GetBounds()
{
    // TODO: Update code
    return mBounds;
}
