#include <direct.h>

#include <ctime>
#include <iostream>
#include <fstream>

#include "log.hpp"

#include "../tools/tools.hpp"

namespace io
{
t_log::~t_log()
{
    m_writer->close();
    delete m_writer;
}

t_log::t_log()
{
    mt::mkdir(M_FILE_PATH);
    m_writer = new std::ofstream(M_FILE_PATH, std::ios::trunc);
}

t_log::t_log(const t_log& _origin)
{
    //nothing to do
}


t_log& t_log::operator= (const t_log& _rhs)
{
    return get_instance();
}


void t_log::write(const std::string _contents)
{
    std::cout << _contents << std::flush;
    *m_writer << _contents << std::flush;

    return;
}

void t_log::write_line(const std::string _contents)
{
    std::cout << _contents << std::endl;
    *m_writer << _contents << std::endl;

    return;
}


t_log& t_log::get_instance()
{
    static t_log m_s_instance;
    return m_s_instance;
}

}