#include "GameData.h"
#include <fstream> // For file I/O
#include <string>
using namespace std;

// Initialize static member
GameData* GameData::instance = nullptr;

GameData::GameData() {}

GameData* GameData::GetInstance()
{
    if (instance == nullptr)
    {
        instance = new GameData();
    }
    return instance;
}

void GameData::SaveGame(const Player& player)
{
    ofstream outFile("savegame.txt");
    if (outFile.is_open())
    {
        // Save order: Name, Health, Attack, Score, X, Y
        outFile << player.getName() << endl;
        outFile << player.getHealth() << endl;
        outFile << player.getScore() << endl; // Assuming Score stores progress
        outFile << player.getX() << endl;
        outFile << player.getY() << endl;

        cout << "Game Saved Successfully!" << endl;
        outFile.close();
    }
    else
    {
        cout << "Error: Unable to save game." << endl;
    }
}

void GameData::LoadGame(Player& player)
{
    ifstream inFile("savegame.txt");
    if (inFile.is_open())
    {
        string name;
        int hp, score, x, y;

        // Read in the same order we saved
        getline(inFile, name);
        inFile >> hp;
        inFile >> score;
        inFile >> x;
        inFile >> y;

        // Use setters to update player
        // Note: might need to add setScore or setX/Y to Player if missing
        player.setHealth(hp);
        //player.setScore(score); 
        //player.setPosition(x, y); 
        cout << "Game Loaded Successfully!" << endl;
        inFile.close();
    }
    else
    {
        cout << "No save file found." << endl;
    }
}