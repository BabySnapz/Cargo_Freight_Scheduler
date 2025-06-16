#include <string>
#include <iostream>

using namespace std;

#include "Records.h"

Records::Records(string id_, string location_, string time_) {
	id = id_;
	location = location_;
	time = time_;
}

const string& Records::getID() {
	return id;
}

void Records::setID(const string& id_) {
	id = id_;
}

const string& Records::getLocation() {
	return location;
}

void Records::setLocation(const string& location_) {
	location = location_;
}

const string& Records::getTime() {
	return time;
}

void Records::setTime(const string& time_) {
	time = time_;
}

void Records::showDetails() const {  
	cout << id << ", " << location << ", " << time << endl;  
}

ostream& operator<< (ostream &out, const Records &aRecord) {  
   out << aRecord.id << ", " << aRecord.location << ", " << aRecord.time << endl;  
   return out;  
}
