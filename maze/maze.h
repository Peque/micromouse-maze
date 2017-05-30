//
// Created by Peter Harrison on 26/05/2017.
//

#ifndef MAZE_D5MAZE_H
#define MAZE_D5MAZE_H

#include "mazeconstants.h"
#include "priorityqueue.h"
#include <stdint.h>
/*
 * Functions and methods for which there are
 * passing tests are marked thus: ///
 */
class Maze {
public:

  Maze(uint16_t width);

  uint16_t numCells(); ///
  uint16_t width(); ///

  void resetToEmptyMaze(void); ///

  // static functions about headings
  static uint8_t rightOf(uint8_t direction); ///
  static uint8_t leftOf(uint8_t direction); ///
  static uint8_t behind(uint8_t direction); ///


  // static functions about neighbours
  uint16_t cellNorth(uint16_t cell); ///
  uint16_t cellEast(uint16_t cell); ///
  uint16_t cellSouth(uint16_t cell); ///
  uint16_t cellWest(uint16_t cell); ///

  uint16_t neighbour(uint16_t cell, uint16_t direction); ///

  uint16_t home(); ///
  uint16_t goal(); ///
  void setGoal(uint16_t goal); ///


// return the state of the walls at a given cell.
// in the form used by the maze file format
  uint8_t walls(uint16_t cell); ///
  bool isKnownWall(uint16_t cell, uint8_t direction); ///
  bool hasExit(uint16_t cell, uint8_t direction); ///
  bool hasWall(uint16_t cell, uint8_t direction); ///


  uint8_t direction(uint16_t cell); ///
  void setDirection(uint16_t cell, uint8_t direction); ///

  bool isVisited(uint16_t cell); ///
  void setVisited(uint16_t cell); ///
  void clearVisited(uint16_t cell); ///
  void resetCell(uint16_t cell); ///

// modify a single wall in a cell. Will not remove existing data
  void setWall(uint16_t cell, uint8_t direction); ///

  void clearWall(uint16_t cell, uint8_t direction); ///

// adds all walls for a cell
// mWalls should be a four bit quantity as stored in a .maz file
// DO NOT USE when updating map from mouse data - use updateMap()
  void copyCellFromFileData(uint16_t cell, uint8_t wallData);  ///

// Updates the map by adding walls
// Used when exploring only.
// Will not remove a wall
  void updateMap(uint16_t cell, uint8_t wallData); ///

/*
 * By setting unknown walls as present or absent
 * the flooding can compare safe and unsafe routes.
 * When the cost of both routes is the same, the maze
 * has an optimal solution
 */
  void setUnknowns(void); ///
  void clearUnknowns(void); ///


  uint16_t cost(uint16_t cell); ///
  uint16_t cost(uint16_t cell, uint16_t direction); ///
  uint16_t costNorth(uint16_t cell); ///
  uint16_t costEast(uint16_t cell); ///
  uint16_t costSouth(uint16_t cell); ///
  uint16_t costWest(uint16_t cell); ///
  void setCost(uint16_t cell, uint16_t cost); ///

  void recalculateGoal(); ///
/*
 * need
 * numExits
 */

  int16_t costDifference(void); ///
  uint16_t openMazeCost() const; ///
  uint16_t closedMazeCost() const; ///

  bool isSolved(void); ///
  uint16_t flood(uint16_t goal); ///
  uint16_t runLengthFlood(uint16_t goal); ///
  uint16_t smallestNeighbourDirection(uint16_t cell, uint8_t direction = NORTH);

  bool testForSolution(void); ///


protected:
  uint16_t mWidth;
  uint16_t mCost[1024];
  uint8_t mDirection[1024];
  PriorityQueue openList;
  uint16_t mGoal;
  uint8_t mWalls[1024];
  uint16_t mPathCostOpen;
public:

protected:
  uint16_t mPathCostClosed;
  uint16_t mCostDifference;
  bool mIsSolved;
};

#endif //MAZE_D5MAZE_H
