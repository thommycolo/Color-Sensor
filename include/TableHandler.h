//ColorTable.h
#ifndef TABLEHANDLER_H
#define TABLEHANDLER_H

#include "Types.h"
#include <Arduino.h>
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
