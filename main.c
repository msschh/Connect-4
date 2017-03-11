#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

char place[6][7];
int player1, player2;

void display()//functie care afiseaza tabla
{
    int i, j;

    printf(" 1   2   3   4   5   6   7\n");

    for(i = 0; i <= 5; i++)//pentru fiecare cele 6 randuri, vom construi 7 casute patratice
    {
        for(j = 0; j <= 6; j++)//creez partea superioara
            printf("%c%c%c ", (char)218, (char)196, (char)191);

        printf("\n");

        for(j = 0; j <= 6; j++)//creez partea mediana
            printf("%c%c%c ", (char)179, place[i][j], (char)179);

        printf("\n");

        for(j = 0; j <= 6; j++)//creez partea inferioara
            printf("%c%c%c ", (char)192, (char)196, (char)217);

        printf("\n");
    }
}

int CheckWin(int a, int b)//verificam daca cineva a castigat
{
    int vertical = 1;//pestru a verifica castig pe verticala
    int horizontal = 1;//oentru a verifica castig pe orizintala
    int diagonal1 = 1;//pentru a verifica castig pe diagolana principala
    int diagonal2 = 1;//pentru a verifica castig pe diagolana secundara
    char player = place[a][b];
    int i, ii;

    for(i = a + 1; place[i][b] == player && i <= 5; i++, vertical++);
    for(i = a - 1; place[i][b] == player && i >= 0; i--, vertical++);
    if(vertical >= 4)
        return 1;

    for(ii = b - 1; place[a][ii] == player && ii >= 0; ii--, horizontal++);
    for(ii = b + 1; place[a][ii] == player && ii <= 6; ii++, horizontal++);
    if(horizontal >= 4)
        return 1;

    for(i = a - 1, ii = b - 1; place[i][ii] == player && i >= 0 && ii >= 0; diagonal1++, i--, ii--);
    for(i = a + 1, ii = b + 1; place[i][ii] == player && i <= 5 && ii <= 6; diagonal1++, i++, ii++);
    if(diagonal1 >= 4)
        return 1;

    for(i = a - 1, ii = b + 1; place[i][ii] == player && i >= 0 && ii <= 6; diagonal2++, i--, ii++);
    for(i = a + 1, ii = b - 1; place[i][ii] == player && i <= 5 && ii >= 0; diagonal2++, i++, ii--);
    if(diagonal2 >= 4)
        return 1;

    return 0;
}

int drop(int b, char player)//funcita care plaseaza piesa pe o anumita coloana si returneaza linie pe care a picat
{                           //sau -1 in caz in care nu a putut plasa piesa pe coloana dorita
    if(b >= 0 && b <= 6)
    {
        if(place[0][b] == ' ')
        {
            int i;
            for(i = 0; place[i][b] == ' '; i++)
                if(i == 5)
                {
                    place[i][b] = player;
                    return i;
                }
            i--;
            place[i][b] = player;
            return i;
        }
        else
            return -1;
    }
    else
        return -1;
}

int PlayerVsPlayer()//functie pentru modul de PlayerVsPlayer
{
    int i, j;

    for(i = 0; i <= 5; i++)//initializam tabla
    {
        for(j = 0; j <= 6; j++)
            place[i][j] = ' ';
    }
    display();//afisam tabla

    int hold;//folosit pentru a alege coloana pe care vom plasa piesa
    int hold2 = 0;//folosit pentru a retine pe ce linie a picat piesa
    int PlacedNumber = 0;//retine cate piese au fost plasate
    int winner = 0;//verifica daca cineva a castigat
    char player = 15;//retinu randul jucatorilor

    while(!winner)
    {
        if(hold2 != -1)
        {
            if(player == 15)
            {
                printf("Player 1 drop where?");
                player = 254;
            }
            else
            {
                printf("Player 2 drop where?");
                player = 15;
            }
        }
        while(1)//citim valori pana cand tabla este plica sau pana cand este o valoare acceptata
        {
            if(PlacedNumber == 42) break;
            scanf("%d", &hold);
            hold--;
            if(hold <= 6 && hold >= 0) break;
            else
            {
                printf("\nPlease enter a value between 1 and 7 :");
                fseek(stdin, 0, SEEK_END);
            }

        }
        if(PlacedNumber == 42) break;//dc jocul este egal
        hold2 = drop(hold,player);
        if(hold2 == -1)	printf("Colomn is full\nPlease enter another number between 1 and 7:");//citim o alta valoare deoarece coloana este plina
        else//verificam pentru castig
        {
            winner = CheckWin(hold2,hold);
            PlacedNumber ++;
            system("cls");
            display();
        }
    }
    system("cls");
    if(PlacedNumber == 42)//egal
    {
        printf("No winner. Game was draw!\n");
        system("pause");
        return 0;
    }
    if(player == 15)//castig al doilea player
        {
            printf("Game won by : player 2\n");
            player2++;
        }
    else//castig primul player
        {
            printf("Game won by : player 1\n");
            player1++;
        }
    system("pause");

    return 0;
}

