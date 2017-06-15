#ifndef _maze_h
#define _maze_h
/*
        maze.h
        common functions for manipulating the maze map
        and for creating the flooded route
 */
#include <stdint.h>
#include <stdbool.h>
#include "mazeconstants.h"
#include "mazedata.h"

class Maze {

 public:
  explicit Maze(uint16_t width);

  /// the maze is assumed to be square
  uint16_t width(); ///
  uint16_t numCells(); ///

  ///  reset the wall, cost and direction data to defaults
  void clearData();
  /// clear the data and then set all the walls that exist in an empty maze
  void resetToEmptyMaze(void); ///

  /// Clear the costs and directions and then copy the walls from an array
  void copyMaze(const uint8_t *wallData, uint16_t cellCount);

  /// return the column number of  given cell
  uint16_t col(uint16_t cell);
  /// return the roww number of a given cell
  uint16_t row(uint16_t cell);

  /// return the address of the cell ahead from this cardinal direction
  static uint8_t ahead(uint8_t direction);
  /// return the address of the cell on the right of this cardinal direction
  static uint8_t rightOf(uint8_t direction);
  /// return the address of the cell on the left of this cardinal direction
  static uint8_t leftOf(uint8_t direction);
  /// return the address of the cell behind this cardinal direction
  static uint8_t behind(uint8_t direction);
  /// return the address of the cell opposite the given wall
  static uint8_t opposite(uint8_t direction);

  // static functions about neighbours
  /// return the address of the cell in the indicated direction
  uint16_t cellNorth(uint16_t cell);
  /// return the address of the cell in the indicated direction
  uint16_t cellEast(uint16_t cell);
  /// return the address of the cell in the indicated direction
  uint16_t cellSouth(uint16_t cell);
  /// return the address of the cell in the indicated direction
  uint16_t cellWest(uint16_t cell);

  /// return the address of the cell in the given direction
  uint16_t neighbour(uint16_t cell, uint16_t direction);

  /// return the address of the home cell. Nearly always cell zero
  uint16_t home();
  /// return the cell address of the current goal
  uint16_t goal();
  ///  set the current goal to a new value
  void setGoal(uint16_t goal);


  /// return the state of the four walls surrounding a given cell
  uint8_t walls(uint16_t cell);
  /// test whether a wall in a given direction has been observed
  bool isSeen(uint16_t cell, uint8_t direction);
  ///  test for the absence of a wall. Don't care if it is seen or not
  bool hasExit(uint16_t cell, uint8_t direction);
  ///  test for the definite, observed absence of a wall.
  bool hasRealExit(uint16_t cell, uint8_t direction);
  ///  test for the presence of a wall. Don't care if it is seen or not
  bool hasWall(uint16_t cell, uint8_t direction);
  ///  test for the definite, observed presence of a wall.
  bool hasRealWall(uint16_t cell, uint8_t direction);


  /// return the stored direction for the given cell
  uint8_t direction(uint16_t cell);
  /// set the direction for the given cell
  void setDirection(uint16_t cell, uint8_t direction);

  /// test to see if  all the walls of a given cell have been seen
  bool isVisited(uint16_t cell);
  /// set a cell as having all the walls seen
  void setVisited(uint16_t cell);
  /// set a cell as having none of the walls seen
  void clearVisited(uint16_t cell);


  /// NOT TO BE USED IN SEARCH. Unconditionally set a  wall in a cell and mark as seen.
  void setWall(uint16_t cell, uint8_t direction);
  /// NOT TO BE USED IN SEARCH. Unconditionally clear a  wall in a cell and mark as seen.
  void clearWall(uint16_t cell, uint8_t direction);

  /// NOT TO BE USED IN SEARCH. Update a single cell from stored map data.
  void copyCellFromFileData(uint16_t cell, uint8_t wallData);

  /// USE THIS FOR SEARCH. Update a single cell with wall data (normalised for direction)
  void updateMap(uint16_t cell, uint8_t wallData);

  /// Set all unseen walls as present. This is the closed maze used to test for a solution
  void setUnknowns(void);
  /// Set all unseen walls as present. This is the open maze used for path generation
  void clearUnknowns(void);

  /// return the cost value for a given cell. Used in flooding and searching
  uint16_t cost(uint16_t cell);
  /// return the cost in the neighbouring cell in the given direction
  uint16_t cost(uint16_t cell, uint16_t direction);
  /// return the cost in the neighbouring cell to the North
  uint16_t costNorth(uint16_t cell);
  /// return the cost in the neighbouring cell to the East
  uint16_t costEast(uint16_t cell);
  /// return the cost in the neighbouring cell to the South
  uint16_t costSouth(uint16_t cell);
  /// return the cost in the neighbouring cell to the West
  uint16_t costWest(uint16_t cell);

  /// set the cost in the given cell.
  void setCost(uint16_t cell, uint16_t cost); ///

  /// examine the goal area and move the goal if needed for a better entry speed
  void recalculateGoal();


  /// return the cost of the current best path assuming unknowns are absent
  uint16_t openMazeCost() const;
  /// return the cost of the current best path assuming unknowns are present
  uint16_t closedMazeCost() const;
  /// return the difference between the open and closed cost. Zero when the best route is found.
  int16_t costDifference(void);
  /// flood the maze for the give goal
  uint16_t flood(uint16_t goal);
  /// RunLengthFlood is a specific kind of flood sed in this mouse
  uint16_t runLengthFlood(uint16_t goal);
  /// Flood the maze both open and closed and then test the cost difference
  bool testForSolution(void);
  /// returns the result of the most recent test for a solution
  bool isSolved(void);

  ///  return the direction from the given cell to the least costly neighbour
  uint8_t directionToSmallest(uint16_t cell);
  /// for every cell in the maze, calculate and store the least costly direction
  void updateDirections();

  /// save the wall data, including visited flags in the target array. Not checked for overflow.
  void save(uint8_t *data);
  /// load the wall data, including visited flags from the target array. Not checked for overflow.
  void load(uint8_t *data);

  /// descriptions of the different methds for printing the maze
  enum PrintStyle {
    PRINT_AS_CDECL,
    PRINT_WITH_DIRS,
    PRINT_WALLS_ONLY
  };


  /// DEPRECATED. use separate Maze Printer class
  void print(PrintStyle style);

 protected:
  /// the width of the maze in cells. Assume mazes are always square
  uint16_t mWidth;
  /// stores the wall and visited flags. Allows for 32x32 maze but wastes space
  uint8_t mWalls[1024];
  /// stores the least costly direction. Allows for 32x32 maze but wastes space
  uint8_t mDirection[1024];
  /// stores the cost information from a flood. Allows for 32x32 maze but wastes space
  uint16_t mCost[1024];
  /// the current goal as defined by the conetst rules
  uint16_t mGoal;
  /// The cost of the best path assuming unseen walls are absent
  uint16_t mPathCostOpen;
  /// The cost of the best path assuming unseen walls are present
  uint16_t mPathCostClosed;
  /// flag set when maze has been solved
  bool mIsSolved;
};

extern Maze theMaze;

#endif

