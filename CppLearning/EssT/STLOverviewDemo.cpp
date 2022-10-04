/* 
The Standard Template Library is part of the C++ standards, so it's guaranteed to be part of every C++ development system. 
Commonly called the STL, the Standard Template Library provides containers and supporting data types like, vectors, lists, queues, and iterators. 
Other basic functions are provided by the C++ standard library. 
The STL provides a number of standard containers, iterators and algorithms. 
Some of these include 
    vector, a fundamental random access container, that can be used in many places as C array could be used, but with a lot more functionality. 
    List, a double ended list optimized for fast inserts and deletes. 
    Set, an ordered sequence container, where elements are kept in a strict order based on their value. 
    Map, an associate of container where unique keys are used to access associated values. 
    Stack, queue and deck are LIFO FIFO and double ended queues for pushing and popping data from a stack. 
    String, is a specialized container of characters, optimized for use as strings. And 
    IO streams, for reading and writing data to and from files and IO devices. 
*/
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <fstream>

// created name Space and class E which inherits exception 
namespace BW {
    class E : public std::exception {
        const char * msg;
        E();
    public:
        E(const char *s) noexcept(true) : msg(s) {}
        const char * what() const noexcept(true) { return msg; }
    };
}

// Throw std::exception()
void broken1() {
    std::cout << "this is a broken function" << std::endl;
    throw std::exception();
}

// Throw user defined exceptions
const BW::E e_ouch("ouch");
const BW::E e_bad("bad code");
const BW::E e_worse("dont do that!");

void broken2() {
    std::cout << "this is a broken function which takes inherited Class E from BW namespace" << std::endl;
    throw e_worse;
}

struct item
{
	int sku;
	std::string name;
	std::string desc;
};

int main() {

// Vector Demo
    std::cout << "vector from initializer list: " << std::endl;
    std::vector<int> vi1 = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };  //Defined like template syntax
    
    std::cout << "size: " << vi1.size() << std::endl;
    std::cout << "front: " << vi1.front() << std::endl;
    std::cout << "back: " << vi1.back() << std::endl;
    std::cout << std::endl;
    
    // iterator
    std::vector<int>::iterator itbegin = vi1.begin();  // auto can be used as compiler knows its type 
    std::vector<int>::iterator itend = vi1.end();
    for (auto it = itbegin; it < itend; ++it) {
        std::cout << *it << ' ';
    }
    std::cout << std::endl;
    
    std::cout << "element at 5: " << vi1[5] << std::endl;
    std::cout << "element at 5: " << vi1.at(5) << std::endl;

    std::cout << "range-based for loop:" << std::endl;
    for (int i : vi1) {
        std::cout << i << ' ';
    }
    std::cout << std::endl << std::endl;

    std::cout << "insert 42 at begin + 5: " << std::endl;
    vi1.insert(vi1.begin() + 5, 42);
    std::cout << "size: " << vi1.size() << std::endl;
    std::cout << "vi1[5]: " << vi1[5] << std::endl;
    
    std::cout << "erase at begin + 5: " << std::endl;
    vi1.erase(vi1.begin() + 5);
    std::cout << "size: " << vi1.size() << std::endl;
    std::cout << "vi1[5]: " << vi1[5] << std::endl;
    
    std::cout << "push_back 47: " << std::endl;
    vi1.push_back(47);
    std::cout << "size: " << vi1.size() << std::endl;
    std::cout << "vi1.back() " << vi1.back() << std::endl;
    std::cout << std::endl;

    // from C-array
    const static size_t size = 10;
    int ia[size] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    std::cout << "vector from C-array: " << std::endl;
    std::vector<int> vi2(ia, ia + size);
    for( int i : vi2 ) {
        std::cout << i << ' ';
    }
    std::cout << std::endl << std::endl;
    
    // std::vector of strings
    std::cout << "vector of strings:" << std::endl;
    std::vector<std::string> vs = { "one", "two", "three", "four", "five" };
    for(const std::string & v : vs) {
        std::cout << v << std::endl;
    }

// String Demo
    std::string s1 = "This is a string";
    std::string::iterator it;
    
    // size & length
    std::cout << "size is same as length: " << s1.size() << std::endl;
    std::cout << "size is same as length: " << s1.length() << std::endl;
    
    // + for concatenation
    std::cout << "concatenated strings: ";
    std::string s2 = "this is also a string";
    std::cout << s1 + ":" + s2 << std::endl;
    std::cout << std::endl;

    // compare
    std::cout << "is s1 == s2? " << (s1 == s2 ? "yes" : "no") << std::endl;
    std::cout << "copy-assign s2 = s1" << std::endl;
    s2 = s1;
    std::cout << "is s1 == s2? " << (s1 == s2 ? "yes" : "no") << std::endl;
    std::cout << "is s1 > \"other string\"? " << (s1 > "other string" ? "yes" : "no") << std::endl;
    std::cout << "is s1 < \"other string\"? " << (s1 < "other string" ? "yes" : "no") << std::endl;
    std::cout << "is \"other string\"? > s1  " << ("other string" > s1 ? "yes" : "no") << std::endl;
    std::cout << "is \"other string\" < s1? " << ("other string" < s1 ? "yes" : "no") << std::endl;
    std::cout << std::endl;

    // iteration
    std::cout << "each character: ";
    for( char c : s1 ) {
        std::cout << c << " ";
    }
    std::cout << std::endl;
    
    // insert & erase with an iterator
    it = s1.begin() + 5;
    s1.insert(it, 'X');
    std::cout << "s1 after insert: " << s1 << std::endl;
    
    it = s1.begin() + 5;
    s1.erase(it);
    std::cout << "s1 after erase: " << s1 << std::endl;
    std::cout << std::endl;

    // replace
    s1.replace(5, 2, "ain't");
    std::cout << "s1 after replace: " << s1 << std::endl;

    // substr
    std::cout << "substr: " << s1.substr(5, 5) << std::endl;

    // find
    size_t pos = s1.find("s");
    std::cout << "find first \"s\" in s1 (pos): " << pos << std::endl;
    
    // rfind
    pos = s1.rfind("s");
    std::cout << "find last \"s\" in s1 (pos): " << pos << std::endl;