int AiEasy()//functie pentru player vs calculator mod easy
{
    int i, j;

    for(i = 0; i <= 5; i++)
    {
        for(j = 0; j <= 6; j++)
            place[i][j] = ' ';
    }
    display();

    int hold;
    int hold2 = 0;
    int PlacedNumber = 0;
    int winner = 0;
    char player = 15;

    srand(time(NULL));//initializam functia rand
    while(!winner)
    {
        if(player == 15)//player-ul alege de la tastatura unde sa plaseze piesa
        {
            printf("Player 1 drop where?");
            player = 254;
            do
            {
                if(PlacedNumber == 42) break;
                scanf("%d", &hold);
                hold--;

                if(hold <= 6 && hold >= 0)
                {
                    continue;
                }
                else
                {
                    printf("\nPlease enter a value between 1 and 7 :");
                    fseek(stdin, 0, SEEK_END);
                }
            }
            while(place[0][hold] != ' ');//cat timp coloana nu este plina
        }
        else//ai-ul alege coloana prin functia rand() pana gaseste una care nu este plina
        {
            player = 15;
            do
            {
                hold = rand() % 7;
                printf("%d", hold);
            }
            while(place[0][hold] != ' ');
        }

        if(PlacedNumber == 42) break;
        hold2 = drop(hold,player);
        if(hold2 == -1)	printf("Colomn is full\nPlease enter another number between 1 and 7:");
        else
        {
            winner = CheckWin(hold2,hold);
            PlacedNumber ++;
            system("cls");
            display();
        }
    }
    system("cls");
    if(PlacedNumber == 42)
    {
        printf("No winner. Game was draw!\n");
        system("pause");
        return 0;
    }
    if(player == 15)
        {
            printf("Game won by : AI\n");
            player2++;
        }
    else
        {
            printf("Game won by : player 1\n");
            player1++;
        }
    system("pause");

    return 0;
}

int CheckThree(int a, int b)//verificam dc exita 3 piese in linie de acelasi fel
{
    int vertical = 1;
    int horizontal = 1;
    int diagonal1 = 1;
    int diagonal2 = 1;
    char player = place[a][b];
    int i, ii;
    int s = 0;

    for(i = a + 1; place[i][b] == player && i <= 5; i++, vertical++);
    for(i = a - 1; place[i][b] == player && i >= 0; i--, vertical++);
    if(vertical == 3)
        s++;

    for(ii = b - 1; place[a][ii] == player && ii >= 0; ii--, horizontal++);
    for(ii = b + 1; place[a][ii] == player && ii <= 6; ii++, horizontal++);
    if(horizontal == 3)
        s++;

    for(i = a - 1, ii = b - 1; place[i][ii] == player && i >= 0 && ii >= 0; diagonal1++, i--, ii--);
    for(i = a + 1, ii = b + 1; place[i][ii] == player && i <= 5 && ii <= 6; diagonal1++, i++, ii++);
    if(diagonal1 == 3)
        s++;

    for(i = a - 1, ii = b + 1; place[i][ii] == player && i >= 0 && ii <= 6; diagonal2++, i--, ii++);
    for(i = a + 1, ii = b - 1; place[i][ii] == player && i <= 5 && ii >= 0; diagonal2++, i++, ii--);
    if(diagonal2 == 3)
        s++;

    if(s)
        return s;
    else
        return 0;
}

