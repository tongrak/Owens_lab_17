#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstring>
#include<cstdlib>

using namespace std;

char score2grade(int score){
    if(score >= 80) return 'A';
    if(score >= 70) return 'B';
    if(score >= 60) return 'C';
    if(score >= 50) return 'D';
    else return 'F';
}

string toUpperStr(string x){
    string y = x;
    for(unsigned i = 0; i < x.size();i++) y[i] = toupper(x[i]);
    return y;
}

void importDataFromFile(string file, vector<string> &name, vector<int> &score, vector<char> &letter){
    ifstream read;
    read.open(file.c_str());
    int a, b, c;
    string holder;
    char name_hold[100];
    char form[]="%[^:]: %d %d %d";
    while(getline(read, holder)){
        sscanf(holder.c_str(),form,name_hold,&a,&b,&c);
        name.push_back(name_hold);
        score.push_back(a+b+c);
        letter.push_back(score2grade(a+b+c));
    }
    read.close();
}

void getCommand(string &c1, string &key){
    string holder;
    cout<<"Please input your command: ";
    getline(cin, holder);
     int an=holder.find_first_of(" ");
    c1=holder.substr(0,an);
    key=holder.substr(an+1);
}

void searchName(vector<string> nam, vector<int> scr, vector<char> lett, string key){
    cout<<"---------------------------------"<<endl;
    int posi;
    bool check=false;
    for(unsigned int i=0;i<nam.size();i++){
        if(toUpperStr(nam[i])==toUpperStr(key)){
            posi=i;
            check=true;
            cout<<nam.at(posi)<<"'s score = "<<scr.at(posi)<<endl<<nam.at(posi)<<"'s grade = "<<lett.at(posi)<<endl;
            break;
        }
    }
        
    if(!check){
        cout<<"Cannot found."<<endl;
    }
    cout<<"---------------------------------"<<endl;
    

}

void searchGrade(vector<string> nam, vector<int> scr, vector<char> lett, string key){
    cout<<"---------------------------------"<<endl;

    for(unsigned int i=0;i<nam.size();i++)
    {
        if(key[0]==lett[i]){
            cout<<nam[i]<<" ("<<scr[i]<<")"<<endl;
        }
    }
    

    cout<<"---------------------------------"<<endl;
}


int main(){
    string filename = "name_score.txt";
    vector<string> names;
    vector<int> scores;
    vector<char> grades; 
    importDataFromFile(filename, names, scores, grades);
    
    do{
        string command, key;
        getCommand(command,key);
        command = toUpperStr(command);
        key = toUpperStr(key);
        if(command == "EXIT") break;
        else if(command == "GRADE") searchGrade(names, scores, grades, key);
        else if(command == "NAME") searchName(names, scores, grades, key);
        else{
            cout << "---------------------------------\n";
            cout << "Invalid command.\n";
            cout << "---------------------------------\n";
        }
    }while(true);
    
    return 0;
}
