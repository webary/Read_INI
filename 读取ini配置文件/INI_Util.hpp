/**
	��ȡ�����ļ���
    @Author: �Ų�(webary)
**/
#pragma once
#ifndef  _INI_Util_HPP_
#define  _INI_Util_HPP_
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
using namespace std;

class INI_Util {
    typedef struct {
        string key;		//�ؼ���
        string value;	//��ֵ
    } Record;
    typedef struct {
        string node;		//�ڵ���
        vector<Record> set;	//��¼����
    } Group;
    vector<Group> conf;

    string defaultNode;	//Ĭ�ϲ��ҽڵ�
    string state;		//����״̬,����ʧ���Ǵ洢ʧ��ԭ��
	string lastFileName;//��һ��������ļ���

public:
#define For_each(it,vec) for(auto it=vec.begin();it<vec.end();++it)

    INI_Util(const string iniFileName="",const string defaultNode="") {
        state = lastFileName = "";
        setDefaultNode(defaultNode);
        if(iniFileName!="")
			loadINI(iniFileName);
    }

    void loadINI(const string iniFileName="");

    string getRecord(const string &key,const string node = "");

    void showAllRecord();

    string getState()const {
        return state;
    }

    void setDefaultNode(const string &node) {
        defaultNode = node;
    }

    const string& getDefaultNode()const {
        return defaultNode;
    }

	const string& getLastFileName()const {
		return lastFileName;
	}
private:
    //ȥ����β�Ŀո��\t
    const static string& trim(string &s) {
        if(s.empty())
            return s;
        s.erase(0,s.find_first_not_of(" \t"));
        s.erase(s.find_last_not_of(" \t") + 1);
        return s;
    }
};

void INI_Util::loadINI(const string iniFileName) {
	if(iniFileName!="")
		lastFileName = iniFileName;
	if(lastFileName=="")
		return;
    ifstream readINI(lastFileName.c_str());
    if(readINI.is_open()) {
        //�����ǰ����Ϣ
        For_each(it,conf)
        	it->set.clear();
        conf.clear();
        string line;
        string::size_type pos;
        string tmpNode = "";
        while(getline(readINI,line)) {
            trim(line);
            if(line=="")
				continue;
            if(line[0]=='[' && line[line.length()-1]==']') {
                tmpNode = line.substr(1,line.length()-2);
                continue;
            }
            pos = line.find('=');
            if(pos==line.npos)
                continue;
            string tmpKey = line.substr(0,pos);
            string tmpValue = line.substr(pos+1);
            trim(tmpNode);
            trim(tmpKey);
			trim(tmpValue);
			Record record = {tmpKey,tmpValue};
			Group group = {tmpNode,vector<Record>()};
            bool found = false;
            For_each(it,conf) {
                if(it->node == tmpNode) {
                    it->set.push_back(record);
                    found = true;
                    break;
                }
            }
			//��ǰ����û�д洢����
            if(!found) {
                conf.push_back(group);
                conf.rbegin()->set.push_back(record);
            }
        }
        readINI.close();
    }
}

string INI_Util::getRecord(const string &key,const string node) {
    if(key=="") {
        state = "key is invalid!";
        return "";
    }
    string findNode = node;
    if(node=="")
        findNode = defaultNode;
    state = "Node '"+findNode+"' not found!";
    For_each(it,conf) {
        if(it->node==findNode) {
            state = "key '"+key+"' not found!";
            For_each(it2,it->set) {
                if(it2->key==key) {
                    state = "key '"+key+"' find out!";
                    return it2->value;
                }
            }
            break;
        }
    }
    return "";
}

void INI_Util::showAllRecord() {
    For_each(it,conf) {
    	cout<<"["<<it->node<<"]"<<endl;
		For_each(it2,it->set)
			cout<<it2->key<<" = "<<it2->value<<endl;
    	cout<<endl;
    }
}

#endif // _INI_Util_HPP_
