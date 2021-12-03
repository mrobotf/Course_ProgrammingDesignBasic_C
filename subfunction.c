#include <stdio.h>
#include <stdlib.h>
#include "subfunction.h"


void printform(char (*board)[8])
{
    int i = 0, j = 0, boardi = 0, boardj = 0;
    setcursorpos(0, 13);
    for(i = 0; i < 17; i++)
    {
        if(i == 0)
        {
            for(j = 0; j < 17; j++)
            {
                if(j == 0) printf("��");
                else if(j == 16) printf("��");
                else if(j%2 != 0)  printf("������");
                else  printf("��");
            }
            printf("\n");
        }
        else if(i == 16)    //�������һ��
        {
            for(j = 0; j < 17; j++)
            {
                if(j == 0) printf("��");
                else if(j == 16) printf("��");
                else if(j%2 != 0)  printf("������");
                else  printf("��");
            }
            printf("\n");
        }
        else if(i%2 == 0)
        {
            for(j = 0; j < 17; j++)
            {
                if(j == 0)  printf("��");
                else if(j == 16)  printf("��\n");
                else if(j%2 != 0)  printf("������");
                else if(j%2 == 0)  printf("��");
            }
        }
        else
        {
            for(j = 0, boardj = 0; j < 17; j++)
            {
                if(j%2 == 0)  printf("��");
                else
                    printf(" %c ", board[boardi][boardj]), boardj++;
            }
            printf("\n");
            boardi++;
        }
    }
}

void calcom(int Tag, int com[])
{
    int i;
    char compare[7] = {1, 2, 3, 4, 5, 6, 7};
    for(i = 0; i < 7; i++)
    {
        if(i + 1 == Tag)
        {
            --com[i];
            break;
        }
    }
}

void calhum(int Tag, int hum[])
{
    int i;
    for(i = 0; i < 7; i++)
    {
        if(i + 1 == Tag)
        {
            hum[i]--;
            break;
        }
    }
}

void PrintLetter(int op)
{
    char a[7] = {'E', 'T', 'L', 'W', 'D', 'C', 'S'};
    int b[7] = {7, 6, 5, 4, 3, 2, 1};
    int i = 0;
    for(; i < 7; i++)
        if(b[i] == op)
        {
            printf("%c ", a[i]);
            break;
        }
}

void PrintLetterBoard(int op, int x, int y)
{
    char a[7] = {'E', 'T', 'L', 'W', 'D', 'C', 'S'};
    int b[7] = {7, 6, 5, 4, 3, 2, 1};
    int i = 0;
    for(i = 0; i < 7; i++)
        if(b[i] == op)
        {
            setcursorpos(x, y);
            printf("%c!", a[i]);
            break;
        }
}




void CcountMinus(int op, int c[])
{
    int i = 0;
    for(i = 0; i < 7; i++)
    {
        if(i + 1 == op)
            c[i]--;
    }
}

void CcountPlus(int op, int c[])
{
    int i = 0;
    for(i = 0; i < 7; i++)
    {
        if(i + 1 == op)
            c[i]++;
    }
}





char Changeop(int op)
{
    char a[7] = {'S', 'C', 'D', 'W', 'L', 'T', 'E'};
    int i;
    for(i = 0; i < 7; i++)
        if(i + 1 == op)
        return a[i];
}
