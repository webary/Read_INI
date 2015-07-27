#include "INI_Util.hpp"
#include <ctime>

int main() {
    int start = clock();
    INI_Util ini("set.ini");
    cout<<"构造该类对象并读取配置文件耗时："<<clock()-start<<endl;

    ini.setDefaultNode("MyCNN");
    for(int i=0; i<10000; ++i) {	//Windows ：40ms
        string find = ini.getRecord("key_name");
        ini.getRecord(find);
        //cout<<find<<" = "<<ini.getRecord(find)<<endl;
        //cout<<ini.getState();
    }
    cout<<"执行2W次查找耗时："<<clock()-start<<endl;

    cout<<"\n配置文件所有内容如下"<<endl;
    ini.showAllRecord();
    cin.get();
    return 0;
}
