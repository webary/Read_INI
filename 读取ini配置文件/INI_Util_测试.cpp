#include "INI_Util.hpp"
#include <ctime>

int main() {
    int start = clock();
    INI_Util ini("set.ini");
    cout<<"���������󲢶�ȡ�����ļ���ʱ��"<<clock()-start<<endl;

    ini.setDefaultNode("MyCNN");
    for(int i=0; i<10000; ++i) {	//Windows ��40ms
        string find = ini.getRecord("key_name");
        ini.getRecord(find);
        //cout<<find<<" = "<<ini.getRecord(find)<<endl;
        //cout<<ini.getState();
    }
    cout<<"ִ��2W�β��Һ�ʱ��"<<clock()-start<<endl;

    cout<<"\n�����ļ�������������"<<endl;
    ini.showAllRecord();
    cin.get();
    return 0;
}
