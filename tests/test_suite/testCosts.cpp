#include "gtest/gtest.h"
#include "maze.h"


class CostTest : public ::testing::Test {
protected:
  Maze *maze;

  virtual void SetUp() {
    maze = new Maze(16);
    maze->resetToEmptyMaze();
  }

  virtual void TearDown() {
    delete maze;
  }

};

TEST_F (CostTest, MazeGetCosts_default_ValuesUINT16_MAX) {
  for (int cell = 0; cell < maze->numCells(); ++cell) {
    EXPECT_EQ (MAX_COST, maze->cost(cell));
  }
}


TEST_F (CostTest, MazeSetCosts_SetCost_getCost) {
  maze->setCost(0x43, 123);
  EXPECT_EQ(123, maze->cost(0x43));
}

TEST_F (CostTest, GetNeighbourCosts_GetCostIgnoresWals) {
  maze->resetToEmptyMaze();
  for (int cell = 0; cell < maze->numCells(); ++cell) {
    maze->setCost(cell,cell);
  }
  uint32_t neighbour;
  uint32_t cell;
  for (int cell = 0; cell < maze->numCells(); ++cell) {
    uint32_t neighbour;
    EXPECT_EQ(cell,maze->cost(cell));
    neighbour = maze->cellNorth(cell);
    EXPECT_EQ(neighbour,maze->cost(neighbour));
    neighbour = maze->cellEast(cell);
    EXPECT_EQ(neighbour,maze->cost(neighbour));
    neighbour = maze->cellSouth(cell);
    EXPECT_EQ(neighbour,maze->cost(neighbour));
    neighbour = maze->cellWest(cell);
    EXPECT_EQ(neighbour,maze->cost(neighbour));
  }
}

TEST_F (CostTest, CostDirection_GivesNeighbourCostIfNoWall) {
  maze->resetToEmptyMaze();
  for (int cell = 0; cell < maze->numCells(); ++cell) {
    maze->setCost(cell,cell);
  }
  uint32_t neighbour;
  uint32_t cell;
  cell = 0x22;
  neighbour = maze->cellNorth(cell);
  EXPECT_EQ(neighbour,maze->costNorth(cell));
  neighbour = maze->cellEast(cell);
  EXPECT_EQ(neighbour,maze->costEast(cell));
  neighbour = maze->cellSouth(cell);
  EXPECT_EQ(neighbour,maze->costSouth(cell));
  neighbour = maze->cellWest(cell);
  EXPECT_EQ(neighbour,maze->costWest(cell));
}

TEST_F (CostTest, CostDirection_GivesUINT16_MAXIfWall) {
  maze->resetToEmptyMaze();
  for (int cell = 0; cell < maze->numCells(); ++cell) {
    maze->setCost(cell,cell);
  }
  uint32_t cell;
  cell = 0x22;
  maze->setWall(cell,NORTH);
  maze->setWall(cell,EAST);
  maze->setWall(cell,SOUTH);
  maze->setWall(cell,WEST);
  EXPECT_EQ(MAX_COST,maze->costNorth(cell));
  EXPECT_EQ(MAX_COST,maze->costEast(cell));
  EXPECT_EQ(MAX_COST,maze->costSouth(cell));
  EXPECT_EQ(MAX_COST,maze->costWest(cell));
}

TEST_F (CostTest, SmallestNeighbourDirection) {
  maze->resetToEmptyMaze();
  for (int cell = 0; cell < maze->numCells(); ++cell) {
    maze->setCost(cell,cell);
  }

  EXPECT_EQ(WEST, maze->directionToSmallest(0x22));
  maze->setWall(0x22,WEST);
  EXPECT_EQ(SOUTH, maze->directionToSmallest(0x22));
  maze->setWall(0x22,SOUTH);
  EXPECT_EQ(NORTH, maze->directionToSmallest(0x22));
  maze->setWall(0x22,NORTH);
  EXPECT_EQ(EAST, maze->directionToSmallest(0x22));
  maze->setWall(0x22,EAST);

  // no accessible neighbours now
  EXPECT_EQ(INVALID_DIRECTION, maze->directionToSmallest(0x22));
  EXPECT_EQ(INVALID_DIRECTION, maze->directionToSmallest(0x22, NORTH));
  EXPECT_EQ(INVALID_DIRECTION, maze->directionToSmallest(0x22, EAST));
  EXPECT_EQ(INVALID_DIRECTION, maze->directionToSmallest(0x22, SOUTH));
  EXPECT_EQ(INVALID_DIRECTION, maze->directionToSmallest(0x22, WEST));

}

TEST_F (CostTest, UpdateDirections) {
  maze->resetToEmptyMaze();
  for (int cell = 0; cell < maze->numCells(); ++cell) {
    maze->setCost(cell,cell);
  }

  maze->updateDirections();
  EXPECT_EQ(WEST, maze->direction(0x22));

  maze->setWall(0x22,WEST);
  EXPECT_EQ(WEST, maze->direction(0x22));
  maze->updateDirections();
  EXPECT_EQ(SOUTH, maze->direction(0x22));

  maze->setWall(0x22,SOUTH);
  EXPECT_EQ(SOUTH, maze->direction(0x22));
  maze->updateDirections();
  EXPECT_EQ(NORTH, maze->direction(0x22));

  maze->setWall(0x22,NORTH);
  EXPECT_EQ(NORTH, maze->direction(0x22));
  maze->updateDirections();
  EXPECT_EQ(EAST, maze->direction(0x22));

  maze->setWall(0x22,EAST);
  EXPECT_EQ(EAST, maze->direction(0x22));
  maze->updateDirections();
  EXPECT_EQ(INVALID_DIRECTION, maze->direction(0x22));
}
