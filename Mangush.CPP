#include <graphics.h>
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "mouse1.cpp"

#define TOTAL_CARDS 52
#define SHUFFLE_TURNS 8


int PLAYER_CARD_NUMBERS=0, AI_1_CARD_NUMBERS=0, AI_2_CARD_NUMBERS=0, AI_3_CARD_NUMBERS=0;
int CURRENT_HAND=0, XTRA_CARD_COUNT=0, TWO_COUNT=0, COUNT=0, X, Y;
int PLAYER_RULE_FLAG=0, AI_1_RULE_FLAG=0, AI_2_RULE_FLAG=0, AI_3_RULE_FLAG=0;


struct CARD
{
   char card_symbol;
   char card_number[3];
   int identifier_number, card_start_point, card_end_point;

}CARD_DECK[TOTAL_CARDS], PLAYER[20], AI_1[20], AI_2[20], AI_3[20], CURRENT_CARD, XTRA_CARD[52];

void PLAYER_game_rules(int);
void AI_1_game_rules(int);
void AI_2_game_rules(int);
void AI_3_game_rules(int);
int AI_1_hand_update(int);
int AI_2_hand_update(int);
int AI_3_hand_update(int);
void XTRA_CARD_update(int);
int mouse();

void speads(int top_left_x, int top_left_y, int btm_right_x, int btm_right_y, char card_number[3])
{
   int mid_point_x=(top_left_x + btm_right_x)/2;
   int mid_point_y=(top_left_y + btm_right_y)/2;
   int card_crdnt[]={top_left_x, top_left_y, top_left_x, btm_right_y, btm_right_x, btm_right_y, btm_right_x, top_left_y, top_left_x, top_left_y};
   int speads_crdnt[]={mid_point_x-14, mid_point_y, mid_point_x+14, mid_point_y, mid_point_x, mid_point_y-20, mid_point_x-14, mid_point_y};
   int speads_tail_crdnt[]={mid_point_x, mid_point_y, mid_point_x+8, mid_point_y+15, mid_point_x-8, mid_point_y+15, mid_point_x, mid_point_y};

   setcolor(RED);
   setfillstyle(SOLID_FILL, WHITE);
   fillpoly(5, card_crdnt);

   setcolor(BLACK);
   setfillstyle(SOLID_FILL, BLACK);
   fillellipse(mid_point_x-6, mid_point_y, 8, 8);
   fillellipse(mid_point_x+6, mid_point_y, 8, 8);
   fillpoly(3, speads_crdnt);
   fillpoly(4, speads_tail_crdnt);
   outtextxy(top_left_x+5, top_left_y+5, card_number);
   outtextxy(top_left_x+10, top_left_y+10, " ");
   setfillstyle(1,23);

}


void clubs(int top_left_x,int top_left_y,int  btm_right_x,int btm_right_y, char card_number[3])
{
   int card_crdnt[]={top_left_x, top_left_y, top_left_x, btm_right_y, btm_right_x, btm_right_y, btm_right_x, top_left_y, top_left_x, top_left_y};
   int clubs_crdnt[]={ top_left_x+38, top_left_y+65, top_left_x+38, top_left_y+78, top_left_x+42, top_left_y+78, top_left_x+42, top_left_y+65, top_left_x+38, top_left_y+65 };

   setcolor(RED);
   setfillstyle(SOLID_FILL, WHITE);
   fillpoly(5, card_crdnt);

   setcolor(RED);
   setfillstyle(SOLID_FILL, RED	);
   fillellipse(top_left_x+30, top_left_y+40, 6, 12);
   fillellipse(top_left_x+40, top_left_y+49, 12, 6);
   fillellipse(top_left_x+20, top_left_y+49, 12, 6);
   fillpoly(5, clubs_crdnt);
   outtextxy(top_left_x+5, top_left_y+5, card_number);
   outtextxy(top_left_x+70, top_left_y+115, card_number);

}



void hearts(int top_left_x, int top_left_y, int btm_right_x, int btm_right_y, char card_number[3])
{
   int mid_point_x=(top_left_x + btm_right_x)/2;
   int mid_point_y=(top_left_y + btm_right_y)/2;
   int card_crdnt[]={top_left_x, top_left_y, top_left_x, btm_right_y, btm_right_x, btm_right_y, btm_right_x, top_left_y, top_left_x, top_left_y};
   int heart_crdnt[]={mid_point_x-14, mid_point_y, mid_point_x+14, mid_point_y, mid_point_x, mid_point_y+20, mid_point_x-14, mid_point_y};

   setcolor(RED);
   setfillstyle(SOLID_FILL, WHITE);
   fillpoly(5, card_crdnt);

   setcolor(RED);
   setfillstyle(1,4);
   fillellipse(mid_point_x-6, mid_point_y, 8, 8);
   fillellipse(mid_point_x+6, mid_point_y, 8, 8);
   fillpoly(3, heart_crdnt);
   outtextxy(top_left_x+5, top_left_y+5, card_number);
   setfillstyle(1,23);
}

void backside(int top_left_x, int top_left_y, int btm_right_x, int btm_right_y)
{

   int mid_point_x=(top_left_x + btm_right_x)/2;
   int mid_point_y=(top_left_y + btm_right_y)/2;
   int card_crdnt[]={top_left_x, top_left_y, top_left_x, btm_right_y, btm_right_x, btm_right_y, btm_right_x, top_left_y, top_left_x, top_left_y};


   setcolor(RED);
   setfillstyle(SOLID_FILL, LIGHTGRAY);
   fillpoly(5, card_crdnt);

   setfillstyle(LINE_FILL, BLUE);
   fillellipse(mid_point_x, mid_point_y, 20, 20);
   setfillstyle(INTERLEAVE_FILL, LIGHTBLUE);
   fillellipse(mid_point_x, mid_point_y, 10, 10);
   setfillstyle(SOLID_FILL, CYAN);
}


