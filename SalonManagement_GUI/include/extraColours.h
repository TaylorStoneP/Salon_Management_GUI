#pragma once
#include "colourquad.h"
#include "wx/colour.h"
//change this to change colour class
#define tpCOLOURTYPE wxColour
//change this to change whether colours are read in 0-1 format or 0-255 format
#define tpCOLOURNUMBERTYPE 255

#define tpBITDEPTH 32

#if tpCOLOURNUMBERTYPE == 255
#define tpCDIV(x) x
#elif tpCOLOURNUMBERTYPE == 1
#define tpCDIV(x) x/255
#endif

#if tpBITDEPTH == 24
#define DEPTH_C(x)
#elif tpBITDEPTH == 32
#define DEPTH_C(x) x
#endif

namespace tp_colour_menus {
	static const tpCOLOURTYPE menu_white	(tpCDIV(218),	tpCDIV(218),	tpCDIV(218),	DEPTH_C(tpCDIV(255)));
	static const tpCOLOURTYPE menu_grey		(tpCDIV(180),	tpCDIV(180),	tpCDIV(180),	DEPTH_C(tpCDIV(255)));
	static const tpCOLOURTYPE menu_black	(tpCDIV(46),	tpCDIV(46),		tpCDIV(46),		DEPTH_C(tpCDIV(255)));
}																												
																												
namespace tp_colour_misc {																						
	static const tpCOLOURTYPE cyan			(tpCDIV(0),		tpCDIV(255),	tpCDIV(255),	DEPTH_C(tpCDIV(255)));
	static const tpCOLOURTYPE magenta		(tpCDIV(255),	tpCDIV(0),		tpCDIV(255),	DEPTH_C(tpCDIV(255)));
	static const tpCOLOURTYPE white			(tpCDIV(255),	tpCDIV(255),	tpCDIV(255),	DEPTH_C(tpCDIV(255)));
	static const tpCOLOURTYPE black			(tpCDIV(0),		tpCDIV(0),		tpCDIV(0),		DEPTH_C(tpCDIV(255)));
	static const tpCOLOURTYPE green			(tpCDIV(0),		tpCDIV(255),	tpCDIV(0),		DEPTH_C(tpCDIV(255)));
	static const tpCOLOURTYPE red			(tpCDIV(255),	tpCDIV(0),		tpCDIV(0),		DEPTH_C(tpCDIV(255)));
	static const tpCOLOURTYPE blue			(tpCDIV(0),		tpCDIV(0),		tpCDIV(255),	DEPTH_C(tpCDIV(255)));
	static const tpCOLOURTYPE yellow		(tpCDIV(255),	tpCDIV(255),	tpCDIV(0),		DEPTH_C(tpCDIV(255)));
	static const tpCOLOURTYPE orange		(tpCDIV(255),	tpCDIV(128),	tpCDIV(0),		DEPTH_C(tpCDIV(255)));
	static const tpCOLOURTYPE purple		(tpCDIV(128),	tpCDIV(0),		tpCDIV(255),	DEPTH_C(tpCDIV(255)));
	static const tpCOLOURTYPE deep_blue		(tpCDIV(44),	tpCDIV(44),		tpCDIV(127),	DEPTH_C(tpCDIV(255)));
	static const tpCOLOURTYPE wash_blue		(tpCDIV(14),	tpCDIV(212),	tpCDIV(203),	DEPTH_C(tpCDIV(255)));
	static const tpCOLOURTYPE sand_yellow	(tpCDIV(249),	tpCDIV(233),	tpCDIV(142),	DEPTH_C(tpCDIV(255)));
	static const tpCOLOURTYPE grass_green	(tpCDIV(53),	tpCDIV(159),	tpCDIV(0),		DEPTH_C(tpCDIV(255)));
	static const tpCOLOURTYPE forest_green	(tpCDIV(0),		tpCDIV(72),		tpCDIV(51),		DEPTH_C(tpCDIV(255)));
	static const tpCOLOURTYPE rock_brown	(tpCDIV(90),	tpCDIV(77),		tpCDIV(65),		DEPTH_C(tpCDIV(255)));
	static const tpCOLOURTYPE dirt_brown	(tpCDIV(68),	tpCDIV(42),		tpCDIV(27),		DEPTH_C(tpCDIV(255)));
}

namespace tp_colour_log {
	static const tpCOLOURTYPE error(tpCDIV(255), tpCDIV(70), tpCDIV(54), DEPTH_C(tpCDIV(255)));
	static const tpCOLOURTYPE warning(tpCDIV(237), tpCDIV(171), tpCDIV(0), DEPTH_C(tpCDIV(255)));
	static const tpCOLOURTYPE trace(tpCDIV(135), tpCDIV(227), tpCDIV(107), DEPTH_C(tpCDIV(255)));
	static const tpCOLOURTYPE light(tpCDIV(228), tpCDIV(228), tpCDIV(228), DEPTH_C(tpCDIV(255)));
	static const tpCOLOURTYPE debug(tpCDIV(75), tpCDIV(75), tpCDIV(75), DEPTH_C(tpCDIV(255)));
	static const tpCOLOURTYPE info(tpCDIV(121), tpCDIV(182), tpCDIV(223), DEPTH_C(tpCDIV(255)));
}