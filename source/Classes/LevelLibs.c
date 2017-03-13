#include "LevelLibs.h"

#define true 1
#define false 0

#define roundTransitionDelay 30

Tower ***allocTowersMatrix(int i, int j) {

	int auxI,auxII;

    Tower ***matrix;

    matrix = (Tower ***) malloc(i * sizeof(Tower **));

    for (auxI = 0; auxI < i; auxI++) {

        matrix[auxI] = (Tower **) malloc(j * sizeof(Tower *));

        for (auxII = 0; auxII < j; auxII++) {

        	matrix[auxI][auxII] = NULL;

        }

    }

    return matrix;

}

void freeTower(Tower *tower) {

	destroy_bitmap(tower->image);

	free(tower);

}

Enemie **allocEnemiesMatrix(int i) {

	int aux;

	Enemie **matrix;

	matrix = (Enemie **) malloc(i * sizeof(Enemie *));

	for (aux = 0; aux < i; aux++) {

		matrix[aux] = (Enemie *) malloc(sizeof(Enemie));

	}

	return matrix;

}

void loadLevel(int level, int ***groundMatrix, Enemie ***enemies, int *qntEnemies, int **qntEnemiesPerLine, BITMAP *enemyImage1[], BITMAP *enemyImage2[], BITMAP *enemyImage3[], BITMAP *enemyImage4[], BITMAP *enemyImage5[], int *qntLifes, int *qntMoney, int *qntRounds, Axis **groundAxis, int *qntGroundAxis) {

	int auxI, auxII;

	/* Acessamos o arquivo contendo as informacoes do level */

	FILE *levelFile = NULL;

    if (level == 0){

    	levelFile = fopen("entrada.in", "r");

    }else{

    	char levelPath[19] = "Levels/level_0.txt";
		levelPath[13] = level + '0';
		levelFile = fopen(levelPath, "r");

    }

    /* Auxiliares na determinacao dos eixos de coordenadas */

    Axis *newAxis = NULL;

    int qntAxis = 0,qntPaths = 0,cameDirection = 0,currentDirection = 0,lastDirection = 0,initialTileI = 0,initialTileJ = 0,tileLocker = 0;

    /* Auxiliares na leitura dos inimigos */

    Enemie **newEnemies = NULL;

    int *enemiesPerLine = NULL;

    char enemyType;
    int enemyLevel;
    int enemyDelay;
    int qntEnemiesCounter = 0;
    long bytesRead;

    float initialPosX;
    float initialPosY;

	int imageRandomizer;
    BITMAP *image;
    int imagePosX;
    int imagePosY;

    float hp;
    float upgradeHp;
    float defense;
    float upgradeDefense;
    float speed;
    float upgradeSpeed;
    float maxSpeed;
    float refund;
    float upgradeRefund;

    int enemyBaseScore;

    /* Proceddimentos */

    if (levelFile != NULL) {

    	/* Loop para receber os componentes do terreno */

        for (auxI = 0; auxI < 12; auxI++) {

            for (auxII = 0; auxII < 16; auxII++) {

                fscanf(levelFile, "%i", groundMatrix[0][auxI] + auxII);

                if (groundMatrix[0][auxI][auxII] != 0) {

                	if (groundMatrix[0][auxI][auxII] == 2) {

                		initialTileI = auxI;

                		initialTileJ = auxII;

					}

				qntPaths++;

				}

            }

        }

		/* Definimos a posicao onde os inimigos apareceram */

		initialPosX = 80 + (initialTileJ * 40);

		initialPosY = 40 + (initialTileI * 40);

		/* Loop para gerar um vetor de eixos */

		for (auxI = 0; auxI < qntPaths; auxI++) {

			tileLocker = 0;

			if (initialTileJ > 1 && tileLocker == 0) {

				if (groundMatrix[0][initialTileI][initialTileJ-1] != 0 && cameDirection != left) {

					tileLocker = 1;

					cameDirection = right;

					currentDirection = left;

				}

			}

			if (initialTileJ < 15 && tileLocker == 0) {

				if (groundMatrix[0][initialTileI][initialTileJ+1] != 0 && cameDirection != right) {

					tileLocker = 1;

					cameDirection = left;

					currentDirection = right;

				}

			}

			if (initialTileI > 1 && tileLocker == 0) {

				if (groundMatrix[0][initialTileI-1][initialTileJ] != 0 && cameDirection != top) {

					tileLocker = 1;

					cameDirection = bottom;

					currentDirection = top;

				}

			}

			if (initialTileI < 11 && tileLocker == 0) {

				if (groundMatrix[0][initialTileI+1][initialTileJ] != 0 && cameDirection != bottom) {

					tileLocker = 1;

					cameDirection = top;

					currentDirection = bottom;

				}

			}

			if (auxI == 0 || auxI == (qntPaths-1) || lastDirection != currentDirection) {

				lastDirection = currentDirection;

				newAxis = (Axis *) realloc(newAxis, (qntAxis + 1) * sizeof(Axis));

				if (newAxis == NULL){

					exit(1);

				}

				newAxis[qntAxis].posX = 100 + (initialTileJ * 40);
				newAxis[qntAxis].posY = 60 + (initialTileI * 40);

				newAxis[qntAxis].direction = currentDirection;

				if (cameDirection == top || cameDirection == bottom){

					newAxis[qntAxis].line = vertical;

				}else{

					newAxis[qntAxis].line = horizontal;

				}

				qntAxis++;

			}

			switch (cameDirection) {

				case top: initialTileI += 1; break;

				case bottom: initialTileI -= 1; break;

				case left: initialTileJ += 1; break;

				case right: initialTileJ -= 1; break;

			}

		}

        fscanf(levelFile, "%i", qntLifes);

        fscanf(levelFile, "%i", qntMoney);

        fscanf(levelFile, "%i", qntRounds);

        enemiesPerLine = (int *) calloc(*qntRounds, sizeof(int));

        bytesRead = ftell(levelFile);

        /* Loop para contar a quantidade de inimigos */

        for (auxI = 0, auxII = 0; !feof(levelFile);) {

        	enemyDelay = 0;

            fscanf(levelFile, "%c", &enemyType);

            if (enemyType != ' ' && enemyType != '\n') {

                fscanf(levelFile, "%i", &enemyLevel);

                fscanf(levelFile, "%i", &enemyDelay);

                auxI++;

                qntEnemiesCounter++;

                if (enemyDelay == 0 && qntEnemiesCounter != 0) {

                    enemiesPerLine[auxII] = auxI;

                    qntEnemiesCounter = 0;

                    auxII++;

                }

            }

        }

		*qntEnemies = auxI;

        newEnemies = allocEnemiesMatrix(auxI);

        fseek(levelFile, bytesRead, SEEK_SET);

        /* Loop para ler e gerar as informacoes dos inimigos */

        for (auxI = 0; !feof(levelFile);) {

        	enemyDelay = 0;

            fscanf(levelFile, "%c", &enemyType);

            if (enemyType != ' ' && enemyType != '\n') {

                fscanf(levelFile, "%i", &enemyLevel);

                fscanf(levelFile, "%i", &enemyDelay);

                if (auxI > 0 && enemyDelay == 0) { enemyDelay = roundTransitionDelay; }

                switch (enemyType) {

                    case eNormal:

						imageRandomizer = rand()%7;

						image = enemyImage1[imageRandomizer];
						imagePosX = 0;
						imagePosY = (enemyLevel-1) * 80;

                        upgradeHp = 50;
                        hp = 100 + (upgradeHp * (enemyLevel-1));
                        upgradeDefense = 4;
                        defense = 0 + (upgradeDefense * (enemyLevel-1));
                        upgradeSpeed = 0.2;
                        maxSpeed = 2;
                        speed = (1 + (upgradeSpeed * (enemyLevel-1))) * 1.2;
                        speed = (speed > maxSpeed ? maxSpeed : speed);
                        upgradeRefund = 5;
                        refund = 20 + (upgradeRefund * (enemyLevel-1));
                        enemyBaseScore = 100;

                        break;

                    case eRSplash:

						imageRandomizer = 0;

						image = enemyImage2[imageRandomizer];
						imagePosX = 0;
						imagePosY = (enemyLevel - 1) * 80;

                        upgradeHp = 60;
                        hp = 120 + (upgradeHp * (enemyLevel - 1));
                        upgradeDefense = 5;
                        defense = 4 + (upgradeDefense * (enemyLevel - 1));
                        upgradeSpeed = 0.2;
                        maxSpeed = 2;
                        speed = (1 + (upgradeSpeed * (enemyLevel - 1))) * 1.2;
                        speed = (speed > maxSpeed ? maxSpeed : speed);
                        upgradeRefund = 7;
                        refund = 35 + (upgradeRefund * (enemyLevel - 1));
                        enemyBaseScore = 150;

                        break;

                    case eStrong:

						imageRandomizer = 0;

						image = enemyImage3[imageRandomizer];
						imagePosX = 0;
						imagePosY = (enemyLevel - 1) * 80;

                        upgradeHp = 100;
                        hp = 150 + (upgradeHp * (enemyLevel - 1));
                        upgradeDefense = 6;
                        defense = 5 + (upgradeDefense * (enemyLevel - 1));
                        upgradeSpeed = 0.15;
                        maxSpeed = 1.5;
                        speed = (0.8 + (upgradeSpeed * (enemyLevel - 1))) * 1.2;
                        speed = (speed > maxSpeed ? maxSpeed : speed);
                        upgradeRefund = 10;
                        refund = 40 + (upgradeRefund * (enemyLevel - 1));
                        enemyBaseScore = 200;

                        break;

                    case eFast:

						imageRandomizer = 0;

						image = enemyImage4[imageRandomizer];
						imagePosX = 0;
						imagePosY = (enemyLevel - 1) * 80;

                        upgradeHp = 40;
                        hp = 80 + (upgradeHp * (enemyLevel - 1));
                        upgradeDefense = 3;
                        defense = 2 + (upgradeDefense * (enemyLevel - 1));
                        upgradeSpeed = 0.3;
                        maxSpeed = 3;
                        speed = (1.5 + (upgradeSpeed * (enemyLevel - 1))) * 1.2;
                        speed = (speed > maxSpeed ? maxSpeed : speed);
                        upgradeRefund = 7;
                        refund = 30 + (upgradeRefund * (enemyLevel - 1));
                        enemyBaseScore = 250;

                        break;

                    case eSafer:

						imageRandomizer = rand()%2;

						image = enemyImage5[imageRandomizer];
						imagePosX = 0;
						imagePosY = (enemyLevel - 1) * 80;

                        upgradeHp = 45;
                        hp = 90 + (upgradeHp * (enemyLevel - 1));
                        upgradeDefense = 4;
                        defense = 2 + (upgradeDefense * (enemyLevel - 1));
                        upgradeSpeed = 0.2;
                        maxSpeed = 2;
                        speed = (1 + (upgradeSpeed * (enemyLevel - 1))) * 1.2;
                        speed = (speed > maxSpeed ? maxSpeed : speed);
                        upgradeRefund = 7;
                        refund = 30 + (upgradeRefund * (enemyLevel - 1));
                        enemyBaseScore = 300;

                        break;

                    default: break;

                }

				newEnemies[auxI]->image = image;
				newEnemies[auxI]->imagePosX = imagePosX;
				newEnemies[auxI]->imagePosY = imagePosY;

				newEnemies[auxI]->movingImage = 0;
				newEnemies[auxI]->movingImageTicks = 0;

				newEnemies[auxI]->type = enemyType;
				newEnemies[auxI]->level = enemyLevel;

				newEnemies[auxI]->delay = enemyDelay;

                newEnemies[auxI]->hp = hp;
                newEnemies[auxI]->totalHp = hp;
                newEnemies[auxI]->upgradeHp = upgradeHp;
                newEnemies[auxI]->defense = defense;
                newEnemies[auxI]->upgradeDefense = upgradeDefense;
                newEnemies[auxI]->speed = speed;
                newEnemies[auxI]->upgradeSpeed = upgradeSpeed;
                newEnemies[auxI]->maxSpeed = maxSpeed;
				newEnemies[auxI]->refund = refund;
				newEnemies[auxI]->upgradeRefund = upgradeRefund;

				newEnemies[auxI]->posX = initialPosX;
				newEnemies[auxI]->posY = initialPosY;

				newEnemies[auxI]->distanceWalked = 0;

				newEnemies[auxI]->posAxis = 1;

				newEnemies[auxI]->isMarked = false;
				newEnemies[auxI]->isSlower = false;

				newEnemies[auxI]->isPoisoned = false;
				newEnemies[auxI]->poisonDamage = 0;

				newEnemies[auxI]->beaconRankNormal = 0;
				newEnemies[auxI]->beaconRankSplash = 0;
				newEnemies[auxI]->beaconRankSlow = 0;
				newEnemies[auxI]->beaconRankPoison = 0;

				newEnemies[auxI]->baseScore = enemyBaseScore;

                auxI++;

            }

        }

    }else{

    	exit(1);

    }

    *enemies = newEnemies;

    *qntEnemiesPerLine = enemiesPerLine;

    *groundAxis = newAxis;

    *qntGroundAxis = qntAxis;

}

