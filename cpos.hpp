#ifndef __CURSORPOSITION__
#define __CURSORPOSITION__

struct coord_t {
int x;
int y;
};

coord_t getpos();
void setpos(int, int);

#endif
