#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <string>
#define EMPTY ' '
#define WALL '#'
#define PLAYER 1
#define TREASURE 'T'

using namespace std;

const int sizeY = 47;
const int sizeX = 150;

int playerX;
int playerY;

char map[47][150] = {
	"#####################################################################################################################################################",
	"#                                                             #######                                                                               #",
	"#                                                             #     #                                                                               #",
	"#                                                             #     #                                                                               #",
	"#                                                             #     #                                                                               #",
	"#                                           ######            #     #                                                                               #",
	"#                                           #    #            #     ###################################################    #######################  #",
	"#############################################    #            #                                                       #    #                     #  #",
	"#  WIJONO             MUS                        #            #                                                       #    #                     #  #",
	"#############################################    ##############      #########################     ###############    ######    ############     #  #",
	"#                    #    #                  #                       #                       #     #             #              #          #     #  #",
	"#                    #    #                  #                       #                       #     #             #              #          #     #  #",
	"#                    #    #                  #########################    ################## #     #             #              #          #     #  #",
	"#                   #     #                                               #                # #     #             ################          #     #  #",
	"#                  #     #                                                #                # #     #                                       #     #  #",
	"#                 #     #    ####                                         #######    ####### #     #                                       #     #  #",
	"#            #####     #     #  #                                               #   #        #     #                        ################     #  #",
	"#            #         #     #  #                                               #   #        #     #                        #                    #  #",
	"#            ###########     #  #                              #################    #        #     #                        #                    #  #",
	"#                            #  #                              #                    #        #     #                        #    #################  #",
	"#                            #  #                              #                    #        #     #    #####################    #                  #",
	"#                            #  #                              #     ##########     #        #     #    #                        #                  #",
	"#                            #  #                              #     #        #     ##########     #    #     ###################                   #",
	"#                            #  #                              #     #        #                    #     #     #                                    #",
	"#                            #  ##                             #     #        ######################      #     ################                    #",
	"#                            ##   ##                           #     #                      ##########    #                    #                    #",
	"#                              ##   ####################################################    #        #    #############        #                    #",
	"#                                ##                                               T    #    #   ###  #                #        #                    #",
	"#                                  #     #######################      ##################    #   # #  #                #        #                    #",
	"#        ###########               #     #                     #      #                     #   # #  ##################        #                    #",
	"#       #           #              #     #                     #      #######################   # #                            #                    #",
	"#      #             #             #     #                     #                                #  ########    #################                    #",
	"#######    #####      #            #     #                     ##################################         #    #                                    #",
	"#Start    #     #      #           #     #                                                                #    #                                    #",
	"#      ###     #      #            #     #             ################################                ####    ######                               #",
	"#######         #     #            #     #             #                              #                #            #                               #",
	"#                #     #           #     #             #   #############    ###########                ##############                               #",
	"#                 #     ############     ###############   #           #    #                                                                       #",
	"#                  #                                       #           #    #                                                                       #",
	"#                  #    ################################   #           #    #                                                                       #",
	"#                  #    #                              #   #############    #                                                                       #",
	"#                  #    #                              #                    #                                                                       #",
	"#                  #    #                              ######################                                                                       #",
	"#                  #    #                                                                                                                           #",
	"#                  #    #                                                                                                                           #",
	"#####################################################################################################################################################"
};

