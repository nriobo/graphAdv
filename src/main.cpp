//main.cpp

#include "main.h"
#include "datafile.h"   // pour les datafiles
#define ALCANCE_X 80
#define ALCANCE_Y 80

bool levelChanged = false;
bool mouseOriginal = true;
bool usingItem = false;
bool mouseShowing = true;
bool animationOn = false;
bool answerChosen = false;
int answerSelected;
bool showText = true;

int animationSequence = 0;
int animationSequenceIntCounter = 0;

using namespace std;

int main()
{
    char textLives[5], textCoins[5];
    int gameTimer = 0;
    bool fullscreen = false;
    int collisions = 0;
    bool done = false;      
    initAllegro(fullscreen);   
    bool walkingTowardsDoor = false;

    DATAFILE *my_datafile = load_datafile("datafile.dat");
    //Check that the datafile was created correctly
    if(my_datafile == NULL)
    {
       set_gfx_mode(GFX_TEXT,0,0,0,0);
       allegro_message("Could not load datafile!");
       exit(EXIT_FAILURE);
    }

    the_music = (MIDI *)my_datafile[rmce].dat;
    if (!the_music)
      allegro_message("Error reading MIDI file.\n");

    startMusic();
    musicOn = true;
    midi_pause();

    BITMAP *bitmapItems[NUMBER_ITEMS];
    
    BITMAP *buffer = create_bitmap(SCR_W, SCR_H);
    BITMAP *spritePlayer = (BITMAP *)my_datafile[STAN].dat;
    BITMAP *blackBg = (BITMAP *)my_datafile[BLACK_BG].dat;
    BITMAP *originalMouse = (BITMAP *)my_datafile[MOUSE_POINTER].dat;
    BITMAP *spritePlayerSpeaking = (BITMAP *)my_datafile[STAN_SPEAKING].dat;
    BITMAP *spriteCollected = (BITMAP *)my_datafile[COLLECTED].dat;
    
    LevelClass level[NUMBER_LEVELS];    //Create an array of levels... right now we only have one.
    PlayerClass player;     //Create the player
    player.x = player.destX = 300;
    player.y = player.destY = 150;
    player.frames = 6;      // 7th is when the character is not walking
    player.w = 40;
    player.h = 62;
    float offsetX, offsetY;
    int tgt = 0;  // to avoid mouse click bouncing
    BITMAP *bitmapMousePointer = createMouse(originalMouse);
    ItemsClass items[NUMBER_ITEMS];
    
    #include "LoadItems.h"
    
    actionSelectedNumber = 0;    // start with action "go to"
    sprintf(actionSelected, "%s", level[0].GetActionName(actionSelectedNumber));

    animationSequence = ANIMATION_SEQUENCE_START;
    animationOn = true;
    showActions = false;
    hideMouse();
    player.alive = false;

    while ( !done )     //while we're not done with the game
    {
        while ( speedCounter > 0 )
        {
		  if(!animationOn)
		  {
				int pos;
				pos = mouse_pos;
				mousePointer.x = pos >> 16;
				mousePointer.y = pos & 0x0000ffff;

				if ( key[KEY_F5] )  //fullscreen toggle
				{
					if ( fullscreen )
					{
						set_gfx_mode(GFX_AUTODETECT_WINDOWED, SCR_W, SCR_H, 0, 0);
						fullscreen = false;
					}
					else
					{
						set_gfx_mode(GFX_AUTODETECT, SCR_W, SCR_H, 0, 0);
						fullscreen = true;
					}
				}
				if ( key[KEY_ESC] )      //quit game with F4 or ESC
				{
					 if (gameTimer > 600)
					   done = true;
				}
				if ( key[KEY_S] )        // turn on and off music
				{
					 if (musicOn)
					 {
					   musicOn = false;
					   midi_pause();
					 } 
					 else
					 {
					   musicOn = true;
					   midi_resume();
					 }
				}
				// mouse
				if (mouse_b & LEFT_BUTTON && gameTimer - tgt > 100)
				{
				  tgt = gameTimer;
				  itemClickedNumber = itemSelectedNumber;
				  walkingTowardsDoor = false;
				  if (mousePointer.y < 290)
				  {
					if (!mouseOriginal)
					  bitmapMousePointer = createMouse(originalMouse);
									 
					player.destX = mousePointer.x-(player.w)/2;
					player.destY = mousePointer.y-(player.h)/2;

					if (itemSelected[0] != 0)
					{
					  actionResult = level[0].GetActionBinary(actionSelectedNumber) & items[itemsInLevel[activeLevel][itemSelectedNumber]].actionDoable;
					  if (actionResult == 0)     // cannot do that action on that item                                   
					  {
						  for (int ii=0; ii<NUMBER_ACTIONS; ii++)
						  {
							if (actionSelectedNumber == ii)
							{
							  if (items[itemsInLevel[activeLevel][itemSelectedNumber]].responseNo[ii][0] != 0)
							  {
								strcpy(actionDebug, items[itemsInLevel[activeLevel][itemSelectedNumber]].responseNo[ii]);
								actionDebugLine2[0] = 0;  
							  }
							  else
							  {
								actionDebugLine2[0]=0;
								if (actionSelectedNumber == ACTION_IR_A_INDEX)
								  sprintf(actionDebug, TEXT_CANT_GO_THERE);
								else
								  sprintf(actionDebug, TEXT_CANT_DO_THAT);
							  }
							}
						  }
						  player.speaking = true;
						  player.speakTime = 0;
						  player.walking = false;
						  player.destX = player.x;
						  player.destY = player.y;
					  }
					  else if (actionSelectedNumber == ACTION_ABRIR_INDEX)   // switch action??
					  {
						  if (gameActions[GAME_ACT_DOOR1_UNLOCKED])
						  {
							  tgt = gameTimer;
							  items[itemsInLevel[activeLevel][itemSelectedNumber]].alive = false;
							  // debug!
							  items[itemsInLevel[activeLevel][9]].alive = true;
							  // \debug!
							  
							  if (items[itemsInLevel[activeLevel][itemSelectedNumber]].responseYes[ACTION_ABRIR_INDEX][0] != 0)
							  {
								strcpy(actionDebug, items[itemsInLevel[activeLevel][itemSelectedNumber]].responseYes[ACTION_ABRIR_INDEX]);
								actionDebugLine2[0] = 0;
								player.speaking = true;
								player.speakTime = 0;
							  }
							  actionSelectedNumber = ACTION_IR_A_INDEX;
							  sprintf(actionSelected, "%s", level[0].GetActionName(actionSelectedNumber));
							  
							  walkingTowardsDoor = false;
	//                              player.walking = false;
	//                              player.destX = player.x;
	//                              player.destY = player.y;
						  } else
						  {
								strcpy(actionDebug, TEXT_DOOR_LOCKED);
								actionDebugLine2[0] = 0;
								player.speaking = true;
								player.speakTime = 0;
						  }

					  } // else action_abrir
					  
					  else if (actionSelectedNumber == ACTION_HABLAR_INDEX)
					  {
	//                       for (int i = 0; i<sizeof(plPhrases) / sizeof(plPhrases[0]); i++)
	//                       {
	//                           if (plPhrases[i].item == itemsInLevel[activeLevel][itemSelectedNumber] && !plPhrases[i].alreadySaid && !player.speaking)
	//                           {
	//                               strcpy(actionDebug, plPhrases[i].phrase);
	//                               actionDebugLine2[0] = 0;
	//                               player.speaking = true;
	//                               player.speakTime = 0;
	//                               if (!plPhrases[i].everlasting)
	//                                  plPhrases[i].alreadySaid = true;
	//                               i = sizeof(plPhrases) / sizeof(plPhrases[0]);
	//                               if(plPhrases[i].nextAnswer != 0)
	//                               {
	//                                   showActions = false;
	//                                   hideMouse();
									   animationOn = true;
									   animationSequenceIntCounter = -1;//plPhrases[i].nextAnswer;
									   animationSequence = ANIMATION_SEQUENCE_CHOOSE_PHRASE;//ANIMATION_SEQUENCE_DIALOG;
									   showActions = false;
									   showText = false;
									   hideMouse();
	//                               } // if(plPhrases[i].nextAnswer != 0)
	//                           } // for i...
	//                       }
						   
					  } // else action_hablar
					  
					  else if (actionSelectedNumber == ACTION_USAR_INDEX)
					  {
						  if (items[itemsInLevel[activeLevel][itemSelectedNumber]].responseYes[ACTION_USAR_INDEX][0] != 0)
						  {
								strcpy(actionDebug, items[itemsInLevel[activeLevel][itemSelectedNumber]].responseYes[ACTION_USAR_INDEX]);
								actionDebugLine2[0] = 0;
								player.speaking = true;
								player.speakTime = 0;
						  }
						  
						  // debug!!!
						  if(checkCanUse(player.itemsCollected[itemToUseNumber], itemsInLevel[activeLevel][itemSelectedNumber], gameActions, items))
						  {
								player.speaking = true;
								player.speakTime = 0;                                                         
						  } else
						  {
								   player.speaking = true;
								player.speakTime = 0;                                                         
							}

					  } // else aciton_abrir

					  else if (actionSelectedNumber == ACTION_CERRAR_INDEX)
					  {
						  items[itemsInLevel[activeLevel][itemSelectedNumber]].alive = false;
						  // debug!
						  items[itemsInLevel[activeLevel][0]].alive = true;
						  // \debug!
						  
						  if (items[itemsInLevel[activeLevel][itemSelectedNumber]].responseYes[ACTION_CERRAR_INDEX][0] != 0)
						  {
							strcpy(actionDebug, items[itemsInLevel[activeLevel][itemSelectedNumber]].responseYes[ACTION_CERRAR_INDEX]);
							actionDebugLine2[0] = 0;
							player.speaking = true;
							player.speakTime = 0;
						  } 
						  actionSelectedNumber = ACTION_IR_A_INDEX;
						  sprintf(actionSelected, "%s", level[0].GetActionName(actionSelectedNumber));
					  } // else aciton_agarrar

					  else if (actionSelectedNumber == ACTION_IR_A_INDEX && items[itemsInLevel[activeLevel][itemClickedNumber]].canEnter)  // use ACTION_ENTER plutot
					  {
						   walkingTowardsDoor = true;
					  } // else aciton_ir_a
					
					  else if (actionSelectedNumber == ACTION_AGARRAR_INDEX)
					  {
						if ((player.x - items[itemsInLevel[activeLevel][itemSelectedNumber]].x + items[itemsInLevel[activeLevel][itemSelectedNumber]].w > ALCANCE_X || player.x - items[itemsInLevel[activeLevel][itemSelectedNumber]].x + items[itemsInLevel[activeLevel][itemSelectedNumber]].w < 0) || 
							(player.y - items[itemsInLevel[activeLevel][itemSelectedNumber]].y + items[itemsInLevel[activeLevel][itemSelectedNumber]].h > ALCANCE_Y || player.y - items[itemsInLevel[activeLevel][itemSelectedNumber]].y + items[itemsInLevel[activeLevel][itemSelectedNumber]].h < 0))
						{
						  sprintf(actionDebug, TEXT_CANT_REACH);
						  actionDebugLine2[0] = 0;
						  player.speaking = true;
						  player.speakTime = 0;
						  player.walking = false;
						  player.destX = player.x;
						  player.destY = player.y;                      
						} 
						else
						{
						  items[itemsInLevel[activeLevel][itemSelectedNumber]].alive = false;
						  player.AddItemCollected(itemsInLevel[activeLevel][itemSelectedNumber]);
						  player.itemsSoFar++;
						  
						  if (items[itemsInLevel[activeLevel][itemSelectedNumber]].responseYes[ACTION_AGARRAR_INDEX][0] != 0)
						  {
							strcpy(actionDebug, items[itemsInLevel[activeLevel][itemSelectedNumber]].responseYes[ACTION_AGARRAR_INDEX]);
							actionDebugLine2[0] = 0;
							player.speaking = true;
							player.speakTime = 0;
						  }
						} // endif too far to reach
					  } // else aciton_open
					} // if itemselected[0] != 0
					else
					{
						actionSelectedNumber = ACTION_IR_A_INDEX;
						sprintf(actionSelected, "%s", level[0].GetActionName(actionSelectedNumber));
					}
				  }
				  else // \if mousePointer.y < 290
				  {
					if (itemCollectedSelected != -1)
					{
					  itemToUseNumber = itemCollectedSelected;
					  bitmapMousePointer = changeMousePointer(spriteCollected, player.itemsCollected, itemCollectedSelected);
					  actionSelectedNumber = ACTION_USAR_INDEX;
					  sprintf(actionSelected, TEXT_ACTION_ITEM_WITH, level[0].GetActionName(actionSelectedNumber), items[player.itemsCollected[itemCollectedSelected]].name);
					  usingItem = true;
					}
					else
					{
						if (showActions)
						{
							actionSelectedNumber = level[0].CheckCollisionActions((int)mousePointer.x, (int)mousePointer.y);
							if (actionSelectedNumber != -1)  // an action has been clicked
							{
							  usingItem = false;
							  itemToUseNumber = -1;
							  sprintf(actionSelected, "%s", level[0].GetActionName(actionSelectedNumber));
							  bitmapMousePointer = createMouse(originalMouse);
							}
						}

						if (showPhrases)
						{
						  answerSelected = level[0].CheckCollisionPhrases((int)mousePointer.x, (int)mousePointer.y);
						  if (answerSelected != -1)
						  {
							   for (int i = 0; i<sizeof(plPhrases)/sizeof(plPhrases[0]); i++)
								   if (plPhrases[i].serial == answerSelected)
									  answerSelected = i;
							   strcpy(actionDebug, plPhrases[answerSelected].phrase);
							   actionDebugLine2[0] = 0;
							   player.speaking = true;
							   player.speakTime = 0;
							   if (!plPhrases[answerSelected].everlasting)
								 plPhrases[answerSelected].alreadySaid = true;
		//                               i = sizeof(plPhrases) / sizeof(plPhrases[0]);
							   if(plPhrases[answerSelected].nextAnswer != 0)
							   {
								   animationOn = true;
								   animationSequenceIntCounter = plPhrases[answerSelected].nextAnswer;
								   animationSequence = ANIMATION_SEQUENCE_DIALOG;
								   showActions = false;
								   showText = false;
								   hideMouse();
								   level[0].createPhrases(plPhrases, itemsInLevel[activeLevel][itemSelectedNumber], sizeof(plPhrases)/sizeof(plPhrases[0]));
							   } else if(!player.itemSpeaking)
							   {
								 animationOn = false;
								 showActions = true; 
								 showText = true;
								 showPhrases = false;
							   }
						  }
						}
					}                
					level[0].CheckCollisionArrows((int)mousePointer.x, (int)mousePointer.y, gameTimer, player.itemsSoFar);
				  }
				}
				if (mouse_b & RIGHT_BUTTON)  // debug: right button changes level/room
				{

	//              if (!levelChanged)
	//              {
	//                level[0].LoadMap("level2.txt");
	//                levelChanged = true;
	//                activeLevel = 1;
	//              }
	//              else
	//              {
	//                level[0].LoadMap("level0.txt");
	//                levelChanged = false;
	//                activeLevel = 0;
	//              }
				}
				
				if (walkingTowardsDoor)
				{
	//                            sprintf(actionDebug, "diffX:%.1f, diffY:%.1f, playerY %.1f, itemY: %f itemh%d", player.x - items[itemsInLevel[activeLevel][itemClickedNumber]].x, player.y - items[itemsInLevel[activeLevel][itemClickedNumber]].y, player.y, items[itemsInLevel[activeLevel][itemClickedNumber]].y, items[itemsInLevel[activeLevel][itemClickedNumber]].h);
	//                            actionDebugLine2[0] = 0;
	//                            player.speaking = true;
	//                            player.speakTime = 0;
								
	//                 if ((!((player.x - items[itemsInLevel[activeLevel][itemClickedNumber]].x + items[itemsInLevel[activeLevel][itemClickedNumber]].w > 80 || player.x - items[itemsInLevel[activeLevel][itemClickedNumber]].x + items[itemsInLevel[activeLevel][itemClickedNumber]].w < 0) || 
	//                  (player.y - items[itemsInLevel[activeLevel][itemClickedNumber]].y + items[itemsInLevel[activeLevel][itemClickedNumber]].h > 80 || player.y - items[itemsInLevel[activeLevel][itemClickedNumber]].y + items[itemsInLevel[activeLevel][itemClickedNumber]].h < 0)))&&items[itemsInLevel[activeLevel][itemClickedNumber]].canEnter)

					 if (
						
						(
						(player.x > items[itemsInLevel[activeLevel][itemClickedNumber]].x) && (player.x - items[itemsInLevel[activeLevel][itemClickedNumber]].x < items[itemsInLevel[activeLevel][itemClickedNumber]].w) ||
						(player.x < items[itemsInLevel[activeLevel][itemClickedNumber]].x) && (player.x - items[itemsInLevel[activeLevel][itemClickedNumber]].x > -items[itemsInLevel[activeLevel][itemClickedNumber]].w)
						)
						&&
						( 
						(player.y > items[itemsInLevel[activeLevel][itemClickedNumber]].y) && (player.y - items[itemsInLevel[activeLevel][itemClickedNumber]].y < items[itemsInLevel[activeLevel][itemClickedNumber]].h) ||
						(player.y < items[itemsInLevel[activeLevel][itemClickedNumber]].y) && (player.y - items[itemsInLevel[activeLevel][itemClickedNumber]].y > -items[itemsInLevel[activeLevel][itemClickedNumber]].h)
						)
						&& 
						items[itemsInLevel[activeLevel][itemClickedNumber]].canEnter
						)
					 {
						  for (int i=0; i<sizeof(exits) / sizeof(exits[0]); i++)
							if(exits[i][0] == itemsInLevel[activeLevel][itemClickedNumber])
							{  
							   if (exits[i][1] == 1)
								  level[0].LoadMap("level2.txt", exits[i][1]);
							   if (exits[i][1] == 0)
								  level[0].LoadMap("level0.txt", exits[i][1]);
															  
							  if (exits[i][1] == 1 && !gameActions[GAME_ACT_PASSED_LEVEL_2])
							  {
								strcpy(actionDebug, "Tiens ! Il fait nuit... Bizarre...");
								actionDebugLine2[0] = 0;
								player.speaking = true;
								player.speakTime = 0;
								gameActions[GAME_ACT_PASSED_LEVEL_2] = true;
							  }
							  if (exits[i][1] == 1)
							  {
								  player.y = 195;
								  player.destY = 195;
								  player.x = 590;
								  player.destX = 590;
								  levelChanged = true;
								  activeLevel = exits[i][1];
								  walkingTowardsDoor = false;
							  }
							  if (exits[i][1] == 0)
							  {
								  player.y = 100;
								  player.destY = 100;
								  player.x = 140;
								  player.destX = 140;
								  activeLevel = exits[i][1];
								  walkingTowardsDoor = false;
							  }
							}
							else if (itemsInLevel[activeLevel][itemClickedNumber] == FINAL_DOOR)
							{
							  level[0].setBackground(blackBg);
							  walkingTowardsDoor = false;
							  player.walking = false;
							  player.destX = player.x;
							  player.destY = player.y;
							  player.alive = false;
							  showActions = false;
							  showText = false;
							  hideMouse();
							  animationOn = true;
							  animationSequence = ANIMATION_SEQUENCE_END;
							}                      
						  
						  if (items[itemsInLevel[activeLevel][itemClickedNumber]].responseYes[ACTION_ABRIR_INDEX][0] != 0)
						  {
							strcpy(actionDebug, items[itemsInLevel[activeLevel][itemClickedNumber]].responseYes[ACTION_ABRIR_INDEX]);
							actionDebugLine2[0] = 0;
							player.speaking = true;
							player.speakTime = 0;
						  }
						  actionSelectedNumber = ACTION_IR_A_INDEX;
						  sprintf(actionSelected, "%s", level[0].GetActionName(actionSelectedNumber));
					 } // endif too far
				} // else walkingTowardsDoor
				
		  }//if(!animationOn)
		  else
		  {
			if ( key[KEY_ESC] )      //quit game with F4 or ESC
			{
			  gameTimer = 0;
			  animationOn = false;
			  animationSequenceIntCounter = 0;
			  animationSequence = -1;
			  player.speaking = false;
			  showMouse();
			  showActions = true;
			  showText = true;
			  player.alive = true;

			}

			switch(animationSequence)
			{
			  case ANIMATION_SEQUENCE_END:
				if (!player.speaking && animationSequenceIntCounter == 0)
				{
				   strcpy(actionDebug, TEXT_FIN_JEU_1);
				   actionDebugLine2[0] = 0;
				   player.speaking = true;
				   player.speakTime = 0;
				   animationSequenceIntCounter++;
				}
				if (!player.speaking && animationSequenceIntCounter == 1)
				{
				   strcpy(actionDebug, TEXT_FIN_JEU_2_1);
				   strcpy(actionDebugLine2, TEXT_FIN_JEU_2_2);
				   player.speaking = true;
				   player.speakTime = 0;
				   animationSequenceIntCounter++;
				}
			  
				if (animationSequenceIntCounter == 2 && !player.speaking)
				{
				  animationSequenceIntCounter = 0;
				  done = true;
				}
				break;
				
			  case ANIMATION_SEQUENCE_START:
				if (!player.speaking && animationSequenceIntCounter == 0)
				{
				   strcpy(actionDebug, "Quelque part sur une ile, où il fait très chaud");
				   strcpy(actionDebugLine2, "(presque si chaud qu'à l'enfer),");
				   player.speaking = true;
				   player.speakTime = 0;
				   animationSequenceIntCounter++;
				}
				if (!player.speaking && animationSequenceIntCounter == 1)
				{
				   strcpy(actionDebug, "un malheureux naufragé essaye de retourner chez lui,");
				   strcpy(actionDebugLine2, "d'echapper aux sauvages...");
				   player.speaking = true;
				   player.speakTime = 0;
				   animationSequenceIntCounter++;
				}
							   
				if (!player.speaking && animationSequenceIntCounter == 2)
				{
				   strcpy(actionDebug, "Pourras-tu le sauver ?");
				   actionDebugLine2[0] = 0;
				   player.speaking = true;
				   player.speakTime = 0;
				   animationSequenceIntCounter++;
				}      
				if (animationSequenceIntCounter == 3 && !player.speaking)
				{
				  animationOn = false;
				  animationSequenceIntCounter = 0;
				  player.speaking = false;
				  showMouse();
				  player.alive = true;
				  showActions = true;
				  showText = true;
				}
				break;             

			  case ANIMATION_SEQUENCE_DIALOG:
				if (!player.speaking && animationSequenceIntCounter != 0)
				{
				   actionDebug[0] = 0;
				   actionDebugLine2[0] = 0;
				   for (int ii=0; ii<sizeof(itPhrases)/sizeof(itPhrases[0]); ii++)
				   {
					   if (itPhrases[ii].serial == animationSequenceIntCounter)
						  strcpy(actionDebug, itPhrases[ii].phrase);
					   if (itPhrases[ii].continueDialog)   
						  animationSequence = ANIMATION_SEQUENCE_CHOOSE_PHRASE;
				   }

				   player.itemSpeaking = true;
				   player.itemSpeakTime = 0;
				   animationSequenceIntCounter = 0;
				}
				if (!player.itemSpeaking && animationSequenceIntCounter == 0)
				{
				   actionDebug[0] = 0;
				   actionDebugLine2[0] = 0;                                                    
				   player.itemSpeaking = false;
				   animationOn = false;
				   showActions = true;
				   showText = true;
				   showMouse();
				}
				break;    
					 
			  case ANIMATION_SEQUENCE_CHOOSE_PHRASE:
				   if (!player.itemSpeaking)        // wait till it finishes speaking
				   {
					 level[0].createPhrases(plPhrases, itemsInLevel[activeLevel][itemSelectedNumber], sizeof(plPhrases)/sizeof(plPhrases[0]));
					 showPhrases = true;
					 animationOn = false;
					 showMouse();
				   }
				   break;
			  }// switch
		    } // else (if (animationOn))

            if(player.destX < player.x-10)
            {
                if ( CheckCollision( &player, LEFT, &level[0] ) == false )
                {
                  player.Move(LEFT);
                  collisions = 0;
                }
                else
                  collisions++;
            }
            else if(player.destX > player.x +10)
            {
                if ( CheckCollision( &player, RIGHT, &level[0] ) == false )
                {
                  player.Move(RIGHT);
                  collisions = 0;
                }
                else
                  collisions++;
            }
            
            if(player.destY < player.y - 5)
            {
                if ( CheckCollision( &player, UP, &level[0] ) == false )
                {
                  player.Move(UP);
                  collisions = 0;
                }
                else
                  collisions++;
            }
            else if(player.destY > player.y + 5)
            {
                if ( CheckCollision( &player, DOWN, &level[0] ) == false )
                {
                  player.Move(DOWN);
                  collisions = 0;
                }
                else
                  collisions++;
            }
            
            if((player.x > player.destX - 15 && player.x < player.destX + 15) && (player.y > player.destY - 15 && player.y < player.destY + 15))
            {
              player.walking = false;
            } 
            
            if (collisions > 4)
            {
                player.walking = false;
                player.destX = player.x;
                player.destY = player.y;
                collisions = 0;
            }
      
            player.Update();  // update sprite's frames, etc.

            itemCollectedSelected = level[0].CheckCollisionCollected((int)mousePointer.x, (int)mousePointer.y, player.itemsSoFar);
                            
            //items
            for (int i = 0; i<NUMBER_ITEMS; i++)
            {
                if (checkCollisionItem((int)mousePointer.x, (int)mousePointer.y, mousePointer.w, mousePointer.h,  &items[itemsInLevel[activeLevel][i]]) == true && items[itemsInLevel[activeLevel][i]].alive == true)
                {
                  sprintf(itemSelected, "%s", items[itemsInLevel[activeLevel][i]].name);
                  itemSelectedNumber = i;
                  i = NUMBER_ITEMS;
                }
                else if (itemCollectedSelected != -1)
                {
                  sprintf(itemSelected, "%s", items[player.itemsCollected[itemCollectedSelected]].name);
                  itemSelectedNumber = i;
                  i = NUMBER_ITEMS;
                }
                else
                  sprintf(itemSelected, "");
                  
                if (itemsInLevel[activeLevel][i] == -1)  // all items read?
                  i = NUMBER_ITEMS;
            }

            speedCounter --;
            gameTimer++;
            if(level[0].scrollableScreen)
              Update(&offsetX, &offsetY, &player);
              
        } // while(speedCounter...)
        
        text_mode(-1);          //sets text background to be transparent
        vsync();        //to prevent screen blinking
        acquire_screen();

        scare_mouse();
        //Draw graphics
        level[0].DrawBottom(buffer, offsetX, offsetY);

        if (showActions)
          level[0].ShowActions(buffer);
          
        if (showPhrases)
          level[0].ShowPhrases(buffer);
        
        level[0].DrawCollected(buffer, spriteCollected, player.itemsCollected, player.itemsSoFar);
        
        for (int i=0; i<NUMBER_ITEMS; i++)
        {
            if (items[itemsInLevel[activeLevel][i]].alive && !items[itemsInLevel[activeLevel][i]].drawTop)
            {
              items[itemsInLevel[activeLevel][i]].DrawAnim(buffer, bitmapItems[itemsInLevel[activeLevel][i]], offsetX, offsetY, items[itemsInLevel[activeLevel][i]].w, items[itemsInLevel[activeLevel][i]].h, items[itemsInLevel[activeLevel][i]].frames);
              items[itemsInLevel[activeLevel][i]].Update();
            }
            if (itemsInLevel[activeLevel][i]==-1)
              i=NUMBER_ITEMS;
        }

        if (player.alive)
          player.Draw(buffer, spritePlayer, offsetX, offsetY);
          
        if (player.speaking && player.alive)
          player.DrawSpeaking(buffer, spritePlayerSpeaking, offsetX, offsetY);

        for (int i=0; i<NUMBER_ITEMS; i++)
        {
            if (items[itemsInLevel[activeLevel][i]].alive && items[itemsInLevel[activeLevel][i]].drawTop)
            {
              items[itemsInLevel[activeLevel][i]].DrawAnim(buffer, bitmapItems[itemsInLevel[activeLevel][i]], offsetX, offsetY, items[itemsInLevel[activeLevel][i]].w, items[itemsInLevel[activeLevel][i]].h, items[itemsInLevel[activeLevel][i]].frames);
              items[itemsInLevel[activeLevel][i]].Update();
            }
            if (itemsInLevel[activeLevel][i]==-1)
              i=NUMBER_ITEMS;
        }
        sprintf(textShown, "%s %s", actionSelected, itemSelected);
        if (showText)
          level[0].DrawItems(buffer, textLives, textShown);
        
        if (player.speaking)
        {
          level[0].WriteLine(buffer, actionDebug);
          if (actionDebugLine2[0] != 0)
          {
            level[0].WriteLine(buffer, actionDebugLine2, true);
            if (player.speakTime++ > SPEAK_TIME_MAX*2)
            {
              player.speaking = false;
              actionDebugLine2[0] = 0;              // so that I don't need to set
                                                    // to 0 each time
            }
          } 
          else                                      // means speaking only 1 line
          {
              if (player.speakTime++ > SPEAK_TIME_MAX)
                player.speaking = false;
          }
        } else if (player.itemSpeaking)
        {
               
          level[0].WriteLine(buffer, actionDebug, 255, 0, 0);
          if (actionDebugLine2[0] != 0)
          {
            level[0].WriteLine(buffer, actionDebugLine2, true, 255, 0, 0);
            if (player.itemSpeakTime++ > SPEAK_TIME_MAX*2)
            {
              player.itemSpeaking = false;
              actionDebugLine2[0] = 0;              // so that I don't need to set
                                                    // to 0 each time
            }
          } 
          else                                      // means speaking only 1 line
          {
              if (player.itemSpeakTime++ > SPEAK_TIME_MAX)
                player.itemSpeaking = false;
          }             
        }


        if(mouseShowing)
          mousePointer.DrawAnim(buffer, bitmapMousePointer, offsetX, offsetY, mousePointer.w, mousePointer.h, mousePointer.frames);

        blit(buffer, screen, 0, 0, 0, 0, SCR_W, SCR_H);
        clear_bitmap(buffer);       //clear off the buffer after we draw it to the screen
        release_screen();
    }//while ( !done )
    unload_datafile(my_datafile);
    return 0;
}
END_OF_MAIN();

