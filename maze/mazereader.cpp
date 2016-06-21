/*
 * File:   mazereader.c
 * Author: peterharrison
 *
 * Created on 13 February 2016, 21:16
 */

#include <stdio.h>
#include <assert.h>
#include "maze.h"
#include "mazereader.h"

static uint8_t wallData[MAZE_ROWS][MAZE_COLS];

void ClearWallData (void)
{
  location_t loc;
  for (loc.col = 0; loc.col < MAZE_COLS; loc.col++) {
    for (loc.row = 0; loc.row < MAZE_ROWS; loc.row++) {
      wallData[loc.row][loc.col] = 0;
    }
  }
}

void ReadRealWallsFromFile (char * filename)
{
  FILE *fp;
  location_t loc;
  ClearWallData(); /* in case we do not find a file */
  if ( (fp = fopen (filename, "rb")) == NULL) {
    return;
  }
  for (loc.col = 0; loc.col < MAZE_COLS; loc.col++) {
    for (loc.row = 0; loc.row < MAZE_ROWS; loc.row++) {
      wallData[loc.row][loc.col] = fgetc (fp);// & ~VISITED;
    }
  }
  fclose (fp);
}

/*
 * TODO: should this be in the maze.c file?
 */
void UpdateEntireMazeFromRealWalls (void)
{
  location_t loc;
  for (loc.col = 0; loc.col < MAZE_COLS; loc.col++) {
    for (loc.row = 0; loc.row < MAZE_ROWS; loc.row++) {
      UpdateCellFromWallData (loc, wallData[loc.row][loc.col]);
    }
  }
}

walls_t ReadWallSensors (location_t loc)
{
  return wallData[loc.row][loc.col];
}

