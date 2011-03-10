/**********************************************************
  Header files
 **********************************************************/
#include "LPC210x.h"
#include "system.h"
#include "printmacros.h"
#include "graphicdata.h"
#include "intcomm.h"
#include "pong_data.h"
#include <stdio.h>



//#define WHITE 5
//#define BLACK 1
#define WHITE 3
#define BLACK 1
#define MULTI  1
#define SINGLE  0
#define SAVER 2
/**********************************************************
  MAIN
 **********************************************************/

int ballX = 0;
int ballY = 0;
int oldballX = 0;
int oldballY = 0;

int ballXarray[10] = { 32,32,32,32,32,32,32,32,32,32 };
int ballYarray[10] = { 32,32,32,32,32,32,32,32,32,32 };
int ballVelXarray[10] =  { 1,1,-1,-1,1,1,-1,-1,1,1 };
int ballVelYarray[10] =  { 1,-1,1,-1,1,-1,1,-1,1,-1 }; 

int drops[4] = { 0,0,0,0 };

int ballsInPlay = 0;

int bar1 = 27;
int bar2 = 27;
int bar3 = 27;
int bar4 = 27;
int oldbar1 = 0;
int oldbar2 = 0;
int oldbar3 = 0;
int oldbar4 = 0;

int hits = 0;

int fullreset = 1;
int explodereset = 0;

int STARTSTATE = 1;
int BALLSPEED = 1;
int GAMESTATE = SINGLE;
int BARSPEED = 4;

int move1L = 1, move2L = 1, move3L = 1, move4L = 1;
int move1R = 1, move2R = 1, move3R = 1, move4R = 1;


int vel[2] = { -3,-3 };
char strip[64][64];



void update_ball(int ball_num);
void update_paddles(void);
void clear_matrix(void);
void refresh(void);
void put_number(int number);
void clear_number(void);
void clear_move(void);
void reset(void);
void menu(void);
void run(void);
void explode_bar(void);
void screen_saver(void);
void reset_velocities(void);

int main (void) 
{
  char c;

  boot_up();
  spi_init();
  
  
  PRINTF0("\n\r    Sparkfun Electronics\n\r");
  PRINTF0("Makerfaire Light Table Firmware\n\r");

	IODIR0 &= ~((1<<22) | (1<<23) | (1<<24) | (1<<25) | (1<<26) | (1<<27) | (1<<28) | (1<<29) | (1<<30) | (1<<31));

	clear_matrix();
	reset_velocities();
	menu();
	while(1);

}

void run(void)
{
	int i;
	while(1)
  	{
		update_paddles();
		for(i = 0; i <= ballsInPlay; i++)
		{
			update_ball(i);
		}
		put_number(hits);
		refresh();
	
		
   	}
}


