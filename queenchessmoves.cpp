#include <iostream> 
#include <iomanip>
#include <random>
#include <functional>
#include <vector>
#include <map>

using namespace std;

//how many random moves until a queen has hit every spot on a chessboard

int main(int argc, char* argv[]){
	if(argc < 3){
		cout << "Please enter the necessary 2 command line arguments next time. Now terminating." << endl;
		return 0;
	}
	int N = stoi(argv[1]); //size of the board
	int trials = stoi(argv[2]); //number of trials
	
	random_device rd;
	int seed_value = rd();
	
	mt19937 generator(seed_value); //random generator to get the direction the queen moves
	uniform_int_distribution<int> direction_distribution(0, 7);
	auto select_direction = bind(direction_distribution, generator);
	
	mt19937 generator2(seed_value); //random generator to get distance the queen moves
	uniform_int_distribution<int> length_distribution(1, N-1);
	auto select_length = bind(length_distribution, generator2);
	
	int total = 0; //variable to hold the total moves
	
	for(int i=0; i< trials; i++){ //loop through the trials
		vector<vector<int>> chessboard(N, vector<int>(N)); //initialize the chessboard
		vector<int> location ={0,0}; //set the starting location for the queen
		bool finished = false;
		int moves = 0;
		while(!finished){ //while every space has not yet been reached
			vector<vector<int>> options;
			options = {{1,0}, {0,1}, {1,1}, {-1,1}, {1,-1}, {-1,-1}, {0,-1}, {-1,0}};
			bool validmove = false;
			while(!validmove){
				int opt = select_direction();
				int length = select_length();
				int x = location[0] + options[opt][0]*length;
				int y = location[1] + options[opt][1]*length;
				if(x >= 0 && x< N && y >=0 && y< N){
					validmove = true;
					location[0] = x;
					location[1] = y;
					chessboard[x][y] += 1;
				}
			}
			moves += 1;
			int check = 1;
			for(vector<int> v: chessboard){ //check to see if all the squares have been hit yet
				for(int i: v){
					check = check*i;
				}
			}
			if(check != 0){
				finished = true;
			}
		}
		total += moves;
	}
	double average = double(total)/trials;
	
	cout << "The average number of moves necessary was: " << average << endl;
	
	return 0;
	
}
