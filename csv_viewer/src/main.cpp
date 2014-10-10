#include "system/graph.hpp"

#include "DxLib.h"


/* setting , init and end DxLib */
int WINAPI WinMain(HINSTANCE hInstance    ,
                   HINSTANCE hPrevInstance,
                   LPSTR     lpCmdLine    ,
                   int       nCmdShow     )
{
    int error_code;
    //setting before init

    //init
    error_code = DxLib_Init();
    if(error_code == -1)
    {
        return -1;
    }
    //setting after init
    
    //body of process
    sys::t_graph hoge = sys::t_graph();
    //end
#ifndef _DEBUG
    DxLib_End();
#endif
    return 0;
}