int CheckTwo(int a, int b)//verificam dc exita 2 piese in linie de acelasi fel
{
    int vertical = 1;
    int horizontal = 1;
    int diagonal1 = 1;
    int diagonal2 = 1;
    char player = place[a][b];
    int i, ii;
    int s = 0;

    for(i = a + 1; place[i][b] == player && i <= 5; i++, vertical++);
    for(i = a - 1; place[i][b] == player && i >= 0; i--, vertical++);
    if(vertical == 2)
        s++;

    for(ii = b - 1; place[a][ii] == player && ii >= 0; ii--, horizontal++);
    for(ii = b + 1; place[a][ii] == player && ii <= 6; ii++, horizontal++);
    if(horizontal == 2)
        s++;

    for(i = a - 1, ii = b - 1; place[i][ii] == player && i >= 0 && ii >= 0; diagonal1++, i--, ii--);
    for(i = a + 1, ii = b + 1; place[i][ii] == player && i <= 5 && ii <= 6; diagonal1++, i++, ii++);
    if(diagonal1 == 2)
        s++;

    for(i = a - 1, ii = b + 1; place[i][ii] == player && i >= 0 && ii <= 6; diagonal2++, i--, ii++);
    for(i = a + 1, ii = b - 1; place[i][ii] == player && i <= 5 && ii >= 0; diagonal2++, i++, ii--);
    if(diagonal2 == 2)
        s++;

    if(s)
        return 1;
    else
        return 0;
}

int CheckOne(int a, int b)//verificam dc exita o piesa in linie de acelasi fel
{
    int vertical = 1;
    int horizontal = 1;
    int diagonal1 = 1;
    int diagonal2 = 1;
    char player = place[a][b];
    int i, ii;
    int s = 0;

    for(i = a + 1; place[i][b] == player && i <= 5; i++, vertical++);
    for(i = a - 1; place[i][b] == player && i >= 0; i--, vertical++);
    if(vertical == 1)
        s++;

    for(ii = b - 1; place[a][ii] == player && ii >= 0; ii--, horizontal++);
    for(ii = b + 1; place[a][ii] == player && ii <= 6; ii++, horizontal++);
    if(horizontal == 1)
        s++;

    for(i = a - 1, ii = b - 1; place[i][ii] == player && i >= 0 && ii >= 0; diagonal1++, i--, ii--);
    for(i = a + 1, ii = b + 1; place[i][ii] == player && i <= 5 && ii <= 6; diagonal1++, i++, ii++);
    if(diagonal1 == 1)
        s++;

    for(i = a - 1, ii = b + 1; place[i][ii] == player && i >= 0 && ii <= 6; diagonal2++, i--, ii++);
    for(i = a + 1, ii = b - 1; place[i][ii] == player && i <= 5 && ii >= 0; diagonal2++, i++, ii--);
    if(diagonal2 == 1)
        s++;

    if(s)
        return s;
    else
        return 0;
}

int CheckNonWin(int a, int b)//verificam dc putem impiedica adversarul sa castige
{
    int vertical = 1;
    int horizontal = 1;
    int diagonal1 = 1;
    int diagonal2 = 1;
    char player;
    if(place[a][b] == 15)
        player = 254;
    else player = 15;
    int i, ii;

    for(i = a + 1; place[i][b] == player && i <= 5; i++, vertical++);
    for(i = a - 1; place[i][b] == player && i >= 0; i--, vertical++);
    if(vertical >= 4)
        return 1;

    for(ii = b - 1; place[a][ii] == player && ii >= 0; ii--, horizontal++);
    for(ii = b + 1; place[a][ii] == player && ii <= 6; ii++, horizontal++);
    if(horizontal >= 4)
        return 1;

    for(i = a - 1, ii = b - 1; place[i][ii] == player && i >= 0 && ii >= 0; diagonal1++, i--, ii--);
    for(i = a + 1, ii = b + 1; place[i][ii] == player && i <= 5 && ii <= 6; diagonal1++, i++, ii++);
    if(diagonal1 >= 4)
        return 1;

    for(i = a - 1, ii = b + 1; place[i][ii] == player && i >= 0 && ii <= 6; diagonal2++, i--, ii++);
    for(i = a + 1, ii = b - 1; place[i][ii] == player && i <= 5 && ii >= 0; diagonal2++, i++, ii--);
    if(diagonal2 >= 4)
        return 1;

    return 0;
}

