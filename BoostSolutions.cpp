// boostSolutions.cpp : Defines the entry point for the console application.
//serializes a vector<Student> using XML archives
// XML requires tags identifying the elements.  XML serialization
// is greatly simplified using the BOOST_SERIALIZATION_NVP

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;



#include <boost\archive\xml_iarchive.hpp>
#include <boost\archive\xml_oarchive.hpp>
#include <boost\serialization\vector.hpp>
#include <boost\serialization\nvp.hpp>


class Student
{
	public:
		string Name;
		string LastName;
		Student(string Name, string LastName) { this->Name = Name; this->LastName = LastName; }
		Student(){}
		template<typename Arch>
		void serialize(Arch &arch, const unsigned version)
		{
			arch & BOOST_SERIALIZATION_NVP(Name) & BOOST_SERIALIZATION_NVP(LastName);
		}
};

int main()
{
	vector<Student> out_vec, in_vec;
	out_vec.push_back(Student("Daniel", "Mendoza"));
	out_vec.push_back(Student("Lisa", "Kotecki"));
	out_vec.push_back(Student("Maggie", "Williams"));
	out_vec.push_back(Student("Louis", "Nichola"));
	out_vec.push_back(Student("Pretty", "Williams"));

	ofstream output("boostser.xml");
	boost::archive::xml_oarchive xmloarch(output);

	xmloarch & BOOST_SERIALIZATION_NVP(out_vec);
	output.close();

	ifstream input("boostser.xml");
	boost::archive::xml_iarchive xmlarch(input);

	xmlarch & BOOST_SERIALIZATION_NVP(in_vec);
	input.close();

	cout << "\nThe  new container:\n";
	for (auto it = in_vec.begin(); it != in_vec.end(); ++it) cout << it->Name << " " << it->LastName << endl;
	cout << "\nThe  old container:\n";
	for (auto it = out_vec.begin(); it != out_vec.end(); ++it) cout << it->Name << " " << it->LastName << endl;

	cout << "\n\n\n";  system("pause");  return 0;
}

