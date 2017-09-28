#ifndef MY_STRING_H
#define MY_STRING_H

#include <iostream>
#include <string.h>
#include <vector>

class MyString
{
	public:
		// default constructor
		MyString ();

		// parameterized constructor
		MyString (char* newString);

		// copy constructor
		MyString (const MyString &copy);

		// destructor
		~MyString ();

		// overloaded assignment operator
		MyString & operator= (const MyString &rhs);

		// getter
		char* getString () const;

		void set (char* stringValue);
		MyString substr (int startIndex, int length) const;
		int indexof (char* substr, int startIndex);
		int* bad_char_table (int* badCharTable);
		void split (char c, std::vector<MyString>& outputVector) const;
		int anagrams (std::vector<MyString>& candidates, std::vector<MyString>& output);
		MyString suffix_of_length (int length);
		bool starts_with (char* testString);
		void reverse (std::vector<char>& output);
		bool is_integer ();
		void write (std::ostream& stream) const;

	private:
		char* mString;
};

#endif