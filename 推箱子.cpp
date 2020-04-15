#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <Windows.h>    // µ¯³ö¶Ô»°¿ò
/*
    0: ¿ÕµØ
    1: Ä¿µÄµØ   ¡î
    2: Ç½±Ú     ¡ö 
    4: Ïä×Ó     ¨ˆ
    8: Íæ¼Ò     ¡â
    16: Ïä×Óµ½´ïÄ¿µÄµØ  ¡ï
*/
int map[20][20] = {
    {0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0},
    {0, 0, 0, 0, 2, 0, 0, 0, 0, 2, 0, 0, 0, 0},
    {0, 2, 2, 2, 2, 0, 0, 4, 4, 2, 2, 2, 2, 2},
    {0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 2},
    {0, 2, 0, 4, 0, 0, 0, 4, 0, 0, 0, 4, 0, 2},
    {0, 2, 0, 0, 0, 2, 2, 0, 2, 2, 2, 2, 2, 2},
    {2, 2, 2, 2, 4, 2, 2, 0, 0, 0, 0, 0, 0, 2},
    {2, 0, 0, 0, 4, 0, 2, 0, 0, 0, 8, 0, 0, 2},
    {2, 0, 4, 0, 4, 0, 2, 0, 2, 2, 2, 2, 2, 2},
    {2, 2, 0, 0, 4, 0, 2, 0 ,2, 1, 1, 1, 2, 0},
    {0, 2, 0, 2, 0, 0, 0, 0, 0, 1, 1, 1, 2, 0},
    {0, 2, 0, 0, 0, 0, 2, 2, 1, 1, 1, 1, 2, 0},
    {0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0}
};
// Ä¿±êµã
int tarPos[][2] = {
    {9, 9},
    {9, 10},
    {9, 11},
    {10, 9},
    {10, 10},
    {10, 11},
    {11, 8},
    {11, 9},
    {11, 10},
    {11, 11}
};
char key = 0;   // ´æ´¢ÓÃ»§µÄ°´¼ü
int row = 0, column = 0;    // ÈËÎïÔÚµÚ¼¸ÐÐ£¬µÚ¼¸ÁÐ
int oldType = 0;    // ÈËÎïÕ¾×ÅµÄµØ·½Ô­À´ÊÇÊ²Ã´µØÃæ
int oldBoxType = 0; // Ïä×ÓÕ¾×ÅµÄµØ·½Ô­À´ÊÇÊ²Ã´µØÃæ 
// »­µØÍ¼·½·¨
void DrawMap() {
    for (int i = 0; i < sizeof(map) / sizeof(map[0]); i++)
    {
        for (int j = 0; j < sizeof(map[0]) / sizeof(map[0][0]); j++)
        {
            switch (map[i][j])
            {
            case 0:
                printf("  ");
                break;
            case 1:
                printf("¡î");
                break;
            case 2:
                printf("¡ö");
                break;
            case 4:
                printf("¨ˆ");
                break;
            case 8:
                printf("¡â");
                row = i;
                column = j;
                break;
            case 16:
                printf("¡ï");
                break;
            }
        }
        printf("\n");
    }
}
void Move(int r, int c)
{
    if (map[row + r][column + c] != 2)  // Èç¹ûÇ°Ãæ²»ÊÇÇ½±ÚµÄ»°£¬¾Í¿ÉÒÔÒÆ¶¯
    {
        if (map[row + r][column + c] == 4 || map[row + r][column + c] == 16)    // Èç¹ûÓöµ½Ïä×ÓµÄ´¦Àí°ì·¨
        {
            if (map[row + 2 * r][column + 2 * c] != 2 && map[row + 2 * r][column + 2 * c] != 4 && map[row + 2 * r][column + 2 * c] != 16)   // Ïä×ÓºóÃæ²»ÊÇÇ½±ÚºÍÏä×Ó
            {
                // ÒÆ¶¯Ïä×Ó
                if (map[row + r][column + c] == 16)
                {
                    oldBoxType = 1;
                }
                else if (map[row + r][column + c] == 4)
                {
                    oldBoxType = 0;
                }
                map[row + r][column + c] = oldBoxType;
                if (map[row + 2 * r][column + 2 * c] == 1)
                {
                    map[row + 2 * r][column + 2 * c] = 16;
                }
                else
                {
                    map[row + 2 * r][column + 2 * c] = 4;
                }
            }
            else {
                return; // Èç¹ûÏä×ÓºóÃæÊÇÇ½±Ú£¬ÄÇÃ´Í£Ö¹ÒÆ¶¯
            }
        }
        map[row][column] = oldType; // ½«ÈËÎï×ß¹ýµÄµØ·½ÉèÎªÔ­À´µÄµØÃæÀàÐÍ
        oldType = map[row + r][column + c]; // ´æ´¢ÈËÎï½ÓÏÂÀ´Òª×ßµÄµØ·½µÄµØÃæÀàÐÍ
        map[row + r][column + c] = 8;   // ÈËÒÆ¶¯µÄÎ»ÖÃ·¢Éú±ä»¯
    }
}void resultCheck()
{
    bool result = true;
    for (int i = 0; i < sizeof(tarPos) / sizeof(tarPos[0]); i++)
    {
        if (map[tarPos[i][0]][tarPos[i][1]] != 16)
        {
            result = false;
        }
    }
    if (result)
    {
        MessageBox(NULL, TEXT("ÄãÓ®ÁË!!"), TEXT("ÓÎÏ·½áÊø"), MB_OK);
        exit(0);
    }
}
int main(void)
{
    DrawMap();
    while (true)
    {
        key = getch();    //_gettch()¿ÉÒÔÓÃÀ´¼àÌý¼üÅÌ°´¼ü
        switch (key)
        {
        case 'a':
            Move(0, -1);
            break;
        case 'd':
            Move(0, 1);
            break;
        caseÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