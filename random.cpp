#include "random.hpp"
#include <chrono>
#include <math.h>
#include <unistd.h>

long long int probe (int n)
{
    double b;
    double c;
    double d;
    long long int nt = n;
    random_device rd;
    mt19937_64 gen (rd());
    uniform_int_distribution<> dist (20000, 999999);
    uniform_int_distribution<> dist1 (25, 303);
    c = pow (dist (gen), 0.0256473);
    c = 1 / c;
    b = pow (dist (gen), c);
    b = modf (b, &d);
    b = (b + c) * pow (10, dist1 (gen));
    b = modf (b, &d);
    b += c;
    b *= (1000000 + 100 * nt);
    b = modf (b, &d);
    return static_cast<long long int> (d);
}

void* Timer (void* arg)
{
    string hour, min, sec, msec;
    int h, m, s, ms;
    bool* item = static_cast<bool*> (arg);
    for (long long int n = 0; *item != 1; n++)
    {
        // this_thread::sleep_for (chrono::milliseconds (10));
        h  = n / 360000;
        m  = n / 6000;
        s  = n / 100;
        ms = n % 60;
        if (h > 24) h = h % 24;
        if (m > 60) m = m % 60;
        if (s > 60) s = s % 60;
        if (ms > 10) ms = ms % 10;
        if (h < 10) cout << "0";
        if (h == 24) cout << "00";
        else cout << h;
        cout << ":";
        if (m < 10) cout << "0";
        if (m == 60) cout << "00";
        else cout << m;
        cout << ":";
        if (s < 10) cout << "0";
        if (s == 60) cout << "00";
        else cout << s;
        cout << ":";
        if (ms == 10) cout << "0";
        else cout << ms;
        cout << "\r";
    }
    return nullptr;
}

void checksum (int n)
{
    bool item = 0;
    double *a, b = 0, min = 100, max = 0;
    a = new double[n * sizeof (double)];
    for (int i = 0; i < n; i++)
        a[i] = 0;
    for (unsigned long long int i = 0; i < 10000 * (unsigned long long int)n;
         i++)
    {
        a[(probe (n)) % n]++;
    }
    for (int i = 0; i < n; i++)
        b += a[i];
    cout.precision (6);
    for (int i = 0; i < n; i++)
    {
        // cout<<a[i]/b*100<<"% ";
        if ((a[i] / b * 100) <= min && (a[i] / b) > 0.000000000001)
        {
            min = a[i] / b * 100;
        }
        if ((a[i] / b * 100) >= max)
        {
            max = a[i] / b * 100;
        }
    }
    item = 1;
    delete[] a;
    a = NULL;
    cout << endl;
    if (max - min > pow (1000, -n)) cout << (max - min) * n << "%" << endl;
}

void check (int n)
{
    bool item = 0;
    double *a, b = 0, min = 100, max = 0;
    random_device rd;
    mt19937_64 gen (rd());
    uniform_int_distribution<> dist (0, n);
    a = new double[n * sizeof (double)];
    for (int i = 0; i < n; i++)
        a[i] = 0;
    for (unsigned long long int i = 0; i < 10000 * (unsigned long long int)n;
         i++)
    {
        a[(dist (gen)) % n]++;
    }
    for (int i = 0; i < n; i++)
        b += a[i];
    cout.precision (6);
    for (int i = 0; i < n; i++)
    {
        // cout<<a[i]/b*100<<"% ";
        if ((a[i] / b * 100) <= min && (a[i] / b) > 0.000000000001)
        {
            min = a[i] / b * 100;
        }
        if ((a[i] / b * 100) >= max)
        {
            max = a[i] / b * 100;
        }
    }
    item = 1;
    delete[] a;
    a = NULL;
    cout << endl;
    if (max - min > pow (1000, -n)) cout << (max - min) * n << "%" << endl;
}

void timeM (int n)
{
    cout << "Your waiting time equals " << n / 100000.0 * 4.092 << " seconds"
         << endl;
    cout << endl;
    for (int i = 1; i <= 10; i++)
    {
        unsigned int len = static_cast<unsigned int> (pow (10, i));
        auto begin       = std::chrono::steady_clock::now();
        for (unsigned int l = 0; l < len; l++)
            probe (len);
        auto end = std::chrono::steady_clock::now();
        auto elapsed_ms =
            std::chrono::duration_cast<std::chrono::milliseconds> (end - begin);
        cout << elapsed_ms.count() << " ";
    }
    cout << endl;
}
