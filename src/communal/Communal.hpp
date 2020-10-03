#ifndef COMMUNAL_HPP
#define COMMUNAL_HPP
#include <string>

int random(int min_p, int max_p);

void seed();
void set_seed(int s_p);

double sin_degrees(double theta);
double atan2_degrees(double,double);

int extract_next_int_from_string(int,std::string);

#endif