#ifndef MAP_H
#define MAP_H

typedef struct MapValue{
  int type;
  char * initialization;
} MapValue;

typedef struct MapEntry{
  char * key;
  MapValue value;
} MapEntry;

typedef struct Map{
  struct MapEntry * map;
  long capacity;
  long size;
} Map;

typedef enum {TRUE, FALSE, ERROR_MAP} bool;

Map * mapInit(long capacity);
bool mapPut(Map * map, char * key, MapValue value);
bool mapRemove(Map * map, char * key);
MapValue mapGet(Map * map, char * key);

#endif
