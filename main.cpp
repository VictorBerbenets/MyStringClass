#include "MyString.h"



int main() {

    using std::cout;
    using std::endl;

    String str =  ("Hello");
    String str2 = ("Isogood");
    // String str3('B', 10);

    // str = str + str2 + str3;
    str.Print();

    // str.Erase(2, 6);
    str.Append(str2, 1, 6);
    str.Print();

    char* string = str.Substr(0, 6);

    cout << "string = " << string << endl;
    delete [] string;

    return 0;
}