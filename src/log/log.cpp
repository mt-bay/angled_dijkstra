#include "log.hpp"

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
    m_writer = new std::ofstream(m_s_file_path);
    std::atexit(io::t_log::del_instance);
}

t_log::t_log(const t_log& _origin)
{
    //nothing to do
}

void t_log::write(const std::string _contents)
{
    *m_writer << _contents << std::flush;

    return;
}

void t_log::write_line(const std::string _contents)
{
    *m_writer << _contents << std::endl;

    return;
}


t_log& t_log::get_instance()
{
    if(m_instance == nullptr)
    {
        m_instance = new t_log();
    }

    return *m_instance;
}

void t_log::del_instance()
{
    if(m_instance != nullptr)
    {
        delete m_instance;
    }

    return;
}


}