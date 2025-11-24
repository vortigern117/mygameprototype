#include <iostream>
#include <string>
#include <fstream>
#include <random>
#include <vector>
using namespace std;

struct Player 
{
    string name;
    int health = 100;
    int attack = 30;
    int defense = 20;
    int money = 50;
};

struct Goblin 
{
    int health = 35;
    int attack = 40;
    int defense = 10;
};

struct Item 
{
    string name;
};

int getRandNum(int min, int max) 
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(min, max);
    return dis(gen);
}

void gameLoop(Player &player, Goblin &goblin) 
{
    srand(static_cast<unsigned>(time(0)));

    auto encounterEnemy = [&]() 
    {
        cout << "Enemy Encontered, it's a Goblin!\n";
        string choice;
        cout << "Will you fight or run? ";
        cin >> choice;

        while (true) 
        {
            if (choice == "fight") 
            {
                cout << "YOUR TURN\n\n";
                cout << "Choose your action:\n";
                cout << "1. Attack\n";
                cout << "2. Defend\n";
                cout << "3. View Enemy Stats\n";
                int action;
                cin >> action;

                bool goblinDefending = false;
                switch(action) 
                {
                    case 1: {
                        cout << "You attack!\n";
                        int damage = getRandNum(10, 15);
                        cout << "Your sword deals " << damage << " dmg, successful hit!\n";
                        goblin.health -= damage;
                        if (goblin.health <= 0) 
                        {
                            cout << "You win!\n";
                            return;
                        }
                        if (goblinDefending) 
                        {
                            int damage = getRandNum(5, 7.5);
                            goblin.health -= damage;
                            if (goblin.health <= 0) { cout << "You win.\n"; }
                        }
                        break;
                    }
                    
                    case 2: 
                    {
                        cout << "You defend\n";
                        int defendDamage = getRandNum(20, 25);
                        cout << "Because you defended, the goblin only deals " << defendDamage << " dmg!\n";
                        player.health -= defendDamage;
                        if (player.health <= 0) 
                        {
                            cout << "Game over";
                            return;
                        }
                        break;
                    }

                    case 3: 
                    {
                        cout << "Health: " << goblin.health << endl;
                        cout << "Attack: " << goblin.attack << endl;
                        cout << "Defense: " << goblin.defense << endl;
                        break;
                    }
                } //end of switch statement

                //what the goblin does if the player attacks (option 1)
                if (action == 1) 
                {
                    cout << "ENEMY TURN\n\n";
                    int decision = rand() % 2 + 1;
                    if (decision == 1) 
                    {
                        cout << "The goblin attacks\n";
                        int goblinDamage = getRandNum(30, 40);
                        player.health -= goblinDamage;
                        cout << "You took " << goblinDamage << " damage\n";
                        if (player.health <= 0) 
                        {
                            cout << "Game over.\n";
                            return;
                        }
                    }
                    else if (decision == 2) 
                    {
                        cout << "The goblin defends\n";
                        bool goblinDefending = true;
                    }
                }

                //what the goblin does if the player defends (option 2)
                else if (action == 2) 
                {
                    cout << "ENEMY TURN\n\n";
                    int goblinAttack = getRandNum(15, 25);
                    cout << "The goblin attacks\n";
                    player.health -= goblinAttack;
                    if (player.health <= 0) 
                    {
                        cout << "Game over";
                        return;
                    }
                }
            }
            else if (choice == "run") 
            {
                cout << "You chose to flee\n";
                int chance = rand() % 5 + 1;

                if (chance == 3) 
                {
                    cout << "You successfully flee\n";
                    break;
                }
                else 
                {
                    cout << "You failed to flee\n";
                    //code for the enemies turn here
                }
            }
        }
    }; //end of enemy encounter code

    auto encounterVillage = [&]() 
    {
        string choice;
        cout << "You came across a village, will you enter it?\n";
        cout << "Yes\n";
        cout << "No\n";
        cout << "";
        cin >> choice;

        while(true) 
        {
            if (choice == "yes") 
            {
                int location;
                cout << "Where would you like to go?\n";
                cout << "1. Town Square\n";
                cout << "2. Markets\n";
                cout << "3. Inn\n";
                cout << "4. Shops\n";
                cout << "5. City Hall\n";
                cout << "6. Resedential District\n";
                cout << "7. Leave\n";
                cout << "";
                cin >> location;

                switch(location) 
                {
                    case 1: 
                    {
                        cout << "You arrive at the town square";
                    } //end of town square code

                    case 2: 
                    {
                        cout << "You arrive at the markets";
                    } //end of markets code

                    case 3: 
                    {
                        cout << "You arrive at the Inn's\n";
                        string decision;
                        cout << "You can choose to spend the night here for a small fee, replenishing your health. Would you like to spend the night here?\n";
                        cout << "";
                        cin >> decision;
                        if (decision == "yes") 
                        {
                            if (player.money >= 10) 
                            {
                                cout << "You have a fruitful rest, and are feeling rejuvinated. Your health has been fully restored!\n";
                                player.health = 100;
                                player.money -= 10;
                                break;
                            }
                        }

                        else if (decision == "no") 
                        {
                            string returnOrLeave;
                            cout << "Would you like to return to the town, or to leave it?\n";
                            cout << "";
                            cin >> returnOrLeave;
                            if (returnOrLeave  == "return") { return; }
                            
                            else { break; }

                        }
                    } // end of Inn code

                    case 4: 
                    {
                        cout << "You arrive at the shops. It's a bustling scene of people coming and going, chatting and wandering in groups.\n";
                        int shopChoice;
                        cout << "The shops that you could go to are:\n";
                        cout << "1. The weapons shop\n" << "2. The armour shop\n" << "3. The items shop\n" << "Where will you go?\n";
                        cout << "";
                        cin >> shopChoice;
                        switch(shopChoice) 
                        {
                            case 1: 
                            {
                                cout << "You enter the armour store. Various bits of armour line the shelves.\n";
                                cout << "You can buy:\n" << "1. Helmets\n" << "2. Body armour\n" << "3. Leg armour.\n";
                                int armourChoice;
                                cout << "";
                                cin >> armourChoice;
                                
                                switch(armourChoice) 
                                {
                                    case 1:  
                                    {
                                        cout << "You can buy:\n";
                                        cout << "Helmet1 - Defense 20, Cost 20\n";
                                        cout << "Helmet2 - Defense 40, Cost 30\n";
                                        cout << "Helmet3 - Defense 60, Cost 50\n";
                                    } //end of helmet code

                                    case 2: 
                                    {
                                        cout << "You can buy:\n";
                                        cout << "Armour1 - Defense 50, Cost 20\n";
                                        cout << "Armour2 - Defense 70, Cost 30\n";
                                        cout << "Armour3 - Defense 100, Cost 50\n";
                                    } //end of body armour code

                                    case 3: 
                                    {
                                        cout << "You can buy:\n";
                                        cout << "Leggings1 - Speed 10, Cost 20\n";
                                        cout << "Leggings2 - Speed 20, Cost 30\n";
                                        cout << "Leggings3 - Speed 40, Cost 40\n";
                                    } //end of leg armour code
                                } //end of armour code - REMEMBER FOR LATER - add a money check (and increase defense)
                            }
                            
                            case 2: 
                            {
                                cout << "The weapons store\n";
                                cout << "The weapons that you can buy are:\n";
                                cout << "Weapon1 - Attack 30, Cost 20";
                                cout << "Weapon2 - Attack 50, Cost 40";
                                cout << "Weapon3 - Attack 70, Cost 50";
                                //add the switch statement later
                            }
                            
                            case 3: 
                            {
                                cout << "Item store\n";
                                cout << "The items that you can buy are:\n";
                                cout << "Potions\n";
                                cout << "Books\n";
                                cout << "Accessories\n";
                                string itemDecision;
                                cout << "";
                                cin >> itemDecision;

                                if (itemDecision == "potions") 
                                {
                                    cout << "potion1 - cost 10\n";
                                    cout << "potion2 - cost 20\n";
                                    cout << "potion3 - cost 30\n";
                                    int potionBuy;
                                    cout << "";
                                    cin >> potionBuy;
                                }
                                //BIG THINGS HAPPENING! for any of the things that you buy, make them part an instance of the Item construct and add them to the inventory
                            }
                        }
                        //obviously weapons increase attack and armour increases defense. dont know about items theres not even an inventory
                    } //end of shops code

                    case 5: 
                    {
                        cout << "You arrive at the city hall";
                    } //end of city hall code

                    case 6: 
                    {
                        cout << "You arrive at the resedential district";
                    } //end of resedential district code

                    case 7: 
                    {
                        cout << "You continue on your journey";
                        return;
                    } //end of leaving code
                } //end of switch statement
            }

            else 
            {
                cout << "You continue on your journey.\n";
                break;
            }
        }
    }; //end of village code

    auto rest = [&]() 
    {
        cout << "You come across a small, quite, peaceful cave. There's no danger around, and nobody to be seen. Would you like to take a rest here?\n";
        string restDeision;
        cout << "";
        cin >> restDeision;
        if (restDeision == "yes") 
        {
            cout << "The atmosphere was so peaceful that you ended up falling asleep, although due to the safety of the area, no harm befell you.\n";
            cout << "Your health has been fully restord!\n";
            player.health = 100;
            return;
        }
        else 
        {
            cout << "You continue on your journey";
            return;
        }
    }; //end of rest code

    bool gameRunning = true;
    while (gameRunning) 
    {
        int action = rand() % 3 + 1;

        switch(action) 
        {
            case 1:
                encounterEnemy();
                break;
            
            case 2:
                encounterVillage();
                break;
            
            case 3:
                rest();
                break;
        }
    }
}

