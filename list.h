/* 
 * File:   list.h
 * Author: peterharrison
 *
 * Created on 13 February 2016, 16:55
 */

#ifndef LIST_H
#define LIST_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stdint.h"
#include "stdbool.h"
#include "maze.h"
  
  /* Set the list size to zero, initialise Size and MaxSize to zero*/
  void ListClear(void);
  
  /* return true if list has no items in it */
  bool ListEmpty(void);
  
  /* Add an item to the tail of the list */
  void ListAdd(location_t loc);
  
  /* retrieve an item from the tail - list acts as a stack */
  location_t ListTail(void);
  
  /* retrieve an item from the head - list acts as a queue */
  location_t ListHead(void);
  
  /* current number of items in the list */
  int ListSize(void);
  
  /* the maximum number of items in the list since it was last cleared */
  int ListMaxSize(void);
  


#ifdef __cplusplus
}
#endif

#endif /* LIST_H */

