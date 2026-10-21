#ifndef SET_ADT_H
#define SET_ADT_H

#include <string>
using namespace std;

const int SET_TABLE_SIZE = 1009;

struct SetNode {
    char* value;
    SetNode* next;
};

struct Set {
    SetNode* buckets[SET_TABLE_SIZE];
};

void initSet(Set& set);
void setAdd(Set& set, const char* value, bool verbose = true);
void setDel(Set& set, const char* value);
bool setContains(const Set& set, const char* value);
void clearSet(Set& set);

void runSetADT();

#endif
