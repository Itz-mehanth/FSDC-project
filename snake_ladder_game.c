#include <stdio.h>
#include <stdlib.h>
//function to print the snake_home page
void snake_home(int input){
        printf("\n-----------------------------------------------------------------------------\n");
        printf("                SNAKE AND LADDER\n");
        printf("Snakes:- 47 to 23    89 to 45    99 to 55\n");
        printf("Ladders:-28 to 56    45 to 76     78 to 89\n");
        if(input==1)
        printf("Player 1 plays\n");
        else if(input==2)
        printf("Player 2 plays\n");
    }

void displayBoard(int diceres,char player[]){
    int i=100;
    while(i>0){
        if(i%10==0){
            printf("\n\n");
        }
        if (i==diceres)
        {
            printf("(%s)\t",player);
        }else{
            printf("%d\t",i);
        }
        i--;      
    }
}
int snake_ladder_game()
{
    char c;
    int input=1,temp_rand,randomp1=0,randomp2=0;
    char p1[10]="P1",p2[10]="P2";
    displayBoard(0,NULL);
    while (1)
    {   
        snake_home(input);
        B:
        if(input==1){
            printf("Press Enter to throw the dice\n");
            c = getchar();
            if (c != '\n')
            {
                return 0;
            }
            
        }
        A:temp_rand=rand()%7;
        if(temp_rand==0){goto A;}
        if(input==1)
            printf("You got %d !\n",temp_rand);
        else if(input ==2)
            printf("Your opponent got %d !\n",temp_rand);
        getchar();
        system("cls");
        if(input==1){
            if (randomp1+temp_rand<=100)
            {
                randomp1+=temp_rand;
            }
            displayBoard(randomp1,p1);
            input=2;
        }else if (input==2)
        {
            if (randomp2+temp_rand<=100)
            {
                randomp2+=temp_rand;
            }
            displayBoard(randomp2,p2);
            input=1;
        }else{
            printf("Print a valid input");
        }

        switch (randomp1)
        {
        case 47:
            randomp1=23;
            printf("\n->You have bitten by a snake\n");
            break;
        case 89:
            randomp1=45;
            printf("\n->You have bitten by a snake\n");
            break;
        case 99:
            randomp1=55;
            printf("\n->You have bitten by a snake\n");
            break;
        case 28:
            randomp1=56;
            printf("\n->You got a ladder\n");
            break;
        case 45:
            randomp1=76;
            printf("\n->You got a ladder\n");
            break;
        case 78:
            randomp1=89;
            printf("\n->You got a ladder\n");
            break;
        
        default:
            break;
        }

        switch (randomp1)
        {
        case 47:
            randomp1=23;
            printf("\n->You have bitten by a snake\n");
            break;
        case 89:
            randomp1=45;
            printf("\n->You have bitten by a snake\n");
            break;
        case 99:
            randomp1=55;
            printf("\n->You have bitten by a snake\n");
            break;
        case 28:
            randomp1=56;
            printf("\n->You got a ladder\n");
            break;
        case 45:
            randomp1=76;
            printf("\n->You got a ladder\n");
            break;
        case 78:
            randomp1=89;
            printf("\n->You got a ladder\n");
            break;
        
        default:
            break;
        }
        
        if (randomp1==100)
        {
            printf("CONGRATULATIONS PLAYER 1 WON THE MATCH");
            return 0;
        }else if (randomp2==100)
        {
            printf("CONGRATULATIONS PLAYER 2 WON THE MATCH");
            return 0;
        }
    }
    
    
    

    return 0;
}
