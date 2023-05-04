#include "MyString.h"



int main() {

    using std::cout;
    using std::endl;

    String str =  ("Hello");
    String str2 = ("");
    // String str3('B', 10);

    // str = str + str2 + str3;
    str.Print();

    str.Erase(2, 6);
    str.Append(str2);
    str.Print();

    return 0;
}