void initAllegro(bool fullscreen)
{
    allegro_init();
    install_keyboard();
    install_timer();
    install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, 0);
    install_joystick(JOY_TYPE_AUTODETECT);
    install_mouse();
    LOCK_VARIABLE(speedCounter);
    LOCK_FUNCTION(incrementCounter);
    install_int_ex(incrementCounter, BPS_TO_TIMER(90));
    set_color_depth(16);
set_uformat(U_ASCII);
    if ( fullscreen )
        set_gfx_mode(GFX_AUTODETECT, SCR_W, SCR_H, 0, 0);
    else
        set_gfx_mode(GFX_AUTODETECT_WINDOWED, SCR_W, SCR_H, 0, 0);
}

void incrementCounter()
{
    speedCounter++;
}

bool CheckCollision(const PlayerClass *player, int direction, const LevelClass *level)
{
    int tx, ty;
    if ( direction == LEFT )
    {
        tx = ((int)player->x - (int)player->speed) / TILESIZE;
        ty = (int)player->y/TILESIZE;
    }
    else if ( direction == RIGHT )
    {
        tx = ((int)player->x + (int)player->speed + player->w/3) / TILESIZE;
        ty = (int)player->y/TILESIZE;
    }
    else if ( direction == DOWN)
    {
        tx = (int)player->x/TILESIZE;
        ty = ((int)player->y +((int)player->h/3)) / TILESIZE;
    }
    else if ( direction == UP)
    {
        tx = (int)player->x/TILESIZE;
        ty = ((int)player->y -1)/TILESIZE;
    }

    if ( direction == DOWN )
    {
        if ( !level->tile[0][tx][ty].walkable || !level->tile[0][tx][ty+1].walkable )
        {
            return true;     
        }
    }
    else if ( direction == LEFT )
    {
        if ( !level->tile[0][tx][ty].walkable || !level->tile[0][tx][ty+1].walkable )
        {
            return true;
        }
    }
    else if ( direction == RIGHT )
    {
        if ( !level->tile[0][tx+1][ty].walkable || !level->tile[0][tx+1][ty+1].walkable )
        {
            return true;
        }
    }
    else if ( direction == UP )
    {
        if ( !level->tile[0][tx][ty].walkable )
        {
            return true;
        }
    }

    return false;       
}

