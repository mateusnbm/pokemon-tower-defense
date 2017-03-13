#include <stdio.h>
#include <time.h>
#include <allegro.h>
#include "Classes/MathLibs.h"
#include "Classes/DrawLibs.h"
#include "Classes/MemoryLibs.h"
#include "Classes/LevelLibs.h"
#include "Classes/UIButton.h"
#include "Classes/UIBlitButton.h"
#include "Classes/UITextField.h"

#define true 1
#define false 0

#define splashScreenDuration 50
#define loadingMainMenuDuration 200
#define loadingLevelDuration 200

#define qntLevels 1
#define qntMaxLevelsLinha 5
#define levelButtonW 100
#define levelButtonH 100

volatile int ticks;
void tickCounter () { ticks++; }
END_OF_FUNCTION(tickCounter)

enum {

    telaSplashScreen, telaEndScreen, telaMenuLoading, telaMenuPrincipal, telaMenuLevels, telaMenuJogar, telaResultado1, telaResultado2, telaAlmanaqueMenu, telaAlmanaqueJogo

};

enum{

	pMoreLifer,pLessLifer,pAfterPath,pClosest

};

int mouseOverBitmap (BITMAP *obj, int posX, int posY) {

    int mouseOver = 0;

    if (mouse_x >= posX && mouse_x <= posX + obj->w) {

        if (mouse_y >= posY && mouse_y <= posY + obj->h) {

            mouseOver = 1;

        }

    }

    return mouseOver;
}

void menuSplashScreen (int duracaoMSEC) {

    ticks = 0;

    int sairTela = false;

    int old_ticks = 0;

    int tempoPassadoMSEC = 0;

    BITMAP *screenBuffer = create_bitmap(SCREEN_W, SCREEN_H);

    BITMAP *splashImage = load_bitmap("Imagens/SplashScreen/cintendo_800x600.bmp", NULL);

	while (!sairTela) {

        while (!sairTela && ticks > 0) {

            if(key[KEY_ESC]){ sairTela = true; }

            if (old_ticks == 0) { old_ticks = ticks; }

            if (ticks != old_ticks) {

                old_ticks = ticks;

                tempoPassadoMSEC++;

                if (tempoPassadoMSEC == duracaoMSEC) { sairTela = true;}

            }

            draw_sprite(screenBuffer, splashImage, 0, 0);

            draw_sprite(screen, screenBuffer, 0, 0);

            clear(screenBuffer);

        }

    }

    destroy_bitmap(splashImage);

    destroy_bitmap(screenBuffer);

}

void menuShootingPrefs (BITMAP *window, int index, int *prefs){

	int exitScreen = false;

	int mouseLocker = (mouse_b == 1 ? true : false);

	BITMAP *screenBuffer = create_bitmap(SCREEN_W, SCREEN_H);

    BITMAP *menuImage_Mouse[2];
    menuImage_Mouse[0] = load_bitmap("Imagens/Cursor/cursor.bmp", NULL);
    menuImage_Mouse[1] = load_bitmap("Imagens/Cursor/cursor_clicked.bmp", NULL);
    int menuImage_Mouse_Frame = 0;

	BITMAP *pref1Images[4];
	pref1Images[0] = load_bitmap("Imagens/Redirecionamento/MoreHPButton.bmp", NULL);
	pref1Images[1] = load_bitmap("Imagens/Redirecionamento/MoreHPButton.bmp", NULL);
	pref1Images[2] = load_bitmap("Imagens/Redirecionamento/MoreHPButton.bmp", NULL);
	pref1Images[3] = load_bitmap("Imagens/Redirecionamento/MoreHPButton.bmp", NULL);
	UIButton *pref1Button = uibutton_create(pref1Images, NULL, (SCREEN_W/2)-230, (SCREEN_H/2)-40, 100, 50);

	BITMAP *pref2Images[4];
	pref2Images[0] = load_bitmap("Imagens/Redirecionamento/LessHPButton.bmp", NULL);
	pref2Images[1] = load_bitmap("Imagens/Redirecionamento/LessHPButton.bmp", NULL);
	pref2Images[2] = load_bitmap("Imagens/Redirecionamento/LessHPButton.bmp", NULL);
	pref2Images[3] = load_bitmap("Imagens/Redirecionamento/LessHPButton.bmp", NULL);
	UIButton *pref2Button = uibutton_create(pref2Images, NULL, (SCREEN_W/2)-110, (SCREEN_H/2)-40, 100, 50);

	BITMAP *pref3Images[4];
	pref3Images[0] = load_bitmap("Imagens/Redirecionamento/FoeWithMostDistanceWalkedButton.bmp", NULL);
	pref3Images[1] = load_bitmap("Imagens/Redirecionamento/FoeWithMostDistanceWalkedButton.bmp", NULL);
	pref3Images[2] = load_bitmap("Imagens/Redirecionamento/FoeWithMostDistanceWalkedButton.bmp", NULL);
	pref3Images[3] = load_bitmap("Imagens/Redirecionamento/FoeWithMostDistanceWalkedButton.bmp", NULL);
	UIButton *pref3Button = uibutton_create(pref3Images, NULL, (SCREEN_W/2)+10, (SCREEN_H/2)-40, 100, 50);

	BITMAP *pref4Images[4];
	pref4Images[0] = load_bitmap("Imagens/Redirecionamento/NearestFoeButton.bmp", NULL);
	pref4Images[1] = load_bitmap("Imagens/Redirecionamento/NearestFoeButton.bmp", NULL);
	pref4Images[2] = load_bitmap("Imagens/Redirecionamento/NearestFoeButton.bmp", NULL);
	pref4Images[3] = load_bitmap("Imagens/Redirecionamento/NearestFoeButton.bmp", NULL);
	UIButton *pref4Button = uibutton_create(pref4Images, NULL, (SCREEN_W/2)+130, (SCREEN_H/2)-40, 100, 50);

	BITMAP *foo[4];

	switch(prefs[index-1]){

		case 1:

			foo[0] = load_bitmap("Imagens/Redirecionamento/MoreHPButtonClicked.bmp", NULL);
			foo[1] = load_bitmap("Imagens/Redirecionamento/MoreHPButtonClicked.bmp", NULL);
			foo[2] = load_bitmap("Imagens/Redirecionamento/MoreHPButtonClicked.bmp", NULL);
			foo[3] = load_bitmap("Imagens/Redirecionamento/MoreHPButtonClicked.bmp", NULL);
			uibutton_setimages(pref1Button, foo);

			break;

		case 2:

			foo[0] = load_bitmap("Imagens/Redirecionamento/LessHPButtonClicked.bmp", NULL);
			foo[1] = load_bitmap("Imagens/Redirecionamento/LessHPButtonClicked.bmp", NULL);
			foo[2] = load_bitmap("Imagens/Redirecionamento/LessHPButtonClicked.bmp", NULL);
			foo[3] = load_bitmap("Imagens/Redirecionamento/LessHPButtonClicked.bmp", NULL);
			uibutton_setimages(pref2Button, foo);

			break;

		case 3:

			foo[0] = load_bitmap("Imagens/Redirecionamento/FoeWithMostDistanceWalkedButtonClicked.bmp", NULL);
			foo[1] = load_bitmap("Imagens/Redirecionamento/FoeWithMostDistanceWalkedButtonClicked.bmp", NULL);
			foo[2] = load_bitmap("Imagens/Redirecionamento/FoeWithMostDistanceWalkedButtonClicked.bmp", NULL);
			foo[3] = load_bitmap("Imagens/Redirecionamento/FoeWithMostDistanceWalkedButtonClicked.bmp", NULL);
			uibutton_setimages(pref3Button, foo);

			break;

		case 4:

			foo[0] = load_bitmap("Imagens/Redirecionamento/NearestFoeButtonClicked.bmp", NULL);
			foo[1] = load_bitmap("Imagens/Redirecionamento/NearestFoeButtonClicked.bmp", NULL);
			foo[2] = load_bitmap("Imagens/Redirecionamento/NearestFoeButtonClicked.bmp", NULL);
			foo[3] = load_bitmap("Imagens/Redirecionamento/NearestFoeButtonClicked.bmp", NULL);
			uibutton_setimages(pref4Button, foo);

			break;

	}

	while (!exitScreen) {

		if (key[KEY_ESC]){ exitScreen = true; }

	    while (!exitScreen && ticks > 0) {

	    	if (mouse_b != 1) { mouseLocker = false; }

	    	uibutton_update(pref1Button);
	    	uibutton_update(pref2Button);
	    	uibutton_update(pref3Button);
	    	uibutton_update(pref4Button);

	    	if (pref1Button->isClicked == true && mouseLocker == false){

	    		prefs[index-1] = 1;

	    		mouseLocker = true;

	    		exitScreen = true;

	    	}

	    	if (pref2Button->isClicked == true && mouseLocker == false){

	    		prefs[index-1] = 2;

	    		mouseLocker = true;

	    		exitScreen = true;

	    	}

	    	if (pref3Button->isClicked == true && mouseLocker == false){

	    		prefs[index-1] = 3;

	    		mouseLocker = true;

	    		exitScreen = true;

	    	}

	    	if (pref4Button->isClicked == true && mouseLocker == false){

	    		prefs[index-1] = 4;

	    		mouseLocker = true;

	    		exitScreen = true;



	    	}

	        draw_sprite(screenBuffer, window, 0, 0);

	        rectfill(screenBuffer, 0, 0, SCREEN_W, SCREEN_H, makeacol(0, 0, 0, 125));

			rectfill(screenBuffer, (SCREEN_W/2)-240, (SCREEN_H/2)-50, (SCREEN_W/2)+240, (SCREEN_H/2)+50, makeacol(255, 255, 255, 255));

			uibutton_draw(pref1Button, pref1Button->posX, pref1Button->posY, screenBuffer);
			uibutton_draw(pref2Button, pref2Button->posX, pref2Button->posY, screenBuffer);
			uibutton_draw(pref3Button, pref3Button->posX, pref3Button->posY, screenBuffer);
			uibutton_draw(pref4Button, pref4Button->posX, pref4Button->posY, screenBuffer);

			draw_sprite(screenBuffer, menuImage_Mouse[menuImage_Mouse_Frame], mouse_x-6, mouse_y);

	        draw_sprite(screen, screenBuffer, 0, 0);

	        clear(screenBuffer);

	        ticks--;

	    }

	}

	destroy_bitmap(menuImage_Mouse[0]);
	destroy_bitmap(menuImage_Mouse[1]);
	destroy_bitmap(screenBuffer);

	uibutton_release(pref1Button);
	uibutton_release(pref2Button);
	uibutton_release(pref3Button);
	uibutton_release(pref4Button);

}

