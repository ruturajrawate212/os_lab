#include <stdio.h>
#include <limits.h>

#define MAX 50

typedef struct {
    int pid, at, bt, ct, tat, wt;
} Process;

void printTable(Process p[], int n) {
    float avg_tat = 0, avg_wt = 0;
    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");
    for(int i=0;i<n;i++){
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid,p[i].at,p[i].bt,p[i].ct,p[i].tat,p[i].wt);
        avg_tat += p[i].tat;
        avg_wt  += p[i].wt;
    }
    printf("\nAverage TAT = %.2f\nAverage WT = %.2f\n", avg_tat/n, avg_wt/n);
}

void printGantt(int seq[],int st[],int et[],int count){
    printf("\nGantt Chart:\n");
    for(int i=0;i<count;i++) printf(" -------");
    printf("\n|");
    for(int i=0;i<count;i++) printf("  P%-3d |", seq[i]);
    printf("\n");
    for(int i=0;i<count;i++) printf(" -------");
    printf("\n0");
    for(int i=0;i<count;i++) printf("      %2d", et[i]);
    printf("\n");
}

int main(){
    int n;
    printf("Enter number of processes: ");
    scanf("%d",&n);

    Process p[n];

    for(int i=0;i<n;i++){
        p[i].pid=i+1;
        printf("Enter AT & BT of P%d: ",i+1);
        scanf("%d %d",&p[i].at,&p[i].bt);
    }

    // Sort by AT
    for(int i=0;i<n;i++)
        for(int j=i+1;j<n;j++)
            if(p[j].at < p[i].at){
                Process t = p[i]; p[i]=p[j]; p[j]=t;
            }

    int time=0;
    int seq[MAX], st[MAX], et[MAX], count=0;

    for(int i=0;i<n;i++){
        if(time < p[i].at) time = p[i].at;

        st[count]=time;
        seq[count]=p[i].pid;

        time += p[i].bt;
        et[count]=time;
        count++;

        p[i].ct = time;
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt  = p[i].tat - p[i].bt;
    }

    printGantt(seq,st,et,count);
    printTable(p,n);

    return 0;
}