void gotoxy(int x, int y){
	COORD c = {x, y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void cls(){
	for (int i = 0; i < 70; i++) cout << endl;
}

class Model{
protected:
	string name;
	string dialogue;
	int attack;
	int defense;
	int hp;
public:
	void setName(string name){
		this->name = name;
	}
	string getName(){
		return this->name;
	}
	void setDialogue(string dialogue){
		this->dialogue = dialogue;
	}
	string getDialogue(){
		return this->dialogue;
	}
	void setAttack(int attack){
		this->attack = attack;
	}
	int getAttack(){
		return this->attack;
	}
	void setDefense(int defense){
		this->defense = defense;
	}
	int getDefense(){
		return this->defense;
	}
	void setHp(int hp){
		this->hp = hp;
	}
	int getHp(){
		return this->hp;
	}
};

class Enemy : public Model{
private:
	int index;
public:
	void setIndex(int index){
		this->index = index;
	}
	int getIndex(){
		return this->index;
	}
};

class Player : public Model{
private:
	int healingSalve;
	bool win;
public:
	Player(){
		healingSalve = 3;
		win = false;
	}

	void useHealingSalve(int &currHp){
		if (healingSalve > 0){
			if(currHp == hp){
				cout << "Your hp is full, cannot use it in this time";
			}
			else if (currHp + healingSalve >= hp){
				currHp = hp;
				healingSalve--;
				cout << healingSalve << " healing salve(s) remaining" << endl;
			}
			else{
				currHp = currHp + 100;
				healingSalve--;
				cout << healingSalve << " healing salve(s) remaining" << endl;
			}
			cin.get();
		}
		else{
			cout << "You don't have healing salve";
			cin.get();
		}
	}
	
	void setWin(bool win){
		this->win = win;
	}

	bool getWin(){
		return this->win;
	}
};

class Treasure{
protected:
	int x;
	int y;
	int index;
public:
	virtual void foundTreasure() = 0;
	int getX(){
		return this->x;
	}
	int getY(){
		return this->y;
	}
	void setCoord(int x, int y, int index){
		this->x = x;
		this->y = y;
		this->index = index;
	}
};

class FakeTreasure : public Treasure{
public:
	void foundTreasure(){
		cls();
		cout << "You found fake treasure !!!" << endl;
		cout << "Better lucky next time";
		cin.get();
	}
};

class RealTreasure : public Treasure{
private:
	int hp;
	int attack;
	int defense;
public:
	void foundTreasure(Player player){
		cls();
		cout << "You found treasure !!!" << endl;
		player.setHp(player.getHp() + hp);
		cout << " Your hp + " << hp << endl;
		player.setAttack(player.getAttack() + attack);
		cout << " Your attack + " << attack << endl;
		player.setDefense(player.getDefense() + defense);
		cout << " Your defense + " << defense << endl;
	}

};

FakeTreasure fakeTreasure[4];

void createTreasure(){
	//map[y][x]
	fakeTreasure[0].setCoord(65, 2, 1);
	map[fakeTreasure[0].getY()][fakeTreasure[0].getX()]= TREASURE;
	map[13][82] = TREASURE;
	map[16][31] = TREASURE;
	map[17][15] = TREASURE;
	map[27][82] = TREASURE;
	map[35][84] = TREASURE;
	map[44][22] = TREASURE;
}

void viewMap(){
	createTreasure();
	gotoxy(0,0);
	for (int i = 0; i < sizeY; i++){
		for (int j = 0; j < sizeX; j++){
			cout << map[i][j];
		}
		cout << endl;
	}
	gotoxy(playerX+1, playerY);
}

void showHpBar(int currHp, int hp){
	float barCount = 0;

	barCount = ((float)currHp / (float)hp) * 20;

	cout << "[";
	for (int i = 0; i < barCount; i++){
		cout << (char) 177;
	}
	for (int i = 0; i < 20 - barCount; i++){
		cout << (char)176;
	}
	cout << "]";
}

int attackEnemy(Model attacker, Model attacked){
	int random = rand() % 26 + 50;
	int attackDamage = (float)((attacker.getAttack() / attacked.getDefense() * attacker.getAttack()) + 2) * ((float) random / (float) 100);
	return attackDamage;
}

void showDialogue(Player player, Enemy enemy){
	system("cls");
	cls();
	cout << player.getName() << endl;;
	for (int i = 0; i < player.getDialogue().length(); i++){
		Sleep(50);
		cout << player.getDialogue()[i];
	}
	cout << endl << endl;
	cout << enemy.getName() << endl;;
	for (int i = 0; i < enemy.getDialogue().length(); i++){
		Sleep(50);
		cout << enemy.getDialogue()[i];
	}
	cout << endl << endl;
	system("pause");
}

Enemy soraka, visage, angela;

Player player;


bool foundNormalEnemy(){
	int enemyOut;
	int currEnemyHp = 0;
	int currPlayerHp = 0;
	int playerDamage = 0;
	int enemyDamage = 0;
	int choose;
	int random;
	bool end = false;
	bool gameEnd = false;
	Enemy enemy;
	
	enemyOut = rand()%3 + 1;
	if (enemyOut == 1) enemy = soraka;
	else if (enemyOut == 2) enemy = visage;
	else enemy = angela;

	currEnemyHp = enemy.getHp();
	currPlayerHp = player.getHp();
	showDialogue(player, enemy);
	do{
		system("cls");
		cls();
		cout << "                                                                      " << enemy.getName() << endl;
		cout << "                                                                      " << enemy.getHp(); showHpBar(currEnemyHp, enemy.getHp()); cout << currEnemyHp << endl;
		cout << player.getName() << endl;
		cout << player.getHp() ; showHpBar(currPlayerHp, player.getHp()); cout << currPlayerHp << endl;

		do{
			cout << endl << endl << endl;
			cout << "1. Attack" << endl;
			cout << "2. Use Healing Salve" << endl;
			cout << "3. Escape" << endl;
			cout << ">> ";
			cin >> choose; cin.clear(); cin.sync();
		} while(choose < 1 || choose > 3);

		switch(choose){
		case 1:
			cout << "You turn to attack" << endl;
			Sleep(1000);
			playerDamage = attackEnemy(player, enemy);
			currEnemyHp -= playerDamage;
			cout << "You just hit enemy with " << playerDamage << " damage(s)" << endl;
			Sleep(1000);
			cout << "Enemy turn to attack" << endl;
			Sleep(1000);
			enemyDamage = attackEnemy(enemy, player);
			currPlayerHp -= enemyDamage;
			cout << "Enemy just hit you with " << enemyDamage << " damage(s)" << endl;
			Sleep(1000);
			break;
		case 2:
			player.useHealingSalve(currPlayerHp);
			break;
		case 3:
			end = true;
			player.setWin(false);
			cout << "You success escape"<<endl;
			system("pause");
			return gameEnd = false;
			break;
		}

		if (currEnemyHp <= 0){
			cout << "You Win" << endl;
			end = true;
			gameEnd = false;
			player.setWin(true);
			system("pause");
		}
		else if (currPlayerHp <= 0){
			cout << "You Lose" << endl;
			end = true;
			gameEnd = true;
			player.setWin(false);
			system("pause");
		}
	} while(end == false);
	return gameEnd;
}

void createEnemyStatus(){
	//Soraka
	soraka.setName("Soraka");
	soraka.setDialogue("Yes, that was a banana. *giggles* No one expects the banana.");
	soraka.setAttack(30);
	soraka.setDefense(30);
	soraka.setHp(80);
	soraka.setIndex(1);
	
	//Visage
	visage.setName("Visage");
	visage.setDialogue("That which passes beyond the veil must forever stay.");
	visage.setAttack(100);
	visage.setDefense(100);
	visage.setHp(150);
	visage.setIndex(2);

	//Angela
	angela.setName("Angela");
	angela.setDialogue("Kiki kaka! The strings of my puppet got tangled up... can you help me with that?");
	angela.setAttack(65);
	angela.setDefense(50);
	angela.setHp(110);
	angela.setIndex(3);
}

bool move(int x, int y){
	if (map[playerY + y][playerX + x] == EMPTY){
		gotoxy(playerX, playerY);
		cout << " ";
		map[playerY][playerX] = EMPTY;
		playerX += x;
		playerY += y;
		map[playerY][playerX] = PLAYER;
		gotoxy(playerX, playerY);
		cout << (char)PLAYER;
		return false;
	}
	else if(map[playerY + y][playerX + x] == TREASURE){
		bool check = foundNormalEnemy();
		if (check == false){
			if (player.getWin() == true){
				map[playerY][playerX] = EMPTY;
				playerY += y;
				playerX += x;
				map[playerY][playerX] = PLAYER;
				system("cls");
				viewMap();
				gotoxy(playerX, playerY);
				cout << (char)PLAYER;
			}
			else{
				system("cls");
				viewMap();
			}
		}
		return check;
	}
	else{
		return false;
	}
}

void createPlayer(){
	playerX = 1;
	playerY = 34;
	map[playerY][playerX] = 1;
	player.setName("Niki");
	player.setDialogue("Today we fight each other. Tomorrow, we may fight together");
	player.setAttack(999);
	player.setDefense(999);
	player.setHp(999);
}

void play(){
	char player;
	bool end = false;
	createPlayer();
	createEnemyStatus();
	viewMap();

	while (end == false){
		switch(player = getch()){
		case 'w':
		case 'W':
		case 72:
			end = move(0, -1);
			break;
		case 'a':
		case 'A':
		case 75:
			end = move(-1, 0);
			break;
		case 's':
		case 'S':
		case 80:
			end = move(0, 1);
			break;
		case 'd':
		case 'D':
		case 77:
			end = move(1, 0);
			break;
		case 27:
			end = true;
		}
	}
}

void finalFuntasticLogo(){
	gotoxy(30, 30);
	Sleep(100);
	cout << " _______  _                _     _______                                           _        " << endl;
	Sleep(100);
	gotoxy(30, 31);
	cout << "(_______)(_)              | |   (_______)                 _                   _   (_)       " << endl;
	Sleep(100);
	gotoxy(30, 32);
	cout << " _____    _  ____   _____ | |    _____    _   _  ____   _| |_  _____   ___  _| |_  _   ____ " << endl;
	Sleep(100);
	gotoxy(30, 33);
	cout << "|  ___)  | ||  _ \\ (____ || |   |  ___)  | | | ||  _ \\ (_   _)(____ | /___)(_   _)| | / ___)" << endl;
	Sleep(100);
	gotoxy(30, 34);
	cout << "| |      | || | | |/ ___ || |   | |      | |_| || | | |  | |_ / ___ ||___ |  | |_ | |( (___ " << endl;
	Sleep(100);
	gotoxy(30, 35);
	cout << "|_|      |_||_| |_|\\_____| \\_)  |_|      |____/ |_| |_|   \\__)\\_____|(___/    \\__)|_| \\____)" << endl;
	Sleep(100);
	gotoxy(47, 39);
	system("pause");

}

void loadingScreen(){
	gotoxy(77, 33);
	cout << "LOADING";
	for (int i = 0; i < 3; i++){
		gotoxy(80, 26);
		cout << (char) 3;
		Sleep(500);
		gotoxy(80, 26);
		cout << " ";
		gotoxy(85, 33);
		cout << (char) 5;
		Sleep(500);
		gotoxy(85, 33);
		cout << " ";
		gotoxy(80, 40);
		cout << (char) 6;
		Sleep(500);
		gotoxy(80, 40);
		cout << " ";
		gotoxy(75, 33);
		cout << (char) 4;
		Sleep(500);
		gotoxy(75, 33);
		cout << " ";
	}
}

void setIntro(){
	system("title Final Funtastic");
	CONSOLE_FULLSCREEN_MODE;
	gotoxy(45, 30);
	cout << "for play this game, please use fullscreen mode (alt + enter) and Raster font";
	::SendMessage(::GetConsoleWindow(), WM_SYSKEYDOWN, VK_RETURN, 0x20000000);
	Sleep(5000);
	system("cls");
	loadingScreen();
	system("cls");
	finalFuntasticLogo();
}

void help(){
	
}

void exit(){
	system("cls");
	cls();
	Sleep(50);cout << " ######## ##     ##    ###    ##    ## ##    ##    ##    ##  #######  ##     ##" << endl; 
	Sleep(50);cout << "    ##    ##     ##   ## ##   ###   ## ##   ##      ##  ##  ##     ## ##     ##" << endl; 
	Sleep(50);cout << "    ##    ##     ##  ##   ##  ####  ## ##  ##        ####   ##     ## ##     ##" << endl;
	Sleep(50);cout << "    ##    ######### ##     ## ## ## ## #####          ##    ##     ## ##     ##" << endl; 
	Sleep(50);cout << "    ##    ##     ## ######### ##  #### ##  ##         ##    ##     ## ##     ##" << endl; 
	Sleep(50);cout << "    ##    ##     ## ##     ## ##   ### ##   ##        ##    ##     ## ##     ##" << endl; 
	Sleep(50);cout << "    ##    ##     ## ##     ## ##    ## ##    ##       ##     #######   ####### " << endl <<endl;        

	
	Sleep(1000);
	system("cls");
	cout << "\n\n\n\n\n\n\n\n\n\n";
	gotoxy(20,10);Sleep(500);cout << "Create By:" << endl <<endl;
	gotoxy(20,12);Sleep(500);cout << "Kevin Nicky Setiawan 2101635076" << endl <<endl;
	gotoxy(20,14);Sleep(500);cout << "Eldwin Dylan Kusnadi 2101643714" << endl <<endl;
	gotoxy(20,16);Sleep(500);cout << "Kevin Axellino Triantio 2101720631" << endl <<endl;
	gotoxy(20,18);Sleep(500);cout << "Vivaldy Augusta MI 2101642680" << endl <<endl;
	gotoxy(20,25);system("pause");
}

void menu(){
	int opt;
	do{
		system("cls");
		cls();
		cout << "1. Play" << endl;
		cout << "2. Help" << endl;
		cout << "3. Exit" << endl;
		cout << ">> ";
		cin >> opt; cin.clear(); cin.sync();
		switch(opt){
		case 1:
			play();
			break;
		case 2:
			help();
			break;
		case 3:
			exit();
			break;
		}
	} while(opt != 3);
}

int main(){
	setIntro();
	menu();
	
	return 0;
}