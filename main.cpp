#include <cstdlib>
#include <ncurses.h>

#define kEY_UP 0403 
#define KEY_DOWN 0402 
#define KEY_LEFT 0404
#define KEY_RIGHT 0405 

const int width=20,height=20;
int  x, y, fruitx,fruity,score;
enum eDirection {STOP = 0, LEFT, RIGHT, UP, DOWN};

eDirection dir;

int tailX[100],tailY[100];
int nTail=0;

bool gameover;
void setup()
{
	initscr();
	clear();
	noecho();
	cbreak();
	curs_set(0);


	gameover=false;
	dir=STOP;
	x=width/2;
	y=height/2;
	fruitx=(rand()%width)+1;
	fruity=(rand()%height)+1;
	score=0;
}

void draw()
{
	clear();
	for(int i=0;i<width+2;i++)
	{
		mvprintw(0,i,"+");
	}
	for(int i=0;i<height+2;i++)
	{
		for(int j=0;j<width+2;j++)
		{
			if(i==0 || i==21)
			{
				mvprintw(i,j,"+");
			}
			else if(j==0 || j==21)
			{
				mvprintw(i,j,"+");
			}
			else if (i==y && j==x)
			{
				mvprintw(i,j,"O");
			}
			else if(i==fruity && j==fruitx)
			{
			mvprintw(i,j,"@");
			}
			else
			{
				for(int k=0;k<nTail;k++)
				{
					if(tailX[k]==j && tailY[k]==i)
					{
						mvprintw(i,j,"o");
					}
				}
			}
		}
	}
	mvprintw(23,0,"score %d ",score);
	refresh();
	

}

void input()
{
	keypad(stdscr,TRUE);
	halfdelay(2);
	int c=getch();
	switch(c)
	{
	case KEY_LEFT:
		dir=LEFT;
		break;
	case KEY_RIGHT:
		dir=RIGHT;
		break;
	case KEY_UP:
		dir=DOWN;
		break;
	case KEY_DOWN:
		dir=UP;
		break;
	case 113:
		gameover=true;
		break;
	}
}

void logic()
{
	int prevx=tailX[0];
	int prevY=tailY[0];
	int prev2x,prev2y;
	tailX[0]=x;
	tailY[0]=y;

	for(int i=1;i<nTail;i++)
	{
		prev2x=tailX[i];
		prev2y=tailY[i];
		tailX[i]=prevx;
		tailY[i]=prevY;
		prevx=prev2x;
		prevY=prev2y;

	}

	switch(dir)
	{
	case LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;
	case UP:
		y++;
		break;
	case DOWN:
		y--;
		break;
	default:
		break;
	}

	if(x>width || x< 1 || y>height || y<1)
		{gameover=true;}

	if(x==fruitx && y==fruity)
	{
		score++;
		fruitx=(rand()%width)+1;
	fruity=(rand()%height)+1;
	nTail++;
	}

for(int i=0;i< nTail;i++)
{
	if(tailX[i]==x && tailY[i]==y)
	{
		gameover=true;
	}
}

}

int main()
{
	setup();
	while(!gameover)
	{
		draw();
		input();
		logic();
	}
	getch();
	endwin();

	return 0;
}