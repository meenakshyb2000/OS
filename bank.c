#include <stdio.h>
void safety(int n, int inst, int PN[n], int max[n][inst], int need[n][inst], int allocate[n][inst], int available[inst])
{
    int f=0,ctr=0,i=0,k=0;
    int F[n],S[n];
    for(int i=0;i<n;i++)
     {   
        S[i]=0;
        F[i]=0;
     }
    while(i<n)
    {
        if(S[i]!=1)
        {
            for(int j=0;j<inst;j++)
            {
                if(need[i][j]<=available[j])
                {
                    f=1;
                    continue;
                }    
                else
                {   f=0;
                    break;
                }
            }
            if(f==1)
            {
                ctr++; //no of completed processes
                F[k++]=PN[i];
                for(int j=0;j<inst;j++)
                {    
                    available[j]+=allocate[i][j];
                }
                S[i]=1;
            }       
            if(ctr!=n &&i==n-1)
            {    
                i=0;
                continue;
            }
            i++;
            if(k==n) break;
        }
        else if(S[i]==1 &&ctr!=n)
            i=(i+1)%n;
    }//endWhile
    if(k!=n)
    {
        printf("SYSTEM IS IN DEADLOCK!!!!");
        return;
    }
    int c;
    printf("Safe Sequence ");
    for(int j=0;j<k;j++)
    {
        printf("--->P%d",F[j]);
    }    
}
void Resource(int n, int inst, int PN[n], int max[n][inst], int need[n][inst], int allocate[n][inst], int available[inst])
{
    int pno,P[3],f=0;
    printf("Enter the process no having extra request: ");
    scanf("%d",&pno);
    printf("Enter the request row: ");
    for(int j=0;j<inst;j++)
    {
        scanf("%d",&P[j]);
    }
    for(int i=0;i<inst;i++)
    {
        if(P[i]<available[i] && P[i]<=need[pno][i])
            f=1;
        else
        {
            f=0;
            break;
        }
    }
    if(f==1)
    {
        printf("Resource can be allocated!! System will go to deadlock!!\n");
        for(int i=0;i<inst;i++)
        {
            available[i]-=P[i];
            need[pno][i]-=P[i];
        }
        safety(n,inst,PN,max,need,allocate,available);
    }
    else if(f==0)
        printf("Resource cannot be allocated to the request!!!");
}
void main()
{
    int choice;
    do
    {
        int n;
        printf("Enter the number of processes: ");
        scanf("%d", &n);
        int PN[n];
        printf("Enter the process numbers: ");
        for (int i = 0; i < n; i++)
        {
            scanf("%d", &PN[i]);
        }
        int inst;
        printf("Enter the number of instances: "); //resource a,b,c,d
        scanf("%d", &inst);
        int max[n][inst], allocate[n][inst], need[n][inst];
        printf("\nEnter the Max matrix:\n"); //total req resources
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < inst; j++)
                scanf("%d", &max[i][j]);
        }
        printf("Enter the Allocated matrix:\n");
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < inst; j++)
                scanf("%d", &allocate[i][j]);
        }
        int available[inst];
        printf("Enter the available array: ");
        for (int i = 0; i < inst; i++)
        {
            scanf("%d", &available[i]);
        }
        printf("\nNeed Matrix:\n");
        for (int i = 0; i < n; i++)
        {
            printf("P%d ", PN[i]);
            for (int j = 0; j < inst; j++)
            {
                need[i][j] = max[i][j] - allocate[i][j];
                printf("%d ", need[i][j]);
            }
            printf("\n");
        }
        int t, ch;

        printf("\nChoose: 1- Safety Algorithm OR 2-Resource Request Algorithm : ");
        scanf("%d", &ch);
        switch (ch)
        {
        case 1:
            safety(n, inst, PN, max, need, allocate, available);
            //if(t==0)
            //printf("\n SYSTEM IS IN DEADLOCK!!");
            break;
        case 2:
            Resource(n, inst, PN, max, need, allocate, available);
            break;
        default:
            printf("\nInvalid choice!!");
            break;
        }
        printf("\n\nDo you want to continue? Type 1 for yes and 0 for no: ");
        scanf("%d", &choice);
    } while (choice != 0);
}