void grabTileBlitPosition(int ***groundMatrix, int i, int j, int *posX, int *posY) {

    int tile = groundMatrix[0][i][j];

    int topTile = (i > 0 ? groundMatrix[0][i-1][j] : -1);
    int bottomTile = (i < 11 ? groundMatrix[0][i+1][j] : -1);
    int leftTile = (j > 0 ? groundMatrix[0][i][j-1] : -1);
    int rightTile = (j < 15 ? groundMatrix[0][i][j+1] : -1);

    int qntIgualdades = 0;

    qntIgualdades += (tile == topTile ? 1 : 0);
    qntIgualdades += (tile == bottomTile ? 1 : 0);
    qntIgualdades += (tile == leftTile ? 1 : 0);
    qntIgualdades += (tile == rightTile ? 1 : 0);

    if (tile == 0) {

        *posX = 40;
        *posY = 40;

    }else if (tile == 1) {

    	if (qntIgualdades == 0){

    		if (topTile == 2 || topTile == 3){
    			*posX = 0;
    			*posY = 40;
    		}else{
    			*posX = 40;
    			*posY = 0;
    		}

    	}

        if (qntIgualdades == 1) {
            if (tile == topTile) {
                if (rightTile != 0) {
                    *posX = 0; *posY = 80;
                }else if (bottomTile != 0) {
                    *posX = 40; *posY = 0;
                }else if (leftTile != 0) {
                    *posX = 80; *posY = 80;
                }
            }else if (tile == rightTile) {
                if (topTile != 0) {
                    *posX = 80; *posY = 0;
                }else if (bottomTile != 0) {
                    *posX = 00; *posY = 0;
                }else if (leftTile != 0) {
                    *posX = 40; *posY = 0;
                }
            }else if (tile == bottomTile) {
                if (topTile != 0) {
                    *posX = 0; *posY = 40;
                }else if (rightTile != 0) {
                    *posX = 0; *posY = 0;
                }else if (leftTile != 0) {
                    *posX = 80; *posY = 0;
                }
            }else if (tile == leftTile) {
                if (topTile != 0) {
                    *posX = 80; *posY = 80;
                }else if (rightTile != 0) {
                    *posX = 40; *posY = 0;
                }else if (bottomTile != 0) {
                    *posX = 80; *posY = 0;
                }
            }
        }

        if (qntIgualdades == 2) {
            if (tile == topTile && tile == bottomTile) {
                *posX = 0;
                *posY = 40;
            }
            else
            if (tile == topTile && tile == rightTile) {
                *posX = 0;
                *posY = 80;
            }
            else
            if (tile == topTile && tile == leftTile) {
                *posX = 80;
                *posY = 80;
            }
            else
            if (tile == bottomTile && tile == rightTile) {
                *posX = 0;
                *posY = 0;
            }
            else
            if (tile == bottomTile && tile == leftTile) {
                *posX = 80;
                *posY = 0;
            }
            else
            if (tile == rightTile && tile == leftTile) {
                *posX = 40;
                *posY = 0;
            }
        }

        if (qntIgualdades == 3) {

            if (tile == topTile && tile == rightTile && tile == leftTile) {
                *posX = 40;
                *posY = 40;
            }
            else
            if (tile == topTile && tile == rightTile && tile == bottomTile) {
                *posX = 40;
                *posY = 40;
            }
            else
            if (tile == topTile && tile == bottomTile && tile == leftTile) {
                *posX = 40;
                *posY = 40;
            }
            else
            if (tile == bottomTile && tile == rightTile && tile == leftTile) {
                *posX = 40;
                *posY = 40;
            }

        }

    }else if (tile == 2) {

        *posX = 0;
        *posY = 120;

    }else if (tile == 3) {

        *posX = 40;
        *posY = 120;

    }

}

