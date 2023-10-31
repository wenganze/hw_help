#include <iostream>
#include <vector>
#include <sstream>
#include <string>

using namespace std;

int n,step;
vector<int> tower[3];//三個塔

bool run(int plate,int position,int target);


int main(int argc,char* argv[]){
    cout<<"Enter the number od disks:";
    cin >> n;
    string discard;
    getline(cin,discard);
    bool exe = true;
    while(exe)
    {
        vector<int> input;
        string line;
        getline(cin,line);
        istringstream iss(line);
        string word;
        while (getline(iss,word,' '))input.push_back(stoi(word));
        if(input.size() % 3 != 0){
            cout <<"input error\n";
            continue;
        }
        for(int i =0;i < 3;i++)tower[i].clear();
        for(int i = n;i > 0;i--)tower[0].push_back(i);
        step = 0;
        exe = false;
        for(int i = 0;i < input.size()/3;i++){
            if(run(input[i*3],input[i*3+1]-1,input[i*3+2]-1)){
                exe = true;
                break;
            }
        }
        if(!tower[0].empty() || !tower[1].empty())exe = true;

        if(exe)cout <<"input error\n";
        else{
            for(int i = 0;i < input.size()/3;i++){
            cout << "Plate " << input[i*3] << " move from tower " << input[i*3+1] << " to tower " << input[i*3+2] << "\n";
            }
            cout << "Total moves: " << step << "\n\n";
            cout << "win\n";
        }
        
    }
        
}

bool run(int plate,int position,int target){
    if(plate < 1 || plate > n || position < 0 || position > 3 || target < 0 || target > 3)return true;
    if(tower[position].empty()) return true;
    if(tower[position].back() != plate)return true;
    if(!tower[target].empty()){
        if(plate > tower[target].back())return true;
    }
    tower[position].pop_back();
    tower[target].push_back(plate);
    step++;
    return false;
}

