#pragma once
#ifndef _DP_H_
#define _DP_H_

#include "GUA_OM.h"
#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>

#define MAX_LAYERS 10

class DP_COM
{

public:
	float*	   m_pZBuffer      ;    //儲存每一階層的ZBuffer值       
	unsigned int*     m_ValidBuffer ;    //此Pixel是否存在mesh的判斷buffer，判斷加速用

	//---------------function---------------//
	bool Scene_Init( );
	void Set_BufferObj(  int, int  );
	void ClearBuffer( );
	void Peeling_layer(  int, int, int,  Tri_Mesh*, double *xf  ) ;
	void Set_ValidRegion(int, int );

protected:
private:

};


#endif