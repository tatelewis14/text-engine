#pragma once

typedef struct room 
{
	room* west = NULL; 
	room* east = NULL;
	room* south = NULL;
	room* north = NULL;
	bool winning_room = false;
	char* text;
} room;
typedef enum 
{
	WEST,
    EAST,
    SOUTH,
    NORTH
} Direction;

void free_room(room* r);

void free_rooms(int n, ...);

void set_room_text(room* r, const char* c);

bool has_paths(room* r);

void ask_dir(room* r);

void run_room(room* r);

void link_rooms(room* r, int pairs, ...);

void clear_input_buffer();

void set_winning_room(room r);
