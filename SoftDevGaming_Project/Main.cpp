//#include <iostream>
//#include "Map.h"
//#include "EnemyFactory.h"
//#include "Enemy.h"
//
//int main()
//{
//    std::cout << "Game: The Maze Runner\n\n";
//    int numRows = 10;
//    int numCols = 20;
//
//    Map map(numCols, numRows); //width x height
//    Item i("Sword", "Weapon", 's', 30);
//
//    map.ReplaceTile('P', 0, 0);
//    map.ReplaceTile('X', 19, 9);
//
//    std::cout << map;
//
//
//    // === TEST ENEMY FACTORY ===
//    cout << "\n=== Enemy Factory Test ===\n";
//
//    vector<EnemySpawnData> enemies = EnemyFactory::CreateEnemiesForLevel(1);
//
//    // Display enemies
//    for (const auto& e : enemies) {
//        cout << "Enemy: " << e.enemy->getName()
//            << " | HP: " << e.enemy->getHealth()
//            << " | ATK: " << e.enemy->getAttack()
//            << " | Pos: (" << e.x << "," << e.y << ")\n";
//    }
//
//    // Clean up dynamically allocated enemies
//    for (auto& e : enemies) {
//        delete e.enemy;
//        e.enemy = nullptr; // optional, safer
//    }
//
//    enemies.clear();
//    return 0;
//}

#include "GameManager.h"
#include <iostream>

int main()
{
    // Create the Game Manager
    // This calls the constructor, which sets up the Player and Map sizing
    GameManager game;

    // Initialize the Game
    // This sets up the grid, places the exit/treasure, and spawns enemies
    game.InitGame();

    // Start the Main Loop
    // This runs the game (Input -> Update -> Draw) until the player wins or dies
    game.MainLoop();

    // End of Program
    std::cout << "Thanks for playing!" << std::endl;
    return 0;
}