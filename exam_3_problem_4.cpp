#include <iostream>
#include <random>
#include <functional>
#include <cmath>
#include <vector>
#include <map>
#include <iomanip>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

//decrypt an encrypted file using encryption keys

vector<string> decrypt(vector<string> v, map<char, char> m);

int main(){
	ifstream input_file("encrypted_test_text.txt");
	
	if(!input_file.is_open()){
		cout << "Error: unable to open the file. Now exiting." << endl;
		return 0;
	}
	
	ifstream input_file2("encrypted_test_key.txt");
	
	if(!input_file2.is_open()){
		cout << "Error: unable to open the file. Now exiting." << endl;
		return 0;
	}
	
	ofstream output_file("decrypted_text.txt");
	
	
	if(!output_file.is_open()){
		cout << "Error: unable to create the specified output file. Now exiting." << endl;
		return 0;
	}
	
	map<char,char> x;
	string line;
	while(getline(input_file2, line)){
		if(!line.empty()){
			istringstream linedata(line);
			char encrypted;
			char decrypted;
			while(!linedata.eof()){
				linedata >> encrypted >> decrypted;
				x[encrypted] = decrypted;
			}
		}
	}
	
	while(getline(input_file, line)){
		vector<string> a;
		vector<string> b;
		if(!line.empty()){
			istringstream linedata(line);
			string c;
			while(!linedata.eof()){
				linedata >> c;
				a.push_back(c);
			}
			b = decrypt(a,x);
			for(int i=0; i<b.size(); i++){
				output_file << b[i] << " ";
			}
			output_file << "\n";
		}
	}
	input_file.close();
	input_file2.close();
	output_file.close();
}

vector<string> decrypt(vector<string> v, map<char,char> m){
	vector<string> final_vector;
	for(int i=0; i< v.size(); i++){
		string a = v[i];
		string b = "";
		for(char c: a){
			b+= m[c];
		}
		final_vector.push_back(b);
	}
	return final_vector;
}