#include <iostream>
#include <cstdlib>
#include <ctime>

struct Entity {
    std::string name;
    int hp;
    int maxHp;
    int attackPower;
};

void displayBattleUI(const Entity& player, const Entity& enemy) {
    std::cout << "\n----------------------------------------\n";
    std::cout << player.name << " HP: " << player.hp << "/" << player.maxHp << "\n";
    std::cout << enemy.name << " HP: " << enemy.hp << "/" << enemy.maxHp << "\n";
    std::cout << "----------------------------------------\n";
}

void playerTurn(Entity& player, Entity& enemy) {
    std::cout << "Choose Action:\n";
    std::cout << "1. Light Slash (Guaranteed hit)\n";
    std::cout << "2. Heavy Strike (High damage, 50% accuracy)\n";
    std::cout << "3. Heal Spell (+20 HP)\n";
    std::cout << "Selection: ";

    int choice;
    std::cin >> choice;

    if (choice == 1) {
        int dmg = player.attackPower;
        enemy.hp -= dmg;
        std::cout << player.name << " used Light Slash for " << dmg << " damage!\n";
    } 
    else if (choice == 2) {
        if (rand() % 2 == 0) {
            int dmg = player.attackPower * 2;
            enemy.hp -= dmg;
            std::cout << "CRITICAL HIT! " << player.name << " dealt " << dmg << " damage!\n";
        } else {
            std::cout << player.name << " swung wildly and MISSED!\n";
        }
    } 
    else if (choice == 3) {
        player.hp += 20;
        if (player.hp > player.maxHp) player.hp = player.maxHp;
        std::cout << player.name << " healed 20 HP!\n";
    }
}

void enemyTurn(Entity& enemy, Entity& player) {
    if (enemy.hp <= 0) return;
    int dmg = 8 + (rand() % 6);
    player.hp -= dmg;
    std::cout << enemy.name << " attacked you back for " << dmg << " damage!\n";
}

int main() {
    srand(time(0));
    Entity hero = {"Kurt", 80, 80, 12};
    Entity goblin = {"Goblin Raider", 60, 60, 10};

    std::cout << "=== TURN-BASED TACTICAL COMBAT SIMULATOR ===\n";

    while (hero.hp > 0 && goblin.hp > 0) {
        displayBattleUI(hero, goblin);
        playerTurn(hero, goblin);
        if (goblin.hp < 0) goblin.hp = 0;
        enemyTurn(goblin, hero);
        if (hero.hp < 0) hero.hp = 0;
    }

    if (hero.hp > 0) std::cout << "\nVICTORY! You slew the " << goblin.name << "!\n";
    else std::cout << "\nDEFEAT! You were slain in battle, dweeb.\n";

    return 0;
}