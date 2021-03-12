// Akbar "Hey There" Haider

#include <vector>
#include <string>
#include <cmath>
#include <random>
#include <algorithm>
#include <chrono>
#include <iostream>

using namespace std;


string displayHand(vector<string> hand, string l){
	
	string options = " ";
	int count = 0;
	
	for(string i : hand){
		options += "  (" + l.substr(count,1) + ") " + i;
		count++;
	}
	/*while(count < hand.size()){
		options += "  (" + l.substr(0,1) + ") " + hand[count];
		//l = l.substr(1,l.length()-1);
		count++;
	}*/
	
	options += "  (" + l.substr(count,count+1) + ") draw";
	
	return options;
}

int main(){
	std::vector<string> deck = {"DA","D2","D3","D4","D5","D6","D7","D8","D9","D10","DJ","DQ","DK",
								"CA","C2","C3","C4","C5","C6","C7","C8","C9","C10","CJ","CQ","CK",
								"HA","H2","H3","H4","H5","H6","H7","H8","H9","H10","HJ","HQ","HK",
								"SA","S2","S3","S4","S5","S6","S7","S8","S9","S10","SJ","SQ","SK"};
	
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::shuffle(std::begin(deck), std::end(deck), std::default_random_engine(seed));
	
	//deck(randperm(length(deck)));
								
	//cout << 2%4 << endl;
							
	std::vector<string> user;
	std::vector<string> p1;
	std::vector<string> p2;
	std::vector<string> p3;
	int randomCard = 0;
	
	for(int i = 0; i < 32; i++){
		randomCard = rand() % (52 - i);
		if(i % 4 == 0){
			user.push_back(deck[randomCard]);
			deck.erase(deck.begin()+randomCard);
		}
		else if(i % 4 == 1){
			p1.push_back(deck[randomCard]);
			deck.erase(deck.begin()+randomCard);
		}
		else if(i % 4 == 2){
			p2.push_back(deck[randomCard]);
			deck.erase(deck.begin()+randomCard);
		}
		else{
			p3.push_back(deck[randomCard]);
			deck.erase(deck.begin()+randomCard);
		}
	}
	
	bool play = true;
	std::string letters = "abcdefghijkl";
	std::string usable_options = "";
	std::string choice = "";
	//std::size_t found;
	std::size_t found;
	std::string currentCard = "";
	bool drawP1 = false;
	bool drawP2 = false;
	bool drawP3 = false;
	
	int cardsUsed = 32;
	randomCard = rand() % (52 - cardsUsed);
	std::vector<string> pile = {deck[randomCard]};
	deck.erase(deck.begin()+randomCard);
	
	int whoseTurn = 0;
	
	while(play){
		if(deck.size() == 1){
			//cardsUsed == 52 - pile.size() - 1;
			string temp = pile[pile.size()-1];
			pile[pile.size()-1] = pile[0];
			pile[0] = temp;
			for(int r = 1; r < pile.size(); r++){
				if(pile[r].substr(1,2) != "*"){
					deck.push_back(pile[r]);
					pile.pop_back();
				}
			}
			cardsUsed = 52 - deck.size();
			unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
			std::shuffle(std::begin(deck), std::end(deck), std::default_random_engine(seed));
		}
		currentCard = pile[pile.size() - 1];
		cout << "Pile has " << currentCard;
		
		//Users Turn
		if(whoseTurn % 4 == 0){ //user
			usable_options = letters.substr(0,user.size()+1);
			cout << " <--- your turn " << endl;
			cout << endl;
			cout << displayHand(user,usable_options) << endl;
			cout << endl;
			cout << "Which one to play?  " << endl;
			cin >> choice;
			
			//Chose to cheat
			if(choice == "?"){
				cout << "Player 1" << displayHand(p1,letters) << endl;
				cout << "Player 2" << displayHand(p2,letters) << endl;
				cout << "Player 3" << displayHand(p3,letters) << endl;
			}
			//Chose to draw
			else if(usable_options.find(choice) == user.size()){
				if(user.size() > 12 || deck.size() == 0){
					whoseTurn = 1;
				}
				else{
					//randomCard = rand() % (52 - cardsUsed);
					randomCard = deck.size()-1;
					user.push_back(deck[randomCard]);
					//deck.erase(deck.begin()+randomCard);
					deck.pop_back();
					cardsUsed++;
				}
			}
			else{
				found = usable_options.find(choice);
				if(found!=std::string::npos){
					//Matching suites
					if(user[found].substr(0,1) == currentCard.substr(0,1) && user[found].substr(1,1) != "8"){
						pile.push_back(user[found]);
						user.erase(user.begin()+found);
						whoseTurn = 1;
					}
					//Crazy eights boiii
					else if(user[found].substr(1,1) == "8"){
						pile.push_back(user[found]);
						user.erase(user.begin()+found);
						cout << "choose a suit: (a) D (b) C (c) H (d) S" << endl;
						cin >> choice;
						string aaahhh = "abcd";
						found = aaahhh.find(choice);
						if(found == 0){
							pile.push_back("D*");
						}
						else if(found == 1){
							pile.push_back("C*");
						}
						else if(found == 2){
							pile.push_back("H*");
						}
						else{
							pile.push_back("S*");
						}
						whoseTurn = 1;
					}
					//Matching numbers
					else if(user[found].substr(1,2) == currentCard.substr(1,2)){
						pile.push_back(user[found]);
						user.erase(user.begin()+found);
						whoseTurn = 1;
					}
				}
			}
		}
		else{
			cout << endl;
			int c = 0;
			currentCard = pile[pile.size() - 1];
			//if(whoseTurn % 4 == 1){ //p1
			//for(int c = 0; c < p1.size(); c++){
			while(whoseTurn % 4 == 1 && !drawP1){
				if(c == p1.size()){
					drawP1 = true;
				}
				//If Player 1 has a matching suite
				else if(p1[c].substr(0,1) == currentCard.substr(0,1) && p1[c].substr(1,1) != "8"){
					pile.push_back(p1[c]);
					p1.erase(p1.begin()+c);
					cout << "	Player 1 chose " + pile[pile.size()-1] << endl;
					whoseTurn = 2;
				}
				//Crazy 8 boiii
				else if(p1[c].substr(1,1) == "8"){
					pile.push_back(p1[c]);
					p1.erase(p1.begin()+c);
					cout << "	Player 1 chose " + pile[pile.size()-1] << endl;
					int diamonds = 0;
					int hearts = 0;
					int spades = 0;
					int clovers = 0;
					for(string i : p1){
						if(i.substr(0,1) == "D"){
							diamonds++;
						}
						else if(i.substr(0,1) == "H"){
							hearts++;
						}
						else if(i.substr(0,1) == "S"){
							spades++;
						}
						else{
							clovers++;
						}
					}
					if(diamonds > p1.size()/4){
						pile.push_back("D*");
						cout << "	Player 1 declared suite D" << endl;
					}
					else if(hearts > p1.size()/4){
						pile.push_back("H*");
						cout << "	Player 1 declared suite H" << endl;
					}
					else if(spades > p1.size()/4){
						pile.push_back("S*");
						cout << "	Player 1 declared suite S" << endl;
					}
					else{
						pile.push_back("C*");
						cout << "	Player 1 declared suite C" << endl;
					}
					whoseTurn = 2;
				}
				//Matching numbers
				else if(p1[c].substr(1,2) == currentCard.substr(1,2)){
					pile.push_back(p1[c]);
					p1.erase(p1.begin()+c);
					cout << "	Player 1 chose " + pile[pile.size()-1] << endl;
					whoseTurn = 2;
				}
				c++;
			} 
			if(whoseTurn % 4 == 1){ //Needs to draw
				if(p1.size() > 12 || deck.size() == 0){
					whoseTurn = 2;
				}
				else{
					//randomCard = rand() % (52 - cardsUsed);
					randomCard = deck.size()-1;
					p1.push_back(deck[randomCard]);
					//deck.erase(deck.begin()+randomCard);
					deck.pop_back();
					cardsUsed++;
					cout << "		Player 1 drawing..." << endl;
				}
				drawP1 = false;
			}
			//cout << "hey wassup Hello" << endl;
			c = 0;
			currentCard = pile[pile.size() - 1];
			//for(int c = 0; c < p2.size(); c++){
			while(whoseTurn % 4 == 2 && !drawP2){
				if(c == p2.size()){
					drawP2 = true;
				}
				//If Player 2 has a matching suite
				else if(p2[c].substr(0,1) == currentCard.substr(0,1) && p2[c].substr(1,1) != "8"){
					pile.push_back(p2[c]);
					p2.erase(p2.begin()+c);
					cout << "	Player 2 chose " + pile[pile.size()-1] << endl;
					whoseTurn = 3;
				}
				//Crazy 8 boiii
				else if(p2[c].substr(1,1) == "8"){
					pile.push_back(p2[c]);
					p2.erase(p2.begin()+c);
					cout << "	Player 2 chose " + pile[pile.size()-1] << endl;
					int diamonds = 0;
					int hearts = 0;
					int spades = 0;
					int clovers = 0;
					for(string i : p2){
						if(i.substr(0,1) == "D"){
							diamonds++;
						}
						else if(i.substr(0,1) == "H"){
							hearts++;
						}
						else if(i.substr(0,1) == "S"){
							spades++;
						}
						else{
							clovers++;
						}
					}
					if(diamonds > p2.size()/4){
						pile.push_back("D*");
						cout << "	Player 2 declared suite D " << endl;
					}
					else if(hearts > p2.size()/4){
						pile.push_back("H*");
						cout << "	Player 2 declared suite H " << endl;
					}
					else if(spades > p2.size()/4){
						pile.push_back("S*");
						cout << "	Player 2 declared suite S " << endl;
					}
					else{
						pile.push_back("C*");
						cout << "	Player 2 declared suite C " << endl;
					}
					whoseTurn = 3;
				}
				//Matching numbers
				else if(p2[c].substr(1,2) == currentCard.substr(1,2)){
					pile.push_back(p2[c]);
					p2.erase(p2.begin()+c);
					cout << "	Player 2 chose " + pile[pile.size()-1] << endl;
					whoseTurn = 3;
				}
				c++;
			}
			//Needs to draw
			if(whoseTurn % 4 == 2){
				if(p2.size() > 12 || deck.size() == 0){
					whoseTurn = 3;
				}
				else{
					//randomCard = rand() % (52 - cardsUsed);
					randomCard = deck.size()-1;
					p2.push_back(deck[randomCard]);
					//deck.erase(deck.begin()+randomCard);
					deck.pop_back();
					cardsUsed++;
					cout << "		Player 2 drawing..." << endl;
				}
				drawP2 = false;
			}
			//cout << "hey wassup Hello" << endl;
			c = 0;
			currentCard = pile[pile.size() - 1];
			//for(int c = 0; c < p3.size(); c++){
			while(whoseTurn % 4 == 3 && !drawP3){
				if(c == p3.size()){
					drawP3 = true;
				}
				//If Player 3 has a matching suite
				else if(p3[c].substr(0,1) == currentCard.substr(0,1) && p3[c].substr(1,1) != "8"){
					pile.push_back(p3[c]);
					p3.erase(p3.begin()+c);
					cout << "	Player 3 chose " + pile[pile.size()-1] << endl;
					whoseTurn = 0;
				}
				//Crazy 8 boiii
				else if(p3[c].substr(1,1) == "8"){
					pile.push_back(p3[c]);
					p2.erase(p3.begin()+c);
					cout << "	Player 3 chose " + pile[pile.size()-1] << endl;
					int diamonds = 0;
					int hearts = 0;
					int spades = 0;
					int clovers = 0;
					for(string i : p3){
						if(i.substr(0,1) == "D"){
							diamonds++;
						}
						else if(i.substr(0,1) == "H"){
							hearts++;
						}
						else if(i.substr(0,1) == "S"){
							spades++;
						}
						else{
							clovers++;
						}
					}
					if(diamonds > p3.size()/4){
						pile.push_back("D*");
						cout << "	Player 3 declared suite D " << endl;
					}
					else if(hearts > p3.size()/4){
						pile.push_back("H*");
						cout << "	Player 3 declared suite H " << endl;
					}
					else if(spades > p3.size()/4){
						pile.push_back("S*");
						cout << "	Player 3 declared suite S " << endl;
					}
					else{
						pile.push_back("C*");
						cout << "	Player 3 declared suite C " << endl;
					}
					whoseTurn = 0;
				}
				//Matching numbers
				else if(p3[c].substr(1,2) == currentCard.substr(1,2)){
					pile.push_back(p3[c]);
					p3.erase(p3.begin()+c);
					cout << "	Player 3 chose " + pile[pile.size()-1] << endl;
					whoseTurn = 0;
				}
				c++;
			}
			//Needs to draw
			if(whoseTurn % 4 == 3){
				if(p3.size() > 12 || deck.size() == 0){
					whoseTurn = 0;
				}
				else{
					cout << "		Player 3 drawing..." << endl;
					//randomCard = rand() % (52 - cardsUsed);
					randomCard = deck.size()-1;
					p3.push_back(deck[randomCard]);
					//deck.erase(deck.begin()+randomCard);
					deck.pop_back();
					cardsUsed++;
				}
				drawP3 = false;
			}
			//cout << "hey wassup Hello" << endl;
		}
	
		if(user.size() == 0){
			play = false;
			cout << "You win!!!" << endl;
		}
		else if(p1.size() == 0){
			play = false;
			cout << "Player 1 win!!!" << endl;
		}
		else if(p2.size() == 0){
			play = false;
			cout << "Player 2 win!!!" << endl;
		}
		else if(p3.size() == 0){
			play = false;
			cout << "Player 3 win!!!" << endl;
		}
	}
}