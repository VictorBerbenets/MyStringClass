#include "MyString.h"



int main() {

    using std::cout;
    using std::endl;

    String str("Hello big fella");
    String str2 = ("Isogood");
    String str3(10, 'B');

    String stroka{'A', 'B', 'C'};
    stroka.Print();
    stroka = str + str2;

    stroka.Print();

    return 0;
}