//
// Created by Peter Harrison on 26/05/2017.
//

#ifndef MAZE_D5MAZE_H
#define MAZE_D5MAZE_H

#include "mazeconstants.h"
#include "priorityqueue.h"
#include <stdint.h>

class Maze {
public:
  typedef enum {
    unknownsAreWalls,
    unknownsAreClear
  } floodMode;


  Maze();

  // static functions about headings
  static int rightOf(int direction);

  static int leftOf(int direction);

  static int behind(int direction);


  // static functions about neighbours
  static uint16_t cellNorth(uint16_t cell);

  static uint16_t cellEast(uint16_t cell);

  static uint16_t cellSouth(uint16_t cell);

  static uint16_t cellWest(uint16_t cell);

  // manipulating the goal cell
  void setGoal(uint16_t goal);

  uint16_t goal();

  // wall data
  bool isKnownWall(uint8_t wallData, uint8_t heading);

  int hasExit(int cell, int direction);

// return the state of the walls at a given cell.
  uint8_t walls(uint16_t cell);

  uint8_t walls(uint16_t x, uint16_t y);

  // return the heading data
  uint8_t heading(uint16_t cell);

 // uint8_t heading(uint16_t x, uint16_t y);

  void setHeading(uint16_t cell, uint8_t heading);

 // void setHeading(uint16_t x, uint16_t y, uint8_t heading);

  //
  bool isSolved(void);

  bool isVisited(uint16_t cell);

  bool isVisited(uint16_t x, uint16_t y);

  int16_t costDifference(void);

  bool goalFound(void);

  uint8_t toFileFormat(uint8_t wallData);

  void resetData(void);

// set maze to empty except start and edges
  void clearMaze(void);

// modify a single wall in a cell. Will not remove existing data
  void setWall(uint16_t cell, uint8_t wall);

  void clearWall(uint16_t cell, uint8_t wall);

// adds all walls for a cell
// mWalls should be a four bit quantity as stored in a .maz file
  void updateWalls(uint16_t cell, uint8_t mWalls);

  uint16_t neighbour(uint16_t cell, uint16_t heading);

  void setUnknownsAsWalls(void);

  void setUnknownsAsClear(void);

  int16_t flood(uint16_t goal, floodMode mode);

  int runLengthFlood(int goal);

  uint16_t costNorth(uint16_t cell);

  uint16_t costEast(uint16_t cell);

  uint16_t costSouth(uint16_t cell);

  uint16_t costWest(uint16_t cell);

  uint16_t cost(uint16_t cell, uint16_t heading);

  uint16_t cost(uint16_t cell);

  void setCost(uint16_t cell, uint16_t cost);

  uint16_t smallestNeighbourDirection(uint16_t cell, uint8_t heading = NORTH);

  bool testForSolution(void);

  uint16_t recalculateGoal();

protected:
  uint16_t mCost[NUMCELLS];
  uint8_t mHeading[NUMCELLS];
  PriorityQueue openList;
  uint16_t _goal;
  uint8_t *savedWalls;
  uint8_t mWalls[NUMCELLS];
  uint16_t _costWithUnknownsAsWalls;
  uint16_t _costWithUnknownsAsClear;
  uint16_t _costDifference;
  bool _isSolved;
  bool _goalFound;
};

#endif //MAZE_D5MAZE_H
