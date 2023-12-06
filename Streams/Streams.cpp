#include <iostream>
#include <thread>
#include <chrono>

using namespace std;
using namespace chrono;

void func(atomic<double> & result) {
    double tmp = 5.;
    for (int i = 0; i < 50; ++i) {
        for (int j = 0; j < 999999; ++j) {
            tmp = 5. + sqrt(tmp*tmp*tmp) / sqrt(tmp);
        }
        result = tmp;
    }
}

int main() {
    atomic<double> a = 0;

    //  ------------------ 1 thread ------------------------

    system_clock::time_point point_1 = system_clock::now();
    func(a);
    system_clock::time_point point_2 = system_clock::now();
    duration<double> duration_1_thread = point_2 - point_1;
    cout << "[1 thread]\ta = " << a << "\n";
    cout << "[1 thread]\tDuration for 1 thread = " << duration_1_thread.count() << " sec.\n\n";

    //  ------------------ 2 threads -----------------------

    system_clock::time_point point_3 = system_clock::now();
    thread thr1(func, ref(a));
    thread thr2(func, ref(a));
    thr1.join();
    thr2.join();
    system_clock::time_point point_4 = system_clock::now();
    duration<double> duration_2_threads = point_4 - point_3;

    cout << "[2 threads]\ta = " << a << "\n";
    cout << "[2 threads]\tDuration for 2 threads = " << duration_2_threads.count() << " sec.\n\n";

    //  -----------------------------------------------------

    return 0;
}