void addItemToInv() 
{
    //placeholder
}

void inventory(vector<string>& inventory, size_t maxInvSize) 
{
    for (const auto& item : inventory) 
    {
        cout << item;
    }
}

void readFromFile() 
{
    //placeholder
}

void writeToFile() 
{
    //placeholder
}

void menu() 
{
    cout << "1. Conintue Game\n";
    cout << "2. New Game\n";
    cout << "3. Load\n";
    cout << "4. Quit\n";
}

int choiceInput() 
{
    int choice;
    cout << "";
    cin >> choice;
    return choice;
}

void continue_game() 
{
    //if (file.empty()) {
        //cout << "No save game exists. Please start a new game.";
    //}
    //else {
        //code for reading from file here
        //gameLoop(player, goblin);
    //}
}

void new_game(Player &player, Goblin &goblin) 
{
    cout << "Welcome\n";
    cout << "Pick a name: ";
    cin >> player.name;
    cout << "Welcome, " << player.name;
    cout << "\nThe objective of this game is to something, i havent thought of it yet. some super simple rpg stuff\n\n";
    gameLoop(player, goblin);
}

void load() 
{
    //placeholder
    //maybe display a list of files here? dont know how, but maybe figure it out down the line
}

void quit() { exit(0); }

int main() 
{
    Player player;
    Goblin goblin;
    vector<string> inventory;
    const size_t maxInvSize = 10;

    while(true) 
    {
        int choice;
        menu();
        cin >> choice;

        switch(choice) 
        {
            case 1:
                continue_game();
                cout << "\n";
                break;
            
            case 2:
                new_game(player, goblin);
                cout << "\n";
                break;
            
            case 3:
                load();
                cout << "\n";
                break;
            
            case 4:
                quit();
                cout << "\n";
                break;
        }
    }
    return 0;
}