void dize(int top_left_x, int top_left_y, int btm_right_x, int btm_right_y, char card_number[3])
{
   int mid_point_x=(top_left_x + btm_right_x)/2;
   int mid_point_y=(top_left_y +btm_right_y)/2;
   int dize_crdnt[]={mid_point_x-10, mid_point_y, mid_point_x, mid_point_y+10, mid_point_x+10, mid_point_y, mid_point_x, mid_point_y-10, mid_point_x-10, mid_point_y};
   int card_crdnt[]={top_left_x, top_left_y, top_left_x, btm_right_y, btm_right_x, btm_right_y, btm_right_x, top_left_y, top_left_x, top_left_y};


   setcolor(RED);
   setfillstyle(SOLID_FILL, WHITE);
   fillpoly(5, card_crdnt);

   setcolor(RED);
   outtextxy(top_left_x+5, top_left_y+5, card_number);
   setfillstyle(1,4);
   fillpoly(5, dize_crdnt);
   setfillstyle(1,40);

}


void player_card_crdnt()
{
   int i=100, j=0, temp;
   while(j<PLAYER_CARD_NUMBERS)
   {

      if(PLAYER[j].card_symbol == 'S')
      {
	speads(i, 380, i+60, 380+90, PLAYER[j].card_number);
	PLAYER[j].card_start_point = i;
	PLAYER[j].card_end_point = i+10;
      }
      if(PLAYER[j].card_symbol == 'C')
      {
	clubs(i, 380, i+60, 380+90, PLAYER[j].card_number);
	PLAYER[j].card_start_point = i;
	PLAYER[j].card_end_point = i+10;
      }
      if(PLAYER[j].card_symbol == 'D')
      {
	dize(i, 380, i+60, 380+90, PLAYER[j].card_number);
	PLAYER[j].card_start_point = i;
	PLAYER[j].card_end_point = i+10;
      }
      if(PLAYER[j].card_symbol == 'H')
      {
	hearts(i, 380, i+60, 380+90, PLAYER[j].card_number);
	PLAYER[j].card_start_point = i;
	PLAYER[j].card_end_point = i+10;
      }
      j++;
      i+=30;
   }

}

void AI_1_crdnt()
{
   int i=150, j=0;
   while(j<AI_1_CARD_NUMBERS)
   {

      backside(i, 20, i+60, 20+90);
      AI_1[j].card_start_point = i;
      AI_1[j].card_end_point = i+10;
      j++;
      i+=10;
   }
}

void AI_2_crdnt()
{
   int i=120, j=0;
   while(j<AI_2_CARD_NUMBERS)
   {

      backside(500, i, 500+90, i+60);
      AI_2[j].card_start_point = i;
      AI_2[j].card_end_point = i+10;
      j++;
      i+=10;
   }
}

void AI_3_crdnt()
{
   int i=120, j=0;
   while(j<AI_3_CARD_NUMBERS)
   {
      backside(20, i, 20+90, i+60);
      AI_3[j].card_start_point = i;
      AI_3[j].card_end_point = i+10;
      j++;
      i+=10;
   }
}


void current_card()
{
   if(CURRENT_CARD.card_symbol == 'S')
   {
	speads(320, 190, 320+80, 190+120, CURRENT_CARD.card_number);
   }
   if(CURRENT_CARD.card_symbol == 'C')
   {
	clubs(320, 190, 320+80, 190+120, CURRENT_CARD.card_number);
   }
   if(CURRENT_CARD.card_symbol == 'H')
   {
	hearts(320, 190, 320+80, 190+120, CURRENT_CARD.card_number);
   }
   if(CURRENT_CARD.card_symbol == 'D')
   {
	dize(320, 190, 320+80, 190+120, CURRENT_CARD.card_number);
   }
}


void print_background()
{
   cleardevice();
   setbkcolor(GREEN);
   player_card_crdnt();
   outtextxy(380, 470, "PLAYER !");
   AI_1_crdnt();
   setcolor(BROWN);
   outtextxy(380, 40, "AI 1");
   AI_2_crdnt();
   setcolor(YELLOW);
   outtextxy(40, 310, "AI 2");
   AI_3_crdnt();
   setcolor(BLUE);
   outtextxy(500, 310, "AI 3");
   backside(220, 190, 220+80, 190+120);
   current_card();
}

void init_hands()
{
   int i=0;
   while(i<20)
   {
      PLAYER[i].identifier_number=-1;
      AI_1[i].identifier_number=-1;
      AI_2[i].identifier_number=-1;
      AI_3[i].identifier_number=-1;
      i++;
   }
}


void set_deck()
{
    int i;
    for(i=1; i<=TOTAL_CARDS; i++)
    {
      CARD_DECK[i].identifier_number=i;
      //printf("%d ", CARD_DECK[i].identifier_number);
    }
}


void deck_init()
{
   char card_symbol[]={'S', 'C', 'D', 'H'};
   char card_number[][3]={"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"};


   int i,j,k=0;
   for(i=0; i<4; i++)
   {
      for(j=0; j<13; j++)
      {
	CARD_DECK[k].card_symbol=card_symbol[i];
	strcpy(CARD_DECK[k].card_number, card_number[j]);
	k++;
      }
   }
}


