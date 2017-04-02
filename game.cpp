#include "game.h"

Game::Game():mWindow(sf::VideoMode(750,460),"FROG JUMP"), jumpOnce(false), jumpTwice(false), isKeyPressed(false)
{
//////////////////////Background Scenes////////////////////////////////////
    if(!mSceneOne.loadFromFile("resources/scene.png")) //loads background unflipped scene
    {
        cout<<"error in loading scene"<<endl;
    }
    mSceneSpriteOne.setTexture(mSceneOne);
    mSceneSpriteOne.setPosition(0,0);  //sets the position of first background scene
    bg1X=mSceneSpriteOne.getPosition().x; //gets x co-ordinate of first background scene

    if(!mSceneTwo.loadFromFile("resources/sceneflipped.png"))
    {
        cout<<"Error in loading flipped scene"<<endl;
    }
    mSceneSpriteTwo.setTexture(mSceneTwo);
    mSceneSpriteTwo.setPosition(750,0); //sets the position of flipped background scene
    bg2X=mSceneSpriteTwo.getPosition().x;  //gets x co-ordinate of flipped background scene

///////////////////////////Player////////////////////////
    if(!mFrog.loadFromFile("resources/frog.png")) //loads frog
    {
        cout<<"Error in loading Player"<<endl;
    }
    mFrogSprite.setTexture(mFrog);
    mFrogSprite.setTextureRect(sf::IntRect(0,60,66,64));
    mFrogSprite.setPosition(225,348);

///////////////////////////Leaf/////////////////////////////
    if(!mLeaf.loadFromFile("resources/leaf.png")) //loads leaf
    {
        cout<<"Error in loading leaf"<<endl;
    }
     if(!mBrick.loadFromFile("resources/brick.png")) //loads leaf
    {
        cout<<"Error in loading brick"<<endl;
    }
    mLeafSpriteDefault.setTexture(mLeaf);
    mBrickSpriteDefault.setTexture(mBrick);
    for(int i=4;i<100;i++)
    {
        if(i%2==0)
        mLeafSprite.push_back(mLeafSpriteDefault);
        else
        mLeafSprite.push_back(mBrickSpriteDefault);

    }
     for(int i=100;i<=600;i++)
    {
        mLeafSprite.push_back(mBrickSpriteDefault);

    }
     mLeafSprite[0].setPosition(0*leafX,leafY);
     mLeafSprite[1].setPosition(1*leafX,leafY);
     mLeafSprite[2].setPosition(2*leafX,leafY);
     mLeafSprite[3].setPosition(3*leafX,leafY);
     for(int i=4;i<=600;i++)
        mLeafSprite[i+1].setPosition(mLeafSprite[i].getPosition().x+(rand()%2+1)*75,leafY);
    //////////////////Sound////////////////////////
    if(!mSound.loadFromFile("resources/cutfrog.ogg"))
    {
        cout<<"Error in loading sound"<<endl;
    }
    frogSound.setBuffer(mSound);
    frogSound.setVolume(30);
    if(!splash.loadFromFile("resources/splasss.wav"))
    {
        cout<<"Error in loading splash sound"<<endl;
    }
    splashSound.setBuffer(splash);
    splashSound.setVolume(100);
    if(!mticktock.loadFromFile("resources/ticktock.wav"))
    {
        cout<<"Error in loading ticktock sound"<<endl;
    }
    ticktock.setBuffer(mticktock);
    //////////////////////Font/////////////////////////
    if (!font.loadFromFile("resources/COOPBL.ttf"))
    {
        cout<<"couldnt load font"<<endl;
    }
    mtextScore.setString("Score");
    mtextScore.setFont(font);
    mtextScore.setFillColor(sf::Color::Red);
    mtextScore.setPosition(5,10);
}
void Game::run()
{
    sf::Clock gameClock;   //starts the game clock
   while(mWindow.isOpen())
   {

       sf::Time gameTime=gameClock.getElapsedTime();
       int playTime=gameTime.asMilliseconds()/1000;
       updateTime(playTime);
       if(playTime==20)  //playtime is 20 seconds
       {
           gameOver();
       }
       if(playTime==15)
       {
           //ticktock.setPitch(0.1);
           ticktock.play();
           //Sleep(500);
       }

       mWindow.setKeyRepeatEnabled(false);
       processEvents();
       update();
       render();
   }
}
void Game::processEvents()
{
    sf::Event event;
    while (mWindow.pollEvent(event))
    {
        switch(event.type)
        {
            case sf::Event::Closed :
                mWindow.close();
                break;
            case sf::Event::KeyPressed:
                {
                    handlePlayerInput(event.key.code, true);
                    sf::Keyboard::Key key=event.key.code;
                    if(key==sf::Keyboard::Z)
                    {
                       frogSound.play();   //plays frog sound
                        for(int i=0;i<=mLeafSprite.size();i++)
                        {
                            float leaf;
                            leaf=mLeafSprite[i].getPosition().x-75;
                            mLeafSprite[i].setPosition(leaf,leafY);
                        }
                    }
                    else if(key==sf::Keyboard::M)
                    {
                       frogSound.play();  //plays frog sound
                        for(int i=0;i<=mLeafSprite.size();i++)
                        {
                            float leaf;
                            leaf=mLeafSprite[i].getPosition().x-150;
                            mLeafSprite[i].setPosition(leaf,leafY);

                        }
                    }
                }
                break;
            case sf::Event::KeyReleased:
                {
                    gameScore=gameScore+1;
                    handlePlayerInput(event.key.code,false);
                    break;
                }
            default:
                break;

        }
    }

}
void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{

    if(key==sf::Keyboard::Z)
    {
        jumpOnce=isPressed;
        isKeyPressed=isPressed;
    }
    if(key==sf::Keyboard::M)
    {
      jumpTwice=isPressed;
      isKeyPressed=isPressed;
    }

}

