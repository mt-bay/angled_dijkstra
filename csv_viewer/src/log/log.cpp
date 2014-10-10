#include "log.hpp"

#include <iostream>
#include <fstream>

namespace io
{
t_log::~t_log()
{
    m_writer->close();
    delete m_writer;
}

t_log::t_log()
{
    m_writer = new std::ofstream(C_FILE_PATH);
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
    std::cout << _contents <<std::flush;
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