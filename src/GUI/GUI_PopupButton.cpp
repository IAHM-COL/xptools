#include "GUI_PopupButton.h"
#include "GUI_Messages.h"
#include "GUI_Fonts.h"
#include "GUI_GraphState.h"

#if APL
	#include <OpenGL/gl.h>
#else
	#include <gl/gl.h>
#endif

GUI_PopupButton::GUI_PopupButton()
{
}

GUI_PopupButton::~GUI_PopupButton()
{
}

void		GUI_PopupButton::SetDescriptor(const string& inDesc)
{
	GUI_Control::SetDescriptor(inDesc);

	mItems.clear();

	string::const_iterator b, e;
	b = inDesc.begin();
	while (b != inDesc.end())
	{
		e = b;
		while (e != inDesc.end() && *e != '\n') ++e;
		mItems.push_back(string(b,e));
		if (e != inDesc.end()) ++e;
		b = e;
	}
	
	SetMax(mItems.size());
	if (GetValue() > GetMax()) SetValue(GetMax());
	Refresh();
}

void		GUI_PopupButton::Draw(GUI_GraphState * state)
{
	string desc, sub;
	
	int bounds[4];
	GetBounds(bounds);
	state->SetState(0,0,0,  0,0,0,0);
	glColor3f(1,1,1);
	glBegin(GL_QUADS);
	glVertex2i(bounds[0],bounds[1]);
	glVertex2i(bounds[0],bounds[3]);
	glVertex2i(bounds[2],bounds[3]);
	glVertex2i(bounds[2],bounds[1]);
	glEnd();

	glVertex3f(0,0,0);
	glBegin(GL_LINE_LOOP);
	glVertex2i(bounds[0],bounds[1]);
	glVertex2i(bounds[0],bounds[3]);
	glVertex2i(bounds[2],bounds[3]);
	glVertex2i(bounds[2],bounds[1]);
	glEnd();

	int i = GetValue();
	if (i >= 0 && i < mItems.size())
	{		
		float c[4] = { 0,0,0,1 };
		float w = GUI_MeasureRange(font_UI_Basic, &*mItems[i].begin(), &*mItems[i].end());
		GUI_FontDraw(state,font_UI_Basic, c, (bounds[0]+bounds[2]-w) /2, bounds[1], mItems[i].c_str());
	}
}

int			GUI_PopupButton::MouseDown(int x, int y, int button)
{
	vector<GUI_MenuItem_t>	items;
	
	items.resize(mItems.size()+1);
	for (int n = 0; n < mItems.size(); ++n)
	{
		items[n].name = mItems[n].c_str();
		items[n].key = 0;
		items[n].flags = 0;
		items[n].cmd = 0;
		items[n].checked = 0;
	}	

	items.back().name = NULL;
	items.back().key = 0;
	items.back().flags = 0;
	items.back().cmd = 0;
	items.back().checked = 0;

	int bounds[4];
	GetBounds(bounds);

	int picked = PopupMenuDynamic(&*items.begin(), bounds[0], bounds[3], GetValue());
	if (picked >= 0)
	{
		SetValue(picked);
		BroadcastMessage(GUI_CONTROL_VALUE_CHANGED,0);
	}
	return 1;
}

void		GUI_PopupButton::MouseDrag(int x, int y, int button)
{
}

void		GUI_PopupButton::MouseUp  (int x, int y, int button)
{
}

void		GUI_PopupButton::SetValue(float inValue)
{
	GUI_Control::SetValue(inValue);
	Refresh();
}
	
