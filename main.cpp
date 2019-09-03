#include <iostream>
#include <vector>
using namespace std;

vector<int> read();

int main() {

    vector<int> data = read();
    
    return 0;
}

vector<int> read(){
    int N;
    vector<int> data;
    cin>>N;
    int s;

    for(int i=0; i< N*3;i++){
        cin >> s;
        data.push_back(s);
    }
    return data;
}

