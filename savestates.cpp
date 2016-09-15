#include "savestates.h"

int save_savestate(void* pointer)
{
  char *file_destination = (char*) pointer;
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
  for(i = 0; i < MAX_MAP_HEIGHT; i++)
  {
    if(MAX_MAP_WIDTH != fwrite(resource_map[i], sizeof(int), MAX_MAP_WIDTH, f))
    {
    return_value = 1;
    goto save_savestate_return;
    }
  }
  save_savestate_return:
  fclose(f);
  return return_value;
}

int load_savestate(void* pointer)
{
  char *file_destination = (char*) pointer;
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
  for(i = 0; i < MAX_MAP_HEIGHT; i++)
  {
    if(MAX_MAP_WIDTH != fread(resource_map[i], sizeof(int), MAX_MAP_WIDTH, f))
    {
    return_value = 1;
    goto load_savestate_return;
    }
  }
  load_savestate_return:
  fclose(f);
  return return_value;
}

int load_keys()
{
  FILE *f;
  int i = 0, return_value = 0, key, flag, value;
  f = fopen("keys.dat", "r");
  if(f == NULL)
  {
    return_value = 1;
    goto load_keys_return;
  }
  fscanf(f, "\n");
  while(fscanf(f, "%d %d %d\n", &key, &flag, &value)
  {
    resource_keys[i] = key;
    resource_keys[i + 1] = flag;
    resource_keys[i + 2] = value;
    i += 3;
  }
  load_keys_return:
  fclose(f);
  return return_value;
}

int load_textures()
{
  FILE *f;
  int index, texture, return_value = 0;
  f = fopen("textures.dat", "r");
  if(f == NULL)
  {
    return_value = 1;
    goto load_textures_return;
  }
  fscanf(f, "\n");
  while(fscanf(f, "%d %d\n", &index, &texture) != 2)
  {
    resource_textures[index] = texture;
  }
  load_textures_return:
  fclose(f);
  return return_value;
}

int load_map()
{
  FILE *f;
  int i, j, return_value = 0;
  f = fopen("map.dat", "r");
  if(f == NULL)
  {
    return_value = 1;
    goto load_keys_return;
  }
  fscanf(f, "\n");
  for(i = 0; i < MAX_MAP_HEIGHT; i++)
  {
    for(j = 0; j < MAX_MAP_WIDTH; j++)
    {
      fscanf("%d", &resource_map[i][j]);
    } 
  }
  load_keys_return:
  fclose(f);
  return return_value;
}