int pokeDexScreen (int lastScreen) {

    ticks = 0;

    BITMAP *mouseImage[2];
    mouseImage[0] = load_bitmap("Imagens/Cursor/cursor.bmp", NULL);
    mouseImage[1] = load_bitmap("Imagens/Cursor/cursor_clicked.bmp", NULL);
    int mouseImage_Frame = 0;

    BITMAP *screenBuffer = create_bitmap(SCREEN_W, SCREEN_H);
    BITMAP *profOakLab = load_bitmap("Imagens/Pokedex/TelaTutorial.bmp", NULL);
    BITMAP *icons = load_bitmap("Imagens/Pokedex/PokeIcons.bmp", NULL);
    BITMAP *sprites = load_bitmap("Imagens/Pokedex/PokeSprites.bmp", NULL);

    MIDI *screenMusic = load_midi("Musicas/MusicaPokedex.mid");

    if(lastScreen != 0) {

		play_midi(screenMusic, true);
    }

    SAMPLE *pokemonCry = load_sample("Musicas/Cries/SquirtleCry.wav");

    int exitScreen = false;

    BITMAP *backImage = load_bitmap("Imagens/Pokedex/backButton_93x81.bmp", NULL);

    while(!exitScreen) {

        while(!exitScreen && ticks > 0) {

            if(mouse_x >= 20 && mouse_x <= 73 && mouse_y >= 540 && mouse_y <= 580 && mouse_b) { exitScreen = true; }

            if(mouse_b) {

                mouseImage_Frame = 1;

            } else {

                mouseImage_Frame = 0;
            }

            draw_sprite(screenBuffer, profOakLab, 0, 0);

            //Desenhamos os ícones dos Pokémons de Red

            textout_centre_ex(screenBuffer, font, "RED'S POKEMON", 120, 20, makeacol(255, 0, 0, 100), -1);

            masked_blit(icons, screenBuffer, 0, 0, 40, 40, 40, 40);
            masked_blit(icons, screenBuffer, 40, 0, 100, 40, 40, 40);
            masked_blit(icons, screenBuffer, 80, 0, 160, 40, 40, 40);
            masked_blit(icons, screenBuffer, 120, 0, 40, 100, 40, 40);
            masked_blit(icons, screenBuffer, 160, 0, 100, 100, 40, 40);
            masked_blit(icons, screenBuffer, 200, 0, 160, 100, 40, 40);
            masked_blit(icons, screenBuffer, 0, 40, 40, 160, 40, 40);
            masked_blit(icons, screenBuffer, 40, 40, 100, 160, 40, 40);
            masked_blit(icons, screenBuffer, 80, 40, 160, 160, 40, 40);
            masked_blit(icons, screenBuffer, 120, 40, 40, 220, 40, 40);
            masked_blit(icons, screenBuffer, 160, 40, 100, 220, 40, 40);
            masked_blit(icons, screenBuffer, 200, 40, 160, 220, 40, 40);
            masked_blit(icons, screenBuffer, 0, 80, 40, 280, 40, 40);
            masked_blit(icons, screenBuffer, 40, 80, 100, 280, 40, 40);
            masked_blit(icons, screenBuffer, 80, 80, 160, 280, 40, 40);

            //Desenhamos os ícones dos Pokémons de Blue

            textout_centre_ex(screenBuffer, font, "BLUE'S POKEMON", 680, 20, makeacol(0, 0, 255, 100), -1);

            masked_blit(icons, screenBuffer, 120, 80, 600, 40, 40, 40);
            masked_blit(icons, screenBuffer, 160, 80, 660, 40, 40, 40);
            masked_blit(icons, screenBuffer, 200, 80, 720, 40, 40, 40);
            masked_blit(icons, screenBuffer, 0, 120, 600, 100, 40, 40);
            masked_blit(icons, screenBuffer, 40, 120, 660, 100, 40, 40);
            masked_blit(icons, screenBuffer, 80, 120, 720, 100, 40, 40);
            masked_blit(icons, screenBuffer, 120, 120, 600, 160, 40, 40);
            masked_blit(icons, screenBuffer, 160, 120, 660, 160, 40, 40);
            masked_blit(icons, screenBuffer, 200, 120, 720, 160, 40, 40);
            masked_blit(icons, screenBuffer, 0, 160, 600, 220, 40, 40);
            masked_blit(icons, screenBuffer, 40, 160, 660, 220, 40, 40);
            masked_blit(icons, screenBuffer, 80, 160, 720, 220, 40, 40);
            masked_blit(icons, screenBuffer, 120, 160, 600, 280, 40, 40);
            masked_blit(icons, screenBuffer, 160, 160, 660, 280, 40, 40);
            masked_blit(icons, screenBuffer, 200, 160, 720, 280, 40, 40);
            masked_blit(icons, screenBuffer, 0, 200, 600, 340, 40, 40);
            masked_blit(icons, screenBuffer, 40, 200, 660, 340, 40, 40);
            masked_blit(icons, screenBuffer, 80, 200, 720, 340, 40, 40);
            masked_blit(icons, screenBuffer, 120, 200, 600, 400, 40, 40);
            masked_blit(icons, screenBuffer, 160, 200, 660, 400, 40, 40);
            masked_blit(icons, screenBuffer, 200, 200, 720, 400, 40, 40);
            masked_blit(icons, screenBuffer, 0, 240, 600, 460, 40, 40);

            // Infos Pokémons de Red

            if(mouse_x >= 40 && mouse_x <= 80 && mouse_y >= 40 && mouse_y <= 80) {

                masked_blit(sprites, screenBuffer, 0, 0, 360, 333, 80, 80);
                textprintf_centre_ex(screenBuffer, font, 399, 455, makecol(255, 255, 255), -1, "NAME: Squirtle");
                textprintf_centre_ex(screenBuffer, font, 399, 470, makecol(255, 255, 255), -1, "TYPE: Normal");
                textprintf_centre_ex(screenBuffer, font, 399, 485, makecol(255, 255, 255), -1, "ATTACK: Water Gun");
                textprintf_centre_ex(screenBuffer, font, 399, 500, makecol(255, 255, 255), -1, "EVOLVES FROM: Starting Form");
                textprintf_centre_ex(screenBuffer, font, 399, 515, makecol(255, 255, 255), -1, "EVOLVES INTO: Wartotle (Level 3)");

                pokemonCry = load_sample("Musicas/Cries/SquirtleCry.wav");

                if(mouse_b) { play_sample(pokemonCry, 255, 0, 1000, 0); }
            }

            if(mouse_x >= 100 && mouse_x <= 140 && mouse_y >= 40 && mouse_y <= 80) {

                masked_blit(sprites, screenBuffer, 80, 0, 360, 333, 80, 80);
                textprintf_centre_ex(screenBuffer, font, 399, 455, makecol(255, 255, 255), -1, "NAME: Wartotle");
                textprintf_centre_ex(screenBuffer, font, 399, 470, makecol(255, 255, 255), -1, "TYPE: Normal");
                textprintf_centre_ex(screenBuffer, font, 399, 485, makecol(255, 255, 255), -1, "ATTACK: Water Gun");
                textprintf_centre_ex(screenBuffer, font, 399, 500, makecol(255, 255, 255), -1, "EVOLVES FROM: Squirtle (Level 3)");
                textprintf_centre_ex(screenBuffer, font, 399, 515, makecol(255, 255, 255), -1, "EVOLVES INTO: Blastoise (Level 5)");

                pokemonCry = load_sample("Musicas/Cries/WartotleCry.wav");

                if(mouse_b) { play_sample(pokemonCry, 255, 0, 1000, 0); }
            }

            if(mouse_x >= 160 && mouse_x <= 200 && mouse_y >= 40 && mouse_y <= 80) {

                masked_blit(sprites, screenBuffer, 160, 0, 360, 333, 80, 80);
                textprintf_centre_ex(screenBuffer, font, 399, 455, makecol(255, 255, 255), -1, "NAME: Blastoise");
                textprintf_centre_ex(screenBuffer, font, 399, 470, makecol(255, 255, 255), -1, "TYPE: Normal");
                textprintf_centre_ex(screenBuffer, font, 399, 485, makecol(255, 255, 255), -1, "ATTACK: Water Gun");
                textprintf_centre_ex(screenBuffer, font, 399, 500, makecol(255, 255, 255), -1, "EVOLVES FROM: Wartotle (Level 5)");
                textprintf_centre_ex(screenBuffer, font, 399, 515, makecol(255, 255, 255), -1, "EVOLVES INTO: Final Form");

                pokemonCry = load_sample("Musicas/Cries/BlastoiseCry.wav");

                if(mouse_b) { play_sample(pokemonCry, 255, 0, 1000, 0); }
            }

            if(mouse_x >= 40 && mouse_x <= 80 && mouse_y >= 100 && mouse_y <= 140) {

                masked_blit(sprites, screenBuffer, 240, 0, 360, 333, 80, 80);
                textprintf_centre_ex(screenBuffer, font, 399, 455, makecol(255, 255, 255), -1, "NAME: Charmander");
                textprintf_centre_ex(screenBuffer, font, 399, 470, makecol(255, 255, 255), -1, "TYPE: Splash");
                textprintf_centre_ex(screenBuffer, font, 399, 485, makecol(255, 255, 255), -1, "ATTACK: Flame Burst");
                textprintf_centre_ex(screenBuffer, font, 399, 500, makecol(255, 255, 255), -1, "EVOLVES FROM: Starting Form");
                textprintf_centre_ex(screenBuffer, font, 399, 515, makecol(255, 255, 255), -1, "EVOLVES INTO: Charmeleon (Level 3)");

                pokemonCry = load_sample("Musicas/Cries/CharmanderCry.wav");

                if(mouse_b) { play_sample(pokemonCry, 255, 0, 1000, 0); }
            }

            if(mouse_x >= 100 && mouse_x <= 140 && mouse_y >= 100 && mouse_y <= 140) {

                masked_blit(sprites, screenBuffer, 320, 0, 360, 333, 80, 80);
                textprintf_centre_ex(screenBuffer, font, 399, 455, makecol(255, 255, 255), -1, "NAME: Charmeleon");
                textprintf_centre_ex(screenBuffer, font, 399, 470, makecol(255, 255, 255), -1, "TYPE: Splash");
                textprintf_centre_ex(screenBuffer, font, 399, 485, makecol(255, 255, 255), -1, "ATTACK: Flame Burst");
                textprintf_centre_ex(screenBuffer, font, 399, 500, makecol(255, 255, 255), -1, "EVOLVES FROM: Charmander (Level 3)");
                textprintf_centre_ex(screenBuffer, font, 399, 515, makecol(255, 255, 255), -1, "EVOLVES INTO: Charizard (Level 5)");

                pokemonCry = load_sample("Musicas/Cries/CharmeleonCry.wav");

                if(mouse_b) { play_sample(pokemonCry, 255, 0, 1000, 0); }
            }

            if(mouse_x >= 160 && mouse_x <= 200 && mouse_y >= 100 && mouse_y <= 140) {

                masked_blit(sprites, screenBuffer, 400, 0, 360, 333, 80, 80);
                textprintf_centre_ex(screenBuffer, font, 399, 455, makecol(255, 255, 255), -1, "NAME: Charizard");
                textprintf_centre_ex(screenBuffer, font, 399, 470, makecol(255, 255, 255), -1, "TYPE: Splash");
                textprintf_centre_ex(screenBuffer, font, 399, 485, makecol(255, 255, 255), -1, "ATTACK: Flame Burst");
                textprintf_centre_ex(screenBuffer, font, 399, 500, makecol(255, 255, 255), -1, "EVOLVES FROM: Charmeleon (Level 5)");
                textprintf_centre_ex(screenBuffer, font, 399, 515, makecol(255, 255, 255), -1, "EVOLVES INTO: Final Form");

                pokemonCry = load_sample("Musicas/Cries/CharizardCry.wav");

                if(mouse_b) { play_sample(pokemonCry, 255, 0, 1000, 0); }
            }

            if(mouse_x >= 40 && mouse_x <= 80 && mouse_y >= 160 && mouse_y <= 200) {

                masked_blit(sprites, screenBuffer, 0, 80, 360, 333, 80, 80);
                textprintf_centre_ex(screenBuffer, font, 399, 455, makecol(255, 255, 255), -1, "NAME: Pichu");
                textprintf_centre_ex(screenBuffer, font, 399, 470, makecol(255, 255, 255), -1, "TYPE: Slow");
                textprintf_centre_ex(screenBuffer, font, 399, 485, makecol(255, 255, 255), -1, "ATTACK: Thunder Wave");
                textprintf_centre_ex(screenBuffer, font, 399, 500, makecol(255, 255, 255), -1, "EVOLVES FROM: Starting Form");
                textprintf_centre_ex(screenBuffer, font, 399, 515, makecol(255, 255, 255), -1, "EVOLVES INTO: Pikachu (Level 3)");

                pokemonCry = load_sample("Musicas/Cries/PichuCry.wav");

                if(mouse_b) { play_sample(pokemonCry, 255, 0, 1000, 0); }
            }

            if(mouse_x >= 100 && mouse_x <= 140 && mouse_y >= 160 && mouse_y <= 200) {

                masked_blit(sprites, screenBuffer, 80, 80, 360, 333, 80, 80);
                textprintf_centre_ex(screenBuffer, font, 399, 455, makecol(255, 255, 255), -1, "NAME: Pikachu");
                textprintf_centre_ex(screenBuffer, font, 399, 470, makecol(255, 255, 255), -1, "TYPE: Slow");
                textprintf_centre_ex(screenBuffer, font, 399, 485, makecol(255, 255, 255), -1, "ATTACK: Thunder Wave");
                textprintf_centre_ex(screenBuffer, font, 399, 500, makecol(255, 255, 255), -1, "EVOLVES FROM: Pichu (Level 3)");
                textprintf_centre_ex(screenBuffer, font, 399, 515, makecol(255, 255, 255), -1, "EVOLVES INTO: Raichu (Level 5)");

                pokemonCry = load_sample("Musicas/Cries/PikachuCry.wav");

                if(mouse_b) { play_sample(pokemonCry, 255, 0, 1000, 0); }
            }

            if(mouse_x >= 160 && mouse_x <= 200 && mouse_y >= 160 && mouse_y <= 200) {

                masked_blit(sprites, screenBuffer, 160, 80, 360, 333, 80, 80);
                textprintf_centre_ex(screenBuffer, font, 399, 455, makecol(255, 255, 255), -1, "NAME: Raichu");
                textprintf_centre_ex(screenBuffer, font, 399, 470, makecol(255, 255, 255), -1, "TYPE: Slow");
                textprintf_centre_ex(screenBuffer, font, 399, 485, makecol(255, 255, 255), -1, "ATTACK: Thunder Wave");
                textprintf_centre_ex(screenBuffer, font, 399, 500, makecol(255, 255, 255), -1, "EVOLVES FROM: Pikachu (Level 5)");
                textprintf_centre_ex(screenBuffer, font, 399, 515, makecol(255, 255, 255), -1, "EVOLVES INTO: Final Form");

                pokemonCry = load_sample("Musicas/Cries/RaichuCry.wav");

                if(mouse_b) { play_sample(pokemonCry, 255, 0, 1000, 0); }
            }

            if(mouse_x >= 40 && mouse_x <= 80 && mouse_y >= 220 && mouse_y <= 260) {

                masked_blit(sprites, screenBuffer, 240, 80, 360, 333, 80, 80);
                textprintf_centre_ex(screenBuffer, font, 399, 455, makecol(255, 255, 255), -1, "NAME: Bulbasaur");
                textprintf_centre_ex(screenBuffer, font, 399, 470, makecol(255, 255, 255), -1, "TYPE: Poison");
                textprintf_centre_ex(screenBuffer, font, 399, 485, makecol(255, 255, 255), -1, "ATTACK: PoisonPowder");
                textprintf_centre_ex(screenBuffer, font, 399, 500, makecol(255, 255, 255), -1, "EVOLVES FROM: Starting Form");
                textprintf_centre_ex(screenBuffer, font, 399, 515, makecol(255, 255, 255), -1, "EVOLVES INTO: Ivysaur (Level 3)");

                pokemonCry = load_sample("Musicas/Cries/BulbasaurCry.wav");

                if(mouse_b) { play_sample(pokemonCry, 255, 0, 1000, 0); }
            }

            if(mouse_x >= 100 && mouse_x <= 140 && mouse_y >= 220 && mouse_y <= 260) {

                masked_blit(sprites, screenBuffer, 320, 80, 360, 333, 80, 80);
                textprintf_centre_ex(screenBuffer, font, 399, 455, makecol(255, 255, 255), -1, "NAME: Ivysaur");
                textprintf_centre_ex(screenBuffer, font, 399, 470, makecol(255, 255, 255), -1, "TYPE: Poison");
                textprintf_centre_ex(screenBuffer, font, 399, 485, makecol(255, 255, 255), -1, "ATTACK: PoisonPowder");
                textprintf_centre_ex(screenBuffer, font, 399, 500, makecol(255, 255, 255), -1, "EVOLVES FROM: Bulbasaur (Level 3)");
                textprintf_centre_ex(screenBuffer, font, 399, 515, makecol(255, 255, 255), -1, "EVOLVES INTO: Venusaur (Level 5)");

                pokemonCry = load_sample("Musicas/Cries/IvysaurCry.wav");

                if(mouse_b) { play_sample(pokemonCry, 255, 0, 1000, 0); }
            }

            if(mouse_x >= 160 && mouse_x <= 200 && mouse_y >= 220 && mouse_y <= 260) {

                masked_blit(sprites, screenBuffer, 400, 80, 360, 333, 80, 80);
                textprintf_centre_ex(screenBuffer, font, 399, 455, makecol(255, 255, 255), -1, "NAME: Venusaur");
                textprintf_centre_ex(screenBuffer, font, 399, 470, makecol(255, 255, 255), -1, "TYPE: Poison");
                textprintf_centre_ex(screenBuffer, font, 399, 485, makecol(255, 255, 255), -1, "ATTACK: PoisonPowder");
                textprintf_centre_ex(screenBuffer, font, 399, 500, makecol(255, 255, 255), -1, "EVOLVES FROM: Ivysaur (Level 5)");
                textprintf_centre_ex(screenBuffer, font, 399, 515, makecol(255, 255, 255), -1, "EVOLVES INTO: Final Form");

                pokemonCry = load_sample("Musicas/Cries/VenusaurCry.wav");

                if(mouse_b) { play_sample(pokemonCry, 255, 0, 1000, 0); }
            }

            if(mouse_x >= 40 && mouse_x <= 80 && mouse_y >= 280 && mouse_y <= 320) {

                masked_blit(sprites, screenBuffer, 0, 160, 360, 333, 80, 80);
                textprintf_centre_ex(screenBuffer, font, 399, 455, makecol(255, 255, 255), -1, "NAME: Happiny");
                textprintf_centre_ex(screenBuffer, font, 399, 470, makecol(255, 255, 255), -1, "TYPE: Beacon");
                textprintf_centre_ex(screenBuffer, font, 399, 485, makecol(255, 255, 255), -1, "ATTACK: Wish");
                textprintf_centre_ex(screenBuffer, font, 399, 500, makecol(255, 255, 255), -1, "EVOLVES FROM: Starting Form");
                textprintf_centre_ex(screenBuffer, font, 399, 515, makecol(255, 255, 255), -1, "EVOLVES INTO: Chansey (Level 2)");

                pokemonCry = load_sample("Musicas/Cries/HappinyCry.wav");

                if(mouse_b) { play_sample(pokemonCry, 255, 0, 1000, 0); }
            }

            if(mouse_x >= 100 && mouse_x <= 140 && mouse_y >= 280 && mouse_y <= 320) {

                masked_blit(sprites, screenBuffer, 80, 160, 360, 333, 80, 80);
                textprintf_centre_ex(screenBuffer, font, 399, 455, makecol(255, 255, 255), -1, "NAME: Chansey");
                textprintf_centre_ex(screenBuffer, font, 399, 470, makecol(255, 255, 255), -1, "TYPE: Beacon");
                textprintf_centre_ex(screenBuffer, font, 399, 485, makecol(255, 255, 255), -1, "ATTACK: Wish");
                textprintf_centre_ex(screenBuffer, font, 399, 500, makecol(255, 255, 255), -1, "EVOLVES FROM: Happiny (Level 2)");
                textprintf_centre_ex(screenBuffer, font, 399, 515, makecol(255, 255, 255), -1, "EVOLVES INTO: Blissey (Level 3)");

                pokemonCry = load_sample("Musicas/Cries/ChanseyCry.wav");

                if(mouse_b) { play_sample(pokemonCry, 255, 0, 1000, 0); }
            }

            if(mouse_x >= 160 && mouse_x <= 200 && mouse_y >= 280 && mouse_y <= 320) {

                masked_blit(sprites, screenBuffer, 160, 160, 360, 333, 80, 80);
                textprintf_centre_ex(screenBuffer, font, 399, 455, makecol(255, 255, 255), -1, "NAME: Blissey");
                textprintf_centre_ex(screenBuffer, font, 399, 470, makecol(255, 255, 255), -1, "TYPE: Beacon");
                textprintf_centre_ex(screenBuffer, font, 399, 485, makecol(255, 255, 255), -1, "ATTACK: Wish");
                textprintf_centre_ex(screenBuffer, font, 399, 500, makecol(255, 255, 255), -1, "EVOLVES FROM: Chansey (Level 3)");
                textprintf_centre_ex(screenBuffer, font, 399, 515, makecol(255, 255, 255), -1, "EVOLVES INTO: Final Form");

                pokemonCry = load_sample("Musicas/Cries/BlisseyCry.wav");

                if(mouse_b) { play_sample(pokemonCry, 255, 0, 1000, 0); }
            }

            // Infos Pokémons de Blue

            if(mouse_x >= 600 && mouse_x <= 640 && mouse_y >= 40 && mouse_y <= 80) {

                masked_blit(sprites, screenBuffer, 240, 160, 360, 333, 80, 80);
                textprintf_centre_ex(screenBuffer, font, 399, 455, makecol(255, 255, 255), -1, "NAME: Eevee");
                textprintf_centre_ex(screenBuffer, font, 399, 470, makecol(255, 255, 255), -1, "TYPE: Normal");
                textprintf_centre_ex(screenBuffer, font, 399, 485, makecol(255, 255, 255), -1, "ABILITY: Adaptability");
                textprintf_centre_ex(screenBuffer, font, 399, 500, makecol(255, 255, 255), -1, "EVOLVES FROM: Starting Form");
                textprintf_centre_ex(screenBuffer, font, 399, 515, makecol(255, 255, 255), -1, "EVOLVES INTO: Multiple (Level 4)");

                pokemonCry = load_sample("Musicas/Cries/EeveeCry.wav");

                if(mouse_b) { play_sample(pokemonCry, 255, 0, 1000, 0); }
            }

            if(mouse_x >= 660 && mouse_x <= 700 && mouse_y >= 40 && mouse_y <= 80) {

                masked_blit(sprites, screenBuffer, 320, 160, 360, 333, 80, 80);
                textprintf_centre_ex(screenBuffer, font, 399, 455, makecol(255, 255, 255), -1, "NAME: Vaporeon");
                textprintf_centre_ex(screenBuffer, font, 399, 470, makecol(255, 255, 255), -1, "TYPE: Normal");
                textprintf_centre_ex(screenBuffer, font, 399, 485, makecol(255, 255, 255), -1, "ABILITY: Adaptability");
                textprintf_centre_ex(screenBuffer, font, 399, 500, makecol(255, 255, 255), -1, "EVOLVES FROM: Eevee (Level 4)");
                textprintf_centre_ex(screenBuffer, font, 399, 515, makecol(255, 255, 255), -1, "EVOLVES INTO: Final Form");

                pokemonCry = load_sample("Musicas/Cries/VaporeonCry.wav");

                if(mouse_b) { play_sample(pokemonCry, 255, 0, 1000, 0); }
            }

            if(mouse_x >= 720 && mouse_x <= 760 && mouse_y >= 40 && mouse_y <= 80) {

                masked_blit(sprites, screenBuffer, 400, 160, 360, 333, 80, 80);
                textprintf_centre_ex(screenBuffer, font, 399, 455, makecol(255, 255, 255), -1, "NAME: Jolteon");
                textprintf_centre_ex(screenBuffer, font, 399, 470, makecol(255, 255, 255), -1, "TYPE: Normal");
                textprintf_centre_ex(screenBuffer, font, 399, 485, makecol(255, 255, 255), -1, "ABILITY: Adaptability");
                textprintf_centre_ex(screenBuffer, font, 399, 500, makecol(255, 255, 255), -1, "EVOLVES FROM: Eevee (Level 4)");
                textprintf_centre_ex(screenBuffer, font, 399, 515, makecol(255, 255, 255), -1, "EVOLVES INTO: Final Form");

                pokemonCry = load_sample("Musicas/Cries/JolteonCry.wav");

                if(mouse_b) { play_sample(pokemonCry, 255, 0, 1000, 0); }
            }

            if(mouse_x >= 600 && mouse_x <= 640 && mouse_y >= 100 && mouse_y <= 140) {

                masked_blit(sprites, screenBuffer, 0, 240, 360, 333, 80, 80);
                textprintf_centre_ex(screenBuffer, font, 399, 455, makecol(255, 255, 255), -1, "NAME: Flareon");
                textprintf_centre_ex(screenBuffer, font, 399, 470, makecol(255, 255, 255), -1, "TYPE: Normal");
                textprintf_centre_ex(screenBuffer, font, 399, 485, makecol(255, 255, 255), -1, "ABILITY: Adaptability");
                textprintf_centre_ex(screenBuffer, font, 399, 500, makecol(255, 255, 255), -1, "EVOLVES FROM: Eevee (Level 4)");
                textprintf_centre_ex(screenBuffer, font, 399, 515, makecol(255, 255, 255), -1, "EVOLVES INTO: Final Form");

                pokemonCry = load_sample("Musicas/Cries/FlareonCry.wav");

                if(mouse_b) { play_sample(pokemonCry, 255, 0, 1000, 0); }
            }

            if(mouse_x >= 660 && mouse_x <= 700 && mouse_y >= 100 && mouse_y <= 140) {

                masked_blit(sprites, screenBuffer, 80, 240, 360, 333, 80, 80);
                textprintf_centre_ex(screenBuffer, font, 399, 455, makecol(255, 255, 255), -1, "NAME: Espeon");
                textprintf_centre_ex(screenBuffer, font, 399, 470, makecol(255, 255, 255), -1, "TYPE: Normal");
                textprintf_centre_ex(screenBuffer, font, 399, 485, makecol(255, 255, 255), -1, "ABILITY: Adaptability");
                textprintf_centre_ex(screenBuffer, font, 399, 500, makecol(255, 255, 255), -1, "EVOLVES FROM: Eevee (Level 4)");
                textprintf_centre_ex(screenBuffer, font, 399, 515, makecol(255, 255, 255), -1, "EVOLVES INTO: Final Form");

                pokemonCry = load_sample("Musicas/Cries/EspeonCry.wav");

                if(mouse_b) { play_sample(pokemonCry, 255, 0, 1000, 0); }
            }

            if(mouse_x >= 720 && mouse_x <= 760 && mouse_y >= 100 && mouse_y <= 140) {

                masked_blit(sprites, screenBuffer, 160, 240, 360, 333, 80, 80);
                textprintf_centre_ex(screenBuffer, font, 399, 455, makecol(255, 255, 255), -1, "NAME: Umbreon");
                textprintf_centre_ex(screenBuffer, font, 399, 470, makecol(255, 255, 255), -1, "TYPE: Normal");
                textprintf_centre_ex(screenBuffer, font, 399, 485, makecol(255, 255, 255), -1, "ABILITY: Adaptability");
                textprintf_centre_ex(screenBuffer, font, 399, 500, makecol(255, 255, 255), -1, "EVOLVES FROM: Eevee (Level 4)");
                textprintf_centre_ex(screenBuffer, font, 399, 515, makecol(255, 255, 255), -1, "EVOLVES INTO: Final Form");

                pokemonCry = load_sample("Musicas/Cries/UmbreonCry.wav");

                if(mouse_b) { play_sample(pokemonCry, 255, 0, 1000, 0); }
            }

            if(mouse_x >= 600 && mouse_x <= 640 && mouse_y >= 160 && mouse_y <= 200) {

                masked_blit(sprites, screenBuffer, 240, 240, 360, 333, 80, 80);
                textprintf_centre_ex(screenBuffer, font, 399, 455, makecol(255, 255, 255), -1, "NAME: Leafeon");
                textprintf_centre_ex(screenBuffer, font, 399, 470, makecol(255, 255, 255), -1, "TYPE: Normal");
                textprintf_centre_ex(screenBuffer, font, 399, 485, makecol(255, 255, 255), -1, "ABILITY: Adaptability");
                textprintf_centre_ex(screenBuffer, font, 399, 500, makecol(255, 255, 255), -1, "EVOLVES FROM: Eevee (Level 4)");
                textprintf_centre_ex(screenBuffer, font, 399, 515, makecol(255, 255, 255), -1, "EVOLVES INTO: Final Form");

                pokemonCry = load_sample("Musicas/Cries/LeafeonCry.wav");

                if(mouse_b) { play_sample(pokemonCry, 255, 0, 1000, 0); }
            }

            if(mouse_x >= 660 && mouse_x <= 700 && mouse_y >= 160 && mouse_y <= 200) {

                masked_blit(sprites, screenBuffer, 320, 240, 360, 333, 80, 80);
                textprintf_centre_ex(screenBuffer, font, 399, 455, makecol(255, 255, 255), -1, "NAME: Glaceon");
                textprintf_centre_ex(screenBuffer, font, 399, 470, makecol(255, 255, 255), -1, "TYPE: Normal");
                textprintf_centre_ex(screenBuffer, font, 399, 485, makecol(255, 255, 255), -1, "ABILITY: Adaptability");
                textprintf_centre_ex(screenBuffer, font, 399, 500, makecol(255, 255, 255), -1, "EVOLVES FROM: Eevee (Level 4)");
                textprintf_centre_ex(screenBuffer, font, 399, 515, makecol(255, 255, 255), -1, "EVOLVES INTO: Final Form");

                pokemonCry = load_sample("Musicas/Cries/GlaceonCry.wav");

                if(mouse_b) { play_sample(pokemonCry, 255, 0, 1000, 0); }
            }

            if(mouse_x >= 720 && mouse_x <= 760 && mouse_y >= 160 && mouse_y <= 200) {

                masked_blit(sprites, screenBuffer, 400, 240, 360, 333, 80, 80);
                textprintf_centre_ex(screenBuffer, font, 399, 455, makecol(255, 255, 255), -1, "NAME: Magby");
                textprintf_centre_ex(screenBuffer, font, 399, 470, makecol(255, 255, 255), -1, "TYPE: Splash Resistant");
                textprintf_centre_ex(screenBuffer, font, 399, 485, makecol(255, 255, 255), -1, "ABILITY: Flame Body");
                textprintf_centre_ex(screenBuffer, font, 399, 500, makecol(255, 255, 255), -1, "EVOLVES FROM: Starting Form");
                textprintf_centre_ex(screenBuffer, font, 399, 515, makecol(255, 255, 255), -1, "EVOLVES INTO: Magmar (Level 3)");

                pokemonCry = load_sample("Musicas/Cries/MagbyCry.wav");

                if(mouse_b) { play_sample(pokemonCry, 255, 0, 1000, 0); }
            }

            if(mouse_x >= 600 && mouse_x <= 640 && mouse_y >= 220 && mouse_y <= 260) {

                masked_blit(sprites, screenBuffer, 0, 320, 360, 333, 80, 80);
                textprintf_centre_ex(screenBuffer, font, 399, 455, makecol(255, 255, 255), -1, "NAME: Magmar");
                textprintf_centre_ex(screenBuffer, font, 399, 470, makecol(255, 255, 255), -1, "TYPE: Splash Resistant");
                textprintf_centre_ex(screenBuffer, font, 399, 485, makecol(255, 255, 255), -1, "ABILITY: Flame Body");
                textprintf_centre_ex(screenBuffer, font, 399, 500, makecol(255, 255, 255), -1, "EVOLVES FROM: Magby (Level 3)");
                textprintf_centre_ex(screenBuffer, font, 399, 515, makecol(255, 255, 255), -1, "EVOLVES INTO: Magmortar (Level 5)");

                pokemonCry = load_sample("Musicas/Cries/MagmarCry.wav");

                if(mouse_b) { play_sample(pokemonCry, 255, 0, 1000, 0); }
            }

            if(mouse_x >= 660 && mouse_x <= 700 && mouse_y >= 220 && mouse_y <= 260) {

                masked_blit(sprites, screenBuffer, 80, 320, 360, 333, 80, 80);
                textprintf_centre_ex(screenBuffer, font, 399, 455, makecol(255, 255, 255), -1, "NAME: Magmortar");
                textprintf_centre_ex(screenBuffer, font, 399, 470, makecol(255, 255, 255), -1, "TYPE: Splash Resistant");
                textprintf_centre_ex(screenBuffer, font, 399, 485, makecol(255, 255, 255), -1, "ABILITY: Flame Body");
                textprintf_centre_ex(screenBuffer, font, 399, 500, makecol(255, 255, 255), -1, "EVOLVES FROM: Magmar (Level 5)");
                textprintf_centre_ex(screenBuffer, font, 399, 515, makecol(255, 255, 255), -1, "EVOLVES INTO: Final Form");

                pokemonCry = load_sample("Musicas/Cries/MagmortarCry.wav");

                if(mouse_b) { play_sample(pokemonCry, 255, 0, 1000, 0); }
            }

            if(mouse_x >= 720 && mouse_x <= 760 && mouse_y >= 220 && mouse_y <= 260) {

                masked_blit(sprites, screenBuffer, 160, 320, 360, 333, 80, 80);
                textprintf_centre_ex(screenBuffer, font, 399, 455, makecol(255, 255, 255), -1, "NAME: Elekid");
                textprintf_centre_ex(screenBuffer, font, 399, 470, makecol(255, 255, 255), -1, "TYPE: Strong");
                textprintf_centre_ex(screenBuffer, font, 399, 485, makecol(255, 255, 255), -1, "ABILITY: Vital Spirit");
                textprintf_centre_ex(screenBuffer, font, 399, 500, makecol(255, 255, 255), -1, "EVOLVES FROM: Starting Form");
                textprintf_centre_ex(screenBuffer, font, 399, 515, makecol(255, 255, 255), -1, "EVOLVES INTO: Electabuzz (Level 3)");

                pokemonCry = load_sample("Musicas/Cries/ElekidCry.wav");

                if(mouse_b) { play_sample(pokemonCry, 255, 0, 1000, 0); }
            }

            if(mouse_x >= 600 && mouse_x <= 640 && mouse_y >= 280 && mouse_y <= 320) {

                masked_blit(sprites, screenBuffer, 240, 320, 360, 333, 80, 80);
                textprintf_centre_ex(screenBuffer, font, 399, 455, makecol(255, 255, 255), -1, "NAME: Electabuzz");
                textprintf_centre_ex(screenBuffer, font, 399, 470, makecol(255, 255, 255), -1, "TYPE: Strong");
                textprintf_centre_ex(screenBuffer, font, 399, 485, makecol(255, 255, 255), -1, "ABILITY: Vital Spirit");
                textprintf_centre_ex(screenBuffer, font, 399, 500, makecol(255, 255, 255), -1, "EVOLVES FROM: Elekid (Level 3)");
                textprintf_centre_ex(screenBuffer, font, 399, 515, makecol(255, 255, 255), -1, "EVOLVES INTO: Electivire (Level 5)");

                pokemonCry = load_sample("Musicas/Cries/ElectabuzzCry.wav");

                if(mouse_b) { play_sample(pokemonCry, 255, 0, 1000, 0); }
            }

            if(mouse_x >= 660 && mouse_x <= 700 && mouse_y >= 280 && mouse_y <= 320) {

                masked_blit(sprites, screenBuffer, 320, 320, 360, 333, 80, 80);
                textprintf_centre_ex(screenBuffer, font, 399, 455, makecol(255, 255, 255), -1, "NAME: Electivire");
                textprintf_centre_ex(screenBuffer, font, 399, 470, makecol(255, 255, 255), -1, "TYPE: Strong");
                textprintf_centre_ex(screenBuffer, font, 399, 485, makecol(255, 255, 255), -1, "ABILITY: Vital Spirit");
                textprintf_centre_ex(screenBuffer, font, 399, 500, makecol(255, 255, 255), -1, "EVOLVES FROM: Electabuzz (Level 5)");
                textprintf_centre_ex(screenBuffer, font, 399, 515, makecol(255, 255, 255), -1, "EVOLVES INTO: Final Form");

                pokemonCry = load_sample("Musicas/Cries/ElectivireCry.wav");

                if(mouse_b) { play_sample(pokemonCry, 255, 0, 1000, 0); }
            }

            if(mouse_x >= 720 && mouse_x <= 760 && mouse_y >= 280 && mouse_y <= 320) {

                masked_blit(sprites, screenBuffer, 400, 320, 360, 333, 80, 80);
                textprintf_centre_ex(screenBuffer, font, 399, 455, makecol(255, 255, 255), -1, "NAME: Growlithe");
                textprintf_centre_ex(screenBuffer, font, 399, 470, makecol(255, 255, 255), -1, "TYPE: Fast");
                textprintf_centre_ex(screenBuffer, font, 399, 485, makecol(255, 255, 255), -1, "ABILITY: Flash Fire");
                textprintf_centre_ex(screenBuffer, font, 399, 500, makecol(255, 255, 255), -1, "EVOLVES FROM: Starting Form");
                textprintf_centre_ex(screenBuffer, font, 399, 515, makecol(255, 255, 255), -1, "EVOLVES INTO: Arcanine (Level 4)");

                pokemonCry = load_sample("Musicas/Cries/GrowlitheCry.wav");

                if(mouse_b) { play_sample(pokemonCry, 255, 0, 1000, 0); }
            }

            if(mouse_x >= 600 && mouse_x <= 640 && mouse_y >= 340 && mouse_y <= 380) {

                masked_blit(sprites, screenBuffer, 0, 400, 360, 333, 80, 80);
                textprintf_centre_ex(screenBuffer, font, 399, 455, makecol(255, 255, 255), -1, "NAME: Arcanine");
                textprintf_centre_ex(screenBuffer, font, 399, 470, makecol(255, 255, 255), -1, "TYPE: Fast");
                textprintf_centre_ex(screenBuffer, font, 399, 485, makecol(255, 255, 255), -1, "ABILITY: Flash Fire");
                textprintf_centre_ex(screenBuffer, font, 399, 500, makecol(255, 255, 255), -1, "EVOLVES FROM: Growlithe (Level 4)");
                textprintf_centre_ex(screenBuffer, font, 399, 515, makecol(255, 255, 255), -1, "EVOLVES INTO: Final Form");

                pokemonCry = load_sample("Musicas/Cries/ArcanineCry.wav");

                if(mouse_b) { play_sample(pokemonCry, 255, 0, 1000, 0); }
            }

            if(mouse_x >= 660 && mouse_x <= 700 && mouse_y >= 340 && mouse_y <= 380) {

                masked_blit(sprites, screenBuffer, 80, 400, 360, 333, 80, 80);
                textprintf_centre_ex(screenBuffer, font, 399, 455, makecol(255, 255, 255), -1, "NAME: Nidoran (F)");
                textprintf_centre_ex(screenBuffer, font, 399, 470, makecol(255, 255, 255), -1, "TYPE: Safer");
                textprintf_centre_ex(screenBuffer, font, 399, 485, makecol(255, 255, 255), -1, "ABILITY: Poison Point");
                textprintf_centre_ex(screenBuffer, font, 399, 500, makecol(255, 255, 255), -1, "EVOLVES FROM: Starting Form");
                textprintf_centre_ex(screenBuffer, font, 399, 515, makecol(255, 255, 255), -1, "EVOLVES INTO: Nidorina (Level 3)");

                pokemonCry = load_sample("Musicas/Cries/NidoranFemaleCry.wav");

                if(mouse_b) { play_sample(pokemonCry, 255, 0, 1000, 0); }
            }

            if(mouse_x >= 720 && mouse_x <= 760 && mouse_y >= 340 && mouse_y <= 380) {

                masked_blit(sprites, screenBuffer, 160, 400, 360, 333, 80, 80);
                textprintf_centre_ex(screenBuffer, font, 399, 455, makecol(255, 255, 255), -1, "NAME: Nidorina");
                textprintf_centre_ex(screenBuffer, font, 399, 470, makecol(255, 255, 255), -1, "TYPE: Safer");
                textprintf_centre_ex(screenBuffer, font, 399, 485, makecol(255, 255, 255), -1, "ABILITY: Poison Point");
                textprintf_centre_ex(screenBuffer, font, 399, 500, makecol(255, 255, 255), -1, "EVOLVES FROM: Nidoran (F) (Level 3)");
                textprintf_centre_ex(screenBuffer, font, 399, 515, makecol(255, 255, 255), -1, "EVOLVES INTO: Nidoqueen (Level 5)");

                pokemonCry = load_sample("Musicas/Cries/NidorinaCry.wav");

                if(mouse_b) { play_sample(pokemonCry, 255, 0, 1000, 0); }
            }

            if(mouse_x >= 600 && mouse_x <= 640 && mouse_y >= 400 && mouse_y <= 440) {

                masked_blit(sprites, screenBuffer, 240, 400, 360, 333, 80, 80);
                textprintf_centre_ex(screenBuffer, font, 399, 455, makecol(255, 255, 255), -1, "NAME: Nidoqueen");
                textprintf_centre_ex(screenBuffer, font, 399, 470, makecol(255, 255, 255), -1, "TYPE: Safer");
                textprintf_centre_ex(screenBuffer, font, 399, 485, makecol(255, 255, 255), -1, "ABILITY: Poison Point");
                textprintf_centre_ex(screenBuffer, font, 399, 500, makecol(255, 255, 255), -1, "EVOLVES FROM: Nidorina (Level 5)");
                textprintf_centre_ex(screenBuffer, font, 399, 515, makecol(255, 255, 255), -1, "EVOLVES INTO: Final Form");

                pokemonCry = load_sample("Musicas/Cries/NidoqueenCry.wav");

                if(mouse_b) { play_sample(pokemonCry, 255, 0, 1000, 0); }
            }

            if(mouse_x >= 660 && mouse_x <= 700 && mouse_y >= 400 && mouse_y <= 440) {

                masked_blit(sprites, screenBuffer, 320, 400, 360, 333, 80, 80);
                textprintf_centre_ex(screenBuffer, font, 399, 455, makecol(255, 255, 255), -1, "NAME: Nidoran (M)");
                textprintf_centre_ex(screenBuffer, font, 399, 470, makecol(255, 255, 255), -1, "TYPE: Safer");
                textprintf_centre_ex(screenBuffer, font, 399, 485, makecol(255, 255, 255), -1, "ABILITY: Poison Point");
                textprintf_centre_ex(screenBuffer, font, 399, 500, makecol(255, 255, 255), -1, "EVOLVES FROM: Nidorino (Level 5)");
                textprintf_centre_ex(screenBuffer, font, 399, 515, makecol(255, 255, 255), -1, "EVOLVES INTO: Final Form");

                pokemonCry = load_sample("Musicas/Cries/NidoranMaleCry.wav");

                if(mouse_b) { play_sample(pokemonCry, 255, 0, 1000, 0); }
            }

            if(mouse_x >= 720 && mouse_x <= 760 && mouse_y >= 400 && mouse_y <= 440) {

                masked_blit(sprites, screenBuffer, 400, 400, 360, 333, 80, 80);
                textprintf_centre_ex(screenBuffer, font, 399, 455, makecol(255, 255, 255), -1, "NAME: Nidorino");
                textprintf_centre_ex(screenBuffer, font, 399, 470, makecol(255, 255, 255), -1, "TYPE: Safer");
                textprintf_centre_ex(screenBuffer, font, 399, 485, makecol(255, 255, 255), -1, "ABILITY: Poison Point");
                textprintf_centre_ex(screenBuffer, font, 399, 500, makecol(255, 255, 255), -1, "EVOLVES FROM: Nidoran (M) (Level 3)");
                textprintf_centre_ex(screenBuffer, font, 399, 515, makecol(255, 255, 255), -1, "EVOLVES INTO: Nidoking (Level 5)");

                pokemonCry = load_sample("Musicas/Cries/NidorinoCry.wav");

                if(mouse_b) { play_sample(pokemonCry, 255, 0, 1000, 0); }
            }

            if(mouse_x >= 600 && mouse_x <= 640 && mouse_y >= 460 && mouse_y <= 500) {

                masked_blit(sprites, screenBuffer, 0, 480, 360, 333, 80, 80);
                textprintf_centre_ex(screenBuffer, font, 399, 455, makecol(255, 255, 255), -1, "NAME: Nidoking");
                textprintf_centre_ex(screenBuffer, font, 399, 470, makecol(255, 255, 255), -1, "TYPE: Safer");
                textprintf_centre_ex(screenBuffer, font, 399, 485, makecol(255, 255, 255), -1, "ABILITY: Poison Point");
                textprintf_centre_ex(screenBuffer, font, 399, 500, makecol(255, 255, 255), -1, "EVOLVES FROM: Nidorino (Level 5)");
                textprintf_centre_ex(screenBuffer, font, 399, 515, makecol(255, 255, 255), -1, "EVOLVES INTO: Final Form");

                pokemonCry = load_sample("Musicas/Cries/NidokingCry.wav");

                if(mouse_b) { play_sample(pokemonCry, 255, 0, 1000, 0); }
            }

            //Treinadores

            if(mouse_x >= 375 && mouse_x <= 391 && mouse_y >= 181 && mouse_y <= 203) {

                masked_blit(sprites, screenBuffer, 160, 480, 360, 333, 80, 80);
                textprintf_centre_ex(screenBuffer, font, 399, 455, makecol(255, 255, 255), -1, "POKEMON TRAINER Red");
                textprintf_centre_ex(screenBuffer, font, 399, 470, makecol(255, 255, 255), -1, "\"...\"");
            }

            if(mouse_x >= 402 && mouse_x <= 419 && mouse_y >= 177 && mouse_y <= 203) {

                masked_blit(sprites, screenBuffer, 80, 480, 360, 333, 80, 80);
                textprintf_centre_ex(screenBuffer, font, 399, 455, makecol(255, 255, 255), -1, "POKEMON TRAINER Blue");
                textprintf_centre_ex(screenBuffer, font, 399, 470, makecol(255, 255, 255), -1, "\"Smell ya later!\"");
            }

            draw_sprite(screenBuffer, backImage, 20, 540);

            draw_sprite(screenBuffer, mouseImage[mouseImage_Frame], mouse_x-6, mouse_y);

            draw_sprite(screen, screenBuffer, 0, 0);

            clear(screenBuffer);

        }

    }

    destroy_bitmap(mouseImage[0]);
    destroy_bitmap(mouseImage[1]);
    destroy_midi(screenMusic);
    destroy_sample(pokemonCry);
    destroy_bitmap(screenBuffer);
    destroy_bitmap(profOakLab);
    destroy_bitmap(icons);
    destroy_bitmap(sprites);
    destroy_bitmap(backImage);

    return lastScreen;
}

