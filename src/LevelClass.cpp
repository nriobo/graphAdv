//LevelClass.cpp
#include "LevelClass.h"
#include "datafile.h"

void LevelClass::DrawBottom(BITMAP *buffer, float offsetX, float offsetY)
{
    //Background
    masked_blit(background, buffer, 0, 0, 0, 0, 640, 480);
    // debug: block around actions to check collision area
	//  for (int i = 0; i<NUMBER_ACTIONS; i++)
	//    rect(buffer, Actions[i].x - offsetX, Actions[i].y - offsetY, Actions[i].x+Actions[i].w - offsetX, Actions[i].y+Actions[i].h - offsetY, makecol(255, 0, 0));

}

void LevelClass::DrawItems(BITMAP *buffer, char *textLives, char *textCoins)
{
    textout_ex( buffer, theFontSmaller, textCoins, centerText(textCoins), 285, makecol( 0, 0, 0 ), -1 );
}

int LevelClass::centerText(char *text)
{
    return (SCR_W-text_length(theFontSmaller,text))/2;
}

int LevelClass::centerAction(char *text, int column)
{
    return (100*(column-1))+(100-text_length(theFontSmaller,text))/2;
}

void LevelClass::WriteLine(BITMAP *buffer, char *text)
{
     // white background for the letters
     textout_ex( buffer, theFontSmaller, text, centerText(text)-1, 30, makecol( 255, 255, 255 ), -1 );
     textout_ex( buffer, theFontSmaller, text, centerText(text)+1, 30, makecol( 255, 255, 255 ), -1 );
     textout_ex( buffer, theFontSmaller, text, centerText(text), 30+1, makecol( 255, 255, 255 ), -1 );
     textout_ex( buffer, theFontSmaller, text, centerText(text), 30-1, makecol( 255, 255, 255 ), -1 );

     textout_ex( buffer, theFontSmaller, text, centerText(text), 30, makecol( 0, 0, 0 ), -1 );
}   
void LevelClass::WriteLine(BITMAP *buffer, char *text, bool line2)
{
     // white background for the letters
     textout_ex( buffer, theFontSmaller, text, centerText(text)-1, 50, makecol( 255, 255, 255 ), -1 );
     textout_ex( buffer, theFontSmaller, text, centerText(text)+1, 50, makecol( 255, 255, 255 ), -1 );
     textout_ex( buffer, theFontSmaller, text, centerText(text), 50+1, makecol( 255, 255, 255 ), -1 );
     textout_ex( buffer, theFontSmaller, text, centerText(text), 50-1, makecol( 255, 255, 255 ), -1 );

     textout_ex( buffer, theFontSmaller, text, centerText(text), 50, makecol( 0, 0, 0 ), -1 );
}   

void LevelClass::WriteLine(BITMAP *buffer, char *text, int r, int g, int b)
{
     // white background for the letters
     textout_ex( buffer, theFontSmaller, text, centerText(text)-1, 30, makecol( r, g, b ), -1 );
     textout_ex( buffer, theFontSmaller, text, centerText(text)+1, 30, makecol( r, g, b ), -1 );
     textout_ex( buffer, theFontSmaller, text, centerText(text), 30+1, makecol( r, g, b ), -1 );
     textout_ex( buffer, theFontSmaller, text, centerText(text), 30-1, makecol( r, g, b ), -1 );

     textout_ex( buffer, theFontSmaller, text, centerText(text), 30, makecol( 0, 0, 0 ), -1 );
}   
void LevelClass::WriteLine(BITMAP *buffer, char *text, bool line2, int r, int g, int b)
{
     // white background for the letters
     textout_ex( buffer, theFontSmaller, text, centerText(text)-1, 50, makecol( r, g, b ), -1 );
     textout_ex( buffer, theFontSmaller, text, centerText(text)+1, 50, makecol( r, g, b ), -1 );
     textout_ex( buffer, theFontSmaller, text, centerText(text), 50+1, makecol( r, g, b ), -1 );
     textout_ex( buffer, theFontSmaller, text, centerText(text), 50-1, makecol( r, g, b ), -1 );

     textout_ex( buffer, theFontSmaller, text, centerText(text), 50, makecol( 0, 0, 0 ), -1 );
}   

