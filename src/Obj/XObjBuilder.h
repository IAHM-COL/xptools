/* 
 * Copyright (c) 2004, Laminar Research.
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
 
 #ifndef XOBJBUILDER_H
 #define XOBJBUILDER_H

#include <string>
using std::string;
 
struct	XObj8;
struct	XObjLOD8;
 
 class	XObjBuilder {
 public:
 
 	 XObjBuilder(XObj8 * inObj);
 	~XObjBuilder();
 	
	void	Finish(void);
	
 	void	BeginLOD(float inNear, float inFar);
 	void	EndLOD(void);
 	
	void	SetTexRepeatParams(float repeat_s, float repeat_t, float offset_s, float offset_t);
	
 	void	SetAttribute(int inAttribute);
 	void	SetAttribute1(int inAttribute, float v);
 	void	SetAttribute3(int inAttribute, float v[3]);
 	void	SetAttribute1Named(int inAttribute, float v, const char * str);
 	
 	// X Y Z nX ny nZ S T repeated 3 times
 	void	AccumTri(float inTri[24]);
 	
 	// X Y Z R G B repeated 2 times, RGB = 0-1
 	void	AccumLine(float inLine[12]);
 	
 	// X Y Z R G B
 	void	AccumLight(float inPoint[6]);
	void	AccumLightNamed(float xyz[3], const char * name);
	void	AccumLightCustom(float xyz[3], float params[9], const char * dataref);	
	void	AccumSmoke(int cmd, float xyz[3], float size);
 
	// tODO SMOKE PUFFS, SHOW HIDE ANIMS!
 
	void	AccumAnimBegin(void);
	void	AccumAnimEnd(void);
 	void	AccumTranslate(float xyz1[3], float xyz2[3], float v1, float v2, const char * ref); 	
 	void	AccumRotate(float axis[3], float r1, float r2, float v1, float v2, const char * ref);
	void	AccumShow(float v1, float v2, const char * ref);
	void	AccumHide(float v1, float v2, const char * ref);

	void	AccumTranslateBegin(const char * ref);
	void	AccumRotateBegin(float axis[3], const char * ref);
 	void	AccumTranslateKey(float v, float xyz[3]);
 	void	AccumRotateKey(float v, float a);
	void	AccumTranslateEnd(void);
	void	AccumRotateEnd(void);	
 
	// A few status checks
	inline string	IsHard(void) const		{ return hard;			}
	inline int		IsCockpit(void) const	{ return cockpit > -2;	}
 
 private:
 
 	void	AssureLOD(void);
 	void	SetDefaultState(void);
	void	SyncAttrs(void);
 
 	XObj8 *		obj;
 	XObjLOD8 *	lod;

 	string		hard;				string	o_hard;
 	int			flat;				int		o_flat;
 	int			two_sided;			int		o_two_sided;
 	float		no_blend;			float	o_no_blend;
 	int			cockpit;			int		o_cockpit;

 	float		offset;				float	o_offset;
	
	float		shiny;				float	o_shiny;
	float		diffuse[3];			float	o_diffuse[3];
	float		emission[3];		float	o_emission[3];
	
	float		tex_repeat_s;
	float		tex_repeat_t;
	float		tex_offset_s;
	float		tex_offset_t;
	
	string		layer_group;
	int			layer_group_offset;
	

};
 
 #endif