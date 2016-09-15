#include "game.h"
#include "savestates.h"
#include "render.h"
#include "events.h"

int *resource_flags, **resource_map, *resource_keys;
char *resource_textures;
int resource_time;

int getch()
{
  struct termios oldt, newt;
  int ch;
  tcgetattr( STDIN_FILENO, &oldt );
  newt = oldt;
  newt.c_lflag &= ~( ICANON | ECHO );
  tcsetattr( STDIN_FILENO, TCSANOW, &newt );
  ch = getchar();
  tcsetattr( STDIN_FILENO, TCSANOW, &oldt );
  return ch;
}

void key_search(int c, int left, int right)
{
  int avg = (left + right) / 2;
  if(resource_keys[3 * avg] == c)
  {
    resource_flags[resource_keys[3 * avg + 1]] = resource_keys[3 * avg + 2];
  }
  if(left >= right)
  {
    return;
  }
  if(resource_keys[3 * avg] < c)
  {
    key_search(c, avg+1, right);
  }
  else
  {
    key_search(c, left, avg-1);
  }
}

void* read_input(void* args)
{
  while(!resource_flags[0])
  {
    int c = getch();
    key_search(c, 0, MAX_KEYS);
  }
  return NULL;
}

int main(int argc, char** argv)
{
  int error_code = 0, i;
  resource_flags = (int*) calloc(MAX_FLAGS, sizeof(int));
  if(!resource_flags)
  {
    error_code = 1;
    goto initialisation_error;
  }
  resource_textures = (char*) calloc(MAX_TEXTURES, sizeof(char));
  if(!resource_textures)
  {
    error_code = 2;
    goto initialisation_error;
  }
  resource_map = (int**) calloc(MAX_MAP_HEIGHT, sizeof(int*));
  if(resource_map)
  {
    error_code = 3;
    goto initialisation_error;
  }
  for(i = 0; i < MAX_MAP_HEIGHT; i++)
  {
    resource_map[i] = (int*) calloc(MAX_MAP_WIDTH, sizeof(int));
    if(!resource_map[i])
    {
      error_code = 4;
      goto initialisation_error;
    }
  }
  resource_keys = (int*) calloc(3 * MAX_KEYS, sizeof(int));
  if(!resource_map)
  {
    error_code = 5;
    goto initialisation_error;
  }
  if(argc >= 2)
  {
    if(load_savestate(argv[1]))
    {
      error_code = 7;
      goto initialisation_error;
    }
  }
  else
  {
    if(load_map())
    {
      error_code = 8;
      goto initialisation_error;
    }
  }
  if(load_keys())
  {
    error_code = 9;
    goto initialisation_error;
  }
  if(load_textures())
  {
    error_code = 10;
    goto initialisation_error;
  }
  if(pthread_create(new pthread_t, NULL, &read_input, NULL))
  {
    error_code = 6;
    goto initialisation_error;
  }
  while(!resource_flags[0])
  {
    resource_time++;
    if(event_interpretation())
    {
      break;
    }
    draw_map();
  }
  return 0;
  initialisation_error:
  printf("Initialisation failed\n");
  printf("Error code : %d \n", error_code);
  return -1;
}


