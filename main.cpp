#include "MyString.h"


int main() {

    using std::cout;
    using std::endl;

    String str =  ("f");
    String str2 = ("");
    String str3('A', 10);
    
    str = str + str2 + str3;
    str.Print();
    

    str.Resize(0, 'c');
    str.Print();

    return 0;
}