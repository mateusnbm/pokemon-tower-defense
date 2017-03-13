#ifndef LEVELLIBS_H_INCLUDED
#define LEVELLIBS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <allegro.h>
#include "MathLibs.h"

enum directions {

	top = 1,
	bottom = 2,
	left = 3,
	right = 4,
	vertical = 5,
	horizontal = 6

};

enum enemieTypes {

    eNormal  = 'N',
    eRSplash = 'R',
    eStrong  = 'S',
    eFast    = 'F',
    eSafer   = 'I'

};

enum towerTypes {

    tNormal = 'N',
    tSplash = 'S',
    tSlow   = 'L',
    tPoison = 'P',
    tBeacon = 'B'

};

typedef struct enemie {

	BITMAP *image;
	int imagePosX;
	int imagePosY;

	int movingImage;
	int movingImageTicks;

    int type;
    int level;
    int delay;

    float hp;
    float totalHp;
    float upgradeHp;
    float defense;
    float upgradeDefense;
    float speed;
    float upgradeSpeed;
    float maxSpeed;
    float refund;
    float upgradeRefund;

    float posX;
    float posY;

    float distanceWalked;

    int posAxis;

    int isMarked;
    int isSlower;

    int isPoisoned;
	int poisonDamage;

	int beaconRankNormal;
	int beaconRankSplash;
	int beaconRankSlow;
	int beaconRankPoison;

	int baseScore;

} Enemie;

typedef struct tower {

    BITMAP *image;
    int imagePosX;

    int type;
    int rank;
    int maxRank;
    int ticksPerFire;
    float slowTax;
    float damage;
    float damageUpgrade;
    float multipleDamage;
    float multipleDamageUpgrade;
    float selfRange;
    float multipleRange;
    float rangeUpgrade;
    float multipleRangeUpgrade;
    float price;
    float upgradePrice;
    float sellPrice;

    int posX;
    int posY;

    int showHUD;

    int fireTimer;
    int ticksForFire;

    Enemie *target;
    Enemie **slowTargets;
    int qntSlowTargets;

    int beaconEffect;
    int beaconRank;

    int towerAnimation;;

} Tower;

typedef struct axis {

	int posX;
	int posY;

	int line;
	int direction;

} Axis;

typedef struct bullet {

	int posX;
	int posY;

	int damage;

	float speed;

	int bulletColor;
	int bulletRadius;

	Tower *sender;
	int shallDivide;

	Enemie *target;

	struct bullet *nextBullet;

} Bullet;

Tower ***allocTowersMatrix(int i, int j);

void freeTower(Tower *tower);

Enemie **allocEnemiesMatrix(int i);

void loadLevel(int level, int ***groundMatrix, Enemie ***enemies, int *qntEnemies, int **qntEnemiesPerLine, BITMAP *enemyImage1[], BITMAP *enemyImage2[], BITMAP *enemyImage3[], BITMAP *enemyImage4[], BITMAP *enemyImage5[], int *qntLifes, int *qntMoney, int *qntRounds, Axis **groundAxis, int *qntGroundAxis);

void grabTileBlitPosition(int ***groundMatrix, int i, int j, int *posX, int *posY);

void drawGround(BITMAP **groundBitmap, int ***groundMatrix);

void drawTiledGround(BITMAP **tiledGround, int ***groundMatrix);

void drawTileBlink(int *auxBlinkCounter, int *auxBlinkLock, BITMAP *window,  int posX, int posY);

int positionAvailible(int **groundMatrix, Tower ***towers, float posX, float posY);

void placeTower(Tower ***towers,int type, int posX, int posY, int **qntTowersByRound, int index);

void drawRangeRadius(Tower ***towers, BITMAP *window);

void drawTowers(Tower ***towers, BITMAP *window, int budget, int *hudVisible);

void checkTowersHUD(Tower ***towers, BITMAP *window, int touchX, int touchY);

int checkClickedHUD(Tower ***towers, BITMAP *window, int touchX, int touchY, int *qntBudget, SAMPLE *levelUp, int *spentMoney);

void closeAllHUD(Tower ***towers);

void drawEnemies(BITMAP *window, Enemie **enemies, int qntEnemies, int *activeRound, int qntRoundEnemies, Axis *groundAxis, int qntAxis);

void checkEnemies (Enemie **enemies, int qntEnemies, int **groundMatrix, int *qntLifes, int *qntBudget, int *qntDeathEnemies, int *globalScore);

void targetEnemies(Tower ***towers, Enemie **enemies, int qntEnemies, Bullet **bullets, int *shootingPrefs);

void newBullet(Bullet **bullets, int posX, int posY, float damage, float speed, int bulletColor, int bulletRadius, Tower *sender, int shallDivide, Enemie *target);

void drawBullets(BITMAP *window, Bullet **bulletsAd, Enemie **enemies, int qntEnemies, SAMPLE *normalEffect, SAMPLE *splashEffect);

void drawSlows(BITMAP *window, Tower ***towers);

void poisonEnemies(Enemie **enemies, int qntEnemies);

void resetBeaconEffect(Tower ***towers);

#endif // LEVELLIBS_H_INCLUDED
