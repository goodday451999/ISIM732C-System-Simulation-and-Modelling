#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int main() {
    int n;
    cin >> n;
    
    double a, b;
    cin >> a >> b;
    double shooterX[n+2];
    double shooterY[n+2];
    shooterX[0] = a;
    shooterY[0] = b;
    
    double bomberX[n+2];
    double bomberY[n+2];
    for(int i = 0 ; i < n+1; i++){
        cin >> bomberX[i] >> bomberY[i];
    }
    
    double vel = 20;
    double dist;
    int check = 1;
    for(int i = 0; i < n ; i++){
        dist = sqrt(pow(bomberX[i]-shooterX[i], 2)+pow(bomberY[i]-shooterY[i], 2));
        if(dist < 10){
                check=0;
                cout << i << endl;
                printf("%.2f", dist);
                break;
        }
        shooterX[i+1]=shooterX[i]+vel*((bomberX[i]-shooterX[i])/dist);
        shooterY[i+1]=shooterY[i]+vel*((bomberY[i]-shooterY[i])/dist);
    }
    // for(int i = 0 ; i <= n+1; i++){
    //     cout << shooterX[i] << " " << shooterY[i] << endl;
    // }
    if(check == 1)
    {
        cout << -1 << endl;
    }
    return 0;
}
