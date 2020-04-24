#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdio>
#include <string>
#include <cstdlib>
#include <vector>

using namespace std;

int gisend,yr,icht,leap,i,j,l,grid;
double v[366][56],ndays[12],mon[366],ngrid;
char file[100];
string infile, chrtfname, outfile;
int startyr, lastyr; 

#include "tclmdatd.h"

        Clmdat45 clmdat;
        FILE* itfile;

int main ()
{


   cout << endl << "Enter the name of the input file: ";

   cin >> infile;

   cout << endl << "number of grids of same area ";

   cin >> ngrid;

    cout << "Enter the first year in the input file: ";

    cin >> startyr;

    cout << "Enter the last year in the input file: ";

    cin >> lastyr;


   cout << endl << "Enter the name of the output file: ";

   cin >> outfile;

    itfile = fopen( infile.c_str(), "r");

        if (!itfile){
                cerr << "tem file could not be opened\n";
                exit(1);
        }

        ofstream fout;
//        fout.open("/share/partition7/tem/temhydro_combo/temhydro_cwd/sum_mon_NEP_MONTR.HVD", ios::out);
        fout.open(outfile.c_str(), ios::out);


         for(j=0; j< 56; j++)
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

         if(leap == 1) 
         {
         for(i=0; i < 366; i++)
         {
            gisend = clmdat.getdel(itfile,i);           
            v[i][yr-startyr] = v[i][yr-startyr] + clmdat.mon[i];
//            cout << "clmdat leap =  " << clmdat.mon[i] << " " << i << " " << clmdat.col << " " << clmdat.row << " " << clmdat.year << " " << clmdat.month << " " << clmdat.day << endl;
         }
         }
         else
         {
         for(i=0; i < 365; i++)
         {
            gisend = clmdat.getdel(itfile,i);
            v[i][yr-startyr] = v[i][yr-startyr] + clmdat.mon[i];
if(clmdat.day == 3 && clmdat.month == 1 && clmdat.year == 1950)  { cout << "clmdat =  " << clmdat.mon[i] << " " << i << " " << clmdat.col << " " << clmdat.row << " " << clmdat.year << " " << clmdat.month << " " << clmdat.day << " " << yr-startyr << " " << v[i][yr-startyr] << endl;}
         }

         }

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



	fclose( itfile );
        fout.close();

};