int CheckNonThree(int a, int b)//verificam dc putem in cate locuri putem impiedica adversarul sa faca 3 in linie
{
    int vertical = 1;
    int horizontal = 1;
    int diagonal1 = 1;
    int diagonal2 = 1;
    char player;
    if(place[a][b] == 15)
        player = 254;
    else player = 15;
    int i, ii;
    int s = 0;

    for(i = a + 1; place[i][b] == player && i <= 5; i++, vertical++);
    for(i = a - 1; place[i][b] == player && i >= 0; i--, vertical++);
    if(vertical == 3)
        s++;

    for(ii = b - 1; place[a][ii] == player && ii >= 0; ii--, horizontal++);
    for(ii = b + 1; place[a][ii] == player && ii <= 6; ii++, horizontal++);
    if(horizontal == 3)
        s++;

    for(i = a - 1, ii = b - 1; place[i][ii] == player && i >= 0 && ii >= 0; diagonal1++, i--, ii--);
    for(i = a + 1, ii = b + 1; place[i][ii] == player && i <= 5 && ii <= 6; diagonal1++, i++, ii++);
    if(diagonal1 == 3)
        s++;

    for(i = a - 1, ii = b + 1; place[i][ii] == player && i >= 0 && ii <= 6; diagonal2++, i--, ii++);
    for(i = a + 1, ii = b - 1; place[i][ii] == player && i <= 5 && ii >= 0; diagonal2++, i++, ii--);
    if(diagonal2 == 3)
        s++;

    if(s)
        return s;
    else
        return 0;
}

int CheckNonTwo(int a, int b)//verificam dc putem in cate locuri putem impiedica adversarul sa faca 2 in linie
{
    int vertical = 1;
    int horizontal = 1;
    int diagonal1 = 1;
    int diagonal2 = 1;
    char player;
    if(place[a][b] == 15)
        player = 254;
    else player = 15;
    int i, ii;
    int s = 0;

    for(i = a + 1; place[i][b] == player && i <= 5; i++, vertical++);
    for(i = a - 1; place[i][b] == player && i >= 0; i--, vertical++);
    if(vertical == 2)
        s++;

    for(ii = b - 1; place[a][ii] == player && ii >= 0; ii--, horizontal++);
    for(ii = b + 1; place[a][ii] == player && ii <= 6; ii++, horizontal++);
    if(horizontal == 2)
        s++;

    for(i = a - 1, ii = b - 1; place[i][ii] == player && i >= 0 && ii >= 0; diagonal1++, i--, ii--);
    for(i = a + 1, ii = b + 1; place[i][ii] == player && i <= 5 && ii <= 6; diagonal1++, i++, ii++);
    if(diagonal1 == 2)
        s++;

    for(i = a - 1, ii = b + 1; place[i][ii] == player && i >= 0 && ii <= 6; diagonal2++, i--, ii++);
    for(i = a + 1, ii = b - 1; place[i][ii] == player && i <= 5 && ii >= 0; diagonal2++, i++, ii--);
    if(diagonal2 == 2)
        s++;

    if(s)
        return 1;
    else
        return 0;
}

int CheckNonOne(int a, int b)//verificam dc putem in cate locuri putem impiedica adversarul sa faca 1 in linie
{
    int vertical = 1;
    int horizontal = 1;
    int diagonal1 = 1;
    int diagonal2 = 1;
    char player;
    if(place[a][b] == 15)
        player = 254;
    else player = 15;
    int i, ii;
    int s = 0;

    for(i = a + 1; place[i][b] == player && i <= 5; i++, vertical++);
    for(i = a - 1; place[i][b] == player && i >= 0; i--, vertical++);
    if(vertical == 1)
        s++;

    for(ii = b - 1; place[a][ii] == player && ii >= 0; ii--, horizontal++);
    for(ii = b + 1; place[a][ii] == player && ii <= 6; ii++, horizontal++);
    if(horizontal == 1)
        s++;

    for(i = a - 1, ii = b - 1; place[i][ii] == player && i >= 0 && ii >= 0; diagonal1++, i--, ii--);
    for(i = a + 1, ii = b + 1; place[i][ii] == player && i <= 5 && ii <= 6; diagonal1++, i++, ii++);
    if(diagonal1 == 1)
        s++;

    for(i = a - 1, ii = b + 1; place[i][ii] == player && i >= 0 && ii <= 6; diagonal2++, i--, ii++);
    for(i = a + 1, ii = b - 1; place[i][ii] == player && i <= 5 && ii >= 0; diagonal2++, i++, ii--);
    if(diagonal2 == 1)
        s++;

    if(s)
        return s;
    else
        return 0;
}