void shuffle_deck()
/*
Shuffles a deck by swapping each card with a random card from the
deck.  Note that this will work with any sized deck.
*/
{
  int i , j , temp ;
  char temp1, temp2[3];

  for( i = 0 ; i < TOTAL_CARDS ; i ++ )
  {
    j = rand() % TOTAL_CARDS ;
    temp = CARD_DECK[i].identifier_number ;
    CARD_DECK[i].identifier_number = CARD_DECK[j].identifier_number ;
    CARD_DECK[j].identifier_number = temp ;
    temp1 = CARD_DECK[i].card_symbol ;
    CARD_DECK[i].card_symbol = CARD_DECK[j].card_symbol ;
    CARD_DECK[j].card_symbol = temp1 ;
    strcpy(temp2 , CARD_DECK[i].card_number);
    strcpy(CARD_DECK[i].card_number, CARD_DECK[j].card_number);
    strcpy(CARD_DECK[j].card_number, temp2);

  }
}


void deal_cards()
{
   int i=0,j=0;
   //time_t t;
   //srand((unsigned) time(NULL));
   while(j<8)
   {
      PLAYER[j].identifier_number=CARD_DECK[i].identifier_number;
      PLAYER[j].card_symbol=CARD_DECK[i].card_symbol;
      strcpy(PLAYER[j].card_number, CARD_DECK[i].card_number);
      i++;
      AI_1[j].identifier_number=CARD_DECK[i].identifier_number;
      AI_1[j].card_symbol=CARD_DECK[i].card_symbol;
      strcpy(AI_1[j].card_number, CARD_DECK[i].card_number);
      i++;
      AI_2[j].identifier_number=CARD_DECK[i].identifier_number;
      AI_2[j].card_symbol=CARD_DECK[i].card_symbol;
      strcpy(AI_2[j].card_number, CARD_DECK[i].card_number);
      i++;
      AI_3[j].identifier_number=CARD_DECK[i].identifier_number;
      AI_3[j].card_symbol=CARD_DECK[i].card_symbol;
      strcpy(AI_3[j].card_number, CARD_DECK[i].card_number);
      i++;
      j++;
   }
   PLAYER_CARD_NUMBERS=8;
   AI_1_CARD_NUMBERS=8;
   AI_2_CARD_NUMBERS=8;
   AI_3_CARD_NUMBERS=8;
   CURRENT_CARD.identifier_number=CARD_DECK[32].identifier_number;
   CURRENT_CARD.card_symbol=CARD_DECK[32].card_symbol;
   strcpy(CURRENT_CARD.card_number, CARD_DECK[32].card_number);
   j=0;
   i=33;
   while(i != 52)
   {
      XTRA_CARD[j].identifier_number=CARD_DECK[i].identifier_number;
      XTRA_CARD[j].card_symbol=CARD_DECK[i].card_symbol;
      strcpy(XTRA_CARD[j].card_number, CARD_DECK[i].card_number);
      i++;
      j++;
      XTRA_CARD_COUNT++;
   }
   CURRENT_HAND=1;
}




void show_card_AI_1()
{
   printf("AI_1 turn & card in hand= %d rule flag= %d\n", AI_1_CARD_NUMBERS, AI_1_RULE_FLAG);
}

void show_card_AI_2()
{
   printf("AI_2 turn & card in hand= %d rule flag=%d\n", AI_2_CARD_NUMBERS,AI_2_RULE_FLAG);
}

void show_card_AI_3()
{
   printf("AI_3 turn & card in hand= %d rule flag=%d\n", AI_3_CARD_NUMBERS,AI_3_RULE_FLAG);
}

void deck_and_hands()
{
   init_hands();
   set_deck();
   deck_init();
   shuffle_deck();
   deal_cards();
}

//players hands update

int player_xtra_card(int x, int y)
{
    if(x>=220 && x<=300 && y>=190 && y<=310)
     {
       PLAYER[PLAYER_CARD_NUMBERS].identifier_number=XTRA_CARD[0].identifier_number;
       PLAYER[PLAYER_CARD_NUMBERS].card_symbol=XTRA_CARD[0].card_symbol;
       PLAYER[PLAYER_CARD_NUMBERS].card_start_point=XTRA_CARD[0].card_start_point;
       PLAYER[PLAYER_CARD_NUMBERS].card_end_point=XTRA_CARD[0].card_end_point;
       strcpy(PLAYER[PLAYER_CARD_NUMBERS].card_number, XTRA_CARD[0].card_number);
       XTRA_CARD_update(1);
       PLAYER_CARD_NUMBERS++;
       return 0;
     }
}