int resultScreen(int vencedor) {

    int nextScreen = telaMenuLevels;
    int timer = 0;
    BITMAP *telaResultado;
    BITMAP *screenBuffer = create_bitmap(SCREEN_W, SCREEN_H);
    MIDI *musicaResultado;

    if(vencedor == 1) {

        telaResultado = load_bitmap("Imagens/FimDeJogo/TelaVitoria.bmp", NULL);
        musicaResultado = load_midi("Musicas/MusicaTelaVitoria.mid");

    } else {

        telaResultado = load_bitmap("Imagens/FimDeJogo/TelaDerrota.bmp", NULL);
        musicaResultado = load_midi("Musicas/MusicaTelaDerrota.mid");
    }

    play_midi(musicaResultado, true);

    while(!key[KEY_ENTER]) {

        draw_sprite(screenBuffer, telaResultado, 0, 0);

        if(timer / 240 == 0) {

            textout_centre_ex(screenBuffer, font, "PRESS ENTER TO CONTINUE", 680, 560, makecol(255, 255, 255), -1);

        } else if(timer == 360) {

            timer = 0;
        }

        draw_sprite(screen, screenBuffer, 0, 0);
        clear(screenBuffer);
        timer++;
    }

    destroy_bitmap(screenBuffer);
    destroy_bitmap(telaResultado);
    destroy_midi(musicaResultado);

    return nextScreen;
}

