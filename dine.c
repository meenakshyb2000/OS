#include<stdio.h>

int CHOPSTICKS[50];
int mutex=1;
int i=-1;
int L,R;
int n;
int wait(int a)
{
    return --a;
}
int signal(int a)
{
    return ++a;
}
void TAKE_CS()
{
    printf("\t---TAKING CHOPSTICKS---\n");
    mutex=wait(mutex);
    CHOPSTICKS[L]=wait(CHOPSTICKS[L]);
    CHOPSTICKS[R]=wait(CHOPSTICKS[R]);
    printf("\nTaking chopsticks %d and %d\n",L,R);
    mutex=signal(mutex);
}
void PUT_CS()
{
printf("\t---PUTTING DOWN CHOPSTICKS---\n");
    mutex=wait(mutex);
    CHOPSTICKS[L]=signal(CHOPSTICKS[L]);
    CHOPSTICKS[R]=signal(CHOPSTICKS[R]);
    printf("\nPutting down chopsticks %d and %d\n",L,R);
    mutex=signal(mutex);
   
}
void main()
{
    int ch,choice=1;
    printf("Enter the number of philosophers: ");
    scanf("%d",&n);
    for(int j=0;j<n;j++)
    CHOPSTICKS[j]=1;
    while(choice==1 && n!=0)
    {
        printf("Choose a philosopher from 0 to %d: ",n-1);
        scanf("%d",&i);
        if(i<0 || i>=n)
        {
        printf("\nInvalid choice!! EXITING\n");
        break;
        }
        L=(i+n-1)%n;
        R=(i)%n;
        printf("\nAVAILABLE OPTIONS:\n 1.TAKE_CHOPSTICKS\n 2.PUT_CHOPSTICKS\n 3.STOP");
        printf("\nEnter your choice: ");
        scanf("%d",&ch);
        switch(ch)
        {
            case 1: if(CHOPSTICKS[L]!=0 && CHOPSTICKS[R] !=0)
                    {
                        TAKE_CS();
                       
                    }
                    else
                    {
                        printf("\nPut down the chopsticks first!!\n");
                    }
                    break;
            case 2: if(CHOPSTICKS[L]!=1 && CHOPSTICKS[R] !=1)
                    {
                        PUT_CS();
                       
                    }
                    else
                    {
                        printf("\nChopsticks not taken!!\n");
                    }
                    break;
            case 3: printf("Stopping philosopher %d\n",i);
                    break;
            default: printf("Invalid choice!!! STOPPING PHILOSOPHER %d!!\n",i);
        }
        printf("Do you want to continue? Type 1 for yes and 0 for no: ");
        scanf("%d",&choice);
    }
}
