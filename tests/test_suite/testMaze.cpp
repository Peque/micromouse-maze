#include "gtest/gtest.h"
#include "oldmaze.h"
#include "mazeprinter.h"
#include "mazedata.h"
#include "maze.h"
/////////////////////

class MazeTest : public ::testing::Test {
protected:
  Maze *maze;

  virtual void SetUp() {
    maze = new Maze();
    maze->resetToEmptyMaze();
  }

  virtual void TearDown() {
    delete maze;
  }

};

TEST_F(MazeTest, SetAndGetGoal) {
  EXPECT_EQ(DEFAULT_GOAL, maze->goal());
  maze->setGoal(99);
  EXPECT_EQ(99, maze->goal());
}

TEST_F (MazeTest, ResetData_16x16_SetsEmptyMaze) {
  maze->resetToEmptyMaze();
  EXPECT_EQ(256, maze->numCells());
  for (int i = 0; i < maze->numCells(); i++) {
    EXPECT_EQ(emptyMaze[i], maze->walls(i));
  }
}

TEST_F (MazeTest, ResetData_OnlyHomeCellVisited) {
  maze->resetToEmptyMaze();
  for (int i = 0; i < maze->numCells(); i++) {
    if (i != maze->home()) {
      EXPECT_FALSE (maze->isVisited(i));
    }
  }
}


TEST_F(MazeTest, SetClearAndGetWalls) {
  maze->resetToEmptyMaze();
  maze->setWall(0x22, NORTH);
  maze->setWall(0x22, EAST);
  maze->setWall(0x22, SOUTH);
  maze->setWall(0x22, WEST);
  EXPECT_FALSE(maze->hasExit(0x22, EAST));
  EXPECT_FALSE(maze->hasExit(0x32, WEST));
  EXPECT_FALSE(maze->hasExit(0x22, SOUTH));
  EXPECT_FALSE(maze->hasExit(0x21, NORTH));
  EXPECT_FALSE(maze->hasExit(0x22, WEST));
  EXPECT_FALSE(maze->hasExit(0x12, EAST));
  EXPECT_FALSE(maze->hasExit(0x22, NORTH));
  EXPECT_FALSE(maze->hasExit(0x23, SOUTH));
  EXPECT_TRUE(maze->hasWall(0x22, EAST));
  EXPECT_TRUE(maze->hasWall(0x32, WEST));
  EXPECT_TRUE(maze->hasWall(0x22, SOUTH));
  EXPECT_TRUE(maze->hasWall(0x21, NORTH));
  EXPECT_TRUE(maze->hasWall(0x22, WEST));
  EXPECT_TRUE(maze->hasWall(0x12, EAST));
  EXPECT_TRUE(maze->hasWall(0x22, NORTH));
  EXPECT_TRUE(maze->hasWall(0x23, SOUTH));
  maze->clearWall(0x22, NORTH);
  maze->clearWall(0x22, EAST);
  maze->clearWall(0x22, SOUTH);
  maze->clearWall(0x22, WEST);
  EXPECT_TRUE(maze->hasExit(0x22, EAST));
  EXPECT_TRUE(maze->hasExit(0x32, WEST));
  EXPECT_TRUE(maze->hasExit(0x22, SOUTH));
  EXPECT_TRUE(maze->hasExit(0x21, NORTH));
  EXPECT_TRUE(maze->hasExit(0x22, WEST));
  EXPECT_TRUE(maze->hasExit(0x12, EAST));
  EXPECT_TRUE(maze->hasExit(0x22, NORTH));
  EXPECT_TRUE(maze->hasExit(0x23, SOUTH));
  EXPECT_FALSE(maze->hasWall(0x22, EAST));
  EXPECT_FALSE(maze->hasWall(0x32, WEST));
  EXPECT_FALSE(maze->hasWall(0x22, SOUTH));
  EXPECT_FALSE(maze->hasWall(0x21, NORTH));
  EXPECT_FALSE(maze->hasWall(0x22, WEST));
  EXPECT_FALSE(maze->hasWall(0x12, EAST));
  EXPECT_FALSE(maze->hasWall(0x22, NORTH));
  EXPECT_FALSE(maze->hasWall(0x23, SOUTH));
}