void drawGround(BITMAP **groundBitmap, int ***groundMatrix) {

    int auxI,auxII;

    int ground_InX;
    int ground_InY;
    int ground_PosX;
    int ground_PosY;

    BITMAP *ground_Tile = load_bitmap("Imagens/Terreno/ground_120x120.bmp", NULL);

    for (auxI = 0; auxI < 15; auxI++) {

        ground_PosY = auxI * 40;

        for (auxII = 0; auxII < 20; auxII++) {

            ground_PosX = auxII * 40;

            if (auxI == 0 || auxI > 12 || auxII < 2 || auxII > 17) {
                ground_InX = 80;
                ground_InY = 120;
            }else{
                grabTileBlitPosition(groundMatrix, auxI-1, auxII-2, &ground_InX, &ground_InY);
            }

            masked_blit(ground_Tile, *groundBitmap, ground_InX, ground_InY, ground_PosX, ground_PosY, 40, 40);

        }

    }

    destroy_bitmap(ground_Tile);

}

void drawTiledGround(BITMAP **tiledGround, int ***groundMatrix) {

    int auxI,auxII;

    int ground_PosX;
    int ground_PosY;

    int drawColor;

    for (auxI = 0; auxI < 15; auxI++) {

        ground_PosY = auxI * 40;

        for (auxII = 0; auxII < 20; auxII++) {

            ground_PosX = auxII * 40;

            if (auxI > 0 && auxI < 13 && auxII > 1 && auxII < 18) {

                if (groundMatrix[0][auxI-1][auxII-2] == 0) {

                    if (auxI % 2 == 0) {

                        if (auxII % 2 == 0) {
                            drawColor = makeacol(0, 130, 0, 60);
                        }else{
                            drawColor = makeacol(0, 255, 0, 60);
                        }

                    }else{

                        if (auxII % 2 == 0) {
                            drawColor = makeacol(0, 255, 0, 60);
                        }else{
                            drawColor = makeacol(0, 130, 0, 60);
                        }

                    }

                    rectfill(*tiledGround, ground_PosX+2, ground_PosY+2, ground_PosX+38, ground_PosY+38, drawColor);

                }

            }

        }

    }

}

void drawTileBlink(int *auxBlinkCounter, int *auxBlinkLock, BITMAP *window, int posX, int posY) {

	int color;

	if (*auxBlinkCounter > 20) { *auxBlinkCounter = 0; }

	if (*auxBlinkLock == true) {

		*auxBlinkCounter += 1;

		color = makeacol(255, 255, 255, 75);

		if (*auxBlinkCounter == 20) {

			*auxBlinkLock = false;

			*auxBlinkCounter = 0;

		}

	}else{

		*auxBlinkCounter += 1;

		color = makeacol(255, 255, 255, 25);

		if (*auxBlinkCounter == 20) {

			*auxBlinkLock = true;

			*auxBlinkCounter = 0;

		}

	}

	rectfill(window, posX+2, posY+2, posX+38, posY+38, color);

}

int positionAvailible(int **groundMatrix, Tower ***towers, float posX, float posY){

    int tileAvailible = 0;

    posX -= 80;
    posY -= 40;

    int tileI = posY/40;
    int tileJ = posX/40;

    if ((posX >= 0 && posX < 640) && (posY >= 0 && posY < 480)) {

        if (groundMatrix[tileI][tileJ] == 0) {

        	if (towers[tileI][tileJ] == NULL) {

        		tileAvailible = 1;

        	}

        }

    }

    return tileAvailible;

}

