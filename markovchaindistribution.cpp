#include <iostream>
#include <random>
#include <functional>
#include <cmath>
#include <vector>
#include <map>
#include <fstream>
#include <iomanip>

using namespace std;

//markov chain distribution problem with marbles randomly distributed between two jars

int main(int argc, char* argv[]){
	if(argc < 4){
		cout << "Please enter the necessary 3 command line arguments next time. Now terminating." << endl;
		return 0;
	}
	int r = stoi(argv[1]); //number of marbles
	int K = stoi(argv[2]); //number of time steps
	long long int trials = stoll(argv[3]); //number of trials
	map<int, int> frequencies; //map to keep track of the frequencies for each possible number
	
	
	random_device rd;
	int seed_value = rd();
	
	for(int i =0; i<r+1; i++){//put all the possible number of marbles into a map as keys with values set to 0
		frequencies[i]=0;
	}
	
	mt19937 generator2(seed_value);
	uniform_int_distribution<int> marble_distribution(0, r);
	auto select_num = bind(marble_distribution, generator2);	
	
	
	for(int trial = 0; trial<trials; trial ++){ //loop through for the total number of trials

		
		int jar_one = select_num(r); //set the number of marbles in jar one
		int jar_two = r - jar_one; //set the number of marbles in jar two
		
		for(int k=0; k<K; k++){

			int marble = select_num();
			
			if(marble <= jar_one){ //see if the number drawn is contained in jar_one
				if(jar_one != 0){
					jar_one = jar_one -1; //move a marble from jar one to jar two
					jar_two = jar_two +1;
				}
			}
			
			else if(jar_one < marble <= r){ //if not in jar one then the marble is in jar two
				if(jar_two != 0){
					jar_two = jar_two - 1; 
					jar_one = jar_one + 1;
				}
			}	
		}
		
		//index the map using the size of the jar as the key and add +=1 to the associated value
		frequencies[jar_one] += 1;
	}
	
	//output the map of relative frequencies into a file 
	ofstream ofs;
	ofs.open("exam_3_problem_2_output.dat"); //create the necessary file
	
	if(!ofs.is_open()){ //check that the file is open
		cout << endl;
		cout << "Error: unable to create the specified output file. Now exiting." << endl;
		return 0;
	}
	for(auto kv: frequencies){//get the key and values from the map and output to the file, use precision of 12
		cout << setprecision(12) << endl; //set the precision to be 12

		ofs << "The relative frequency that there were " << kv.first << " marbles in the first jar is: " << double(kv.second)/double(trials) << endl;
	}
	ofs.close();
	
	return 0;
}	
