#include "MyString.h"



int main() {

    using std::cout;
    using std::endl;

    String str =  ("Hello big fella");
    String str2 = ("Isogood");
    // String str3('B', 10);

    // str = str + str2 + str3;
    str.Print();

    // str.Erase(2, 6);
    str.Append(str2, 0, 7);
    str.Print();

    const char* string = str.C_str();

    cout << "string = " << string << endl;
    // delete [] string;
    std::cout << str.Substr(str.Find("d", 1));

    return 0;
}