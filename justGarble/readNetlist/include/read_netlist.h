#ifndef READ_NETLIST_H_
#define READ_NETLIST_H_

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <assert.h>
#include <sstream>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <unistd.h>
#include <sys/time.h>
#include <boost/tokenizer.hpp>
#include <boost/foreach.hpp>

using namespace std;
using namespace boost; 


#define MAX_NO_OF_INPUTS 20000
#define MAX_NO_OF_OUTPUTS 20000
#define MAX_NO_OF_GATES 100000
#define DEBUG_PARSER 0
#define DEBUG_SCHEDULER 0




typedef struct net{
	bool is_port;
	int index;
} net;

typedef struct GarbledGateS{
	net input[2]; 
	net output;
	int id;
	short type;
} GarbledGateS;

typedef struct GarbledGateString{
	string input[2];
	string output;
	int id;
	short type;
} GarbledGateString;


void write_gate_list(GarbledGateS* , int *, const string &);
void read_gate_list(GarbledGateS*& , int *, const string &);
void write_task_schedule(int *, int , const string &);
void read_task_schedule(int *, int , const string &);
void read_netlist(const string &infilename, const string &outfilename, bool update);
void parse_netlist(const string&);
int search (const string &target, const vector<string> & pool, int guess, int size);
int get_weight(int );
void top_sort(GarbledGateS *, int, int  *);
void schedule(int, int **, const string&);
void arrange_in_time(GarbledGateS *, int, int, int  **, int  **, int *);
void quickSort(int *, int *, int, int);
int get_min_index(int *, int);
int get_max(int *, int);

#endif