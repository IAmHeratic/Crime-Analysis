/*
	Author: Jose Rodriguez
	CS 341 Spring 2018
	University of Illinois at Chicago
	Visual Studio 2017

	Chicago Crime Analysis program in modern C++.
*/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>

#include "classes.h"

using namespace std;


/* Read in from crime codes file and insert data in vector */
void processCrimeCodes(string crimeCodesFilename, vector<CrimeCode> &crimeCodes)
{
	string   line, iucr, pri_desc, sec_desc;
	ifstream codesFile(crimeCodesFilename);

	if (!codesFile.good())
	{
		cout << "**ERROR: cannot open crime codes file: '" << crimeCodesFilename << "'" << endl;
		exit(-1);
	}

	// Skip first line
	getline(codesFile, line);

	// Process each line
	while (getline(codesFile, line))
	{
		// Parse line
		stringstream ss(line);
		getline(ss, iucr, ',');
		getline(ss, pri_desc, ',');
		getline(ss, sec_desc, ',');

		// Insert a CrimeCode into the vector
		CrimeCode newCC(iucr, pri_desc, sec_desc, 0);
		crimeCodes.push_back(newCC);
	}
}


/* Read in from crimes file and insert data in vector */
void processCrimeReports(string crimesFilename,
					vector<CrimeReport> &crimeReports, vector<CrimeCode> &crimeCodes)
{
	string line, iucr, date_time, arrest, domestic;
	string beat, district, ward, com;
	ifstream  crimesFile(crimesFilename);
	
	if (!crimesFile.good())
	{
		cout << "**ERROR: cannot open crimes file: '" << crimesFilename << "'" << endl;
		exit(-1);
	}

	// Skip first line
	getline(crimesFile, line);

	// Process each line
	while (getline(crimesFile, line))
	{
		// Parse line
		stringstream ss(line);
		getline(ss, date_time, ',');
		getline(ss, iucr, ',');
		getline(ss, arrest, ',');
		getline(ss, domestic, ',');
		getline(ss, beat, ',');
		getline(ss, district, ',');
		getline(ss, ward, ',');
		getline(ss, com, ',');

		// Insert a CrimeReport into the vector
		CrimeReport newCR(date_time, iucr, arrest, domestic, stoi(beat),
							stoi(district), stoi(ward), stoi(com));
		crimeReports.push_back(newCR);

		// Find the matching crime code
		auto CR = std::find_if(crimeCodes.begin(), crimeCodes.end(),
		[=](const CrimeCode &a)
		{
			if (a.getIUCR() == iucr)
				return true;
			else
				return false;
		});

		// Increment count for this Crime Code if found
		if (CR == crimeCodes.end())
		{
			//cout << "Error: IUCR (" << iucr <<") of Crime Report not found!" << endl;
		}
		else
		{
			CR->incrementCount();
		}
	}
}


/* Display Date Range of crimes */
void displayDateRange(vector<CrimeReport> cr)
{
	cout << "** Crime Analysis **\n" << endl;

	int size = cr.size();
	cout << "Date range: " << cr[0].getDateAndTime() << " - "
		<< cr[size - 1].getDateAndTime() << "\n" << endl;
}


/* Display top and bottom 3 Crime Codes */
void displayCrimeCodes(const vector<CrimeCode> &cc)
{
	int cc_size = cc.size();

	cout << "# of crime codes: " << cc_size << endl;
	
	for (int i = 0; i < 3; ++i)
	{
		cout << cc[i].getIUCR() << ":   " << cc[i].getPrimeDescription() << ":"
			<< cc[i].getSecondaryDescription() << endl;
	}

	cout << "..." << endl;

	for (int i = cc_size-3; i < cc_size; ++i)
	{
		cout << cc[i].getIUCR() << ":   " << cc[i].getPrimeDescription() << ":"
			<< cc[i].getSecondaryDescription() << endl;
	}
}


