//////////////////////////////MAIN MENU/////////////////////////////////////
#ifndef MENU
#define MENU

#include <conio.h>
#include <cstring>
#include <vector>
#include <windows.h>
#include "game.h"


template <typename T>
std::string toString(const T& value)
{
    std::stringstream stream;
    stream << value;
    return stream.str();
}

using namespace std;

class Menu
{
public:
    Menu();
    void run();
private:
    void processEvents();
    void updateOptionText();
    void render();
    void load();
    void exitMenu();
    void instructions();
    void highscores();

private:
    string Option[3] = { "PLAY","INSTRUCTIONS","EXIT"};
    sf::RenderWindow mWindow;
    sf::Texture mTexture;
    sf::Sprite  mSprite;
    sf::Font mFont;
    sf::Text mText;//loadText,loading;
    sf::Font oFont;
    vector<sf::Text> mOption;  //creating dynamic array for menu Options
    int mOptionIndex;
    sf::Text mInstruction;
    sf::Sprite background;
    // object declaration of Game class
};
Menu ::Menu() : mWindow(sf::VideoMode(750,460), "Frog Jump"),
    mTexture(),mSprite(),mOptionIndex(0),mInstruction(),background()
{
    if(!mTexture.loadFromFile("resources/front.png"))
    {
        cout<<"No File!!"<<endl;
    }
    mSprite.setTexture(mTexture);
    mSprite.setPosition(0,0);
    ////////////////////////Font Load////////////////////////////////////
    if(!mFont.loadFromFile("resources/COOPBL.ttf"))
        cout<<"Error Loading menu font"<<endl;
    mText.setFont(mFont);
    mText.setString("FROG-JUMP");
    mText.setFillColor(sf::Color::Yellow);
    mText.setCharacterSize(117);

    if(!oFont.loadFromFile("resources/COOPBL.ttf"))
        cout<<"Error Loading menu font"<<endl;

    string instruction = "\t\t Instructions\n\n Keys \n Z - Jump Once \n M- Jump Twice \n Jump through the leafs and survive \n Don't fall in the water \n Get HighScore in a limited time";
    mInstruction.setString(instruction);
    mInstruction.setFont(mFont);
    mInstruction.setCharacterSize(30);
    mInstruction.setPosition(sf::Vector2f(100,100));
    background.setTexture(mTexture);
    background.setColor(sf::Color(255,255,255,150));

    for(int i = 0; i<3 ; i++)
    {
        sf::Text tempOption;
        tempOption.setFont(oFont);
        tempOption.setString(Option[i]); //adds string from Option[i] to tempOption object
        tempOption.setFillColor(sf::Color::Green);
        tempOption.setCharacterSize(15);
        tempOption.setPosition(sf::Vector2f(450,250+(i*50)));
        mOption.push_back(tempOption); //adds tempOption to the back of array
    }
    updateOptionText();
}

void Menu::run()
{
    while (mWindow.isOpen())
    {
        processEvents();
        render();
    }
}

void Menu::processEvents()
{
    sf::Event event;
    while (mWindow.pollEvent(event))
    {
        if(event.type == sf::Event::Closed)
            exitMenu();
        if (event.type==sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Up)
            {
                if (mOptionIndex > 0)
                    mOptionIndex--;
                else
                    mOptionIndex = mOption.size() - 1;
                updateOptionText();
            }
            else if (event.key.code == sf::Keyboard::Down)
            {
                if (mOptionIndex < mOption.size() - 1)
                    mOptionIndex++;
                else
                    mOptionIndex = 0;
                updateOptionText();
            }

            if (event.key.code == sf::Keyboard::Return)
            {
                switch(mOptionIndex)
                {
                case 0 :
                    {
                        Game game;
                        //Menu window is close after user selects play option
                        game.run(); //game window opens
                    }
                    break;
                case 1 :
                    instructions();
                    break;
                case 2 :
                    exitMenu();
                }
            }
        }
    }
}

void Menu::updateOptionText()
{

    if (mOption.empty())
        return;
    for(int i = 0 ; i < 3 ; i++)
    {
        mOption[i].setColor(sf::Color::Green);
        mOption[i].setCharacterSize(30);
    }
    mOption[mOptionIndex].setColor(sf::Color::Green);
    mOption[mOptionIndex].setStyle(sf::Text::Bold);
    mOption[mOptionIndex].setCharacterSize(40);
}

void Menu::render()
{
    mWindow.clear();
    mWindow.draw(mSprite);
    mWindow.draw(mText);
    for(int i = 0; i<mOption.size(); i++)
        mWindow.draw(mOption[i]);
    mWindow.display();
}

void Menu :: exitMenu(void) //exit part of the game
{
    mWindow.close();
    exit(1);
}
void Menu::instructions()
{
    mWindow.clear();
    mWindow.draw(background);
    mWindow.draw(mInstruction);
    mWindow.display();
    Sleep(5000);
}
#endif // MENU
