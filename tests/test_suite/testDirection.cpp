#include "gtest/gtest.h"
#include "gtest/gtest-spi.h"
#include "maze.h"

/*
 * test the ability of the maze to store direction information
 */

TEST (Direction, MazeHeading_defaultValue_isNORTH)
{
  Maze maze(16);
  maze.resetToEmptyMaze();
  for(int i = 0; i < maze.numCells(); i++){
    EXPECT_EQ(NORTH, maze.direction(i));
  }
}

TEST (Direction, MazeSetDirection_ReturnSetValue)
{
  Maze maze(16);
  maze.resetToEmptyMaze();
  maze.setDirection(0x33, EAST);
  EXPECT_EQ(EAST, maze.direction(0x33));
  maze.setDirection(0x33, SOUTH);
  EXPECT_EQ(SOUTH, maze.direction(0x33));
  maze.setDirection(0x33, WEST);
  EXPECT_EQ(WEST, maze.direction(0x33));
  maze.setDirection(0x33, NORTH);
  EXPECT_EQ(NORTH, maze.direction(0x33));
}

TEST (Direction, DirectionGetLeftFrom)
{

  EXPECT_EQ (WEST, Maze::leftOf(NORTH));
  EXPECT_EQ (SOUTH, Maze::leftOf (WEST));
  EXPECT_EQ (EAST, Maze::leftOf(SOUTH));
  EXPECT_EQ (NORTH, Maze::leftOf(EAST));
}


TEST (Direction, DirectionGetRightFrom)
{
  EXPECT_EQ (EAST, Maze::rightOf (NORTH));
  EXPECT_EQ (SOUTH, Maze::rightOf  (EAST));
  EXPECT_EQ (WEST, Maze::rightOf  (SOUTH));
  EXPECT_EQ (NORTH, Maze::rightOf  (WEST));

}

TEST (Direction, Behind)
{
  EXPECT_EQ (SOUTH, Maze::behind (NORTH));
  EXPECT_EQ (WEST, Maze::behind (EAST));
  EXPECT_EQ (NORTH, Maze::behind (SOUTH));
  EXPECT_EQ (EAST, Maze::behind (WEST));
}



