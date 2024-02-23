#include <cstdio>
#include <cstdint> //To utilize specified sizes of integer
#include <string>  // to use std::string for AUTO demo
#include <vector>  //to use vector<int> for AUTO demo

// a byte is 8 bits
const size_t byte = 8;

class S
{
public:
    int static_value()
    {
        static int x = 7;
        return ++x;
    }
};

int func()
{
    int x = 7;
    return ++x;
}

int Staticfunc()
{
    static int x = 7;
    return ++x;
}

struct Employee
{
    int id;
    const char *name;
    const char *role;
};

struct Prefs
{
    bool likesMusic : 1;
    bool hasHair : 1;
    bool hasInternet : 1;
    bool hasDinosaur : 1;
    unsigned int numberOfChildren : 4;
};

/* ENUM Demo work */

enum card_suit : uint8_t
{
    SPD,
    HRT,
    DIA,
    CLB
};
enum card_rank : uint8_t
{
    ACE = 1,
    DEUCE = 2,
    JACK = 11,
    QUEEN,
    KING
};

const char *aceString = "Ace";
const char *jckString = "Jack";
const char *queString = "Queen";
const char *kngString = "King";
const char *deuString = "Deuce";
const char *spdString = "Spades";
const char *hrtString = "Hearts";
const char *diaString = "Diamonds";
const char *clbString = "Clubs";

struct card
{
    uint8_t rank;
    uint8_t suit;
};

card deck[52] = {
    {ACE, SPD}, {DEUCE, SPD}, {3, SPD}, {4, SPD}, {5, SPD}, {6, SPD}, {7, SPD}, {8, SPD}, {9, SPD}, {10, SPD}, {JACK, SPD}, {QUEEN, SPD}, {KING, SPD}, {1, HRT}, {2, HRT}, {3, HRT}, {4, HRT}, {5, HRT}, {6, HRT}, {7, HRT}, {8, HRT}, {9, HRT}, {10, HRT}, {11, HRT}, {12, HRT}, {13, HRT}, {1, DIA}, {2, DIA}, {3, DIA}, {4, DIA}, {5, DIA}, {6, DIA}, {7, DIA}, {8, DIA}, {9, DIA}, {10, DIA}, {11, DIA}, {12, DIA}, {13, DIA}, {1, CLB}, {2, CLB}, {3, CLB}, {4, CLB}, {5, CLB}, {6, CLB}, {7, CLB}, {8, CLB}, {9, CLB}, {10, CLB}, {11, CLB}, {12, CLB}, {13, CLB}};

void print_card(const card &c)
{
    if (c.rank >= 3 && c.rank <= 10)
    {
        printf("%d of ", c.rank);
    }
    else
    {
        switch (c.rank)
        {
        case ACE:
            printf("%s of ", aceString);
            break;
        case JACK:
            printf("%s of ", jckString);
            break;
        case QUEEN:
            printf("%s of ", queString);
            break;
        case KING:
            printf("%s of ", kngString);
            break;
        case DEUCE:
            printf("%s of ", deuString);
            break;
        }
    }
    switch (c.suit)
    {
    case SPD:
        puts(spdString);
        break;
    case HRT:
        puts(hrtString);
        break;
    case DIA:
        puts(diaString);
        break;
    case CLB:
        puts(clbString);
        break;
    }
}

// Union may be convinient for simple IPV4, but for complex used you may consider class.
union ipv4
{
    uint32_t i32;
    struct
    {
        uint8_t a;
        uint8_t b;
        uint8_t c;
        uint8_t d;
    } octets;
};

// Typedef handy in instances where type declaration become cumbersome. provides alias to type name.
typedef unsigned char points_t;
typedef unsigned char rank_t;

struct score
{
    points_t p;
    rank_t r;
};

// Void type has special meaning. it specify lack of value for function parameters and function returns
void void_func(void)
{
    puts("this is void void_func ( void )");
}

// AUTO - strongly types automatically
std::string &autofunc()
{
    static std::string s = "this is a string";
    return s;
}

// nullptr demo work.
#ifndef NULL
#define NULL (0LL) /* common C++ definition */
#endif

void nullf(int i)
{
    printf("the int is %d\n", i);
}

void nullf(const char *s)
{
    printf("the pointer is %p\n", s);
}

