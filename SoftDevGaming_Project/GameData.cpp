#include "GameData.h"
#include "Player.h"
#include <fstream> // For file I/O
#include <string>
using namespace std;

//Code commented in this file works just not included due to cheat loop in the game, 
//Else need to implement saving state

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

void GameData::SaveGame(Player& player, int currentLevel)
{
    ofstream outFile("savegame.txt");
    if (!outFile.is_open())
    {
        cout << "\nError: Unable to save game." << endl;
        return;
    }

    // Basic info
    outFile << player.getName() << endl;
    outFile << player.getSymbol() << endl;
    outFile << player.getHealth() << endl;
    outFile << player.getAttack() << endl;
    outFile << player.getScore() << endl;
    outFile << player.getX() << endl;
    outFile << player.getY() << endl;

    // Level
    outFile << currentLevel << endl;

    // Inventory
    //vector<Item> inv = player.getInventory();
    //outFile << inv.size() << endl;  // how many items

    //for (auto& item : inv)
    //{
    //    outFile << item.getName() << endl;
    //    outFile << item.getType() << endl;
    //    outFile << item.getBoostAmount() << endl;
    //} 
}

void GameData::LoadGame(Player& player, int& currentLevel)
{
    ifstream inFile("savegame.txt");
    if (!inFile.is_open())
    {
        cout << "\nNo save file found." << endl;
        return;
    }

    string name;
    char symbol;
    int hp, atk, score, x, y;

    getline(inFile, name);
    inFile >> symbol;
    inFile >> hp;
    inFile >> atk;
    inFile >> score;
    inFile >> x;
    inFile >> y;

    inFile >> currentLevel;

    int invCount;
    inFile >> invCount;
    inFile.ignore(); // flush newline

    /*vector<Item> loadedInv;
    for (int i = 0; i < invCount; i++)
    {
        string itemName, itemType;
        int boost;
        getline(inFile, itemName);
        getline(inFile, itemType);
        inFile >> boost;
        inFile.ignore();

        loadedInv.emplace_back(itemName, itemType, boost);
    }*/

    // Apply to player
    player.setHealth(hp);
    player.setAttack(atk);
    player.setScore(score);
    player.setPosition(x, y);
    //player.setInventory(loadedInv);

    cout << "\nGame Loaded Successfully!" << endl;
}
