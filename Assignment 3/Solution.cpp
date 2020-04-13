#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>

#include<bits/stdc++.h>
using namespace std;
int main() {
   int n;
   cin>>n;
   int p;
   int q;
   cin>>p>>q;
   
   vector<int> vec;
   for(int i=0; i<n; i++){
       int x;
       cin>>x;
       vec.push_back(x);
   }
    
   int initial_inventory = 115;
   float total_cost = 0;
   int demand = 0;
   int day = 0;
   
   for(int i=0; i<n; i++){
       if(day==i){
           initial_inventory += demand;
           demand = 0;
       }
       if(initial_inventory>=vec[i]){
           initial_inventory -= vec[i];
           total_cost += (initial_inventory*0.75);
       }
       else{
           total_cost += (vec[i]-initial_inventory)*18;
           initial_inventory=0;
       }
       if((initial_inventory+demand)<=p){
           total_cost+=75;
           demand = q;
           day = i+3;
       }
   }
   cout<<total_cost<<endl;   
   return 0;
}