int player_hand_update(int x, int y)
{
     int index_number, i, j, k;
     if(PLAYER_CARD_NUMBERS==0)
     {
       return 0;
     }
     for(i=0; i<PLAYER_CARD_NUMBERS; i++)
     {
	if(x>PLAYER[i].card_start_point && x<PLAYER[i].card_end_point)
	{
	  PLAYER_game_rules(i);
	  if(PLAYER_RULE_FLAG == 1)
	  {
	    CURRENT_CARD.card_symbol= PLAYER[i].card_symbol;
	    strcpy(CURRENT_CARD.card_number, PLAYER[i].card_number);
	    CURRENT_CARD.identifier_number= PLAYER[i].identifier_number;
	    index_number=i;
	    //printf("%d", index_number);
	    for(j=index_number; j<PLAYER_CARD_NUMBERS-1; j++)
	    {
	       PLAYER[j].identifier_number=PLAYER[j+1].identifier_number;
	       PLAYER[j].card_symbol=PLAYER[j+1].card_symbol;
	       PLAYER[j].card_start_point=PLAYER[j+1].card_start_point;
	       PLAYER[j].card_end_point=PLAYER[j+1].card_end_point;
	       strcpy(PLAYER[j].card_number, PLAYER[j+1].card_number);
	    }
	    PLAYER_CARD_NUMBERS--;
	  }
	  if(PLAYER_RULE_FLAG == 2)
	  {
	    for(k=0; k<TWO_COUNT; k++)
	    {
	       PLAYER[PLAYER_CARD_NUMBERS].identifier_number=XTRA_CARD[k].identifier_number;
	       PLAYER[PLAYER_CARD_NUMBERS].card_symbol=XTRA_CARD[k].card_symbol;
	       PLAYER[PLAYER_CARD_NUMBERS].card_start_point=XTRA_CARD[k].card_start_point;
	       PLAYER[PLAYER_CARD_NUMBERS].card_end_point=XTRA_CARD[k].card_end_point;
	       strcpy(PLAYER[PLAYER_CARD_NUMBERS].card_number, XTRA_CARD[k].card_number);
	       XTRA_CARD_update(1);
	       PLAYER[PLAYER_CARD_NUMBERS+1].identifier_number=XTRA_CARD[k+1].identifier_number;
	       PLAYER[PLAYER_CARD_NUMBERS+1].card_symbol=XTRA_CARD[k+1].card_symbol;
	       PLAYER[PLAYER_CARD_NUMBERS+1].card_start_point=XTRA_CARD[k+1].card_start_point;
	       PLAYER[PLAYER_CARD_NUMBERS+1].card_end_point=XTRA_CARD[k+1].card_end_point;
	       strcpy(PLAYER[PLAYER_CARD_NUMBERS+1].card_number, XTRA_CARD[k+1].card_number);
	       XTRA_CARD_update(1);
	       PLAYER_CARD_NUMBERS+=2;
	    }
	    TWO_COUNT=0;
	  }
	  if(PLAYER_RULE_FLAG == 2)
	  {
	    CURRENT_CARD.card_symbol= PLAYER[i].card_symbol;
	    strcpy(CURRENT_CARD.card_number, PLAYER[i].card_number);
	    CURRENT_CARD.identifier_number= PLAYER[i].identifier_number;
	    index_number=i;
	    //printf("%d", index_number);
	    for(j=index_number; j<PLAYER_CARD_NUMBERS-1; j++)
	    {
	       PLAYER[j].identifier_number=PLAYER[j+1].identifier_number;
	       PLAYER[j].card_symbol=PLAYER[j+1].card_symbol;
	       PLAYER[j].card_start_point=PLAYER[j+1].card_start_point;
	       PLAYER[j].card_end_point=PLAYER[j+1].card_end_point;
	       strcpy(PLAYER[j-1].card_number, PLAYER[j+1].card_number);
	    }
	    PLAYER_CARD_NUMBERS--;
	    TWO_COUNT++;
	  }
	  if(PLAYER_RULE_FLAG==5)
	  {
	    return 0;
	  }
	}
     }
     return 0;

}

int AI_1_hand_update(int index_number)
{
     int i, j, k;
     if(AI_1_CARD_NUMBERS==0)
     {
       return 0;
     }
     if(AI_1_RULE_FLAG == 1)
     {
       CURRENT_CARD.card_symbol= AI_1[i].card_symbol;
       strcpy(CURRENT_CARD.card_number, AI_1[i].card_number);
       CURRENT_CARD.identifier_number= AI_1[i].identifier_number;
       XTRA_CARD_update(1);
       for(j=index_number; j<AI_1_CARD_NUMBERS-1; j++)
       {
	       AI_1[j].identifier_number=AI_1[j+1].identifier_number;
	       AI_1[j].card_symbol=AI_1[j+1].card_symbol;
	       AI_1[i].card_start_point=AI_1[j+1].card_start_point;
	       AI_1[j].card_end_point=AI_1[j+1].card_end_point;
	       strcpy(AI_1[j].card_number, AI_1[j+1].card_number);
       }
       AI_1_CARD_NUMBERS--;
       //show_card_AI_1();
     }
     if(AI_1_RULE_FLAG == 2)
     {
	    for(k=0; k<TWO_COUNT; k++)
	    {
	       AI_1[AI_1_CARD_NUMBERS].identifier_number=XTRA_CARD[k].identifier_number;
	       AI_1[AI_1_CARD_NUMBERS].card_symbol=XTRA_CARD[k].card_symbol;
	       AI_1[AI_1_CARD_NUMBERS].card_start_point=XTRA_CARD[k].card_start_point;
	       AI_1[AI_1_CARD_NUMBERS].card_end_point=XTRA_CARD[k].card_end_point;
	       strcpy(AI_1[AI_1_CARD_NUMBERS].card_number, XTRA_CARD[k].card_number);
	       XTRA_CARD_update(1);
	       AI_1[AI_1_CARD_NUMBERS+1].identifier_number=XTRA_CARD[k+1].identifier_number;
	       AI_1[AI_1_CARD_NUMBERS+1].card_symbol=XTRA_CARD[k+1].card_symbol;
	       AI_1[AI_1_CARD_NUMBERS+1].card_start_point=XTRA_CARD[k+1].card_start_point;
	       AI_1[AI_1_CARD_NUMBERS+1].card_end_point=XTRA_CARD[k+1].card_end_point;
	       strcpy(AI_1[AI_1_CARD_NUMBERS+1].card_number, XTRA_CARD[k+1].card_number);
	       XTRA_CARD_update(1);
	       AI_1_CARD_NUMBERS+=2;
	    }
	    TWO_COUNT=0;
	    //show_card_AI_1();
     }
     if(AI_1_RULE_FLAG==4)
	  {
	    CURRENT_CARD.card_symbol= AI_1[i].card_symbol;
	    strcpy(CURRENT_CARD.card_number, AI_1[i].card_number);
	    CURRENT_CARD.identifier_number= AI_1[i].identifier_number;
	    XTRA_CARD_update(2);
	    for(j=index_number; j<AI_1_CARD_NUMBERS; j++)
	    {
	       AI_1[j].identifier_number=AI_1[j+1].identifier_number;
	       AI_1[j].card_symbol=AI_1[j+1].card_symbol;
	       AI_1[i].card_start_point=AI_1[j+1].card_start_point;
	       AI_1[j].card_end_point=AI_1[j+1].card_end_point;
	       strcpy(AI_1[j].card_number, AI_1[j+1].card_number);
	    }
	    AI_1_CARD_NUMBERS--;
	    TWO_COUNT++;
	    //show_card_AI_1();
	  }
     if(AI_1_RULE_FLAG==3)
     {
       AI_1[AI_1_CARD_NUMBERS].identifier_number=XTRA_CARD[k].identifier_number;
       AI_1[AI_1_CARD_NUMBERS].card_symbol=XTRA_CARD[k].card_symbol;
       AI_1[AI_1_CARD_NUMBERS].card_start_point=XTRA_CARD[k].card_start_point;
       AI_1[AI_1_CARD_NUMBERS].card_end_point=XTRA_CARD[k].card_end_point;
       strcpy(AI_1[AI_1_CARD_NUMBERS].card_number, XTRA_CARD[k].card_number);
       AI_3_CARD_NUMBERS++;
       XTRA_CARD_update(1);
       //show_card_AI_1();
     }
     if(AI_1_RULE_FLAG==5)
     {
	    return 0;
     }



}

