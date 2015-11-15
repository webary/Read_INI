#include "INI_Util.hpp"
#include <ctime>  //clock()

int main() {
    int t_start = clock();
    INI_Util ini("set.ini");  //构造一个读取ini文件的对象，打开名为“set.ini”的配置文件
    cout<<"构造该类对象并读取配置文件耗时："<<clock()-t_start<<endl;

    ini.setDefaultNode("MyCNN");  //设置默认搜索结点
    for(int i=0; i<10000; ++i) {
        string find = ini.getRecord("key_name"); //获取该记录
        ini.getRecord(find);
        //cout<<find<<" = "<<ini.getRecord(find)<<endl;
        //cout<<ini.getState();
    }
    cout<<"执行2W次查找耗时："<<clock()-t_start<<endl;

    cout<<"\n配置文件所有内容如下"<<endl;
    ini.showAllRecord();  //显示所有记录
    cin.get();
    return 0;
}
