#include<stdio.h>
#include<string.h>
#include<stdlib.h>
struct player
{
    int score;
    char name[20];
};
typedef struct player Player;
struct b
{
    int position;
    int taken;
    char peice;
};typedef struct b Board;
void input_names(Player **p1,Player **p2)
{
    (*p1)=malloc(sizeof(struct player));
    (*p2)=malloc(sizeof(struct player));
    printf("Enter the name of player1:");
    scanf("%s",(*p1)->name);
    printf("Enter the name of player2:");
    scanf("%s",(*p2)->name);
    (*p1)->score=0;
    (*p2)->score=0;
}
void toss(Player **p1,Player **p2)
{
    Player *temp;
    if((rand()%2)){
        temp=*p1;
        *p1=*p2;
        *p2=temp;
    }
}
void init(Board b[3][3])
{
    int i,j;
    for(i=0;i<3;i++)
        for(j=0;j<3;j++)
        {
            b[i][j].position=i*3+j+1;
            b[i][j].taken=0;
            b[i][j].peice=0;
        }
}
void output(Board b[3][3],char mode)
{
    int i,j;	
    printf("Board:\n");
    for(i=0;i<3;i++)
    {
        for(j=0;j<3;j++)
	{
	    if(b[i][j].taken==1)
               	printf("%c  ",b[i][j].peice);
	    else
		printf("   ");
        }
        printf("\n");
    }
    if(mode!='m')
    {
 	printf("remaining positions:\n");
    	for(i=0;i<3;i++)
    	{
        	for(j=0;j<3;j++)
        	{
        	    if((b[i][j].taken)!=1) printf("%d  ",b[i][j].position);
		    else printf("   ");
        	}
        	printf("\n");
    	}
    }
}
int play_input(Board b[3][3],Player *p)
{
    int pos;
    printf("Enter the position for %s:",p->name);
    while(1)
    {
        scanf("%d",&pos);
        if(((b[(pos-1)/3][(pos-1)%3].taken)==0)&&(pos>=1&&pos<=9)) return pos;
        else printf("Wrong choice!\nTry again:");
    }
    return -1;
}
void plot(Board b[3][3],int p,char sym)
{
    b[(p-1)/3][(p-1)%3].taken=1;
    b[(p-1)/3][(p-1)%3].peice=sym;
}
int horizontal(Board b[3][3],int p,char sym)
{
    int i;
    for(i=0;i<3;i++)
        if(b[p][i].peice!=sym) return 0;
    return 1;
}
int vertical(Board b[3][3],int p,char sym)
{
    int i;
    for(i=0;i<3;i++)
        if(b[i][p].peice!=sym) return 0;
    return 1;
}
int pdiagonal(Board b[3][3],char sym)
{
    int i;
    for(i=0;i<3;i++)
        if(b[i][i].peice!=sym) return 0;
    return 1;
}
int sdiagonal(Board b[3][3],char sym)
{
    int i,j;
    for(i=0,j=2;i<3&&j>=0;i++,j--)
        if(b[i][j].peice!=sym) return 0;
    return 1;
}

int check(Board b[3][3],int pos,char sym)
{
    int match=0;
    if(!(pos%2))
        match=(horizontal(b,(pos-1)/3,sym)||vertical(b,(pos-1)%3,sym));
    else
    {
        match=(horizontal(b,(pos-1)/3,sym)||vertical(b,(pos-1)%3,sym));
        if(match==1) return match;
        if(((pos-1)/3)==(pos-1)%3)
            match=pdiagonal(b,sym);
        else
            match=sdiagonal(b,sym);
        if(match==1) return match;
        if(pos==5)
            match=sdiagonal(b,sym);
    }
    return match;
}
void print(Player *p1,Player *p2)
{
	printf("Details:\n");
	printf("Player1:\n");
	printf("Name:%s\tScore:%d\n",p1->name,p1->score);
	printf("Player2:\n");
	printf("Name:%s\tScore:%d\n",p2->name,p2->score);
}
int gameplay(Player *p1,Player *p2)
{
    int count=0,pos,win;
    Board board[3][3];
    Player *p;
    char sym;
    init(board);
    while(count<9)
    {
	system("clear");
	print(p1,p2);
        output(board,'g');
        if(count%2) {p=p2; sym='O';}
        else {p=p1; sym='X';}
        pos=play_input(board,p);
        count++;
        plot(board,pos,sym);
        if(count>=5)
	{
		win=check(board,pos,sym);
        	if((win)&&(count%2))
		{
			printf("Final ");
			output(board,'m');		
			return 0;
		}
        	else if(win) 
		{
			printf("Final ");
			output(board,'m');
			return 1;
		}
	}
    }
    printf("Final ");
    output(board,'m');
    return -1;
}
void score(Player *p1,Player *p2,int winner)
{
    if(winner==1)
    {
	printf("%s won this board!\n",p2->name);
        (p2->score)++;
    }
    else if(winner==0)
    {
	printf("%s won this board!\n",p1->name);
        (p1->score)++;
    }
    else
	printf("Draw!\n");
}
int main()
{
    int play=1,winner;
    Player *p1,*p2;
    input_names(&p1,&p2);
    while(play)
    {
        toss(&p1,&p2);
        winner=gameplay(p1,p2); //winner = 0,player1 wins else if 1, player2 wins and -1 draw        
	score(p1,p2,winner);
        printf("Wanna play again?,1:play 0:quit\n");
	printf("Enter the choice:");
        scanf("%d",&play);
    }
    system("clear");
    printf("Result:\n");
    print(p1,p2);
    printf("\nThe winner is:");
    if(p1->score>p2->score) printf("%s!!!\n",p1->name);
    else if(p2->score>p1->score) printf("%s!!!\n",p2->name);
    else printf("Draw\n");
    return 0;
}