void update_ball(int ball_num)
{
	int barhit = 0;
	
	ballX = ballXarray[ball_num];
	ballY = ballYarray[ball_num];
	vel[0] = ballVelXarray[ball_num];
	vel[1] = ballVelYarray[ball_num];
	
	// Save old ball
	oldballX = ballX;
	oldballY = ballY;
	
	if(STARTSTATE)
	{
		ballX = bar1 + 2;
		ballY = 3;
	}
	else // Update ball position
	{
		ballX = ballX + vel[0];
		ballY = ballY + vel[1];
	}
	
	
	// Test if ball has hit a bar
	if(GAMESTATE != SAVER)
	{
	if((ballY < 3) && (ballX >= (bar1-1)) && ballX <= (bar1 +8)) // Hit bar 1
	{
		vel[1] = -vel[1];
		barhit = 1;
		if(move1L){ vel[0] = vel[0] - 1; move1L = 0; }
		if(move1R){ vel[0] = vel[0] + 1; move1R = 0; }
	}
	
	if((ballY > 59) && (ballX >= (bar2)) && ballX <= (bar2 +8))  // Top
	{
		vel[1] = -vel[1];
		barhit = 1;
		if(move2L){ vel[0] = vel[0] + 1; move2L = 0; }
		if(move2R){ vel[0] = vel[0] - 1; move2R = 0; }
	}
	
	if((ballX > 59) && (ballY >= (bar3-1)) && ballY <= (bar3+7))
	{
		vel[0] = -vel[0];
		barhit = 1;
		if(move3L){ vel[1] = vel[1] - 1; move3L = 0; }
		if(move3R){ vel[1] = vel[1] + 1; move3R = 0; }
	}
	
	if((ballX < 3) && (ballY >= (bar4)) && ballY <= (bar4+8)) // Left
	{
		vel[0] = -vel[0];
		barhit = 1;
		if(move4L){ vel[1] = vel[1] + 1; move4L = 0; }
		if(move4R){ vel[1] = vel[1] - 1; move4R = 0; }
	}
	}
	if(vel[0] > BALLSPEED){ vel[0] = BALLSPEED; }
	if(vel[0] < -BALLSPEED){ vel[0] = -BALLSPEED; }
	if(vel[1] > BALLSPEED){ vel[1] = BALLSPEED; }
	if(vel[1] < -BALLSPEED){ vel[1] = -BALLSPEED; }
	if(GAMESTATE == SINGLE)
	{
		if(vel[0] == 0){ vel[0] = -1; } 
		if(vel[1] == 0){ vel[1] = -1; } 
	}
	
	clear_move();

	// check OBO errors
	if(barhit)
	{
		if(ballX > 59 && barhit){ ballX = 59; }
		if(ballY > 59 && barhit){ ballY = 59; }
		if(ballX < 3 && barhit){ ballX = 3; }
		if(ballY < 3 && barhit){ ballY = 3; }
		if(GAMESTATE == MULTI)
		{
			clear_number();
			hits++;
		}
		if(hits < 10)
		{	
			if(hits == 5){ ballsInPlay++; }
		}
		else if((hits%10) == 0){ ballsInPlay++; }
	}
	
		
	if(ballX > 62){ ballX = 62; }
	if(ballY > 62){ ballY = 62; }
	if(ballX < 0){ ballX = 0; }
	if(ballY < 0){ ballY = 0; }

	// Miss, reset
	if(GAMESTATE == SINGLE)
	{
		if(ballY == 0){ drops[0]++; } // Player 1 Miss
		if(ballX == 62){ drops[1]++; } // Player 2 Miss
		if(ballY == 62){ drops[2]++; } // Player 3 Miss
		if(ballX == 0){ drops[3]++; } // Player 4 Miss
	
		if(drops[0] == 2 || drops[1] == 2 || drops[2] == 2 || drops[3] == 2)
		{
			explode_bar();
		}
		else{ fullreset = 0; }
	}
	
	if(GAMESTATE == SAVER)
	{	
		if((ballX == 62) || (ballX == 0)){ vel[0] = (-vel[0]);}
		if((ballY == 62) || (ballY == 0)){ vel[1] = (-vel[1]); }
	}
	else
	{
		if((ballX == 62) || (ballX == 0)){  reset(); return; }
		if((ballY == 62) || (ballY == 0)){  reset(); return; }  
	}
	
	//if((ballX == 62) || (ballX == 0)){ vel[0] = (-vel[0]);}
	//if((ballY == 62) || (ballY == 0)){ vel[1] = (-vel[1]); }

	// Erase old ball
	strip[oldballX][oldballY] = WHITE;
	strip[oldballX+1][oldballY] = WHITE;
	strip[oldballX][oldballY+1] = WHITE;
	strip[oldballX+1][oldballY+1] = WHITE;

	// Draw New Ball
	strip[ballX][ballY] = BLACK;
	strip[ballX+1][ballY] = BLACK;
	strip[ballX][ballY+1] = BLACK;
	strip[ballX+1][ballY+1] = BLACK;
	
	// Save data to arrays
	ballXarray[ball_num] = ballX;
	ballYarray[ball_num] = ballY;
	ballVelXarray[ball_num] = vel[0];
	ballVelYarray[ball_num] = vel[1];
}