void Game::update()
{
    ///////////////////Score Update//////////////////////////////
    textScore.setFillColor(sf::Color::Yellow);
    string score=static_cast<ostringstream*>(&(ostringstream()<<gameScore))->str();
    textScore.setString(score);
    textScore.setFont(font);
    textScore.setPosition(120,10);
    ///////////////////////////Player Animation and Movement//////////////////////////////////////////////////
    if(jumpOnce==true)
    {
        mFrogSprite.setTextureRect(sf::IntRect(80,60,75,60));
        mFrogSprite.setPosition(225,348-y);
        safe=false;

    }
    else if(jumpTwice==true)
    {
        mFrogSprite.setTextureRect(sf::IntRect(80,60,75,60));
        mFrogSprite.setPosition(225,348-2*y);
        safe=false;
    }
    else
    {
        mFrogSprite.setTextureRect(sf::IntRect(0,60,75,60));
        mFrogSprite.setPosition(225,348);
    }

    ////////////////////////Background movement///////////////////////////////////
    if(isKeyPressed==true)
    {
        float diff=bg1X+mWindow.getSize().x; //calculates the difference between x-windowSize and x-co-ordinate of first background
        if(bg1X<=-750)
        {
            bg1X=750;
        }
        else
        {
            bg1X-=2;
        }
        if(bg2X<=-750)
        {
            bg2X=750;
        }
        else if(bg1X<bg2X)
        {
            bg2X=diff;
        }
        else
        {
            bg2X-=2;
        }
        mSceneSpriteOne.setPosition(bg1X,0); //sets the position of first scene
        mSceneSpriteTwo.setPosition(bg2X,0); //sets the position of second scene
    }
    for(int i=0;i<mLeafSprite.size();i++)
    {
       if(mLeafSprite[i].getGlobalBounds().intersects(mFrogSprite.getGlobalBounds()))
       {
           safe=true;  //player is safe
       }
    }

    if((safe==false)&&mFrogSprite.getPosition().y==348)
    {
    splashSound.play();
    mFrogSprite.setTextureRect(sf::IntRect(155,60,100,60));
    mWindow.draw(mFrogSprite);
    Sleep(200);
    gameOver();

    }


}


void Game::render()    //draws the entites on the window
{
    mWindow.clear();
    mWindow.draw(mSceneSpriteOne); //draws first original background scene
    mWindow.draw(mSceneSpriteTwo);

   for(int i=0;i<mLeafSprite.size();i++)
   {

       mWindow.draw(mLeafSprite[i]);
   }
    mWindow.draw(mtextScore);
    mWindow.draw(mFrogSprite);
    mWindow.draw(timeDisplay);
    mWindow.draw(textScore);
    mWindow.display();
}

void Game::gameOver()
{
    sf::Text mgameOver;
    mgameOver.setFont(font);
    mgameOver.setCharacterSize(100);
    string s = "Game Over";
    string sub;
    //gameOver.setString(s);
    sf::Vector2f v;
    v.x = (mWindow.getSize().x)/8;
    v.y = (mWindow.getSize().y)/3;
    mgameOver.setPosition(sf::Vector2f(v));

    sf::RectangleShape rect;
    rect.setFillColor(sf::Color(0,0,0,77));
    rect.setSize(sf::Vector2f(mWindow.getSize()));

    for(int i = 0 ; i != s.length()+1; i++) //displays "GAME OVER" in the screen
    {
        sub.append(s,i,1);
        mgameOver.setString(sub);
        mWindow.draw(rect);
        mWindow.draw(mgameOver);
        mWindow.display();
        Sleep(200);
    }
    sf::Text scoreDisplay;
    scoreDisplay.setFont(font);
    string score=static_cast<ostringstream*>(&(ostringstream()<<gameScore))->str();
    string mScore="Your score: "+score;
    scoreDisplay.setCharacterSize(50);
    scoreDisplay.setPosition(sf::Vector2f(mWindow.getSize().x/10,mWindow.getSize().y/1.5));
    scoreDisplay.setString(mScore);
    mWindow.draw(scoreDisplay);
    mWindow.draw(timeDisplay);

    mWindow.display();
    Sleep(2000);

    mWindow.close();
}

void Game::updateTime(int time)
{
        static int pTime=20;
        time=pTime-time;
        string timeDown; //updates the game time
        timeDisplay.setFont(font);
        timeDown=static_cast<ostringstream*>(&(ostringstream()<<time))->str();
        string timeDisp="Time: " + timeDown +"s";
        timeDisplay.setString(timeDisp);
        timeDisplay.setFillColor(sf::Color::Yellow);
        timeDisplay.setPosition(500,10);
        timeDisplay.setCharacterSize(30);

}

