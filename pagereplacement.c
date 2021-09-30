#include <stdio.h>
#include <stdlib.h>

void FIFO(int n, int ref[n], int frame)
{
    int q[frame];
    for (int i = 0; i < frame; i++)
        q[i] = -1;
    int rear = 0;
    q[0] = ref[0];
    printf("STEP 1-->  %d  \n", q[0]);
    int fault = 1;
    for (int i = 1; i < n; i++)
    {
        int f = 0;
        for (int j = 0; j < frame; j++)
        {
            if (ref[i] == q[j])
            {
                f = 1; //hit
                break;
            }
        }
        if (f == 0) //page fault
        {
            fault++;
            rear = (rear + 1) % frame;
            q[rear] = ref[i];
        }
        printf("STEP %d--> ", i + 1);
        for (int k = 0; k < frame; k++)
        {
            if (q[k] != -1)
                printf(" %d  ", q[k]);
        }
        printf("\n");
    }
    printf("No of page faults = %d", fault);
}
void LRU(int n, int ref[n], int frame)
{
    int q[frame], index[frame];
    for (int i = 0; i < frame; i++)
    {
        q[i] = -1;
        index[i] = -1;
    }
    int rear = 0;
    int inF = 0, inR = 0;
    q[0] = ref[0];
    printf("STEP 1-->  %d  \n", q[0]);
    index[0] = 0;
    int fault = 1;
    for (int i = 1; i < n; i++)
    {
        int f = 0;
        for (int j = 0; j < frame; j++)
        {
            if (ref[i] == q[j])
            {
                f = 1; //hit
                for (int k = inF; k <= inR; k++)
                {
                    if (index[k] == j) //finding it among the index list
                    {
                        for (int l = k; l < inR; l++)
                            index[l] = index[l + 1];

                        index[inR] = j;
                        break;
                    }
                }
                break;
            }
        }
        if (f == 0) //page fault
        {
            fault++;
            if (rear + 1 < frame)
            {
                inR = inR + 1;
                index[inR] = i;
                rear++;
                q[rear] = ref[i];
            }
            else
            {
                int t = index[inF];
                q[index[inF]] = ref[i];
                for (int l = inF; l < inR; l++)
                    index[l] = index[l + 1];
                index[inR] = t;
                // inF=inF+1;
            }
        }
        printf("STEP %d--> ", i + 1);
        for (int k = 0; k < frame; k++)
        {
            if (q[k] != -1)
                printf(" %d  ", q[k]);
        }
        printf("\n");
    }
    printf("No of page faults = %d", fault);
}
void LFU(int n, int ref[n], int frame)
{
    int q[frame], index[2][frame];
    for (int i = 0; i < frame; i++)
    {
        q[i] = -1;
        index[0][i] = -1;
        index[1][i] = 0;
    }
    int rear = 0;
    int inR = 0;
    q[0] = ref[0];
    printf("STEP 1-->  %d  \n", q[0]);
    index[0][0] = 0;
    index[1][0]++;
    int fault = 1;
    for (int i = 1; i < n; i++)
    {
        int f = 0;
        for (int j = 0; j < frame; j++) //traverse q
        {
            if (ref[i] == q[j])
            {
                f = 1;                         //hit
                for (int k = 0; k <= inR; k++) //traverse index
                {
                    if (index[0][k] == j)
                    {
                        for (int l = k; l < inR; l++) //adjust index
                        {
                            index[0][l] = index[0][l + 1];
                            index[1][l] = index[1][l + 1];
                        }
                        index[0][inR] = j;
                        index[1][inR]++;
                        break;
                    }
                }
                break;
            }
        }
        if (f == 0) //page fault
        {
            fault++;
            if (rear + 1 < frame)
            {
                inR = inR + 1;
                index[0][inR] = i;
                index[1][inR]++;
                rear++;
                q[rear] = ref[i];
            }
            else
            {
                int small = index[1][0], pos = 0;
                for (int j = 1; j <= inR; j++) //traverse index[1]
                {
                    if (index[1][j] < small)
                    {
                        small = index[1][j];
                        pos = j;
                        break;
                    }
                }
                int t = index[0][pos];
                for (int l = pos; l < inR; l++) //adjust index
                {
                    index[0][l] = index[0][l + 1];
                    index[1][l] = index[1][l + 1];
                }
                index[0][inR] = t;
                index[1][inR] = small;
                q[t] = ref[i];
            }
        }
        printf("STEP %d--> ", i + 1);
        for (int k = 0; k < frame; k++)
        {
            if (q[k] != -1)
                printf(" %d  ", q[k]);
        }
        printf("\n");
    }
    printf("No of page faults = %d", fault);
}
void optimal(int n, int ref[n], int frame)
{
    int q[frame], firstocc[frame], fault;
    for (int i = 0; i < frame; i++)
    {
        q[i] = -1;
        firstocc[i] = 0;
    }
    q[0] = ref[0];
    fault = 1;
    int rear = 0;
    printf("STEP 1-->  %d  \n", q[0]);
    int i;
    for (i = 1; i < n; i++)
    {
        int f = 0;
        for (int j = 0; j < frame; j++)
        {
            if (ref[i] == q[j]) //hit
            {
                f = 1;
                break;
            }
        }
        if (f == 0) //fault
        {
            fault++;
            if (rear < frame - 1)
            {
                rear++;
                q[rear] = ref[i];
            }
            else
            {
                for (int j = 0; j < frame; j++)
                {
                    firstocc[j] = 0;
                    for (int k = i + 1; k < n; k++)
                    {
                        if (ref[k] == q[j])
                        {
                            firstocc[j] = k;
                            break;
                        }
                    }
                }
                int t = 0;
                int k;
                for (k = 1; k < frame; k++)
                {
                    if (firstocc[t] == 0)
                    {
                        break;
                    }
                    if (firstocc[k] == 0)
                    {
                        t = k;
                        break;
                    }
                    else if (firstocc[k] > firstocc[t])
                        t = k;
                }
                //printf("\nq[firstocc]=%d\n", q[firstocc]);
                q[t] = ref[i];
            }
        }
        printf("STEP %d--> ", i + 1);
        for (int s = 0; s < frame; s++)
        {
            if (q[s] != -1 && f == 0)
                printf(" %d  ", q[s]);
        }
        printf("\n");
    }
    printf("Number of page faults: %d", fault);
}
void main()
{
    int n, frame, choice, ch;
    do
    {
        printf("\nEnter the number of page reference strings: ");
        scanf("%d", &n);
        int ref[n];
        printf("Enter the page reference strings: ");
        for (int i = 0; i < n; i++)
            scanf("%d", &ref[i]);
        printf("Enter the number of page frames: ");
        scanf("%d", &frame);
        printf("\nOPTIONS:\n 1.FIFO\n 2.LRU\n 3.LFU\n 4.OPTIMAL\n 0.EXIT\n");
        printf("Enter your choice: ");
        scanf("%d", &ch);
        switch (ch)
        {
        case 1:
            FIFO(n, ref, frame);
            break;
        case 2:
            LRU(n, ref, frame);
            break;
        case 3:
            LFU(n, ref, frame);
            break;
        case 4:
            optimal(n, ref, frame);
            break;
        case 0:
            printf("SUCCESSFUL EXIT!!");
            exit(0);
            break;
        default:
            printf("Invalid choice!! Exiting!!");
            exit(1);
        }
        printf("\nDo you want to continue? Type 1 for yes and 0 for no: ");
        scanf("%d", &choice);
    } while (choice == 1);
}