// Challenge Struct
struct libCard
{
    /* data */
    const char *title;
    const char *author;
    const char *publisher;
    const char *subject;
    const char *isbn;
    const char *oclc;
    short int ddc1;
    short int ddc2;
    short int year_pub;
    short int year_acq;
    short int quantity;
};

int main()
{

    // CH3: Data types
    /* Strongly typed - every value have specific type.
    Primitive types:
        integer types (signed and unsigned)
            char(8 bit)
            short int (16 bit)
            int (32 bit)
            long int (32 or 64 bit)
            long long int (64 bit)
            <cstdint> provides Signed and unsigned int with specific bit
        floating point types (real numerical) - Scale and precision has to be considered
            float (32 bit)
            double (64 bit)
            long double (128 bits) - it uses 80 bits IEEE, precision varies
        boolean Type
    Compound Types : containers for primitive or other types
        Array - contiguous sequential set of object of same type. basis of c-string and c++ STL conttainer class
            c-string is array of char.
        Structure - Sequential set of objects of different types, it can contain scalars, arrays and even other structure and classes
        Class - c++ classes are based on C structures (it defaults to private members)
        Union - Set of overlapping object
        pointer - Address that references an object of given type. it also determine the size of increments, decrements and arithmetic operations on pointer
        reference - immutable, once defined they cant be changed, Accessed as aliases without any syntactic indication that its a reference (silent side effects)
        bitfield - ability to pack multiple values into less space.
        ENUM - tend to start with 0, type safe.
    Qualifier - to adjust qualities of object or variable. CV - constant volatile.
        CV      | Storage Duration
        --------| -------
        const   | static
        mutable | register
        volatile| extern

        Const -> variable as read only or immutable. cant be changed
        Mutable -> used to make it writable from const qualified member function
        volatiole -> varible that can be changed by another process. (rarely used)
        static -> life beyond execution of block of code, they live for the duration of program.
        register -> varibles are stored in processor registers, this makes them easier to access and operate on.
        extern -> defined in separate translation unit and linked with code by linker step.

    */
    char c = 0;
    short int si = 0;
    int i = 0;
    long int li = 0;
    long long int lli = 0;
    float f;
    double df;
    long double ldf;
    char cstring[] = "String";

    printf("sizeof char is %zd bits\n", sizeof(c) * 8);
    printf("sizeof short int is %zd bits\n", sizeof(si) * 8);
    printf("sizeof int is %zd bits\n", sizeof(i) * 8);
    printf("sizeof long int is %zd bits\n", sizeof(li) * 8);
    printf("sizeof long long int is %zd bits\n", sizeof(lli) * 8);

    // cstdint usages.
    printf("sizeof int8_t is %ld bits\n", sizeof(int8_t) * 8);
    printf("sizeof int16_t is %ld bits\n", sizeof(int16_t) * 8);
    printf("sizeof int32_t is %ld bits\n", sizeof(int32_t) * 8);
    printf("sizeof int64_t is %ld bits\n", sizeof(int64_t) * 8);

    printf("sizeof uint8_t is %ld bits\n", sizeof(uint8_t) * 8);
    printf("sizeof uint16_t is %ld bits\n", sizeof(uint16_t) * 8);
    printf("sizeof uint32_t is %ld bits\n", sizeof(uint32_t) * 8);
    printf("sizeof uint64_t is %ld bits\n", sizeof(uint64_t) * 8);

    // Float Types
    printf("size of float f is %zd bits\n", sizeof(f) * byte);
    printf("size of double df is %zd bits\n", sizeof(df) * byte);
    printf("size of long double ldf is %zd bits\n", sizeof(ldf) * byte);
    f = 5e2;
    printf("f is (scientific notations 5e2) %f \n", f);
    f = 400.0;
    printf("f is %f \n", f);

    // Scale and precision has to be considered. (precision may not be great)
    f = .1 + .1 + .1;
    printf("f is %f \n", f);
    if (f == 0.3)
        puts("True");
    else
        puts("FALSE");
    printf("f is %1.10f \n", f);

    // c-string  example
    puts(cstring);
    for (int i = 0; cstring[i]; i++)
    {
        printf("%d: %c\n", i, cstring[i]);
    }
    const char *const_cstring = "constCstring"; // type of pointer is const char so we no longer copying it to array

    puts(const_cstring);
    for (int i = 0; const_cstring[i]; i++)
    {
        printf("%d: %c\n", i, const_cstring[i]);
    }

    // Char escape sequences
    puts("Hello,\n\tWorld! \' \" \\ \x40 \u03bc \u0ABF\u0AAE\u0AA4\u0AC1\u0AB2");

    // Non static re assign 7 where as static will retains
    int notStaticF = func();
    notStaticF = func();
    notStaticF = func();
    printf("The integer is %d\n", notStaticF);

    int static_f = Staticfunc();
    static_f = Staticfunc();
    static_f = Staticfunc();
    printf("The integer is %d\n", static_f);

    // Static varible have global storage, each instance will share same varible.
    S s1;
    S s2;
    S s3;
    printf("The s1.static_value() is %d\n", s1.static_value());
    printf("The s2.static_value() is %d\n", s2.static_value());
    printf("The s3.static_value() is %d\n", s3.static_value());

    // Reference Demo
    int ir = 5;
    int &ref_ir = ir; // reference to ir
    ref_ir = 10;      // when we change ref it make ir to 10 as well
    printf("ir is %d\n", ir);

    // Struct demo
    Employee joe = {42, "Joe", "Boss"};
    Employee *jp = &joe;
    printf("%s is the %s and has id %d\n", joe.name, joe.role, joe.id);
    printf("%s is the %s and has id %d\n", jp->name, jp->role, jp->id);

    // bitfields demo
    Prefs homer;
    homer.likesMusic = true;
    homer.hasHair = false;
    homer.hasInternet = true;
    homer.hasDinosaur = false;
    homer.numberOfChildren = 3;

    printf("sizeof homer: %zd bits\n", sizeof(homer) * 8);
    printf("sizeof int: %zd bits\n", sizeof(int) * 8);

    if (homer.likesMusic)
        printf("homer likes music\n");
    if (homer.hasHair)
        printf("homer has hair\n");
    if (homer.hasInternet)
        printf("homer has net\n");
    if (homer.hasDinosaur)
        printf("homer has a dino\n");
    printf("homer has %d children\n", homer.numberOfChildren);

    // Enum Demo.
    long int ecount = sizeof(deck) / sizeof(card);
    printf("count: %ld cards\n", ecount);
    for (card c : deck)
    {
        print_card(c);
    }

    // Union Demo
    union ipv4 addr;
    addr.octets = {192, 168, 73, 42};
    printf("addr is %d.%d.%d.%d is %08x\n",
           addr.octets.a, addr.octets.b, addr.octets.c, addr.octets.d, addr.i32);

    // typedef demo
    score s = {5, 1};
    printf("score s had %d points and a rank of %d\n", s.p, s.r);

    // void demo
    puts("calling func()");
    void_func();

    // Auto demo
    auto ax = autofunc();
    printf("ax is %s\n", ax.c_str());
    printf("type of ax is %s\n", typeid(ax).name());

    std::vector<int> vi = {1, 2, 3, 4, 5};
    for (std::vector<int>::iterator it = vi.begin(); it != vi.end(); ++it)
    {
        printf("int is %d\n", *it);
    }
    // using Auto to get iterator type
    for (auto it = vi.begin(); it != vi.end(); ++it)
    {
        printf("int is %d via Auto iterator\n", *it);
    }

    // c++ 11 defines 'nullptr' keyword - that can be converted to a NULL pointer value or NULL member pointer value.
    // so it can be promoted to pointer of any type.
    nullf(nullptr);
    nullf(0);

    // Challenge on library card.
    libCard lc1 = {
        "The CGI Book", "William E. Weinman", "New Riders",
        "CGI (Computer network protocol)",
        "1562055712 9781562055714", "477166381",
        510, 78, 1996, 1997, 2};

    printf("Title: %s\n", lc1.title);
    printf("Author: %s\n", lc1.author);
    printf("Publisher: %s\n", lc1.publisher);
    printf("Subject: %s\n", lc1.subject);
    printf("ISBN: %s\n", lc1.isbn);
    printf("WorldCat (OCLC): %s\n", lc1.oclc);
    printf("Dewey Decimal: %d.%d\n", lc1.ddc1, lc1.ddc2);
    printf("Year published: %d\n", lc1.year_pub);
    printf("Year acquired: %d\n", lc1.year_acq);
    printf("Quantity: %d\n", lc1.quantity);

    return 0;
}