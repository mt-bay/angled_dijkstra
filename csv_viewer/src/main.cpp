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
    int background_color = 0x282828;
    SetBackgroundColor((background_color & 0xff0000) >> (4 * 4),
                       (background_color & 0x00ff00) >> (2 * 4),
                       (background_color & 0x0000ff) >> (0 * 4));
    //init
    error_code = DxLib_Init();
    if(error_code == -1)
    {
        return -1;
    }
    //setting after init
    
    //body of process
    sys::t_graph graph = sys::t_graph("..\\bin\\location.csv", "..\\bin\\adj.csv");

    graph.show_mesh_grid(0x878787);
    graph.show_line(0xff0000);
    graph.show_point(0x00ff00);
    
    error_code = SaveDrawScreen
                    (0, 0, window_size.x - 1, window_size.y - 1,
                     _T("result.bmp"));
    if(error_code == -1)
    {
        ErrorLogAdd(_T("bmp output error"));
    }

    while(ProcessMessage() != -1)
    {

    }

    //WaitKey();
    //end
#ifdef _DEBUG
    DxLib_End();
#endif
    return 0;
}