void placeTower(Tower ***towers,int type, int posX, int posY, int **qntTowersByRound, int index) {

	Tower *newTower = (Tower *) malloc(sizeof(Tower));

    BITMAP *towerImage;
    int rank;
    int maxRank;
    int ticksPerFire;
    int slowTax;
    int damage;
    int damageUpgrade;
    int multipleDamage;
    int multipleDamageUpgrade;
    float selfRange;
    float rangeUpgrade;
    float multipleRange;
    float multipleRangeUpgrade;
    float price;
    float upgradePrice;
    int fireTimer;

    newTower->type = type;

    switch (type) {

        case tNormal:

			qntTowersByRound[index][0] += 1;

            towerImage = load_bitmap("Imagens/Torres/torre1.bmp", NULL);
            rank                  = 1;
            maxRank			      = 5;
            ticksPerFire          = 16;
            slowTax			      = 0;
            damage                = 25;
            damageUpgrade         = 20;
            multipleDamage        = 0;
            multipleDamageUpgrade = 0;
            selfRange             = 2;
            rangeUpgrade          = 0.3;
            multipleRange         = 0;
            multipleRangeUpgrade  = 0;
            price                 = 80;
            upgradePrice 	      = 120;
            fireTimer		      = 16;

            break;

        case tSplash:

			qntTowersByRound[index][1] += 1;

            towerImage = load_bitmap("Imagens/Torres/torre2.bmp", NULL);
            rank                  = 1;
            maxRank			      = 5;
            ticksPerFire          = 22;
            slowTax			      = 0;
            damage                = 40;
            damageUpgrade         = 35;
            multipleDamage        = 40;
            multipleDamageUpgrade = 15;
            selfRange             = 1.5;
            rangeUpgrade          = 0.25;
            multipleRange         = 1;
            multipleRangeUpgrade  = 0;
            price                 = 200;
            upgradePrice 	      = 300;
            fireTimer		      = 22;

            break;

        case tSlow:

			qntTowersByRound[index][2] += 1;

            towerImage = load_bitmap("Imagens/Torres/torre3.bmp", NULL);
            rank                  = 1;
            maxRank			      = 5;
            ticksPerFire          = 0;
            slowTax			      = 35;
            damage                = 0;
            damageUpgrade         = 0;
            multipleDamage        = 0;
            multipleDamageUpgrade = 0;
            selfRange             = 1.5;
            rangeUpgrade          = 0.25;
            multipleRange         = 1.5;
            multipleRangeUpgrade  = 0.25;
            price                 = 140;
            upgradePrice 	      = 210;
            fireTimer 		      = 0;

            break;

        case tPoison:

			qntTowersByRound[index][3] += 1;

            towerImage = load_bitmap("Imagens/Torres/torre4.bmp", NULL);
            rank                  = 1;
            maxRank			      = 5;
            ticksPerFire          = 3;
            slowTax			      = 0;
            damage                = 1;
            damageUpgrade         = 1;
            multipleDamage        = 1;
            multipleDamageUpgrade = 1;
            selfRange             = 1.5;
            rangeUpgrade          = 0.2;
            multipleRange         = 1.5;
            multipleRangeUpgrade  = 0.2;
            price                 = 160;
            upgradePrice 	      = 320;
            fireTimer 		      = 0;

            break;

        case tBeacon:

			qntTowersByRound[index][4] += 1;

            towerImage = load_bitmap("Imagens/Torres/torre5.bmp", NULL);
            rank                  = 1;
            maxRank			      = 3;
            ticksPerFire          = 0;
            slowTax			      = 0;
            damage                = 0;
            damageUpgrade         = 0;
            multipleDamage        = 0;
            multipleDamageUpgrade = 0;
            selfRange             = 2;
            rangeUpgrade          = 0.5;
            multipleRange         = 0;
            multipleRangeUpgrade  = 0;
            price                 = 400;
            upgradePrice 	      = 600;
            fireTimer 		      = 0;

            break;

    }

	selfRange = (selfRange == 0 ? multipleRange : selfRange);

	newTower->image = towerImage;
	newTower->imagePosX = 0;
	newTower->rank = rank;
	newTower->maxRank = maxRank;
	newTower->ticksPerFire = ticksPerFire;
	newTower->slowTax = slowTax;
	newTower->damage = damage;
	newTower->damageUpgrade = damageUpgrade;
	newTower->multipleDamage = multipleDamage;
	newTower->multipleDamageUpgrade = multipleDamageUpgrade;
	newTower->selfRange = selfRange;
	newTower->rangeUpgrade = rangeUpgrade;
	newTower->multipleRange = multipleRange;
	newTower->multipleRangeUpgrade = multipleRangeUpgrade;
	newTower->price = price;
	newTower->upgradePrice = upgradePrice;
	newTower->sellPrice = price/2;

	newTower->fireTimer = fireTimer;
	newTower->ticksForFire = fireTimer;

	newTower->showHUD = false;

	newTower->target = NULL;
	newTower->slowTargets = NULL;
	newTower->qntSlowTargets = 0;

	newTower->beaconEffect = false;
	newTower->beaconRank = 0;

	newTower->posX = posX - (posX%40);
    newTower->posY = posY - (posY%40);

    newTower->towerAnimation = 0;

    posX -= 80;
    posY -=40;

    int tileI = posY/40;
    int tileJ = posX/40;

    towers[tileI][tileJ] = newTower;

}

void drawRangeRadius(Tower ***towers, BITMAP *window){

	int auxI,auxII;

	for (auxI = 0; auxI < 12; auxI++) {

		for (auxII = 0; auxII < 16; auxII++) {

			if (towers[auxI][auxII] != NULL) {

				if (towers[auxI][auxII]->showHUD == false) {

					if (towers[auxI][auxII]->type == tPoison){

						circlefill(window, towers[auxI][auxII]->posX+20, towers[auxI][auxII]->posY+20, (towers[auxI][auxII]->selfRange*40)+20, makeacol(140, 35, 175, 75));

					}

				}

			}

		}

	}

}

