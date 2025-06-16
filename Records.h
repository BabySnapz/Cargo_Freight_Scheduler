#pragma once

#include <string>
#include <iostream>

class Records
{
	friend std::ostream& operator<<(std::ostream& out, const Records& aRecord);
	private:
		std::string id;
		std::string location;
		std::string time;

	public:
		const std::string& getID();
		void setID(std::string id);
		const std::string& getLocation();
		void setLocation(std::string location);
		const std::string& getTime();
		void setTime(std::string location);
		void showDetails() const;
};

