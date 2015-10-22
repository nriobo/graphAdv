// loaditems.cpp
int exits[][2]={{19, 1}, {21, 0}}; // {item, nextRoom}
bool gameActions[NUMBER_GAME_ACTIONS] = {true, false, false};
//playerPhrases plPhrases[2];

// test: hardcoded!!!
playerPhrases plPhrases[] = { 
//              {item, serial, phrase, alreadySaid, nextAnswer, everlasting}, 
              {1, 1, "Hola, Alfredito.", 0, 1, 0}, 
              {1, 2, "Wow tu parles, taureau !", 0, 2, 0},
              {1, 3, "As-tu quelque chose à me dire ?", 0, 3, 0},
              {1, 4, "Allez, ciao.", 0, 0, 1}
              
              };
              
itemPhrases itPhrases[] = {
//            {serial, phrase, alreadySaid, continueDialog },
            {1, "Salut, mon grand.", 0, false },
            {2, "Beaucoup mieux que toi.", 0, true },
            {3, "Oui, mais j'ai besoin d'argent pour ça.", 0, false }
            
            };

items[0].frames = 1;
items[0].correctY = 16;
items[0].w = 45;
items[0].h = 63;
items[0].y = 90;
items[0].x = 140;
sprintf(items[0].name, TEXT_OBJ_DOOR);
bitmapItems[0] = create_sub_bitmap((BITMAP *)my_datafile[DOOR].dat, 0, 0, 45, 63);

items[0].actionDoable |= ACTION_IR_A;
items[0].actionDoable |= ACTION_ABRIR;
items[0].actionDoable |= ACTION_USAR;
sprintf(items[0].responseNo[ACTION_AGARRAR_INDEX], TEXT_RESP_SURE);

// ouverte
items[19].frames = 1;
items[19].correctY = 16;
items[19].w = 45;
items[19].h = 63;
items[19].y = 90;
items[19].x = 140;
sprintf(items[19].name, TEXT_OBJ_DOOR);
bitmapItems[19] = create_sub_bitmap((BITMAP *)my_datafile[DOOR].dat, 45, 0, 90, 63);
items[19].actionDoable |= ACTION_IR_A;
items[19].actionDoable |= ACTION_CERRAR;
sprintf(items[19].responseNo[ACTION_AGARRAR_INDEX], TEXT_RESP_SURE);
sprintf(items[19].responseNo[ACTION_ABRIR_INDEX], TEXT_RESP_ALREADY_OPEN);
items[19].alive = false;
items[19].canEnter = true;  // conflict with actionDoable = ACTION_ENTER ???
	  
items[1].frames = 3;
items[1].w = 127;
items[1].h = 101;
items[1].y = 160;
items[1].x = 160;
items[1].frameSpeed = 0.071;
sprintf(items[1].name, TEXT_OBJ_BULL);
bitmapItems[1] = (BITMAP *)my_datafile[ALFREDITO].dat;
items[1].drawTop = true;   
sprintf(items[1].responseNo[ACTION_AGARRAR_INDEX], TEXT_RESP_CANT_PICKUP_BULL);
items[1].alive = true;
items[1].actionDoable |= ACTION_HABLAR;

items[2].frames = 1;
items[2].w = 25;
items[2].h = 24;
items[2].y = 137;
items[2].x = 520;
items[2].frameSpeed = 0.1;
sprintf(items[2].name, TEXT_OBJ_SIGN);
bitmapItems[2] = (BITMAP *)my_datafile[SIGN].dat;
items[2].actionDoable |= ACTION_AGARRAR;
items[2].actionDoable |= ACTION_IR_A;
items[2].actionDoable |= ACTION_USAR;
sprintf(items[2].responseYes[ACTION_AGARRAR_INDEX], TEXT_RESP_SIGN_PICKEDUP);        


items[3].frames = 1;
items[3].w = 32;
items[3].h = 34;
items[3].y = 120;
items[3].x = 20;
items[3].frameSpeed = 0.1;
sprintf(items[3].name, TEXT_OBJ_WEALTH);
bitmapItems[3] = (BITMAP *)my_datafile[COINS].dat;
items[3].actionDoable |= ACTION_AGARRAR;
items[3].actionDoable |= ACTION_IR_A;
//         debug
items[3].actionDoable |= ACTION_ENTER;
items[3].nextRoom = 1;

sprintf(items[3].responseYes[ACTION_AGARRAR_INDEX], TEXT_RESP_RICH);                

items[4].frames = 1;
items[4].w = 20;
items[4].h = 34;
items[4].y = 210;
items[4].x = 240;
items[4].frameSpeed = 0.1;
sprintf(items[4].name, TEXT_OBJ_TOTEM);
bitmapItems[4] = (BITMAP *)my_datafile[STAN_SPEAKING].dat;
items[4].actionDoable |= ACTION_IR_A;
sprintf(items[4].responseNo[ACTION_AGARRAR_INDEX], TEXT_RESP_WHATFOR); 

