#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>

#include "subfunction.h"
#include "subfunction.c"

CONSOLE_CURSOR_INFO cci;



void hidecursor()    //���ع��
{
    static char bFirst = 1;
    if (bFirst)
    {
        GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cci);
        bFirst = 0;
    }
    ++bFirst;
    CONSOLE_CURSOR_INFO c = cci;
    c.bVisible = 0;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &c);
}

void displaycursor()     //��ʾ���
{
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cci);
}

void setcursorpos(unsigned x, unsigned y)
{
    COORD pos;
    pos.X=x;
    pos.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
}


int main()
{
    srand(time(NULL));
    char c, board[8][8], human[8][8];
    printf("������A ���� B\nA .��ʼ����Ϸ B .������Ϸ\n");
loop:
    scanf("\n%c",&c);

    if(c == 65 || c == 97)
    {
        setcursorpos(0,3);
        printf("��Ϸ����ÿ��������ֻ�ܷ���һö���ӡ�ÿһö���Ӵ���һֻ����,�漰�Ķ������� (E)���� (T)��ʨ (L)���� (W)���� (D)��è (C)���� (S),ÿһ�ද��ӵ�и��Եĵȼ�,�ȼ�����˳��Ӹߵ��ס�\n\n��Ϸ��ʼʱ����ս��˫������ÿ�ֶ�����ֻ�������̵��·���ʾ B��ÿ�ֶ��������������A ��������������ŷ���������ĳЩ������,��Ӧ�ķ�������ʾһ�������ַ�,ʹ B ��֪��Ӧ�ķ������Ǻ��ֶ��B ����ʹ���ϡ��¡����Ҽ��ƶ���ɫ���鵽����ķ�����,���´����������ĸ�����ö������ӵ��÷����С���� B ���Ķ����� A ���Ķ��ﴦ�����ڵķ�����,��ߵȼ��Ķ��������͵ȼ��Ķ���,����������󡣱�����Ķ������������ʧ,����� B ���Ķ��ﱻ A������,�������·���Ӧ���������������,�������ȿ��ܳ�A������,�ֿ��ܱ���,���Ϊ�Ե�A�����塣B ��Ҳ���Խ���ɫ�����ƶ��������������ڵķ���,���¿ո��ѡ�и�����,Ȼ��ʹ���ϡ��¡����Ҽ��ƶ������ʵķ����к�,�ٴΰ��¿ո�����������������ӵ�Ŀ�귽����,������������ٷ��»��յ��塣�������ķ�ʽһֱ������Ϸ,ֱ��һ���Ķ��ﱻ��һ����ȫ����,����ʣ�����ӵ�һ����ʤ��������˫����ֻ��һö����ʣ��,��������ͬ�Ķ���,��ƽ�֡�\n");
        int i, j = 0;
        for(i = 0; i < 8; i++)
            for(j = 0; j < 8; j++)
                board[i][j] = ' ', human[i][j] = ' ';

        //��ӡ����
        printform(board);

        int deltax = 4, deltay = 2;
        int chessx = 0, chessy = 0, tagx, tagy;
        int judge[14] = {7, 7, 6, 6, 5, 5, 4, 4, 3, 3, 2, 2, 1, 1};

        //�����ļ� ����ϵͳʱ�䴴��
        FILE *fp = NULL;
        time_t timep;
        char name[256] = {0};
        time(&timep);//��ȡ��1970������˶����룬����time_t���͵�timep
        strftime(name, sizeof(name), "%Y.%m.%d-%H-%M-%S.txt",localtime(&timep) ); //���һ����������localtime������ת��Ϊstruct tm�ṹ��

        if((fp = fopen(name, "w")) == NULL)
        {
            printf("���ļ�ʧ��");
            perror("");
        }


        //���������
        for(i = 0; i < 14; i++)
        {
            chessx = rand()%8, chessy = rand()%8;
            tagx = 2  + chessy * deltax, tagy = 14 + chessx * deltay; //tagxΪ�����У�tagyΪ������
            if(board[chessx][chessy] == ' ')
            {
                board[chessx][chessy] = judge[i];
                setcursorpos(tagx, tagy);
                printf("��");
                fprintf(fp, "%d %d %d\n", chessx, chessy, board[chessx][chessy]);

                setcursorpos(tagx, tagy);
            }
            else i--;
        }


        int  x = 2, y = 14;
        setcursorpos(x, y), printf("�~");
        hidecursor();

        //���Ĺ���
        //��ѭ���ⶨ�壬�������¸�ֵ���ʼ��
        int humancount[7] = {2, 2, 2, 2, 2, 2, 2};  //��0��6Ϊm��e
        int comcount[7] = {2, 2, 2, 2, 2, 2, 2};  //��������������  //��7��1����ΪE��M
        char CarrySpace = ' ';
        int c[7] = {0};

        while (1)
        {

            //�ж�ʤ��
            int count1 = 0, count2 = 0; //count1 Ϊ com��count2 Ϊ hum
            int remhum = 0, remcom = 0;
            for(i = 0; i < 7; i++)
            {
                count1 += comcount[i], count2 += humancount[i];
                remcom = comcount[i], remhum = humancount[i];
            }
            if( (count1 == 0 && count2 != 0) || (count1 == 1 && count2 == 2 && remcom == remhum) )
            {
                system("pause");
                system("cls");
                printf("��������ʤ����\n�����Ϸ���̼������ļ�%s�У��ļ������㿪ʼ��Ϸ��ʱ�䣬����Ϸ����һ��Ŀ¼�£�", name);
                displaycursor();
                fclose(fp);
                return 0;
            }
            else if( (count1 != 0 && count2 == 0) || (count1 == 2 && count2 == 1 && remcom == remhum) )
            {
                system("pause");
                system("cls");
                printf("�˼���������\n�����Ϸ���̼������ļ�%s�У��ļ������㿪ʼ��Ϸ��ʱ�䣬����Ϸ����һ��Ŀ¼�£�", name);
                displaycursor();
                fclose(fp);
                return 0;
            }
            else if(count1 == count2 && remcom == remhum && count1 == remhum)
            {
                system("pause");
                system("cls");
                printf("���Ǵ��ƽ����\n�����Ϸ���̼������ļ�%s�У��ļ������㿪ʼ��Ϸ��ʱ�䣬����Ϸ����һ��Ŀ¼�£�", name);
                displaycursor();
                fclose(fp);
                return 0;
            }


            setcursorpos(0, 31);
            printf("�㻹�е���������E:%d  T:%d  L:%d  W:%d  D:%d  C:%d  S:%d", humancount[6], humancount[5], humancount[4], humancount[3], humancount[2], humancount[1], humancount[0]);

            int tag;
            int op = getch();  //����������������������Ҫ��������
            setcursorpos(0, 30);
            printf("                                                                                                                 ");  //�����ʾ
            setcursorpos(x, y);


            //����ƶ�
            //72 up
            //80 down
            //75 left
            //77 right
            if (op == 72 || op == 75 || op == 77 || op == 80)
            {
                chessy = (x - 2)/deltax, chessx = (y - 14)/deltay;

                if(board[chessx][chessy] != ' ')
                    printf("��"), setcursorpos(x, y);
                else if(human[chessx][chessy] != ' ')
                    printf("%c ", human[chessx][chessy]), setcursorpos(x, y);
                else printf("  "), setcursorpos(x, y);


                if (op == 72)
                {
                    if (y != 14 ) setcursorpos(x, y -= deltay);
                    printf("�~"), setcursorpos(x, y);
                }
                else if (op == 75)
                {
                    if (x != 2) setcursorpos(x -= deltax, y);
                    printf("�~"), setcursorpos(x, y);
                }

                else if (op == 77)
                {
                    if (x != 30) setcursorpos(x += deltax, y);
                    printf("�~"), setcursorpos(x, y);
                }
                else if (op == 80)
                {
                    if (y != 28) setcursorpos(x, y += deltay);
                    printf("�~"), setcursorpos(x, y);
                }
            }
            //101 e 69 E    //84 T 116 t
            //76 L 108 l    //119 w 87 W
            //68 D 100 d    //99 c  67 C
            //83 S 115 s    // 32 space
            else if(op == 101 || op == 69 || op == 84 || op == 116 || op == 76 || op == 108 || op == 119 || op == 87 || op == 68 || op == 100 || op == 99 || op == 67 || op == 83 || op == 115)  //op == 32
            {
                chessy = (x - 2)/deltax, chessx = (y - 14)/deltay;

                if(board[chessx][chessy] != ' ' || human[chessx][chessy] != ' ')
                {
                    setcursorpos(0, 30), printf("�����Ѿ���������");
                    continue;
                }

                if(op == 101 || op == 69)
                {
                    if(humancount[6] == 0 || humancount[6] == c[6])
                    {
                        setcursorpos(0, 30), printf("��û�����������");
                        continue;
                    }
                    op = 7, printf("E ");
                    human[chessx][chessy] = 'E';
                }
                if(op == 84 || op == 116)
                {
                    if(humancount[5] == 0 || humancount[5] == c[5])
                    {
                        setcursorpos(0, 30), printf("��û�����������");
                        continue;
                    }
                    op = 6, printf("T ");
                    human[chessx][chessy] = 'T';
                }
                if(op == 76 || op == 108)
                {
                    if(humancount[4] == 0 || humancount[4] == c[4])
                    {
                        setcursorpos(0, 30), printf("��û�����������");
                        continue;
                    }
                    op = 5, printf("L ");
                    human[chessx][chessy] = 'L';
                }
                if(op == 119 || op == 87)
                {
                    if(humancount[3] == 0 || humancount[3] == c[3])
                    {
                        setcursorpos(0, 30), printf("��û�����������");
                        continue;
                    }
                    op = 4, printf("W ");
                    human[chessx][chessy] = 'W';
                }
                if(op == 68 || op == 100)
                {
                    if(humancount[2] == 0 || humancount[2] == c[2])
                    {
                        setcursorpos(0, 30), printf("��û�����������");
                        continue;
                    }
                    op = 3, printf("D ");
                    human[chessx][chessy] = 'D';
                }
                if(op == 99 || op == 67)
                {
                    if(humancount[1] == 0 || humancount[1] == c[1])
                    {
                        setcursorpos(0, 30), printf("��û�����������");
                        continue;
                    }
                    op = 2, printf("C ");
                    human[chessx][chessy] = 'C';
                }
                if(op == 83 || op == 115)
                {
                    if(humancount[0] == 0 || humancount[0] == c[0])
                    {
                        setcursorpos(0, 30), printf("��û�����������");
                        continue;
                    }
                    op = 1, printf("S ");
                    human[chessx][chessy] = 'S';
                }

                //�� (E)���� (T)��ʨ (L)���� (W)���� (D)��è (C) ���� (S) S�������E

                if(op > board[chessx][chessy - 1] && (chessy - 1) >= 0 && board[chessx][chessy - 1] != ' ' && !(op == 7 && board[chessx][chessy - 1] == 1) || op == 1 && board[chessx][chessy - 1] == 7)
                {
                    setcursorpos(x - 1 - deltax, y), printf("   ");
                    setcursorpos(0, 30), printf("��Ե��Է�һ������");

                    fprintf(fp, "1 %d %d %d 1\n", op, chessx, chessy);  //1 ��������  op��¼��������  ���һ��1��ʾ�Ե��˶Է�������

                    tag = board[chessx][chessy - 1];
                    calcom(tag, comcount);
                    CcountPlus(op, c);

                    board[chessx][chessy - 1] = ' ';
                    continue;
                }
                else if(op > board[chessx][chessy + 1] && (chessy + 1) < 8 && board[chessx][chessy + 1] != ' ' && !(op == 7 && board[chessx][chessy + 1] == 1) || op == 1 && board[chessx][chessy + 1] == 7)
                {
                    setcursorpos(x - 1 + deltax, y), printf("   ");
                    setcursorpos(0, 30), printf("��Ե��˶Է�һ������");

                    fprintf(fp, "1 %d %d %d 1\n", op, chessx, chessy);

                    tag = board[chessx][chessy + 1];
                    calcom(tag, comcount);
                    CcountPlus(op, c);

                    board[chessx][chessy + 1] = ' ';
                    continue;
                }
                else if(op > board[chessx - 1][chessy] && (chessx - 1) >= 0 && board[chessx - 1][chessy] != ' ' && !(op == 7 && board[chessx - 1][chessy] == 1) || op == 1 && board[chessx - 1][chessy] == 7)
                {

                    setcursorpos(x - 1, y - deltay), printf("   ");
                    setcursorpos(0, 30), printf("��Ե��˶Է�һ������");

                    fprintf(fp, "1 %d %d %d 1\n", op, chessx, chessy);  //1 ��������  op��¼��������

                    tag = board[chessx - 1][chessy];
                    calcom(tag, comcount);
                    CcountPlus(op, c);

                    board[chessx - 1][chessy] = ' ';
                    continue;

                }
                else if(op > board[chessx + 1][chessy] && (chessx + 1) < 8 && board[chessx + 1][chessy] != ' ' && !(op == 7 && board[chessx + 1][chessy] == 1)|| op == 1 && board[chessx + 1][chessy] == 7)
                {
                    setcursorpos(x - 1, y + deltay), printf("   ");
                    setcursorpos(0, 30), printf("��Ե��˶Է�һ������");

                    fprintf(fp, "1 %d %d %d 1\n", op, chessx, chessy);  //1 ��������  op��¼��������

                    tag = board[chessx + 1][chessy];
                    calcom(tag, comcount);
                    CcountPlus(op, c);

                    board[chessx + 1][chessy] = ' ';
                    continue;
                }


                //����������ӳԵ���ҵ�����
                else if(op < board[chessx][chessy - 1] && (chessy - 1) >= 0 && board[chessx][chessy - 1] != ' '|| op == 7 && board[chessx][chessy - 1] == 1)
                {
                    calhum(op, humancount);
                    human[chessx][chessy] = ' ';
                    setcursorpos(0, 30), printf("������������ӱ��Ե���");
                    setcursorpos(x, y), printf("�~");

                    fprintf(fp, "1 %d %d %d 0\n", op, chessx, chessy);  //1�������� op���µ����� 0������ӱ��Ե�
                    continue;
                }
                else if(op < board[chessx][chessy + 1] && (chessy + 1) < 8 && board[chessx][chessy + 1] != ' '|| op == 7 && board[chessx][chessy + 1] == 1)
                {
                    calhum(op, humancount);
                    human[chessx][chessy] = ' ';
                    setcursorpos(0, 30), printf("������������ӱ��Ե���");
                    setcursorpos(x, y), printf("�~");

                    fprintf(fp, "1 %d %d %d 0\n", op, chessx, chessy);
                    continue;
                }
                else if(op < board[chessx - 1][chessy] && (chessx - 1) >= 0 && board[chessx - 1][chessy] != ' '|| op == 7 && board[chessx - 1][chessy] == 1)
                {
                    calhum(op, humancount);
                    human[chessx][chessy] = ' ';
                    setcursorpos(0, 30), printf("������������ӱ��Ե���");
                    setcursorpos(x, y), printf("�~");

                    fprintf(fp, "1 %d %d %d 0\n", op, chessx, chessy);
                    continue;
                }
                else if(op < board[chessx + 1][chessy] && (chessx + 1) < 8 && board[chessx + 1][chessy] != ' '|| op == 7 && board[chessx + 1][chessy] == 1)
                {
                    calhum(op, humancount);
                    human[chessx][chessy] = ' ';
                    setcursorpos(0, 30), printf("������������ӱ��Ե���");
                    setcursorpos(x, y), printf("�~");

                    fprintf(fp, "1 %d %d %d 0\n", op, chessx, chessy);
                    continue;
                }
                fprintf(fp, "1 %d %d %d 2\n", op, chessx, chessy);  //2 û�г���򱻳�
                CcountPlus(op, c);
            }
            else if(op == 32)
            {
                chessy = (x - 2)/deltax, chessx = (y - 14)/deltay;
                if(human[chessx][chessy] == ' ' && board[chessx][chessy] == ' ' || board[chessx][chessy] != ' ')
                {
                    if(CarrySpace != ' ' && board[chessx][chessy] == ' ')
                    {
                        if(CarrySpace == 'E')
                        {
                            if(humancount[6] == 0 || humancount[6] == c[6])
                            {
                                setcursorpos(0, 30), printf("��û������������");
                                CarrySpace = ' ';
                                continue;
                            }
                            op = 7;
                        }
                        if(CarrySpace == 'T')
                        {
                            if(humancount[5] == 0 || humancount[5] == c[5])
                            {
                                setcursorpos(0, 30), printf("��û������������");
                                CarrySpace = ' ';
                                continue;
                            }
                            op = 6;
                        }
                        if(CarrySpace == 'L')
                        {
                            if(humancount[4] == 0 || humancount[4] == c[4])
                            {
                                setcursorpos(0, 30), printf("��û������������");
                                CarrySpace = ' ';
                                continue;
                            }
                            op = 5;
                        }
                        if(CarrySpace == 'W')
                        {
                            if(humancount[3] == 0 || humancount[3] == c[3])
                            {
                                setcursorpos(0, 30), printf("��û������������");
                                CarrySpace = ' ';
                                continue;
                            }
                            op = 4;
                        }
                        if(CarrySpace == 'D')
                        {
                            if(humancount[2] == 0 || humancount[2] == c[2])
                            {
                                setcursorpos(0, 30), printf("��û������������");
                                CarrySpace = ' ';
                                continue;
                            }
                            op = 3;
                        }
                        if(CarrySpace == 'C')
                        {
                            if(humancount[1] == 0 || humancount[1] == c[1])
                            {
                                setcursorpos(0, 30), printf("��û������������");
                                CarrySpace = ' ';
                                continue;
                            }
                            op = 2;
                        }
                        if(CarrySpace == 'S')
                        {
                            if(humancount[0] == 0 || humancount[0] == c[0])
                            {
                                setcursorpos(0, 30), printf("��û������������");
                                CarrySpace = ' ';
                                continue;
                            }
                            op = 1;
                        }
                        human[chessx][chessy] = CarrySpace;
                        CarrySpace = ' ';

                        if(op > board[chessx][chessy - 1] && (chessy - 1) >= 0 && board[chessx][chessy - 1] != ' ' && !(op == 7 && board[chessx][chessy - 1] == 1) || op == 1 && board[chessx][chessy - 1] == 7)
                        {
                            setcursorpos(x - 1 - deltax, y), printf("   ");
                            setcursorpos(0, 30), printf("��Ե��Է�һ������");

                            fprintf(fp, "1 %d %d %d 1\n", op, chessx, chessy);  //1 ��������  op��¼��������  ���һ��1��ʾ�Ե��˶Է�������

                            tag = board[chessx][chessy - 1];
                            calcom(tag, comcount);
                            CcountPlus(op, c);

                            board[chessx][chessy - 1] = ' ';
                            continue;
                        }
                        else if(op > board[chessx][chessy + 1] && (chessy + 1) < 8 && board[chessx][chessy + 1] != ' ' && !(op == 7 && board[chessx][chessy + 1] == 1) || op == 1 && board[chessx][chessy + 1] == 7)
                        {
                            setcursorpos(x - 1 + deltax, y), printf("   ");
                            setcursorpos(0, 30), printf("��Ե��˶Է�һ������");

                            fprintf(fp, "1 %d %d %d 1\n", op, chessx, chessy);

                            tag = board[chessx][chessy + 1];
                            calcom(tag, comcount);
                            CcountPlus(op, c);

                            board[chessx][chessy + 1] = ' ';
                            continue;
                        }
                        else if(op > board[chessx - 1][chessy] && (chessx - 1) >= 0 && board[chessx - 1][chessy] != ' ' && !(op == 7 && board[chessx - 1][chessy] == 1) || op == 1 && board[chessx - 1][chessy] == 7)
                        {

                            setcursorpos(x - 1, y - deltay), printf("   ");
                            setcursorpos(0, 30), printf("��Ե��˶Է�һ������");

                            fprintf(fp, "1 %d %d %d 1\n", op, chessx, chessy);  //1 ��������  op��¼��������

                            tag = board[chessx - 1][chessy];
                            calcom(tag, comcount);
                            CcountPlus(op, c);

                            board[chessx - 1][chessy] = ' ';
                            continue;
                        }
                        else if(op > board[chessx + 1][chessy] && (chessx + 1) < 8 && board[chessx + 1][chessy] != ' ' && !(op == 7 && board[chessx + 1][chessy] == 1)|| op == 1 && board[chessx + 1][chessy] == 7)
                        {
                            setcursorpos(x - 1, y + deltay), printf("   ");
                            setcursorpos(0, 30), printf("��Ե��˶Է�һ������");

                            fprintf(fp, "1 %d %d %d 1\n", op, chessx, chessy);  //1 ��������  op��¼��������

                            tag = board[chessx + 1][chessy];
                            calcom(tag, comcount);
                            CcountPlus(op, c);

                            board[chessx + 1][chessy] = ' ';
                            continue;
                        }


                        //����������ӳԵ��û�������
                        else if(op < board[chessx][chessy - 1] && (chessy - 1) >= 0 && board[chessx][chessy - 1] != ' '|| op == 7 && board[chessx][chessy - 1] == 1)
                        {
                            calhum(op, humancount);
                            human[chessx][chessy] = ' ';
                            setcursorpos(x, y), printf("  ");

                            fprintf(fp, "1 %d %d %d 0\n", op, chessx, chessy);  //1�������� op���µ����� 0������ӱ��Ե�
                            continue;
                        }
                        else if(op < board[chessx][chessy + 1] && (chessy + 1) < 8 && board[chessx][chessy + 1] != ' '|| op == 7 && board[chessx][chessy + 1] == 1)
                        {
                            calhum(op, humancount);
                            human[chessx][chessy] = ' ';
                            setcursorpos(x, y), printf("  ");

                            fprintf(fp, "1 %d %d %d 0\n", op, chessx, chessy);
                            continue;
                        }
                        else if(op < board[chessx - 1][chessy] && (chessx - 1) >= 0 && board[chessx - 1][chessy] != ' '|| op == 7 && board[chessx - 1][chessy] == 1)
                        {
                            calhum(op, humancount);
                            human[chessx][chessy] = ' ';
                            setcursorpos(x, y), printf("  ");

                            fprintf(fp, "1 %d %d %d 0\n", op, chessx, chessy);
                            continue;
                        }
                        else if(op < board[chessx + 1][chessy] && (chessx + 1) < 8 && board[chessx + 1][chessy] != ' '|| op == 7 && board[chessx + 1][chessy] == 1)
                        {
                            calhum(op, humancount);
                            human[chessx][chessy] = ' ';
                            setcursorpos(x, y), printf("  ");

                            fprintf(fp, "1 %d %d %d 0\n", op, chessx, chessy);
                            continue;
                        }
                        CcountPlus(op, c);
                    }
                    else if(CarrySpace != ' ' && board[chessx][chessy] != ' ')
                        setcursorpos(0, 30), printf("���ﲻ�ܷ�������");
                    else  setcursorpos(0, 30), printf("����û�п��Ի��յ�����");
                }
                else
                {
                    CarrySpace = human[chessx][chessy];

                    if(CarrySpace == 'E') op = 7, CcountMinus(op, c);
                    if(CarrySpace == 'T') op = 6, CcountMinus(op, c);
                    if(CarrySpace == 'L') op = 5, CcountMinus(op, c);
                    if(CarrySpace == 'W') op = 4, CcountMinus(op, c);
                    if(CarrySpace == 'D') op = 3, CcountMinus(op, c);
                    if(CarrySpace == 'C') op = 2, CcountMinus(op, c);
                    if(CarrySpace == 'S') op = 1, CcountMinus(op, c);

                    human[chessx][chessy] = ' ';
                    printf("  ");
                    setcursorpos(0, 30), printf("�������һ�����������ٴΰ��¿ո������������ӣ����������գ����ٴλس�ֻ�������һ�λ��յ��壩");
                    setcursorpos(x, y), printf("�~");
                    fprintf(fp, "0 %d %d %d 2\n", op, chessx, chessy);
                }
            }
            else
            {
                setcursorpos(0, 30), printf("���·�����Ե�����������ĸ��ѡ����Ҫ�µ�����");
                setcursorpos(x, y);
                continue;
            }
        }
    }



    else if(c == 66 || c == 98) //�������B/bʱ
    {
        while(getchar() != '\n')
            continue;

        setcursorpos(0, 3);
        printf("������Ҫ�򿪵��ļ���(�ļ���Ϊ�㿪ʼ��Ϸ��ʱ��):");
        char name[100];
        scanf("%s", name);

        hidecursor();

        int put[100], opr[100], chessxx[100], chessyy[100], e[100];
        int chessx = 0, chessy = 0;
        int deltax = 4, deltay = 2;
        int i = 0, n = 0;
        char board[8][8] = {' '};

        FILE *fp;
        fp=fopen(name,"r");

        if(fp == NULL)  //���ļ�
        {
            printf("���ļ�ʧ��\n");
            exit(1);
        }

        while(!feof(fp))
        {
            while(i < 14)
            {
                fscanf(fp,"%d %d %d", &chessxx[i], &chessyy[i], &opr[i]);
                i++;
            }
            while(i > 13 && !feof(fp))
            {
                fscanf(fp,"%d %d %d %d %d", &put[i], &opr[i], &chessxx[i], &chessyy[i], &e[i]);
                i++;
            }
        }

        n = i;
        i = 14;
        printform(board);

        int x = 0, y = 0;
        //���ݶ�ȡ��������
        for(i = 0; i < 14; i++)
        {
            chessx = chessxx[i], chessy = chessyy[i];
            board[chessx][chessy] = opr[i];

            x = 2  + chessy * deltax, y = 14 + chessx * deltay;
            PrintLetterBoard(opr[i], x, y);
        }

        //�����������
        x = 2, y = 14;
        int humancount[7] = {2, 2, 2, 2, 2, 2, 2};  //��0��6Ϊm��e
        int comcount[7] = {2, 2, 2, 2, 2, 2, 2};  //��������������  //��7��1����ΪE��M



        int tag;
        while(1)
        {
            setcursorpos(0, 6);
            printf("�������¼�������\n");
            printf("�㻹�е���������E:%d  T:%d  L:%d  W:%d  D:%d  C:%d  S:%d", humancount[6], humancount[5], humancount[4], humancount[3], humancount[2], humancount[1], humancount[0]);
            printf("\ncomputer's chess : E:%d  T:%d  L:%d  W:%d  D:%d  C:%d  S:%d", comcount[6], comcount[5], comcount[4], comcount[3], comcount[2], comcount[1], comcount[0]);

            int op = getch();
            printf("\n\n                                                                                  ");

            chessx = chessxx[i], chessy = chessyy[i];
            x = 2  + chessy * deltax, y = 14 + chessx * deltay;

            if(i == n - 1)
            {
                setcursorpos(0, 10), printf("                                                               ");
                setcursorpos(0, 10), printf("������ɣ�");
                displaycursor();
                break;
            }

            if(op == 80)
            {
                op = opr[i];
                setcursorpos(x, y), printf("%c", Changeop(op));

                if(put[i] == 1)
                {
                    if(e[i] == 1)
                    {
                        if(op > board[chessx][chessy - 1] && (chessy - 1) >= 0 && board[chessx][chessy - 1] != ' ' && !(op == 7 && board[chessx][chessy - 1] == 1) || op == 1 && board[chessx][chessy - 1] == 7)
                        {

                            setcursorpos(x - 1 - deltax, y), printf("   ");
                            setcursorpos(0, 10), printf("�������������%d��%d�У����Ե��˶Է�һ����", chessx + 1, chessy + 1);

                            tag = board[chessx][chessy - 1];
                            calcom(tag, comcount);

                            board[chessx][chessy - 1] = ' ';
                        }
                        else if(op > board[chessx][chessy + 1] && (chessy + 1) < 8 && board[chessx][chessy + 1] != ' ' && !(op == 7 && board[chessx][chessy + 1] == 1) || op == 1 && board[chessx][chessy + 1] == 7)
                        {
                            setcursorpos(x - 1 + deltax, y), printf("   ");
                            setcursorpos(0, 10), printf("�������������%d��%d�У����Ե��˶Է�һ����", chessx + 1, chessy + 1);

                            tag = board[chessx][chessy + 1];
                            calcom(tag, comcount);

                            board[chessx][chessy + 1] = ' ';
                        }
                        else if(op > board[chessx - 1][chessy] && (chessx - 1) >= 0 && board[chessx - 1][chessy] != ' ' && !(op == 7 && board[chessx - 1][chessy] == 1) || op == 1 && board[chessx - 1][chessy] == 7)
                        {
                            setcursorpos(x - 1, y - deltay), printf("   ");
                            setcursorpos(0, 10), printf("�������������%d��%d�У����Ե��˶Է�һ����", chessx + 1, chessy + 1);

                            tag = board[chessx - 1][chessy];
                            calcom(tag, comcount);

                            board[chessx - 1][chessy] = ' ';
                        }
                        else if(op > board[chessx + 1][chessy] && (chessx + 1) < 8 && board[chessx + 1][chessy] != ' ' && !(op == 7 && board[chessx + 1][chessy] == 1)|| op == 1 && board[chessx + 1][chessy] == 7)
                        {
                            setcursorpos(x - 1, y + deltay), printf("   ");
                            setcursorpos(0, 10), printf("�������������%d��%d�У����Ե��˶Է�һ����", chessx + 1, chessy + 1);

                            tag = board[chessx + 1][chessy];
                            calcom(tag, comcount);

                            board[chessx + 1][chessy] = ' ';
                        }
                        i++;
                        continue;
                    }

                    if(e[i] == 0)
                    {
                        //����������ӳԵ���ҵ�����
                        if(op < board[chessx][chessy - 1] && (chessy - 1) >= 0 && board[chessx][chessy - 1] != ' '|| op == 7 && board[chessx][chessy - 1] == 1)
                        {
                            calhum(op, humancount);
                            setcursorpos(x, y), printf("  ");
                            human[chessx][chessy] = ' ';
                        }
                        else if(op < board[chessx][chessy + 1] && (chessy + 1) < 8 && board[chessx][chessy + 1] != ' '|| op == 7 && board[chessx][chessy + 1] == 1)
                        {
                            calhum(op, humancount);
                            setcursorpos(x, y), printf("  ");
                            human[chessx][chessy] = ' ';
                        }
                        else if(op < board[chessx - 1][chessy] && (chessx - 1) >= 0 && board[chessx - 1][chessy] != ' '|| op == 7 && board[chessx - 1][chessy] == 1)
                        {
                            calhum(op, humancount);
                            setcursorpos(x, y), printf("  ");
                            human[chessx][chessy] = ' ';
                        }
                        else if(op < board[chessx + 1][chessy] && (chessx + 1) < 8 && board[chessx + 1][chessy] != ' '|| op == 7 && board[chessx + 1][chessy] == 1)
                        {
                            calhum(op, humancount);
                            setcursorpos(x, y), printf("  ");
                            human[chessx][chessy] = ' ';
                        }
                        setcursorpos(0, 10);
                        printf("�����%c������%d��%d�У������Ե���", Changeop(op), chessx + 1, chessy + 1);
                        i++;
                        continue;
                    }
                    setcursorpos(0, 10);
                    printf("�����%c������%d��%d��", Changeop(op), chessx + 1, chessy + 1);
                    i++;
                    continue;
                }
                if(put[i] == 0)
                {
                    setcursorpos(0, 10), printf("���������%d��%d�е���%c", chessx + 1, chessy + 1, Changeop(op) );
                    setcursorpos(x, y), printf("  ");
                    i++;
                }
            }
        }
        return 0;
    }

    else
    {
        setcursorpos(0, 2);
        printf("����������:                                ");
        setcursorpos(11, 2);
        goto loop;
    }
}
