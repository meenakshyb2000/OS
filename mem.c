#include <stdio.h>
#include <limits.h>

void First_Fit(int n, int avail[n], int m, int space_req[m])
{
    printf("\n\t-------FIRST FIT ALLOCATION-------\n");
    int used[n], allocated[m];
    for (int i = 0; i < n; i++)
        used[i] = 0;
    for (int i = 0; i < m; i++)
        allocated[i] = 0;
    for (int i = 0; i < m; i++) //for each process
    {
        if (allocated[i] == 0) //not allocated
        {
            for (int j = 0; j < m; j++)
            {
                if (used[j] == 0 && space_req[i] <= avail[j])
                {
                    used[j] = 1;
                    allocated[i] = 1;
                    printf(" %d ----> %d\n", space_req[i], avail[j]);
                    break;
                }
            }
        }
        if (allocated[i] == 0)
            printf(" %d----> Not Allocated", space_req[i]);
    }
}
void Next_Fit(int n, int avail[n], int m, int space_req[m])
{
    printf("\n\t-------NEXT FIT ALLOCATION-------\n");
    int used[n], allocated[m];
    for (int i = 0; i < n; i++)
        used[i] = 0;
    for (int i = 0; i < m; i++)
        allocated[i] = 0;
    int a = -1;
    for (int i = 0; i < m; i++) //for each process
    {
        if (allocated[i] == 0) //not allocated
        {
            for (int j = a + 1; j < m; j++)
            {
                if (used[j] == 0 && space_req[i] <= avail[j])
                {
                    used[j] = 1;
                    allocated[i] = 1;
                    printf(" %d ----> %d\n", space_req[i], avail[j]);
                    a = j;
                    break;
                }
            }
        }
        if (allocated[i] == 0)
            printf(" %d----> Not Allocated", space_req[i]);
    }
}
void Best_Fit(int n, int avail[n], int m, int space_req[m])
{
    printf("\n\t-------BEST FIT ALLOCATION-------\n");
    int min, pos;
    int used[n], allocated[m];
    for (int i = 0; i < n; i++)
        used[i] = 0;
    for (int i = 0; i < m; i++)
        allocated[i] = 0;
    for (int i = 0; i < m; i++) //for each process
    {
        if (allocated[i] == 0)
        {
            min = INT_MAX;
            pos = -1;
            for (int j = 0; j < n; j++)
            {
                if (used[j] == 0 && space_req[i] <= avail[j] && avail[j] < min)
                {
                    min = avail[j];
                    pos = j;
                }
            }
            if (pos != -1)
            {
                used[pos] = 1;
                allocated[i] = 1;
                printf(" %d ----> %d\n", space_req[i], avail[pos]);
            }
            else if (allocated[i] == 0)
                printf("%d ----> Not Allocated ", space_req);
        }
    }
}
void Worst_Fit(int n, int avail[n], int m, int space_req[m])
{
    printf("\n\t-------WORST FIT ALLOCATION-------\n");
    int max, pos;
    int used[n], allocated[m];
    for (int i = 0; i < n; i++)
        used[i] = 0;
    for (int i = 0; i < m; i++)
        allocated[i] = 0;
    for (int i = 0; i < m; i++) //for each process
    {
        if (allocated[i] == 0)
        {
            max = INT_MIN;
            pos = -1;
            for (int j = 0; j < n; j++)
            {
                if (used[j] == 0 && space_req[i] <= avail[j] && avail[j] > max)
                {
                    max = avail[j];
                    pos = j;
                }
            }
            if (pos != -1)
            {
                used[pos] = 1;
                allocated[i] = 1;
                printf(" %d ----> %d\n", space_req[i], avail[pos]);
            }
            if (allocated[i] == 0)
                printf(" %d ----> Not Allocated\n", space_req[i]);
        }
    }
}
void main()
{
    int ch, n, m;
    int choice;
    printf("Enter the number of available memory blocks : ");
    scanf("%d", &n);
    int avail[n];
    printf("Enter the size of each block: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &avail[i]);
    printf("Enter the number of required memory blocks: ");
    scanf("%d", &m);
    int space_req[m];
    printf("Enter the required storage sizes: ");
    for (int i = 0; i < m; i++)
        scanf("%d", &space_req[i]);
    do
    {
        printf("\nAVAILABLE CHOICES:\n1. First Fit\n2. Best Fit\n3. Worst Fit\n4. Next Fit");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            First_Fit(n, avail, m, space_req);
            break;
        case 2:
            Best_Fit(n, avail, m, space_req);
            break;
        case 3:
            Worst_Fit(n, avail, m, space_req);
            break;
        case 4:
            Next_Fit(n, avail, m, space_req);
            break;
        default:
            printf("\nError!!Invalid choice!!!");
            break;
        }
        printf("\nDo you want to continue? Type 1 for yes and 0 for no: ");
        scanf("%d", &ch);
    } while (ch != 0);
}
