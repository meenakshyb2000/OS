#include<stdio.h>
#include<limits.h>

void sort(int l, int n, float a[], float b[], int c[],float d[])
{
    for(int i=l;i<n-1;i++)//Bubble sort
    {
        for(int j=l;j<n-i-1;j++)
        {
            if(a[j]>a[j+1])
            {
                float temp=a[j];
                a[j]=a[j+1];
                a[j+1]=temp;
                int tempb=b[j];
                b[j]=b[j+1];
                b[j+1]=tempb;
                int tempc=c[j];
                c[j]=c[j+1];
                c[j+1]=tempc;
                float tempd=d[j];
                d[j]=d[j+1];
                d[j+1]=tempd;
            }
        }
    }
}
void FCFS(int n,int PN[],float AT[],float BT[],float PT[])
{
    printf("\n\t--------FIRST COME FIRST SERVE--------\n");
    sort(0,n, AT, BT,PN,PT); 
    printf("Gantt chart:\n");
    float TAT=AT[0]; //here TAT denotes total completion time
    float sumTAT=TAT;
    float sumWT=TAT;
    for(int i=0;i<n;i++)
    {
        printf("    P%d: %f  -  ",PN[i],TAT);
        TAT=TAT+BT[i];
        printf("%f\n",TAT);
        sumWT=sumWT+TAT-AT[i]-BT[i];  //WT= TAT-BT
        sumTAT=sumTAT+TAT-AT[i];    //TAT=completion time of a process - AT
    }
    float num=n;
    float av=sumTAT/num;
    printf("Average Turn Around Time: %f", av);
    av=sumWT/num;
    printf("\nAverage Waiting Time: %f",av);
}
void SJF(int n,int PN[],float AT[],float BT[],float PT[])
{
    printf("\n\t--------SHORTEST JOB FIRST--------\n");
    sort(0,n,AT,BT,PN,PT);
    for(int i=0;i<n;i++)
    {
        for(int j=i+1;j<n;j++)
        {
            if(AT[i]==AT[j])
                sort(i,j+1,BT,AT,PN,PT); //sort on the basis of burst time
        }
    }
    float TAT=AT[0];
    float sumTAT=TAT-AT[0];
    float sumWT=TAT-AT[0];
    printf("Gantt chart:\n");
    printf("    P%d: %f  -  ",PN[0],TAT);
    TAT=TAT+BT[0];
    sumTAT=sumTAT+TAT-AT[0];
    sumWT=sumWT+TAT-AT[0]-BT[0];
    printf("%f\n",TAT);
    int j=0;
    for(int i=0;i<n-1;i++)
    {
        for(;j<n-1-i;j++) //removing elements already displayed
        {
            PN[j]=PN[j+1];
            AT[j]=AT[j+1];
            BT[j]=BT[j+1];
            }
        sort(0,(n-1-i),BT,AT,PN,AT);
        for(int k=0;k<n-1-i;k++)
        {
            if(AT[k]<TAT)  //if process has arrived
            {
                printf("    P%d: %.2f-",PN[k],TAT);
                TAT=TAT+BT[k];
                sumTAT=TAT+sumTAT-AT[k];
                sumWT=sumWT+TAT-BT[k]-AT[k];
                printf("%.2f\n",TAT);
                j=k;
                break;
            }
        }
    }
    printf("Average Turn Around Time: %f",sumTAT/n);
    printf("\nAverage Waiting Time: %f",sumWT/n);
}
void RR(int n,int PN[],float AT[],float BT[],float PT[])
{
    sort(0,n,AT,BT,PN,PT);
    float q;
    printf("\n\t--------ROUND ROBIN--------\n");
    printf("Enter Time Quantum: ");
    scanf("%f",&q);
    float count=0; 
    float countAT=0, countBT;
    for(int i=0;i<n;i++)
    {
        count+=BT[i]; //sum of burst time
        countAT+=AT[i]; //sum of arrival times
    }
    countBT=count;
    float TAT=AT[0];
    float sumTAT=TAT;
    float sumWT=TAT;
    int i=0;
    printf("Gantt chart:\n");
    while(count>0) //all processes not completed
    {
        if(BT[i]>q) 
        {
            printf("    P%d: %f-",PN[i],TAT);
            BT[i]=BT[i]-q;
            TAT=TAT+q;
            count=count-q;
            printf("%f\n",TAT);
        }
        else if(BT[i]>0&&BT[i]<=q)
        {
            printf("    P%d: %f-",PN[i],TAT);
            TAT=TAT+BT[i];
            count=count-BT[i];
            BT[i]=0;
            sumTAT=sumTAT+TAT;
            sumWT=sumWT+TAT;
            printf("%f\n",TAT);
        }
        if(i<n-1)
            i++;
        else
            i=0;
    }
    sumTAT-=countAT;
    sumWT=sumWT-countAT-countBT;
    printf("Average Waiting Time: %f",sumWT/n);
    printf("\nAverage Turn Around Time: %f",sumTAT/n);
}
void PS(int n,int PN[],float AT[],float BT[],float PT[])
{
    printf("\n\t--------PRIORITY SCHEDULING--------\n");
    sort(0,n,AT,BT,PN,PT);
    for(int i=0;i<n;i++)
    for(int j=i+1;j<n;j++)
    {
        if(AT[i]==AT[j])
            sort(i,j+1,PT,AT,PN,BT);
    }
    float TAT=AT[0];
    float sumTAT=TAT;
    float sumWT=TAT;
    printf("Gantt chart: \n");
    printf("    P%d: %f-",PN[0],TAT);
    TAT=TAT+BT[0];
    sumTAT=sumTAT+TAT-AT[0];
    sumWT=sumWT+TAT-BT[0]-AT[0];
    printf("%f\n",TAT);
    int j=0;
    for(int i=0;i<n-1;i++)
    {
        for(;j<n-1-i;j++)
        {
            PN[j]=PN[j+1];
            AT[j]=AT[j+1];
            BT[j]=BT[j+1];
            PT[j]=PT[j+1];
        }
        sort(0,(n-1-i),PT,AT,PN,BT);
        for(int k=0;k<n-1-i;k++)
        {
            if(AT[k]<TAT)
            {
                printf("    P%d: %f-",PN[k],TAT);
                TAT=TAT+BT[k];
                sumTAT=TAT+sumTAT-AT[k];
                sumWT=sumWT+TAT-BT[k]-AT[k];
                printf("%f\n",TAT);
                j=k;
                break;  
            }
        }
    }
    printf("Average Turn Around Time: %f",sumTAT/n);
    printf("\nAverage Waiting Time: %f",sumWT/n);
}
void main()
{
    int n,choice;
    do
    {
        printf("Enter the number of processes: ");
        scanf("%d",&n);
        int pronum[n];
        printf("Enter the process numbers: ");
        for(int i=0;i<n;i++)
            scanf("%d",&pronum[i]);
        float AT[n];
        float PRIORITY[n];
        printf("\nEnter the Arrival time for each process:\n");
        for(int i=0;i<n;i++)
        {
            printf("Process %d: ",pronum[i]);
            scanf("%f",&AT[i]);
            PRIORITY[i]=0;
        }
        float BT[n];
        printf("\nEnter the Burst time for each process:\n");
        for(int i=0;i<n;i++)
        {
            printf("Process %d: ",pronum[i]);
            scanf("%f",&BT[i]);
        }
        printf("\nAVAILABLE CPU SCHEDULING ALGORITHMS:");
        printf("\n  1. First Come First Serve(FCFS)");
        printf("\n  2. Shortest Job First(SJF)");
        printf("\n  3. Round Robin(RR)");
        printf("\n  4. Priority Scheduling(PS)");
        int ch;
        printf("\nEnter your choice: ");
        scanf("%d",&ch);
        switch (ch)
        {
            case 1:FCFS(n,pronum, AT,BT,PRIORITY);
            break;
            case 2:SJF(n,pronum, AT, BT,PRIORITY);
            break;
            case 3:RR(n,pronum, AT,BT,PRIORITY);
            break;
            case 4:
            {
                printf("Enter the priority of each process:\n");
                for(int i=0;i<n;i++)
                {
                    printf("    Process %d: ",pronum[i]);
                    scanf("%f",&PRIORITY[i]);
                }
                PS(n,pronum, AT,BT,PRIORITY);
            }
            break;
            default:printf("\nInvalid choice!!!");
            break;
        }
        printf("\n\nDo you want to continue? Type 1 for yes and 0 for no: ");
        scanf("%d",&choice);
    }while(choice!=0);
}