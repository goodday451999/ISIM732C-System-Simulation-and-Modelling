#include <iostream>
#include <vector>
#include <stdlib.h>
#include <algorithm>
#include <string>
#include <math.h>
#include <set>
#include <map>
#include <limits>
using namespace std;

/*
   Thrust remains constant at T = 1450N balacing the drag force (D)

   beta is used to calcuate the air density (roh) at height h.

   UNITS:

   Thrust: N (Newton)
   Weight: Kg
   wing_area: m^2
   roh0: kg/m^3
   height: m
   velocity: m/s^2
   dt: s

   dW/dt = -k where k = 0.013

   L (Lift) = (1/2)*(roh)*(V^2)*(Cl)*S
   D (Drag) = (1/2)*(roh)*(V^2)*(Cd)*S

   Cd = cd0 + K*(Cl^2)

   sigma = exp(height/beta) = roh/roh0 where roh0 is the air density at sea level

*/

double weight = 10000.0;
const int wing_area = 6, thrust = 1450, beta = 9296, height = 8000;
const double cd0 = 0.025, K = 0.035, k = 0.013, roh0 = 1.225, dt = 0.01;

double roh_calc() {
   double sigma = exp((-height)/(double)beta);
   double roh = (roh0 * sigma);
   return roh;
}

/*
  Considering P = (1/2)*(roh)*(V^2)*S = (thrust + sqrt((thrust*thrust) - 4*(cd0)*(K*weight*weight)))/(double)(2*cd0)
  for easier calulations.
*/
double p_cal() {
  double pval = ( thrust + sqrt( (thrust*thrust) - (4*(cd0)*(K*weight*weight)) ))/(double)(2*cd0);
  return pval;
}

double velocity() {
   double roh = roh_calc(), p = p_cal();
   return sqrt((2*p)/(double)(roh*wing_area));
}

int main()
{
  double distance = 0.0;
  /*
    1 hour = 360,000 seconds
  */
  for(int i=1;i<=360000;i++) {
    weight -= k;
    double new_velocity = velocity();
    distance += new_velocity*dt;
    cout << "W = " << weight << "  " << "V = " << new_velocity << " Distance coverd in dt = " << new_velocity*dt << endl;
  }
  cout << "Total distance (m) = " << distance << endl;
  return 0;
}