int AI_2_hand_update(int index_number)
{
     int i, j, k;
     if(AI_2_CARD_NUMBERS==0)
     {
       return 0;
     }
       if(AI_2_RULE_FLAG == 1)
       {
	 CURRENT_CARD.card_symbol= AI_2[i].card_symbol;
	 strcpy(CURRENT_CARD.card_number, AI_2[i].card_number);
	 CURRENT_CARD.identifier_number= AI_2[i].identifier_number;
	 XTRA_CARD_update(1);
	 for(j=index_number; j<AI_2_CARD_NUMBERS-1; j++)
	 {
	    AI_2[j].identifier_number=AI_2[j+1].identifier_number;
	    AI_2[j].card_symbol=AI_2[j+1].card_symbol;
	    AI_2[i].card_start_point=AI_2[j+1].card_start_point;
	    AI_2[j].card_end_point=AI_2[j+1].card_end_point;
	    strcpy(AI_2[j].card_number, AI_2[j+1].card_number);
	 }
	 AI_2_CARD_NUMBERS--;
	 //show_card_AI_2();
       }
       if(AI_2_RULE_FLAG == 2)
       {
	 for(k=0; k<TWO_COUNT; k++)
	 {
	    AI_2[AI_2_CARD_NUMBERS].identifier_number=XTRA_CARD[k].identifier_number;
	    AI_2[AI_2_CARD_NUMBERS].card_symbol=XTRA_CARD[k].card_symbol;
	    AI_2[AI_2_CARD_NUMBERS].card_start_point=XTRA_CARD[k].card_start_point;
	    AI_2[AI_2_CARD_NUMBERS].card_end_point=XTRA_CARD[k].card_end_point;
	    strcpy(AI_2[AI_2_CARD_NUMBERS].card_number, XTRA_CARD[k].card_number);
	    XTRA_CARD_update(1);
	    AI_2[AI_2_CARD_NUMBERS+1].identifier_number=XTRA_CARD[k+1].identifier_number;
	    AI_2[AI_2_CARD_NUMBERS+1].card_symbol=XTRA_CARD[k+1].card_symbol;
	    AI_2[AI_2_CARD_NUMBERS+1].card_start_point=XTRA_CARD[k+1].card_start_point;
	    AI_2[AI_2_CARD_NUMBERS+1].card_end_point=XTRA_CARD[k+1].card_end_point;
	    strcpy(AI_2[AI_2_CARD_NUMBERS+1].card_number, XTRA_CARD[k+1].card_number);
	    XTRA_CARD_update(2);
	    AI_2_CARD_NUMBERS+=2;
	 }
	 TWO_COUNT=0;
	 //show_card_AI_2();
       }
       if(AI_2_RULE_FLAG==4)
	  {
	    CURRENT_CARD.card_symbol= AI_2[i].card_symbol;
	    strcpy(CURRENT_CARD.card_number, AI_2[i].card_number);
	    CURRENT_CARD.identifier_number= AI_2[i].identifier_number;
	    XTRA_CARD_update(2);
	    for(j=index_number; j<AI_2_CARD_NUMBERS; j++)
	    {
	       AI_2[j].identifier_number=AI_2[j+1].identifier_number;
	       AI_2[j].card_symbol=AI_2[j+1].card_symbol;
	       AI_2[i].card_start_point=AI_2[j+1].card_start_point;
	       AI_2[j].card_end_point=AI_2[j+1].card_end_point;
	       strcpy(AI_2[j].card_number, AI_2[j+1].card_number);
	    }
	    AI_2_CARD_NUMBERS--;
	    TWO_COUNT++;
	    //show_card_AI_2();
	  }
       if(AI_2_RULE_FLAG==3)
       {
	 AI_2[AI_2_CARD_NUMBERS].identifier_number=XTRA_CARD[0].identifier_number;
	 AI_2[AI_2_CARD_NUMBERS].card_symbol=XTRA_CARD[0].card_symbol;
	 AI_2[AI_2_CARD_NUMBERS].card_start_point=XTRA_CARD[0].card_start_point;
	 AI_2[AI_2_CARD_NUMBERS].card_end_point=XTRA_CARD[0].card_end_point;
	 strcpy(AI_2[AI_2_CARD_NUMBERS].card_number, XTRA_CARD[0].card_number);
	 AI_2_CARD_NUMBERS++;
	 XTRA_CARD_update(1);
	 //show_card_AI_2();
       }
     if(AI_2_RULE_FLAG==5)
     {
	    return 0;
     }

}


