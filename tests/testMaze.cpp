#include "gtest/gtest.h"
#include "maze.h"

TEST (Maze, GetWalls_InitialisationValues_AllZero)
{
  location_t loc = {0, 0};
  walls_t walls = MazeGetWalls (loc);
  EXPECT_EQ (0, walls);
}

TEST (Maze, MazeResetData_blankWallsAndCosts)
{
  MazeResetData();
  location_t loc;
  int sum = 0;
  for (loc.row = 0; loc.row < MAZE_ROWS; loc.row++) {
    for (loc.col = 0; loc.col < MAZE_COLS; loc.col++) {
      EXPECT_EQ (WallsNone(), MazeGetWalls (loc));
      EXPECT_EQ (0, MazeGetCost (loc));
    }
  }
}

void testSetWall (location_t loc, direction_t dir)
{
  MazeResetData();
  MazeSetWall (loc, dir);
  walls_t walls = MazeGetWalls (loc);
  EXPECT_TRUE (HasWall (walls, dir));
  EXPECT_FALSE (HasWall (walls, LeftFrom (dir)));
  EXPECT_FALSE (HasWall (walls, RightFrom (dir)));
  EXPECT_FALSE (HasWall (walls, Behind (dir)));

  EXPECT_TRUE (WallIsSeen (walls, dir));
  EXPECT_FALSE (WallIsSeen (walls, LeftFrom (dir)));
  EXPECT_FALSE (WallIsSeen (walls, RightFrom (dir)));
  EXPECT_FALSE (WallIsSeen (walls, Behind (dir)));
  loc = Neighbour (loc, dir);
  dir = Behind (dir);
  walls = MazeGetWalls (loc);
  EXPECT_TRUE (HasWall (walls, dir));
  EXPECT_FALSE (HasWall (walls, LeftFrom (dir)));
  EXPECT_FALSE (HasWall (walls, RightFrom (dir)));
  EXPECT_FALSE (HasWall (walls, Behind (dir)));
  EXPECT_TRUE (WallIsSeen (walls, dir));
  EXPECT_FALSE (WallIsSeen (walls, LeftFrom (dir)));
  EXPECT_FALSE (WallIsSeen (walls, RightFrom (dir)));
  EXPECT_FALSE (WallIsSeen (walls, Behind (dir)));
}

void testClearWall (location_t loc, direction_t dir)
{
  MazeResetData();
  MazeSetWall (loc, NORTH);
  MazeSetWall (loc, EAST);
  MazeSetWall (loc, SOUTH);
  MazeSetWall (loc, WEST);
  MazeClearWall (loc, dir);
  walls_t walls = MazeGetWalls (loc);
  EXPECT_FALSE (HasWall (walls, dir));
  EXPECT_TRUE (WallIsSeen (walls, dir));
  loc = Neighbour (loc, dir);
  dir = Behind (dir);
  walls = MazeGetWalls (loc);
  EXPECT_FALSE (HasWall (walls, dir));
  EXPECT_TRUE (WallIsSeen (walls, dir));
}

TEST (Maze, SetWall_SetWall_GetLocPlusNeighbours)
{
  location_t loc = {3, 4};
  testSetWall (loc, NORTH);
  testSetWall (loc, SOUTH);
  testSetWall (loc, EAST);
  testSetWall (loc, WEST);
}

TEST (Maze, ClearWall_ClearWall_GetLocPlusNeighbours)
{
  location_t loc = {3, 4};
  testClearWall (loc, NORTH);
  testClearWall (loc, SOUTH);
  testClearWall (loc, EAST);
  testClearWall (loc, WEST);
}


TEST (Maze, SetWall_SetAtEdges_IgnoreOverflow)
{
  location_t loc;
  loc.row = 0;
  loc.col = 0;
  testSetWall (loc, WEST);
  testSetWall (loc, SOUTH);
  loc.row = MazeHeight() - 1;
  loc.col = MazeWidth() - 1;
  testSetWall (loc, NORTH);
  testSetWall (loc, EAST);
}

TEST (Maze, MazeUpdateFromWallData_AllWalls)
{
  location_t loc = {2, 4};
  walls_t wallData = 0x0f;  // all walls
  MazeResetData();
  MazeUpdateFromWallData (loc, wallData);
  walls_t walls;
  walls = MazeGetWalls (loc);
  EXPECT_TRUE (HasWall (walls, NORTH));
  EXPECT_TRUE (HasWall (walls, EAST));
  EXPECT_TRUE (HasWall (walls, SOUTH));
  EXPECT_TRUE (HasWall (walls, WEST));
  //no need to check neighbours - that is tested elsewhere
}

TEST (Maze, MazeUpdateFromWallData_SomeWalls)
{
  location_t loc = {2, 4};
  walls_t wallData = 0x03;  // North and East Only
  MazeResetData();
  MazeUpdateFromWallData (loc, wallData);
  walls_t walls;
  walls = MazeGetWalls (loc);
  EXPECT_TRUE (HasWall (walls, NORTH));
  EXPECT_TRUE (HasWall (walls, EAST));
  EXPECT_FALSE (HasWall (walls, SOUTH));
  EXPECT_FALSE (HasWall (walls, WEST));
  //no need to check neighbours - that is tested elsewhere
}

TEST (Maze, MazeUpdateFromWallData_NoWalls)
{
  location_t loc = {2, 4};
  walls_t wallData = 0x00;  // North and East Only
  MazeResetData();
  MazeUpdateFromWallData (loc, wallData);
  walls_t walls;
  walls = MazeGetWalls (loc);
  EXPECT_FALSE (HasWall (walls, NORTH));
  EXPECT_FALSE (HasWall (walls, EAST));
  EXPECT_FALSE (HasWall (walls, SOUTH));
  EXPECT_FALSE (HasWall (walls, WEST));
  //no need to check neighbours - that is tested elsewhere
}