void menuLoading (int duracaoMSEC) {

    ticks = 0;

    int sairTela = false;

    int maxTicksAnimacao = 60;

    int divisorTempo = maxTicksAnimacao / 5;

    int reversa = false;

    int aux,auxPosX;

    int old_ticks = 0;

    int tempoPassadoMSEC = 0;

    MIDI *loadingMusic = load_midi("Musicas/MusicaTelaLoading.mid");

    BITMAP *screenBuffer = create_bitmap(SCREEN_W, SCREEN_H);

    BITMAP *loadingObject = load_bitmap("Imagens/Loading/black_pokeball_21x22.bmp", NULL);

    play_midi(loadingMusic, true);

	while (!sairTela) {

        while (!sairTela && ticks > 0) {

            if (old_ticks == 0) { old_ticks = ticks; }

            if (ticks != old_ticks) {

                old_ticks = ticks;

                if (ticks == maxTicksAnimacao) {
                    ticks = 0;
                    old_ticks = 0;
                    reversa = (reversa == true ? false : true);
                }

                tempoPassadoMSEC++;

                if (tempoPassadoMSEC == duracaoMSEC) { sairTela = true;}

            }

            clear_to_color(screenBuffer, makecol(255, 255, 255));

            for (aux = 0; (ticks/divisorTempo)+1 != aux; aux++) {
                if (reversa == true) {
                    auxPosX = (SCREEN_W/2 + 62) - (aux * 31);
                }else{
                    auxPosX = (SCREEN_W/2 - 62) + (aux * 31);
                }
                draw_sprite(screenBuffer, loadingObject, auxPosX, SCREEN_H/2 - 11);
            }

            draw_sprite(screen, screenBuffer, 0, 0);

            clear(screenBuffer);

        }

    }

    destroy_bitmap(loadingObject);

    destroy_bitmap(screenBuffer);

    destroy_midi(loadingMusic);

}