bool checkCollisionItem(const PlayerClass *player, const ItemsClass *item)
{
  if ((item->x > player->x) && (item->x < player->x + player->w) && (item->y + item->h > player->y) && (item->y < player->y + player->h) || (player->x > item->x) && (player->x < item->x + item->w) && (player->y + player->h > item->y) && (player->y < item->y + item->h))
    return true;
  else
    return false;
}

bool checkCollisionItem(int mouseX, int mouseY, int mouseW, int mouseH, const ItemsClass *item)
{
  if ((item->x > mouseX) && (item->x < mouseX + mouseW) && (item->y + item->h > mouseY) && (item->y < mouseY + mouseH) || (mouseX > item->x) && (mouseX < item->x + item->w) && (mouseY + mouseW > item->y) && (mouseY < item->y + item->h))
    return true;
  else
    return false;
}

void Update(float *offsetX, float *offsetY, PlayerClass *player)
{
    if ( player->x >= 0.525 * SCR_W )
        *offsetX = player->x - 0.5*player->w - 0.5*SCR_W;
    if ( player->y >= 0.525 * SCR_H )
        *offsetY = player->y - 0.5*player->h - 0.5*SCR_H;
}

void startMusic(void)
{
   play_midi(the_music, TRUE);
}

void stopMusic(void)
{
   destroy_midi(the_music);
}

