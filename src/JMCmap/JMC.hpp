#ifndef SRC_JMCMAP_JMC_HPP
#define SRC_JMCMAP_JMC_HPP

#include <iostream>
#include <string>


namespace cd
{
class t_graph;
}


namespace jmc
{

class t_jmc
{
    /* constructor and destractor */
public    :
protected :
private   :

    /* operator overload */
public    :
protected :
private   :

    /* static method */
public    :
    /* 
     * jmc data files to graph
     * parameter    : jmc data file directory
     * return value : generated graph
     * exception    : none
     */
    static cd::t_graph jmc_to_graph(std::string _jmc_data_dir);

protected :
private   :
    /* 
     * check layer header record
     * parameter    : header record
     * return value : 
     * exception    : 
     */



    /* method */
public    :
protected :
private   :


    /* member const value and instance */
public    :
protected :
private   :


    /* static variable and instance */
public    :
protected :
private   :


    /* member variable and instance */
public    :
protected :
private   :


};

}

#endif //!SRC_JMCMAP_JMC_HPP
