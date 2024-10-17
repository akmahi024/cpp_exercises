constexpr int cube(const int n){
    return n*n*n;
}
void test_cube(){
    constexpr int result1=cube(2);
    constexpr int result2=cube(3);
}

int main(){
    test_cube();
    return 0;
}
