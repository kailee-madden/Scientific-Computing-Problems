#include <iostream>
#include <random>
#include <functional>
#include <string>
#include <iomanip>
#include <cmath>

using namespace std;

bool is_valid(double x, double y);

int main(int argc, char* argv[]){
	if(argc < 4){
		cout << "Please enter the necessary 3 command line arguments next time. Now terminating." << endl;
		return 0;
	}
	
	double a = stod(argv[1]);
	double b = stod(argv[2]);
	long long int N = stoll(argv[3]);
	
	
	
	random_device rd;
	int seed_value = rd();
	mt19937 generator(seed_value);
	uniform_real_distribution<double> distribution_x(-1,1);
	uniform_real_distribution<double> distribution_y(-1,1);
	auto draw_x = bind(distribution_x, ref(generator));
	auto draw_y = bind(distribution_y, ref(generator));
	
	double total_distance = 0.0;
	
	double x;
	double y;
	
	for(int i=0; i<N; i++){
		x = draw_x();
		y = draw_y();
		while(!is_valid(x,y)){
			x = draw_x();
			y = draw_y();
		}
		total_distance += pow(pow(x-a,2) + pow(y-b,2), .5);
	}
	double average_distance = total_distance/double(N);
	
	cout << setprecision(12) << endl << endl;
	cout << "The approximate average distance of a point in the unit circle is: " << average_distance << endl << endl;
	
	return 0;
}

bool is_valid(double x, double y){
	if((x*x)+(y*y) <= 1) return true;
	return false;
}
	
	