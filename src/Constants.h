#pragma once

#define LEFT          4
#define RIGHT        6
#define DOWN        2
#define UP              8
#define ENEMIES         8
#define NUMBER_ITEMS    50
#define NUMBER_ACTIONS 6
#define NUMBER_LEVELS 2
#define ITEMS_PER_LEVEL 50
#define MAX_ITEMS_COLLECTED 100

#define LEFT_BUTTON         1
#define RIGHT_BUTTON         2


#define ACTION_IR_A_INDEX 0
#define ACTION_ABRIR_INDEX 1
#define ACTION_AGARRAR_INDEX 2
#define ACTION_CERRAR_INDEX 3
#define ACTION_USAR_INDEX 4
#define ACTION_HABLAR_INDEX 5

#define ACTION_HABLAR         0x40; // 01000000b
#define ACTION_USAR           0x20; // 00100000b
#define ACTION_ENTER          0x10; // 00010000b
#define ACTION_IR_A           0x08; // 00001000b
#define ACTION_ABRIR          0x04; // 00000100b
#define ACTION_AGARRAR        0x02; // 00000010b
#define ACTION_CERRAR         0x01; // 00000001b

#define ARROW_UP              -2
#define ARROW_DN              -3


#define TILESIZE 32
//#define SPEAK_TIME_MAX 200
#define SPEAK_TIME_MAX 200

// test
#define ACTION_GOTO "Aller"

#define NUMBER_GAME_ACTIONS 3

// positions in the array
#define GAME_ACT_DOOR1_UNLOCKED 0
#define GAME_ACT_TRIED_TOTEM 1
#define GAME_ACT_PASSED_LEVEL_2 2

#define ANIMATION_SEQUENCE_END  1
#define ANIMATION_SEQUENCE_START 2
#define ANIMATION_SEQUENCE_DIALOG 3
#define ANIMATION_SEQUENCE_CHOOSE_PHRASE 4

#define FINAL_DOOR 9999

//#define TEXT_CANT_REACH	"No llego hastaaaaaa ahi!"
//#define TEXT_ACTION_ITEM_WITH "%s %s con"
//#define TEXT_CANT_USE_WITH_THAT "No se puede usar con eso."
//#define TEXT_ALREADY_UNLOCKED "Ya esta destrabada."
//#define TEXT_KEY_WORKED "Excelente! Que casualidad, era justo la llave..."
//#define TEXT_BROKEN_BRANCH1 "Rama rota. Me pregunto si no podria"
//#define TEXT_BROKEN_BRANCH2 "trabajar podando para el Gobierno de la Ciudad."
//#define TEXT_DOOR_LOCKED "Esta cerrada con llave."
//#define TEXT_CANT_DO_THAT "No puedo hacer eso."
//#define TEXT_CANT_GO_THERE "No puedo ir ahi."
//#define TEXT_ACTION_GOTO "Ir a"
//#define TEXT_ACTION_OPEN "Abrir"
//#define TEXT_ACTION_PICKUP "Agarrar"
//#define TEXT_ACTION_CLOSE "Cerrar"
//#define TEXT_ACTION_USE "Usar"
//#define TEXT_ACTION_TALKTO "Hablar a"
//#define TEXT_OBJ_KEY "Llave"
//#define TEXT_OBJ_CHGUN "Mitrailleuse"
//#define TEXT_OBJ_AXE "Hacha"
//#define TEXT_OBJ_BRANCH "Rama"
//#define TEXT_OBJ_TOTEM "Totem misterioso"
//#define TEXT_OBJ_WEALTH "Riqueza"
//#define TEXT_OBJ_SIGN "Cartel"
//#define TEXT_OBJ_BULL "Alfredito"
//#define TEXT_OBJ_DOOR "Puerta"
//#define TEXT_RESP_SURE "Si, claro..."
//#define TEXT_RESP_ALREADY_OPEN "Sos o te haces? No ves que ya esta abierta?..."
//#define TEXT_RESP_CANT_PICKUP_BULL "Si, queres tambien que me la lleve al hombro?"
//#define TEXT_RESP_CANT_TALKTO_BULL "Vos me estas tomando el pelo? Es un T-O-R-O."
//#define TEXT_RESP_SIGN_PICKEDUP "Listo! El cartel es mio."
//#define TEXT_RESP_RICH "Soy rico!!!"
//#define TEXT_RESP_WHATFOR "Para que?"
//#define TEXT_RESP_PICKUP_BRANCH "Mmmm, deberia poder romperla con algo..."
//#define TEXT_FIN_JEU_1 "FIN DU JEU"
//#define TEXT_FIN_JEU_2_1 "Graphisme : vole de Monkey Island (sauf taureau)."
//#define TEXT_FIN_JEU_2_2 "Musique : que dalle."


#define TEXT_CANT_REACH	"J'y arrive pas !"
#define TEXT_ACTION_ITEM_WITH "%s %s avec"
#define TEXT_CANT_USE_WITH_THAT "Je ne peux pas l'utiliser avec ça."
#define TEXT_ALREADY_UNLOCKED "Elle n'est plus fermee a clé."
#define TEXT_KEY_WORKED "Nickel ! Quelle chance, c'etait juste la clé dont j'avais besoin..."
#define TEXT_BROKEN_BRANCH1 "Branche cassee."
#define TEXT_BROKEN_BRANCH2 "Je suis tout-puissant !!!"
#define TEXT_DOOR_LOCKED "Elle est fermee a clé."
#define TEXT_CANT_DO_THAT "Je ne peux pas faire cela."
#define TEXT_CANT_GO_THERE "Je ne peux pas y aller."
#define TEXT_ACTION_GOTO "Aller a"
#define TEXT_ACTION_OPEN "Ouvrir"
#define TEXT_ACTION_PICKUP "Prendre"
#define TEXT_ACTION_CLOSE "Fermer"
#define TEXT_ACTION_USE "Utiliser"
#define TEXT_ACTION_TALKTO "Parler à"
#define TEXT_OBJ_KEY "Clé"
#define TEXT_OBJ_CHGUN "Mitrailleuse"
#define TEXT_OBJ_AXE "Hache"
#define TEXT_OBJ_BRANCH "Branche"
#define TEXT_OBJ_TOTEM "Totem mistérieux"
#define TEXT_OBJ_WEALTH "Richesse"
#define TEXT_OBJ_SIGN "Panneau"
#define TEXT_OBJ_BULL "Taureau"
#define TEXT_OBJ_DOOR "Porte"
#define TEXT_RESP_SURE "Oui, biensûr..."
#define TEXT_RESP_ALREADY_OPEN "Ca va pas ? Tu ne voies pas qu'elle est déjà ouverte ?..."
#define TEXT_RESP_CANT_PICKUP_BULL "Oui, tu veux aussi que je le porte sur mes épaules ?"
#define TEXT_RESP_CANT_TALKTO_BULL "Tu te fous de ma gueule ? C'est un T-A-U-R-E-A-U."
#define TEXT_RESP_SIGN_PICKEDUP "Voilà ! Il est à moi."
#define TEXT_RESP_RICH "Je suis riche !!!"
#define TEXT_RESP_WHATFOR "Pour quoi faire ?"
#define TEXT_RESP_PICKUP_BRANCH "Mmmm, je devrais pouvoir la casser avec quelque chose..."
#define TEXT_FIN_JEU_1 "FIN DU JEU"
#define TEXT_FIN_JEU_2_1 "Graphisme : volé de Monkey Island (sauf taureau)."
#define TEXT_FIN_JEU_2_2 "Musique : que dalle."
#define TEXT_RESP_TALK_FLAG "D'accord..."
