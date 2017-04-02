#ifndef GAME
#define GAME

#include <iostream>
#include <vector>
#include <windows.h>
#include <random>
#include<sstream>

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

using namespace std;

class Game
{
public:
    Game();  //Game Constructor
    void run();
private:
    void processEvents();  //process the window events
    void handlePlayerInput(sf::Keyboard::Key, bool isPressed); //handle the input from the player
    void update(); //updates the window
    void render(); //draws in the window
    void gameOver();
    void updateTime(int time);  //updates the game time

    sf::RenderWindow mWindow;
    sf::Texture mLeaf,mBrick, mSceneOne,mSceneTwo, mFrog,fleaf;
    sf::Sprite mSceneSpriteOne,mSceneSpriteTwo, mFrogSprite, mLeafSpriteDefault,mBrickSpriteDefault,fleafSprite;

    sf::SoundBuffer mSound,splash,mticktock;
    sf::Sound frogSound,splashSound,ticktock;
    sf::Text textScore, mtextScore;
    sf::Text timeDisplay;
    sf::Font font;
    vector<sf::Sprite>mLeafSprite;//creates dynamic vector array for leaf sprite
    bool jumpOnce;
    bool jumpTwice;
    bool isKeyPressed;
    bool safe; //checks whether player is safe or not

    int gameScore=0;
    float y=40;  //jumping height for frog

    float bg1X;
    float bg2X;

    float leafX=75;
    float leafY=390; //sets the y position of leaf


};


#endif // GAME
