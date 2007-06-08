#ifndef WED_MAPBKGND_H
#define WED_MAPBKGND_H

#include "WED_MapLayer.h"

class	WED_MapBkgnd : public WED_MapLayer {
public:

						 WED_MapBkgnd(GUI_Pane * host, WED_MapZoomerNew * zoomer, IResolver * resolver);
	virtual				~WED_MapBkgnd();

	virtual	void		DrawVisualization(int inCurrent, GUI_GraphState * g);
	virtual	void		DrawStructure	 (int inCurrent, GUI_GraphState * g);
		
};
		

#endif