void explode_bar(void)
{
	int bar, i, j, side;

	if(drops[0] == 2) // Player 1
	{
		for(i = 0; i < 8; i++)
		{
			strip[bar1+i][2] = WHITE;
			strip[bar1+i][1] = WHITE;
			refresh();
			delay_ms(500);
		}
		
	}
	else if(drops[1] == 2) // Player 2
	{
		
		for(i = 0; i < 8; i++)
		{
			strip[62][bar3+i] = WHITE;
			strip[61][bar3+i] = WHITE;
			refresh();
			delay_ms(500);
		}
	}
	else if(drops[2] == 2) // Player 3
	{ 
		
		for(i = 0; i < 8; i++)
		{
			strip[bar2+i][62] = WHITE;
			strip[bar2+i][61] = WHITE;
			refresh();
			delay_ms(500);
		}
	}
	else if(drops[3] == 2) // Player 4
	{
		for(i = 0; i < 8; i++)
		{
			strip[2][bar4+i] = WHITE;
			strip[1][bar4+i] = WHITE;
			refresh();
			delay_ms(500);
		}

	}
	
	drops[0] = 0;
	drops[1] = 0;
	drops[2] = 0;
	drops[3] = 0;
	explodereset = 1;
	reset();
}

void put_number(int number)
{
	int i;
	int littleEnd, bigEnd;
	
	if(GAMESTATE == MULTI)
	{
		littleEnd = number%10;
		bigEnd = number/10;
		for(i = 63; i>=0; i--)
		{
			if(nums[i+(64*bigEnd)] == 1)
			{
				strip[31+(8-(i%8))][28+(i/8)] = BLACK;
			}
			
			if(nums[i+(64*littleEnd)] == 1)
			{
				strip[22+(8-(i%8))][28+(i/8)] = BLACK;
			}
		}
		if(number/100 > 0)
		{
			for(i = 63; i>=0; i--)
			{
				if(nums[i+(64*1)] == 1)
				{
					strip[40+(8-(i%8))][28+(i/8)] = BLACK;
				}
			}
		}
	}
}

void clear_number(void)
{
	int i; 
	for(i = 63; i>=0; i--)
	{ 
		strip[31+(8-(i%8))][28+(i/8)] = WHITE; 
		strip[22+(8-(i%8))][28+(i/8)] = WHITE; 
	}
}

void update_paddles(void)
{
	int i;
	
	oldbar1 = bar1;
	oldbar2 = bar2;
	oldbar3 = bar3;
	oldbar4 = bar4;

	if(!(IOPIN0 & (1<<23))) // Con1 Button
	{
		STARTSTATE = 0;
		clear_number();
		hits = 0;
	}
	if(!(IOPIN0 & (1<<24))){ bar1 -= BARSPEED; move1L = 1; } // Con1 Left
	if(!(IOPIN0 & (1<<25))){ bar1 += BARSPEED; move1R = 1; } // Con1 Right
	if(!(IOPIN0 & (1<<26))){ bar3 += BARSPEED; move3R = 1; } // Con3 Right
	if(!(IOPIN0 & (1<<27))){ bar3 -= BARSPEED; move3L = 1; } // Con3 Left
	if(!(IOPIN0 & (1<<28))){ bar2 -= BARSPEED; move2L = 1; } // Con2 Left
	if(!(IOPIN0 & (1<<29))){ bar2 += BARSPEED; move2R = 1; } // Con2 Right
	if(!(IOPIN0 & (1<<30))){ bar4 += BARSPEED; move4R = 1; } // Con4 Right
	if(!(IOPIN0 & (1<<31))){ bar4 -= BARSPEED; move4L = 1; } // Con4 Left

	if(bar1 > 53){ bar1 = 53; }
	if(bar1 < 3){ bar1 = 3; }
	if(bar2 > 53){ bar2 = 53; }
	if(bar2 < 3){ bar2 = 3; }
	if(bar3 > 53){ bar3 = 53; }
	if(bar3 < 3){ bar3 = 3; }
	if(bar4 > 53){ bar4 = 53; }
	if(bar4 < 3){ bar4 = 3; }

	// Print new bars
	// Bar 1
	if(move1L || move1R)
	{
		for(i = 0; i < 8; i++)
		{
			strip[oldbar1+i][2] = WHITE;
			strip[oldbar1+i][1] = WHITE;
		}
		for(i = 0; i < 8; i++)
		{
			strip[bar1+i][2] = BLACK;
			strip[bar1+i][1] = BLACK;
		}
	}
	// Bar 2
	if(move2L || move2R)
	{
		for(i = 0; i < 8; i++)
		{
			strip[oldbar2+i][62] = WHITE;
			strip[oldbar2+i][61] = WHITE;
		}
		for(i = 0; i < 8; i++)
		{
			strip[bar2+i][62] = BLACK;
			strip[bar2+i][61] = BLACK;
		}
	}
	// Bar 3
	if(move3L || move3R)
	{
		for(i = 0; i < 8; i++)
		{
			strip[62][oldbar3+i] = WHITE;
			strip[61][oldbar3+i] = WHITE;
		}
		for(i = 0; i < 8; i++)
		{
			strip[62][bar3+i] = BLACK;
			strip[61][bar3+i] = BLACK;
		}
	}
	// Bar 4
	if(move4L || move4R)
	{
		for(i = 0; i < 8; i++)
		{
			strip[2][oldbar4+i] = WHITE;
			strip[1][oldbar4+i] = WHITE;
		}
		for(i = 0; i < 8; i++)
		{
			strip[2][bar4+i] = BLACK;
			strip[1][bar4+i] = BLACK;
		}
	}
}

