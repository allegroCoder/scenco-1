#ifndef __BASE_H__
#define __BASE_H__

// libraries import
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>
#include <math.h>
#include <sstream>
#include <map>
#include <limits>

// constant definition
#define stringLimit	1000
#define eventsLimit	1000
#define scenariosLimit	700
#define predicatesLimit	200

#define WELCOME_STRING "# Log file generated by SCENCO v0.1\n\n"

using namespace std;

// encodings available
enum encodingType
{ 
	single_literal,
	sequential,
	randomE,
	heuristic,
	exhaustive
};

typedef enum BitType
{
	ZERO,
	ONE,
	DONT_USE
} BitType;

// type definition
typedef enum {FALSE, TRUE} boolean;
typedef struct struct_tag{
	char type; 		/*v = vertex, e = edge*/
	char* source, *dest; 	/*if n
				  	source = vertex_name
			       	  if e
				  	source = from vertex
				  	dest = to vertex*/
	boolean condition; 	/*if TRUE, a condition exists*/
	char* cond; 		/*condition on vertex*/
	char* truth, *truth_cond;/*truth table*/
	char **fun, **fun_cond; /*boolean function*/
}CPOG_TYPE;

typedef struct Graph_st
{
	int e[eventsLimit][eventsLimit];
	int v[eventsLimit];
	int pred[eventsLimit];
	
	bool transitiveClosure()
	{
		for(int i = 0; i < eventsLimit; i++)
		if (v[i])
			for(int j = 0; j < eventsLimit; j++)
			if (v[j] && e[j][i])
				for(int k = 0; k < eventsLimit; k++)
				if (v[k] && e[i][k]) e[j][k] = 1;
		
		for(int i = 0; i < eventsLimit; i++) if (e[i][i]) return false;
		
		for(int i = 0; i < eventsLimit; i++)
		if (v[i])
			for(int j = 0; j < eventsLimit; j++)
			if (v[j] && e[j][i])
				for(int k = 0; k < eventsLimit; k++)
				if (v[k] && e[i][k]) e[j][k] = 2;

		return true;
	}
	
}GRAPH_TYPE;

typedef struct Encoding_st
{
	string constraint;
	
	bool trivial;
	int constant;
	
	int literal;
	bool inverted;
}Encoding;

//TEMPORARY FILES
#if defined(__linux) || defined(__APPLE__)
	char TRIVIAL_ENCODING_FILE[] = "/tmp/trivial.XXXXXX";
	char CONSTRAINTS_FILE[] = "/tmp/constraints.XXXXXX";
	char TMP_FILE[] = "/tmp/tmpfile.XXXXXX";
	char SCRIPT_PATH[] = "/tmp/synth.XXXXXX";
#else
	char *TRIVIAL_ENCODING_FILE;
	char *CONSTRAINTS_FILE;
	char *TMP_FILE;
	char *SCRIPT_PATH;
#endif
	char LOG[] = "scenco.log";

// Alex's tool
FILE *fpLOG;
char *numb;
char **manual_file;
char **manual_file_back;
int *custom_perm;
int *custom_perm_back;
boolean *DC_custom = NULL;
int tot_enc;
boolean DC = FALSE;
boolean first = TRUE;
long long int num_perm, all_perm;
int **opt_diff = NULL;
int counter = 0;
int **perm = NULL;
char *file_cons = NULL;
long long int *weights = NULL;
boolean SET;
boolean unfix = FALSE;
//char **name_cond; 
//char **vertices;
char **diff = NULL; 
BitType **opcodes = NULL;
int bits;
int bits_saved;
int total;
int cpog_count = 0;
int *enc;
int *sol;
int len_sequence;
long long int minW;
long long int maxW;

// Andrey's tool
GRAPH_TYPE *g;
int n;
char s[stringLimit];

int V;
map<string, int> eventNames;
string eventNames_str[eventsLimit];
map<string, int> eventPredicates[eventsLimit];

vector<string> scenarioNames;
vector<string> scenarioOpcodes;

string ev[eventsLimit][predicatesLimit];
string ee[eventsLimit][eventsLimit];
map<string, vector<pair<int, int> > > constraints;
map<string, vector<pair<int, int> > >::iterator cp, cq;

vector<Encoding> encodings;

vector<string> cgv;
vector<vector<int> > cge;
vector<int> literal;
vector<int> bestLiteral;

string vConditions[eventsLimit][predicatesLimit];
string aConditions[eventsLimit][eventsLimit];

// alternative = false: alpha + beta * predicate
// alternative = true : alpha * (beta + predicate)
bool alternative = false;

#endif
