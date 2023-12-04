#include <iostream>
#include <thread>
#include <chrono>
#include <math.h>

using namespace std;
using namespace chrono;

void threadFunction(const int num_thread, atomic<double> & result) {
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

    atomic<double> A{ 5.f };

    //  ------------------ 1 thread ------------------------

    point_old = system_clock::now();
    threadFunction(1, A);
    point_new = system_clock::now();
    duration_now = point_new - point_old;
    cout << "[1 thread]\tA = " << A << "\n";
    cout << "[1 thread]\tDuration for threads = " << duration_now.count() << " sec.\n\n";

    //  ------------------ 2 threads -----------------------
    A = 5.f;

    point_old = system_clock::now();
    thread thr1(threadFunction, 1, ref(A));
    thread thr2(threadFunction, 2, ref(A));
    thr1.join();
    thr2.join();
    point_new = system_clock::now();
    duration_now = point_new - point_old;

    cout << "[2 threads]\tA = " << A << "\n";
    cout << "[2 threads]\tDuration for threads = " << duration_now.count() << " sec.\n\n";

    //  -----------------------------------------------------

    return 0;
}