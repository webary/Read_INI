/**
    A class to read and parse .ini config file by stl::map
    @Author: 闻波(webary)
**/
#ifndef  _INI_Util_HPP_
#define  _INI_Util_HPP_

#include <string>
#include <map>
#include <fstream>
#include <iostream>

using std::string;
using std::map;
using std::ifstream;
using std::cout;
using std::endl;

class INI_Util
{
    map<string, map<string, string> >_conf;

    string _default_node;  //默认查找节点
    string _state;         //搜索状态,查找失败是存储失败原因
    string _last_file_name;//上一次载入的文件名

public:
    INI_Util(const string &ini_file_name = "", const string default_node = "")
    {
        _state = _last_file_name = "";
        set_default_node(default_node);
        if (ini_file_name != "")
            load_ini(ini_file_name);
    }

    void load_ini(const string ini_file_name = "")
    {
        if (ini_file_name != "")
            _last_file_name = ini_file_name;
        if (_last_file_name == "")
            return;
        ifstream readINI(_last_file_name.c_str());
        if (readINI.is_open())
        {
            //清除以前的信息
            _conf.clear();
            string line;
            string::size_type pos;
            string tmp_node = "";
            while (getline(readINI, line))
            {
                trim(line);
                if (line.length() < 3)
                    continue;
                if (line[0] == '[' && line[line.length() - 1] == ']')
                {
                    tmp_node = line.substr(1, line.length() - 2);
                    continue;
                }
                pos = line.find('=');
                if (pos == line.npos)
                    continue;
                string tmp_key = line.substr(0, pos);
                string tmp_value = line.substr(pos + 1);
                trim(tmp_node);
                trim(tmp_key);
                trim(tmp_value);
                _conf[tmp_node][tmp_key] = tmp_value;
            }
            readINI.close();
        }
    }

    const string get_record(const string &key, const string node = "")
    {
        if (key == "")
        {
            _state = "key is invalid!";
            return "";
        }
        string find_node = node;
        if (node == "")
            find_node = _default_node;
        if (_conf.find(find_node) != _conf.end())
        {
            if (_conf[find_node].find(key) != _conf[find_node].end())
            {
                _state = "key '" + key + "' find out!";
                return _conf[find_node][key];
            }
            else
            {
                _state = "key '" + key + "' not found!";
            }
        }
        else
        {
            _state = "Node '" + find_node + "' not found!";
        }
        return "";
    }

    void show_all_record()
    {
        for (auto &it : _conf)
        {
            cout << "[" << it.first << "]" << endl;
            for (auto &it2 : it.second)
                cout << it2.first << " = " << it2.second << endl;
            cout << endl;
        }
    }

    const string get_state()const
    {
        return _state;
    }

    void set_default_node(const string &node)
    {
        _default_node = node;
    }

    const string &get_default_node()const
    {
        return _default_node;
    }

    const string &get_last_file_name()const
    {
        return _last_file_name;
    }
private:
    //去除首尾的空格和\t
    const static string &trim(string &s)
    {
        if (s.empty())
            return s;
        s.erase(0, s.find_first_not_of(" \t"));
        s.erase(s.find_last_not_of(" \t") + 1);
        return s;
    }
};

#endif // _INI_Util_HPP_
