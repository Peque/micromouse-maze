/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   main.c
 * Author: peterharrison
 *
 * Created on 07 February 2016, 23:47
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "maze.h"
#include "mazeprinter.h"
/*
 *
 */
int main (int argc, char** argv)
{
  printf ("micromouse maze\n");
  MazeResetData();
  PrintMaze(WALLS+DIRS);
  return (EXIT_SUCCESS);
}

