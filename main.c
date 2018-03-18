#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <string.h>

textcolor(int color_number)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),color_number);
}

gotoxy(int x, int y)
{
    COORD pos = {x,y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}


unsigned char t_ar[22][12];
unsigned char t_ar_save[22][12];
         

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

#define  white        15   

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


int main(int argc, char *argv[]) {

 
   x = 2;
   y = 0;
   s_x = 0;
   s_y = 0;
   s_idx = 0;
   save_idx = 0;
   turn_idx = 0;
   save_turn_idx = 0;

    //배경출력     
   t_ar_init ();
   print_all ();
   
   
   // shape지정  
   srand((unsigned int) time(NULL));
   s_idx = rand()%7;
   print_shape (s_idx, turn_idx);
   
   print_overlap (x,y,s_idx, turn_idx );
  
   
   // next shape
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
                    y =  mid_y;    
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
                     
                }   
                else if(ch == 0x4d) {  // right                 
                      x =  x +1;
                     
                }   
                else if(ch == 0x50) {  // down                             
                       y =  y + 1; 
                                     
                }  
                else if(ch == 0x48) {  // shape change
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
      
       system("cls"); //지우고 나서 프린 트 
  
        
       for(i=0;i<22;i++){
         for(j=0;j<12;j++) {
             	if(  t_ar[i][j] >= 1 ) {
                     
                        if (  t_ar [i][j] == 1 ) textcolor( white );
                        else  textcolor(t_ar [i][j]);
                   	   printf("*");
                    }
        	    else {  
					    textcolor( white );  
              		    printf(" ");
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
        	    else { 
					//	textcolor( white );
              		    printf(" ");
                     }
                }
         printf("\n");            
       }
           
}

 
int   overlap_check ( int  x,  int y, int idx , int turn ) {
    
     int t_i=0, t_j=0 ;
     
     check_cnt++;


       for(i=y;i<y+4;i++){
           t_j = 0;
         for(j=x;j<x+4;j++) {
 
             	if(  shape [idx][turn][t_i][t_j] == 1 )  {
                     
                    if  ( j < 0 )  continue;
                     
                    if ( t_ar [i][j]  >=  1 )    return  move_stop;     
      
                 }   
           		
           t_j++;	
           
         }   // for  j
           t_i++;          
       }  // for i
   
    return   move_go;

}

void  print_overlap ( int x, int y, int idx, int turn ) {
       
      int t_i=0, t_j=0;
      
      t_i =  y;  
      t_j =  x;
     
      int pos_i = 0;
     
      for(i=0;i<4;i++){
          
         for(j=0;j<4;j++) {
                           
                gotoxy(t_j + j,t_i + i);
                
             	
                if(  shape [idx][turn][i][j] == 1 ) {
                       textcolor( color_idx[idx] );
                       printf("*"); 
                       
                    
                       if ( t_i + i > 0)  {
                           save_pos[pos_i].x = t_j + j;
                           save_pos[pos_i].y = t_i + i;
                           pos_i =  pos_i + 1;
                           if ( pos_i >= 4 )  pos_i = 0;
                       }
                       
                     }
    		  //  else printf("-");
                 
           
         }   // for  j
                 
       }  // for i
           
      
}

void  print_recover ( int x, int y ) {


       for(i=y;i<y+4;i++){
         for(j=x;j<x+4;j++) {
                
                if  ( j < 0 )  continue;
                  
                gotoxy(j,i);
             	if (  t_ar [i][j] >= 1 ) {
                    
                    if (  t_ar [i][j] == 1 ) textcolor( white );
                    else  textcolor(t_ar [i][j]);
                    
                   	printf("*");
                   	
                }   	
        	    else if ( i < 21 ) { 
                        textcolor( white );
                     	printf(" ");
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
     gotoxy(26,18);
     printf("clear  cnt %d  score : %d ", clear_cnt, score_cnt * 10 ); 
       
       // Clear screen
       if  ( clear_cnt > 0 )  {
           memcpy ( t_ar, t_ar_save, sizeof(t_ar) );
           Sleep(500);
           
           //  reset 
           print_all ();
           print_shape (next_shape_idx, 0);

      }  
         
         
}



