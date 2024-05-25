#ifndef MAP_H
#define MAP_H

typedef struct {
  char * type;
  char * initialization;
} MapValue;

typedef struct {
  char * key;
  MapValue value;
} MapEntry;

typedef struct {
  MapEntry * map;
  long capacity;
  long size;
} Map;

typedef enum {TRUE, FALSE, ERROR} boolean;

Map * mapInit(long capacity);
int mapPut(Map * map, char * key, MapValue value);
int mapRemove(Map * map, char * key);
MapValue mapGet(Map * map, char * key);

#endif
