#include <iostream>
#include <chrono>

template<typename ...T>
void dynamic_add(T... args)
{
    auto r = 0;
    for (int i : std::initializer_list<int>{args...}){
        r += i;
    }
    std::cout << "r:\t" << r << std::endl;
}

template <typename T>
T fused_multiply_add(T a, T b, T c){
    T r = a * b + c;
    return r;
}

int normal_multiply_add(int a, int b, int c){
    int r = a * b + c;
    return r;
}


int main(){

    // int で実体化
    std::cout << fused_multiply_add<int>(1,2,3) << std::endl;

    // 可変引数
    dynamic_add(1,2,3,4,5);
    dynamic_add(100,200,300);

    auto start = std::chrono::system_clock::now();      // 計測スタート時刻を保存
    // ここに計測したい処理を格納
    for (int i = 0; i < 100000; ++i){
        std::cout << fused_multiply_add<int>(i,2,3) << std::endl;   // 関数テンプレート
        std::cout << normal_multiply_add(i,2,3) << std::endl;   // 通常の関数
    }

    auto end = std::chrono::system_clock::now();       // 計測終了時刻を保存
    auto dur = end - start;        // 要した時間を計算
    auto msec = std::chrono::duration_cast<std::chrono::milliseconds>(dur).count();
    // 要した時間をミリ秒（1/1000秒）に変換して表示
    std::cout << msec << " milli sec \n";

}
