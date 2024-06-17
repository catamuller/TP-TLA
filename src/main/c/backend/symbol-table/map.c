#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "map.h"

/* PRIVATE FUNCTIONS */
int _calcHash(char * key, long mod) {
  long h = 0;
    for (int i = 0; key[i]; i++) {
        h = 31 * h + key[i];
    }
    return h % mod;
}

bool _mapPut(Map * map, char * key, MapValue value, int index, int startingIndex) {
  if (index == startingIndex) return FALSE;
  if (index == map->capacity)
    return _mapPut(map, key, value, 0, startingIndex);
  if (map->map[index].key != NULL) 
    return _mapPut(map, key, value, index+1, startingIndex);
  map->map[index].key = key;
  map->map[index].value = value;
  map->size++;
  return TRUE;
}

bool _mapRemove(Map * map, char * key, int index, int startingIndex) {
  if (index == startingIndex) return FALSE;
  if (index == map->capacity)
    return _mapRemove(map, key, 0, startingIndex);
  if (strcmp(map->map[index].key, key) != 0)
    return _mapRemove(map, key, index+1, startingIndex);
  map->map[index].key = NULL;
  map->size--;
  return TRUE;
}

MapValue _mapGet(Map * map, char * key, int index, int startingIndex) {
  if (index == startingIndex) return (MapValue) {0, NULL};
  if (index == map->capacity)
    return _mapGet(map, key, 0, startingIndex);
  if (strcmp(map->map[index].key, key) != 0)
    return _mapGet(map, key, index+1, startingIndex);
  return map->map[index].value;
}

/* PUBLIC FUNCTIONS */

Map * mapInit(long capacity) {
  Map * map = malloc(sizeof(Map));
  map->capacity = capacity;
  map->size = 0;
  MapEntry * mapEntry = calloc(capacity, sizeof(MapEntry));
  map->map = mapEntry;

  return map;
}

void mapFree(Map * map) {
  free(map->map);
  free(map);
}

bool mapPut(Map * map, char * key, MapValue value) {
  if (key == NULL || *key == '\0' || map->size == map->capacity) return FALSE;
  int hash = _calcHash(key, map->capacity);
  if (map->map[hash].key != NULL) {
    return _mapPut(map, key, value, hash+1, hash);
  }
  map->map[hash].key = key;
  map->map[hash].value = value;
  map->size++;
  return TRUE;
}

bool mapRemove(Map * map, char * key) {
  if (key == NULL || *key == '\0' || map->size == 0) return FALSE;
  int hash = _calcHash(key, map->capacity);
  if (strcmp(map->map[hash].key, key) != 0)
    return _mapRemove(map, key, hash+1, hash);
  map->map[hash].key = NULL;
  map->size--;
  return TRUE;
}

MapValue mapGet(Map * map, char * key) {
  if (key == NULL || *key == '\0' || map->size == 0) return (MapValue) {0, NULL};
  int hash = _calcHash(key, map->capacity);
  if (strcmp(map->map[hash].key, key) != 0)
    return _mapGet(map, key, hash+1, hash);
  return map->map[hash].value;
}

