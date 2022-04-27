#include <stdio.h>
#include <stdlib.h>
#define ARR_MAX 1001

int theorem_graph(int reb, int line, FILE *file)
{
    char conn = '"';
    puts("------------------");
    if (reb >= ((line - 1) * (line - 2) / 2)) // graph connectivity theorem
    {
        puts("graph - connected");
        fprintf(file, "0 [label = %c connected %c]\n", conn, conn);
    }
    else
    {
        puts("graph -  not connected");
        fprintf(file, "0 [label = %c not connected %c]\n", conn, conn);
    }
    puts("------------------");
    return 0;
}

int draw_graph(char arr[ARR_MAX][ARR_MAX], int line, int ver, int reb, FILE *file)
{
    file = fopen("matrix.gv", "w");
    fprintf(file, "graph Graph {\n");
    puts("------------------\n");
    puts("Your matrix:\n");
    for (int a = 0; a <= line; a++)
    {
        int c = a + 1;
        for (int b = 0; b <= ver; b++)
        {
            printf("%c ", arr[a][b]);
            if (arr[a][b] == '1' && arr[c][b] == '1')
            {
                reb++;
            }
        }
        putchar('\n');
    }
    puts("------------------");
    puts("Adjacency list:");
    for (int d = 1; d <= line; d++)
    {
        fprintf(file, "%d\n", d);
        printf("%d\n", d);
    }
    for (int j = 0; j <= line; j++)
    {
        for (int k = 0; k <= ver; k++)
        {
            if (arr[j][k] == '1')
            {
                for (int f = j; f <= line; f++)
                {
                    if (arr[f][k] == '1' && f != j)
                    {
                        printf("%d -- %d\n", j, f);
                        fprintf(file, "%d -- %d\n", j, f);
                    }
                }
            }
        }
    }
    theorem_graph(reb, line, file);
    fputc('}', file);
    // fprintf(file, "}");
    fclose(file);
    system("dot matrix.gv -Tpng -o matrix.png");
    system("matrix.png");
    return 0;
}

int main()
{
    FILE *file = fopen("abc.txt", "r");
    char arr[ARR_MAX][ARR_MAX], s;
    int line = 1, ver = 0, reb = 0, max_len = 0;
    // -----------------------------------------
    while (!feof(file)) // запись матрицы из файла в двумерный массив
    {
        fscanf(file, "%c", &s);
        if (s != ' ' && s != '\n' && s != '\0')
        {
            arr[line][ver] = s;
            ver++;
        }
        else if (s == '\n')
        {
            line++;
            max_len = ver;
            ver = 0;
        }
    }
    arr[line][max_len] = '\0';
    fclose(file);
    draw_graph(arr, line, ver, reb, file); // отрисовка графа + теорема связности + список смежности
    return 0;
}