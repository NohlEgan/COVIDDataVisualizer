// Nohl Egan
// this class implements the methods defined by dataRecord.h
// October 7, 2020

#include "dataRecord.h"

using namespace std;

// Constructor
// Parameters: country name, country code, and the six statistical counts
dataRecord::dataRecord(string cN, string cC, int nCC, int nD, int nRC, int tCC, int tD, int tRC){
	countryName = cN;
	countryCode = cC;
	newConfirmedCases = nCC;
	newDeaths = nD;
	newRecoveredCases = nRC;
	totalConfirmedCases = tCC;
	totalDeaths = tD;
	totalRecoveredCases = tRC;
}

// getCountryName
// a getter method for countryName
// returns countryName
string dataRecord::getCountryName(){
	return countryName;
}

// getCountryCode
// a getter method for countryCode
// returns countryCode
string dataRecord::getCountryCode(){
	return countryCode;
}

// getNewConfirmedCases
// a getter method for newConfirmedCases
// returns newConfirmedCases
int dataRecord::getNewConfirmedCases(){
	return newConfirmedCases;
}

// getNewDeaths
// a getter method for newDeaths
// returns newDeaths
int dataRecord::getNewDeaths(){
	return newDeaths;
}

// getNewRecoveredCases
// a getter method for newRecoveredCases
// returns newRecoveredCases
int dataRecord::getNewRecoveredCases(){
	return newRecoveredCases;
}

// getTotalConfirmedCases
// a getter method for totalConfirmedCases
// returns totalConfirmedCases
int dataRecord::getTotalConfirmedCases(){
	return totalConfirmedCases;
}

// getTotalDeaths
// a getter method for totalDeaths
// returns totalDeaths
int dataRecord::getTotalDeaths(){
	return totalDeaths;
}

// getTotalRecoveredCases
// a getter method for totalRecoveredCases
// returns totalRecoveredCases
int dataRecord::getTotalRecoveredCases(){
	return totalRecoveredCases;
}

