#include "GameEngine.h"
#include <cstdio>
#include "GraphicsObject.h"
#include "CollisionObject.h"

/// @brief
namespace CMPUT350 {
#include "FontData.h"

GameEngine::GameEngine(unsigned int width, unsigned int height, const std::string& name) {
    mWindow = std::make_shared<sf::RenderWindow>(
        sf::VideoMode({width, height}),
        name
    );

    mWindow->setFramerateLimit(30);

    mFont = std::make_shared<sf::Font>();

    if (!mFont->openFromMemory(&_font, _font_len)) {
        fprintf(stderr, "WARNING: Font did not load.\n");
    }

    mDrawContext = std::make_shared<DrawContext>(mWindow, mFont);

    mGameContext.mEngineView = this;
    mGameContext.ScreenContext = mDrawContext.get();
}

GameEngine::~GameEngine() {
    // Cleanup resources
    if (mWindow != nullptr){
        mWindow->close();
    }
}

void GameEngine::AddGameObject(std::shared_ptr<GameObject> gameObject) {
    mNewGameObjects.push_back(gameObject);
}

/**
 * @method Run
 * @arguments None
 * @description Gives control to the game engine. Will not return until the game window is closed or
 * all objects have been destroyed.
 */
void GameEngine::Run() {
    while (mWindow->isOpen())  // window is open
    {
        // 0. Remove any objects that are now dead
        size_t writeIndex = 0;
        for (size_t readIndex = 0; readIndex < mGameObjects.size(); ++readIndex) {
            if (mGameObjects[readIndex]->IsAlive()) {
                mGameObjects[writeIndex] = mGameObjects[readIndex];
                ++writeIndex;
            }
        }

        mGameObjects.resize(writeIndex);

        // 1. Activate and initialize any objects added during the last frame
        for (auto &gameObject : mNewGameObjects) {
            mGameObjects.push_back(gameObject);
            gameObject->Initialize(&mGameContext);
        }

        mNewGameObjects.clear();

        // 2. Process events
        while (const std::optional event = mWindow->pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                mWindow->close();
            }
            else if (const auto* keyPressed =
                        event->getIf<sf::Event::TextEntered>()) {

                if (keyPressed->unicode < 128) {
                    char key = static_cast<char>(keyPressed->unicode);

                    for (auto &gameObject : mGameObjects) {
                        gameObject->HandleKeyEvent(&mGameContext, key);
                    }
                }
            }
        }

        // 3. Update game objects
        for (auto &gameObject : mGameObjects) {
            gameObject->Update(&mGameContext);
        }

        // 4. Process collision events
        for (size_t a = 0; a < mGameObjects.size(); ++a) {
            auto objA = std::dynamic_pointer_cast<CollisionObject>(mGameObjects[a]);

            if (objA == nullptr) {
                continue;
            }

            for (size_t b = a + 1; b < mGameObjects.size(); ++b) {
                auto objB =
                    std::dynamic_pointer_cast<CollisionObject>(mGameObjects[b]);

                if (objB == nullptr) {
                    continue;
                }

                if (objA == objB) {
                    continue;
                }

                const Rect &boundsA = objA->GetBounds();
                const Rect &boundsB = objB->GetBounds();

                float aLeft = boundsA.topLeft.x;
                float aRight = boundsA.topLeft.x + boundsA.width;
                float aTop = boundsA.topLeft.y;
                float aBottom = boundsA.topLeft.y + boundsA.height;

                float bLeft = boundsB.topLeft.x;
                float bRight = boundsB.topLeft.x + boundsB.width;
                float bTop = boundsB.topLeft.y;
                float bBottom = boundsB.topLeft.y + boundsB.height;

                bool overlap =
                    !(aRight < bLeft ||
                    bRight < aLeft ||
                    aBottom < bTop ||
                    bBottom < aTop);

                if (overlap) {
                    objA->CollisionEnter(objB);
                    objB->CollisionEnter(objA);
                }
            }
        }

        // 5. Late updates
        for (auto &gameObject : mGameObjects) {
            gameObject->LateUpdate(&mGameContext);
        }

        // Clear window
        mWindow->clear();

        // 6. Render background
        for (auto &gameObject : mGameObjects) {
            auto graphicsObject = std::dynamic_pointer_cast<GraphicsObject>(gameObject);
            if (graphicsObject != nullptr) {
                graphicsObject->RenderBackground(&mGameContext);
            }
        }

        // 7. Render foreground
        for (auto &gameObject : mGameObjects) {
            auto graphicsObject = std::dynamic_pointer_cast<GraphicsObject>(gameObject);
            if (graphicsObject != nullptr) {
                graphicsObject->RenderForeground(&mGameContext);
            }
        }

        // Actually render to window
        mWindow->display();
    }
}

// Sample code for processing events

// bool GameEngine::ProcessEvents(GameContext *context)
//{
//	while (const std::optional event = mWindow->pollEvent())
//	{
//		if (event->is<sf::Event::Closed>())
//		{
//		}
//		else if (event->is<sf::Event::Resized>())
//		{
//		}
//		else if (const auto* keyPressed = event->getIf<sf::Event::TextEntered>())
//		{
//			// use keyPressed->unicode to get character
//		}
//	}
// }

}  // namespace CMPUT350
