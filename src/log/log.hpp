#ifndef SRC_LOG_LOG_H
#define SRC_LOG_LOG_H


#include <iostream>
#include <fstream>
#include <string>


namespace io
{

/* logger class */
class t_log
{
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


    /* operator overload */
public    :
private   :
    t_log& operator= (const t_log& _rhs);


    /* method */
public   :
    /* 
     * get instance
     * parameter    : void
     * return value : log file instance
     * exception    : none
     */
    static t_log& get_instance();

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

private:


    /* member const value and instance */
public    :
private   :
    const std::string C_FILE_PATH = "log.txt";


    /* static variable and instance */
public    :
private   :
//    static t_log* m_instance;


    /* member variable and instance */
public    :
private   :
    std::ofstream* m_writer;

};
}


#endif //!LOG_LOG_H