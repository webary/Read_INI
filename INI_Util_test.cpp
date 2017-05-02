#include <ctime>  //clock()

#include "INI_Util_Vector.hpp"
#include "INI_Util.hpp"


using namespace std;

int test_ini_util_vector()
{
    int t_start = clock();
    INI_Util_Vector ini("set.ini");  //open ini config file "set.ini"
    cout << "time of construct object and read config file: "
         << clock() - t_start << " ms" << endl;
    ini.setDefaultNode("MyCNN");  //set default search node
    for (int i = 0; i < 500000; ++i)
    {
        string find_str = ini.getRecord("key_name"); //get the record
        ini.getRecord(find_str);
        //cout<<find_str<<" = "<<ini.getRecord(find_str)<<endl;
        //cout<<ini.getState();
    }
    cout << "time of searching 10W times: " << clock() - t_start << " ms" << endl;
    cout << "\nall content of the config file is:" << endl;
    ini.showAllRecord();  //show all the record of the config file
    cin.get();
    return 0;
}

int test_ini_util_map()
{
    int t_start = clock();
    INI_Util ini("set.ini");  //open ini config file "set.ini"
    cout << "time of construct object and read config file: "
         << clock() - t_start << " ms" << endl;
    ini.set_default_node("MyCNN");  //set default search node
    for (int i = 0; i < 500000; ++i)
    {
        string find_str = ini.get_record("key_name"); //get the record
        ini.get_record(find_str);
        //cout<<find_str<<" = "<<ini.get_record(find_str)<<endl;
        //cout<<ini.get_state();
    }
    cout << "time of searching 10W times: " << clock() - t_start << " ms" << endl;
    cout << "\nall content of the config file is:" << endl;
    ini.show_all_record();  //show all the record of the config file
    return 0;
}

int main()
{
    test_ini_util_map();
    test_ini_util_vector();
    cin.get();
    return 0;
}
