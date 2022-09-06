#include <iostream>
#include <stack> 





int solution(int n, int *height){
    int result = 0;
    std :: stack<int> stack;
    for(int i = 0; i < n; ++i){
        while(!stack.empty() && stack.top()  > height[i]){
            stack.pop();
        }
        if(stack.empty() || stack.top() < height[i]){
            stack.push(height[i]);
            result++;
        }
    }
    return result;
}

int main(){
    int num_of_bul;
    int *height;
    int width;
    std :: cin >> num_of_bul;
    height = new int [num_of_bul];
    for(int i = 0; i < num_of_bul; ++i){
        std :: cin >> width;
        std :: cin >> height[i];
    }
    std :: cout << solution(num_of_bul,height);
}