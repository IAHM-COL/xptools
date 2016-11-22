/*
* Copyright (c) 2012, Laminar Research.
*
* Permission is hereby granted, free of charge, to any person obtaining a
* copy of this software and associated documentation files (the "Software"),
* to deal in the Software without restriction, including without limitation
* the rights to use, copy, modify, merge, publish, distribute, sublicense,
* and/or sell copies of the Software, and to permit persons to whom the
* Software is furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
* THE SOFTWARE.
*
*/

#include "WED_HierarchyFilterBar.h"
#include "WED_PackageMgr.h"
#include "WED_Colors.h"
#include "GUI_Fonts.h"
#include "GUI_Resources.h"

WED_HierarchyFilterBar::WED_HierarchyFilterBar(
	GUI_Commander * cmdr,
	intptr_t in_msg,
	intptr_t in_param,
	const string & in_label,
	const string & in_def)
	:
	WED_FilterBar(cmdr, in_msg, in_param, in_label, in_def, false)
{
	this->AddListener(this);
}

void	WED_HierarchyFilterBar::GetCellContent(
	int							cell_x,
	int							cell_y,
	GUI_CellContent&			the_content)
{
	WED_FilterBar::GetCellContent(cell_x, cell_y, the_content);
	/* Filter Bar Table
	* 0        1
	* Lable | Text Field									1
	* Lable | Enum Dictionary (Build from PackageManager)	0
	*/
	//Cell 0,0 and 1,0
	if (cell_y == 1 || WED_FilterBar::GetHaveEnumDict() == false)
	{
		//if(cell_x == 0)
		//	the_content.text_val = mLabel;
		//else
		//	the_content.text_val = mText;
		//the_content.string_is_resource=0;
	}

	if (cell_y == 0 && WED_FilterBar::GetHaveEnumDict() == true)
	{
		//Label
		if (cell_x == 0)
		{
			the_content.text_val = "Choose Pack:";
		}
		//Enum
		if (cell_x == 1)
		{
			the_content.content_type = gui_Cell_Enum;
			the_content.int_val = GetEnumValue();

			//switch on the current int_val
			//Special cases for Local, Library, and All
			//Default for any other value
			int cur_val = WED_FilterBar::GetEnumValue();
			switch (cur_val)
			{
			case pack_Library: the_content.text_val = "Library"; break;
			case pack_Default: the_content.text_val = "Laminar Library"; break;
			default: gPackageMgr->GetNthPackageName(GetEnumValue(), the_content.text_val); break;
			}
			the_content.string_is_resource = 0;
		}
	}
}
