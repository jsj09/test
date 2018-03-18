#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <graphics.h>
#include <conio.h>
#include <iostream>
#include <iomanip>


void textcolor(int color_number)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),color_number);
}

void gotoxy(int x, int y)
{
    COORD pos = {x,y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}


#define  red          12    //  high red
#define  gray          7   //  light  gray
#define  yellow       14   //  yellow
#define  cyan         11   //  high cyan
#define  white        15   //  high cyan

#define  left_color   12   //  high red
#define  right_color  14   //  yellow
#define  up_color     10   //  high green
#define  down_color   11   //  high cyan


unsigned char t_ar[22][12];
unsigned char t_ar_save[22][12];

//unsigned char t_ar[22][12];
//unsigned char t_ar_save[22][12];
         


unsigned char shape[7][4][4][4]= { { { {0,0,1,0}, 
                                       {0,0,1,0}, 
                                       {0,0,1,0}, 
                                       {0,0,1,0} },   
                                     { {0,0,0,0}, 
                                       {0,0,0,0}, 
                                       {1,1,1,1}, 
                                       {0,0,0,0} },   
                                     { {0,0,1,0}, 
                                       {0,0,1,0}, 
                                       {0,0,1,0}, 
                                       {0,0,1,0} }, 
                                     { {0,0,0,0}, 
                                       {0,0,0,0}, 
                                       {1,1,1,1}, 
                                       {0,0,0,0} } },  //  l  모양  
                                    
                                   { { {0,0,0,0}, 
                                       {0,1,0,0}, 
                                       {0,1,1,1}, 
                                       {0,0,0,0} }, 
                                     { {0,0,1,0}, 
                                       {0,0,1,0}, 
                                       {0,1,1,0}, 
                                       {0,0,0,0} },  
                                     { {0,0,0,0}, 
                                       {1,1,1,0},
                                       {0,0,1,0}, 
                                       {0,0,0,0} },  
                                     { {0,0,0,0}, 
                                       {0,1,1,0}, 
                                       {0,1,0,0},
                                       {0,1,0,0} } },  // ㄴ  모양 
                                  
                                   { { {0,0,0,0}, 
                                       {0,1,1,0}, 
                                       {0,1,1,0}, 
                                       {0,0,0,0} },    
                                     { {0,0,0,0}, 
                                       {0,1,1,0}, 
                                       {0,1,1,0}, 
                                       {0,0,0,0} }, 
                                     { {0,0,0,0}, 
                                       {0,1,1,0}, 
                                       {0,1,1,0}, 
                                       {0,0,0,0} }, 
                                     { {0,0,0,0}, 
                                       {0,1,1,0}, 
                                       {0,1,1,0}, 
                                       {0,0,0,0} } },  // ㅁ  모양 
                                    
                                  {  { {0,0,0,0}, 
                                       {0,0,1,0}, 
                                       {0,1,1,1}, 
                                       {0,0,0,0} }, 
                                     { {0,0,0,0}, 
                                       {0,0,1,0}, 
                                       {0,1,1,0}, 
                                       {0,0,1,0} }, 
                                     { {0,0,0,0}, 
                                       {0,0,0,0}, 
                                       {1,1,1,0}, 
                                       {0,1,0,0} },  
                                     { {0,0,0,0}, 
                                       {0,1,0,0}, 
                                       {0,1,1,0}, 
                                       {0,1,0,0} } },  //  ㅗ  모양 
                                       
                                   { { {0,0,0,0}, 
                                       {0,0,1,0}, 
                                       {1,1,1,0}, 
                                       {0,0,0,0} },  
                                     { {0,0,0,0}, 
                                       {0,1,1,0},
                                       {0,0,1,0}, 
                                       {0,0,1,0} },  
                                     { {0,0,0,0}, 
                                       {0,1,1,1}, 
                                       {0,1,0,0}, 
                                       {0,0,0,0} },  
                                     { {0,0,0,0}, 
                                       {0,1,0,0}, 
                                       {0,1,0,0},
                                       {0,1,1,0} } },  // ㄴ  모양 
                                       
                                   { { {0,0,0,0}, 
                                       {0,1,1,0}, 
                                       {0,0,1,1}, 
                                       {0,0,0,0} },  
                                     { {0,0,0,0}, 
                                       {0,0,1,0},
                                       {0,1,1,0}, 
                                       {0,1,0,0} },  
                                     { {0,0,0,0}, 
                                       {0,1,1,0}, 
                                       {0,0,1,1}, 
                                       {0,0,0,0} }, 
                                     { {0,0,0,0}, 
                                       {0,0,1,0},
                                       {0,1,1,0}, 
                                       {0,1,0,0} } },  // ㄹ  모양 
                                       
                                   { { {0,0,0,0}, 
                                       {0,1,1,0}, 
                                       {1,1,0,0}, 
                                       {0,0,0,0} },  
                                     { {0,0,0,0}, 
                                       {0,1,0,0},
                                       {0,1,1,0}, 
                                       {0,0,1,0} },  
                                     { {0,0,0,0}, 
                                       {0,1,1,0}, 
                                       {1,1,0,0}, 
                                       {0,0,0,0} },  
                                     { {0,0,0,0}, 
                                       {0,1,0,0},
                                       {0,1,1,0}, 
                                       {0,0,1,0} } } // ㄹ 반대 모양 
                                };
                                
unsigned char color_idx[7] = { 2,3,4,5,6,7,8 };

char su[10][8] = {    {0x00,0x38,0x44,0x4c,0x54,0x64,0x44,0x38},  //0
                      {0x00,0x10,0x30,0x50,0x10,0x10,0x10,0x7c},  //1
                      {0x00,0x38,0x44,0x04,0x08,0x10,0x20,0x7c},  //2
                      {0x00,0x38,0x44,0x04,0x18,0x04,0x44,0x38},  //3
                      {0x00,0x08,0x18,0x28,0x48,0x7c,0x08,0x08},  //4
                      {0x00,0x7c,0x40,0x78,0x04,0x04,0x44,0x38},  //5
                      {0x00,0x38,0x40,0x40,0x78,0x44,0x44,0x38},  //6
                      {0x00,0x7c,0x04,0x08,0x10,0x20,0x20,0x20},  //7
                      {0x00,0x38,0x44,0x44,0x38,0x44,0x44,0x38},  //8
                      {0x00,0x38,0x44,0x44,0x3c,0x04,0x44,0x38} };  //9
 
#define  mid_x   5
#define  mid_y   0
#define  mid_color   0
#define  cell_size  25
#define  block_size 17

#define  x_pos_offset 250
#define  y_pos_offset 23

#define  x_shape_offset 510
#define  y_shape_offset 17

#define  move_go     1
#define  move_stop   0


int   i =0, j=0, cnt = 0;
int   count = 0;
int   mid  = 0;
int   ch=0, s_idx = 0, save_idx = 0;
int   turn_idx =0, save_turn_idx = 0;;   
int   next_shape_idx =0;

int   shape_cnt = 0;

int   x, y, color;
int   s_x, s_y, s_color;

int   test_cnt = 0;
int   check_cnt = 0;
int   score_cnt = 0;
int   ch_flag  = 0;

unsigned int size;
char *buf;
char *buf1[7];
char *buf2;
char *buf3;
char *buf4;
char *buf5;


unsigned int y_pos=0;
unsigned int x_pos=0;

unsigned int sy_pos=0;
unsigned int sx_pos=0;

typedef struct  {
         int   x;
         int   y;
 } position;
       
position  save_pos[4];
position  before_pos[4];

void  t_ar_init ( void ) ;
void  print_all ( void );
void  print_shape ( int , int );

void  print_recover ( int , int  );
void  print_overlap ( int , int , int , int );
int   overlap_check ( int,  int , int , int );
void  overlap_save ( int , int, int, int  );
void  tetris_clear ( void );

void  t_ar_init ( void ) ;
void  g_tetris_init ( void );
void  g_print_all ( void );
void  g_print_move ( int, int, int );
void  g_print_recover ( int, int );
void  g_screen_rebuild ( void );
void  g_print_shape ( int  , int  , int , unsigned char  );

void  g_score_print ( int );


time_t now=0, before=0;


int main(int argc, char *argv[]) {
   
   x = 1;
   y = 0;
   s_x = 0;
   s_y = 0;
   s_idx = 0;
   save_idx = 0;
   turn_idx = 0;
   save_turn_idx = 0;
   
   
   g_tetris_init ( );
    //배경출력     
   g_print_all ();
   
   t_ar_init ();
   
   print_all ();
   
  
   
   // shape지정  
   srand((unsigned int) time(NULL));
   s_idx = rand()%7;
   print_shape (s_idx, turn_idx);
   
   print_overlap (x,y,s_idx, turn_idx );
  
   
   // next shape  set 
   srand((unsigned int) time(NULL));
   next_shape_idx = (rand()+1)%7;
   print_shape (next_shape_idx, 0);
   
   
  while (1) {
    
    count++;
    if(count==40)
    {
        
       count=0; 
       
        s_x =  x;
        s_y =  y;
        
        y++;   
       
         now = time(NULL);
         gotoxy ( 25, 16);
         printf(" before:%ld  now:%ld   ", before, now );
         before = now;
       
       if  ( y > 19 ) { 
           x =  mid_x;
           y =  mid_y; 
           
           // shape change
           s_idx = next_shape_idx;
           srand((unsigned int) time(NULL));
           next_shape_idx = rand()%7;
           print_shape (next_shape_idx, 0);
       } 
         
       if ( overlap_check ( x,  y, s_idx, turn_idx ) ==  move_go )  {
                 
                    print_recover (s_x,s_y);  
                    print_overlap (x,y,s_idx, turn_idx);  
               } else  {
                    overlap_save (s_x, s_y, s_idx, turn_idx);
                    print_recover (s_x,s_y);
                    
                    //  terminate   
                    if  ( y == 1 )  {
                        gotoxy ( 1, 1);
                        printf("                ");
                        gotoxy ( 1, 1);
                        printf("****************");
                        gotoxy ( 1, 2); 
                        printf("                ");
                        gotoxy ( 1, 2);
                        printf("* game over!!! *");
                        gotoxy ( 1, 3); 
                        printf("                ");
                        gotoxy ( 1, 3); 
                        printf("*score: %5d  *", score_cnt * 10 ); 
                        gotoxy ( 1, 4);
                        printf("                ");
                        gotoxy ( 1, 4);
                        printf("****************");
                        break;
                    }
                    // shape change
                    turn_idx = 0;
                    s_idx = next_shape_idx;
                    srand((unsigned int) time(NULL));
                    next_shape_idx = rand()%7;
                    print_shape (next_shape_idx, turn_idx);
                    
                    
                    
                    //  first line  start
                    x =  mid_x;
                    y=   mid_y;    
                    print_overlap (x,y,s_idx, turn_idx ); 
                    tetris_clear();
               }  
     
       textcolor(white);          
       gotoxy(25,20);
       printf(" score : %d ", score_cnt * 10 ); 
       
            
     } 
                 
              
         if ( kbhit())  {    
            
            ch_flag  =  1;
            
            s_x =  x;
            s_y =  y;
            
    		ch=getch();
    		
           
                if(ch == 0x4b) {   // left             
                      x =  x -1;   
                     //if ( x <= -1 )  x = 0;  //  shape empty  consider 
                                  
                }   
                else if(ch == 0x4d) {  //  right                  
                      x =  x +1;
                     
                }   
                else if(ch == 0x50) {  //  down                              
                       y =  y + 1; 
                                     
                }  
                else if(ch == 0x48) {  //  shape change
                       save_turn_idx  =  turn_idx;
                       turn_idx++;
                       if ( turn_idx > 3 ) turn_idx =  0;  
                       
                       if ( overlap_check ( x,  y, s_idx, turn_idx ) == move_stop ) { 
                                  turn_idx = save_turn_idx;
                                  continue;
                                  }
                       else ; // print_shape (s_idx, turn_idx);                           
                } 
                else  if ( ch == 0x20 )  {
                     
                      while ( 1 ) {
                            
                            y++;
                            if ( overlap_check ( x,  y, s_idx, turn_idx ) == move_stop ) {
                                      y --;
                                      break; // repeat  down  until  move stop 
                            }
                            else {
                              print_recover (s_x,s_y);                                 
                              print_overlap (x,y,s_idx, turn_idx ); 
                              s_x =  x;
                              s_y =  y;
                              Sleep(20);
                              continue;
                            }
                     }
                  
            }  //  if  0x20
            

       if ( overlap_check ( x,  y, s_idx, turn_idx ) ==  move_go )  {
            print_recover (s_x,s_y);   
                                         
            print_overlap (x,y,s_idx, turn_idx );  
       } else   {
            x =   s_x;
            y =   s_y;    
       }  
       
       ch_flag  =  0;   
          
    }  // kbhit 
            
     
   
   Sleep(25);
   
  }  // for  while 
  
  
  system("PAUSE");	
  return 0;
  
}

void  t_ar_init ( void ) {
      
       for(i=0;i<22;i++){
          for ( j=0;j<12;j++)  {
              
              if ( ( i == 0 ) | ( i ==  21 ) )  t_ar [i][j] = 1;
              else  if ( ( j == 0 ) | ( j ==  11 ) )  t_ar [i][j] = 1;  
              else t_ar [i][j] = 0;        

          }                   
       };    

}      

void  print_all ( void ) {
      
       system("cls");
  
        
       for(i=0;i<22;i++){
         for(j=0;j<12;j++) {
             	if(  t_ar[i][j] >= 1 ) {
                     
                        if (  t_ar [i][j] == 1 ) textcolor(white );
                        else  textcolor(t_ar [i][j]);
                   	   printf("*");
                    }
        	    else {  textcolor(white);  
              		printf("-");
                     }  
                }
         printf("\n");            
       }
      
}

void  print_shape ( int s_idx, int t_idx )  {
 
        
       for(i=0;i<4;i++){
         for(j=0;j<4;j++) {
                gotoxy(j+20,i);
             	if(  shape [s_idx][t_idx][i][j] == 1 ) {
                       textcolor( color_idx[s_idx]); 
                   	   printf("*");
                    }
        	    else { textcolor( white );
              		    printf("-");
                     }
                 
                  g_print_shape ( j, i, s_idx, shape [s_idx][t_idx][i][j] );     
                     
                }
         printf("\n");            
       }
           
      
}

void  g_print_shape ( int  x, int  y , int idx, unsigned char data ) {
      
   unsigned int y_pos=0;
   unsigned int x_pos=0;
   int  r_idx = 0;
   
      
      x_pos  = (x +1 ) *  cell_size + x_shape_offset;
      y_pos  = (y + 1) *  cell_size + y_shape_offset;
      
      r_idx =  idx -2 ;  // clolr  code   2 ~ 8  covert  real  idx 
   
     if  ( data  ==  1 )   putimage(x_pos,y_pos,buf1[idx],0); 
     else putimage(x_pos,y_pos,buf3,0); 
     
   
    gotoxy(23,13);
    textcolor( white );
    printf("g shape idx:%4d  x:%4d  xpos:%4d y:%4d, ypos:%4d ",
                     idx,  x, x_pos, y, y_pos    ); 
    
}
 
int   overlap_check ( int  x,  int y, int idx , int turn ) {
    
     int t_i=0, t_j=0 ;
     
     check_cnt++;


       for(i=y;i<y+4;i++){
           t_j = 0;
         for(j=x;j<x+4;j++) {
 
             	if(  shape [idx][turn][t_i][t_j] == 1 )  {
                     
                    if  ( j < 0 )  continue;
                     
                    if ( t_ar [i][j]  >=  1 ) {
                                   textcolor( white );
                                   gotoxy(27,4);
                                   printf(" stop check%d   %4d, %4d  ",check_cnt, x, y);                 
                                   return  move_stop;     
                                }       
                 }   
           		
           t_j++;	
           
         }   // for  j
           t_i++;          
       }  // for i
    
    gotoxy(27,5);
    printf("   go check%d   %4d, %4d  ",check_cnt, x, y);   
   
    return   move_go;

}

void  print_overlap ( int x, int y, int idx, int turn ) {
       
      int t_i=0, t_j=0;
      
      t_i =  y;  
      t_j =  x;
     
      int pos_i = 0;
     
      for(i=0;i<4;i++){
          
         for(j=0;j<4;j++) {
                
                textcolor(red);                     
                gotoxy(t_j + j,t_i + i);
                
             	
                if(  shape [idx][turn][i][j] == 1 ) {
                       textcolor( white );
                       printf("*"); 
                       
                         //  data가 value == color  
                       if ( t_i + i > 0)  {
                           g_print_move ( t_j + j,t_i + i, color_idx[idx]);   //  data가 value == color  
                           save_pos[pos_i].x = t_j + j;
                           save_pos[pos_i].y = t_i + i;
                           pos_i =  pos_i + 1;
                           if ( pos_i >= 4 )  pos_i = 0;
                       }
                       
                       
                       gotoxy(35,1);
                       textcolor( white );
                       printf("overlap x: %4d,  y: %4d ", t_j + j,t_i + i );
                       
                     }
    		  //  else printf("-");
                 
           
         }   // for  j
                 
       }  // for i
           
      
}

void  print_recover ( int x, int y ) {
 
     test_cnt++;
     textcolor( white );
     gotoxy(35,2);
     printf("recover %4d  %4d, %4d ", test_cnt, x, y); 
     
      for ( int pos_i = 0;  pos_i < 4;  pos_i++ ) {
          
       
        
          if ( t_ar[ save_pos[pos_i].y ] [ save_pos[pos_i].x ] == 0 )  {
             g_print_recover (save_pos[pos_i].x, save_pos[pos_i].y);
             gotoxy(35,pos_i);  
             //printf("recover22 x%4d  y%4d \n", save_pos[pos_i].x, save_pos[pos_i].y );
         }
        
    } 

   
    return;

       for(i=y;i<y+4;i++){
         for(j=x;j<x+4;j++) {
                
                if  ( j < 0 )  continue;
                  
                gotoxy(j,i);
             	if (  t_ar [i][j] >= 1 ) {
                    
                    if (  t_ar [i][j] == 1 ) textcolor(white );
                    else  textcolor(t_ar [i][j]);
                    
                   	printf("*");
                   	
                   	if (  t_ar [i][j] >  1 ) g_print_move (j, i, t_ar [i][j] );
                   	
                
                }   	
        	    else if ( i < 21 ) { 
                        textcolor(white );
                     	printf("-");
                     	g_print_recover (j, i);
                      }
           		
          } // for  j   
                 
       }  //   for  i

    
}

void  overlap_save ( int x , int y, int idx , int turn ) {
      
       int t_i=0, t_j=0 ;
      
      for(i=y;i<y+4;i++){
           t_j = 0;
         for(j=x;j<x+4;j++) {
 
             	if(  shape [idx][turn][t_i][t_j] == 1 )  {
                     t_ar [i][j] = color_idx[idx];                   
                 }   
           		
           t_j++;	
           
         }   // for  j
           t_i++;          
       }  // for i
}

void  tetris_clear ( void ) {
      
      int   chk_cnt = 0;
      int   clear_cnt = 0;
      int  idx = 20;
      
      for(i=0;i<22;i++){
          for ( j=0;j<12;j++)  {
              
              if ( ( i == 0 ) | ( i ==  21 ) )  t_ar_save [i][j] = 1;
              else  if ( ( j == 0 ) | ( j ==  11 ) )  t_ar_save [i][j] = 1;  
              else t_ar_save [i][j] = 0;        

          }                   
       };   
      
       for(i=20;i>=1;i--){
                          
              chk_cnt = 0;
              
           for ( j=0;j<12;j++) {
               
               if  ( t_ar[i][j] != 0 ) chk_cnt++;
           }
           
           if ( chk_cnt < 12 ) {
             memcpy ( t_ar_save[idx], t_ar[i], 12 );
             idx--;
           }  else  clear_cnt ++;   
       }  //  for  i
       
       score_cnt =  score_cnt +  clear_cnt;
      
    
     textcolor( white );
     gotoxy(35,18);
     printf("clear  cnt %d  score : %d ", clear_cnt, score_cnt * 10 ); 
       
       // Clear screen
       if  ( clear_cnt > 0 )  {
           memcpy ( t_ar, t_ar_save, sizeof(t_ar) );
           Sleep(500);
           
           //  reset 
           print_all ();
           print_shape (next_shape_idx, 0);
           
           g_screen_rebuild();
           g_score_print ( score_cnt * 10 );
      }  
       
}

void  g_score_print ( int  score ) {

   int  k, j, i ;
   unsigned int   digit[4] ; 
      
   unsigned int  sy_offset=170;
   unsigned int  sx_offset= 90;
   
   unsigned int  x_pos=0;
   
   
   if ( score >= 10000 )  {
        digit[3] = 9; digit[2] = 9; digit[1] = 9; digit[0] = 9;
   } else {
       digit[3] =  score % 10000;  digit[3] =  digit[3] / 1000;
       digit[2] =  score %  1000;  digit[2] =  digit[2] /  100;
       digit[1] =  score %   100;  digit[1] =  digit[1] /   10;
       digit[0] =  score %   10;
   }
   
   
  
  //  score  clear 
   putimage(50, 150, buf5,0); 
      
   for(k=3;k>=0; k--) {   
       
         
     for(j=0;j<8;j++){
        y_pos = sy_offset + ( j * 3 );
                      
    	for(i=0;i<8;i++){
              x_pos =  sx_offset + ( ( 3 - k ) * 14 ) + (i * 2); 
              
    		if( su[digit[k]][j] & (0x80 >> i) ) putimage(x_pos,y_pos,buf4,0); 
    		
    	} // for i  
    	
  	
    }  // for j
  }  // for k
}

void  g_tetris_init ( void ){
      
     
    initwindow( 742 , 552 , "nks tetris" ); 

    //배경그림 불러오기   화면에  display 
    readimagefile(
        "nks_back1.jpg",    	
    0,0,742,552
    ); 
    size = imagesize(0,0,742,552);  
    buf = (char *)malloc(size);
    getimage(0, 0, 742,552,buf);   //  buff  memory로  가져오기 

    //빈 블럭 불러오기 
    readimagefile(
    "nks_nullblock.jpg",    	
    0,0,block_size,block_size
    ); 
    size = imagesize(0, 0, block_size, block_size);
    buf2 = (char *)malloc(size);
    getimage(0, 0, block_size, block_size,buf2);  
    
    //빈shape  블럭 불러오기 
    readimagefile(
    "shape_nullblock.jpg",    	
    0,0,block_size,block_size
    ); 
    size = imagesize(0, 0, block_size, block_size);
    buf3 = (char *)malloc(size);
    getimage(0, 0, block_size, block_size,buf3);
 
 
    //블럭그림 불러오기   
    readimagefile(
    "nks_block0.jpg",    	
    0,0,block_size,block_size
    ); 
    size = imagesize(0, 0, block_size, block_size);
    buf1[0] = (char *)malloc(size);
    getimage(0, 0, block_size, block_size,buf1[0]);
    
    readimagefile(
    "nks_block1.jpg",    	
    0,0,block_size,block_size
    ); 
    size = imagesize(0, 0, block_size, block_size);
    buf1[1] = (char *)malloc(size);
    getimage(0, 0, block_size, block_size,buf1[1]);

     readimagefile(
    "nks_block2.jpg",    	
    0,0,block_size,block_size
    ); 
    size = imagesize(0, 0, block_size,block_size);
    buf1[2] = (char *)malloc(size);
    getimage(0, 0, block_size,block_size,buf1[2]);
    
    readimagefile(
    "nks_block3.jpg",    	
    0,0,block_size,block_size
    ); 
    size = imagesize(0, 0, block_size,block_size);
    buf1[3] = (char *)malloc(size);
    getimage(0, 0, block_size,block_size,buf1[3]);
    
      readimagefile(
    "nks_block4.jpg",    	
    0,0,block_size,block_size
    ); 
    size = imagesize(0, 0, block_size,block_size);
    buf1[4] = (char *)malloc(size);
    getimage(0, 0, block_size,block_size,buf1[4]);
    
    readimagefile(
    "nks_block5.jpg",    	
    0,0,block_size,block_size
    ); 
    size = imagesize(0, 0, block_size,block_size);
    buf1[5] = (char *)malloc(size);
    getimage(0, 0, block_size,block_size,buf1[5]);
    
    readimagefile(
    "nks_block6.jpg",    	
    0,0,block_size,block_size
    ); 
    size = imagesize(0, 0, block_size,block_size);
    buf1[6] = (char *)malloc(size);
    getimage(0, 0, block_size,block_size,buf1[6]);
    
    // score dot block
    readimagefile(
    "score_dot.jpg",    	
    0,0,1,1
    ); 
    size = imagesize(0, 0, 1,1);
    buf4 = (char *)malloc(size);
    getimage(0, 0, 1,1,buf4);
    
     // score clear block
    readimagefile(
    "score_clear.jpg",    	
    0,0,160,50
    ); 
    size = imagesize(0, 0, 160,50);
    buf5 = (char *)malloc(size);
    getimage(0, 0, 160,50,buf5);

      
}

void  g_print_all ( void ){
      
     putimage(0,0,buf,0);  
}

void  g_screen_rebuild ( void ) {
      
      for(i=1;i<21;i++){
         for(j=1;j<11;j++) {
                           
             	if(  t_ar[i][j] > 1 )             	
                   	g_print_move (j, i, t_ar [i][j]);
        	    else          	
              		g_print_recover(j, i);
                }
                    
     }
      
}

void  g_print_move ( int  x, int  y , int idx) {
      
   unsigned int y_pos=0;
   unsigned int x_pos=0;
   int  r_idx = 0;
   
      
      x_pos  = (x -1) *  cell_size + x_pos_offset;
      y_pos  = (y -1) *  cell_size + y_pos_offset;
      
      r_idx =  idx -2 ;  // clolr  code   2 ~ 8  covert  real  idx 
      
     
    gotoxy(20,10);
    textcolor( white );
    printf("gmoveidx:%4d x:%4d xpos:%4d y:%4d, ypos:%4d  ",
                     idx,  x, x_pos, y, y_pos); 
    
   
      putimage(x_pos,y_pos,buf1[r_idx],0); 
}

void  g_print_recover ( int  x, int  y ) {
   unsigned int y_pos=0;
   unsigned int x_pos=0;
     
      x_pos  = (x - 1) *  cell_size + x_pos_offset;
      y_pos  = (y - 1) *  cell_size + y_pos_offset;
      
   
    gotoxy(20,11);
    
     printf("g recover     x:%4d  xpos:%4d  y:%4d, ypos:%4d    ", 
                           x, x_pos, y, y_pos); 
  
      putimage(x_pos,y_pos,buf2,0);

}

void  g_number_print ( int data ) {
      int  i, j, k;
      
    for(k=0;k<10; k++)  {         
          for(j=0;j<8;j++){
                       
    	     for(i=0;i<8;i++){
                              
    	     	if( su[k][j] & (0x80 >> i) )  printf("*");
    	 	    else printf(" ");
    	 	    
    	     }  // for i
    	 
          }  // for  j
          
     }  // for  k
     
         
}

