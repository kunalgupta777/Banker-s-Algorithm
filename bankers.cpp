/// bankers algorithm
#include<iostream>
#include<graphics.h>
using namespace std;

void bankers(int n, int m, int avail[] ,int Max[][100], int Allocated [][100], int Need[][100],int safe_state[],int I,int N)
{
    if(N==0)  /// is N is zero , this means all process are there in safe state of that the system is safe!
    {
        cout<<"\nSafe State!!";
        cout<<"\nOne Possible Safe Sequence is: ";
        for(int i = 0;i<n;i++)
        {
            cout<<"P-"<<safe_state[i]<<"\t";  /// the vector safe_sequence holds the ID of processes as per the safe sequence
        }
        getch();
        exit(1);
    }
    else
    {
        for(int i =0;i<n;i++) /// We'll scan all process in increasing order of their ID to check whether their need can be
        {   int fg = 0;       /// fulfilled currently or not
            for(int j=0;j<I;j++)   /// No process is to be visited again if it's already in the safe state
            {
                if(safe_state[j]==i)
                {
                    fg=1;
                }
            }
             if(fg==0){
                    int flag = 0;

                    for(int z =0;z<m;z++)
                    {
                        if(Need[i][z]>avail[z])   /// the particular process must be having its needs <= Available else we'll skip it
                        {
                            flag = 1;
                            break;
                        }
                    }
                    if(flag==0)
                    {
                        safe_state[I++] = i;   /// if a process is selected then we add it to the safe_state vector
                        for(int z =0;z<m;z++)
                    {
                        avail[z]+=Allocated[i][z];   /// Now we free up the held up resources and also make Need as zero
                        Need[i][z] = 0;
                    }
                        bankers(n,m,avail,Max,Allocated,Need,safe_state,I,N-1);    /// recursive call again to repeat above procedure with one less process
                    }
             }
        }
        if(n==N)  /// if originally all processes didnt come in safe_state then its a safe sequence
        {
            cout<<"\nUnsafe State!!!";
        }
        else   /// otherwise we know we're in a subproblem and we'll go back!
        {
            return;
        }
    }
}
int main()
{
    cout<<"\n-----Banker's Algorithm Implementation!!!-----";
    cout<<"\nEnter The Number of Processes:";
    int n;
    cin>>n;
    cout<<"\nEnter the number of resource types:";
    int m;
    cin>>m;
    int avail[m];
    for(int i =0;i<m;i++)
    {
        cout<<"\nEnter the Available Resource of Instance #"<<i<<":";
        cin>>avail[i];
    }
    int Max[n][100];  /// This matrix contains Maximum required resources of each type by each process
    int Allocated[n][100]; /// This Matrix contains the currently Allocated resources of each type to each Process
    int Need[n][100]; /// This is simply Max - Allocated
    for(int i =0;i<n;i++)
    {
        for(int j = 0;j<m;j++)
        {
            cout<<"\nEnter Maximum Demand and Allocated Instance of Resource #"<<j<<" for Process #"<<i<<":";
            cin>>Max[i][j]>>Allocated[i][j];
            Need[i][j] = Max[i][j] - Allocated[i][j];
        }
    }
    int safe_state[n];
    for(int i=0;i<n;i++){safe_state[i]=i;}
    bankers(n,m,avail,Max,Allocated,Need,safe_state,0,n);  /// function call

}