void drawTowers(Tower ***towers, BITMAP *window, int budget, int *hudVisible) {

	int auxI,auxII;

	int tileI = -1,tileJ = -1;

	*hudVisible = false;

	for (auxI = 0; auxI < 12; auxI++) {

		for (auxII = 0; auxII < 16; auxII++) {

			if (towers[auxI][auxII] != NULL) {

				if (towers[auxI][auxII]->showHUD == false) {

					if (towers[auxI][auxII]->beaconEffect == true){

						rectfill(window, towers[auxI][auxII]->posX, towers[auxI][auxII]->posY, towers[auxI][auxII]->posX+40, towers[auxI][auxII]->posY+40, makeacol(255, 255, 255, 75));

					}

				}

			}

		}

	}

	for (auxI = 0; auxI < 12; auxI++) {

		for (auxII = 0; auxII < 16; auxII++) {

			if (towers[auxI][auxII] != NULL) {

				if (towers[auxI][auxII]->showHUD == true) {

					tileI = auxI;
					tileJ = auxII;

				}else{

					if(towers[auxI][auxII]->towerAnimation >= 0 && towers[auxI][auxII]->towerAnimation < 30)
					{
					    masked_blit(towers[auxI][auxII]->image, window, towers[auxI][auxII]->imagePosX, ((towers[auxI][auxII]->rank - 1) * 80), towers[auxI][auxII]->posX, towers[auxI][auxII]->posY, 40, 40);

					} else if(towers[auxI][auxII]->towerAnimation >= 30 && towers[auxI][auxII]->towerAnimation < 60) {

                        masked_blit(towers[auxI][auxII]->image, window, towers[auxI][auxII]->imagePosX, ((towers[auxI][auxII]->rank - 1) * 80) + 40, towers[auxI][auxII]->posX, towers[auxI][auxII]->posY, 40, 40);
					}

					towers[auxI][auxII]->towerAnimation++;

					if(towers[auxI][auxII]->towerAnimation == 60) { towers[auxI][auxII]->towerAnimation = 0; }
				}
			}

		}

	}

	if (tileI != -1) {

		BITMAP *sellIcon = load_bitmap("Imagens/Torres/HUD/sellTower_30x30.bmp", NULL);
		BITMAP *optionsIcon = load_bitmap("Imagens/Torres/HUD/towerOptions_30x30.bmp", NULL);
		BITMAP *upgradeIcon;

		if (budget >= towers[tileI][tileJ]->upgradePrice && towers[tileI][tileJ]->rank < towers[tileI][tileJ]->maxRank) {

			upgradeIcon = load_bitmap("Imagens/Torres/HUD/upgradeTower_30x30.bmp", NULL);

		}else{

			upgradeIcon = load_bitmap("Imagens/Torres/HUD/upgradeTower_Disabled_30x30.bmp", NULL);

		}

		circlefill(window, towers[tileI][tileJ]->posX+20, towers[tileI][tileJ]->posY+20, (towers[tileI][tileJ]->selfRange*40)+20, makeacol(0, 0, 0, 75));

		draw_sprite(window, sellIcon, towers[tileI][tileJ]->posX-80, towers[tileI][tileJ]->posY-5);

		textprintf_centre_ex(window, font, towers[tileI][tileJ]->posX-55, towers[tileI][tileJ]->posY+50, makeacol(255, 255, 255, 255), -1, "$%.0f",towers[tileI][tileJ]->sellPrice);

		draw_sprite(window, upgradeIcon, towers[tileI][tileJ]->posX+70, towers[tileI][tileJ]->posY-5);

		textprintf_centre_ex(window, font, towers[tileI][tileJ]->posX+95, towers[tileI][tileJ]->posY+50, makeacol(255, 255, 255, 255), -1, "$%.0f",towers[tileI][tileJ]->upgradePrice);

		if (towers[tileI][tileJ]->type != tPoison && towers[tileI][tileJ]->type != tBeacon){

			draw_sprite(window, optionsIcon, towers[tileI][tileJ]->posX-5, towers[tileI][tileJ]->posY+70);

		}

		textprintf_centre_ex(window, font, towers[tileI][tileJ]->posX+20, towers[tileI][tileJ]->posY-20, makeacol(255, 255, 255, 255), -1, "LEVEL %i",towers[tileI][tileJ]->rank);

		masked_blit(towers[tileI][tileJ]->image, window, towers[tileI][tileJ]->imagePosX, ((towers[tileI][tileJ]->rank - 1) * 80), towers[tileI][tileJ]->posX, towers[tileI][tileJ]->posY, 40, 40);

		*hudVisible = true;

	}

}

void checkTowersHUD(Tower ***towers, BITMAP *window, int touchX, int touchY) {

	touchX -= 80;
	touchY -= 40;

	int auxI,auxII;

	int tileI = touchY/40;
	int tileJ = touchX/40;

	if (towers[tileI][tileJ] != NULL) {

		for (auxI = 0; auxI < 12; auxI++) {

			for (auxII = 0; auxII < 16; auxII++) {

				if (tileI != auxI && tileJ != auxII && towers[auxI][auxII] != NULL) {

					towers[auxI][auxII]->showHUD = false;

				}

			}

		}

		towers[tileI][tileJ]->showHUD = (towers[tileI][tileJ]->showHUD == true ? false : true);

	}

}

void closeAllHUD(Tower ***towers) {

	int auxI,auxII;

	for (auxI = 0; auxI < 12; auxI++) {

			for (auxII = 0; auxII < 16; auxII++) {

				if (towers[auxI][auxII] != NULL) {

					towers[auxI][auxII]->showHUD = false;

				}

			}

		}

}

int mouseOverCircularArea(int touchX, int touchY, int centerX, int centerY, int radius) {

	int mouseOver = 0;

	int distance = sqrt( (pow((touchX-centerX),2)+pow((touchY - centerY),2) ));

	if (radius >= distance) { mouseOver = 1; }

	return mouseOver;

}

int checkClickedHUD(Tower ***towers, BITMAP *window, int touchX, int touchY, int *qntBudget, SAMPLE *levelUp, int *spentMoney){

	int hudType = 0;

	int tileI = -1,tileJ = -1;

	int auxI,auxII;

	int optionsAvailable = false;

	for (auxI = 0; auxI < 12; auxI++) {

		for (auxII = 0; auxII < 16; auxII++) {

			if (towers[auxI][auxII] != NULL) {

				if (towers[auxI][auxII]->showHUD == true) {

					tileI = auxI;
					tileJ = auxII;

					auxI = 12;
					auxII = 16;

				}

			}

		}

	}

	if (tileI != -1 && tileJ != -1) {

		if (towers[tileI][tileJ]->type != tPoison && towers[tileI][tileJ]->type != tBeacon){ optionsAvailable = true; }

		if (mouseOverCircularArea(touchX, touchY, towers[tileI][tileJ]->posX-55, towers[tileI][tileJ]->posY+20, 25) == 1) {

			circlefill(window, towers[tileI][tileJ]->posX-55, towers[tileI][tileJ]->posY+20, 30, makeacol(255, 255, 255, 255));

			*qntBudget += towers[tileI][tileJ]->price;

			freeTower(towers[tileI][tileJ]);

			towers[tileI][tileJ] = NULL;

		}else if (mouseOverCircularArea(touchX, touchY, towers[tileI][tileJ]->posX+95, towers[tileI][tileJ]->posY+20, 25) == 1) {

			circlefill(window, towers[tileI][tileJ]->posX+95, towers[tileI][tileJ]->posY+20, 30, makeacol(255, 255, 255, 255));

			if (*qntBudget >= towers[tileI][tileJ]->upgradePrice && towers[tileI][tileJ]->maxRank > towers[tileI][tileJ]->rank) {

				play_sample(levelUp, 255, 0, 1000, 0);

				towers[tileI][tileJ]->rank += 1;

				*qntBudget -= towers[tileI][tileJ]->upgradePrice;

				*spentMoney += towers[tileI][tileJ]->upgradePrice;

				towers[tileI][tileJ]->sellPrice += (towers[tileI][tileJ]->upgradePrice)/2;

				towers[tileI][tileJ]->upgradePrice = (towers[tileI][tileJ]->upgradePrice * 1.5);

				towers[tileI][tileJ]->damage += towers[tileI][tileJ]->damageUpgrade;

				towers[tileI][tileJ]->multipleDamage += towers[tileI][tileJ]->multipleDamageUpgrade;

				towers[tileI][tileJ]->selfRange += towers[tileI][tileJ]->rangeUpgrade;

				towers[tileI][tileJ]->multipleRange += towers[tileI][tileJ]->multipleRangeUpgrade;

			}

		}else if (mouseOverCircularArea(touchX, touchY, towers[tileI][tileJ]->posX+20, towers[tileI][tileJ]->posY+95, 25) == 1 && optionsAvailable == true) {

			switch(towers[tileI][tileJ]->type){

				case tNormal: hudType = 1; break;

				case tSplash: hudType = 2; break;

				case tSlow: hudType = 3; break;

			}

		}else if (mouseOverCircularArea(touchX, touchY, towers[tileI][tileJ]->posX, towers[tileI][tileJ]->posY, (towers[tileI][tileJ]->selfRange*40)+20) == 0) {

			towers[tileI][tileJ]->showHUD = false;

		}


	}

	return hudType;

}

