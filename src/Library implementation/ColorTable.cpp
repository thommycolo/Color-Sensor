// ColorTable population and implementation

#include "ColorTable.h"
#include <cmath>
#include "Types.h"


using namespace std;

const table_row data[] = 
{
	{  0,   0,   0,   "Nero"              },
    {  0,   0,  64,   "Blu-Magenta Scuro" },
    {  0,   0, 128,   "Blu Scuro"         },
    {  0,   0, 255,   "Blu"               },
    {  0,  64,   0,   "Verde-Giallo Scuro"},
    {  0,  64,  64,   "Ciano Scuro"       },
    {  0,  64, 128,   "Blu-Ciano Scuro"   },
    {  0,  64, 192,   "Blu Scuro"         },
    {  0,  64, 255,   "Blu"               },
    {  0, 128,   0,   "Verde Scuro"       },
    {  0, 128,  64,   "Verde-Ciano Scuro" },
    {  0, 128, 128,   "Ciano Scuro"       },
    {  0, 128, 192,   "Blu-Ciano Scuro"   },
    {  0, 128, 255,   "Blu"               },
    {  0, 192,   0,   "Verde Scuro"       },
    {  0, 192,  64,   "Verde Scuro"       },
    {  0, 192, 128,   "Verde-Ciano Scuro" },
    {  0, 192, 192,   "Ciano Chiaro"      },
    {  0, 192, 255,   "Blu-Ciano"         },
    {  0, 255,   0,   "Verde"             },
    {  0, 255,  64,   "Verde"             },
    {  0, 255, 128,   "Verde"             },
    {  0, 255, 192,   "Verde-Ciano"       },
    {  0, 255, 255,   "Ciano"             },
    { 64,   0,   0,   "Arancio Scuro"     },
    { 64,   0,  64,   "Magenta Scuro"     },
    { 64,   0, 128,   "Blu-Magenta Scuro" },
    { 64,   0, 192,   "Blu Scuro"         },
    { 64,   0, 255,   "Blu"               },
    { 64,  64,   0,   "Giallo Scuro"      },
    { 64,  64,  64,   "Grigio Scuro"      },
    { 64,  64, 128,   "Blu-Magenta Scuro" },
    { 64,  64, 192,   "Blu Scuro"         },
    { 64,  64, 255,   "Blu Scuro"         },
    { 64, 128,   0,   "Verde-Giallo Scuro"},
    { 64, 128,  64,   "Verde-Giallo Scuro"},
    { 64, 128, 128,   "Ciano Scuro"       },
    { 64, 128, 192,   "Blu-Ciano Chiaro"  },
    { 64, 128, 255,   "Blu Chiaro"        },
    { 64, 192,   0,   "Verde Scuro"       },
    { 64, 192,  64,   "Verde Scuro"       },
    { 64, 192, 128,   "Verde-Ciano Chiaro"},
    { 64, 192, 192,   "Ciano Chiaro"      },
    { 64, 192, 255,   "Blu-Ciano Chiaro"  },
    { 64, 255,   0,   "Verde"             },
    { 64, 255,  64,   "Verde Scuro"       },
    { 64, 255, 128,   "Verde Chiaro"      },
    { 64, 255, 192,   "Verde-Ciano Chiaro"},
    { 64, 255, 255,   "Ciano Chiaro"      },
    {128,   0,   0,   "Rosso Scuro"       },
    {128,   0,  64,   "Rosso-Magenta Scuro"},
    {128,   0, 128,   "Magenta Scuro"     },
    {128,   0, 192,   "Blu-Magenta Scuro" },
    {128,   0, 255,   "Blu"               },
    {128,  64,   0,   "Arancio Scuro"     },
    {128,  64,  64,   "Arancio Scuro"     },
    {128,  64, 128,   "Magenta Scuro"     },
    {128,  64, 192,   "Blu-Magenta Chiaro"},
    {128,  64, 255,   "Blu Chiaro"        },
    {128, 128,   0,   "Giallo Scuro"      },
    {128, 128,  64,   "Giallo Scuro"      },
    {128, 128, 128,   "Grigio Chiaro"     },
    {128, 128, 192,   "Blu-Magenta Chiaro"},
    {128, 128, 255,   "Blu Chiaro"        },
    {128, 192,   0,   "Verde-Giallo Scuro"},
    {128, 192,  64,   "Verde-Giallo Chiaro"},
    {128, 192, 128,   "Verde-Giallo Chiaro"},
    {128, 192, 192,   "Ciano Chiaro"      },
    {128, 192, 255,   "Blu-Ciano Chiaro"  },
    {128, 255,   0,   "Verde"             },
    {128, 255,  64,   "Verde Chiaro"      },
    {128, 255, 128,   "Verde Chiaro"      },
    {128, 255, 192,   "Verde-Ciano Chiaro"},
    {128, 255, 255,   "Ciano Chiaro"      },
    {192,   0,   0,   "Rosso Scuro"       },
    {192,   0,  64,   "Rosso Scuro"       },
    {192,   0, 128,   "Rosso-Magenta Scuro"},
    {192,   0, 192,   "Magenta Chiaro"    },
    {192,   0, 255,   "Blu-Magenta"       },
    {192,  64,   0,   "Rosso Scuro"       },
    {192,  64,  64,   "Rosso Scuro"       },
    {192,  64, 128,   "Rosso-Magenta Chiaro"},
    {192,  64, 192,   "Magenta Chiaro"    },
    {192,  64, 255,   "Blu-Magenta Chiaro"},
    {192, 128,   0,   "Arancio Scuro"     },
    {192, 128,  64,   "Arancio Chiaro"    },
    {192, 128, 128,   "Arancio Chiaro"    },
    {192, 128, 192,   "Magenta Chiaro"    },
    {192, 128, 255,   "Blu-Magenta Chiaro"},
    {192, 192,   0,   "Giallo Chiaro"     },
    {192, 192,  64,   "Giallo Chiaro"     },
    {192, 192, 128,   "Giallo Chiaro"     },
    {192, 192, 192,   "Grigio Chiaro"     },
    {192, 192, 255,   "Blu-Magenta Chiaro"},
    {192, 224,   0,   "Verde-Giallo Chiaro"},
    {192, 224,  64,   "Verde-Giallo Chiaro"},
    {192, 224, 128,   "Verde-Giallo Chiaro"},
    {192, 224, 192,   "Verde-Giallo Chiaro"},
    {192, 224, 255,   "Blu-Ciano Chiaro"  },
    {192, 255,   0,   "Verde-Giallo"      },
    {192, 255,  64,   "Verde-Giallo Chiaro"},
    {192, 255, 128,   "Verde-Giallo Chiaro"},
    {192, 255, 192,   "Verde-Giallo Chiaro"},
    {192, 255, 255,   "Ciano Chiaro"      },
    {255,   0,   0,   "Rosso"             },
    {255,   0,  64,   "Rosso"             },
    {255,   0, 128,   "Rosso"             },
    {255,   0, 192,   "Rosso-Magenta"     },
    {255,   0, 255,   "Magenta"           },
    {255,  64,   0,   "Rosso"             },
    {255,  64,  64,   "Rosso Scuro"       },
    {255,  64, 128,   "Rosso Chiaro"      },
    {255,  64, 192,   "Rosso-Magenta Chiaro"},
    {255,  64, 255,   "Magenta Chiaro"    },
    {255, 128,   0,   "Rosso"             },
    {255, 128,  64,   "Rosso Chiaro"      },
    {255, 128, 128,   "Rosso Chiaro"      },
    {255, 128, 192,   "Rosso-Magenta Chiaro"},
    {255, 128, 255,   "Magenta Chiaro"    },
    {255, 192,   0,   "Arancio"           },
    {255, 192,  64,   "Arancio Chiaro"    },
    {255, 192, 128,   "Arancio Chiaro"    },
    {255, 192, 192,   "Arancio Chiaro"    },
    {255, 192, 255,   "Magenta Chiaro"    },
    {255, 255,   0,   "Giallo"            },
    {255, 255,  64,   "Giallo Chiaro"     },
    {255, 255, 128,   "Giallo Chiaro"     },
    {255, 255, 192,   "Giallo Chiaro"     },
    {255, 255, 255,   "Bianco"            }
};


const size_t MAX_ROW_DATA = sizeof(data)/sizeof(table_row);


RGB TableHandler::getColor(RGB rgb){
	rgb.r = round( rgb.r/64) *64;
	rgb.g = round( rgb.g/64) *64;
	rgb.b = round( rgb.b/64) *64;
	int i=0;
	for (size_t i = 0; i < MAX_ROW_DATA; i++) {
        
        if (data[i].r == rgb.r && data[i].g == rgb.g && data[i].b == rgb.b) {
            rgb.color_name = data[i].color_name;
            return rgb; 
        }
    }	
	return rgb;
}