int AI_3_hand_update(int index_number)
{
     int i, j, k;
     if(AI_3_CARD_NUMBERS==0)
     {
       return 0;
     }
       if(AI_3_RULE_FLAG == 1)
       {
	    CURRENT_CARD.card_symbol= AI_3[i].card_symbol;
	    strcpy(CURRENT_CARD.card_number, AI_3[i].card_number);
	    CURRENT_CARD.identifier_number= AI_3[i].identifier_number;
	    XTRA_CARD_update(2);
	    for(j=index_number; j<AI_3_CARD_NUMBERS-1; j++)
	    {
	       AI_3[j].identifier_number=AI_3[j+1].identifier_number;
	       AI_3[j].card_symbol=AI_3[j+1].card_symbol;
	       AI_3[i].card_start_point=AI_3[j+1].card_start_point;
	       AI_3[j].card_end_point=AI_3[j+1].card_end_point;
	       strcpy(AI_3[j].card_number, AI_3[j+1].card_number);
	    }
	    AI_3_CARD_NUMBERS--;
	    //show_card_AI_3();
       }
       if(AI_3_RULE_FLAG == 2)
       {
	    for(k=0; k<TWO_COUNT; k++)
	    {
	       AI_3[AI_3_CARD_NUMBERS].identifier_number=XTRA_CARD[k].identifier_number;
	       AI_3[AI_3_CARD_NUMBERS].card_symbol=XTRA_CARD[k].card_symbol;
	       AI_3[AI_3_CARD_NUMBERS].card_start_point=XTRA_CARD[k].card_start_point;
	       AI_3[AI_3_CARD_NUMBERS].card_end_point=XTRA_CARD[k].card_end_point;
	       strcpy(AI_3[AI_3_CARD_NUMBERS].card_number, XTRA_CARD[k].card_number);
	       XTRA_CARD_update(1);
	       AI_3[AI_3_CARD_NUMBERS+1].identifier_number=XTRA_CARD[k+1].identifier_number;
	       AI_3[AI_3_CARD_NUMBERS+1].card_symbol=XTRA_CARD[k+1].card_symbol;
	       AI_3[AI_3_CARD_NUMBERS+1].card_start_point=XTRA_CARD[k+1].card_start_point;
	       AI_3[AI_3_CARD_NUMBERS+1].card_end_point=XTRA_CARD[k+1].card_end_point;
	       strcpy(AI_3[AI_3_CARD_NUMBERS+1].card_number, XTRA_CARD[k+1].card_number);
	       XTRA_CARD_update(1);
	       AI_3_CARD_NUMBERS+=2;
	    }
	    TWO_COUNT=0;
	    //show_card_AI_3();
	  }
	  if(AI_3_RULE_FLAG==4)
	  {
	    CURRENT_CARD.card_symbol= AI_3[i].card_symbol;
	    strcpy(CURRENT_CARD.card_number, AI_3[i].card_number);
	    CURRENT_CARD.identifier_number= AI_3[i].identifier_number;
	    XTRA_CARD_update(2);
	    for(j=index_number; j<AI_3_CARD_NUMBERS-1; j++)
	    {
	       AI_3[j].identifier_number=AI_3[j+1].identifier_number;
	       AI_3[j].card_symbol=AI_3[j+1].card_symbol;
	       AI_3[i].card_start_point=AI_3[j+1].card_start_point;
	       AI_3[j].card_end_point=AI_3[j+1].card_end_point;
	       strcpy(AI_3[j].card_number, AI_3[j+1].card_number);
	    }
	    AI_3_CARD_NUMBERS--;
	    TWO_COUNT++;
	    //show_card_AI_3();
	  }
	  if(AI_3_RULE_FLAG==3)
	  {
	    AI_3[AI_3_CARD_NUMBERS].identifier_number=XTRA_CARD[0].identifier_number;
	    AI_3[AI_3_CARD_NUMBERS].card_symbol=XTRA_CARD[0].card_symbol;
	    AI_3[AI_3_CARD_NUMBERS].card_start_point=XTRA_CARD[0].card_start_point;
	    AI_3[AI_3_CARD_NUMBERS].card_end_point=XTRA_CARD[0].card_end_point;
	    strcpy(AI_3[AI_3_CARD_NUMBERS].card_number, XTRA_CARD[0].card_number);
	    AI_3_CARD_NUMBERS++;
	    XTRA_CARD_update(1);
	    //show_card_AI_3();
	  }
     if(AI_3_RULE_FLAG==5)
     {
	    return 0;
     }
}

