#include <iostream>
#include <cmath>
#include <cstring>
#include <cctype>

///$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$///

class String {
private:

    char* string;
    size_t size;
public:

    String() {
        std::cout << "Called 'empty' constructor: " << this << std::endl;

        string = nullptr;
        size   = 0;
    }

    String(char symb, size_t size) {
        std::cout << "Called 'char symb, size_t size' constructor: " << this << std::endl;

        this->size = size;
        string     = new char[size + 1];

        memset(string, symb, sizeof(char)*size);
        string[size] = '\0';
    }

    String(const char* string) {       
        std::cout << "Called 'const char* string' constructor: " << this << std::endl;

        size         = strlen(string);
        this->string = new char[size + 1];

        std::copy(string, string + size, this->string);
        this->string[size] = '\0';
    }


    String(const String & copy) {
        std::cout << "Called assignment operator: " << this << std::endl;


        string = new char[copy.size + 1];
        size   = copy.size;

        std::copy(copy.string, copy.string + size, string);
        string[size] = '\0';
    }

//----------------------------------Ariphmetic operations----------------------------------//

    ///*********************************Concatenation**************************************//
    String operator +(const String & other) {

        String result;
        result.size   = size + other.size;
        result.string = new char[result.size + 1];

        std::copy(string, string + size, result.string);
        std::copy(other.string, other.string + other.size, result.string + size);

        result.string[result.size] = '\0';

        return result;
    }

    String operator +=(const String & other) {

        String copy = *this;
        delete [] string;

        size   = size + other.size;
        string = new char[size + 1];

        std::copy(copy.string, copy.string + copy.size, string);
        std::copy(other.string, other.string + other.size, string + copy.size);

        string[size] = '\0';

        return *this;
    }

    String operator +(const char & symb) {

        String result;
        result.size   = size + 1;
        result.string = new char[result.size + 1];

        std::copy(string, string + size, result.string);

        result.string[result.size - 1] = symb;
        result.string[result.size ]    = '\0';

        return result;
    }

    String operator +=(const char & symb) {

        String copy = *this;
        delete [] string;

        ++size;
        string = new char[size + 1];

        std::copy(copy.string, copy.string + copy.size, string);

        string[size - 1] = symb;
        string[size]     = '\0';

        return *this;
    }

    ///*********************************Copying**************************************//
    String & operator = (String copy) {
        std::cout << "Called operator (=)" << this << std::endl;

        Swap(copy);
        return *this;
    }

    void Swap(String copy) {
        std::swap(size, copy.size);
        std::swap(string, copy.string);
    }


//--------------------------------------------------------------------------------------------//

    void Print() {
        std::cout << string << std::endl;
    }


    char& operator [] (int index) {
        if (index < 0 || index >= (int)size) {
            std::cout << "invalid index id: " << index << std::endl;
            
        }
        return string[index];
    }

    int Atoi() {

        if (size <= 0) {
            return 0;
        }

        int result   = 0;
        for (size_t ch_number = 0; ch_number < size; ++ch_number) {
            if (!isdigit(string[ch_number])) {
                return 0;
            }
            result += pow(10, size - ch_number - 1) * (string[ch_number] - '0');
        }
        return result;
    }

    void ToUpper() {
        for (size_t ch_number = 0; ch_number < size; ch_number++) {
            if (islower(string[ch_number])) {
                string[ch_number] = toupper(string[ch_number]);
            }
        }
    }

    void ToLower() {
        for (size_t ch_number = 0; ch_number < size; ch_number++) {
            if (isupper(string[ch_number])) {
                string[ch_number] = tolower(string[ch_number]);
            }
        }
    }

    int IsEqual(const String & tocomp) {

        if (size != tocomp.size) {
            return 0;
        }

        for (size_t ch_number = 0; ch_number < size; ch_number++) {
            if (string[ch_number] != tocomp.string[ch_number]) {
                return string[ch_number] - tocomp.string[ch_number];
            }
        }

        return 1;
    }

    size_t GetSize() {
        return size;
    }

    ~String() {
        std::cout << "\nCalled destructor:  " << this << std::endl;
        delete [] string;
    }
};

///$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$///
