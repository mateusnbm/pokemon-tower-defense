#include "MemoryLibs.h"

#define true 1
#define false 0

int **allocIntegerMatrix (int i, int j) {

    int aux;

    int **matrix;

    matrix = (int **) calloc(i, sizeof(int *));

    for (aux = 0; aux < i; aux++) {

        matrix[aux] = (int *) calloc(j, sizeof(int));

    }

    return matrix;

}

char *composeFilePath(char path[], char *baseName){

	int aux = 0, index = 0;

	int pathLen = strlen(path);

	int baseLen = strlen(baseName);

	char *mainPath = (char *) malloc((pathLen+baseLen+5)*sizeof(char));

	for (aux = 0; aux<pathLen; aux++){

		mainPath[index+aux] = path[aux];

	}

	index += pathLen;

	for (aux = 0; aux<baseLen; aux++){

		mainPath[index+aux] = baseName[aux];

	}

	index += baseLen;

	mainPath[index] = '.';
	mainPath[index+1] = 't';
	mainPath[index+2] = 'x';
	mainPath[index+3] = 't';
	mainPath[index+4] = '\0';

	return mainPath;

}

void produceOutLog(int victory, int currentRound, int qntRounds, int *enemiesCounter, int spentMoney, int money, int lifes, int **towersByRound){

	int auxI,auxII;

	FILE *logFile = fopen("LOG.out", "w+");

	if (victory == true){

		fprintf(logFile, "O jogador venceu!\n");

	}else{

		fprintf(logFile, "O jogador perdeu!\n");

	}

	fprintf(logFile ,"%i\n", currentRound);

	fprintf(logFile, "N:%i\n",enemiesCounter[0]);
	fprintf(logFile, "R:%i\n",enemiesCounter[1]);
	fprintf(logFile, "S:%i\n",enemiesCounter[2]);
	fprintf(logFile, "F:%i\n",enemiesCounter[3]);
	fprintf(logFile, "I:%i\n",enemiesCounter[4]);

	fprintf(logFile, "%i\n", spentMoney);

	fprintf(logFile, "%i\n", money);

	fprintf(logFile, "%i\n", lifes);

	for (auxI = 0; auxI < 5; auxI++){

		for (auxII = 0; auxII < qntRounds; auxII++){

			fprintf(logFile ,"%i	", towersByRound[auxII][auxI]);

		}

		fprintf(logFile, "\n");

	}

	fclose(logFile);

}

void produceNewUserFile(char *username, User *usrLogs){

	FILE *userFile = fopen(composeFilePath("Users/", username), "w+");

	if (userFile != NULL){

		usrLogs->scoreLvM = 0;
		usrLogs->scoreLv1 = 0;
		usrLogs->scoreLv2 = 0;
		usrLogs->scoreLv3 = 0;
		usrLogs->scoreLv4 = 0;
		usrLogs->scoreLv5 = 0;
		usrLogs->scoreLv6 = 0;

		fprintf(userFile, "%s\n",username);
		fprintf(userFile, "0\n");
		fprintf(userFile, "0\n");
		fprintf(userFile, "0\n");
		fprintf(userFile, "0\n");
		fprintf(userFile, "0\n");
		fprintf(userFile, "0\n");
		fprintf(userFile, "0\n");

	}

	fclose(userFile);

}

void loadUserFromFile(char *username,User *usrLogs){

	FILE *userFile = fopen(composeFilePath("Users/", username), "r");

	if (userFile != NULL){

		fscanf(userFile, "%s", usrLogs->username);
		fscanf(userFile, "%i", &usrLogs->scoreLvM);
		fscanf(userFile, "%i", &usrLogs->scoreLv1);
		fscanf(userFile, "%i", &usrLogs->scoreLv2);
		fscanf(userFile, "%i", &usrLogs->scoreLv3);
		fscanf(userFile, "%i", &usrLogs->scoreLv4);
		fscanf(userFile, "%i", &usrLogs->scoreLv5);
		fscanf(userFile, "%i", &usrLogs->scoreLv6);

	}

	fclose(userFile);

}

void loadMainUser(User *userLogs){

	char *mainUsername = (char *) malloc(25*sizeof(char));

	FILE *prefsFile = fopen("Users/preferences.txt", "r");

	FILE *userFile = NULL;

	fscanf(prefsFile, "%s", mainUsername);

	userLogs->username = mainUsername;

	userFile = fopen(composeFilePath("Users/", mainUsername), "r");

	if (userFile == NULL){

		produceNewUserFile(mainUsername, userLogs);

	}else{

		loadUserFromFile(mainUsername, userLogs);

	}

	fclose(prefsFile);

	fclose(userFile);

}

void updateMainUser(User *userLogs){

	FILE *userFile = fopen(composeFilePath("Users/", userLogs->username), "w+");

	fprintf(userFile, "%s\n",userLogs->username);
	fprintf(userFile, "%i\n",userLogs->scoreLvM);
	fprintf(userFile, "%i\n",userLogs->scoreLv1);
	fprintf(userFile, "%i\n",userLogs->scoreLv2);
	fprintf(userFile, "%i\n",userLogs->scoreLv3);
	fprintf(userFile, "%i\n",userLogs->scoreLv4);
	fprintf(userFile, "%i\n",userLogs->scoreLv5);
	fprintf(userFile, "%i\n",userLogs->scoreLv6);

	fclose(userFile);

}

void alterMainuser(char *username, User *userLogs){

	FILE *prefsFile = fopen("Users/preferences.txt", "w+");

	updateMainUser(userLogs);

	fprintf(prefsFile, "%s", username);

	fclose(prefsFile);

	loadMainUser(userLogs);

}

char *getCurrentUser(){

	char *mainUsername = (char *) malloc(25*sizeof(char));

	FILE *prefsFile = fopen("Users/preferences.txt", "r");

	fscanf(prefsFile, "%s", mainUsername);

	return mainUsername;

}

//

int verifyUserExistence(char *username){

	int fileExists = false;

	FILE *userFile = fopen(composeFilePath("Users/", username), "r");

	if (userFile != NULL){

		fileExists = true;

	}

	fclose(userFile);

	return fileExists;

}

void updateUserFile(User *usrLogs){}

//
