#include "game.h"

int save_savestate(void* pointer)
{
  file_destination = (char*) pointer;
  FILE *f;
  int i, return_value = 0;
  f = fopen(file_destination, "wb");
  if(f == NULL)
  {
    return_value = 1;
    goto save_savestate_return;
  }
  if(MAX_FLAGS != fwrite(resource_flags, sizeof(int), MAX_FLAGS, f))
  {
    return_value = 1;
    goto save_savestate_return;
  }
  if(MAX_TEXTURES != fwrite(resource_textures, sizeof(char), MAX_TEXTURES, f))
  {
    return_value = 1;
    goto save_savestate_return;
  }
  for(i = 0; i < MAX_MAP_HEIGHT; i++)
  {
    if(MAX_MAP_WIDTH != fwrite(resource_map[i], sizeof(int), MAX_MAP_WIDTH, f))
    {
    return_value = 1;
    goto save_savestate_return;
    }
  }
  if(3 * MAX_KEYS != fwrite(resource_keys, sizeof(int), 3 * MAX_KEYS, f))
  {
    return_value = 1;
    goto save_savestate_return;
  }
  save_savestate_return:
  fclose(f);
  return return_value;
}

int load_savestate(void* pointer)
{
  file_destination = (char*) pointer;
  FILE *f;
  int i, return_value = 0;
  f = fopen(file_destination, "rb");
  if(f == NULL)
  {
    return_value = 1;
    goto load_savestate_return;
  }
  if(MAX_FLAGS != fread(resource_flags, sizeof(int), MAX_FLAGS, f))
  {
    return_value = 1;
    goto load_savestate_return;
  }
  if(MAX_TEXTURES != fread(resource_textures, sizeof(char), MAX_TEXTURES, f))
  {
    return_value = 1;
    goto load_savestate_return;
  }
  for(i = 0; i < MAX_MAP_HEIGHT; i++)
  {
    if(MAX_MAP_WIDTH != fread(resource_map[i], sizeof(int), MAX_MAP_WIDTH, f))
    {
    return_value = 1;
    goto load_savestate_return;
    }
  }
  if(3 * MAX_KEYS != fread(resource_keys, sizeof(int), 3 * MAX_KEYS, f))
  {
    return_value = 1;
    goto load_savestate_return;
  }
  load_savestate_return:
  fclose(f);
  return return_value;
}

void time_tick()
{
  if(!(sim_time % 100))
  {
  }
}
