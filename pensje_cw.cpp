#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>



using namespace std;

#define MAX_N 1000001

int num;
int parent[MAX_N];
int salary[MAX_N];
bool used_salary[MAX_N] {false};
bool nie_j[MAX_N];
vector<int> sons[MAX_N];

struct subtree_t{
    int parent;
    int size;
    int upper_limit;
    subtree_t(int p, int u): parent(p), upper_limit(u) {;};
    bool operator<(const subtree_t &other){
        return this->upper_limit < other.upper_limit;
    }
};

int find_size(int n){
    int size = 1;
    for(int i = 0; i < sons[n].size(); ++i){
        size += find_size(sons[n][i]);
    }
    return size;
}
void set_salaries(int parent, vector<int> &M){
    salary[parent] = M.back();
    M.pop_back();
    if(sons[parent].size() == 1){
        set_salaries(sons[parent].back(),M);
    }
}

int main(){
    cin >> num;
    for(int i = 1; i < num + 1; ++i){
        cin >> parent[i];
        cin >> salary[i];
        if(parent[i] == i){
            parent[i] = 0 ;
            salary[i] = num;
        }
    }    
    for(int i = 1; i < num + 1; ++i){
        if(salary[i]){
            used_salary[salary[i]] = true;
        }
    }
    queue<int> K,P;

    for(int i = 1; i < num + 1; ++i){
        if(!used_salary[i]){
            K.push(i);
            P.push(i);
        }
    }
    vector<subtree_t> subtrees;
    for(int i = 1; i < num + 1; ++i){
        if(salary[i] == 0 && salary[parent[i]] != 0){
            subtrees.push_back(subtree_t(i,salary[parent[i]]));
        }else if(salary[i] == 0 && salary[parent[i]] == 0){
            sons[parent[i]].push_back(i);
        }
    }
    sort(subtrees.begin(), subtrees.end());
    for(int i = 0; i < subtrees.size(); ++i){
        subtrees[i].size = find_size(subtrees[i].parent);
        vector<int> M;
        while(!K.empty() && K.front() < subtrees[i].upper_limit && M.size() < subtrees[i].size){
            M.push_back(K.front());
            K.pop();
        }
        bool niej = false;
        if(K.empty() || K.front() > subtrees[i].upper_limit){
            set_salaries(subtrees[i].parent,M);
        }else{
            niej = true;
        }
        while(!P.empty() && P.front() < subtrees[i].upper_limit ){
            if(niej){
                nie_j[P.front()] = true;
            }
            P.pop();
        }
    }
    for(int i = 1; i < num + 1; ++i){
        if(salary[i] != 0 && !nie_j[salary[i]]){
            cout << salary[i] << '\n';
        }else{
            cout << "0\n";
        }
    }    

}