/* Display the top and bottom 3 Crime Reports */
void displayCrimeReports(const vector<CrimeReport> &cr)
{
	string arrest, domestic;
	int cc_size = cr.size();

	cout << "\n# of crimes: " << cc_size << endl;
	
	for (int i = 0; i < 3; ++i)
	{
		cout << cr[i].getIUCR() << ":   " << cr[i].getDateAndTime() << ", " << cr[i].getBeat() <<
			", " << cr[i].getDistrict() << ", " << cr[i].getWard() << ", " << cr[i].getCommunity();

		
		arrest = cr[i].isArrest();
		std::transform(arrest.begin(), arrest.end(), arrest.begin(), ::toupper);

		if (arrest == "TRUE")
		{
			cout << ", " << "arrested";
		}

		domestic = cr[i].isDomestic();
		std::transform(domestic.begin(), domestic.end(), domestic.begin(), ::toupper);

		if (domestic == "TRUE")
		{
			cout << ", " << "domestic violence";
		}
		cout << endl;
	}

	cout << "..." << endl;

	for (int i = cc_size-3; i < cc_size; ++i)
	{
		cout << cr[i].getIUCR() << ":   " << cr[i].getDateAndTime() << ", " << cr[i].getBeat() <<
			", " << cr[i].getDistrict() << ", " << cr[i].getWard() << ", " << cr[i].getCommunity();

		arrest = cr[i].isArrest();
		std::transform(arrest.begin(), arrest.end(), arrest.begin(), ::toupper);

		if (arrest == "TRUE")
		{
			cout << ", " << "arrested";
		}

		domestic = cr[i].isDomestic();
		std::transform(domestic.begin(), domestic.end(), domestic.begin(), ::toupper);

		if (domestic == "TRUE")
		{
			cout << ", " << "domestic violence";
		}
		cout << endl;
	}
}


/* Sort crime codes by IUCR */
void sortCodesByIUCR(vector<CrimeCode> &cr)
{
	std::sort(cr.begin(), cr.end(),
		[](const CrimeCode &a, const CrimeCode &b)
	{
		if (a.getIUCR() < b.getIUCR())
			return true;
		else
			return false;
	});
}


/* Sort crime codes by count */
void sortCodesByCount(vector<CrimeCode> &cr)
{
	std::sort(cr.begin(), cr.end(),
		[](const CrimeCode &a, const CrimeCode &b)
	{
		if (a.getCount() > b.getCount())
			return true;
		else
			return false;
	});
}


/* Display the top five crimes by occurences */
void displayTopCrimes(vector<CrimeCode> &cc)
{
	cout << "\n** Top-5 Crimes **" << endl;
	cout << "Code:   Total, Description" << endl;
	for (int i = 0; i < 5; ++i)
	{
		cout << cc[i].getIUCR() << ":   " << cc[i].getCount()
			<< ", " << cc[i].getPrimeDescription() << ": " << cc[i].getSecondaryDescription() << endl;
	}
	cout << "\n** Done **" << endl;
}


int main()
{
	std::vector<CrimeCode> crimeCodes;
	std::vector<CrimeReport> crimeReports;
	string  crimeCodesFilename, crimesFilename;

	// Read in file names
	cin >> crimeCodesFilename;
	cout << crimeCodesFilename << endl;

	cin >> crimesFilename;
	cout << crimesFilename << endl;

	cout << std::fixed;
	cout << std::setprecision(2);


	processCrimeCodes(crimeCodesFilename, crimeCodes);
	processCrimeReports(crimesFilename, crimeReports, crimeCodes);
	
	displayDateRange(crimeReports);
	sortCodesByIUCR(crimeCodes);

	displayCrimeCodes(crimeCodes);
	displayCrimeReports(crimeReports);

	sortCodesByCount(crimeCodes);
	displayTopCrimes(crimeCodes);


	system("PAUSE");
	return 0;
}