items[5].frames = 1;
items[5].w = 26;
items[5].h = 33;
items[5].y = 54;
items[5].x = 454;
items[5].frameSpeed = 0.1;
sprintf(items[5].name, TEXT_OBJ_BRANCH);
bitmapItems[5] = (BITMAP *)my_datafile[BRANCH].dat;
items[5].actionDoable |= ACTION_IR_A;
items[5].actionDoable |= ACTION_USAR;
sprintf(items[5].responseNo[ACTION_AGARRAR_INDEX], TEXT_RESP_PICKUP_BRANCH); 

items[7].frames = 1;
items[7].w = 22;
items[7].h = 39;
items[7].y = 120;
items[7].x = 60;
items[7].frameSpeed = 0.1;
sprintf(items[7].name, TEXT_OBJ_AXE);
bitmapItems[7] = create_sub_bitmap((BITMAP *)my_datafile[WEAPONS].dat, 30, 0, 22, 39);
items[7].actionDoable |= ACTION_IR_A;
items[7].actionDoable |= ACTION_AGARRAR;

items[6].frames = 1;
items[6].w = 49;
items[6].h = 20;
items[6].y = 120;
items[6].x = 60;
items[6].frameSpeed = 0.1;
sprintf(items[6].name, TEXT_OBJ_CHGUN);
bitmapItems[6] = create_sub_bitmap((BITMAP *)my_datafile[WEAPONS].dat, 52, 0, 49, 20);
items[6].actionDoable |= ACTION_IR_A;
items[6].actionDoable |= ACTION_AGARRAR;
items[6].alive = false;


// TO DO: keep cleaning test-hardcoded names/words!
items[8].frames = 1;
items[8].w = 64;
items[8].h = 86;
items[8].y = 174;
items[8].x = 90;
items[8].frameSpeed = 0.1;
sprintf(items[8].name, "Matón");
bitmapItems[8] = load_bmp ("peroncho.bmp", NULL);
items[8].actionDoable |= ACTION_IR_A;


items[9].frames = 1;
items[9].w = 49;
items[9].h = 36;
items[9].y = 35;
items[9].x = 454;
items[9].frameSpeed = 0.1;
sprintf(items[9].name, TEXT_OBJ_KEY);
bitmapItems[9] = create_sub_bitmap((BITMAP *)my_datafile[WEAPONS].dat, 52, 20, 49, 36);
items[9].actionDoable |= ACTION_IR_A;
items[9].actionDoable |= ACTION_AGARRAR;

items[20].frames = 3;
items[20].w = 48;
items[20].h = 89;
items[20].y = 160;
items[20].x = 180;
items[20].frameSpeed = 0.1;
sprintf(items[20].name, "Drapeau");
bitmapItems[20] = (BITMAP *)my_datafile[FLAG].dat;
items[20].drawTop = true;
sprintf(items[20].responseNo[ACTION_HABLAR_INDEX], TEXT_RESP_TALK_FLAG); 

items[21].frames = 1;
items[21].correctY = 16;
items[21].w = 45;
items[21].h = 100;
items[21].y = 150;
items[21].x = 590;
sprintf(items[21].name, "Plage");
bitmapItems[21] = load_bmp ("transp.bmp", NULL);
items[21].actionDoable |= ACTION_IR_A;
items[21].canEnter = true;  //      

items[22].frames = 1;
items[22].correctY = 16;
items[22].w = 45;
items[22].h = 100;
items[22].y = 150;
items[22].x = 20;
sprintf(items[22].name, "La joie eternelle");
bitmapItems[22] = load_bmp ("transp.bmp", NULL);
//        items[22].actionDoable |= ACTION_IR_A;
sprintf(items[22].responseNo[ACTION_IR_A_INDEX], "No puedo. Este sindicalista la bloquea."); 

items[22].canEnter = true;  //      

level[0].LoadMap("level0.txt", 0);
level[0].scrollableScreen = false;
level[0].createActions();
level[0].itemsCollectedStartPosition = 0;

// for int i=... ???
itemsInLevel[0][0] = 0;
itemsInLevel[0][1] = 20;
itemsInLevel[0][2] = 2;
itemsInLevel[0][3] = 5;
itemsInLevel[0][4] = 6;
itemsInLevel[0][5] = 7;
//itemsInLevel[0][6] = 8;
itemsInLevel[0][7] = 9;
itemsInLevel[0][8] = 10;
itemsInLevel[0][9] = 19;
itemsInLevel[0][10] = 1;
itemsInLevel[0][11] = -1;
itemsInLevel[1][0] = 3;
//itemsInLevel[1][1] = 1;
itemsInLevel[1][2] = 21;
itemsInLevel[1][3] = 8;
itemsInLevel[1][4] = 22;
itemsInLevel[1][5] = -1;


