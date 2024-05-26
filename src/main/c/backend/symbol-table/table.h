#ifndef TABLE_H
#define TABLE_H

#include "map.h"

void initTable();
bool checkExistance(char * id);
bool addToTable(char * id, char * type, char * init);
int getType(char * id);


#endif