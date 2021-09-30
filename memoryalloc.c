#include <stdio.h>
#include <limits.h>
void display(int m, int space_req[m], int allocated[m])
{
    printf("\nAllocated spaces:\n");
    for (int i = 0; i < m; i++)
    {
        if (allocated[i] == 0)
            printf("%d--->Not Allocated\n", space_req[i]);
        else
            printf("%d--->%d\n", space_req[i], allocated[i]);
    }
}
void First_Fit(int n, int avail[n], int m, int space_req[m])
{
    printf("\n\t-------FIRST FIT ALLOCATION-------");
    int used[n], allocated[m]; //used-to see if block is allocated, allocated- to see which is allocated to
    for (int i = 0; i < n; i++)
        used[i] = 0;
    for (int i = 0; i < m; i++)
        allocated[i] = 0;
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (used[j] == 0 && avail[j] >= space_req[i])
            {
                allocated[i] = avail[j];
                used[j] = 1;
                break;
            }
        }
    }
    display(m, space_req, allocated);
}
void Best_Fit(int n, int avail[n], int m, int space_req[m])
{
    printf("\n\t-------BEST FIT ALLOCATION------");
    int used[n], allocated[m];
    for (int i = 0; i < n; i++)
        used[i] = 0;
    for (int i = 0; i < m; i++)
        allocated[i] = 0;
    for (int i = 0; i < m; i++)
    {
        int min = __INT_MAX__, pos = -1;
        ;
        for (int j = 0; j < n; j++)
        {
            if (used[j] == 0 && ((avail[j] >= space_req[i]) && (avail[j] - space_req[i]) < min))
            {
                min = avail[j] - space_req[i];
                pos = j;
                allocated[i] = avail[j];
            }
        }
        if (pos != -1)
            used[pos] = 1;
    }
    display(m, space_req, allocated);
}
void Worst_Fit(int n, int avail[n], int m, int space_req[m])
{
    printf("\n\t-------WORST FIT ALLOCATION-------");
    int used[n], allocated[m];
    for (int i = 0; i < n; i++)
    {
        used[i] = 0;
    }
    for (int i = 0; i < m; i++)
    {
        allocated[i] = 0;
    }
    for (int i = 0; i < m; i++)
    {
        int max = INT_MIN, pos = -1;
        for (int j = 0; j < n; j++)
        {
            if (used[j] == 0 && ((avail[j] >= space_req[i]) && (avail[j] - space_req[i]) > max))
            {
                max = avail[j] - space_req[i];
                pos = j;
                allocated[i] = avail[j];
            }
        }
        if (pos != -1)
            used[pos] = 1;
    }
    display(m, space_req, allocated);
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
        printf("\nAVAILABLE CHOICES:\n1. First Fit\n2. Best Fit\n3. Worst Fit");
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
        default:
            printf("\nError!!Invalid choice!!!");
            break;
        }
        printf("\nDo you want to continue? Type 1 for yes and 0 for no: ");
        scanf("%d", &ch);
    } while (ch != 0);
}
