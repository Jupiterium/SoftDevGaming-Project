#include "GameData.h"
#include "Player.h"
#include "EnemyFactory.h"
#include <fstream>
#include <string>
using namespace std;

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

void GameData::SaveGame(Player& player, int currentLevel, const vector<Item*>& worldItems, const vector<Item*>& worldKeys, const vector<Enemy*>& enemies)
{
    ofstream outFile("savegame.txt");
    if (!outFile.is_open()) {
        cout << "Error: Unable to save game." << endl;
        return;
    }

    // Save Player Stats
    outFile << player.getName() << endl;
    outFile << player.getSymbol() << endl;
    outFile << player.getHealth() << endl;
    outFile << player.getAttack() << endl;
    outFile << player.getScore() << endl;
    outFile << player.getX() << endl;
    outFile << player.getY() << endl;
    outFile << currentLevel << endl;

    // Save Inventory
    vector<Item>& inv = player.getInventory();
    outFile << inv.size() << endl;
    for (const auto& item : inv) {
        outFile << item.getName() << endl;
        outFile << item.getType() << endl;
        outFile << item.getSymbol() << endl;
        outFile << item.getBoostAmount() << endl;
    }

    // Save World Items
    outFile << worldItems.size() << endl;
    for (Item* item : worldItems) {
        outFile << item->getName() << endl;
        outFile << item->getType() << endl;
        outFile << item->getSymbol() << endl;
        outFile << item->getBoostAmount() << endl;
        outFile << item->getX() << endl;
        outFile << item->getY() << endl;
    }

    // Save World Keys
    outFile << worldKeys.size() << endl;
    for (Item* key : worldKeys) {
        outFile << key->getName() << endl;
        outFile << key->getType() << endl;
        outFile << key->getSymbol() << endl;
        outFile << key->getBoostAmount() << endl;
        outFile << key->getX() << endl;
        outFile << key->getY() << endl;
    }

    // Save Enemies
    outFile << enemies.size() << endl;
    for (auto* e : enemies) {
        outFile << e->getName() << endl;
        outFile << e->getHealth() << endl;
        outFile << e->getAttack() << endl;
        outFile << e->getX() << endl;
        outFile << e->getY() << endl;
    }

    outFile.close();
}

bool GameData::LoadGame(Player& player, int& currentLevel, vector<Item*>& worldItems, vector<Item*>& worldKeys, vector<Enemy*>& enemies)
{
    ifstream inFile("savegame.txt");
    if (!inFile.is_open()) {
        return false;
    }

    string name; char symbol; int hp, atk, score, x, y;
    getline(inFile, name);
    inFile >> symbol >> hp >> atk >> score >> x >> y;

    player.setHealth(hp);
    player.setAttack(atk);
    player.setScore(score);
    player.setPosition(x, y);

    inFile >> currentLevel;

    // Load Inventory
    int invCount;
    inFile >> invCount;
    inFile.ignore(); // flush newline

    vector<Item> loadedInv;
    for (int i = 0; i < invCount; i++)
    {
        string iName, iType; char iSym; int iBoost;
        getline(inFile, iName);
        getline(inFile, iType);
        inFile >> iSym >> iBoost;
        inFile.ignore();

        // Create item (X,Y are 0 since it's in inventory)
        loadedInv.push_back(Item(iName, iType, iSym, iBoost, 0, 0));
    }
    player.setInventory(loadedInv);

    // Load World Items
    int itemCount;
    inFile >> itemCount;
    inFile.ignore();

    for (auto i : worldItems) delete i;
    worldItems.clear();

    for (int i = 0; i < itemCount; i++) {
        string iName, iType; char iSym; int iBoost, iX, iY;
        getline(inFile, iName);
        getline(inFile, iType);
        inFile >> iSym >> iBoost >> iX >> iY;
        inFile.ignore();
        worldItems.push_back(new Item(iName, iType, iSym, iBoost, iX, iY));
    }

    // Load World Keys
    int keyCount;
    inFile >> keyCount;
    inFile.ignore();

    for (auto k : worldKeys) delete k;
    worldKeys.clear();

    for (int i = 0; i < keyCount; i++)
    {
        string kName, kType; char kSym; int kBoost, kX, kY;
        getline(inFile, kName);
        getline(inFile, kType);
        inFile >> kSym >> kBoost >> kX >> kY;
        inFile.ignore();
        worldKeys.push_back(new Item(kName, kType, kSym, kBoost, kX, kY));
    }

    // Load Enemies
    int enemyCount;
    inFile >> enemyCount;
    inFile.ignore();

    for (auto e : enemies) delete e;
    enemies.clear();

    for (int i = 0; i < enemyCount; ++i)
    {
        string eName; int eHp, eAtk, eX, eY;
        getline(inFile, eName);
        inFile >> eHp >> eAtk >> eX >> eY;
        inFile.ignore();

        int typeId = 1;
        if (eName == "Goblin") typeId = 2;
        else if (eName == "Orc") typeId = 3;

        Enemy* newEnemy = EnemyFactory::CreateEnemy(typeId, eX, eY);
        newEnemy->setHealth(eHp);
        enemies.push_back(newEnemy);
    }


    inFile.close();
    return true;
}