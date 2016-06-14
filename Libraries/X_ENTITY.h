#ifndef X_ENTITY
#define X_ENTITY

typedef struct s_entity
{
  float temperature;
  float pressure;
  char date;
  struct s_entity * next;
}Entity;

Entity * createEntity(float temp, float pre, char date);

//void deleteAll(Entity * header);

Entity * deleteDate(Entity * header, char date);

void decreaseDate(Entity * header);

Entity * deleteFirstDay(Entity * header);

#endif