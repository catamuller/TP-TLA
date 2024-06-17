#include <stdio.h>
#include "map.h"

#define _CHECK_INITIALIZATION_ if (!_isInitialized()) return ERROR_MAP

Map * symbolTable = NULL;
long capacity = 1024;

void initTable() {
  symbolTable = mapInit(capacity);
}

bool _isInitialized() {
  return symbolTable != NULL;
}

bool checkExistance(char * id) {
  _CHECK_INITIALIZATION_;
  MapValue value = mapGet(symbolTable, id);
  return value.type != 0;
}

int getType(char * id) {
  if (checkExistance(id)) return ERROR_MAP;
  MapValue mv = mapGet(symbolTable, id);
  return mv.type;
}

bool _addToTable(char * id, int type, char * init) {
  _CHECK_INITIALIZATION_;
  MapValue value = (MapValue) {type, init};
  return mapPut(symbolTable, id, value);
}

bool addToTable(char * id, int type, char * init) {
  if (checkExistance(id)) return ERROR_MAP;
  return _addToTable(id, type, init);
}

