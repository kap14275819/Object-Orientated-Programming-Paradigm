#include <iostream>

using namespace std;

const int NO_QUARTER = 0; 
const int HAS_QUARTER = 1;
const int SOLD_OUT = 2;
const int SOLD = 3;
//all four integers are constant integers which are only called upon or activated when used within the state machine and will not change the value at all

class Gumball {
	private:
		int state;
		int sold_count;
		int max_capacity;
		int turns_count;
		int max_turns;

		void setState(const int& newState){
			this->state = newState;
		}

	public:
	
		void setMaxTurns(const int& max){
			this->max_turns = max;
		}

		void setMaxCapacity(const int& max){			
			this->max_capacity = max;
			setState(NO_QUARTER);
		}

		int getInventory(){			
			int stock = max_capacity - sold_count;
			if(stock < 0){
				stock = 0;
			}

			return stock;
		}

		int getState(){
			return state;
		}

		void insertQuarter(){
			switch(state){
				case NO_QUARTER:
					cout << "Quarter inserted\n";
					setState(HAS_QUARTER);
					break;
				case HAS_QUARTER:
					cout << "You have already inserted a quarter.\n";
					break;
				case SOLD_OUT:
					cout << "There is no more gumballs to buy, SOLD OUT!\n";
					break;
				default:
					cout <<"Quarter could not be inserted\n";
					break;
			}
		}

		void ejectQuarter(){
			switch(state){
				case HAS_QUARTER:
					cout << "Quarter ejected\n";
					setState(NO_QUARTER);
					break;
				case NO_QUARTER:
					cout << "You haven't inserted a quarter\n";
					break;
				case SOLD:
					cout << "Sorry, you already turned the crank\n";
					break;
			}
		}

		void turnCrank(){
			switch(state){
				case HAS_QUARTER:
					cout << "You turned.\n";
					if(sold_count >= max_capacity){
						cout << "Out of gumballs\n";
						ejectQuarter();
						setState(SOLD_OUT);						
						return;
					}
					turns_count++;
					setState(SOLD);
					if(turns_count >= max_turns){						
						turns_count = 0;
						dispense(true);
					} else {
						dispense();
					}				
					break;
				case NO_QUARTER:
					cout << "Insert a quarter to be able to turn.\n";
					break;
				case SOLD:
					cout << "Already turned, please wait.\n";
					break;
			}
		}	

		void dispense(bool is_winner = false){
			switch(state){
				case NO_QUARTER:
					cout << "A quarter must be inserted first.\n";
					break;
				case SOLD:
					if(is_winner){
						cout << "You're a winner! Heres 2 Gumballs! .\n";
						sold_count += 2;
					} else {
						cout << "Here is one Gumball.\n";
						sold_count++;
					}
					setState(NO_QUARTER);
					break;
			}
		}

};


int main() {
  Gumball machine;
  machine.setMaxTurns(10);
  machine.setMaxCapacity(20);
  bool keepAlive = true;
  while(keepAlive){
	cout << "Gumballs: " << machine.getInventory() << endl;
	cout << "Press enter to insert a quarter and crank\n";
	getwchar();
  machine.insertQuarter();
  	machine.turnCrank();
	cout << endl;
  }
}
