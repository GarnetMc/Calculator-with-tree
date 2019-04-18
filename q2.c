#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

typedef struct node{
    int key;
    int ints[10];
} node;

int main()
{
    int swap;
    int ints[20][10];
    node* heap[21];
    node* temp;
    FILE *fp;
    fp = fopen("f.dat", "r");
    for (int i = 0; i < 20; i++)
    {
        fscanf(fp, "%d %d %d %d %d %d %d %d %d %d", &ints[i][0], &ints[i][1], &ints[i][2], &ints[i][3], &ints[i][4], &ints[i][5], &ints[i][6], &ints[i][7], &ints[i][8], &ints[i][9]);
    }
    for (int j = 1; j < 21; j++)   //create the heap
    {
        heap[j] = (node*)malloc(sizeof(node));
        heap[j] -> key = ints[j-1][0] + ints[j-1][1] + ints[j-1][2];
        for (int k = 0; k < 10; k++)
        {
            heap[j] -> ints[k] = ints[j-1][k];
        }
    }
    swap = 0;
    while (swap == 0)
    {
        swap = 1;
        for (int n = 10; n>1; n--)
        {
            if (n != 10)
            {
                if (((heap[n]-> key) > (heap[n*2]-> key)) || ((heap[n]-> key) > (heap[n*2+1]-> key)))
                {
                    swap = 0;
                    if ((heap[n*2]-> key) < (heap[n*2+1]-> key))
                    {
                        temp = heap[n*2];
                        heap[n*2] = heap[n];
                        heap[n] = temp;

                    }
                    else
                    {
                        temp = heap[n*2+1];
                        heap[n*2+1] = heap[n];
                        heap[n] = temp;
                    }
                }
            }
            else
            {
                if ((heap[n]-> key) > (heap[n*2]-> key))
                {
                    swap = 0;
                    temp = heap[n*2];
                    heap[n*2] = heap[n];
                    heap[n] = temp;
                }
            }
        }
    }
    for (int l = 1; l<21; l++)     //print the heap
    {
      printf("Key: %-3d Values: ",  heap[l]-> key);
      for (int m = 0; m<10; m++)
      {
          printf("%-2d ", heap[l]-> ints[m]);
      }
      printf("\n");
    }
    return 0;
}