void LevelClass::createActions(void)
{
	gameTimerTemp = 0;
	DATAFILE *my_datafile = load_datafile("datafile.dat");

    //Check that the datafile was created correctly
    if(my_datafile == NULL)
    {
       set_gfx_mode(GFX_TEXT,0,0,0,0);
       allegro_message("Could not load datafile!");
       exit(EXIT_FAILURE);
    }

	spriteArrowU = (BITMAP *)my_datafile[ARROW_UP_BMP].dat;
	spriteArrowD = (BITMAP *)my_datafile[ARROW_DN_BMP].dat;

	unload_datafile(my_datafile);
	PALETTE palette;

	char *names[] = { "COMIC" , NULL};
	char *names2[] = { "COMIC_SM", NULL};

	theFont = load_bitmap_font("comic.pcx", NULL, NULL);
	theFontSmaller = load_font("comicSm.pcx", NULL, NULL);

	strcpy(Actions[0].texto, TEXT_ACTION_GOTO);
	Actions[0].x = centerAction(Actions[0].texto, 1);
	Actions[0].y = 300;
	Actions[0].w=text_length(theFont,Actions[0].texto);
	Actions[0].h=text_height(theFont);

	Actions[0].binary = ACTION_IR_A;

	strcpy(Actions[1].texto, TEXT_ACTION_OPEN);
	Actions[1].x = centerAction(Actions[1].texto, 2);
	Actions[1].y = 300;
	Actions[1].w=text_length(theFont,Actions[1].texto);
	Actions[1].h=text_height(theFont);
	Actions[1].binary = ACTION_ABRIR;

	strcpy(Actions[2].texto, TEXT_ACTION_PICKUP);
	Actions[2].x = centerAction(Actions[2].texto, 1);
	Actions[2].y = 330;
	Actions[2].w=text_length(theFont,Actions[2].texto);
	Actions[2].h=text_height(theFont);
	Actions[2].binary = ACTION_AGARRAR;

	strcpy(Actions[3].texto, TEXT_ACTION_CLOSE);
	Actions[3].x = centerAction(Actions[3].texto, 2);
	Actions[3].y = 330;
	Actions[3].w=text_length(theFont,Actions[3].texto);
	Actions[3].h=text_height(theFont);
	Actions[3].binary = ACTION_CERRAR;

	strcpy(Actions[4].texto, TEXT_ACTION_USE);
	Actions[4].x = centerAction(Actions[4].texto, 1);
	Actions[4].y = 360;
	Actions[4].w=text_length(theFont,Actions[4].texto);
	Actions[4].h=text_height(theFont);
	Actions[4].binary = ACTION_USAR;

	strcpy(Actions[5].texto, TEXT_ACTION_TALKTO);
	Actions[5].x = centerAction(Actions[5].texto, 2);
	Actions[5].y = 360;
	Actions[5].w=text_length(theFont,Actions[5].texto);
	Actions[5].h=text_height(theFont);
	Actions[5].binary = ACTION_HABLAR;
}

void LevelClass::ShowActions(BITMAP *buffer)
{
     for (int i=0; i<NUMBER_ACTIONS; i++)
     {
       textout_ex( buffer, theFont, Actions[i].texto, Actions[i].x, Actions[i].y, makecol( 0, 255, 255 ), -1 );         
     }
}   
    
void LevelClass::LoadMap(string filename, int level)
{
     for (int j=0; j<TILEY; j++)
        for(int i=0; i<TILEX; i++)
          tile[0][i][j].walkable = true;
                
    ifstream infile;
    infile.open(filename.c_str());
    string temp;
    infile>>temp;       //x
    infile>>temp;       //160
    infile>>temp;       //y
    infile>>temp;       //60
    infile>>temp;       //bgimage
    infile>>temp;       //background
    infile>>temp;       //backgroundName
//    background = load_bitmap(temp.c_str(), NULL);

    DATAFILE *my_bg = load_datafile("bgdatafile.dat");

    //Check that the datafile was created correctly
    if(my_bg == NULL)
    {
       set_gfx_mode(GFX_TEXT,0,0,0,0);
       allegro_message("Could not load datafile!");
       exit(EXIT_FAILURE);
    }
    background = (BITMAP *)my_bg[level].dat;
    
    //bottom layer
    for (int j=0; j<TILEY; j++)
    {
        for(int i=0; i<TILEX; i++)
        {
            infile>>temp;
            tile[0][i][j].cx = atoi ( temp.c_str() ) * 32;
            tile[0][i][j].x = i * 32;  // every tile is 32x32 pixels
            tile[0][i][j].y = j * 32;
            
            if ( tile[0][i][j].cx == 0 )
                tile[0][i][j].walkable = true;
            else
                tile[0][i][j].walkable = false;
        }
    }
}

int LevelClass::CheckCollisionActions(int mouseX, int mouseY)
{
  int ret = -1;
  for (int i = 0; i<NUMBER_ACTIONS; i++)
  {
    if (mouseX > Actions[i].x && mouseX < Actions[i].x + Actions[i].w && mouseY > Actions[i].y && mouseY < Actions[i].y + Actions[i].h)
      ret = i;
  }  
  return ret;
}

