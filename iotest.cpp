#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <exception>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <sstream>
#include <string>

using namespace std;

//#define USE_SIGN // Define this to have signed custom int I/O

const int limit   = 10000000; // How many objects to output
const int retries = 3;        // How many times to run each test

// Turn on iostreams optimizations
inline void init()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
}

//
// Custom int write and read functions
//
// FIXME: Can't read or write INT_MIN
// TODO: Can these functions be further sped up?
//

inline void write_int(int x)
{
#ifdef USE_SIGN
    if (x < 0)
    {
        putchar('-');
        x = -x;
    }
#endif

    char buf[10], *p = buf;
    do
    {
        *p++ = '0' + x % 10;
        x /= 10;
    }
    while (x);
    do
    {
        putchar(*--p);
    }
    while (p > buf);
}

inline int read_int()
{
    char c;

    while (c = getchar(), c <= ' ');

#ifdef USE_SIGN
    bool sign = c == '-';
    if (sign)
    {
        c = getchar();
    }
#endif

    int res = c - '0';
    while (c = getchar(), c >= '0' && c <= '9')
    {
        res = res * 10 + (c - '0');
    }
    // One character is gobbled here

#ifdef USE_SIGN
    return sign ? -res : res;
#else
    return res;
#endif
}

//
// Begin tests
//

void int_printf()
{
    for (int i = 0; i < limit; i++)
    {
        printf("%d\n", i);
    }
}

void int_cout()
{
    init();
    for (int i = 0; i < limit; i++)
    {
        cout << i << '\n';
    }
}

void int_write_int()
{
    for (int i = 0; i < limit; i++)
    {
        write_int(i);
        putchar('\n');
    }
}

void int_scanf()
{
    for (int i = 0; i < limit; i++)
    {
        int x;
        scanf("%d", &x);
    }
}

void int_cin()
{
    init();
    for (int i = 0; i < limit; i++)
    {
        int x;
        cin >> x;
    }
}

void int_read_int()
{
    for (int i = 0; i < limit; i++)
    {
        read_int();
    }
}

void double_printf()
{
    for (int i = 0; i < limit; i++)
    {
        printf("%.6f\n", static_cast<double>(i));
    }
}

void double_cout()
{
    init();
    cout.setf(ios::fixed);
    cout.precision(6);
    for (int i = 0; i < limit; i++)
    {
        cout << static_cast<double>(i) << '\n';
    }
}

void double_scanf()
{
    for (int i = 0; i < limit; i++)
    {
        double x;
        scanf("%lf", &x);
    }
}

void double_cin()
{
    init();
    for (int i = 0; i < limit; i++)
    {
        double x;
        cin >> x;
    }
}

void char_putchar()
{
    for (int i = 0; i < limit * 10; i++)
    {
        putchar(' ' + i % 64);
    }
    putchar('\n');
}

void char_cout()
{
    init();
    for (int i = 0; i < limit * 10; i++)
    {
        cout.put(' ' + i % 64);
    }
    cout.put('\n');
}

void char_getchar()
{
    for (int i = 0; i < limit * 10; i++)
    {
        getchar();
    }
}

void char_cin()
{
    init();
    for (int i = 0; i < limit * 10; i++)
    {
        cin.get();
    }
}

const char   s[] = "abcdefghijklmnop";
const string str(s);
char         buf[sizeof(s)];

void str_puts()
{
    for (int i = 0; i < limit; i++)
    {
        puts(s);
    }
}

void str_cout()
{
    init();
    for (int i = 0; i < limit; i++)
    {
        cout << s << '\n';
    }
}

void string_cout()
{
    init();
    for (int i = 0; i < limit; i++)
    {
        cout << str << '\n';
    }
}

void str_gets()
{
    for (int i = 0; i < limit; i++)
    {
        gets(buf);
    }
}

void str_cin()
{
    init();
    for (int i = 0; i < limit; i++)
    {
        cin.getline(buf, sizeof(buf));
    }
}

