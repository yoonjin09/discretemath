#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "intset.h"

int main()
{
    FILE *fp = fopen("formmine", "w");
    char array[20][20];
    int length;
    int confirm_num;
    int x_l = 0;
    int y_l = 0;
    scanf("%d", &length);

    /*
    입력한 값들을 array에 저장한다.
    */
    for (int i = 1; i <= length; i++)
    {
        for (int j = 1; j <= length; j++)
        {
            scanf("%s", &array[i][j]);
        }
    }
    /*
    queen 했던 것처럼 2개만 선언
    */
    for (int i = 1; i <= length; i++)
        for (int n = 1; n <= length; n++)
            fprintf(fp, "(declare-const p%d0%d Bool)\n", i, n);

    //S0
    fprintf(fp, "; S0\n");
    fprintf(fp, "(assert (and ");
    for (x_l = 1; x_l <= length; x_l++)
    {
        fprintf(fp, "(and ");
        for (y_l = 1; y_l <= length; y_l++)
        {
            confirm_num = array[x_l][y_l] - '0';
            if (confirm_num >= 0 && confirm_num < 9)
            {
                fprintf(fp, "(not p%d0%d) ", x_l, y_l);
            }
            else
            {
                array[x_l][y_l] = ' ';
            }
        }
        fprintf(fp, ")");
    }
    fprintf(fp, "))\n");

    //S1
    /*
    설정을
    1 2 3
    4   5
    6 7 8
    이렇게 할 것이다.
    */
    fprintf(fp, "; S1\n");
    fprintf(fp, "(assert (and ");
    for (x_l = 1; x_l <=length; x_l++)
    {
        for (y_l = 1; y_l <= length; y_l++)
        {
            confirm_num = array[x_l][y_l] - '0';

            if (confirm_num >= 0 && confirm_num < 9)
            { //만약 그 칸에 숫자가 들어있다면 SUBSETS 을 준비한다.
                intset *s = intset_alloc();
                intset_add(s, 1);
                intset_add(s, 2);
                intset_add(s, 3);
                intset_add(s, 4);
                intset_add(s, 5);
                intset_add(s, 6);
                intset_add(s, 7);
                intset_add(s, 8); //먼저 다 ADD를 해놓고 조건에 따라 뺀다

                if (x_l == 1)
                { // 만약 맨 윗줄이라면 윗부분이 없다.
                    intset_remove(s, 1);
                    intset_remove(s, 2);
                    intset_remove(s, 3);
                }
                if (x_l == length)
                { //만약 맨 아래라면 아래부분이 없다.
                    intset_remove(s, 6);
                    intset_remove(s, 7);
                    intset_remove(s, 8);
                }

                if (y_l == 1)
                { // 만약 맨 왼쪽이라면 윗부분이 없다.
                    intset_remove(s, 1);
                    intset_remove(s, 4);
                    intset_remove(s, 6);
                }
                if (y_l == length)
                { //만약 맨 오른쪽이라면 아래부분이 없다.
                    intset_remove(s, 3);
                    intset_remove(s, 5);
                    intset_remove(s, 8);
                }

                size_t n_ps1;
                intset **ps1 = intset_subsets(s, confirm_num, &n_ps1);
                fprintf(fp, "(or ");
                for (int i = 0; i < n_ps1; i++)
                {
                    fprintf(fp, "(and ");
                    intset *n = intset_alloc();
                    n = intset_clone(s);
                    int content;
                    for (int j = 0; j < ps1[i]->n_elems; j++)
                    { //subsets을 이용해서

                        content = ps1[i]->elems[j];

                        intset_remove(n, content);
                        printf("content %d %d: %d\n", i, j, content);
                        switch (content)
                        {
                        case 1:
                            printf("case 1!!\n");
                            fprintf(fp, "p%d0%d ", x_l - 1, y_l - 1);
                            break;
                        case 2:
                            printf("case 2!!\n");
                            fprintf(fp, "p%d0%d ", x_l - 1, y_l);
                            break;
                        case 3:
                            printf("case 3!!\n");
                            fprintf(fp, "p%d0%d ", x_l - 1, y_l + 1);
                            break;
                        case 4:
                            printf("case 4!!\n");
                            fprintf(fp, "p%d0%d ", x_l, y_l - 1);
                            break;
                        case 5:
                            printf("case 5!!\n");
                            fprintf(fp, "p%d0%d ", x_l, y_l + 1);
                            break;
                        case 6:
                            printf("case 6!!\n");
                            fprintf(fp, "p%d0%d ", x_l + 1, y_l - 1);
                            break;
                        case 7:
                            printf("case 7!!\n");
                            fprintf(fp, "p%d0%d ", x_l + 1, y_l);
                            break;
                        case 8:
                            printf("case 8!!\n");
                            fprintf(fp, "p%d0%d ", x_l + 1, y_l + 1);
                            break;
                        default:
                            break;
                        }
                    }
                    for (int ia = 1; ia <= 8; ia++)
                    {
                        if (intset_contains(n, ia) == 1)
                        {
                            switch (ia)
                            {
                            case 1:
                                fprintf(fp, "(not p%d0%d) ", x_l - 1, y_l - 1);
                                break;
                            case 2:
                                fprintf(fp, "(not p%d0%d) ", x_l - 1, y_l);
                                break;
                            case 3:
                                fprintf(fp, "(not p%d0%d)", x_l - 1, y_l + 1);
                                break;
                            case 4:
                                fprintf(fp, "(not p%d0%d) ", x_l, y_l - 1);
                                break;
                            case 5:
                                fprintf(fp, "(not p%d0%d) ", x_l, y_l + 1);
                                break;
                            case 6:
                                fprintf(fp, "(not p%d0%d) ", x_l + 1, y_l - 1);
                                break;
                            case 7:
                                fprintf(fp, "(not p%d0%d) ", x_l + 1, y_l);
                                break;
                            case 8:
                                fprintf(fp, "(not p%d0%d) ", x_l + 1, y_l + 1);
                                break;
                            default:
                                break;
                            }
                        }
                    }

                    free(n);
                    fprintf(fp, ")\n");
                    // intset_print(stderr, ps1[i]) ; fprintf(stderr, "\n") ;
                    // printf("\n");
                    intset_free(ps1[i]);
                }
                fprintf(fp, ")\n");

                free(ps1);
                free(s);
            }
        }
    }
    fprintf(fp, "))\n");
    //////////////////////////////////////////////////////////////////////
    fprintf(fp, "(check-sat)\n(get-model)\n");

    fclose(fp);
    FILE *fin = popen("z3 formmine", "r");
    char buf[128];
    char pnum[128];
    char num[128]; //strcpy를 위한.
    int i_num = 0; //int 형 number
    char tru[128] = "true)";
    int mine[20][20];
    int confirm = 0;
    int x_1, y_1, num_1;
    for (int r_1 = 1; r_1 <= length; r_1++)
    {
        for (int r_2 = 1; r_2 <= length; r_2++)
        {
            mine[r_1][r_2] = 9;
            confirm_num = array[r_1][r_2] - '0';
            if (confirm_num > 0 && confirm_num < 9)
            {
                mine[r_1][r_2] = confirm_num;
            }
        }
    }
    fscanf(fin, "%s %s", buf, buf);
    while (!feof(fin))
    {
        fscanf(fin, "%s", buf);
        printf("%s ", buf);
        fscanf(fin, "%s", pnum);
        printf("%s ", pnum);
        fscanf(fin, "%s", buf);
        printf("%s ", buf);
        fscanf(fin, "%s", buf);
        printf("%s ", buf);
        fscanf(fin, "%s", buf);
        printf("%s\n", buf);
        if (confirm == strcmp(buf, tru))
        {
            strcpy(num, pnum + 1);
            i_num = atoi(num);

            if(i_num < 1000){
                y_l = i_num%10;
                x_l = i_num/100;
            }
            else if(i_num < 10000){
                if(i_num%100 < 10){
                    y_l = i_num%100;
                    x_l = i_num/100;
                }
                else
                {
                    y_l = i_num%100;
                    x_l = i_num/1000;
                }
                
            }
            else {
                y_l = i_num%100;
                x_l = i_num/1000;
            }
            
            mine[x_1][y_1] = 10;
        }
    }
    pclose(fin);
    printf("\n");
    for (int x_sudo = 1; x_sudo <= length; x_sudo++)
    {
        for (int y_sudo = 1; y_sudo <= length; y_sudo++)
        {
            switch (mine[x_sudo][y_sudo])
            {
            case 0:
                printf("_ ");
                break;
            case 1:
                printf("1 ");
                break;
            case 2:
                printf("2 ");
                break;
            case 3:
                printf("3 ");
                break;
            case 4:
                printf("4 ");
                break;
            case 5:
                printf("5 ");
                break;
            case 6:
                printf("6 ");
                break;
            case 7:
                printf("7 ");
                break;
            case 8:
                printf("8 ");
                break;
            case 9:
                printf("_ ");
                break;
            case 10:
                printf("m ");
                break;
            default:
                break;
            }
        }
        printf("\n");
    }
    return 0;
}
