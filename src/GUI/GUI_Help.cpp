/* 
 * Copyright (c) 2007, Laminar Research.
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

#include "GUI_Help.h"
#if APL
	#include <Carbon/Carbon.h>
#endif

void	GUI_LaunchURL(const char * url)
{
	#if APL
		ICInstance inst;						
		OSStatus err=ICStart(&inst,0x3F3F3F3F);	// Use your creator code if you have one!
		if(err==noErr){
			long startSel	=0			;
			long endSel		=strlen(url);
			err=ICLaunchURL(inst,"\p",url,endSel,&startSel,&endSel);
			(void)ICStop(inst);}
	#endif
	#if IBM
		ShellExecute(NULL,"open",url,NULL,NULL,SW_SHOWNORMAL);
	#endif
	#if LIN
		#error not impl
	#endif
}