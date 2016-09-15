#include "render.h"

void draw_map()
{
  int i, j;
  for(i = 0; i < MAX_MAP_HEIGHT; i++)
  {
    for(j = 0; j < MAX_MAP_WIDTH; j++)
    {
      printf("%c", resource_textures[resource_map[i][j]]);
    }
  }
}