/////////////////////
TEST_F(MazeTest, UpdateMap_OnlyAddsWalls) {
  maze->resetToEmptyMaze();
  uint16_t cell = 0x22;
  maze->updateMap(cell,0x00);
  EXPECT_FALSE(maze->hasWall(cell,NORTH));
  EXPECT_FALSE(maze->hasWall(cell,EAST));
  EXPECT_FALSE(maze->hasWall(cell,SOUTH));
  EXPECT_FALSE(maze->hasWall(cell,WEST));

  maze->updateMap(cell,1<<NORTH);
  EXPECT_TRUE(maze->hasWall(cell,NORTH));
  EXPECT_FALSE(maze->hasWall(cell,EAST));
  EXPECT_FALSE(maze->hasWall(cell,SOUTH));
  EXPECT_FALSE(maze->hasWall(cell,WEST));

  maze->updateMap(cell,1<<EAST);
  EXPECT_TRUE(maze->hasWall(cell,NORTH));
  EXPECT_TRUE(maze->hasWall(cell,EAST));
  EXPECT_FALSE(maze->hasWall(cell,SOUTH));
  EXPECT_FALSE(maze->hasWall(cell,WEST));

  maze->updateMap(cell,1<<SOUTH);
  EXPECT_TRUE(maze->hasWall(cell,NORTH));
  EXPECT_TRUE(maze->hasWall(cell,EAST));
  EXPECT_TRUE(maze->hasWall(cell,SOUTH));
  EXPECT_FALSE(maze->hasWall(cell,WEST));

  maze->updateMap(cell,1<<WEST);
  EXPECT_TRUE(maze->hasWall(cell,NORTH));
  EXPECT_TRUE(maze->hasWall(cell,EAST));
  EXPECT_TRUE(maze->hasWall(cell,SOUTH));
  EXPECT_TRUE(maze->hasWall(cell,WEST));

}

/////////////////////
TEST_F(MazeTest, HasExit) {
  maze->resetToEmptyMaze();
  EXPECT_FALSE(maze->hasExit(0x0F, WEST));
  EXPECT_FALSE(maze->hasExit(0x0F, NORTH));
  EXPECT_FALSE(maze->hasExit(0xF0, EAST));
  EXPECT_FALSE(maze->hasExit(0xF0, SOUTH));
}

TEST_F(MazeTest, IsKnownWall_distinguishKnownFromUnknown) {
  maze->resetToEmptyMaze();
  EXPECT_FALSE(maze->isKnownWall(0x22, WEST));
  maze->setWall(0x22,WEST);
  EXPECT_TRUE(maze->isKnownWall(0x22, WEST));
  maze->clearWall(0x22,WEST);
  EXPECT_TRUE(maze->isKnownWall(0x22, WEST));
  EXPECT_TRUE(maze->isKnownWall(0x00, WEST));
  EXPECT_TRUE(maze->isKnownWall(0x00, NORTH));
  EXPECT_TRUE(maze->isKnownWall(Maze::cellNorth(0x00), SOUTH));
}

TEST_F (MazeTest, CopyCellFromFileData_GetExactCopy) {
  const uint8_t *src = japan2007;
  maze->resetToEmptyMaze();
  for (int i = 0; i < maze->numCells(); i++) {
    maze->copyCellFromFileData(i, src[i]);
  }
  for (int i = 0; i < maze->numCells(); i++) {
    EXPECT_EQ(src[i], maze->walls(i));
    EXPECT_TRUE(maze->isVisited(i));
  }
}

TEST_F(MazeTest, OpenClosedMaze_HasExitWhenOpen) {
  maze->resetToEmptyMaze();
  maze->clearUnknowns();
  EXPECT_TRUE(maze->hasExit(0x22, WEST));
  EXPECT_TRUE(maze->hasExit(0x22, NORTH));
  EXPECT_TRUE(maze->hasExit(0x22, EAST));
  EXPECT_TRUE(maze->hasExit(0x22, SOUTH));
  maze->setUnknowns();
  EXPECT_FALSE(maze->hasExit(0x22, WEST));
  EXPECT_FALSE(maze->hasExit(0x22, NORTH));
  EXPECT_FALSE(maze->hasExit(0x22, EAST));
  EXPECT_FALSE(maze->hasExit(0x22, SOUTH));
  maze->clearUnknowns();
  EXPECT_TRUE(maze->hasExit(0x22, WEST));
  EXPECT_TRUE(maze->hasExit(0x22, NORTH));
  EXPECT_TRUE(maze->hasExit(0x22, EAST));
  EXPECT_TRUE(maze->hasExit(0x22, SOUTH));
}

TEST_F(MazeTest, NeighbourCellAddresses) {
  for (uint16_t cell = 0; cell < maze->numCells(); cell++) {
    EXPECT_EQ((cell + 1) % maze->numCells(), Maze::cellNorth(cell));
    EXPECT_EQ((cell + maze->width()) % maze->numCells(), Maze::cellEast(cell));
    EXPECT_EQ((cell + maze->numCells() - 1) % maze->numCells(), Maze::cellSouth(cell));
    EXPECT_EQ((cell + maze->numCells() - maze->width()) % maze->numCells(), Maze::cellWest(cell));
    EXPECT_EQ(Maze::cellNorth(cell),Maze::neighbour(cell,NORTH));
    EXPECT_EQ(Maze::cellEast(cell),Maze::neighbour(cell,EAST));
    EXPECT_EQ(Maze::cellSouth(cell),Maze::neighbour(cell,SOUTH));
    EXPECT_EQ(Maze::cellWest(cell),Maze::neighbour(cell,WEST));
  }
}


TEST_F(MazeTest, NeighbourInvalidDirection_ReturnsUINT16_MAX) {
    EXPECT_EQ(UINT16_MAX, Maze::neighbour(0,-1));
}