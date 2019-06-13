/*
	Author: Jose Rodriguez
	CS 341 Spring 2018
	University of Illinois at Chicago

	Classes for use with Chicago Crime Analysis program,
	CrimeReport and CrimeCode.
*/

#pragma once

#include <iostream>
#include <string>

using namespace std;

/* This class contains the info for each Crime Code */
class CrimeCode
{
	private:
		string IUCR;
		string Primary_Descr;
		string Secondary_Descr;
		int    Count;

	public:
		// Constructor
		CrimeCode(string iucr, string primary_d, string secondary_d, int count)
			: IUCR(iucr), Primary_Descr(primary_d), Secondary_Descr(secondary_d),
				Count(count)
		{ }


		string getIUCR() const
		{
			return IUCR;
		}


		string getPrimeDescription() const
		{
			return Primary_Descr;
		}


		string getSecondaryDescription() const
		{
			return Secondary_Descr;
		}


		int getCount() const
		{
			return Count;
		}


		void incrementCount()
		{
			Count += 1;
		}
};


/* This class contains info for each Crime Report */
class CrimeReport
{
	private:
		string Date_Time;
		string IUCR;
		string Arrest;
		string Domestic;
		int    Beat;
		int    District;
		int    Ward;
		int    Community;

	public:
		CrimeReport(string d_t, string iucr, string arrest, string domestic,
					int beat, int dist, int w, int com)
			: Date_Time(d_t), IUCR(iucr), Arrest(arrest), Domestic(domestic),
				Beat(beat), District(dist), Ward(w), Community(com)
		{ }


		string getDateAndTime() const
		{
			return Date_Time;
		}


		string getIUCR() const
		{
			return IUCR;
		}


		string isArrest() const
		{
			return Arrest;
		}


		string isDomestic() const
		{
			return Domestic;

		}


		int getBeat() const
		{
			return Beat;
		}


		int getDistrict() const
		{
			return District;
		}


		int getWard() const
		{
			return Ward;
		}


		int getCommunity() const
		{
			return Community;
		}
};