void clear_matrix(void)
{
	int i;
	int j;
	for(i = 0; i<64; i++)
	{
		for(j = 0; j<64; j++)
		{
			strip[i][j] = WHITE;
		}
	}
	/*for(i = 0; i < 3; i++)
	{
		strip[i][2] = BLACK;
		strip[2][i] = BLACK;
		strip[61][i] = BLACK;
		strip[i][61] = BLACK;
	}
	for(i = 61; i < 64; i++)
	{
		strip[i][61] = BLACK;
		strip[61][i] = BLACK;
		strip[2][i] = BLACK;
		strip[i][2] = BLACK;
	}*/
		
}

void refresh(void)
{

 		int i,j;
		set_addr(0);
		//delay_ms(1);
		for(i = 63;i>=0;i--)
		{
			for(j = 7;j>=0;j--)
			{
				spi_putch(strip[i][j]);
				//PRINTF1("%d ",strip[i][j]);
			}	
		}	
		//PRINTF0("\n\r");
 		set_addr(1);
		 //delay_ms(1);
		for(i = 63;i>=0;i--)
		{
			for(j = 15;j>=8;j--)
			{
				spi_putch(strip[i][j]);
				//PRINTF1("%d ",strip[i][j]);
			}	
		}	
 		set_addr(2);
		 //delay_ms(1);
		for(i = 63;i>=0;i--)
		{
			for(j = 23;j>=16;j--)
			{
				spi_putch(strip[i][j]);
				//PRINTF1("%d ",strip[i][j]);
			}	
		}	
 		set_addr(3);
		 //delay_ms(1);
		for(i = 63;i>=0;i--)
		{
			for(j = 31;j>=24;j--)
			{
				spi_putch(strip[i][j]);
				//PRINTF1("%d ",strip[i][j]);
			}	
		}	
 		set_addr(4);
		 //delay_ms(1);
		for(i = 63;i>=0;i--)
		{
			for(j = 39;j>=32;j--)
			{
				spi_putch(strip[i][j]);
				//PRINTF1("%d ",strip[i][j]);
			}	
		}	
 		set_addr(5);
		 //delay_ms(1);
		for(i = 63;i>=0;i--)
		{
			for(j = 47;j>=40;j--)
			{
				spi_putch(strip[i][j]);
				//PRINTF1("%d ",strip[i][j]);
			}	
		}	
 		set_addr(6);
		 //delay_ms(1);
		for(i = 63;i>=0;i--)
		{
			for(j = 55;j>=48;j--)
			{
				spi_putch(strip[i][j]);
				//PRINTF1("%d ",strip[i][j]);
			}	
		}	
 		set_addr(7);
		 //delay_ms(1);
		for(i = 63;i>=0;i--)
		{
			for(j = 63;j>=56;j--)
			{
				spi_putch(strip[i][j]);
				//PRINTF1("%d ",strip[i][j]);
			}	
		}	
}

