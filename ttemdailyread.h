/* *************************************************************
TTEMDAILYREAD.H - object to read and write the structure of the
	          output data from files generated by the
	          Terrestrial Ecosystem Model (TEM)


************************************************************* */

#ifndef TTEMDAILYREAD_H
#define TTEMDAILYREAD_H

#include "temconstsd.hpp"

class Temdailyread
{

  public:

     Temdailyread( void );

/* *************************************************************
		 Public Functions
************************************************************* */


     int getdel( FILE* ifile );

     int getdel_leap( FILE* ifile );

/* *************************************************************
		 Public Variables
************************************************************* */

/* NOTE:  substitute "daily" for "monthly" if CYCLE = 365 rather
          than CYCLE = 12 */

     // mean annual value for the grid cell
     double ave;

     // area covered by grid cell (square kilometers)
     long carea;

     // Index for community type
     int cmnt;

     // column or longitude of grid cell (degrees)
     float col;

     // Current vegetation type in grid cell
     int currentveg;

     // Cohort index
     int icohort;

     // maximum monthly value for the grid cell
     double max;

     // minimum monthly value for the grid cell
     double min;

     // monthly values of the TEM output variable for the
     //   grid cell

     int CYCLE;

     double mon[366];

     // Potential vegetation type of grid cell
     //   (categorical data)
     int potveg;

     // percent silt plus percent clay of the grid cell
     double psiplusc;

     // quality control flag
     int qlcon;

     // name of region containing grid cell
     string region;

     // row or latitude of grid cell (degrees)
     float row;

    // Stand age of cohort
     int standage;

     // area covered by cohort in a grid cell
     //   (square kilometers)
     long subarea;

     // vegetation subtype of grid cell (categorical data)
     int subtype;

     // annual sum of monthly data for the grid cell
     double total;

     // name of TEM output variable
     string varname;


     // date (year) of data (transient version of TEM)
     //   or number of years until equilibrium are met
     //  (equilibrium version of TEM)
     int year;

  private:

/* ************************************************************
		      Private Variables
************************************************************ */

     int temend;
     long curpos;
     long lagpos;

};

#endif

