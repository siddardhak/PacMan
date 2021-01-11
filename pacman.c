#include <stdio.h> 
#include <conio.h> 
#include <windows.h>
#include <stdbool.h>

#define Height 35
#define Width 65
#define Ghosts 3

struct coordinates
{
   int x;
   int y;
};

struct PacMan {
   struct coordinates position;
   int vx;
   int vy;
   int lives;
   bool chasing;
   int food_collected;
};


struct Ghost {
   struct coordinates position;
   int vx;
   int vy;
   bool chasing;
};


struct Ghost allGhosts[Ghosts];

struct PacMan myPacMan = {
                           {
                              .x = 1,
                              .y = 1,                              
                           },
                           .vx = 0,
                           .vy = 0,
                           .lives = 3,
                           .chasing = false,
                           .food_collected = 0
                         };

char playfield[Height][Width] =
{
   { "############################################################" },
   { "#                                                          #" },
   { "# ################## #                                     #" },
   { "# ##               # #                                     #" },
   { "# ##          #### # #                                     #" },
   { "# ##          ## # # #                                     #" },
   { "# ##  ######  ## # # #                                     #" },
   { "# ##  #    #  ## # # #                                     #" },
   { "# ##  #### #  ## # # #                                     #" },
   { "# ##       #  ##   # #                                     #" },
   { "# ##########  ###### #                                     #" },
   { "#                    #                                     #" },
   { "######################                                     #" },
   { "#                                                          #" },
   { "#                                                          #" },
   { "#                                                          #" },
   { "#                                                          #" },
   { "#                                                          #" },
   { "#                                                          #" },
   { "#                                                          #" },
   { "#                                                          #" },
   { "#                                                          #" },
   { "#                                                          #" },
   { "#                                                          #" },
   { "#                                                          #" },
   { "#                                                          #" },
   { "#                                                          #" },
   { "#                                                          #" },
   { "#                                                          #" },
   { "############################################################" }
}; 


void initialize()
{
   
   for (int i = 0; i < Height; i++)
   {
      for (int j = 0; j < Width; j++)
      {
         if (playfield[i][j]==' ')
            playfield[i][j] = '.';
      }
   }

   for (int i = 0; i < Ghosts; i++)
   {
      allGhosts[i].vx = 0;
      allGhosts[i].vy = 0;
      allGhosts[i].chasing = true;

      int x,y;
      do
      {
         x = 1 + rand() % (Width-1);
         y = 1 + rand() % (Height-1);
     
      } while (playfield[y][x] != '.');
      allGhosts[i].position.x = x;
      allGhosts[i].position.y = y;
      playfield[y][x] = '\1';

   }
  

} 


void user_input()
{
   if (_kbhit())
   {
      char c1 = _getch();

      if (c1 == -32)
      {
         char c2 = _getch();

         myPacMan.vx = 0;
         myPacMan.vy = 0;

         switch (c2)
         {
            case 72: myPacMan.vy = -1; break; 
            case 80: myPacMan.vy = +1; break; 
            case 75: myPacMan.vx = -1; break; 
            case 77: myPacMan.vx = +1; break;             
         }
      }
      
      
   }
}


void move_figures()
{
   playfield[myPacMan.position.y][myPacMan.position.x] = ' ';

   int nx = myPacMan.vx + myPacMan.position.x;
   int ny = myPacMan.vy + myPacMan.position.y;

   if (playfield[ny][nx] == '#')
   {
      myPacMan.vx = 0;
      myPacMan.vy = 0;
   }

   myPacMan.position.x += myPacMan.vx;
   myPacMan.position.y += myPacMan.vy;

   if (playfield[ny][nx] == '.')
   {
      myPacMan.food_collected++;
   }

   playfield[myPacMan.position.y][myPacMan.position.x] = '\2';

   
}


int check_for_collisions()
{

   if (allGhosts->position.x == myPacMan.position.x && allGhosts->position.y == myPacMan.position.y){
      initialize();
      return false;
   }
   return true;

}


void show_playfield()
{
   for (int i = 0; i < Height; i++)
   {
      for (int j = 0; j < Width; j++)
      {
         printf("%c", playfield[i][j]);
      }
      printf("\n");
   }

   printf("Score: %d\n", myPacMan.food_collected);
}



void set_cursor_position(int x, int y)
{
   COORD coord = { x, y };
   SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

} 


void hidecursor()
{
   HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
   CONSOLE_CURSOR_INFO info;
   info.dwSize = 100;
   info.bVisible = FALSE;
   SetConsoleCursorInfo(consoleHandle, &info);
}


int main()
{
   
   system("cls");
   hidecursor();
   initialize();
   while (check_for_collisions())
   {
      user_input();
      move_figures();
      show_playfield();

      Sleep( 10000 / 30 );
      set_cursor_position(0,0);
   }

}