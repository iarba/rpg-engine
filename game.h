#include <iostream>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <savestates.h>
#include "defines.h"

int *resource_flags, **resource_map, *resource_keys;
char *resource_textures;