void drawEnemies(BITMAP *window, Enemie **enemies, int qntEnemies, int *activeRound, int qntRoundEnemies, Axis *groundAxis, int qntAxis) {

	int auxI;

	int qntOut;

	int lifeBar;

	int hpColor;

	float finalSpeed = 0;

	for (auxI = 0, qntOut = 0; auxI < qntRoundEnemies ; auxI++) {

		if (enemies[auxI] != NULL) {

			if (enemies[auxI]->delay == 0) {

				finalSpeed = (enemies[auxI]->isSlower == true ? (enemies[auxI]->speed*(0.65-(enemies[auxI]->beaconRankSlow*0.05))) : enemies[auxI]->speed);

				enemies[auxI]->distanceWalked += finalSpeed;

				switch (groundAxis[enemies[auxI]->posAxis-1].direction) {

					case left:
						enemies[auxI]->imagePosX = 80;
						enemies[auxI]->posX -= finalSpeed;
						if (enemies[auxI]->posX + 20 <= groundAxis[enemies[auxI]->posAxis].posX) { enemies[auxI]->posAxis += 1; }
						break;

					case right:
						enemies[auxI]->imagePosX = 240;
						enemies[auxI]->posX += finalSpeed;
						if (enemies[auxI]->posX + 20 >= groundAxis[enemies[auxI]->posAxis].posX) { enemies[auxI]->posAxis += 1; }
						break;

					case top:
						enemies[auxI]->imagePosX = 160;
						enemies[auxI]->posY -= finalSpeed;
						if (enemies[auxI]->posY + 20 <= groundAxis[enemies[auxI]->posAxis].posY) { enemies[auxI]->posAxis += 1; }
						break;

					case bottom:
						enemies[auxI]->imagePosX = 0;
						enemies[auxI]->posY += finalSpeed;
						if (enemies[auxI]->posY + 20 >= groundAxis[enemies[auxI]->posAxis].posY) { enemies[auxI]->posAxis += 1; }
						break;

				}

				if (enemies[auxI]->movingImageTicks == 0) {

					enemies[auxI]->movingImageTicks = 5;
					enemies[auxI]->movingImage = (enemies[auxI]->movingImage == 0 ? 1 : 0);

				}else{

					enemies[auxI]->movingImageTicks -= 1;

				}

				enemies[auxI]->imagePosY = (enemies[auxI]->movingImage * 40) + (enemies[auxI]->level>5?4:enemies[auxI]->level-1) * 80;

				lifeBar = (enemies[auxI]->hp*20/enemies[auxI]->totalHp);

				lifeBar = (lifeBar <= 0 ? 0 : lifeBar);

				rectfill(window, enemies[auxI]->posX+10, enemies[auxI]->posY-1, enemies[auxI]->posX+30, enemies[auxI]->posY+1, makeacol(0, 0, 0, 255));

				if(enemies[auxI]->hp/enemies[auxI]->totalHp >= 0.5) {

				    hpColor = makeacol(0, 255, 0, 255);

				} else if(enemies[auxI]->hp/enemies[auxI]->totalHp >= 0.25) {

				    hpColor = makeacol(255, 255, 0, 255);

				} else {

                    hpColor = makeacol(255, 0, 0, 255);
				}

				rectfill(window, enemies[auxI]->posX+10, enemies[auxI]->posY-1, enemies[auxI]->posX+10+lifeBar, enemies[auxI]->posY+1, hpColor);

				rect(window, enemies[auxI]->posX+10, enemies[auxI]->posY-1, enemies[auxI]->posX+30, enemies[auxI]->posY+1, makeacol(0, 0, 0, 255));

				masked_blit(enemies[auxI]->image, window, enemies[auxI]->imagePosX, enemies[auxI]->imagePosY, enemies[auxI]->posX, enemies[auxI]->posY, 40, 40);

			}else{

				enemies[auxI]->delay -= 1;

				auxI = qntRoundEnemies;

			}

		}else{

			qntOut++;

			if (qntOut == qntRoundEnemies) {

				*activeRound += 1;

			}

		}

	}

}

void checkEnemies (Enemie **enemies, int qntEnemies, int **groundMatrix, int *qntLifes, int *qntBudget, int *qntDeathEnemies, int *globalScore) {

	int auxI;

	int tileI,tileJ;

	int remover;

	for (auxI = 0; auxI < qntEnemies; auxI++) {

		if (enemies[auxI] != NULL) {

			remover = 0;

			tileI = (enemies[auxI]->posY - 40 + 20)/40;
			tileJ = (enemies[auxI]->posX - 80 + 20)/40;

			if (enemies[auxI]->hp <= 0) {

				*globalScore += (enemies[auxI]->baseScore) * (enemies[auxI]->level);

				*qntBudget += enemies[auxI]->refund;

				switch(enemies[auxI]->type){

					case eNormal: qntDeathEnemies[0] += 1; break;

					case eRSplash: qntDeathEnemies[1] += 1; break;

					case eStrong: qntDeathEnemies[2] += 1; break;

					case eFast: qntDeathEnemies[3] += 1; break;

					case eSafer: qntDeathEnemies[4] += 1; break;

				}

				remover = 1;

			}

			if (groundMatrix[tileI][tileJ] == 3) {

				*qntLifes -= 1;

				remover = 1;

			}

			if (remover == 1) {

				free(enemies[auxI]);

				enemies[auxI] = NULL;

			}

		}

	}

}

int insideCircularArea(int touchX, int touchY, float centerX, float centerY, float radius, float *pDistance) {

	int mouseOver = 0;

	int distance = sqrt( (pow((touchX-centerX),2)+pow((touchY - centerY),2) ));

	if (pDistance != NULL){ *pDistance = distance; }

	if (radius >= distance) { mouseOver = 1; }

	return mouseOver;

}

