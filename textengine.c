#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdarg.h>
//room for holding different directions and text
typedef struct room 
{
	room* west = NULL; 
	room* east = NULL;
	room* south = NULL;
	room* north = NULL;
	bool winning_room = false;
	char* text;
} room;
//for managing directions
typedef enum 
{
	WEST,
    EAST,
    SOUTH,
    NORTH
} Direction;
//from chatgpt for clearing newline after changing rooms
void clear_input_buffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
// obvious...
void free_room(room* r)
{
	if(r->text) free(r->text);
}
void free_rooms(int n, ...)
{
	va_list ptr;
	va_start(ptr, n);
	for(int i = 0; i < n; i++)
	{
		room temp = va_arg(ptr, room);
		if(temp.text)
		free(temp.text);
	}
};
//also obvious...
void set_room_text(room* r, const char* c)
{
	//appends a newline if there isn't one already
	size_t size = strlen(c);
	if(c[size-1] != '\n');
	char* temp = (char*)malloc(strlen(c)+2);
	strcpy(temp, c);
	strcat(temp, "\n");
	r->text = strdup(temp);
	free(temp);
}
//c'mon
bool has_paths(room* r)
{
	return r->west || r->east || r->north || r->south;
}
//asks what direction a user wants to go in and handles input
void ask_dir(room* r)
{
	if(r->west != NULL) printf("Go [W]est?\n");
	if(r->east != NULL) printf("Go [E]ast?\n");
	if(r->north != NULL) printf("Go [N]orth?\n");
	if(r->south != NULL) printf("Go [S]outh?\n");
}
//prints the room's text and it's paths if it has them
void run_room(room* r)
{
	if(r->text) printf("\n%s\n", r->text); //isolate room text
	if(!has_paths(r)) return;
	if(r->winning_room == true)
	{
		printf("You won!\n");
		printf("exiting game");
		return;
	}
	ask_dir(r);
	printf("Enter the first letter of the direction\n");
	printf("Enter [Q] to exit\n");
	char dir;
	dir = getchar();
	clear_input_buffer();
	switch (dir) 
        {
            case 'W':
                if (r->west) run_room(r->west);
                else printf("There is no room to the west.\n");
                break;
            case 'E':
                if (r->east) run_room(r->east);
                else printf("There is no room to the east.\n");
                break;
            case 'N':
                if (r->north) run_room(r->north);
                else printf("There is no room to the north.\n");
                break;
            case 'S':
                if (r->south) run_room(r->south);
                else printf("There is no room to the south.\n");
                break;
			case 'Q':
				printf("Game Exited");
				break;
            default:
                printf("Invalid direction. Try again.\n");
        }
}
void link_rooms(room* r, int pairs, ...)
{
	//-------------------------------------------------------------------------//
	//  IF A DUPLICATE DIRECTION IS PASSED IT WILL OVERRIDE THE PREVIOUS ROOM  //
	//-------------------------------------------------------------------------//
	
	if(pairs > 4) printf("Excessive amount of rooms being linked");
	
	va_list args;
	va_start(args, pairs);
	for(int i = 0; i < pairs; i++)
	{
		int dir = va_arg(args, int); // has to be converted to an int when passed thru '...'(variadic args)
		room* linked_room = va_arg(args, room*);
		switch(dir)
		{
			case WEST:
                r->west = linked_room;
				linked_room->east = r;
                break;
            case EAST:
                r->east = linked_room;
				linked_room->west = r;
                break;
            case SOUTH:
                r->south = linked_room;
				linked_room->north = r;
                break;
            case NORTH:
                r->north = linked_room;
				linked_room->south = r;
                break;
			
		}
	}
	va_end(args);
}
void set_winning_room(room r)
{
	r.winning_room = true;
}
