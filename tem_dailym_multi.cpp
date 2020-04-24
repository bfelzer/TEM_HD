#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdio>
#include <string>
#include <cstdlib>
#include <vector>

using namespace std;

int gisend,yr,icht,leap,i,j,l,grid;
double v[366][94],ndays[12],mon[366],ngrid;
char file[100];
string infile, chrtfname, outfile;
int startyr, lastyr, firstchrtyr, tlulcflag;

#include "ttemdailyread.h"
#include "tmaxcohortdat45.h"

        Temdailyread temdat;
        MaxCohortdat45 mxdat;
        FILE* ifile;
        FILE* itfile;

int main ()
{


   cout << endl << "Enter the name of the input file: ";

   cin >> infile;

   cout << endl << "Enter the name of the mxcohort file: ";

   cin >> chrtfname;

   cout << endl << "number of grids of same area ";

   cin >> ngrid;

    cout << "Enter the first year in the input file: ";

    cin >> startyr;

    cout << "Enter the last year in the input file: ";

    cin >> lastyr;

    cout << "Does land cover change over time in the output: ";
    cout << endl;
    cout << "Enter 0 for no changes in land cover: " << endl;
    cout << "Enter 1 for changing land cover: " << endl;

    cin >> tlulcflag;

    if( 1 == tlulcflag )
    {
      cout << "Enter the first year of the maximum number of ";
      cout << "cohorts data: " << endl;

      cin >> firstchrtyr;
    }

   cout << endl << "Enter the name of the output file: ";

   cin >> outfile;

//   tarea = 142.0;

//    ifile = fopen("/share/partition7/bfelzer/tem/msb_lulc/crumxcohrts1895_2011.hvd", "r");
    ifile = fopen(chrtfname.c_str(), "r");

        if (!ifile){
                cerr << "lulc file could not be opened\n";
                exit(1);
        }

//    itfile = fopen("/share/partition7/tem/temhydro_combo/temhydro_cwd/NEP_MONTR.HVD", "r");
    itfile = fopen( infile.c_str(), "r");

        if (!itfile){
                cerr << "tem file could not be opened\n";
                exit(1);
        }

        ofstream fout;
//        fout.open("/share/partition7/tem/temhydro_combo/temhydro_cwd/sum_mon_NEP_MONTR.HVD", ios::out);
        fout.open(outfile.c_str(), ios::out);

       if(tlulcflag == 1)
       {
        if(firstchrtyr < startyr)
        {
        gisend = mxdat.getdel(ifile);
        }
       }
       if(tlulcflag == 0)
       {
        gisend = mxdat.getdel(ifile);
       }

         for(j=0; j< 94; j++)
         {
         for(i=0; i < 366; i++)
         {
         v[i][j] = 0.0;
         }
         }


//        for(yr=1896; yr<2007; yr++) {

        for(grid = 0; grid<ngrid; grid++) {
        for(yr=startyr; yr<lastyr + 1; yr++) {

        cout << "grid, year = " << grid << " " << yr << endl;

      if((yr%4) == 0)  
      {
        leap = 1;
      }
      else
      {
        leap = 0;
      }

    ndays[0] = 31;
    if(leap == 1)
    {
    ndays[1] = 29;
    }
    else
    {
    ndays[1] = 28;
    }
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

    l=0;
    for(j=0; j < 12; j++)
    {
    for(i = 0; i < ndays[j]; i++)
    {
      mon[l] = j+1;
      l=l+1;
    }
    }

          if(tlulcflag == 1)
          {
	   gisend = mxdat.getdel(ifile);
          }
         cout << "cohorts = " << mxdat.total << endl;
         for(icht = 0; icht < mxdat.total; icht++) {
         if(leap == 1) 
         {
         gisend = temdat.getdel_leap(itfile);
//         if(temdat.subarea == 1) { temdat.subarea = 0;}
//         cout << "reading in leap = " << temdat.year << " " << temdat.subarea << " " << temdat.region << endl;
         for(i=0; i < 366; i++)
         {
            v[i][yr-startyr] = v[i][yr-startyr] + temdat.mon[i];
//cout << "diag = " << temdat.mon[i] << " " << grid << " " << i << " " << yr << endl;
//if(yr-startyr == 0 && i == 0) {cout << "diag = " << temdat.mon[i] << " " << grid << endl;}
//            cout << "leap diag = " << i << " " << temdat.mon[i] << " " << temdat.subarea << " " << tarea << endl;
         }
         }
         else
         {
         gisend = temdat.getdel(itfile);
//         if(temdat.subarea == 1) { temdat.subarea = 0;}
//         cout << "reading in nonleap = " << temdat.year << " " << temdat.subarea << " " << temdat.region << endl;
         for(i=0; i < 365; i++)
         {
            v[i][yr-startyr] = v[i][yr-startyr] + temdat.mon[i];
//cout << "diag = " << temdat.mon[i] << " " << grid << " " << i << " " << yr << endl;
//if(yr-startyr == 0 && i == 0) {cout << "diag = " << temdat.mon[i] << " " << grid << endl;}
//         cout << "nonleap diag = " << i << " " << temdat.mon[i] << " " << temdat.subarea << endl;
         }

         }

            }  // cohort loop
         }  // year loop
         }  // grid loop

       for(yr=startyr; yr<lastyr + 1; yr++) {

      if((yr%4) == 0)
      {
        leap = 1;
      }
      else
      {
        leap = 0;
      }

        if(leap == 1)
        {
         for(i=0; i < 366; i++)
         {
          fout << yr << " " << i+1 << " " << mon[i] << " " << v[i][yr-startyr] << endl;
         }
        }
        else
        {
         for(i=0; i < 365; i++)
         {
          fout << yr << " " << i+1 << " " << mon[i] << " " << v[i][yr-startyr] << endl;
         }

        }

         }  // year loop



	fclose( ifile );
	fclose( itfile );
        fout.close();

};
