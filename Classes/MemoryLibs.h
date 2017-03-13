#ifndef MEMORYLIBS_H_INCLUDED
#define MEMORYLIBS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct user {

	char *username;
	int scoreLvM;
	int scoreLv1;
	int scoreLv2;
	int scoreLv3;
	int scoreLv4;
	int scoreLv5;
	int scoreLv6;

} User;

int **allocIntegerMatrix (int i, int j);

void produceOutLog(int victory, int currentRound, int qntRounds, int *enemiesCounter, int spentMoney, int money, int lifes, int **towersByRound);

void produceNewUserFile(char *username, User *usrLogs);

void loadUserFromFile(char *username, User *usrLogs);

void loadMainUser(User *userLogs);

void updateMainUser(User *userLogs);

void alterMainuser(char *username, User *userLogs);

char *getCurrentUser();

//

int verifyUserExistence(char *username);

void updateUserFile(User *usrLogs);

#endif // MEMORYLIBS_H_INCLUDED