void showInputScreen(BITMAP *window, User *userLogs){

	int exitScreen = false;

	int mouseLocker = (mouse_b == 1 ? true : false);

	BITMAP *screenBuffer = create_bitmap(SCREEN_W, SCREEN_H);

    BITMAP *menuImage_Mouse[2];
    menuImage_Mouse[0] = load_bitmap("Imagens/Cursor/cursor.bmp", NULL);
    menuImage_Mouse[1] = load_bitmap("Imagens/Cursor/cursor_clicked.bmp", NULL);
    int menuImage_Mouse_Frame = 0;

    //

    BITMAP *cancelUserImage[4];
    cancelUserImage[0] = load_bitmap("Imagens/UsersMenu/cancelButton_140x42.bmp", NULL);
    cancelUserImage[1] = load_bitmap("Imagens/UsersMenu/cancelButtonOver_140x42.bmp", NULL);
    cancelUserImage[2] = load_bitmap("Imagens/UsersMenu/cancelButtonClicked_140x42.bmp", NULL);
    cancelUserImage[3] = load_bitmap("Imagens/UsersMenu/cancelButton_140x42.bmp", NULL);
    UIButton *cancelUserButton = uibutton_create(cancelUserImage, NULL, (SCREEN_W/2)+1, (SCREEN_H/2)+49, 140, 34);

    BITMAP *loadUserImage[4];
    loadUserImage[0] = load_bitmap("Imagens/UsersMenu/confirmButton_140x42.bmp", NULL);
    loadUserImage[1] = load_bitmap("Imagens/UsersMenu/confirmButtonOver_140x42.bmp", NULL);
    loadUserImage[2] = load_bitmap("Imagens/UsersMenu/confirmButtonClicked_140x42.bmp", NULL);
    loadUserImage[3] = load_bitmap("Imagens/UsersMenu/confirmButton_140x42.bmp", NULL);
    UIButton *loadUserButton = uibutton_create(loadUserImage, NULL, (SCREEN_W/2)-140, (SCREEN_H/2)+49, 140, 34);

    BITMAP *fieldImage[2];
	fieldImage[0] = create_bitmap(160, 40); clear_to_color(fieldImage[0], makeacol(255, 230, 255, 255));
	fieldImage[1] = create_bitmap(160, 40); clear_to_color(fieldImage[1], makeacol(200, 200, 200, 255));
    UITextField *userTextField = uitextfield_create(fieldImage, 160, 40, (SCREEN_W/2)-80, (SCREEN_H/2)-30, NULL, "Username");
    userTextField->textColor = makeacol(0, 0, 0, 255);
    userTextField->placeholderColor = makeacol(80, 80, 80, 255);

	//

	while (!exitScreen) {

		if (key[KEY_ESC]){ exitScreen = true; }

	    while (!exitScreen && ticks > 0) {

	    	if (mouse_b != 1) { mouseLocker = false; }

	    	uibutton_update(cancelUserButton);
	    	uibutton_update(loadUserButton);
	    	uitextfield_update(userTextField);

	    	if (cancelUserButton->isClicked == true && mouseLocker == false){

	    		mouseLocker = true;

	    		exitScreen = true;

	    	}

	    	if (loadUserButton->isClicked == true && mouseLocker == false){

				mouseLocker = true;

				if (userTextField->hasText == true){

					alterMainuser(userTextField->text, userLogs);

					exitScreen = true;

				}

			}

			if (userTextField->editing == true) {

            	if (keypressed()) {

            		int  newkey   = readkey();
					char ASCII    = newkey & 0xff;

					uitextfield_add(userTextField, ASCII);

            	}

            	clear_keybuf();

            }


	        draw_sprite(screenBuffer, window, 0, 0);

	        rectfill(screenBuffer, 0, 0, SCREEN_W, SCREEN_H, makeacol(0, 0, 0, 125));

			rectfill(screenBuffer, (SCREEN_W/2)-140, (SCREEN_H/2)-90, (SCREEN_W/2)+140, (SCREEN_H/2)+90, makeacol(255, 255, 255, 255));

			textout_centre_ex(screenBuffer, font, "INSERT YOUR NAME", (SCREEN_W/2), (SCREEN_H/2)-60, makeacol(0,0,0,255), -1);

			uitextfield_draw(userTextField, screenBuffer);

			uibutton_draw(cancelUserButton, cancelUserButton->posX, cancelUserButton->posY, screenBuffer);

			uibutton_draw(loadUserButton, loadUserButton->posX, loadUserButton->posY, screenBuffer);

			draw_sprite(screenBuffer, menuImage_Mouse[menuImage_Mouse_Frame], mouse_x-6, mouse_y);

	        draw_sprite(screen, screenBuffer, 0, 0);

	        clear(screenBuffer);

	        ticks--;

	    }

	}

	destroy_bitmap(menuImage_Mouse[0]);
	destroy_bitmap(menuImage_Mouse[1]);
	destroy_bitmap(screenBuffer);

	//

}

int menuPrincipal (User *userLogs) {

    ticks = 0;

    int exitScreen = false;

    int nextScreen = telaMenuPrincipal;

    int mouseLocker = false;

    MIDI *mainMenuMusic = load_midi("Musicas/MusicaTelaInicial.mid");

    BITMAP *mouseImage[2];
    mouseImage[0] = load_bitmap("Imagens/Cursor/cursor.bmp", NULL);
    mouseImage[1] = load_bitmap("Imagens/Cursor/cursor_clicked.bmp", NULL);
    int mouseImage_Frame = 0;

    BITMAP *screenBuffer = create_bitmap(SCREEN_W, SCREEN_H);

    BITMAP *backgroundImage = load_bitmap("Imagens/MenuPrincipal/background_800x600.bmp", NULL);

    // Botao do almanaque

    BITMAP *almanaqueImages[4];
    almanaqueImages[0] = load_bitmap("Imagens/Botoes/almanacImage.bmp", NULL);
    almanaqueImages[1] = load_bitmap("Imagens/Botoes/almanacImage.bmp", NULL);
    almanaqueImages[2] = load_bitmap("Imagens/Botoes/almanacImage.bmp", NULL);
    almanaqueImages[3] = load_bitmap("Imagens/Botoes/almanacImage.bmp", NULL);
    UIButton *almanaqueButton = uibutton_create(almanaqueImages, NULL, 680, 530, 100, 50);

    // Botao de selecao de levels

    BITMAP *levelButtonImage[4];
    levelButtonImage[0] = load_bitmap("Imagens/MenuPrincipal/playButton_138x39.bmp", NULL);
    levelButtonImage[1] = load_bitmap("Imagens/MenuPrincipal/playButtonOver_138x39.bmp", NULL);
    levelButtonImage[2] = load_bitmap("Imagens/MenuPrincipal/playButtonClicked_138x39.bmp", NULL);
    levelButtonImage[3] = load_bitmap("Imagens/MenuPrincipal/playButton_138x39.bmp", NULL);
    UIButton *levelsButton = uibutton_create(levelButtonImage, NULL, (SCREEN_W/2)-69, 441, 138, 39);

    // Botao de saida

    BITMAP *exitButtonImage[4];
    exitButtonImage[0] = load_bitmap("Imagens/MenuPrincipal/exitButton_120x39.bmp", NULL);
    exitButtonImage[1] = load_bitmap("Imagens/MenuPrincipal/exitButtonOver_120x39.bmp", NULL);
    exitButtonImage[2] = load_bitmap("Imagens/MenuPrincipal/exitButtonClicked_120x39.bmp", NULL);
    exitButtonImage[3] = load_bitmap("Imagens/MenuPrincipal/exitButton_120x39.bmp", NULL);
    UIButton *exitButton = uibutton_create(exitButtonImage, NULL, (SCREEN_W/2)-60, 511, 120, 39);

    // Criamos o campo de texto

    BITMAP *loadUserImage[4];
    loadUserImage[0] = load_bitmap("Imagens/MenuPrincipal/UserChangeButton_50x50.bmp", NULL);
    loadUserImage[1] = load_bitmap("Imagens/MenuPrincipal/UserChangeButtonOver_50x50.bmp", NULL);
    loadUserImage[2] = load_bitmap("Imagens/MenuPrincipal/UserChangeButtonClicked_50x50.bmp", NULL);
    loadUserImage[3] = load_bitmap("Imagens/MenuPrincipal/UserChangeButton_50x50.bmp", NULL);
    UIButton *loadUserButton = uibutton_create(loadUserImage, NULL, 200, 530, 50, 50);

    // Musicas

    play_midi(mainMenuMusic, true);

    // Menu loop

	while (!exitScreen) {

		if (key[KEY_ESC]){ exitScreen = true; nextScreen = telaEndScreen; }

        while (!exitScreen && ticks > 0) {

            if (mouse_b != 1){ mouseLocker = false; }

            draw_sprite(screenBuffer, backgroundImage, 0, 0);

            uibutton_update(levelsButton);
            uibutton_update(exitButton);
            uibutton_update(almanaqueButton);
            uibutton_update(loadUserButton);

            if (levelsButton->isClicked == true && mouseLocker == false) {

            	mouseLocker = true;

            	nextScreen = telaMenuLevels;

            	exitScreen = true;

            }

			if (exitButton->isClicked == true && mouseLocker == false){

				mouseLocker = true;

				nextScreen = telaEndScreen;

				exitScreen = true;

			}

			if (almanaqueButton->isClicked == true && mouseLocker == false){

				mouseLocker = true;

				nextScreen = telaAlmanaqueMenu;

				exitScreen = true;

			}

			uibutton_draw(levelsButton, levelsButton->posX, levelsButton->posY, screenBuffer);
			uibutton_draw(exitButton, exitButton->posX, exitButton->posY, screenBuffer);
			uibutton_draw(almanaqueButton, almanaqueButton->posX, almanaqueButton->posY, screenBuffer);
			uibutton_draw(loadUserButton, loadUserButton->posX, loadUserButton->posY, screenBuffer);

			textprintf_centre_ex(screenBuffer, font, loadUserButton->posX+25, loadUserButton->posY+44, makeacol(255,255,255,255), -1, "LOAD USER");

			//-----

			rectfill(screenBuffer, 20, 530, 180, 580, makeacol(255, 255, 255, 255));

			textprintf_centre_ex(screenBuffer, font, 100, 555, makeacol(0,0,0,255), -1, "%s", userLogs->username);

			if (loadUserButton->isClicked == true && mouseLocker == false){

				mouseLocker = true;

				showInputScreen(screenBuffer, userLogs);

			}

			//-----

            draw_sprite(screenBuffer, mouseImage[mouseImage_Frame], mouse_x-6, mouse_y);

            draw_sprite(screen, screenBuffer, 0, 0);

            clear(screenBuffer);

            ticks--;

        }

    }

    destroy_midi(mainMenuMusic);

    destroy_bitmap(screenBuffer);

    destroy_bitmap(mouseImage[0]);
    destroy_bitmap(mouseImage[1]);

    uibutton_release(almanaqueButton);
    uibutton_release(levelsButton);
    uibutton_release(exitButton);

    return nextScreen;

}

