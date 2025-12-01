#include <stdio.h>
#include <limits.h>

#define MAX 50

typedef struct {
    int pid, at, bt, pr, bt_rem, ct, tat, wt, completed;
} Process;

void printTable(Process p[], int n){
    float avg_tat=0, avg_wt=0;
    printf("\nPID\tAT\tBT\tPR\tCT\tTAT\tWT\n");
    for(int i=0;i<n;i++){
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid,p[i].at,p[i].bt,p[i].pr,p[i].ct,p[i].tat,p[i].wt);
        avg_tat+=p[i].tat; avg_wt+=p[i].wt;
    }
    printf("\nAvg TAT = %.2f\nAvg WT  = %.2f\n", avg_tat/n, avg_wt/n);
}

void printGantt(int seq[], int st[], int et[], int count){
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

void priority_np(Process p[], int n){
    int time=0, completed=0;
    int seq[MAX], st[MAX], et[MAX], count=0;

    while(completed<n){
        int idx=-1, best=INT_MAX;
        for(int i=0;i<n;i++)
            if(!p[i].completed && p[i].at<=time && p[i].pr < best){
                best=p[i].pr;
                idx=i;
            }

        if(idx==-1){ time++; continue; }

        st[count]=time;
        seq[count]=p[idx].pid;

        time += p[idx].bt;
        et[count]=time;
        count++;

        p[idx].ct=time;
        p[idx].tat=time - p[idx].at;
        p[idx].wt =p[idx].tat - p[idx].bt;
        p[idx].completed=1;
        completed++;
    }

    printf("\n--- PRIORITY NON-PREEMPTIVE ---");
    printGantt(seq,st,et,count);
    printTable(p,n);
}

void priority_p(Process p[], int n){
    int time=0, completed=0, prev=-1;
    int seq[MAX], st[MAX], et[MAX], count=0;

    while(completed<n){
        int idx=-1, best=INT_MAX;
        for(int i=0;i<n;i++)
            if(!p[i].completed && p[i].at<=time && p[i].pr < best && p[i].bt_rem>0){
                best=p[i].pr;
                idx=i;
            }

        if(idx==-1){ time++; continue; }

        if(prev != idx){
            st[count]=time;
            seq[count]=p[idx].pid;
            if(count>0) et[count-1]=time;
            count++;
        }

        prev=idx;
        p[idx].bt_rem--;
        time++;

        if(p[idx].bt_rem==0){
            p[idx].completed=1;
            p[idx].ct=time;
            p[idx].tat=time - p[idx].at;
            p[idx].wt =p[idx].tat - p[idx].bt;
            completed++;
        }
    }

    et[count-1]=time;

    printf("\n--- PRIORITY PREEMPTIVE ---");
    printGantt(seq,st,et,count);
    printTable(p,n);
}

int main(){
    int n;
    printf("Enter number of processes: ");
    scanf("%d",&n);

    Process p[n], backup[n];

    for(int i=0;i<n;i++){
        p[i].pid=i+1;
        printf("Enter AT BT PRIORITY of P%d: ",i+1);
        scanf("%d%d%d",&p[i].at,&p[i].bt,&p[i].pr);
        p[i].bt_rem=p[i].bt;
        p[i].completed=0;
        backup[i]=p[i];
    }

    for(int i=0;i<n;i++) p[i]=backup[i];
    priority_np(p,n);

    for(int i=0;i<n;i++){ p[i]=backup[i]; p[i].bt_rem=p[i].bt; p[i].completed=0; }
    priority_p(p,n);

    return 0;
}
