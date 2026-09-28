#include <cassert>
#include "Player.h"
#include "Bullet.h"
#include "GameContext.h"
#include <algorithm>
#include <SFML/Window/Keyboard.hpp>

Player::Player(CMPUT350::Point2D loc)
:mLocation(loc), mBounds(loc - 20.0f, 40, 40),mAlive(true)
{
    // TODO: Update code
}

void Player::Initialize(CMPUT350::GameContext* context)
{
}

void Player::Update(CMPUT350::GameContext* context)
{
    const float speed = 10.0f;
    const float halfWidth = 20.0f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)){
        mLocation.x -= speed;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)){
        mLocation.x += speed;
    }

    // Do not allow the player to leave the screen
    float screenWidth = context->ScreenContext->GetWindowWidth();
    if (mLocation.x < halfWidth){
        mLocation.x = halfWidth;
    }
    if (mLocation.x > screenWidth - halfWidth){
        mLocation.x = screenWidth - halfWidth;
    }
    mBounds = CMPUT350::Rect(mLocation- 20.0f,40,40);
}

void Player::LateUpdate(CMPUT350::GameContext* context)
{
}

bool Player::HandleKeyEvent(CMPUT350::GameContext* context, char key)
{
    if (key == ' ')
    {
        mBullets.erase(
            std::remove_if(
                mBullets.begin(),
                mBullets.end(),
                [](const std::weak_ptr<Bullet>& bullet)
                {
                    return bullet.expired();
                }
            ),
            mBullets.end()
        );

        if (mBullets.size() >= 2)
        {
            return true;
        }

        std::shared_ptr<Bullet> bullet =
            std::make_shared<Bullet>(
                mLocation,
                CMPUT350::Point2D(0, -15),
                true
            );

        context->mEngineView->AddGameObject(bullet);
        mBullets.push_back(bullet);
        return true;
    }
    return false;
}

void Player::RenderBackground(CMPUT350::GameContext* context)
{
}

void Player::RenderForeground(CMPUT350::GameContext* context)
{
    CMPUT350::Point2D top =  mLocation + CMPUT350::Point2D(0, -20);
    CMPUT350::Point2D left = mLocation + CMPUT350::Point2D(-20, 20);
    CMPUT350::Point2D right = mLocation + CMPUT350::Point2D(20, 20);
    context->ScreenContext->DrawLine( top,left,3.0f,CMPUT350::Colors::cyan);

    context->ScreenContext->DrawLine(left,right,3.0f,CMPUT350::Colors::cyan);

    context->ScreenContext->DrawLine(right,top,3.0f,CMPUT350::Colors::cyan);
}

void Player::CollisionEnter(const std::shared_ptr<CMPUT350::CollisionObject>& obj)
{
    std::shared_ptr<Bullet> bullet =std::dynamic_pointer_cast<Bullet>(obj);
    if (bullet && bullet->IsPlayerBullet()){
        return;
    }
}

void Player::Kill()
{
    mAlive = false;
}

bool Player::IsAlive() const
{
    // TODO: Update code
    return mAlive;
}

const CMPUT350::Rect& Player::GetBounds()
{
    // TODO: Update code
    return mBounds;
}
