#include "MyString.h"


int main() {

    using std::cout;
    using std::endl;

    String str = ("heyy ");
    cout << str.GetSize() << endl;

    str += "meeow";
    str.Print();
    cout << str.GetSize() << endl;

    int x = 6;
    int y = 7;

  
    return 0;
}