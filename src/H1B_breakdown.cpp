#include <iostream>
#include <string>
#include <fstream>
#include <string>
#include <map>
#include <unordered_map>
#include <utility>
#include<vector>
#include <set>
using namespace std;
struct comp
{
    template<typename T>
    bool operator()(const T& l, const T& r) const
    {
        if (l.second != r.second)
            return l.second > r.second;
        
        return l.first < r.first;
    }
};
void setPars(const string& parFile);
string filename, label;
int main(int argc, char* argv[]) {
    string parFile = argv[1];
    setPars(parFile);
    string line;
    int delim_pos; int string_num;
    string str;
    map<int,string> column;
    
    ifstream file(filename);
    if (file.is_open()){
        cout << "ok" << endl;
    }
    getline(file,line);
    for (string_num=0; (delim_pos = line.find(";")) != -1; string_num++){
        str = line.substr(0, delim_pos);
        column[string_num]=str;
        line.erase(0, delim_pos + 1);
    }
    //for (map<int,string>::iterator it = column.begin(); it != column.end(); it++) cout<< it->first <<"\t" << it->second << endl;
    int OCC_ind, STATUS_ind, STATE_ind;
    for (map<int,string>::iterator it = column.begin(); it != column.end(); it++) {
        if( it->second.find("SOC") != string::npos && it->second.find("NAME") != string::npos ) OCC_ind = it->first;
        if( it->second.find("STATUS") != string::npos ) STATUS_ind = it->first;
        if( (it->second.find("STATE") != string::npos && it->second.find("CASE") != string::npos) || (it->second.find("STATE") != string::npos && it->second.find("WORKSITE") != string::npos) ) STATE_ind = it->first;

    }
    int i=0;
    map<string,int>  keycount, allcount;
    map<string,int>  statekeycount, stateallcount;

    while ( getline(file,line) ){
        string feature1;
        for (string_num=0; (delim_pos = line.find(";")) != -1; string_num++){
            str = line.substr(0, delim_pos);
            if(string_num==STATUS_ind)   {feature1= str;}
            else if(string_num==OCC_ind ) {
                allcount[str]++;
                if( feature1 == "CERTIFIED" ) {keycount[str]++;}
            }
            else if(string_num==STATE_ind ) {
                stateallcount[str]++;
                if( feature1 == "CERTIFIED" ) {statekeycount[str]++;}
            }
            line.erase(0, delim_pos + 1);
        }
        i++;

    }
    int j=0;
    freopen ("output/top_10_occupations.txt","w",stdout);
    printf ("year %s\n",label.c_str());
    
    printf ("||%5s%-15s%5s||%5s%-10s%5s||%5s%-10s%3s\n", "","TOP_OCCUPATIONS;","", "","NUMBER_CERTIFIED_APPLICATIONS;","", "","PERCENTAGE;","");
    set<pair<string,int>, comp> set1(keycount.begin(), keycount.end());
    for (auto const &pair1: set1) {
        printf ("||%5s%-15s;\t%-10.1d;\t%-10.1f%3s\n", "",pair1.first.c_str(),pair1.second,double(pair1.second)/double(allcount[pair1.first])*100,"");
        if(j>10) break;
        j++;
    }
    
    j=0;
    freopen ("output/top_10_states.txt","w",stdout);
    printf ("year %s\n",label.c_str());
    printf ("||%3s%-10s%3s||%5s%-10s%5s||%5s%-10s%3s||\n", "","FormTOP_STATES;","", "","NUMBER_CERTIFIED_APPLICATIONS;","", "","PERCENTAGE;","");
    set<pair<string,int>, comp> set2(statekeycount.begin(), statekeycount.end());
    for (auto const &pair2: set2) {
        if(j!=0)
            printf ("||%6s%-10s%5s||%11s%-18.1d%11s||%5s%-10.1f%4s||\n", "",pair2.first.c_str(),"", "",pair2.second,"", "",double(pair2.second)/double(stateallcount[pair2.first])*100,"");
        if(j>11) break;
        j++;
    }
    return 0;
}
void setPars(const string& parFile) {
    ifstream file(parFile);
    string line;
    while (getline(file, line)){
        if (line.length() > 0){
            while (line.at(0) == ' ') line.erase(0, 1);
        }
        int delim_pos = line.find(' ');
        if (delim_pos == -1) continue;
        
        string var = line.substr(0, delim_pos);
        line.erase(0, delim_pos + 1);
        while (line.at(0) == ' ') line.erase(0, 1);
        while (line.at(line.length()-1) == ' ') line.erase(line.length()-1, line.length());
        if (var == "filename")   filename = line.data();
        else if (var == "label") label = line.data();
    }
    file.close();
}