//IO Stream Demo.
    static int lineno = 0;
    static const char * filename = "test.txt";
    static const char * textstring = "This is the test file";
    
    // write a file
    std::cout << "write the file:" << std::endl;
    std::ofstream ofile(filename);
    ofile << ++lineno << " " << textstring << std::endl;
    ofile << ++lineno << " " << textstring << std::endl;
    ofile << ++lineno << " " << textstring << std::endl;
    ofile.close();
    
    // read a file
    static char buf[128];
    std::cout << "read the file:" << std::endl;
    std::ifstream infile(filename);
    while (infile.good()) {
        infile.getline(buf, sizeof(buf));
        std::cout << buf << std::endl;
    }
    infile.close();
    
    // delete file
    std::cout << "delete file." << std::endl;
    remove(filename);
    std::cout << std::endl;

    // cout is a very common class from iostream
    std::cout << "Hello, World!" << std::endl;

    std::string istr;
    std::cout << "Prompt: ";
    std::cin >> istr;    // one word at a time
    std::cout << "Input: " << istr << std::endl;

    char buff[128];
    std::cin.getline(buff, sizeof(buff));  //To fetch 128 chars.
    std::cout << buff << std::endl;

    // integer formatting
    int i1 = 42;
    int i2 = 127;
    int i3 = 5555;
    std::cout << "default: " << i1 << ' ' << i2 << ' ' << i3 << std::endl;
    std::cout << "hex: " << std::hex << i1 << ' ' << i2 << ' ' << i3 << std::endl;
    std::cout << "hex with showbase: " << std::showbase << std::hex << i1 << ' ' << i2 << ' ' << i3 << std::endl;
    std::cout << "octal with showbase: " << std::oct << i1 << ' ' << i2 << ' ' << i3 << std::endl;
    std::cout << "default: " << std::noshowbase << std::dec << i1 << ' ' << i2 << ' ' << i3 << std::endl << std::endl;
    
    // floating point formatting options
    double d1, d2, d3;
    d1 = 3.1415926534;
    d2 = 1234.5;
    d3 = 4.2e-10;
    std::cout << "default: " << d1 << ' ' << d2 << ' ' << d3 << ' ' << std::endl;
    std::cout << "fixed: " << std::fixed << d1 << ' ' << d2 << ' ' << d3 << ' ' << std::endl;
    std::cout << "scientific: " << std::scientific << d1 << ' ' << d2 << ' ' << d3 << ' ' << std::endl;
    std::cout << "set precision (3): " << std::setprecision(3) << std::fixed << d1 << ' ' << d2 << ' ' << d3 << ' ' << std::endl;
    std::cout << "scientific (7): " << std::setprecision(7) << std::scientific << d1 << ' ' << d2 << ' ' << d3 << ' ' << std::endl;
    std::cout.unsetf(std::ios_base::floatfield);
    std::cout << "default: " << d1 << ' ' << d2 << ' ' << d3 << ' ' << std::endl << std::endl;
    
    // string formatting options
    std::string ss1 = "This is a string.";
    std::string ss2 = "This is a much longer string.";
    std::string ss3 = "Today's news: Big Light in Sky Slated to Appear in East";
    
    std::cout << ss1 << std::endl;
    std::cout << ss2 << std::endl;
    std::cout << ss3 << std::endl;
    
    std::cout << std::setw(64) << std::right << ss1 << std::endl;
    std::cout << std::setw(64) << std::right << ss2 << std::endl;
    std::cout << std::setw(64) << std::right << ss3 << std::endl;
    
    std::cout << std::setfill('-') << std::setw(64) << std::right << ss1 << std::endl;
    std::cout << std::setfill(' ') << std::setw(64) << std::right << ss1 << std::endl;
    std::cout << std::left << ss1 << std::endl;

// Handling exception
    std::cout << "Exception Demo: " << std::endl;
    std::cout << "let's have an emergency!" << std::endl;
    // broken1(); // code will keep running and system will throw exception 9 etc.
    // Use try catch with  std::exception
    try {
        broken1();
    }
    catch (std::exception & e) {
        std::cout << e.what() << std::endl;
    }
    // Use try catch with inherited exception 
    try {
        broken2();
    }
    catch (BW::E & e) {
        std::cout << e.what() << std::endl;
    }

// Challenge work
    static const char * filename1 = "items.txt";   
    // read a file
    static char in_buffer[128];
    // cout << "read the file:" << endl;
    std::ifstream infile1(filename1);
    while (infile1.good()) {
        infile1.getline(in_buffer, sizeof(in_buffer));
        // cout << in_buffer << endl;
        size_t pos1 = std::string(in_buffer).find("\t");
        size_t pos2 = std::string(in_buffer).rfind("\t");

        // cout << pos << endl;
        item i1 = {stoi(std::string(in_buffer).substr(0,pos1)), std::string(in_buffer).substr(pos1+1,pos2-1), std::string(in_buffer).substr(pos2+1,-1)};
        std::cout <<"SKU: "<< i1.sku << "\t" << "NAME: " << i1.name << "\t"<<"DESC: "<< i1.desc<< std::endl;
        // cout << pos << endl;
    }
    infile.close();

    return 0;
}
