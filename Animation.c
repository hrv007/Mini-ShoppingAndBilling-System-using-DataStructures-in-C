#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

void main()
{
    getch();
    for(int i=0; i<=5; i++)
    {
        for(int j=5; j>=i; j--)
        {
            printf("\n\n\n\n\n");
        }
        printf("\t\t\t\t\t\t\t*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n");
        printf("\t\t\t\t\t\t\t|                                 |\n");
        printf("\t\t\t\t\t\t\t*              AMAZUN             *\n");
        printf("\t\t\t\t\t\t\t|             ------->            |\n");
        printf("\t\t\t\t\t\t\t*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n");
        sleep(1.00);
        system("cls");
    }

    sleep(1.00);
    for(int i=0; i<20; i++) printf("\n");
    printf("\t\t\t\t\t\t\t*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n");
    printf("\t\t\t\t\t\t\t|                                 |\n");
    printf("\t\t\t\t\t\t\t*              AMAZUN             *\n");
    printf("\t\t\t\t\t\t\t|             ------->            |\n");
    printf("\t\t\t\t\t\t\t*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n");

    getch();
    system("cls");
    printf("Welcome");
}
