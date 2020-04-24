#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdio>
#include <cmath>

using namespace std;

void main ()
{	


  const double pi = 3.141592654;                // Greek "pi"
  const double sp = 1368.0 * 3600.0 / 41860.0;  // solar constant
  //const double sp = 1368.0 * 3600.0;  // solar constant in J/m2/hr


  double lambda;
  double sumd;
  double sig;
  double eta;
  double sinbeta;
  double sb;
  double sotd;
  int day;
  int hour;
  double gross;
  int ndays[12],dm;
  double lat,sumday;

  //lat = 45.1878;
  lat = 38.9;
  sumday = 0.;

  ndays[0] = 31;
  ndays[1] = 28;
  ndays[2] = 31;
  ndays[3] = 30;
  ndays[4] = 31;
  ndays[5] = 30;
  ndays[6] = 31;
  ndays[7] = 31;
  ndays[8] = 30;
  ndays[9] = 31;
  ndays[10] = 30;
  ndays[11] = 31;

  lambda = lat * pi / 180.0;

  for ( dm = 0; dm < 12; dm++ ) {
	  
  gross = 0.0;
  for ( day = 0; day < ndays[dm]; day++ )
  {

    ++sumday;
    sumd = 0;
    sig = -23.4856*cos(2 * pi * (sumday + 10.0)/365.25);
    sig *= pi / 180.0;

    for ( hour = 0; hour < 24; hour++ )
    {
      eta = (double) ((hour+1) - 12) * pi / 12.0;
      sinbeta = sin(lambda)*sin(sig) + cos(lambda)*cos(sig)*cos(eta);
      sotd = 1 - (0.016729 * cos(0.9856 * (sumday - 4.0) * pi / 180.0));
      sb = sp * sinbeta / pow(sotd,2.0);
      if (sb >= 0.0) { sumd += sb; }
    }

    gross += sumd;
  }

  gross /= (double) ndays[dm];

  gross = gross*41860/(24.*3600.);  // convert back to W/m2

  cout << dm+1 << " " << gross << endl;

}

};
