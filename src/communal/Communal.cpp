#include <stdlib.h>  
#include <time.h>
#include <math.h>
#include "Communal.hpp" 


#define PI 3.14159265



int random(int min_p, int max_p){
	return rand()%(max_p-min_p+1)+min_p;
}

void seed(){
	srand(time(NULL));
}
void set_seed(int s_p){
	srand(s_p);
}

double sin_degrees(double theta){
	return sin(theta*PI/180);
}

double atan2_degrees(double y_p,double x_p){
	return atan2(y_p,x_p)*180/PI;
}


int extract_next_int_from_string(int start_index_p,std::string string_p){
	int found_index=-1;
	for(int i=start_index_p;i<(int)string_p.size();i++){
		if(string_p.at(i)>='0'&&string_p.at(i)<='9' ){
			if(found_index==-1){
				found_index=i;
			}
		}else if(found_index!=-1){
			return std::stoi(string_p.substr(found_index,i-found_index));
		}
	}
	if(found_index==-1){
		return -1;
	}else{
		return std::stoi(string_p.substr(found_index,string_p.size()-found_index));
	}	
}