void string_getline()
{
    init();
    for (int i = 0; i < limit; i++)
    {
        //
        // We can most certainly speed up this loop by moving x outside. But
        // this would differ with what we are trying to emulate: reading many
        // strings into a string array, where each element is initialized anew.
        //
        string x;

        //
        // In most problems we know the maximum possible length of a string,
        // thus we can tell x about it.
        //
        x.reserve(sizeof(s));

        getline(cin, x);
    }
}

//
// End tests
//


enum io_dir {
    IN,
    OUT
};

struct test_entry {
    string   name;     // Test name
    void   (*func)();  // Test function
    io_dir   dir;      // I/O direction
};

// List of tests
const test_entry entries[] = {
    { "int, printf",     int_printf,     OUT },
    { "int, cout",       int_cout,       OUT },
    { "int, custom/out", int_write_int,  OUT },
    { "int, scanf",      int_scanf,      IN  },
    { "int, cin",        int_cin,        IN  },
    { "int, custom/in",  int_read_int,   IN  },
    { "double, printf",  double_printf,  OUT },
    { "double, cout",    double_cout,    OUT },
    { "double, scanf",   double_scanf,   IN  },
    { "double, cin",     double_cin,     IN  },
    { "char, putchar",   char_putchar,   OUT },
    { "char, cout",      char_cout,      OUT },
    { "char, getchar",   char_getchar,   IN  },
    { "char, cin",       char_cin,       IN  },
    { "char *, puts",    str_puts,       OUT },
    { "char *, cout",    str_cout,       OUT },
    { "string, cout",    string_cout,    OUT },
    { "char *, gets",    str_gets,       IN  },
    { "char *, cin",     str_cin,        IN  },
    { "string, getline", string_getline, IN  }
};

int main(int argc, char *argv[])
try
{
    if (argc == 0)
    {
        // Can't run itself
        throw runtime_error("program name not available");
    }
    else if (argc == 1)
    {
        //
        // This is the main process
        //

        // Get a temporary file name
        const char *fname = tmpnam(NULL);
        if (!fname)
        {
            throw runtime_error("tmpnam() failed");
        }

        // Run all tests
        for (size_t i = 0; i < sizeof(entries)/sizeof(entries[0]); i++)
        {
            cerr << left << setw(15) << entries[i].name << " " << flush;

            // Prepare the command
            ostringstream cmd;
            cmd << argv[0] << " " << i
                << (entries[i].dir == OUT ? " > " : " < ") << fname;

            // Repeat the command 'retries' times
            for (int j = 0; j < retries; j++)
            {
                // If this is a write test, clean up leftovers
                if (entries[i].dir == OUT && ifstream(fname))
                {
                    if (remove(fname) != 0)
                    {
                        throw runtime_error("remove() failed");
                    }
                }

                // Run the command
                if (system(cmd.str().c_str()) != 0)
                {
                    return EXIT_FAILURE;
                }
            }
            cerr << endl;
        }

        // Final cleanup
        if (remove(fname) != 0)
        {
            throw runtime_error("remove() failed");
        }
    }
    else
    {
        //
        // This is the child process
        //

        // Get the test number
        istringstream param(argv[1]);
        int i;
        param >> i;

        // Run and time the function
        clock_t start = clock();
        entries[i].func();
        if (entries[i].dir == OUT)
        {
            cout << flush;
        }
        clock_t end   = clock();

        //
        // Check for errors. Unfortunately, this check doesn't always work
        // with stdio. However, placing error checks into the test functions
        // would incur a performance penalty, so we leave it as it is.
        //
        // I hope calling ferror() is fine even with sync_with_stdio(false).
        //
        if (ferror(stdin) || !cin.good() || ferror(stdout) || !cout.good())
        {
            throw runtime_error("input/output error");
        }

        // Output result
        cerr << fixed << setw(7) << setprecision(2) << right
             << static_cast<double>(end - start) / CLOCKS_PER_SEC << flush;
    }
}
catch (const exception& e)
{
    cerr << "error: " << e.what() << endl;
    return EXIT_FAILURE;
}