void clear_move(void)
{
	// clear movement vectors
	move1L = 0;
	move1R = 0;
	move2L = 0;
	move2R = 0;
	move3L = 0;
	move3R = 0;
	move4L = 0;
	move4R = 0;
}

void reset(void)
{
	
	int i;
	int j = 0; 
	
	if(GAMESTATE == MULTI)
	{
		for(i=0;i<5;i++)
		{
			put_number(hits);
			refresh();
			delay_ms(1500);
			clear_number();
			refresh();
			delay_ms(700);
		}
	}

	STARTSTATE = 1; 
	clear_move(); 
	clear_matrix();
	clear_number();
	update_ball(0);
	update_paddles();
	vel[0] = 3;
	vel[1] = 3;
	ballsInPlay = 0;

	refresh();
	
	
	move1L = 1;
	move2L = 1;
	move3L = 1;
	move4L = 1;

	for(i = 0; i < 10; i++)
	{
		ballXarray[i] = 32;
		ballYarray[i] = 32;
		if(j%2 == 0){ ballVelXarray[i] =  1; } 
		else{ ballVelXarray[i] = -1; }
		if(j == 0){ ballVelYarray[i] =  -1;  }
		else{ ballVelYarray[i] =  -ballVelYarray[i-1];  }
		j++;
	}
	reset_velocities();
	if(fullreset){ menu(); }
	if(explodereset) { menu(); }

}

void menu(void)
{
	int i;
	int choice = 0;
	int change = 1;
	int erase = 1;
	int t1 = 0, t2 = 0;
	while(!(IOPIN0 & (1<<23)));
	clear_matrix();
	for(i = (8*51); i > 0; i--)
	{
		if(single[i]){ strip[(12+(i%51))][8-(24+(i/51))] = BLACK; }
	}
	for(i = (8*44); i > 0; i--)
	{
		if(multi[i]){ strip[(12+(i%44))][8-(34+(i/44))] = BLACK; }
	}
	

	while(IOPIN0 & (1<<23)) // Con1 Button
	{
		if(!(IOPIN0 & (1<<24))){ choice = 0; erase = 1; change = 1;} // Con1 Left
		if(!(IOPIN0 & (1<<25))){ choice = 1; erase = 0; change = 1; } // Con1 Right
		
		if(change)
		{
			for(i = (8*8); i > 0; i--)
			{
				strip[(4+(i%8))][8-(24+(10*erase)+(i/8))] = WHITE;
			}
			for(i = (8*8); i > 0; i--)
			{
				if(arrow[i]){ strip[(4+(i%8))][8-(24+(10*choice)+(i/8))] = BLACK; }
			}
			refresh();
			change = 0;
		}
		if(t1 >= 65000){ t2++; t1=0; }
		if(t2 >= 700){ clear_matrix(); screen_saver(); t2 = 0; } //100 = ~nine seconds
		t1++;
	}
	if(choice){ GAMESTATE = MULTI; BALLSPEED = 1; BARSPEED = 4; }
	else{ GAMESTATE = SINGLE; BALLSPEED = 4; BARSPEED = 3; } 
	STARTSTATE = 1;
	clear_matrix();
	refresh();
	run();
}