int LevelClass::CheckCollisionPhrases(int mouseX, int mouseY)
{
  int ret = -1;
  for (int i = 0; i<4; i++)
  {
    if ((mouseX > PhrasesShown[i].x && mouseX < PhrasesShown[i].x + PhrasesShown[i].w && mouseY > PhrasesShown[i].y && mouseY < PhrasesShown[i].y + PhrasesShown[i].h) && PhrasesShown[i].texto[0]!=0)
      ret = PhrasesShown[i].serial;
  }  
  return ret;
}


int LevelClass::CheckCollisionCollected(int mouseX, int mouseY, int itemsSoFar)
{
  int ret = -1, fil = 0;
  // selected items      
  for (int i = itemsCollectedStartPosition; i<itemsSoFar; i++)
  {
    if (i == itemsCollectedStartPosition + 3)
      fil++;
      
    if (mouseX > 500 + 40*(i-itemsCollectedStartPosition-3*fil) && mouseX < 532 + 40*(i-itemsCollectedStartPosition-3*fil) && mouseY > 310 + 40*fil && mouseY < 340 + 40*fil)
      ret = i;
    
    if (i==5)
      i=itemsSoFar;
  }  

  return ret;
}

int LevelClass::CheckCollisionArrows(int mouseX, int mouseY, int gameTimer, int itemsSoFar)
{
  int ret = -1;
  if (gameTimer - gameTimerTemp > 30)
  {
      // arrow UP
      if (mouseX > 450 && mouseX < 482 && mouseY > 300 && mouseY < 342)
      {
          if (itemsCollectedStartPosition >= 6)
          {
              itemsCollectedStartPosition -= 6;
              gameTimerTemp = gameTimer;
          }
          
      }
      // ARROW DOWN
      if (mouseX > 450 && mouseX < 482 && mouseY > 350 && mouseY < 392)
      {
          if (itemsSoFar >= itemsCollectedStartPosition + 6)
          {
              itemsCollectedStartPosition += 6;
              gameTimerTemp = gameTimer;
          }
      }
  }
}

char* LevelClass::GetActionName(int actionNumber)
{
  return Actions[actionNumber].texto;     
}

int LevelClass::GetActionBinary(int actionNumber)
{
  return Actions[actionNumber].binary;
}

void LevelClass::DrawCollected(BITMAP *buffer, BITMAP *sprite, int *itemsCollected, int itemsSoFar)
{
  int l = 0, c = 0;
  for (int i=itemsCollectedStartPosition; i<itemsSoFar; i++)
  {
    if (i == itemsCollectedStartPosition + 3)
    {
      l = 1;
      c = 0;
    }
    if (i == itemsCollectedStartPosition + 6)
      i = itemsSoFar;
    
    if (itemsCollected[i] != -1)         // still not in the end
      masked_blit(sprite, buffer, (int)itemsCollected[i]*32, 0, 500+40*c, 310+l*40, 32, 32);
    else
      i=itemsSoFar;
    c++;
  }
  if (itemsSoFar > 6)
  {
     stretch_sprite(buffer, spriteArrowU, 450, 300, 32, 42);
     stretch_sprite(buffer, spriteArrowD, 450, 350, 32, 42);
  }
}

void LevelClass::setBackground(BITMAP *newBg)
{
     background = newBg;
}
        
void LevelClass::createPhrases(playerPhrases *Phrase, int theItem, int length)
{
       for (int d = 0; d<4; d++)    
           PhrasesShown[d].texto[0] = 0;

       char *names[] = { "COMIC" , NULL};
       char *names2[] = { "COMIC_SM", NULL};

       theFont = load_bitmap_font("comic.pcx", NULL, NULL);
       theFontSmaller = load_font("comicSm.pcx", NULL, NULL);
  int posI = 0;
  for (int i = 0; i<length; i++)
  {
      if (Phrase[i].item == theItem && !Phrase[i].alreadySaid)
      {
          strcpy(PhrasesShown[posI].texto, Phrase[i].phrase);
          PhrasesShown[posI].x = 10;
          PhrasesShown[posI].y = posYphrase1 + 20*posI;
          PhrasesShown[posI].w=text_length(theFontSmaller,PhrasesShown[posI].texto);
          PhrasesShown[posI].h=text_height(theFontSmaller);
          PhrasesShown[posI].serial = Phrase[i].serial;
          posI++;
      }
  }
}

void LevelClass::ShowPhrases(BITMAP *buffer)
{
     for (int i=0; i<4; i++)
     {
       textout_ex( buffer, theFontSmaller, PhrasesShown[i].texto, PhrasesShown[i].x, PhrasesShown[i].y, makecol( 0, 255, 255 ), -1 );         
     }
}   
    