void targetEnemies(Tower ***towers, Enemie **enemies, int qntEnemies, Bullet **bullets, int *shootingPrefs) {

	int auxI,auxII,auxIII,auxIIII,auxIIIII,auxIIIIII;

	int tPosX,tPosY,tRadius;

	float bulletDamage;

	float distance = 0;

	Enemie **slowVector = NULL;

	int slowVectorIndex = 0;

	int prefCmp = 0, cmpDistance = false;

	float prefCmpValue = 0,prefCmpValueCmp = 0;

	Enemie *cmpTarget = NULL;

	for (auxI = 0; auxI<12; auxI++){

		for(auxII = 0; auxII<16; auxII++){

			if (towers[auxI][auxII] != NULL){

				tPosX = towers[auxI][auxII]->posX+20;
				tPosY = towers[auxI][auxII]->posY+20;
				tRadius = (towers[auxI][auxII]->selfRange*40)+20;

				if (towers[auxI][auxII]->type == tBeacon){

					for (auxIIII = 0; auxIIII < 12; auxIIII++){

						for (auxIIIII = 0; auxIIIII < 16; auxIIIII++){

							if (towers[auxIIII][auxIIIII] != NULL){

								if (towers[auxIIII][auxIIIII]->beaconEffect == false){

									if (insideCircularArea(towers[auxIIII][auxIIIII]->posX+20, towers[auxIIII][auxIIIII]->posY+20, tPosX, tPosY, tRadius, NULL) == 1){

										towers[auxIIII][auxIIIII]->beaconEffect = true;

										towers[auxIIII][auxIIIII]->beaconRank = towers[auxI][auxII]->rank;

									}

								}

							}

						}

					}

				}

			}

		}

	}

	for (auxI = 0; auxI < 12; auxI++) {

		for (auxII = 0; auxII < 16; auxII++) {

			if (towers[auxI][auxII] != NULL) {

				tPosX = towers[auxI][auxII]->posX+20;
				tPosY = towers[auxI][auxII]->posY+20;
				tRadius = (towers[auxI][auxII]->selfRange*40)+20;

				// Econtramos inimigos para tTormal e tSplash

				if (towers[auxI][auxII]->type == tNormal) {

					bulletDamage *= 1 + (0.05*towers[auxI][auxII]->beaconRank);

					prefCmp = shootingPrefs[0];

					prefCmpValue = prefCmpValueCmp = -1;

					cmpTarget = NULL;

					for (auxIII = 0; auxIII < qntEnemies; auxIII++) {

						if (enemies[auxIII] != NULL) {

							if (enemies[auxIII]->distanceWalked >= 10){

								if (insideCircularArea(enemies[auxIII]->posX+20, enemies[auxIII]->posY+20, tPosX, tPosY, tRadius, &distance) == 1) {

									switch (prefCmp){

										case 1: prefCmpValue = enemies[auxIII]->hp; break;

										case 2: prefCmpValue = enemies[auxIII]->totalHp - enemies[auxIII]->hp; break;

										case 3: prefCmpValue = enemies[auxIII]->distanceWalked; break;

										case 4: prefCmpValue = tRadius - distance; break;

									}

									if (prefCmpValue > prefCmpValueCmp){

										prefCmpValueCmp = prefCmpValue;

										cmpTarget = enemies[auxIII];

									}

								}

							}

						}

					}

					if (cmpTarget != NULL){

						towers[auxI][auxII]->target = cmpTarget;

						if (towers[auxI][auxII]->ticksForFire == 0) {

							bulletDamage = towers[auxI][auxII]->damage;

							newBullet(&*(bullets), tPosX, tPosY, bulletDamage, 4.8, makeacol(0, 200, 255, 255), 2, towers[auxI][auxII], true, towers[auxI][auxII]->target);

							towers[auxI][auxII]->ticksForFire = towers[auxI][auxII]->fireTimer;

						}

					}else{

						towers[auxI][auxII]->target = NULL;

					}

					if (towers[auxI][auxII]->ticksForFire > 0) {

						towers[auxI][auxII]->ticksForFire--;

					}

				}

				// Encontramos inimigos para a tSplash

				if (towers[auxI][auxII]->type == tSplash) {

					prefCmp = shootingPrefs[1];

					prefCmpValue = prefCmpValueCmp = -1;

					cmpTarget = NULL;

					for (auxIII = 0; auxIII < qntEnemies; auxIII++) {

						if (enemies[auxIII] != NULL) {

							if (enemies[auxIII]->distanceWalked >= 10){

								if (insideCircularArea(enemies[auxIII]->posX+20, enemies[auxIII]->posY+20, tPosX, tPosY, tRadius, &distance) == 1) {

									switch (prefCmp){

										case 1: prefCmpValue = enemies[auxIII]->hp; break;

										case 2: prefCmpValue = enemies[auxIII]->totalHp - enemies[auxIII]->hp; break;

										case 3: prefCmpValue = enemies[auxIII]->distanceWalked; break;

										case 4: prefCmpValue = tRadius - distance; break;

									}

									if (prefCmpValue > prefCmpValueCmp){

										prefCmpValueCmp = prefCmpValue;

										cmpTarget = enemies[auxIII];

									}

								}

							}

						}

					}

					if (cmpTarget != NULL){

						towers[auxI][auxII]->target = cmpTarget;

						if (towers[auxI][auxII]->ticksForFire == 0) {

							bulletDamage = towers[auxI][auxII]->damage;

							newBullet(&*(bullets), tPosX, tPosY, bulletDamage, 4.8, makeacol(230, 40, 15, 255), 2, towers[auxI][auxII], true, towers[auxI][auxII]->target);

							towers[auxI][auxII]->ticksForFire = towers[auxI][auxII]->fireTimer;

						}

					}else{

						towers[auxI][auxII]->target = NULL;

					}

					if (towers[auxI][auxII]->ticksForFire > 0) {

						towers[auxI][auxII]->ticksForFire--;

					}

				}

				// Encontramos inimigos para tSlow

				if (towers[auxI][auxII]->type == tSlow){

					if (towers[auxI][auxII]->slowTargets == NULL) {

						prefCmp = shootingPrefs[1];

						prefCmpValue = prefCmpValueCmp = -1;

						cmpTarget = NULL;

						for (auxIII = 0; auxIII < qntEnemies; auxIII++) {

							if (enemies[auxIII] != NULL) {

								if (enemies[auxIII]->distanceWalked >= 10){

									if (enemies[auxIII]->type != eSafer && enemies[auxIII]->isSlower == false){

										switch (prefCmp){

											case 1: prefCmpValue = enemies[auxIII]->hp; cmpDistance = false; break;

											case 2: prefCmpValue = enemies[auxIII]->totalHp - enemies[auxIII]->hp; cmpDistance = false; break;

											case 3: prefCmpValue = enemies[auxIII]->distanceWalked; cmpDistance = false; break;

											case 4: cmpDistance = true; break;

										}

										if (insideCircularArea(enemies[auxIII]->posX+20, enemies[auxIII]->posY+20, tPosX, tPosY, tRadius, &distance) == 1) {

											if (slowVectorIndex < towers[auxI][auxII]->rank){

												enemies[auxIII]->isSlower = true;

												enemies[auxIII]->beaconRankSlow = towers[auxI][auxII]->beaconRank;

												slowVector = (Enemie **) realloc(slowVector, (slowVectorIndex+1)*sizeof(Enemie));

												slowVector[slowVectorIndex] = enemies[auxIII];

												slowVectorIndex++;

											}else{

												for (auxIIIIII = 0; auxIIIIII < towers[auxI][auxII]->rank; auxIIIIII++){

													switch (prefCmp){

														case 1: prefCmpValueCmp = slowVector[auxIIIIII]->hp; cmpDistance = false; break;

														case 2: prefCmpValueCmp = slowVector[auxIIIIII]->totalHp - slowVector[auxIIIIII]->hp; cmpDistance = false; break;

														case 3: prefCmpValueCmp = slowVector[auxIIIIII]->distanceWalked; cmpDistance = false; break;

														case 4: cmpDistance = true; break;

													}

													if (prefCmpValue > prefCmpValueCmp){

														if (cmpDistance == true){ prefCmpValue = tRadius - distance; }

														slowVector[auxIIIIII]->isSlower = false;
														slowVector[auxIIIIII]->beaconRankSlow = 0;

														enemies[auxIII]->isSlower = true;
														enemies[auxIII]->beaconRankSlow = towers[auxI][auxII]->beaconRank;
														slowVector[auxIIIIII] = enemies[auxIII];

													}

												}

											}

										}

									}

								}

							}

						}

						towers[auxI][auxII]->slowTargets = slowVector;

						towers[auxI][auxII]->qntSlowTargets = slowVectorIndex;

					}

					slowVector = NULL;
					slowVectorIndex = 0;

				}

				// Encontramos inimigos para tPoison

				if (towers[auxI][auxII]->type == tPoison){

					if (towers[auxI][auxII]->ticksForFire == 0 || towers[auxI][auxII]->slowTargets == NULL) {

						towers[auxI][auxII]->ticksForFire = towers[auxI][auxII]->ticksPerFire;

						for (auxIII = 0; auxIII < qntEnemies; auxIII++) {

							if (enemies[auxIII] != NULL) {

								if (insideCircularArea(enemies[auxIII]->posX+20, enemies[auxIII]->posY+20, tPosX, tPosY, tRadius, NULL) == 1) {

									if (enemies[auxIII]->isPoisoned == false || enemies[auxIII]->poisonDamage < towers[auxI][auxII]->damage){

										enemies[auxIII]->isPoisoned = true;
										enemies[auxIII]->poisonDamage = towers[auxI][auxII]->damage;

										enemies[auxIII]->beaconRankPoison = towers[auxI][auxII]->beaconRank;

									}

								}

							}

						}

						towers[auxI][auxII]->slowTargets = slowVector;

					}

					if (towers[auxI][auxII]->ticksForFire > 0) {

						towers[auxI][auxII]->ticksForFire--;

					}


				}

			}

		}

	}

}

