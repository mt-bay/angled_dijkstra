#include "log/log.hpp"

#include <string>

int main(int argc, char** argv)
{
    const int L_ARGC_MIN = 4;

    if(argc < L_ARGC_MIN)
    {
        io::t_log::get_instance().write_line
            ("[this program] [target line item recode] [target line classification recode] [dij result p_graph] [origin JMC file(s)]...");

        return -1;
    }
    int l_target_line_item_recode;
    int l_target_line_classification_recode;
    {
        int index = -1;
        
        l_target_line_item_recode           = std::stoi(argv[++index]);
        l_target_line_classification_recode = std::stoi(argv[++index]);
        
    }
    return 0;
}