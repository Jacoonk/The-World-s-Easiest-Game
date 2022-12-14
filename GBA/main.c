#include "main.h"

#include <stdio.h>
#include <stdlib.h>

#include "gba.h"

// images
#include "images/title.h"
#include "images/boxer.h"
#include "images/win.h"


/* TODO: */
// Include any header files for title screen or exit
// screen images generated by nin10kit. Example for the provided garbage
// image:
// #include "images/garbage.h"

/* TODO: */
// Add any additional states you need for your app. You are not requried to use
// these specific provided states.
enum gba_state {
  START,
  INIT_PLAY,
  PLAY,
  WIN,
};

int buttonWasDown[10] = {0};
int buttonJusReleased[10] = {0};
int timer = 0;
int time;

int main(void) {
  /* TODO: */
  // Manipulate REG_DISPCNT here to set Mode 3. //
  REG_DISPCNT = MODE3 | BG2_ENABLE;

  // Save current and previous state of button input.
  u32 previousButtons = BUTTONS;
  u32 currentButtons = BUTTONS;

  // Load initial application state
  enum gba_state state = START;

  struct state cs;
  cs.currentState = 1;
  cs.nextState = 1;
  cs.mc.col = 120;
  cs.mc.row = 150; 

  cs.balls[0].row = 120;
  cs.balls[0].col = 220;
  cs.balls[0].dr = 3;
  cs.balls[0].cd = 2;
  cs.balls[0].color = GREEN;
  cs.balls[0].size = 4;
        
  cs.balls[1].row = 130;
  cs.balls[1].col = 220;
  cs.balls[1].dr = 1;
  cs.balls[1].cd = 2;
  cs.balls[1].color = BLUE;
  cs.balls[1].size = 4;
        
  cs.balls[2].row = 110;
  cs.balls[2].col = 220;
  cs.balls[2].dr = 2;
  cs.balls[2].cd = 3;
  cs.balls[2].color = WHITE;
  cs.balls[2].size = 4;
  int moveLeft = 1;
  //struct state ps;
  
  while (1) {
    //ps = cs;
    currentButtons = BUTTONS; // Load the current state of the buttons
    for (int i = 0; i < 10; i++) {
      buttonJusReleased[i] = KEY_DOWN(i, BUTTONS) == 0 && buttonWasDown[i];
      buttonWasDown[i] = KEY_DOWN(i, BUTTONS) != 0;
    }
    /* TODO: */
    // Manipulate the state machine below as needed //
    // NOTE: Call waitForVBlank() before you draw

    switch (state) {
      // Start = creation of title screen
      case START:
      timer = 0;
        waitForVBlank();
        drawFullScreenImageDMA(title);
        if (buttonJusReleased[BUTTON_START]) {
          state = INIT_PLAY;
        }
        break;
      
      case INIT_PLAY:
        cs.obstacle.row = 0;
        cs.obstacle.col = 80;
        cs.obstacle.length = 140;
        cs.obstacle.w = 5;
        cs.obstacle.color = CYAN;

        cs.mc.cd = 3;
        cs.mc.dr = 3;
        cs.mc.row = 150; 
        cs.mc.col = 120;
        cs.mc.size = 10;
      
        cs.balls[0].row = 120;
        cs.balls[0].col = 220;
        cs.balls[0].dr = 3;
        cs.balls[0].cd = 2;
        cs.balls[0].color = GREEN;
        cs.balls[0].size = 4;
        
        cs.balls[1].row = 130;
        cs.balls[1].col = 220;
        cs.balls[1].dr = 1;
        cs.balls[1].cd = 2;
        cs.balls[1].color = BLUE;
        cs.balls[1].size = 4;
        
        cs.balls[2].row = 110;
        cs.balls[2].col = 220;
        cs.balls[2].dr = 2;
        cs.balls[2].cd = 3;
        cs.balls[2].color = WHITE;
        cs.balls[2].size = 4;
        
        state = PLAY;
        break;
      case PLAY:
        waitForVBlank();
        fillScreenDMA(BLACK);
        drawRectDMA(cs.obstacle.row, cs.obstacle.col, cs.obstacle.w, cs.obstacle.length, cs.obstacle.color);
        if (vBlankCounter % 60 == 0) {
          timer ++;
        }
        char tens;
        char ones;
        tens = (timer / 10) % 10 + 48;
        ones = timer % 10 + 48;
        drawString(24,15, "Timer", WHITE);
        drawChar(24,50,tens,WHITE);
        drawChar(24,57,ones,WHITE);
        drawRectDMA(40,0,240,20,MAGENTA);
        int leftObs = 1;
        int rightObs = 1;
        int upObs = 1;
        if (!((cs.mc.col > cs.obstacle.col + cs.obstacle.w) || (cs.mc.col < cs.obstacle.col)) && !(cs.mc.row > cs.obstacle.row + cs.obstacle.length)) {
          leftObs = 0;
        }
        if (KEY_DOWN(BUTTON_LEFT, currentButtons) && !(cs.mc.col - 1 < 0) && leftObs) {
          cs.mc.col = cs.mc.col - 1;
        }

        if (!((cs.mc.col + 10 < cs.obstacle.col) || (cs.mc.col + 5 > cs.obstacle.col + cs.obstacle.w)) && !(cs.mc.row > cs.obstacle.row + cs.obstacle.length))  {
          rightObs = 0;
        }
        if (KEY_DOWN(BUTTON_RIGHT, currentButtons) && !(cs.mc.col + 11 > 240) && rightObs) {
          cs.mc.col++;
         }

        if (!((cs.mc.row > cs.obstacle.row + cs.obstacle.length) || (cs.mc.col + 9 < cs.obstacle.col || cs.mc.col + 1> cs.obstacle.col + cs.obstacle.w))) {
          upObs = 0;
        }
        if (KEY_DOWN(BUTTON_UP, currentButtons) && !(cs.mc.row - 10  < 0) && upObs) {
          cs.mc.row = cs.mc.row - 1;
        }
        if (KEY_DOWN(BUTTON_DOWN, currentButtons) && !(cs.mc.row + 10 > 160)) {
           cs.mc.row++;
        }
        
        drawImageDMA(cs.mc.row, cs.mc.col, cs.mc.size, cs.mc.size, boxer);
        

        if (cs.balls[0].col == cs.obstacle.col + cs.obstacle.w || cs.balls[0].col < 240) {
          
        }
        if (moveLeft) {
          cs.balls[0].col--;
          cs.balls[1].col--;
          cs.balls[2].col--;
        } 
        if (cs.balls[0].col == cs.obstacle.col + cs.obstacle.w) {
          moveLeft = 0;
        }
        if (!(moveLeft)) {
          cs.balls[0].col++;
          cs.balls[1].col++;
          cs.balls[2].col++;
        } 
        if (cs.balls[0].col + 5 == 240) {
          moveLeft = 1;
        }
        
        

        drawRectDMA(cs.balls[0].row, cs.balls[0].col, 4, 4, cs.balls[0].color);
        drawRectDMA(cs.balls[1].row, cs.balls[1].col, 4, 4, cs.balls[1].color);
        drawRectDMA(cs.balls[2].row, cs.balls[2].col, 4, 4, cs.balls[2].color);
        
        if (KEY_DOWN(BUTTON_SELECT, currentButtons)) {
           state = START;
        }
        if (cs.mc.row < 60) {
          time = timer;
          state = WIN;
        }
        if (timer == 40) {
          time = timer;
          state = WIN;
        }
        break;
      case WIN:
        waitForVBlank();
        drawFullScreenImageDMA(win);
        char tenrs;
        char oners;
        tenrs = (time / 10) % 10 + 48;
        oners = time % 10 + 48;
        drawString(130,15, "Seconds it took to win", BLACK);
        drawChar(130,150,tenrs,BLACK);
        drawChar(130,157,oners,BLACK);
        if (KEY_DOWN(BUTTON_SELECT, currentButtons)) {
           state = START;
        }
        break;
    }

    previousButtons = currentButtons; // Store the current state of the buttons
  }

  UNUSED(previousButtons); // You can remove this once previousButtons is used

  return 0;
}