void newBullet(Bullet **bullets, int posX, int posY, float damage, float speed, int bulletColor, int bulletRadius, Tower *sender, int shallDivide, Enemie *target){

	Bullet *nBullet = (Bullet *) malloc(sizeof(Bullet));

	nBullet->posX = posX;
	nBullet->posY = posY;
	nBullet->damage = damage;
	nBullet->speed = speed;
	nBullet->bulletColor = bulletColor;
	nBullet->bulletRadius = bulletRadius;
	nBullet->sender = sender;
	nBullet->shallDivide = shallDivide;
	nBullet->target = target;
	nBullet->nextBullet = NULL;

	if (*bullets == NULL) {

		*bullets = nBullet;

	}else{

		Bullet *aux = *bullets;

		while(aux->nextBullet != NULL){

			aux = aux->nextBullet;

		}

		aux->nextBullet = nBullet;

	}

}

void drawBullets(BITMAP *window, Bullet **bulletsAd, Enemie **enemies, int qntEnemies, SAMPLE *normalEffect, SAMPLE *splashEffect) {

	Bullet *bullets = *(bulletsAd);

	Bullet *aux = bullets;

	Bullet *removalAux = NULL;

	int bulletEffect = 0;

	float damageEffect = 0;

	int auxSearch = 0;

	if (aux != NULL) {

		while(aux != NULL){

			if (aux->target != NULL) {

				circlefill(window, aux->posX, aux->posY, aux->bulletRadius, aux->bulletColor);
				aux->posX += (aux->target->posX + 20 - aux->posX)/aux->speed;
				aux->posY += (aux->target->posY + 20 - aux->posY)/aux->speed;

				if (pointRectCollision(aux->posX, aux->posY, (int)aux->target->posX+10, (int)aux->target->posY+10, 20, 20) == 1) {

					if (aux->sender->type == tSplash && aux->shallDivide == true){

						for (auxSearch = 0; auxSearch < qntEnemies; auxSearch++){

							if (enemies[auxSearch] != NULL){

								if (enemies[auxSearch] != aux->target){

									if (insideCircularArea(enemies[auxSearch]->posX+20, enemies[auxSearch]->posY+20, aux->target->posX+20, aux->target->posY+20, ((aux->sender->multipleRange+aux->sender->beaconRank)*40)+20, NULL) == 1){

										if(enemies[auxSearch]->type != eRSplash) {

										    newBullet(&*(bulletsAd), aux->target->posX + 20, aux->target->posY + 20, 0.01*aux->damage*aux->sender->multipleDamage, aux->speed, makeacol(255, 30, 30, 255), 1, aux->sender, false, enemies[auxSearch]);
										}

									}

								}

							}

						}

					}

					bulletEffect = rand()%100;

					damageEffect = (aux->damage - aux->target->defense);

					if (bulletEffect <= 2){

						damageEffect *= 0.8;

					}else if (bulletEffect >= 95){

						damageEffect *= 1.3;

					}

					damageEffect = (damageEffect < 5 ? 5 : damageEffect);

					aux->target->hp -= damageEffect;

					if(aux->sender->type == tNormal) {play_sample(normalEffect, 255, 0, 1000, 0);}

					if(aux->sender->type == tSplash) {play_sample(splashEffect, 255, 0, 1000, 0);}

					aux->target = NULL;

				}

			}else{

				if (aux != bullets){

					removalAux = bullets;

					while(removalAux->nextBullet != aux){ removalAux = removalAux->nextBullet; }

					removalAux->nextBullet = aux->nextBullet;

					free(aux);

					aux = removalAux;

				}

			}

			aux = aux->nextBullet;

		}

	}

}

void drawSlows(BITMAP *window, Tower ***towers){

	int auxI,auxII,auxIII;

	for (auxI = 0; auxI<12; auxI++){

		for (auxII = 0; auxII<16; auxII++){

			if (towers[auxI][auxII] != NULL){

				if (towers[auxI][auxII]->type == tSlow && towers[auxI][auxII]->slowTargets != NULL){

					for (auxIII = 0; auxIII < towers[auxI][auxII]->qntSlowTargets; auxIII++) {

						if (towers[auxI][auxII]->slowTargets[auxIII] != NULL) {

							fastline(window, towers[auxI][auxII]->posX+20, towers[auxI][auxII]->posY+20, towers[auxI][auxII]->slowTargets[auxIII]->posX+20, towers[auxI][auxII]->slowTargets[auxIII]->posY+20, makeacol(245, 250, 100, 255));

							circlefill(window, towers[auxI][auxII]->posX+20, towers[auxI][auxII]->posY+20, 20, makeacol(245, 250, 100, 200));

							towers[auxI][auxII]->slowTargets[auxIII]->isSlower = false;

						}

					}

					towers[auxI][auxII]->slowTargets = NULL;
					towers[auxI][auxII]->qntSlowTargets = 0;

				}

			}

		}

	}

}

void poisonEnemies(Enemie **enemies, int qntEnemies){

	int aux;

	for (aux = 0; aux < qntEnemies; aux++){

		if (enemies[aux] != NULL){

			if (enemies[aux]->isPoisoned == true && enemies[aux]->type != eSafer){

				enemies[aux]->hp -= enemies[aux]->poisonDamage+enemies[aux]->beaconRankPoison;
				enemies[aux]->isPoisoned = false;
				enemies[aux]->poisonDamage = 0;

			}

		}

	}

}

void resetBeaconEffect(Tower ***towers){

	int auxI,auxII;

	for (auxI = 0; auxI < 12; auxI++){

		for (auxII = 0; auxII < 16; auxII++){

			if (towers[auxI][auxII] != NULL){

				towers[auxI][auxII]->beaconEffect = false;
				towers[auxI][auxII]->beaconRank = 0;

			}

		}

	}

}

