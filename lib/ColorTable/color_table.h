//color_table.h
#ifndef COLOR_TABLE_H
#define COLOR_TABLE_H

#include <stddef.h>
#include <arduino.h>

struct table_row{
	int r,g,b;
	const char* color_name;
};

extern const size_t MAX_ROW_DATA;

class TableHandler{
	public:
		static const char* getColor(int r, int g, int b);
};


#endif