int menuLevels (int *loadLevel, User *userLogs) {

    ticks = 0;

    int exitScreen = false;

    int nextScreen = telaMenuLevels;

    MIDI *levelSelectMusic = load_midi("Musicas/MusicaStageSelect.mid");

    //-----

    BITMAP *screenBuffer = create_bitmap(SCREEN_W, SCREEN_H);

    BITMAP *mouseImage[2];
    mouseImage[0] = load_bitmap("Imagens/Cursor/cursor.bmp", NULL);
    mouseImage[1] = load_bitmap("Imagens/Cursor/cursor_clicked.bmp", NULL);
    int mouseImage_Frame = 0;

    BITMAP *menuBackground = load_bitmap("Imagens/MenuLevels/background_800x600.bmp", NULL);

    BITMAP *backButtonImage[4];
    backButtonImage[0] = load_bitmap("Imagens/MenuLevels/backButton_93x81.bmp", NULL);
    backButtonImage[1] = load_bitmap("Imagens/MenuLevels/backButton_93x81.bmp", NULL);
    backButtonImage[2] = load_bitmap("Imagens/MenuLevels/backButton_93x81.bmp", NULL);
    backButtonImage[3] = NULL;
    UIButton *backButton = uibutton_create(backButtonImage, NULL, 20, 540, 93, 81);

    BITMAP *levelMButtonImage[4];
    levelMButtonImage[0] = load_bitmap("Imagens/MenuLevels/m_level_93x81.bmp", NULL);
    levelMButtonImage[1] = load_bitmap("Imagens/MenuLevels/m_levelOver_93x81.bmp", NULL);
    levelMButtonImage[2] = load_bitmap("Imagens/MenuLevels/m_levelClicked_93x81.bmp", NULL);
    levelMButtonImage[3] = NULL;
    UIButton *levelMButton = uibutton_create(levelMButtonImage, NULL, 135, 195, 93, 81);

    BITMAP *level1ButtonImage[4];
    level1ButtonImage[0] = load_bitmap("Imagens/MenuLevels/1_level_93x81.bmp", NULL);
    level1ButtonImage[1] = load_bitmap("Imagens/MenuLevels/1_levelOver_93x81.bmp", NULL);
    level1ButtonImage[2] = load_bitmap("Imagens/MenuLevels/1_levelClicked_93x81.bmp", NULL);
    level1ButtonImage[3] = NULL;
    UIButton *level1Button = uibutton_create(level1ButtonImage, NULL, 280, 195, 93, 81);

    BITMAP *level2ButtonImage[4];
    level2ButtonImage[0] = load_bitmap("Imagens/MenuLevels/2_level_93x81.bmp", NULL);
    level2ButtonImage[1] = load_bitmap("Imagens/MenuLevels/2_levelOver_93x81.bmp", NULL);
    level2ButtonImage[2] = load_bitmap("Imagens/MenuLevels/2_levelClicked_93x81.bmp", NULL);
    level2ButtonImage[3] = NULL;
    UIButton *level2Button = uibutton_create(level2ButtonImage, NULL, 425, 193, 93, 81);

    BITMAP *level3ButtonImage[4];
    level3ButtonImage[0] = load_bitmap("Imagens/MenuLevels/3_level_93x81.bmp", NULL);
    level3ButtonImage[1] = load_bitmap("Imagens/MenuLevels/3_levelOver_93x81.bmp", NULL);
    level3ButtonImage[2] = load_bitmap("Imagens/MenuLevels/3_levelClicked_93x81.bmp", NULL);
    level3ButtonImage[3] = NULL;
    UIButton *level3Button = uibutton_create(level3ButtonImage, NULL, 570, 195, 93, 81);

    BITMAP *level4ButtonImage[4];
    level4ButtonImage[0] = load_bitmap("Imagens/MenuLevels/4_level_93x81.bmp", NULL);
    level4ButtonImage[1] = load_bitmap("Imagens/MenuLevels/4_levelOver_93x81.bmp", NULL);
    level4ButtonImage[2] = load_bitmap("Imagens/MenuLevels/4_levelClicked_93x81.bmp", NULL);
    level4ButtonImage[3] = NULL;
    UIButton *level4Button = uibutton_create(level4ButtonImage, NULL, 211, 325, 93, 81);

    BITMAP *level5ButtonImage[4];
    level5ButtonImage[0] = load_bitmap("Imagens/MenuLevels/5_level_93x81.bmp", NULL);
    level5ButtonImage[1] = load_bitmap("Imagens/MenuLevels/5_levelOver_93x81.bmp", NULL);
    level5ButtonImage[2] = load_bitmap("Imagens/MenuLevels/5_levelClicked_93x81.bmp", NULL);
    level5ButtonImage[3] = NULL;
    UIButton *level5Button = uibutton_create(level5ButtonImage, NULL, 354, 325, 93, 81);

    BITMAP *level6ButtonImage[4];
    level6ButtonImage[0] = load_bitmap("Imagens/MenuLevels/6_level_93x81.bmp", NULL);
    level6ButtonImage[1] = load_bitmap("Imagens/MenuLevels/6_levelOver_93x81.bmp", NULL);
    level6ButtonImage[2] = load_bitmap("Imagens/MenuLevels/6_levelClicked_93x81.bmp", NULL);
    level6ButtonImage[3] = NULL;
    UIButton *level6Button = uibutton_create(level6ButtonImage, NULL, 498, 325, 93, 81);

    //

    play_midi(levelSelectMusic, true);

	while (!exitScreen) {

		if (key[KEY_ESC]){ exitScreen = true; nextScreen = telaEndScreen; }

        while (!exitScreen && ticks > 0) {

            draw_sprite(screenBuffer, menuBackground, 0, 0);

            uibutton_update(backButton);
            uibutton_update(levelMButton);
            uibutton_update(level1Button);
            uibutton_update(level2Button);
            uibutton_update(level3Button);
            uibutton_update(level4Button);
            uibutton_update(level5Button);
            uibutton_update(level6Button);

            if (backButton->isClicked == true){

            	nextScreen = telaMenuPrincipal;

            	exitScreen = true;

            }

			if (levelMButton->isClicked == true){

				nextScreen = telaMenuJogar;

				*loadLevel = 0;

				exitScreen = true;

			}

			if (level1Button->isClicked == true){

				nextScreen = telaMenuJogar;

				*loadLevel = 1;

				exitScreen = true;

			}

			if (level2Button->isClicked == true){

				nextScreen = telaMenuJogar;

				*loadLevel = 2;

				exitScreen = true;

			}

			if (level3Button->isClicked == true){

				nextScreen = telaMenuJogar;

				*loadLevel = 3;

				exitScreen = true;

			}

			if (level4Button->isClicked == true){

				nextScreen = telaMenuJogar;

				*loadLevel = 4;

				exitScreen = true;

			}

			if (level5Button->isClicked == true){

				nextScreen = telaMenuJogar;

				*loadLevel = 5;

				exitScreen = true;

			}

			if (level6Button->isClicked == true){

				nextScreen = telaMenuJogar;

				*loadLevel = 6;

				exitScreen = true;

			}

            uibutton_draw(backButton, backButton->posX, backButton->posY, screenBuffer);

            uibutton_draw(levelMButton, levelMButton->posX, levelMButton->posY, screenBuffer);
            textprintf_centre_ex(screenBuffer, font, levelMButton->posX+46, levelMButton->posY+71, makeacol(100, 100, 100, 255), -1, "%i",userLogs->scoreLvM);

            uibutton_draw(level1Button, level1Button->posX, level1Button->posY, screenBuffer);
            textprintf_centre_ex(screenBuffer, font, level1Button->posX+46, level1Button->posY+71, makeacol(100, 100, 100, 255), -1, "%i",userLogs->scoreLv1);

            uibutton_draw(level2Button, level2Button->posX, level2Button->posY, screenBuffer);
            textprintf_centre_ex(screenBuffer, font, level2Button->posX+46, level2Button->posY+72, makeacol(100, 100, 100, 255), -1, "%i",userLogs->scoreLv2);

            uibutton_draw(level3Button, level3Button->posX, level3Button->posY, screenBuffer);
            textprintf_centre_ex(screenBuffer, font, level3Button->posX+46, level3Button->posY+71, makeacol(100, 100, 100, 255), -1, "%i",userLogs->scoreLv3);

            uibutton_draw(level4Button, level4Button->posX, level4Button->posY, screenBuffer);
            textprintf_centre_ex(screenBuffer, font, level4Button->posX+46, level4Button->posY+71, makeacol(100, 100, 100, 255), -1, "%i",userLogs->scoreLv4);

            uibutton_draw(level5Button, level5Button->posX, level5Button->posY, screenBuffer);
            textprintf_centre_ex(screenBuffer, font, level5Button->posX+46, level5Button->posY+71, makeacol(100, 100, 100, 255), -1, "%i",userLogs->scoreLv5);

            uibutton_draw(level6Button, level6Button->posX, level6Button->posY, screenBuffer);
            textprintf_centre_ex(screenBuffer, font, level6Button->posX+46, level6Button->posY+71, makeacol(100, 100, 100, 255), -1, "%i",userLogs->scoreLv6);

            draw_sprite(screenBuffer, mouseImage[mouseImage_Frame], mouse_x-6, mouse_y);

            draw_sprite(screen, screenBuffer, 0, 0);

            clear(screenBuffer);

            ticks--;

        }

    }

    destroy_midi(levelSelectMusic);

    destroy_bitmap(screenBuffer);

    destroy_bitmap(mouseImage[0]);
    destroy_bitmap(mouseImage[1]);

    destroy_bitmap(menuBackground);

    uibutton_release(backButton);
    uibutton_release(levelMButton);
    uibutton_release(level1Button);
    uibutton_release(level2Button);
    uibutton_release(level3Button);
    uibutton_release(level4Button);
    uibutton_release(level5Button);
    uibutton_release(level6Button);

    return nextScreen;

}

