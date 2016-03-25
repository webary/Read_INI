#include "INI_Util.hpp"
#include <ctime>  //clock()

int main()
{
    int t_start = clock();
    INI_Util ini("set.ini");  //open a ini config file named "set.ini"
    cout << "time of construct object and read config file: "
         << clock() - t_start << " ms" << endl;
    ini.setDefaultNode("MyCNN");  //set default search node
    for(int i = 0; i < 10000; ++i) {
        string find = ini.getRecord("key_name"); //get the record
        ini.getRecord(find);
        //cout<<find<<" = "<<ini.getRecord(find)<<endl;
        //cout<<ini.getState();
    }
    cout << "time of searching 2W times: " << clock() - t_start << " ms" << endl;
    cout << "\nall content of the config file is:" << endl;
    ini.showAllRecord();  //show all the record of the config file
    cin.get();
    return 0;
}
