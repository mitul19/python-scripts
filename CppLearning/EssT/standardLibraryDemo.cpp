/*
The C++ standard library is used to support a large number of common system level tasks. 
This set of library functions is mostly inherited from the C standard library as generally compatible with standard C code. 
The standard library includes a great number of functions and macros supporting a broad scope of functionalities 
    including file I/O facilities for creating reading and writing files. 
    Support for C strings null terminated a raise of characters. 
    Error handling functions for standardized handling of common system errors. 
    Date and time functions. Provide support for common date and time structures. 
    Other utilities including math, localization, signals and other system services. 
The headers for the C++ standard library are the same as those for the C standard library with a simple difference. 
For C++, the headers have .h at the end of the file name and have a lowercase C at the beginning like this. 
This effectively distinguishes the C++ library headers from the C versions which are likely also included with your development environment. 
These C++ library functions are in the standard namespace for compatibility with C code these functions are also in the global namespace. 
So it's usually fine to admit the std:: namespace specifier at the beginning of the function name but be aware that there may be some instances where it is required. 
*/
#include <cstdio>
#include <cstring>
#include <cstdint>
#include <cmath>
#include <ctime>
#include <cerrno>   //Error no. work, Access to int value of error.

constexpr int maxstring = 1024;    // read buffer size
constexpr int repeat = 5;
constexpr size_t maxlen = 127;
const size_t maxbuf = 128;
const char * ss1 = "String one";
const char * s2 = "String two";

// struct for binary mode demo.
struct s1 {
    uint8_t num;
    uint8_t len;
    char s[maxlen + 1];
};

int main() {
    const char * fn = "testfile.txt";   // file name
    const char * str = "This is a literal c-string.\n";

    // create/write the file
    puts("writing file");
    FILE * fw = fopen(fn, "w");
    for(int i = 0; i < repeat; i++) {
        fputs(str, fw);
    }
    
    fclose(fw);
    puts("done.");
    
    // read the file
    puts("reading file");
    char buf[maxstring];
    FILE * fr = fopen(fn, "r");
    while(fgets(buf, maxstring, fr)) {
        fputs(buf, stdout);
    }
    
    fclose(fr);
    remove(fn);
    
    puts("done.");

// Binary mode demo.
    const char * fnb = "test.file";            // file name
    const char * strb = "This is a literal C-string.";
    
    // create/write the file
    puts("writing file");
    FILE * fwb = fopen(fnb, "wb");
    
    static s1 buf1;
    for( int i = 0; i < 5; i++ ) {
        buf1.num = i;
        buf1.len = (uint8_t) strlen(str);
        if(buf1.len > maxlen) buf1.len = maxlen;
        strncpy(buf1.s, strb, maxlen);
        buf1.s[buf1.len] = 0; // make sure it's terminated
        fwrite(&buf1, sizeof(s1), 1, fwb);
    }
    
    fclose(fwb);
    puts("done.");
    
    // read the file
    puts("reading file");
    FILE * frb = fopen(fnb, "rb");
    static s1 buf2;
    size_t rc;
    while(( rc = fread(&buf2, sizeof(s1), 1, frb) )) {
        printf("a: %d, b: %d, s: %s\n", buf2.num, buf2.len, buf2.s);
    }
    
    fclose(frb);
    remove(fnb);

//Read and rename work
    static const char * fn1 =  "file1";
    static const char * fn2 =  "file2";
    FILE * fnw1  = fopen(fn1, "w");
    fclose(fnw1);
    puts("file1 done.");

    rename(fn1, fn2);  // return 0 on success , both  remove and rename works that way
    puts("rename to fn2 done.");

//Unformatted char I/O
    const int bufsize = 256;
    static char unbuf[bufsize];
    fputs("prompt :", stdout);   
    fgets(unbuf, bufsize, stdin); //Never use gets as it doesn't check for bufsize. 
    puts("Output :");
    fputs(unbuf, stdout);
    fflush(stdout);  //it says finish writing and i will wait. For large mega bytes files it makes sense to wait.


//Formatted char I/O 
// %d - integer, %f - float, %s - c-string, %c - char, %p - pointer, %% - the % character
    int fi = 5;
    long int fli =  1234567890L;
    const char * fstring = "This is a string";
    printf("i is %04d, long int is %ld and string : %s \n", fi, fli, fstring);
    fprintf(stdout, "pointer : %p, size : %zd \n", fstring, sizeof(fstring));  //fprintf can be used to write formated output.

    int neg = -7;
    int x = abs(neg);
    printf("x is %d\n", x);
    double dneg = -47;
    double dx = fabs(neg);
    double de = exp(2);
    double dl = log(100);
    double dp = pow(2 , 2);
    double dsrqt = sqrt(1024);
    const double pi = acos(-1);
    double dpi = sin(pi/6);
    printf("dx : %lf, de : %lf, dl : %lf, dp : %lf, dsqrt : %lf, dpi : %lf \n", dx, de, dl, dp, dsrqt, dpi);

//ctime - rand demos.
    printf("time value: %ld\n", (long) time(nullptr));
    srand((unsigned)time(nullptr));
    rand();
    printf("pseudo-random value: %d\n", rand() % 1000);
    printf("pseudo-random value: %d\n", rand() % 1000);
    printf("pseudo-random value: %d\n", rand() % 1000);
    printf("RAND_MAX is %d\n", RAND_MAX);

// String related tasks. Which are simple, efficient and flexible, 
// Used where complexity and power of OOP not needed

    char sd1[maxbuf];
    char sd2[maxbuf];
    int ii = 0;
    char cc = 0;
    char * cp = nullptr;
    
    // strncpy -- copy a string
    strncpy(sd1, ss1, maxbuf);
    printf("sd1 is %s\n", sd1);
    strncpy(sd2, s2, maxbuf);
    printf("sd2 is %s\n", sd2);
    
    // strncat -- concatenate string
    strncat(sd1, " - ", maxbuf - strlen(sd1) - 1);
    strncat(sd1, s2, maxbuf - strlen(sd1) - 1);
    printf("sd1 is %s\n", sd1);
    
    // strnlen -- get length of string
    printf("length of sd1 is %zd\n", strnlen(sd1, maxbuf));
    printf("length of sd2 is %zd\n", strnlen(sd2, maxbuf));
    
    // strcmp -- compare strings
    ii = strcmp(sd1, sd2);
    printf("sd1 %s sd2 (%d)\n", (ii == 0) ? "==" : "!=", ii);
    ii = strcmp(sd2, s2);
    printf("sd2 %s s2 (%d)\n", (ii == 0) ? "==" : "!=", ii);
    
    // strchr -- find a char in string
    cc = 'n';
    cp = strchr(sd1, cc);
    printf("Did we find a '%c' in sd1? %s\n", cc, cp ? "yes" : "no");
    if(cp) printf("The first '%c' in sd1 is at position %ld\n", cc, cp - sd1);
    
    // strstr -- find a string in string
    cp = strstr(sd1, s2);
    printf("Did we find '%s' in sd1? %s\n", s2, cp ? "yes" : "no");
    if(cp) printf("The first '%s' in sd1 is at position %ld\n", s2, cp - sd1);

// Error Demo.
    printf("Erasing file foo.bar\n");
    remove("foo.bar");
    printf("errno is: %d\n", errno);
    perror("Cannot erase file");
    //we can use below if we dont want to use perror
    const char * errstr = strerror(errno);
    printf("error (%d) : %s\n", errno, errstr);

// Challenge Work.
    return 0;
}
