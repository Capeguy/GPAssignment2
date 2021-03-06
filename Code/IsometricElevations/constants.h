//  Module:             Games Programming
//  Assignment2:        Breakout Jack
//  Student Name 
//	Student Number:  
//						Ng Syn Kae				S10147534B
//						Lau Jun Hao Benjamin	S10138434C
//						Clarence Chew Kai Wei	S10147015J
//						Isaac Hong				S10148698F

#ifndef _CONSTANTS_H            // Prevent multiple definitions if this 
#define _CONSTANTS_H            // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include <windows.h>

//-----------------------------------------------
// Useful macros
//-----------------------------------------------
// Safely delete pointer referenced item
#define SAFE_DELETE(ptr)       { if (ptr) { delete (ptr); (ptr)=NULL; } }
// Safely release pointer referenced item
#define SAFE_RELEASE(ptr)      { if(ptr) { (ptr)->Release(); (ptr)=NULL; } }
// Safely delete pointer referenced array
#define SAFE_DELETE_ARRAY(ptr) { if(ptr) { delete [](ptr); (ptr)=NULL; } }
// Safely call onLostDevice
#define SAFE_ON_LOST_DEVICE(ptr)    { if(ptr) { ptr->onLostDevice(); } }
// Safely call onResetDevice
#define SAFE_ON_RESET_DEVICE(ptr)   { if(ptr) { ptr->onResetDevice(); } }
#define TRANSCOLOR  SETCOLOR_ARGB(255,255,0,255)  // transparent color (magenta)

//-----------------------------------------------
//                  Constants
//-----------------------------------------------

// window
const char CLASS_NAME[] = "BreakoutJack";
const char GAME_TITLE[] = "BreakoutJack Demo";
const bool FULLSCREEN = false;              // windowed or fullscreen
const UINT GAME_WIDTH = 1280;               // width of game in pixels
const UINT GAME_HEIGHT = 800;               // height of game in pixels

// game
const double PI = 3.14159265;
const float FRAME_RATE = 200.0f;                // the target frame rate (frames/sec)
const float MIN_FRAME_RATE = 10.0f;             // the minimum frame rate
const float MIN_FRAME_TIME = 1.0f / FRAME_RATE;   // minimum desired time for 1 frame
const float MAX_FRAME_TIME = 1.0f / MIN_FRAME_RATE; // maximum time used in calculations
const float FULL_HEALTH = 100;
const int	NUM_LEVEL = 3;
const int	NUM_ITEMS = 4;
const int	NUM_BUTTONS = 4;
// Graphic images
const char TEXTURE_IMAGE[] = "pictures\\tileset.png"; // game textures
const char TEXTURE_PLAYER[] = "pictures\\player.png";
const char TEXTURE_NPC[] = "pictures\\player.png";
const char TEXTURE_ITEM[] = "pictures\\item.png";
const char TEXTURE_GUNS[] = "pictures\\gun.png";
const char TEXTURE_HUD_GUN[] = "pictures\\hud_gun.png";
const char TEXTURE_BULLETS[] = "pictures\\bullet.png";
const char TEXTURE_HUD_HP[] = "pictures\\hud_healthbar.png";
const char TEXTURE_NPC_HEALTH[] = "pictures\\npc_health.png";
const char TEXTURE_NPC_HEALTH_BACK[] = "pictures\\npc_healthback.png";
const char TEXTURE_HUD_HP_RED[] = "pictures\\hud_healthbar_red.png";
const char TEXTURE_MENU[] = "pictures\\menu.png";
const char TEXTURE_BUTTONS[] = "pictures\\menu_buttons.png";
const char TEXTURE_PAUSE_MENU[] = "pictures\\pause_menu.png";
const char TEXTURE_PAUSE_MENU_BUTTONS[] = "pictures\\pause_menu_buttons.png";
const char TEXTURE_CREDITS[] = "pictures\\credit.png";
const char TEXTURE_INSTRUCTIONS[] = "pictures\\instructions.png";
const char TEXTURE_ICON[] = "pictures\\minimap_icon.png";
const char ITEM_ICON_TEXTURE[] = "pictures\\crate_ico.png";
const char TEXTURE_WINLOSE_BUTTON[] = "pictures\\win_lose_buttons.png";
const char TEXTURE_BOSS_GUN_SPRITE[] = "pictures\\boss gun sprite.png";
// Audio files required by audio.cpp
// WAVE_BANK must be location of .xwb file.
const char WAVE_BANK[] = "audio\\Win\\BreakoutJackWaveBank.xwb";
// SOUND_BANK must be location of .xsb file.
const char SOUND_BANK[] = "audio\\Win\\BreakoutJackSoundBank.xsb";
// Audio cues
const char BEEP2[] = "beep2";
const char PISTOL_SHOT[] = "pistol";
const char MACHINEGUN_SHOT[] = "machinegun";
const char SHOTGUN_SHOT[] = "shotgun";
const char RELOAD[] = "reload";
const char DIE[] = "die";
const char HURT[] = "hurt";
const char BK_MUSIC[] = "bkmusic";
const char BOSS_MUSIC[] = "bossmusic";
const char LOSE_MUSIC[] = "lose";
const char VICTORY_MUSIC[] = "victory";
// key mappings
// In this game simple constants are used for key mappings. If variables were used
// it would be possible to save and restore key mappings from a data file.
const UCHAR CONSOLE_KEY = VK_F1;    // `~ key for U.S.
const UCHAR ESC_KEY = VK_ESCAPE;   // escape key
const UCHAR ALT_KEY = VK_MENU;     // Alt key
const UCHAR ENTER_KEY = VK_RETURN;   // Enter key
const UCHAR PLAYER_LEFT = 'A';
const UCHAR PLAYER_RIGHT = 'D';
const UCHAR PLAYER_UP = 'W';
const UCHAR PLAYER_DOWN = 'S';
const UCHAR PLAYER_JUMP = VK_SPACE;
const UCHAR PLAYER_INVENT_CYCLE_LEFT = 'Q';
const UCHAR PLAYER_INVENT_CYCLE_RIGHT = 'E';
const UCHAR PAUSE = 'P';
#endif
