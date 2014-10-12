#include "define.hpp"
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
    ChangeWindowMode(TRUE);
    SetWindowSize(window_size.x, window_size.y);
    SetBackgroundColor(0xff, 0xff, 0xff);
    //init
    error_code = DxLib_Init();
    if(error_code == -1)
    {
        return -1;
    }
    //setting after init
    
    //body of process
    sys::t_graph graph = sys::t_graph("bin\\location.csv", "bin\\adj.csv");

    graph.show_mesh_grid(0x787878);
    graph.show_line(0x0000ff);
    //graph.show_point(0xff0000);
    
    WaitKey();
    //end
#ifdef _DEBUG
    DxLib_End();
#endif
    return 0;
}