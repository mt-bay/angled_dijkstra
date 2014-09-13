#include <iostream>
#include <fstream>
#include <string>


namespace io
{

/* logger class */
class t_log
{
    /* member variable and instance */
public   :
private  :
    static t_log*  m_instance;
    std::ofstream* m_writer;
    const std::string m_s_file_path = "log.txt";

    /* constractor and destractor */
public   :
    /* 
     * destractor
     */
    ~t_log();

private  :
    /* 
     * default constractor
     * parameter : void
     * built     : log file
     * exception : none
     */
     t_log();

    /* 
     * copy constractor
     * parameter : origin
     * built     : copy
     * exception : none
     */
     t_log(const t_log& _origin);

    /* method */
public   :
    /* 
     * add contents
     * parameter    : contents
     * return value : void
     * exception    : void
     */
    void write(const std::string _contents);

    /* 
     * add line
     * parameter    : contents
     * return value : void
     * exception    : none
     */
    void write_line(const std::string _contents);

    /* 
     * get instance
     * parameter    : void
     * return value : log file instance
     * exception    : none
     */
    static t_log& get_instance();

private:
    /* 
     * delete instance
     * parameter    : void
     * return value : void
     * exception    : none
     */
    static void del_instance();
};
}