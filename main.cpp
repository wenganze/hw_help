#include <iostream>
#include <vector>
#include <sstream>
#include <string>

using namespace std;

int n,step;
vector<int> tower[3];                           //三個塔

bool run(int plate,int position,int target);    //判斷方程


int main(int argc,char* argv[]){
    cout<<"Enter the number od disks:";
    cin >> n;                                   //input有幾個碟子
    string discard;
    getline(cin,discard);                       //把\n讀掉
    bool exe = true;
    while(exe)                                  //輸入不正確再while一次
    {
        vector<int> input;                      //預先用來存input轉int的空間
        string line;
        getline(cin,line);                      //讀一行
        istringstream iss(line);
        string word;
        while (getline(iss,word,' '))input.push_back(stoi(word));  //把讀進來的東西以空格分開轉int存進input
        if(input.size() % 3 != 0){                                 //判斷全不是不是剛好有3n個數做n次動作
            cout <<"input error\n";
            continue;
        }
        for(int i =0;i < 3;i++)tower[i].clear();                   
        for(int i = n;i > 0;i--)tower[0].push_back(i);             //格式化tower
        step = 0;                                                  //動作次數歸0
        exe = false;
        for(int i = 0;i < input.size()/3;i++){
            if(run(input[i*3],input[i*3+1]-1,input[i*3+2]-1)){     //判斷有沒有符合條件
                exe = true;
                break;
            }
        }
        if(!tower[0].empty() || !tower[1].empty())exe = true;      //判斷是不是只有第三個塔上有元素

        if(exe)cout <<"input error\n";
        else{
            for(int i = 0;i < input.size()/3;i++){
            cout << "Plate " << input[i*3] << " move from tower " << input[i*3+1] << " to tower " << input[i*3+2] << "\n";  //輸出所做的動作
            }
            cout << "Total moves: " << step << "\n\n";      //輸出總動作次數
            cout << "win\n";
        }
        
    }
        
}

bool run(int plate,int position,int target){
    if(plate < 1 || plate > n || position < 0 || position > 3 || target < 0 || target > 3)return true;      //判斷有沒有超出範圍
    if(tower[position].empty()) return true;               
    if(tower[position].back() != plate)return true;      //判斷元素是不是有沒有在要移動的塔的最上層，沒有就移不了(先判斷塔裡面有沒有元素)
    if(!tower[target].empty()){                          
        if(plate > tower[target].back())return true;     //判斷要移到的塔的最上面的元素有沒有比現在要移去的小(先判斷那個塔是不是空的)
    }
    tower[position].pop_back();                          //刪除原本塔中的那個元素
    tower[target].push_back(plate);                      //在要移去的塔增新那個元素
    step++;                                              //步驟+1
    return false;
}