/*this area is infected with u know what so kala san debug it */

int card_symbol_choice()
{
   int window_points[]={150, 150, 500, 150, 500, 400, 150, 400, 150, 150};
   setcolor(WHITE);
   fillpoly(4, window_points);
   setcolor(BLACK);
   outtextxy(180, 180, "CHOOSE THE SYMBOL TO PLAY NEXT HAND");
   hearts(200, 200, 250, 280, " ");
   clubs(280, 200, 330, 280, " ");
   speads(300, 300, 350, 380, " ");
   dize(380, 300, 430, 380, " ");

   while(1)
   {
      show_mouse();
      mouse_position();

      if ( (button&1) == 1)
      //if(mouse())
      {
	 if(x>= 200 && x<= 250)
	 {
	   CURRENT_CARD.identifier_number=-2;
	   strcpy(CURRENT_CARD.card_number, " ");
	   CURRENT_CARD.card_symbol= 'H';
	   print_background();
	   return 0;
	 }
	 if(x>= 280 && x<=330)
	 {
	   CURRENT_CARD.identifier_number=-2;
	   strcpy(CURRENT_CARD.card_number, " ");
	   CURRENT_CARD.card_symbol= 'C';
	   print_background();
	   return 0;
	 }
	 if(x>= 300 && x<=350)
	 {
	   CURRENT_CARD.identifier_number=-2;
	   strcpy(CURRENT_CARD.card_number, " ");
	   CURRENT_CARD.card_symbol= 'S';
	   print_background();
	   return 0;
	 }
	 if(x>= 380 && x<= 430)
	 {
	   CURRENT_CARD.identifier_number=-2;
	   strcpy(CURRENT_CARD.card_number, " ");
	   CURRENT_CARD.card_symbol= 'H';
	   print_background();
	   return 0;
	 }
	 delay(500);
	 hide_mouse();
      }
   }
}

void PLAYER_game_rules(int n)
{
     int temp1, temp2;
     temp1=CURRENT_CARD.identifier_number/13;
     temp2=CURRENT_CARD.identifier_number%13;
     if(PLAYER[n].identifier_number%13==0)
     {
       PLAYER_RULE_FLAG=5;
     }
     if(PLAYER[n].identifier_number%13==10)
     {
       PLAYER_RULE_FLAG=1;
       card_symbol_choice();
     }
     if(CURRENT_CARD.identifier_number%13==1 && PLAYER[n].identifier_number%13==1)
     {
       PLAYER_RULE_FLAG=4;
     }
     if(CURRENT_CARD.identifier_number%13==1)
     {
       PLAYER_RULE_FLAG=2;
     }
     if(PLAYER[n].identifier_number/13== temp1 || PLAYER[n].identifier_number%13== temp2)
     {
       PLAYER_RULE_FLAG=1;
     }
     else
     {
       PLAYER_RULE_FLAG=3;
     }
}

void AI_1_game_rules(int n)
{
     int temp1, temp2;
     temp1=CURRENT_CARD.identifier_number/13;
     temp2=CURRENT_CARD.identifier_number%13;
     if(AI_1[n].identifier_number%13==0)
     {
       AI_1_RULE_FLAG=5;
     }
     if(AI_1[n].identifier_number%13==10)
     {
       AI_1_RULE_FLAG=1;
       //card_symbol_choice();
     }
     else if(CURRENT_CARD.identifier_number%13==1 && AI_1[n].identifier_number%13==1)
     {
       AI_1_RULE_FLAG=4;
     }
     else if(CURRENT_CARD.identifier_number%13==1)
     {
       AI_1_RULE_FLAG=2;
     }
     else if(AI_1[n].identifier_number/13== temp1 || AI_1[n].identifier_number%13== temp2)
     {
       AI_1_RULE_FLAG=1;
     }
     else
     {
       AI_1_RULE_FLAG=3;
     }
}

void AI_2_game_rules(int n)
{
     int temp1, temp2;
     temp1=CURRENT_CARD.identifier_number/13;
     temp2=CURRENT_CARD.identifier_number%13;
     if(AI_2[n].identifier_number%13==0)
     {
       AI_2_RULE_FLAG=5;
     }
     if(AI_2[n].identifier_number%13==10)
     {
       AI_2_RULE_FLAG=1;
       //card_symbol_choice();
     }
     else if(CURRENT_CARD.identifier_number%13==1 && AI_2[n].identifier_number%13==1)
     {
       AI_2_RULE_FLAG=4;
     }
     else if(CURRENT_CARD.identifier_number%13==1)
     {
       AI_2_RULE_FLAG=2;
     }
     else if(AI_2[n].identifier_number/13== temp1 || AI_2[n].identifier_number%13== temp2)
     {
       AI_2_RULE_FLAG=1;
     }
     else
     {
       AI_2_RULE_FLAG=3;
     }
}

void AI_3_game_rules(int n)
{
     int temp1, temp2;
     temp1=CURRENT_CARD.identifier_number/13;
     temp2=CURRENT_CARD.identifier_number%13;
     if(AI_2[n].identifier_number%13==0)
     {
       AI_2_RULE_FLAG=5;
     }
     if(AI_3[n].identifier_number%13==10)
     {
       AI_3_RULE_FLAG=1;
       //card_symbol_choice();
     }
     else if(CURRENT_CARD.identifier_number%13==1 && AI_3[n].identifier_number%13==1)
     {
       AI_3_RULE_FLAG=4;
     }
     else if(CURRENT_CARD.identifier_number%13==1)
     {
       AI_3_RULE_FLAG=2;
     }
     else if(AI_3[n].identifier_number/13== temp1 || AI_3[n].identifier_number%13== temp2)
     {
       AI_3_RULE_FLAG=1;
     }
     else
     {
       AI_3_RULE_FLAG=3;
     }
}


