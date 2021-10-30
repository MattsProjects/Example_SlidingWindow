// Example_SlidingWindow.cpp
// Task: Given string myString and string myLetters, find the smallest substring inside myString
// that contains all of the letters in myLetters (including duplicate letters).
// Solution:
// Use two pointers to create a 'sliding window' that will scan myString and compare it to myLetters.
// We will open the window until we detect a match, then close the window behind us to see how short the matching substring really is.
// Author: Matthew Breit (github.com/mattsprojects)

#include <iostream>
#include <unordered_map>
#include <string>

// Namespace for using cout.
using namespace std;

// Return the smallest substring of myString that contains all letters in myLetters.
string FindFirstSmallest(string myString, string myLetters)
{
	// First, cover the edge cases. If neither string exists, we can do nothing.
	if (myString == "" || myLetters == "" || myString.size() < myLetters.size())
		return "";

	// We will use an unordered map as a histogram of the letters we need to find,
	// and an unordered map to represent a histogram of the characters in the window.
	unordered_map<char, int> letters;
	unordered_map<char, int> window;

	// We will record the length of the smallest substring, and the substring itself, in these variables
	size_t minLength = SIZE_MAX;
	string minString = "";

	// Track how many matches we find in the substring.
	int matches = 0;

	// It doesn't make sense to scan substrings smaller than the amount of letters we are looking for.
	int minWindowSize = myLetters.size();

	// Our pointers that create the sliding window
	char* pfollower = &myString[0];
	char* pleader = &myString[minWindowSize];

	// for debug only, it might be useful to know how many scans it takes
	int debugLoopcounter = 0;

	// initialize the unordered map of letters we need to scan for.
	for (char c : myLetters)
		letters[c]++;

	// scan myString
	while (pleader < &myString[myString.size()] + 1)
	{
		// -------------------------------------------------------
		// For Debug only. Show each substring scan on the console
		debugLoopcounter++;
		int debugF = distance(&myString[0], pfollower);
		int debugL = distance(&myString[0], pleader);
		string debugCopy = myString;
		debugCopy.append(" ");
		debugCopy.insert(debugF, "|", 1);
		debugCopy.insert(debugL + 1, "|", 1);
		string debugMessage = "";
		debugMessage.append(to_string(debugLoopcounter));
		debugMessage.append(" : ");
		debugMessage.append(debugCopy);
		// -------------------------------------------------------

		// create our substring with the sliding window pointers
		string subString(pfollower, pleader);

		// Clear the window contents and reset the match counter for the scan.
		window.clear();
		matches = 0;

		// scan the substring for matches
		for (char c : subString)
		{
			if (letters.count(c))
			{
				window[c]++;
				if (window[c] == letters[c])
					matches++;
			}
		}

		// if the substring didn't contain all the letters,
		// open the window for the next scan by pushing the leader forward.
		if (matches < letters.size())
		{
			debugMessage.append(" : NO SUITABLE STRING FOUND. Opening window...");
			pleader++;
		}

		// if the substring did contain all the letters,
		// log the info and close the window to look for a smaller one in the next scan
		else
		{
			debugMessage.append(" : SUITABLE STRING FOUND. Closing window...");

			if (subString.size() < minLength)
			{
				debugMessage.append(" <-- shortest so far ");
				debugMessage.append(to_string(subString.size()));
				minLength = subString.size();
				minString = subString;
			}

			// close the window from behind to see if there was a shorter match in there
			pfollower++;

			// If this makes the window too small, open it to accomodate.
			if (pleader - pfollower < minWindowSize)
				pleader++;
		}

		cout << debugMessage << endl;
	}

	return minString;

	return 0;
}

int main(int /*argc*/, char* /*argv*/[])
{
	string letters = "abcd";
	string str = "dabacadabacabbacabdddcbaabcddcbaabc";
	string firstSmallest = "";

	firstSmallest = FindFirstSmallest(str, letters);

	if (firstSmallest == "")
	{
		cerr << "Error" << endl;
		return 1;
	}

	cout << endl;
	cout << "Letters                    : " << letters << endl;
	cout << "Number of letters          : " << letters.size() << endl;
	cout << "String                     : " << str << endl;
	cout << "Size of String             : " << str.size() << endl;
	cout << endl;
	cout << "First smallest substring   : " << firstSmallest << endl;
	cout << "Size of smallest substring : " << firstSmallest.size() << endl;

	return 0;
}