void screen_saver(void)
{
	GAMESTATE = SAVER;
	
	ballXarray[0] = 10;
	ballXarray[1] = 12;
	ballXarray[2] = 14;
	ballXarray[3] = 16;
	ballXarray[4] = 18;
	ballXarray[5] = 20;
	ballXarray[6] = 22;
	ballXarray[7] = 24;
	ballXarray[8] = 26;
	ballXarray[9] = 28;
	ballYarray[0] = 32;
	ballYarray[1] = 32;
	ballYarray[2] = 32;
	ballYarray[3] = 32;
	ballYarray[4] = 32;
	ballYarray[5] = 32;
	ballYarray[6] = 32;
	ballYarray[7] = 32;
	ballYarray[8] = 32;
	ballYarray[9] = 32;
	ballVelXarray[0] = 1;
	ballVelXarray[1] = 2;
	ballVelXarray[2] = 3;
	ballVelXarray[3] = 4;
	ballVelXarray[4] = 5;
	ballVelXarray[5] = 1;
	ballVelXarray[6] = 2;
	ballVelXarray[7] = 3;
	ballVelXarray[8] = 4;
	ballVelXarray[9] = 5;
	ballVelYarray[0] = 5; 
	ballVelYarray[1] = 4; 
	ballVelYarray[2] = 3; 
	ballVelYarray[3] = 2; 
	ballVelYarray[4] = 1; 
	ballVelYarray[5] = 3; 
	ballVelYarray[6] = 2; 
	ballVelYarray[7] = 1; 
	ballVelYarray[8] = 4; 
	ballVelYarray[9] = 5; 
	
	ballsInPlay = 9;
	BALLSPEED = 4;
	STARTSTATE = 0;
	int i;	
	while(IOPIN0 & (1<<23)) // Con1 Button
  	{
		//update_paddles();
		for(i = 0; i <= ballsInPlay; i++)
		{
			update_ball(i);
		}
		//put_number(hits);
		refresh();
		
   	}

	ballX = 0;
	ballY = 0;
	oldballX = 0;
	oldballY = 0;

	for(i = 0; i<10; i++)
	{
		ballXarray[i] = 32;
		ballYarray[i] = 32;
	}
	/*
	for(i = 0; i<10; i++)
	{
		if(i%2 == 0){ ballVelYarray[i] = 1; }
		else{ ballVelYarray[i] = -1; }
	}
	for(i = 0; i<10; i++)
	{
		if(i == 0){ ballVelXarray[i] = 1; }
		else{ ballVelXarray[i] = -ballVelXarray[i-1]; }
	}*/

	reset_velocities();

	ballsInPlay = 0;
	
	bar1 = 27;
	bar2 = 27;
	bar3 = 27;
	bar4 = 27;
	oldbar1 = 0;
	oldbar2 = 0;
	oldbar3 = 0;
	oldbar4 = 0;
	
	hits = 0;

	fullreset = 1;
	explodereset = 0;

	STARTSTATE = 1;
	BALLSPEED = 1;
	GAMESTATE = SINGLE;
	BARSPEED = 4;

	move1L = 1;
	move2L = 1;
	move3L = 1; 
	move4L = 1;
	move1R = 1; 
	move2R = 1; 
	move3R = 1; 
	move4R = 1;

	vel[0] = -3;
	vel[1] = -3;
	delay_ms(100);
	menu();
	
}

void reset_velocities(void)
{
	
	ballXarray[0] = 32;
	ballXarray[1] = 47;
	ballXarray[2] = 47;
	ballXarray[3] = 15;
	ballXarray[4] = 32;
	ballXarray[5] = 15;
	ballXarray[6] = 15;
	ballXarray[7] = 32;
	ballXarray[8] = 47;
	ballXarray[9] = 32;
	
	ballYarray[0] = 32;
	ballYarray[1] = 15;
	ballYarray[2] = 32;
	ballYarray[3] = 47;
	ballYarray[4] = 47;
	ballYarray[5] = 15;
	ballYarray[6] = 32;
	ballYarray[7] = 15;
	ballYarray[8] = 47;
	ballYarray[9] = 32;

	ballVelXarray[0] = 1;
	ballVelXarray[1] = 0;
	ballVelXarray[2] = -1;
	ballVelXarray[3] = 0;
	ballVelXarray[4] = -1;
	ballVelXarray[5] = 1;
	ballVelXarray[6] = 1;
	ballVelXarray[7] = 1;
	ballVelXarray[8] = -1;
	ballVelXarray[9] = 1;

	ballVelYarray[0] = 1;
	ballVelYarray[1] = 1;
	ballVelYarray[2] = 1;
	ballVelYarray[3] = -1;
	ballVelYarray[4] = -1;
	ballVelYarray[5] = 0;
	ballVelYarray[6] = -1;
	ballVelYarray[7] = 1;
	ballVelYarray[8] = 0;
	ballVelYarray[9] = 1;
}
	
