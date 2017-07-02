/*
 * File:   mazepathfinder.c
 * Author: peterharrison
 *
 * Created on 16 February 2016, 14:55
 */

#include "mazepathfinder.h"
#include <cstring>

/*
 * Generate a path from cost data following a flood;
 * The method simply walks downhill from start to target marking the
 * direction data on its way.
 * All cells not on the path will have INVALID direction data
 * Returns the length of the path in cells
 *
 * No attempt is made to verify that a valid path exists
 */


PathFinder::PathFinder() :
    mCellCount(0),
    mStartHeading(INVALID_DIRECTION),
    mEndHeading(INVALID_DIRECTION),
    mStartCell(0),
    mEndCell(0),
    mReachesTarget(false) {
  memset(mBuffer, 0, 1024);
}

PathFinder::~PathFinder() {

}

char *PathFinder::path() {
  return mBuffer;
}

char *PathFinder::toString() {
  return (char *) mBuffer;
}

static char pathOptions[16] = {
    'F', 'R', 'A', 'L',
    'L', 'F', 'R', 'A',
    'A', 'L', 'F', 'R',
    'R', 'A', 'L', 'F'
};

void PathFinder::generate(Maze *maze, uint16_t start, uint16_t target) {

  char *pPath = mBuffer;
  uint16_t here = start;
  uint8_t headingHere = maze->direction(here);
  mStartHeading = headingHere;
  mEndHeading = mStartHeading;
  mCellCount = 0;
  *pPath++ = 'B';
  if (headingHere == INVALID_DIRECTION) {
    *pPath++ = 'S';
    *pPath = 0;
    return;
  }
  while (here != target) {
    if (!maze->isVisited(here)) {
      break;
    }
    if (mCellCount >= MAX_PATH_LENGTH) {
      break;
    }
    uint8_t headingLast = headingHere;
    headingHere = maze->direction(here);
    char command = pathOptions[headingLast * 4 + headingHere];
    if (command == 'R') {
      mEndHeading = Maze::rightOf(mEndHeading);
    }
    if (command == 'L') {
      mEndHeading = Maze::leftOf(mEndHeading);
    }
    *pPath++ = command;
    mCellCount++;
    here = maze->neighbour(here, headingHere);
  }
  mEndCell = here;
  if (mEndCell == target) {
    *pPath++ = 'S';
    mReachesTarget = true;
  } else {
    *pPath++ = 'X';
    mReachesTarget = false;
  }
  // this is a string to be sure it gets terminated properly
  mCellCount++;
  *pPath = 0;
}

/**
 * The length will always include the final move ('S" or 'X') as it is
 * a cell through which the mouse moves.
 * The start marker ('B') is not counted
 *
 */
uint16_t PathFinder::length() {
  return mCellCount;
}

uint8_t PathFinder::startHeading() const {
  return mStartHeading;
}

uint8_t PathFinder::endHeading() const {
  return mEndHeading;
}

uint16_t PathFinder::endCell() const {
  return mEndCell;
}

bool PathFinder::reachesTarget() const {
  return mReachesTarget;
}

uint16_t PathFinder::startCell() const {
  return mStartCell;
}

void PathFinder::makeDiagonalPath(uint8_t *pCommands, const char *src) {
  *pCommands++ = CMD_BEGIN;
  *pCommands++ = CMD_END;
  *pCommands = CMD_STOP;

}

void PathFinder::makeSmoothPath(uint8_t *pCommands, const char *src) {
  *pCommands++ = CMD_BEGIN;
  *pCommands++ = CMD_END;
  *pCommands = CMD_STOP;
}

void PathFinder::makeInPlacePath(uint8_t *pCommands, const char *src) {
  *pCommands++ = CMD_BEGIN;
  *pCommands++ = CMD_END;
  *pCommands = CMD_STOP;

}

