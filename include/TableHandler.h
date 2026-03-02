//ColorTable.h
#ifndef TABLEHANDLER_H
#define TABLEHANDLER_H

#include <stddef.h>
#include <arduino.h>
#include "Types.h"
struct table_row{
	int r,g,b;
	const char* color_name;
};

extern const size_t MAX_ROW_DATA;

class TableHandler{
	public:
		static RGB getColor(RGB rgb);
};


#endif