int AI_1_move()
{
     int i;
     for(i=0; i<AI_1_CARD_NUMBERS; i++)
     {
	if(AI_1[i].identifier_number/13==CURRENT_CARD.identifier_number/13 || AI_1[i].identifier_number%13==CURRENT_CARD.identifier_number%13)
	{
	  AI_1_game_rules(i);
	  AI_1_hand_update(i);
	  return 0;
	}
     }
}

int AI_2_move()
{
     int i;
     for(i=0; i<AI_2_CARD_NUMBERS; i++)
     {
	if(AI_2[i].identifier_number/13==CURRENT_CARD.identifier_number/13 || AI_3[i].identifier_number%13==CURRENT_CARD.identifier_number%13)
	{
	  AI_2_game_rules(i);
	  AI_2_hand_update(i);
	  return 0;
	}
     }

}

int AI_3_move()
{
     int i;
     for(i=0; i<AI_1_CARD_NUMBERS; i++)
     {
	if(AI_3[i].identifier_number/13==CURRENT_CARD.identifier_number/13 || AI_3[i].identifier_number%13==CURRENT_CARD.identifier_number%13)
	{
	  AI_3_game_rules(i);
	  AI_3_hand_update(i);
	  return 0;
	}
     }
}



void player_turns(int x, int y)
{
     //if(CURRENT_HAND == 1)

       player_hand_update(x,y);
       //CURRENT_HAND=3;
       //printf("PLAYER HAND\nrule flag=%d \n", PLAYER_RULE_FLAG);
       //printf("current card %c%s\n ", CURRENT_CARD.card_symbol, CURRENT_CARD.card_number);

     //if(CURRENT_HAND == 3)
     //{
       AI_1_move();
       //CURRENT_HAND =2;
       //printf("AI_1 HAND\n");
       //printf("current card %c%s\n ", CURRENT_CARD.card_symbol, CURRENT_CARD.card_number);
     //}
     //if(CURRENT_HAND == 2)
     //{
       AI_2_move();
       //CURRENT_HAND=4;
       //printf("AI_2 HAND\n");
       //printf("current card %c%s\n ", CURRENT_CARD.card_symbol, CURRENT_CARD.card_number);
     //}
     //if(CURRENT_HAND == 4)
     //{
       AI_3_move();
       //CURRENT_HAND=1;
       //printf("AI_3 HAND\n");
       //printf("current card %c%s\n ", CURRENT_CARD.card_symbol, CURRENT_CARD.card_number);
     //}
}

void XTRA_CARD_update(int n)
{
     int j;
     if(n==1)
     {
       for(j=0; j<=XTRA_CARD_COUNT; j++)
       {
	  XTRA_CARD[j].identifier_number=XTRA_CARD[j+1].identifier_number;
	  XTRA_CARD[j].card_symbol=XTRA_CARD[j+1].card_symbol;
	  strcpy(XTRA_CARD[j].card_number, XTRA_CARD[j+1].card_number);
       }
       XTRA_CARD_COUNT--;
     }
     if(n==2)
     {
       XTRA_CARD[XTRA_CARD_COUNT].identifier_number=CURRENT_CARD.identifier_number;
       XTRA_CARD[XTRA_CARD_COUNT].card_symbol=CURRENT_CARD.card_symbol;
       strcpy(XTRA_CARD[XTRA_CARD_COUNT].card_number, CURRENT_CARD.card_number);
       XTRA_CARD_COUNT++;
     }
}

int end_condition()
{
     if(PLAYER_CARD_NUMBERS == 0 && AI_1_CARD_NUMBERS == 0 && AI_2_CARD_NUMBERS == 0)
     {
       return 1;
     }
     if(PLAYER_CARD_NUMBERS == 0 && AI_2_CARD_NUMBERS == 0 && AI_3_CARD_NUMBERS == 0)
     {
       return 1;
     }
     if(PLAYER_CARD_NUMBERS == 0 && AI_2_CARD_NUMBERS == 0 && AI_3_CARD_NUMBERS == 0)
     {
       return 1;
     }
     if(AI_1_CARD_NUMBERS == 0 && AI_2_CARD_NUMBERS == 0 && AI_3_CARD_NUMBERS == 0)
     {
       return 1;
     }
     else
     {
       return 0;
     }
}

/*int mouse()
{

   show_mouse();
   mouse_position();
   if((button&1)==1)
   {
     X=x;
     Y=y;
     return 1;
   }
   delay(500);
   hide_mouse();
} */

int main()
{
   clrscr();
   int gd = DETECT, gm;

   initgraph(&gd, &gm, "C:\\TC\\BGI");

   deck_and_hands();
   load_driver();
   //show_card();
   print_background();
   show_mouse();
   int flag=0;
   while(1)
   {
      if(end_condition())
      {
	exit(1);
      }
      if(kbhit())
      {
	exit(1);
      }
      mouse_position();

      if(flag==0)
      {
	print_background();
	flag=1;
      }
      if( (button&1) == 1)
      {
	  //board_update(x,y);
	  if(x>=220 && x<=300 && y>=190 && y<=310)
	  {
	    player_xtra_card(x,y);
	  }
	  player_turns(x,y);
	  print_background();
	  flag=0;
	  delay(500);
      }
   }


   getch();
   closegraph();
   return 0;
}
