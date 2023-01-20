// blank: 5, code: 10, comment: 9
#include <iostream>
#include <string>

using namespace std;

int main() {

	/*John: firstName*/ string firstName = "John ";
	string lastName = "Doe"; // lastName: Doe
	string fullName = firstName + lastName; /* firstName "John ",
											   lastName "Doe",
											   firstName + lastName = ..,											
											   fullName = "John Doe"
											*/

	cout << fullName; // fullName "John Doe"
	return 0;

}