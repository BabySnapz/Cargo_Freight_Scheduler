#pragma once

#include <string>
#include <iostream>

class Records
{
	friend std::ostream& operator<<(std::ostream &out, const Records &aRecord);
	private:
		std::string id;
		std::string location;
		std::string time;

	public:
		Records(std::string id_, std::string location_, std::string time_);
		const std::string& getID();
		void setID(const std::string &id_);
		const std::string& getLocation();
		void setLocation(const std::string &location_);
		const std::string& getTime();
		void setTime(const std::string &time_);
		void showDetails() const;
};

