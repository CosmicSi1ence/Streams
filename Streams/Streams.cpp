#include <iostream>
#include <thread>
#include <chrono>

using namespace std;
using namespace chrono;

void threadFunction(atomic<double> & result) {
    double tmp = 5.;
    for (int i = 0; i < 50; ++i) {
        for (int j = 0; j < 999999; ++j) {
            tmp = 5. + sqrt(tmp*tmp*tmp) / sqrt(tmp);
        }
        result = tmp;
    }
}

int main() {

    system_clock::time_point point_new, point_old;
    duration<double> duration_now;

    atomic<double> a = 5.;

    //  ------------------ 1 thread ------------------------

    point_old = system_clock::now();
    threadFunction(a);
    point_new = system_clock::now();
    duration_now = point_new - point_old;
    cout << "[1 thread]\ta = " << a << "\n";
    cout << "[1 thread]\tDuration for 1 thread = " << duration_now.count() << " sec.\n\n";

    //  ------------------ 2 threads -----------------------
    a = 5.;

    point_old = system_clock::now();
    thread thr1(threadFunction, ref(a));
    thread thr2(threadFunction, ref(a));
    thr1.join();
    thr2.join();
    point_new = system_clock::now();
    duration_now = point_new - point_old;

    cout << "[2 threads]\ta = " << a << "\n";
    cout << "[2 threads]\tDuration for 2 threads = " << duration_now.count() << " sec.\n\n";

    //  -----------------------------------------------------

    return 0;
}