int choose(int x)//functie prin care ai-ul decide pe ce coloana sa plaseze piesa
{
    int i = 0;
    if(place[0][x] == ' ')
    {
        while(i < 5 && place[i + 1][x] == ' ')
            i++;
    }
    else
        return 0;
    place[i][x] = 254;
    int s = 0;
    s += 100000000 * CheckWin(i, x);
    s += 1000 * CheckThree(i, x);
    s += 100 * CheckTwo(i, x);
    s += 10 * CheckOne(i, x);
    s += 50000000 * CheckNonWin(i, x);
    s += 500 * CheckNonThree(i, x);
    s += 50 * CheckNonTwo(i, x);
    s += 5 * CheckNonOne(i, x);
    place[i][x] = ' ';
    return s;
}

int AiMediu()//functie pentru modul de player vs game nivel mediu
{
    int i, j;

    for(i = 0; i <= 5; i++)
    {
        for(j = 0; j <= 6; j++)
            place[i][j] = ' ';
    }
    display();

    int hold;
    int hold2 = 0;
    int PlacedNumber = 0;
    int winner = 0;
    char player = 15;

    while(!winner)
    {

        if(player == 15)
        {
            printf("Player 1 drop where?");
            player = 254;
            do
            {
                if(PlacedNumber == 42) break;
                scanf("%d", &hold);
                hold--;
                if(hold <= 6 && hold >= 0) continue;
                else
                {
                    printf("\nPlease enter a value between 1 and 7 :");
                    fseek(stdin, 0, SEEK_END);
                }

            }
            while(place[0][hold] != ' ');
        }
        else
        {
            player = 15;
            int max = choose(0);
            hold = 0;
            int i;
            for(i = 1; i <= 6; i++)//ai-ul apeleaza functia choose() pentru fiecare coloana si decide mutarea care ofera cea mai mare suma
                if(choose(i) > max)
                {
                    max = choose(i);
                    hold = i;
                }
        }

        if(PlacedNumber == 42) break;
        hold2 = drop(hold,player);
        if(hold2 == -1)	printf("Colomn is full\nPlease enter another number between 1 and 7:");
        else
        {
            winner = CheckWin(hold2,hold);
            PlacedNumber ++;
            system("cls");
            display();
        }
    }
    system("cls");
    if(PlacedNumber == 42)
    {
        printf("No winner. Game was draw!\n");
        system("pause");
        return 0;
    }
    if(player == 15)
        {
            printf("Game won by : AI\n");
            player2++;
        }
    else
        {
            printf("Game won by : player 1\n");
            player1++;
        }
    system("pause");

    return 0;

}

int main()
{
    int x;

    printf("Chose level:\n1)Player Vs Player\n2)Plaver Vs Game Easy\n3)Player Vs Game Mediu\n");

    do
    {
        scanf("%d", &x);
    }
    while(x <= 0 || x >= 4);

    system("cls");

    int ok = 1;
    while(ok == 1)
    {
        ok = 0;
        if(x == 1)//folosim 3 functii pentru fiecare tip de nivel si doua variabile globale pentru a retine scorul
            {
                PlayerVsPlayer();
                printf("SCORE: Player 1 - %d            Player2 - %d\n", player1, player2);
                printf("Press 1 to play again or 2 to exit!\n");
                scanf("%d", &ok);
                system("cls");
            }
        else if(x == 2)
            {
                AiEasy();
                printf("SCORE: Player 1 - %d          Ai - %d\n", player1, player2);
                printf("Press 1 to play again or 2 to exit!\n");
                scanf("%d", &ok);
                system("cls");
            }
            else {
                    AiMediu();
                    printf("SCORE: Player 1 - %d          Ai - %d\n", player1, player2);
                    printf("Press 1 to play again or 2 to exit!\n");
                    scanf("%d", &ok);
                    system("cls");
                 }
    }

    return 0;
}
