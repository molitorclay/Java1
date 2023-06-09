#include <string>
#include <iostream>
#include <cctype>
#include <stdexcept>
#include <optional>

#include "LetterInventory.hpp"

// Clay Molitor
// CS 145
// Letter Inventory: Lab 03
/*
	LetterInventory is a class that takes a string and keeps a count of the numbers of each letter in this string.
	All characters are converted to lower case and all non-alphabet characters are dropped.
	Counts can be altered through set() and got through get().


	For extra credit I:
		Used C++ 
		Implemented operator overloads

*/

class LetterInventory {
private:
	const static int arraySize = 'z' - 'a' + 1;
	// Length 26 array with a value for each lowercase ascii letter.
	int lettersCount[arraySize] = {}; // Only Access using countAt.

	// Setting to -1 indicates that the size needs to be recalculated.
	// Use size() to get, set to -1 after editing lettersCount.
	int lastSize; 

	// Returns a pointer to the characters count.
	int* countAt(char letter)
	{
		letter = tolower(letter);
		checkValid(letter, true);
		//std::cout << letter  << "- " << letter - 'a' << std::endl;
		return &lettersCount[letter - 'a'];
	}

	// Returns true if the letter is inside the a-z range.
	bool checkValid(char letter)
	{
		return checkValid(letter, false);
	}
	// Returns true if the letter is inside the a-z range.
	// Throws an error instead of returning false if throwError is true.
	bool checkValid(char letter, bool throwError)
	{
		letter = tolower(letter);

		if(letter >= 'a' && letter <= 'z') { // is valid
			return true;
		}
		else if(throwError) {
			// Closest thing I could find to IllegalArgumentException in C++
			throw std::invalid_argument("IllegalArgumentException");
		}
		else {
			return false;
		} 
	}

public:
	// Keeps count of the english alphabet characters of the passed string.
	// Upper and Lower case letters are treated as identical, A == a.
	LetterInventory(std::string data)
	{
		lastSize = -1;

		// Add one to letterCount for each instance of a letter.
		for(char letter : data)
		{
			if(checkValid(letter, false)) {
				( *countAt(letter) )++; // Add one to the letters count
			}
		}
	}
	int get(char letter)
	{
		letter = tolower(letter);
		return *countAt(letter);
	}
	// Sets letterCount to "value" at the index of "letter".
	void set(char letter, int value)
	{
		lastSize = -1; // Marks lastSize to be recalculated.
		letter = tolower(letter);
		*countAt(letter) = value;
	}
	// Prints all counted characters ordered alphabetically.
	std::string toString()
	{
		std::string output = "[";
		for(char letter = 'a'; letter <= 'z'; letter++)
		{
			int count = *countAt(letter);
			output += std::string(count, letter);
		} 
		return output + "]";
	}

	// Returns true if all letters are of count 0.
	bool isEmpty()
	{
		return size() == 0;
	}

	// Returns the total of all letters count.
	int size()
	{
		
		if(lastSize != -1) // Last size is not flagged for recalculation.
		{
			return lastSize;
		}
		else { // Calculate size;
			int sum = 0;
			static int* foo =  countAt('a');

			// From the first to last element of lettersCount
			for (int* i = countAt('a'); i <= countAt('z'); i++)
			{
				sum += *i;
			} 
			return sum;
		}
	}

	// Returns a new LetterInventory with the sum of the letter counts
	LetterInventory add(LetterInventory that)
	{
		LetterInventory sum("");
		for(char letter = 'a'; letter <= 'z'; letter++)
		{
			// Set sum's count to the added values of the current letter
			sum.set(letter, *(this->countAt(letter)) + *(that.countAt(letter)));
		}
		return sum;
	}
	// Subtracts the counts of the passed object from the current object
	// Returns empty optional<> if any letter counts are negative
	// Returns type optional<LetterInventory> to mimic Java's ability to return NULL non-pointer objects
	std::optional<LetterInventory> subtract (LetterInventory that)
	{
		LetterInventory sum("");
		for(char letter = 'a'; letter <= 'z'; letter++)
		{
			// Set sum's count to the subtracted values of the current letter
			int value = *(this->countAt(letter)) - *(that.countAt(letter));

			sum.set(letter, value);

			if(value < 0){
				return {}; // Returns "Null"
			}
		}
		return sum;
	}
	// Addition operator overload, returns add(that)
	LetterInventory operator+(LetterInventory const& that)
	{
		return this->add(that);
	}
	
};

// Test and demonstrate the functionality of the above class
int main() {
	

	std::cout << "------- SET -------" << std::endl;
	LetterInventory a("a a a bcdefgggggg-hyzz...123,?g");

	a.set('f', 250);
	for(char letter = 'a'; letter <= 'z'; letter++)
	{
		std::cout << letter << "> " << a.get(letter) << std::endl; 
	}


	std::cout << "------- IS EMPTY? -------" << std::endl;
	LetterInventory b("");
	LetterInventory bee(SAMPLE_STRING);
	LetterInventory c("yyyyyyb./?");

	std::cout << "is A empty? \t" << a.isEmpty() << std::endl;
	std::cout << "is B empty? \t" << b.isEmpty() << std::endl;
	std::cout << "is C empty? \t" << c.isEmpty() << std::endl;
	c.set('y',0);
	c.set('b',0); 
	std::cout << "is C empty now? " << c.isEmpty() << std::endl;


	std::cout << "------- ADDITION -------" << std::endl;
	LetterInventory d = a + a + c + a;
	std::cout << "Size of D: \t" << d.size() << std::endl;

	std::cout << "------- SET -------" << std::endl;
	std::cout << "Size of A: \t" << a.size() << std::endl;
	a.set('f', 83);
	std::cout << "New Size of A:\t" << a.size() << std::endl;


	std::cout << "------- SUBTRACTION -------" << std::endl;
	std::optional<LetterInventory> e = a.subtract(bee); // Will return null
	std::optional<LetterInventory> f = bee.subtract(a); // Will not return null;

	std::cout << ((e)? "E is not Null" : "E is Null") << std::endl;
	std::cout << ((f)? "F is not Null" : "F is Null") << std::endl;
	std::cout << "Size of Bee: \t" << bee.size() << std::endl;
	std::cout << "Size of Bee - A:" << bee.subtract(a).value().size() << std::endl;


	std::cout << "------- TO STRING -------" << std::endl;
	std::cout << "A to string: \t" <<a.toString() << std::endl;
	std::cout << "Bee to string:\t" <<bee.toString() << std::endl;


	return 0;
}