BITMAP *createMouse(BITMAP *originalMouse)
{
    mousePointer.w = 15;
    mousePointer.h = 25;
    mousePointer.frames = 1;
    return originalMouse;
}

BITMAP *changeMousePointer(BITMAP* pointer, int* itemsCollected, int item)
{
    mousePointer.w = 32;      
    mousePointer.h = 32;
    mouseOriginal = false;
    return create_sub_bitmap(pointer, 32*itemsCollected[item], 0, 32, 32);
}

bool checkCanUse(int item1, int onItem2, bool *gameActions, ItemsClass *item)
{
    bool ans = false;
    for (int i=0; i<sizeof(itemsUsable) / sizeof(itemsUsable[0]); i++)
      if(itemsUsable[i][0] == item1)
        if(itemsUsable[i][1] == onItem2)
          ans = true;
    if (!ans)
    {
      sprintf(actionDebug, TEXT_CANT_USE_WITH_THAT);
      actionDebugLine2[0] = 0;      
    }
    if (ans)
    {
      if (item1 == 9 && onItem2 == 0)
      {
        if (gameActions[GAME_ACT_DOOR1_UNLOCKED] == true)
        {
          strcpy(actionDebug, TEXT_ALREADY_UNLOCKED);
          actionDebugLine2[0] = 0;
        }
        else
        {
          gameActions[GAME_ACT_DOOR1_UNLOCKED] = true;
          strcpy(actionDebug, TEXT_KEY_WORKED);
          actionDebugLine2[0] = 0;
        }
      }
      else if (item1 == 7 && onItem2 == 5)
      {
        strcpy(actionDebug, TEXT_BROKEN_BRANCH1);
        strcpy(actionDebugLine2, TEXT_BROKEN_BRANCH2);
        item[onItem2].alive = false;
        item[9].y = 150;
      }
    } // \if(ans)
    return ans;
}

void hideMouse(void)
{
     mouseShowing = false;
}

void showMouse(void)
{
     mouseShowing = true;
}

