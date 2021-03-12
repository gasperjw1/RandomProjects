/*
	MackCode:
	- Takes a large number and breaks it into bits of 5 that eventually make a sentence.
	- Takes a word and converts it into a large number
*/

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <cstdlib>
//#include <bits/stdc++.h> 

using namespace std;

/*
	recursive function used to get the amount of digits in a number given the number itself, n, and the ending zeroes, lz, 
    for when we end but did not account for zeroes at the end.
*/
int lengthOfInt(unsigned long long int n, int lz){
	if(n == 0){//base case where if n is 0, we are done and lz accounts for the ending zeroes.
		return lz;
	}
	else{//continues on until we have no more digits.
		return 1 + lengthOfInt(n/10,log10(n));
	}
}

/*
	recursive function that takes a binary number, b, with length, l, and converts it into decimal by going through each bit
	starting from the end using c to keep track.
*/
long int cBTDHelper(unsigned long long int b, int l, int c){
	if(b == 0 || c == l){//base case: if we have no more 1s in our binary number or we have reached the end of our binary adventure, end the loop.
		return 0;
	}
	else{//if there are more binary bits, keeps the function going.
		return ((b%10) * pow(2,c)) + cBTDHelper(b/10,l,c+1); 
	}
}

//takes a binary number, bin, finds the length using lengthOfInt() then plugs it into cBTDHelper().
unsigned long long int convertBinaryToDecimal(long int bin){
	//cout << bin << endl;
	int length = lengthOfInt(bin,0);
	return cBTDHelper(bin,length,0);
}

//recursive function that finds the highest position of a bit, p, for a decimal number, n.
int findHighestPower(int d, int p){
	if(pow(2,p) > d){//base case: if 2^p > d, then p-1 must be the greatest power of 2 that does not go higher than d.
		return p-1;
	}
	//keeps the function going if p can be higher.
	return findHighestPower(d,p+1);
}

//recursive function that converts decimal to binary given the decimal number, d, and highest possible power of 2, p, that is less than the decimal number.
string cDTBHelper(int d, int p){
	if(p < 0){ //base case: when p < 0, no more binary digits left.
		return "";
	}
	else if(pow(2,p) > d){ //first case: if 2^p > remaining decimal number, this binary digit is 0.
		return "0" + cDTBHelper(d,p-1);
	}
	//second case: this binary digit is 1 since we can reduce our remaining decimal number by 2^p without it going below 0.
	return "1" + cDTBHelper(d-pow(2,p),p-1);
}

//takes a decimal, d, puts it into cDTBHelper and prints out the binary equivalent as an int.
/*int convertDecimalToBinary(int dec){
	//int length = lengthOfInt(dec);
	return static_cast<int>(cDTBHelper(dec,findHighestPower(dec,0)));
}*/

//takes a decimal, d, puts it into cDTBHelper and prints out the binary equivalent as an string.
string convertDecimalToBinaryAsString(int dec){
	return cDTBHelper(dec,findHighestPower(dec,0));
}

//checks if a string, l, is a letter then returns it's position in the alphabet or punctuation as a 5-bit binary number.
string cSTBHelper(string l){
	/*if(l.substr(0,1) == " "){//checks if l is a space.
		return "00000";
	}
	else*/ if(l.substr(0,1) == "."){//checks if l is a period.
		return convertDecimalToBinaryAsString((rand() % 4) + 27);
	}
	else{//checks if l is a letter.
		if(l == "a" || l == "A") {return "00001";}
		else if(l == "b" || l == "B") {return "00010";}
		else if(l == "c" || l == "C") {return "00011";}
		else if(l == "d" || l == "D") {return "00100";}
		else if(l == "e" || l == "E") {return "00101";}
		else if(l == "f" || l == "F") {return "00110";}
		else if(l == "g" || l == "G") {return "00111";}
		else if(l == "h" || l == "H") {return "01000";}
		else if(l == "i" || l == "I") {return "01001";}
		else if(l == "j" || l == "J") {return "01010";}
		else if(l == "k" || l == "K") {return "01011";}
		else if(l == "l" || l == "L") {return "01100";}
		else if(l == "m" || l == "M") {return "01101";}
		else if(l == "n" || l == "N") {return "01110";}
		else if(l == "o" || l == "O") {return "01111";}
		else if(l == "p" || l == "P") {return "10000";}
		else if(l == "q" || l == "Q") {return "10001";}
		else if(l == "r" || l == "R") {return "10010";}
		else if(l == "s" || l == "S") {return "10011";}
		else if(l == "t" || l == "T") {return "10100";}
		else if(l == "u" || l == "U") {return "10101";}
		else if(l == "v" || l == "V") {return "10110";}
		else if(l == "w" || l == "W") {return "10111";}
		else if(l == "x" || l == "X") {return "11000";}
		else if(l == "y" || l == "Y") {return "11001";}
		else if(l == "z" || l == "Z") {return "11010";}
	}
	return "";
}

//converts a string, s, into a binary number.
string convertStringToBinary(string s){
	if(s == ""){//if string is empty, then we are done.
		return s;
	}//else look at current letter and get its binary equivalent and concadenate it to the string of binary.
	return cSTBHelper(s.substr(0,1)) + convertStringToBinary(s.substr(1,s.length()));
}

//takes in a string of numbers, s, and turns it into an int.
unsigned long long int convertStringToNum(string s){
	if(s == ""){//base case: if string is empty then we have the number.
		return 0;
	}
	//cout << (stoi(s.substr(0,1)) * pow(10,s.length())) << endl; //test
	return (stoi(s.substr(0,1)) * pow(10,s.length()-1)) + convertStringToNum(s.substr(1,s.length()));
}

//converts a string into a unique number.
unsigned long long int convertToMC(string word){
	string s = convertStringToBinary(word);
	//reverse(s.begin(), s.end());
	//return convertBinaryToDecimal(static_cast<int>(s));
	//cout << s << endl; //test
	return convertBinaryToDecimal(convertStringToNum(s));
}

int main(){
	cout << convertToMC("pier") << endl;
	return 0;
}