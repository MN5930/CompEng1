#include "X_ENTITY.h"
#include <stdlib.h>

Entity * createEntity(float temp, float pre, char date)
{
  Entity * tmp;
  tmp = (Entity *)malloc(sizeof(Entity) * 5);
  if(tmp == NULL)
    return NULL;
  free(tmp);
  tmp = (Entity *)malloc(sizeof(Entity));
  tmp->temperature = temp;
  tmp->pressure = pre;
  tmp->date = date;
  tmp->next = NULL;
  return tmp; 
}

void deleteAll(Entity * header)
{
  Entity * tmp;
  if(header == NULL)
    return;
  do
  {
    tmp = header->next;
    free(header);
    header = tmp;
  }while(tmp != NULL);
}

Entity * deleteDate(Entity * header, char date)
{
  Entity * tmp;
  if(header == NULL)
    return NULL;
  while(header->date == date)
  {
    tmp = header;
    header = tmp->next;
    free(tmp);
    if(header == NULL)
      return NULL;
  }
  
  Entity * tmp2;
  tmp = header;
  tmp2 = tmp->next;
  while(tmp2 != NULL)
  {
    if(tmp2->date == date)
    {
      free(tmp2);
      tmp->next = tmp2->next;
    }
    else
    {
      tmp = tmp2;
    }
    tmp2 = tmp->next;
  }  
  return header;
}

void decreaseDate(Entity * header)
{
  while(header != NULL)
  {
    header->date --;
	header = header->next;
  }
}

Entity * deleteFirstDay(Entity * header)
{
  if(header == NULL)
	return NULL;
  return deleteDate(header, header->date);
}