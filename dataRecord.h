// Nohl Egan
// this file is the header file for the dataRecord class, which will be used to store a country's data as a record
// October 7, 2020

#include "string"

using namespace std;

#ifndef DATA_RECORD_H
#define DATA_RECORD_H

class dataRecord{
	public:
		dataRecord(string cN, string cC, int nCC, int nD, int nRC, int tCC, int tD, int tRC);
		
		// blank constructor to be used when making the container for the dataRecord items
		dataRecord(){
		
		}
		
		// destructor
		~dataRecord(){
		
		}	
		
		// getter methods
		string getCountryName();
		string getCountryCode();
		int getNewConfirmedCases();
		int getNewDeaths();
		int getNewRecoveredCases();
		int getTotalConfirmedCases();
		int getTotalDeaths();
		int getTotalRecoveredCases();
		
	private:
		string countryName;
		string countryCode;
		int newConfirmedCases;
		int newDeaths;
		int newRecoveredCases;
		int totalConfirmedCases;
		int totalDeaths;
		int totalRecoveredCases;
		
};

#endif
