#include "raylib.h"

#define number_of_buttons 3
#define number_of_settings 5

typedef enum GameScreen { Menu_Screen = 0, Settings_Screen, Start_Screen} GameScreen;

int main(){

    bool CloseGame{false};

    int window_width {1920};
    int window_height {1080};

    int mouse_touch {-1};
    int mouse_touch_settings {-1};
    int current_process {-1};
    int current_process_settings {-1};

    Vector2 position[number_of_buttons] = {0};
    for(int i = 0; i < number_of_buttons; i++){
    position[i].x = 1750;
    position[i].y = 750 + 120*i; 
    }
    
    static const char *text[] = {"Start", "Settings", "Exit"};
    static const char *Setting_text[] = {"Graphics", "Audio", "Video", "Controls"};

    Rectangle buttons[number_of_buttons] = {0};
    Rectangle buttons_in_settings[number_of_settings] = {0};
    for(int i = 0; i < number_of_buttons; i++){       
    //buttons[i] = (Rectangle){1720, (float)((window_height/1.5) + (float)((window_height/9)*i)), (float)(window_width/6.4), (float)(window_width/19.2)};
    buttons[i] = (Rectangle){1720, (float)(720 + 120*i), 300, 100};
    }

    for(int i = 0; i < number_of_settings - 1; i++){
    buttons_in_settings[i] = (Rectangle){480, (float)(280 + 70*i), 288, 50};    
    }
    buttons_in_settings[4] = (Rectangle){1340, 180, 100, 100};

    InitWindow(window_width, window_height, "Galore");
    SetTargetFPS(60);
    ToggleFullscreen();

    GameScreen CurrentScreen = Menu_Screen;

//Logo
    Image Logo = LoadImage("Icon.png");
    SetWindowIcon(Logo);

    Texture2D Cross = LoadTexture("Cross.png");
    Texture2D CrossAnim = LoadTexture("CrossAnim.png");
    Texture2D background = LoadTexture("MainMenu.png");
    Texture2D Settings = LoadTexture("Settings.png");

    Vector2 settings_text_position;
    settings_text_position.x = 550;
    settings_text_position.y = 215;
    Vector2 setting_buttons_position[number_of_settings - 1];
    for(int i = 0; i < number_of_settings - 1; i++){
    setting_buttons_position[i].x = 500;
    setting_buttons_position[i].y = (float)(300 + 70*i);
    }

   //Rectangle switch_audio = (Rectangle){};

    Font myfont = LoadFont("AllenoireFont.otf");

    InitAudioDevice();    
    Music music = LoadMusicStream("MainMenuSound.mp3");
    SetMusicVolume(music, 0.01); 
    PlayMusicStream(music);

    

while(CloseGame == false){

// Music
     UpdateMusicStream(music);
     if(!IsMusicStreamPlaying(music)){
        PlayMusicStream(music);
     }

// Mouse Logic    
switch (CurrentScreen)
{
case Menu_Screen:

for(int i = 0; i < number_of_buttons; i++){

        if(CheckCollisionPointRec(GetMousePosition(), buttons[i])){

          mouse_touch = i;

          if(IsMouseButtonReleased(MOUSE_BUTTON_LEFT)){
               
            current_process = i;

          }

          break;

        }else mouse_touch = -1; 
     }

     //Exit button
        if(current_process == 2){
        CloseGame = true; 
        }
//Settings
        if(current_process == 1){
        CurrentScreen = Settings_Screen;
        current_process = -1;
        }  
//Start
        if(current_process == 0){
        CurrentScreen = Start_Screen;
        }

    break;

case Settings_Screen:

for(int i = 0; i < number_of_settings; i++){ 

        if(CheckCollisionPointRec(GetMousePosition(), buttons_in_settings[i])){
        
          mouse_touch_settings = i;

          if(IsMouseButtonReleased(MOUSE_BUTTON_LEFT)){

            current_process_settings = i;
          
          }

          break;

        }else mouse_touch_settings = -1;

    }

    if(current_process_settings == 4){
    CurrentScreen = Menu_Screen;
    current_process_settings = -1;
    }

    break;    

case Start_Screen:
    break;    

default: break;
}





//Drawing
    BeginDrawing();

    ClearBackground(RAYWHITE);

    switch (CurrentScreen)
    {
    case Menu_Screen:

        DrawTexture(background, 0, 0, WHITE);

        for(int i = 0; i < number_of_buttons; i++){
        DrawRectangleRec(buttons[i], BLANK);
        DrawTextEx(myfont, text[i], position[i], (i == mouse_touch) ? 35 : 30, 0.0, PURPLE);
        }
        
        break;
    case Start_Screen:

        break;

    case Settings_Screen:

        DrawTexture(background, 0, 0, WHITE);
        DrawTexture(Settings, 480, 180, WHITE);
        DrawTextEx(myfont,"Settings", settings_text_position, 40, 0 , PURPLE);
       

        if(mouse_touch_settings == 4) DrawTexture(CrossAnim, 1363, 202, WHITE);
        else DrawTexture(Cross, 1365, 205, WHITE);
        

        for(int i = 0; i < number_of_settings; i++){
        DrawRectangleRec(buttons_in_settings[i], BLANK);
        }
        for(int i = 0; i < 4; i++){
        DrawTextEx(myfont, Setting_text[i], setting_buttons_position[i], (i == mouse_touch_settings) ? 35 : 30, 0, PURPLE);
        }

       // if(current_process_settings == 1){
            
        //}

        for(int i = 0; i < number_of_buttons; i++){ 
        DrawRectangleRec(buttons[i], BLANK);
        DrawTextEx(myfont, text[i], position[i], (i == mouse_touch) ? 35 : 30, 0.0, PURPLE);
        }

        break;
    
    default: break;
    }
    EndDrawing();
}

// Unload and Close
    UnloadTexture(background);
    UnloadTexture(Cross);
    UnloadTexture(Settings);
    UnloadMusicStream(music);

    CloseAudioDevice();      
    CloseWindow(); 
   

    return 0;
}