/**
    A class to read and parse .ini config file by stl::vector
    @Author: �Ų�(webary)
**/
#ifndef  _INI_Util_VECTOR_HPP_
#define  _INI_Util_VECTOR_HPP_

#include <string>
#include <vector>
#include <fstream>
#include <iostream>

using std::string;
using std::vector;
using std::ifstream;
using std::cout;
using std::endl;

class INI_Util_Vector
{
    typedef struct
    {
        string key;     //�ؼ���
        string value;   //��ֵ
    } Record;
    typedef struct
    {
        string node;        //�ڵ���
        vector<Record> set; //��¼����
    } Group;
    vector<Group> conf;

    string defaultNode; //Ĭ�ϲ��ҽڵ�
    string state;       //����״̬,����ʧ���Ǵ洢ʧ��ԭ��
    string lastFileName;//��һ��������ļ���

public:
    INI_Util_Vector(const string iniFileName = "", const string _defaultNode = "")
    {
        state = lastFileName = "";
        setDefaultNode(_defaultNode);
        if (iniFileName != "")
            loadINI(iniFileName);
    }

    void loadINI(const string iniFileName = "")
    {
        if (iniFileName != "")
            lastFileName = iniFileName;
        if (lastFileName == "")
            return;
        ifstream readINI(lastFileName.c_str());
        if (readINI.is_open())
        {
            //�����ǰ����Ϣ
            for (auto &it : conf)
                it.set.clear();
            conf.clear();
            string line;
            string::size_type pos;
            string tmpNode = "";
            while (getline(readINI, line))
            {
                trim(line);
                if (line == "")
                    continue;
                if (line[0] == '[' && line[line.length() - 1] == ']')
                {
                    tmpNode = line.substr(1, line.length() - 2);
                    continue;
                }
                pos = line.find('=');
                if (pos == line.npos)
                    continue;
                string tmpKey = line.substr(0, pos);
                string tmpValue = line.substr(pos + 1);
                trim(tmpNode);
                trim(tmpKey);
                trim(tmpValue);
                Record record = {tmpKey, tmpValue};
                Group group = {tmpNode, vector<Record>()};
                bool found = false;
                for (auto &it : conf)
                {
                    if (it.node == tmpNode)
                    {
                        it.set.push_back(record);
                        found = true;
                        break;
                    }
                }
                //��ǰ����û�д洢����
                if (!found)
                {
                    conf.push_back(group);
                    conf.rbegin()->set.push_back(record);
                }
            }
            readINI.close();
        }
    }

    const string getRecord(const string &key, const string node = "")
    {
        if (key == "")
        {
            state = "key is invalid!";
            return "";
        }
        string findNode = node;
        if (node == "")
            findNode = defaultNode;
        state = "Node '" + findNode + "' not found!";
        for (auto &it : conf)
        {
            if (it.node == findNode)
            {
                state = "key '" + key + "' not found!";
                for (auto &it2 : it.set)
                {
                    if (it2.key == key)
                    {
                        state = "key '" + key + "' find out!";
                        return it2.value;
                    }
                }
                break;
            }
        }
        return "";
    }

    void showAllRecord()
    {
        for (auto &it : conf)
        {
            cout << "[" << it.node << "]" << endl;
            for (auto &it2 : it.set)
                cout << it2.key << " = " << it2.value << endl;
            cout << endl;
        }
    }

    const string getState()const
    {
        return state;
    }

    void setDefaultNode(const string &node)
    {
        defaultNode = node;
    }

    const string &getDefaultNode()const
    {
        return defaultNode;
    }

    const string &getLastFileName()const
    {
        return lastFileName;
    }
private:
    //ȥ����β�Ŀո��\t
    const static string &trim(string &s)
    {
        if (s.empty())
            return s;
        s.erase(0, s.find_first_not_of(" \t"));
        s.erase(s.find_last_not_of(" \t") + 1);
        return s;
    }
};

#endif // _INI_Util_VECTOR_HPP_
