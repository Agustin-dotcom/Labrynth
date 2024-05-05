#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <stdbool.h>

void unstep(int S,int *currentLocation){
    switch (S){
        case 1:
            currentLocation[0] = currentLocation[0] + 1;
            break;
        case 2:
            currentLocation[1] = currentLocation[1] - 1;
            break;
        case 3:
            currentLocation[0] = currentLocation[0] - 1;
            break;
        case 4:
            currentLocation[1] = currentLocation[1] + 1;
            break;
    }
}
void step(int S,int *currentLocation){
    switch (S){
        case 1:
            currentLocation[0] = currentLocation[0] - 1;
            break;
        case 2:
            currentLocation[1] = currentLocation[1] + 1;
            break;
        case 3:
            currentLocation[0] = currentLocation[0] + 1;
            break;
        case 4:
            currentLocation[1] = currentLocation[1] - 1;
            break;
    }
}

void toString (int n,int m,bool matrix[n+2][m+2]){
    for (int i = 0; i < n+2; ++i) {
        for (int j = 0; j < m+2; ++j) {
            if(matrix[i][j])
                printf("M ");
            else
                printf("  ");
        }
        printf("\n");
    }
}

/*                 1
 *                 A
 *                 |
 *         4 <-----------> 2
 *                 |
 *                 V
 *                 3
 *
 * */
int main() {
   int n = 7;
   int m = 5;
    int bushes = 12;
    int currentLocation[2] = {2,0};
    int i = 0;
    int minimumPath = INT_MAX;
//    printf("n:");
//    scanf("%d",&n);
//    printf("bushes:");
//    scanf("%d",&bushes);
    int S[n*m - bushes];
    int snapshot[n*m-bushes];
    for (int i = 0; i < n * m - bushes; ++i) {
        S[i] = 0;
        snapshot[i]=0;
    }
    bool visited[n+2][m+2];
    for (int i = 0; i < n + 2; ++i) {
        for (int j = 0; j < m + 2; ++j) {
            visited[i][j] = false;
        }
    }
    for (int i = 0; i < n+2; ++i) {
        visited[i][0] = true;
        visited[i][m+2-1] = true;
        visited[0][i] = true;
        visited[n+2-1][i] = true;
    }
    visited[1][1] = true;
    visited[1][2] = true;
    visited[1][m+2-2]=true;
    visited[2][m+2-2] = true;
    visited[2][m+2-3] = true;
    visited[3][1] = true;
    visited[3][2] = true;
    visited[4][4] = true;
    visited[6][1] = true;
    visited[6][3] = true;
    visited[7][1] = true;
    visited[7][m+2-2] = true;
    //visited[][] = false;
    //visited[2][0]=false;
    visited[n+2-1][4]=false;
    toString(n,m,visited);

//    srand((unsigned)time(NULL));
//    for (int i = 0; i < rand() % n; ++i) {
//
//    }
    while(i < n*m-bushes){// Worst case scenario we are going to have O(4^(n*m-bushes))
        S[i]++;
        if(S[i] == 5){//BT node
            //BT actions
            if(i==0){
                printf("(");
                for (int i = 0; i < n * m - bushes; ++i) {
                    printf("%d,",snapshot[i]);
                }
                printf(")\n");
                return 0;
            }else{
                S[i] = 0;
                visited[currentLocation[0]][currentLocation[1]] = false;
                unstep(S[i-1],currentLocation);
                i--;
            }
        }else{
            step(S[i],currentLocation);
            if(visited[currentLocation[0]][currentLocation[1]] || currentLocation[0]<0||currentLocation[0]>n+2-1||currentLocation[1]<0||currentLocation[1]>m+2-1)
                unstep(S[i],currentLocation);
            else{
                visited[currentLocation[0]][currentLocation[1]] = true;
                i++;
                if(currentLocation[0]==n+2-1 && currentLocation[1] == 4){
                    if(i < minimumPath){
                        minimumPath = i;
                        for (int i = 0; i < n * m - bushes; ++i) {
                            snapshot[i] = S[i];
                        }
                    }
                }
            }
        }
    }
}