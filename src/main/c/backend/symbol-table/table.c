#include <stdio.h>
#include "map.h"

#define _CHECK_INITIALIZATION_ if (!_isInitialized()) return ERROR

Map * symbolTable = NULL;
long capacity = 1024;

void initTable() {
  symbolTable = mapInit(capacity);
}

boolean _isInitialized() {
  return symbolTable != NULL;
}

boolean checkExistance(char * id) {
  _CHECK_INITIALIZATION_;
  MapValue value = mapGet(symbolTable, id);
  return value.type != NULL;
}

boolean _addToTable(char * id, char * type, char * init) {
  _CHECK_INITIALIZATION_;
  MapValue value = (MapValue) {type, init};
  return mapPut(symbolTable, id, value);
}

boolean addToTable(char * id, char * type, char * init) {
  if (checkExistance(id)) return ERROR;
  return _addToTable(id, type, init);
}