int menuJogar (int level, User *userLogs) {

    menuLoading(loadingLevelDuration);

    ticks = 0;

    int mouseLocker = false;

    int exitScreen = false;

    int nextScreen = telaMenuPrincipal;

    int auxBlinkCounter = 0, auxBlinkLock = false;

    int draggingTower = false, draggingTowerType = 0;

    int hudVisible = false;

    int gamePaused = false;

    // Auxiliares do timer inicial

    int timerVisible = true,qntTimer = 0;

    // Carregamos o level
    int **groundMatrix = allocIntegerMatrix(12, 16);
    if (groundMatrix == NULL) { exit(1); }
    int qntLifes,qntBudget,qntRounds,qntWonRounds = 0,qntEnemies,*qntEnemiesPerLine = NULL;
    Enemie **enemies;

    SAMPLE *levelComplete = load_sample("Musicas/SomRoundVencido.wav");
    SAMPLE *levelUp = load_sample("Musicas/SomLevelUp.wav");
    SAMPLE *normalSound = load_sample("Musicas/SomNormalAttack.wav");
    SAMPLE *splashSound = load_sample("Musicas/SomSplashAttack.wav");
    MIDI *gameMusic = load_midi("Musicas/MusicaBatalha.mid");

    BITMAP *screenBuffer = create_bitmap(SCREEN_W, SCREEN_H);

    BITMAP *pauseMenu = load_bitmap("Imagens/PauseMenu.bmp", NULL);

    // Auxiliares do mouse

    BITMAP *menuImage_Mouse[2];
    menuImage_Mouse[0] = load_bitmap("Imagens/Cursor/cursor.bmp", NULL);
    menuImage_Mouse[1] = load_bitmap("Imagens/Cursor/cursor_clicked.bmp", NULL);
    int menuImage_Mouse_Frame = 0;

    // Auxiliares de pause

    BITMAP *pausedScreenBuffer = create_bitmap(SCREEN_W, SCREEN_H);
    BITMAP *pauseImage[4];
    pauseImage[0] = load_bitmap("Imagens/Botoes/pauseButton_40x40.bmp", NULL);
    pauseImage[1] = load_bitmap("Imagens/Botoes/pauseButton_40x40.bmp", NULL);
    pauseImage[2] = load_bitmap("Imagens/Botoes/pauseButton_40x40.bmp", NULL);
    pauseImage[3] = load_bitmap("Imagens/Botoes/pauseButton_40x40.bmp", NULL);
    UIButton *pauseButton = uibutton_create(pauseImage, NULL, 740, 10, 40, 40);

    BITMAP *roundPlayImages[4];
    roundPlayImages[0] = load_bitmap("Imagens/Botoes/resumeButton_40x40.bmp", NULL);
    roundPlayImages[1] = load_bitmap("Imagens/Botoes/resumeButton_40x40.bmp", NULL);
    roundPlayImages[2] = load_bitmap("Imagens/Botoes/resumeButton_40x40.bmp", NULL);
    roundPlayImages[3] = load_bitmap("Imagens/Botoes/resumeButton_40x40.bmp", NULL);
    UIButton *roundPlayButton = uibutton_create(roundPlayImages, NULL, 740, 10, 40, 40);
    uibutton_sethidden(roundPlayButton, true);

    BITMAP *enemyImage1[7];
    enemyImage1[0] = load_bitmap("Imagens/Inimigos/inimigo1_1_400x400.bmp", NULL);
    enemyImage1[1] = load_bitmap("Imagens/Inimigos/inimigo1_2_400x400.bmp", NULL);
    enemyImage1[2] = load_bitmap("Imagens/Inimigos/inimigo1_3_400x400.bmp", NULL);
    enemyImage1[3] = load_bitmap("Imagens/Inimigos/inimigo1_4_400x400.bmp", NULL);
    enemyImage1[4] = load_bitmap("Imagens/Inimigos/inimigo1_5_400x400.bmp", NULL);
    enemyImage1[5] = load_bitmap("Imagens/Inimigos/inimigo1_6_400x400.bmp", NULL);
    enemyImage1[6] = load_bitmap("Imagens/Inimigos/inimigo1_7_400x400.bmp", NULL);
    BITMAP *enemyImage2[1];
    enemyImage2[0] = load_bitmap("Imagens/Inimigos/inimigo2_1_400x400.bmp", NULL);
    BITMAP *enemyImage3[1];
    enemyImage3[0] = load_bitmap("Imagens/Inimigos/inimigo3_1_400x400.bmp", NULL);
    BITMAP *enemyImage4[1];
    enemyImage4[0] = load_bitmap("Imagens/Inimigos/inimigo4_1_400x400.bmp", NULL);
    BITMAP *enemyImage5[2];
    enemyImage5[0] = load_bitmap("Imagens/Inimigos/inimigo5_1_400x400.bmp", NULL);
    enemyImage5[1] = load_bitmap("Imagens/Inimigos/inimigo5_2_400x400.bmp", NULL);

    Axis *groundAxis;
    int qntAxis = 0;

    loadLevel(level, &groundMatrix, &enemies, &qntEnemies, &qntEnemiesPerLine, enemyImage1, enemyImage2, enemyImage3, enemyImage4, enemyImage5, &qntLifes, &qntBudget, &qntRounds, &groundAxis, &qntAxis);

    // Desenhamos o terreno

    BITMAP *menuImage_Ground = create_bitmap(SCREEN_W, SCREEN_H);

    drawGround(&menuImage_Ground, &groundMatrix);

    BITMAP *menuImage_TiledGround = create_bitmap(SCREEN_W, SCREEN_H);

    draw_sprite(menuImage_TiledGround, menuImage_Ground, 0, 0);

    drawTiledGround(&menuImage_TiledGround, &groundMatrix);

    /* Criamos as representacoes das torres(disponiveis para serem arrastadas e adicionadas ao mapa) */

    Tower ***towers = allocTowersMatrix(12, 16);

    BITMAP *tower1DragIcon = load_bitmap("Imagens/Torres/torre1_120x60.bmp", NULL);
    int tower1DragIcon_PosX = 0;
	BITMAP *tower1Image[4];
	tower1Image[0] = load_bitmap("Imagens/Torres/tower1Drag.bmp", NULL);
	tower1Image[1] = load_bitmap("Imagens/Torres/tower1Drag.bmp", NULL);
	tower1Image[2] = load_bitmap("Imagens/Torres/tower1Drag.bmp", NULL);
	tower1Image[3] = load_bitmap("Imagens/Torres/tower1Drag.bmp", NULL);
    int tower1_coast = 80;
    int tower1_rangeRadius = 80;
    UIButton *tower1DragButton = uibutton_create(tower1Image, NULL, 90, 540, 40, 40);

    BITMAP *tower2DragIcon = load_bitmap("Imagens/Torres/torre2_120x60.bmp", NULL);
    int tower2DragIcon_PosX = 0;
	BITMAP *tower2Image[4];
	tower2Image[0] = load_bitmap("Imagens/Torres/tower2Drag.bmp", NULL);
	tower2Image[1] = load_bitmap("Imagens/Torres/tower2Drag.bmp", NULL);
	tower2Image[2] = load_bitmap("Imagens/Torres/tower2Drag.bmp", NULL);
	tower2Image[3] = load_bitmap("Imagens/Torres/tower2Drag.bmp", NULL);
	int tower2_coast = 200;
    int tower2_rangeRadius = 60;
    UIButton *tower2DragButton = uibutton_create(tower2Image, NULL, 160, 540, 40, 40);

    BITMAP *tower3DragIcon = load_bitmap("Imagens/Torres/torre3_120x60.bmp", NULL);
    int tower3DragIcon_PosX = 0;
	BITMAP *tower3Image[4];
	tower3Image[0] = load_bitmap("Imagens/Torres/tower3Drag.bmp", NULL);
	tower3Image[1] = load_bitmap("Imagens/Torres/tower3Drag.bmp", NULL);
	tower3Image[2] = load_bitmap("Imagens/Torres/tower3Drag.bmp", NULL);
	tower3Image[3] = load_bitmap("Imagens/Torres/tower3Drag.bmp", NULL);
	int tower3_coast = 140;
    int tower3_rangeRadius = 80;
    UIButton *tower3DragButton = uibutton_create(tower3Image, NULL, 230, 540, 40, 40);

    BITMAP *tower4DragIcon = load_bitmap("Imagens/Torres/torre4_120x60.bmp", NULL);
    int tower4DragIcon_PosX = 0;
	BITMAP *tower4Image[4];
	tower4Image[0] = load_bitmap("Imagens/Torres/tower4Drag.bmp", NULL);
	tower4Image[1] = load_bitmap("Imagens/Torres/tower4Drag.bmp", NULL);
	tower4Image[2] = load_bitmap("Imagens/Torres/tower4Drag.bmp", NULL);
	tower4Image[3] = load_bitmap("Imagens/Torres/tower4Drag.bmp", NULL);
	int tower4_coast = 160;
    int tower4_rangeRadius = 60;
    UIButton *tower4DragButton = uibutton_create(tower4Image, NULL, 300, 540, 40, 40);

    BITMAP *tower5DragIcon = load_bitmap("Imagens/Torres/torre5_120x60.bmp", NULL);
    int tower5DragIcon_PosX = 0;
    BITMAP *tower5Image[4];
	tower5Image[0] = load_bitmap("Imagens/Torres/tower5Drag.bmp", NULL);
	tower5Image[1] = load_bitmap("Imagens/Torres/tower5Drag.bmp", NULL);
	tower5Image[2] = load_bitmap("Imagens/Torres/tower5Drag.bmp", NULL);
	tower5Image[3] = load_bitmap("Imagens/Torres/tower5Drag.bmp", NULL);
	int tower5_coast = 400;
    int tower5_rangeRadius = 60;
    UIButton *tower5DragButton = uibutton_create(tower5Image, NULL, 370, 540, 40, 40);

    // Criamos a janela de pause

    BITMAP *mainMenuImages[4];
    mainMenuImages[0] = load_bitmap("Imagens/Botoes/mainMenuImage.bmp", NULL);
    mainMenuImages[1] = load_bitmap("Imagens/Botoes/mainMenuImage.bmp", NULL);
    mainMenuImages[2] = load_bitmap("Imagens/Botoes/mainMenuImage.bmp", NULL);
    mainMenuImages[3] = load_bitmap("Imagens/Botoes/mainMenuImage.bmp", NULL);
    UIButton *mainMenuButton = uibutton_create(mainMenuImages, NULL, (SCREEN_W/2)-160, (SCREEN_H/2)+50, 100, 50);

    BITMAP *levelMenuImages[4];
    levelMenuImages[0] = load_bitmap("Imagens/Botoes/levelSelectImage.bmp", NULL);
    levelMenuImages[1] = load_bitmap("Imagens/Botoes/levelSelectImage.bmp", NULL);
    levelMenuImages[2] = load_bitmap("Imagens/Botoes/levelSelectImage.bmp", NULL);
    levelMenuImages[3] = load_bitmap("Imagens/Botoes/levelSelectImage.bmp", NULL);
    UIButton *levelMenuButton = uibutton_create(levelMenuImages, NULL, (SCREEN_W/2)-50, (SCREEN_H/2)+50, 100, 50);

    BITMAP *continueImages[4];
    continueImages[0] = load_bitmap("Imagens/Botoes/resumeGameImage.bmp", NULL);
    continueImages[1] = load_bitmap("Imagens/Botoes/resumeGameImage.bmp", NULL);
    continueImages[2] = load_bitmap("Imagens/Botoes/resumeGameImage.bmp", NULL);
    continueImages[3] = load_bitmap("Imagens/Botoes/resumeGameImage.bmp", NULL);
    UIButton *continueButton = uibutton_create(continueImages, NULL, (SCREEN_W/2)+60, (SCREEN_H/2)+50, 100, 50);

    // Criamos o botao do almanaque

    BITMAP *almanaqueImages[4];
    almanaqueImages[0] = load_bitmap("Imagens/Botoes/almanacImage.bmp", NULL);
    almanaqueImages[1] = load_bitmap("Imagens/Botoes/almanacImage.bmp", NULL);
    almanaqueImages[2] = load_bitmap("Imagens/Botoes/almanacImage.bmp", NULL);
    almanaqueImages[3] = load_bitmap("Imagens/Botoes/almanacImage.bmp", NULL);
    UIButton *almanaqueButton = uibutton_create(almanaqueImages, NULL, 440, 535, 100, 50);

	// Criamos as listas encadeadas que armazenaram as conexoes entre torres e inimigos

	Bullet *bullets = NULL;

	// Criamos as variaveis auxiliares no redirecionamento dos alvos

	int prefsType = 0;

	int shootingPrefs[3] = {4,4,4};

	// Criamos as variaveis auxiliares na producao do log de saida

	int lastRound = 0,lockRoundBegin = false;
	int victory,spentMoney = 0, index = 0;
	int *enemiesCounter = (int *)calloc(5, sizeof(int));
	int **towersByRound = allocIntegerMatrix(qntRounds, 5);

	// Score global

	int scoreLevel = 0;

    // Game loop

    play_midi(gameMusic, true);

    while (!exitScreen) {

        while (!exitScreen && ticks > 0) {

        	if (key[KEY_ESC]){ exitScreen = true; nextScreen = telaEndScreen; }

            if (mouse_b != 1) { mouseLocker = false; }

            if (gamePaused == false) {

				// Analisamos se o usuario esta arrastando uma torre,para desenharmos o terreno apropriado

				draw_sprite(screenBuffer, (draggingTower == true ? menuImage_TiledGround : menuImage_Ground), 0, 0);

				// Verificamos quais torres o usuario pode comprar

				(qntBudget >= tower1_coast ? uibutton_enable(tower1DragButton) : uibutton_disable(tower1DragButton));
				(qntBudget >= tower2_coast ? uibutton_enable(tower2DragButton) : uibutton_disable(tower2DragButton));
				(qntBudget >= tower3_coast ? uibutton_enable(tower3DragButton) : uibutton_disable(tower3DragButton));
				(qntBudget >= tower4_coast ? uibutton_enable(tower4DragButton) : uibutton_disable(tower4DragButton));
				(qntBudget >= tower5_coast ? uibutton_enable(tower5DragButton) : uibutton_disable(tower5DragButton));

				// Atualizamos os marcadores dos botoes

				uibutton_update(pauseButton);
				uibutton_update(roundPlayButton);
				uibutton_update(tower1DragButton);
				uibutton_update(tower2DragButton);
				uibutton_update(tower3DragButton);
				uibutton_update(tower4DragButton);
				uibutton_update(tower5DragButton);
				uibutton_update(almanaqueButton);

				if (pauseButton->isClicked == true && mouseLocker == false) {

					gamePaused = true;

				}

				if (roundPlayButton->isClicked == true && mouseLocker == false){

					midi_resume();

					lockRoundBegin = false;

					uibutton_sethidden(pauseButton, false);
					uibutton_sethidden(roundPlayButton, true);

				}

				if (almanaqueButton->isClicked == true && mouseLocker == false){

            		pokeDexScreen(0);

            		ticks = 1;

            	}

				drawRangeRadius(towers, screenBuffer);

				// The magic happens here

				if (timerVisible == false){

					if (qntWonRounds < qntRounds && qntLifes > 0) {

						checkEnemies(enemies, qntEnemies, groundMatrix, &qntLifes, &qntBudget, enemiesCounter, &scoreLevel);

						targetEnemies(towers, enemies, qntEnemiesPerLine[qntWonRounds], &bullets, &shootingPrefs[0]);

						if (lockRoundBegin == false){

							drawEnemies(screenBuffer, enemies, qntEnemies, &qntWonRounds, qntEnemiesPerLine[qntWonRounds], groundAxis, qntAxis);

							if (lastRound != qntWonRounds){

								lockRoundBegin = true;

								midi_pause();

								play_sample(levelComplete, 255, 0, 1000, 0);

								uibutton_sethidden(pauseButton, true);
								uibutton_sethidden(roundPlayButton, false);

								lastRound = qntWonRounds;

								index++;

							}

						}

						if (qntWonRounds < qntRounds){

							drawBullets(screenBuffer, &bullets, enemies, qntEnemiesPerLine[qntWonRounds], normalSound, splashSound);

							drawSlows(screenBuffer, towers);

							poisonEnemies(enemies, qntEnemiesPerLine[qntWonRounds]);

						}

					} else if (qntWonRounds == qntRounds && qntLifes > 0) {

						victory = true;

						nextScreen = telaResultado1;
						exitScreen = true;

					} else {

						victory = false;

						nextScreen = telaResultado2;
						exitScreen = true;
					}

				}

				// Verificamos se,e qual,botao foi clicado,para arrastarmos a imagem correspondente a torre

				if (tower1DragButton->isClicked == true) {

					draggingTower = true;

					draggingTowerType = tNormal;

					tower1DragButton->posX = mouse_x-20;
					tower1DragButton->posY = mouse_y-20;

					int tempColor = (positionAvailible(groundMatrix, towers, mouse_x, mouse_y) == true ? makeacol(255, 255, 255, 75) : makeacol(255, 0, 0, 100));

					circlefill(screenBuffer, mouse_x-(mouse_x%40)+20, mouse_y-(mouse_y%40)+20, tower1_rangeRadius+20, tempColor);

					drawTileBlink(&auxBlinkCounter, &auxBlinkLock, screenBuffer, mouse_x-(mouse_x%40), mouse_y-(mouse_y%40));

				}else if (tower2DragButton->isClicked == true) {

					draggingTower = true;

					draggingTowerType = tSplash;

					tower2DragButton->posX = mouse_x-20;
					tower2DragButton->posY = mouse_y-20;

					int tempColor = (positionAvailible(groundMatrix, towers, mouse_x, mouse_y) == true ? makeacol(255, 255, 255, 75) : makeacol(255, 0, 0, 100));

					circlefill(screenBuffer, mouse_x-(mouse_x%40)+20, mouse_y-(mouse_y%40)+20, tower2_rangeRadius+20, tempColor);

					drawTileBlink(&auxBlinkCounter, &auxBlinkLock, screenBuffer, mouse_x-(mouse_x%40), mouse_y-(mouse_y%40));

				}else if (tower3DragButton->isClicked == true) {

					draggingTower = true;

					draggingTowerType = tSlow;

					tower3DragButton->posX = mouse_x-20;
					tower3DragButton->posY = mouse_y-20;

					int tempColor = (positionAvailible(groundMatrix, towers, mouse_x, mouse_y) == true ? makeacol(255, 255, 255, 75) : makeacol(255, 0, 0, 100));

					circlefill(screenBuffer, mouse_x-(mouse_x%40)+20, mouse_y-(mouse_y%40)+20, tower3_rangeRadius+20, tempColor);

					drawTileBlink(&auxBlinkCounter, &auxBlinkLock, screenBuffer, mouse_x-(mouse_x%40), mouse_y-(mouse_y%40));

				}else if (tower4DragButton->isClicked == true) {

					draggingTower = true;

					draggingTowerType = tPoison;

					tower4DragButton->posX = mouse_x-20;
					tower4DragButton->posY = mouse_y-20;

					int tempColor = (positionAvailible(groundMatrix, towers, mouse_x, mouse_y) == true ? makeacol(255, 255, 255, 75) : makeacol(255, 0, 0, 100));

					circlefill(screenBuffer, mouse_x-(mouse_x%40)+20, mouse_y-(mouse_y%40)+20, tower4_rangeRadius+20, tempColor);

					drawTileBlink(&auxBlinkCounter, &auxBlinkLock, screenBuffer, mouse_x-(mouse_x%40), mouse_y-(mouse_y%40));

				}else if (tower5DragButton->isClicked == true) {

					draggingTower = true;

					draggingTowerType = tBeacon;

					tower5DragButton->posX = mouse_x-20;
					tower5DragButton->posY = mouse_y-20;

					int tempColor = (positionAvailible(groundMatrix, towers, mouse_x, mouse_y) == true ? makeacol(255, 255, 255, 75) : makeacol(255, 0, 0, 100));

					circlefill(screenBuffer, mouse_x-(mouse_x%40)+20, mouse_y-(mouse_y%40)+20, tower5_rangeRadius+20, tempColor);

					drawTileBlink(&auxBlinkCounter, &auxBlinkLock, screenBuffer, mouse_x-(mouse_x%40), mouse_y-(mouse_y%40));

				}else{

					// Identificamos o tipo da torre que estava sendo arrastada,e caso a posicao que ela foi deixada seja valida,a adicionamos

					if (draggingTower == true) {

						if (positionAvailible(groundMatrix, towers, mouse_x, mouse_y) == true) {

							switch (draggingTowerType) {

								case tNormal:

									placeTower(towers, tNormal, mouse_x, mouse_y, towersByRound, index);
									qntBudget -= tower1_coast;
									spentMoney += tower1_coast;

									break;

								case tSplash:

									placeTower(towers, tSplash, mouse_x, mouse_y, towersByRound, index);
									qntBudget -= tower2_coast;
									spentMoney += tower2_coast;

									break;

								case tSlow:

									placeTower(towers, tSlow, mouse_x, mouse_y, towersByRound, index);
									qntBudget -= tower3_coast;
									spentMoney += tower3_coast;

									break;

								case tPoison:

									placeTower(towers, tPoison, mouse_x, mouse_y, towersByRound, index);
									qntBudget -= tower4_coast;
									spentMoney += tower4_coast;

									break;

								case tBeacon:

									placeTower(towers, tBeacon, mouse_x, mouse_y, towersByRound, index);
									qntBudget -= tower5_coast;
									spentMoney += tower5_coast;

									break;

								default: break;

							}

						}

						// Retornamos os icones as suas posicoes iniciais

						tower1DragButton->posX = 90;
						tower1DragButton->posY = 540;

						tower2DragButton->posX = 160;
						tower2DragButton->posY = 540;

						tower3DragButton->posX = 230;
						tower3DragButton->posY = 540;

						tower4DragButton->posX = 300;
						tower4DragButton->posY = 540;

						tower5DragButton->posX = 370;
						tower5DragButton->posY = 540;

					}

					draggingTower = false;

					draggingTowerType = 0;

				}

				// Desenhamos as torres

				drawTowers(towers, screenBuffer, qntBudget, &hudVisible);

				// Realizamos verificacoes quanto ao HUD das torres

				if (draggingTower == false && mouseLocker == false && mouse_b == 1) {

					mouseLocker = true;

					if (mouse_x >= 80 && mouse_x <= 720 && mouse_y >= 40 && mouse_y <= 520) {

						if (hudVisible == false){

							checkTowersHUD(towers, screenBuffer, mouse_x, mouse_y);

						}

					}

					prefsType = checkClickedHUD(towers, screenBuffer, mouse_x, mouse_y, &qntBudget, levelUp, &spentMoney);

					if (prefsType != 0){

						menuShootingPrefs(screenBuffer, prefsType, &shootingPrefs[0]);

						prefsType = 0;

						closeAllHUD(towers);

					}

				}

				if (draggingTower == true) {

					closeAllHUD(towers);

				}else{

					draggingTowerType = 0;

				}

				resetBeaconEffect(towers);

				// Desenhamos os botoes inferiores,representando as torres disponiveis

				if (hudVisible == false) {

					switch (draggingTowerType) {

						case 0:
							uibutton_draw(tower1DragButton, tower1DragButton->posX, tower1DragButton->posY, screenBuffer);
							uibutton_draw(tower2DragButton, tower2DragButton->posX, tower2DragButton->posY, screenBuffer);
							uibutton_draw(tower3DragButton, tower3DragButton->posX, tower3DragButton->posY, screenBuffer);
							uibutton_draw(tower4DragButton, tower4DragButton->posX, tower4DragButton->posY, screenBuffer);
							uibutton_draw(tower5DragButton, tower5DragButton->posX, tower5DragButton->posY, screenBuffer);
							break;

						case tNormal:
							uibutton_draw(tower1DragButton, tower1DragButton->posX, tower1DragButton->posY, screenBuffer);
							break;

						case tSplash:
							uibutton_draw(tower2DragButton, tower2DragButton->posX, tower2DragButton->posY, screenBuffer);
							break;

						case tSlow:
							uibutton_draw(tower3DragButton, tower3DragButton->posX, tower3DragButton->posY, screenBuffer);
							break;

						case tPoison:
							uibutton_draw(tower4DragButton, tower4DragButton->posX, tower4DragButton->posY, screenBuffer);
							break;

						case tBeacon:
							uibutton_draw(tower5DragButton, tower5DragButton->posX, tower5DragButton->posY, screenBuffer);
							break;

					}

				}

				if (draggingTower == false && hudVisible == false) {

					rectfill(screenBuffer, 0, 520, 800, 600, makeacol(0, 0, 0, 100));

					masked_blit(tower1DragIcon, screenBuffer, tower1DragIcon_PosX, 0, 80, 525, 60, 60);
					textprintf_centre_ex(screenBuffer, font, 110, 590, makecol(255, 255, 255), -1, "$%i",tower1_coast);

					masked_blit(tower2DragIcon, screenBuffer, tower2DragIcon_PosX, 0, 150, 525, 60, 60);
					textprintf_centre_ex(screenBuffer, font, 180, 590, makecol(255, 255, 255), -1, "$%i",tower2_coast);

					masked_blit(tower3DragIcon, screenBuffer, tower3DragIcon_PosX, 0, 220, 525, 60, 60);
					textprintf_centre_ex(screenBuffer, font, 250, 590, makecol(255, 255, 255), -1, "$%i",tower3_coast);

					masked_blit(tower4DragIcon, screenBuffer, tower4DragIcon_PosX, 0, 290, 525, 60, 60);
					textprintf_centre_ex(screenBuffer, font, 320, 590, makecol(255, 255, 255), -1, "$%i",tower4_coast);

					masked_blit(tower5DragIcon, screenBuffer, tower5DragIcon_PosX, 0, 360, 525, 60, 60);
					textprintf_centre_ex(screenBuffer, font, 390, 590, makecol(255, 255, 255), -1, "$%i",tower5_coast);

					uibutton_draw(almanaqueButton, almanaqueButton->posX, almanaqueButton->posY, screenBuffer);

					textprintf_centre_ex(screenBuffer, font, 602, 537, makecol(255, 255, 255), -1, "MONEY $%i",qntBudget);

                    textprintf_centre_ex(screenBuffer, font, 586, 557, makecol(255, 255, 255), -1, "ROUND %i",qntWonRounds+1);

                    textprintf_centre_ex(screenBuffer, font, 590, 577, makecol(255, 255, 255), -1, "LIFES %i",qntLifes);

				}

				// Verificamos se o jogo foi pausado

				if (gamePaused == true) {

					draw_sprite(pausedScreenBuffer, screenBuffer, 0, 0);

				}

				uibutton_draw(pauseButton, pauseButton->posX, pauseButton->posY, screenBuffer);
				uibutton_draw(roundPlayButton, roundPlayButton->posX, roundPlayButton->posY, screenBuffer);

				if (timerVisible == true){

            		rectfill(screenBuffer, (SCREEN_W/2)-20, 16, (SCREEN_W/2)+20, 30, makeacol(0, 0, 0, 100));

            		textprintf_centre_ex(screenBuffer, font, (SCREEN_W/2), 20, makeacol(255, 255, 255, 255), -1, "%is", 15-(qntTimer/33));

            		qntTimer++;

            		if (qntTimer > 495){

            			timerVisible = false;

            		}

            	}

            }else{

            	uibutton_update(mainMenuButton);
            	uibutton_update(levelMenuButton);
            	uibutton_update(continueButton);

            	if (mainMenuButton->isClicked == true){

            		nextScreen = telaMenuPrincipal;

            		exitScreen = true;

            	}

            	if (levelMenuButton->isClicked == true){

            		nextScreen = telaMenuLevels;

            		exitScreen = true;

            	}

            	if (continueButton->isClicked == true){

            		gamePaused = false;

            	}

            	draw_sprite(screenBuffer, pausedScreenBuffer, 0, 0);

            	rectfill(screenBuffer, 0, 0, SCREEN_W, SCREEN_H, makeacol(0, 0, 0, 150));

            	draw_sprite(screenBuffer, pauseMenu, (SCREEN_W/2)-170, (SCREEN_H/2)-110);

            	textprintf_centre_ex(screenBuffer, font, (SCREEN_W/2), (SCREEN_H/2)-4, makeacol(255, 255, 255, 255), -1, "SCORE: %i", scoreLevel);

            	uibutton_draw(mainMenuButton, mainMenuButton->posX, mainMenuButton->posY, screenBuffer);
            	uibutton_draw(levelMenuButton, levelMenuButton->posX, levelMenuButton->posY, screenBuffer);
            	uibutton_draw(continueButton, continueButton->posX, continueButton->posY, screenBuffer);

            }

            draw_sprite(screenBuffer, menuImage_Mouse[menuImage_Mouse_Frame], mouse_x-6, mouse_y);

			draw_sprite(screen, screenBuffer, 0, 0);

			clear(screenBuffer);

            ticks--;

        }

    }

	//-----

	produceOutLog(victory, qntWonRounds, qntRounds, enemiesCounter, spentMoney, qntBudget, qntLifes, towersByRound);

	switch(level){

		case 0: userLogs->scoreLvM = (scoreLevel > userLogs->scoreLvM ? scoreLevel : userLogs->scoreLvM); break;

		case 1: userLogs->scoreLv1 = (scoreLevel > userLogs->scoreLv1 ? scoreLevel : userLogs->scoreLv1); break;

		case 2: userLogs->scoreLv2 = (scoreLevel > userLogs->scoreLv2 ? scoreLevel : userLogs->scoreLv2); break;

		case 3: userLogs->scoreLv3 = (scoreLevel > userLogs->scoreLv3 ? scoreLevel : userLogs->scoreLv3); break;

		case 4: userLogs->scoreLv4 = (scoreLevel > userLogs->scoreLv4 ? scoreLevel : userLogs->scoreLv4); break;

		case 5: userLogs->scoreLv5 = (scoreLevel > userLogs->scoreLv5 ? scoreLevel : userLogs->scoreLv5); break;

		case 6: userLogs->scoreLv6 = (scoreLevel > userLogs->scoreLv6 ? scoreLevel : userLogs->scoreLv6); break;

	}

	//-----

    destroy_midi(gameMusic);
    destroy_sample(levelComplete);
    destroy_sample(levelUp);
    destroy_sample(splashSound);
    destroy_sample(normalSound);

    destroy_bitmap(screenBuffer);

    destroy_bitmap(menuImage_Mouse[0]);
    destroy_bitmap(menuImage_Mouse[1]);

    uibutton_release(pauseButton);

    destroy_bitmap(pauseMenu);
    destroy_bitmap(enemyImage1[0]);
    destroy_bitmap(enemyImage1[1]);
    destroy_bitmap(enemyImage1[2]);
    destroy_bitmap(enemyImage1[3]);
    destroy_bitmap(enemyImage1[4]);
    destroy_bitmap(enemyImage1[5]);
    destroy_bitmap(enemyImage1[6]);
    destroy_bitmap(enemyImage2[0]);
    destroy_bitmap(enemyImage3[0]);
    destroy_bitmap(enemyImage4[0]);
    destroy_bitmap(enemyImage5[0]);
    destroy_bitmap(enemyImage5[1]);

    destroy_bitmap(tower1DragIcon);
    destroy_bitmap(tower2DragIcon);
    destroy_bitmap(tower3DragIcon);
    destroy_bitmap(tower4DragIcon);
    destroy_bitmap(tower5DragIcon);

    uibutton_release(tower1DragButton);
    uibutton_release(tower2DragButton);
    uibutton_release(tower3DragButton);
    uibutton_release(tower4DragButton);
    uibutton_release(tower5DragButton);

    uibutton_release(roundPlayButton);

    uibutton_release(mainMenuButton);
    uibutton_release(levelMenuButton);
    uibutton_release(continueButton);
    uibutton_release(almanaqueButton);

    return nextScreen;

}

