#include<bits/stdc++.h>
#define ll long long 
#define pb push_back
using namespace std;

ll m = 2147483649;// 2^31 + 1
ll seed = 1e4 + 6;
ll a = 259;// k(32)*8 + 3
ll mu = 1e9 + 7;
ll previ;
double chi = 0;
vector <double> inbuilt_random_array;
vector <double> additive_random_array;
vector <double> multiplicative_random_array; 
vector <double> mixed_random_array;
int inbuilt_random_count_array[11];
int additive_random_count_array[11];
int multiplicative_random_count_array[11];
int mixed_random_count_array[11];
int tc;
ofstream myfile;
int main()
{
  //INBUILT SUDO RANDOM NUMBER GENERATION
  srand(time(NULL));
  tc = 1000;
  myfile.open ("Inbuilt.txt");
  while(tc--)
  {
    ll n = rand() % m;
    double num = (double)(n);
    num /= (m-1);
    inbuilt_random_array.pb(num);
    myfile << num << " "; 
  }
  for (auto it : inbuilt_random_array)
  {
    int generated_num = (int)(it * 10);
    inbuilt_random_count_array[generated_num]++;
  }
  //CALCULATING VALUE OF CHI SQUARE FOR INBUILT RANDOM FUNCTION
  cout << "INBUILT RANDOM\n";
  for (int i = 0; i < 10; ++i)
  {
    double val = (inbuilt_random_count_array[i] - 100);
    cout << inbuilt_random_count_array[i] << "\n";
    val *= val;
    chi += val/100;
  }
  cout << "chi value is : " << chi << "\n\n";
  myfile.close();

  //MULTIPLICATIVE SUDO RANDOM NUMBER GENERATION 
  tc = 1000;
  previ = seed;
  myfile.open ("Multiplicative.txt");
  while(tc--)
  {
    double num = (double)(previ % m);
    num /= (m-1);
    multiplicative_random_array.pb(num); 
    previ = (previ * a) % m;
    myfile << num << " ";
  }
  for (auto it : multiplicative_random_array)
  {
    int generated_num = (int)(it * 10);
    multiplicative_random_count_array[generated_num]++;
  }
  //CALCULATING VALUE OF CHI SQUARE FOR MULTIPLICATIVE RANDOM 
  chi = 0;
  cout << "MULTIPLICATIVE RANDOM\n";
  for (int i = 0; i < 10; ++i)
  {
    double val = (multiplicative_random_count_array[i] - 100);
    cout << multiplicative_random_count_array[i] << "\n";
    val *= val;
    chi += val/100;
  }
  cout << "chi value is : " << chi << "\n\n";
  myfile.close();

  //ADDITIVE SUDO RANDOM NUMBER GENERATION 
  tc = 1000;
  previ = seed;
  myfile.open ("Additive.txt");
  while(tc--)
  {
    double num = (double)(previ % m);
    num /= (m-1);
    // cout << num << " ";
    additive_random_array.pb(num); 
    previ = (previ + mu) % m;
    myfile << num << " ";
  }
  for (auto it : additive_random_array)
  {
    int generated_num = (int)(it * 10);
    additive_random_count_array[generated_num]++;
  }
  //CALCULATING VALUE OF CHI SQUARE FOR ADDITIVE RANDOM 
  chi = 0;
  cout << "ADDITIVE RANDOM\n";
  for (int i = 0; i < 10; ++i)
  {
    double val = (additive_random_count_array[i] - 100);
    cout << additive_random_count_array[i] << "\n";
    val *= val;
    chi += val/100;
  }
  cout << "chi value is : " << chi << "\n\n";
  myfile.close();

  //MIXED SUDO RANDOM NUMBER GENERATION 
  tc = 1000;
  previ = seed;
  myfile.open ("Mixed.txt");
  while(tc--)
  {
    double num = (double)(previ % m);
    // cout << num << " ";
    num /= (m-1);
    mixed_random_array.pb(num); 
    previ = (previ * a + mu) % m;
    myfile << num << " ";
  }
  for (auto it : mixed_random_array)
  {
    int generated_num = (int)(it * 10);
    mixed_random_count_array[generated_num]++;
  }
  //CALCULATING VALUE OF CHI SQUARE FOR MIXED RANDOM 
  chi = 0;
  cout << "MIXED RANDOM\n";
  for (int i = 0; i < 10; ++i)
  {
    double val = (mixed_random_count_array[i] - 100);
    cout << mixed_random_count_array[i] << "\n";
    val *= val;
    chi += val/100;
  }
  cout << "chi value is :" << chi << "\n\n";
  myfile.close();
  return 0;
}