inline void init () {

	allegro_init();
	set_color_depth(32);
	set_gfx_mode(GFX_AUTODETECT, 800, 600, 0, 0);

	set_alpha_blender();
	drawing_mode(DRAW_MODE_TRANS, 0, 0, 0);

	install_timer();
	install_keyboard();
	install_mouse();
	install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, NULL);

	ticks = 0;
	LOCK_FUNCTION(tickCounter);
	LOCK_VARIABLE(ticks);
	install_int_ex(tickCounter, MSEC_TO_TIMER(30));

}

inline void deinit () {

	clear_keybuf();
	allegro_exit();

}

int main () {

	srand((unsigned)time(NULL));

	init();

	int exitGame = false;

	int gameScreen = telaMenuPrincipal;

	int loadLevel = 0;

	User *userLogs = (User *)malloc(sizeof(User));

	loadMainUser(userLogs);

	menuSplashScreen(splashScreenDuration);

    menuLoading(loadingMainMenuDuration);

	while (!exitGame) {

		if (key[KEY_ESC]) { exitGame = true; }

	    while (!exitGame && ticks > 0) {

	        switch (gameScreen) {

	            case telaMenuPrincipal: gameScreen = menuPrincipal(userLogs); break;

	            case telaMenuLevels: gameScreen = menuLevels(&loadLevel, userLogs); break;

	            case telaMenuJogar: gameScreen = menuJogar(loadLevel, userLogs); break;

	            case telaAlmanaqueMenu: gameScreen = pokeDexScreen(telaMenuPrincipal); break;

	            case telaAlmanaqueJogo: gameScreen = pokeDexScreen(telaMenuJogar); break;

	            case telaResultado1: gameScreen = resultScreen(1); break;

	            case telaResultado2: gameScreen = resultScreen(2); break;

	            case telaEndScreen: exitGame = true; break;

	        }

	    }

	}

	updateMainUser(userLogs);

	deinit();

	return 0;

}

END_OF_MAIN()
