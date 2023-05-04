#include <iostream>
#include <cmath>
#include <cstring>
#include <cctype>

///$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$///

class String {
//---------------------------------------------------------------------------------------//
private:
    char* string;
    size_t size;
public:
//---------------------------------------------------------------------------------------//
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

    ///(1) Concatenation:
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

    ///(2)Copying:
    String & operator = (String copy) {

        std::cout << "Called operator (=)" << this << std::endl;

        Swap(copy);
        return *this;
    }

    void Swap(String copy) {
        std::swap(size, copy.size);
        std::swap(string, copy.string);
    }

    ///(3)Comparison:
    bool operator == (const String & tocomp) {
        
        if (size != tocomp.size) {
            return false;
        }

        for (size_t ch_position = 0; ch_position < size; ++ch_position) {
            if (string[ch_position] != tocomp.string[ch_position]) {
                return false;
            }
        }

        return true;
    }

    bool operator != (const String & tocomp) {

        if (size != tocomp.size) {
            return true;
        }

        for (size_t ch_position = 0; ch_position < size; ++ch_position) {
            if (string[ch_position] != tocomp.string[ch_position]) {
                return true;
            }
        }
        return false;
    }

    bool operator < (const String & tocomp) {

        size_t ch_position = 0;
        for ( ; string[ch_position] && tocomp.string[ch_position]; ++ch_position) {
            if (string[ch_position] < tocomp.string[ch_position]) {
                return true;
            }
            else if (string[ch_position] > tocomp.string[ch_position]) {
                return false;
            }
        }

        if(!string[ch_position]) {
            if (tocomp.string[ch_position]) {
                return true;
            }
            return false;
        }

        return false;
    }

    bool operator <= (const String & tocomp) {

        size_t ch_position = 0;
        for ( ; string[ch_position] && tocomp.string[ch_position]; ++ch_position) {
            if (string[ch_position] <= tocomp.string[ch_position]) {
                return true;
            }
            else {
                return false;
            }
        }

        if(!string[ch_position]) {
            return true;
        }

        return false;
    }

    bool operator > (const String & tocomp) {

        size_t ch_position = 0;
        for ( ; string[ch_position] && tocomp.string[ch_position]; ++ch_position) {
            if (string[ch_position] > tocomp.string[ch_position]) {
                return true;
            }
            else if (string[ch_position] < tocomp.string[ch_position]) {
                return false;
            }
        }

        if(!string[ch_position]) {
            return false;
        }

        return true;
    }

    bool operator >= (const String & tocomp) {

        size_t ch_position = 0;
        for ( ; string[ch_position] && tocomp.string[ch_position]; ++ch_position) {
            if (string[ch_position] >= tocomp.string[ch_position]) {
                return true;
            }
            return false;
        }

        if(!string[ch_position]) {
            if (tocomp.string[ch_position]) {
                return false;
            }
            return true;
        }

        return true;
    }
//--------------------------------------------------------------------------------------------//
//---------------------------------------String manipulations---------------------------------//
    ///Resize (1)
    void Resize(size_t new_size) {

        String copy = *this;
        delete [] string;

        string = new char[new_size + 1];
        size   = new_size;
        
        if (size <= copy.size) {
            std::copy(copy.string, copy.string + size, string);
            string[new_size] = '\0';

        } else {
            std::copy(copy.string, copy.string + copy.size, string);
            string[copy.size] = '\0';

        }

    }

    ///Resize (2)
    void Resize(size_t new_size, char symb) {

        String copy = *this;
        delete [] string;

        string = new char[new_size + 1];
        size   = new_size;
        
        if (size <= copy.size) {
            std::copy(copy.string, copy.string + size, string);

        } else {
            std::copy(copy.string, copy.string + copy.size, string);
            memset(string + copy.size, symb, sizeof(char) * (new_size - copy.size));
        }
        string[new_size] = '\0';

    }

    void PushBack(char symb) {

        String copy = *this;
        delete [] string;

        ++size;
        string = new char[size + 1];
        std::copy(copy.string, copy.string + copy.size, string);
        string[copy.size] = symb;
        string[size]      = '\0';

    }

    String & Erase(size_t delete_id, size_t count) {

        if (delete_id >= size) {
            std::cout << "Can't do 'erase' method: index of erasing is out of range:" << delete_id << "\nsize = " << 
            size << std::endl;
            return *this;
        }

        size_t deleted_size = count - delete_id + 1;
        size_t final_size   = size - deleted_size;

        if (count >= size) { 
            memset(string + delete_id, '\0', sizeof(char)*(size - delete_id));  
            size = delete_id;
        } else if (count < delete_id) {
            std::cout << "invalid second operator: " << count << std::endl;
        } else {
            String copy = *this;
            delete [] string;
            string = new char[final_size + 1];

            std::copy(copy.string, copy.string + delete_id, string);
            std::copy(copy.string + (count + 1), copy.string + size, string + delete_id);

            string[final_size] = '\0';
            size = final_size;
        }
        
        return *this;
    }

    ///Append (1)
    String & Append(int count, char symb) {

        String copy = *this;
        delete [] string;

        string = new char[size + count + 1];

        std::copy(copy.string, copy.string + size, string);
        memset(string + size, symb, sizeof(char)*count);

        size += count;
        string[size] = '\0';

        return *this;
    }

    ///Append (2.1)
    String & Append(const char* other) {

        if (!other || other[0] == '\0') {
            return *this;
        }

        String copy = *this;
        delete [] string;

        size_t other_len = strlen(other);
        string = new char[size + other_len + 1];

        std::copy(copy.string, copy.string + size, string);
        std::copy(other, other + other_len, string + size);

        size += other_len;
        string[size] = '\0';

        return *this;
    }

    ///Append (2.2)
    String & Append(const String & other) {

        if (!other.string || other.string[0] == '\0') {
            std::cout << "\nString is empty :(\n" << std::endl;
            return *this;
        }

        String copy = *this;
        delete [] string;

        string = new char[size + other.size + 1];

        std::copy(copy.string, copy.string + size, string);
        std::copy(other.string, other.string + other.size, string + size);

        size += other.size;
        string[size] = '\0';

        return *this;
    }

    ///Append (3)
    String & Append(const String & other, size_t pos, size_t count) {

        if (!other.string || other.string[0] == '\0') {
            std::cout << "\nstring is empty :(\n" << std::endl;
            return *this;
        }
   
        if (pos > count) {
            std::cout << "can't append symbs, invalid pos = " << pos << " and count = " << count << std::endl;
            return *this;
        }
        if (pos >= other.size) {
            std::cout << "invalid pos = " << pos << "; other.size = " << other.size << std::endl;
            return *this;
        }

        size_t appended_size = 0;
        if (count >= other.size) {
            appended_size = other.size - pos;
            count = other.size;
        } else {
            appended_size = count - pos;
        }

        String copy = *this;
        delete [] string;

        string = new char[size + appended_size + 1];

        std::copy(copy.string, copy.string + size, string);
        std::copy(other.string + pos, other.string + count, string + size);

        size += appended_size;
        string[size] = '\0';

        return *this;
    }

    ///Substr (1)
    char* Substr(size_t pos, size_t count) {

        if (pos > count) {
            std::cout << "\ncan't append symbs, invalid pos = " << pos << " and count = " << count << std::endl;
            return nullptr;
        }
        if (pos >= size) {
            std::cout << "\ninvalid pos = " << pos << "; size = " << size << std::endl;
            return nullptr;
        }

        char* ret_string   = nullptr;
        size_t lim_to_copy = 0;
        size_t string_size = 0;

        if (count >= size) {
            ret_string  = new char[size - pos + 1];
            string_size = size - pos;
            lim_to_copy = size; 
        } else {
            ret_string  = new char[count - pos + 1];
            string_size = count - pos;
            lim_to_copy = count;
        }

        std::copy(string + pos, string + lim_to_copy, ret_string);
        ret_string[string_size] = '\0';

        return ret_string;
    }


    char& operator [] (int index) {
        if (index < 0 || index >= (int)size) {
            std::cout << "invalid index id: " << index << std::endl;
        }
        return string[index];
    }


    void Clear() {
        memset(string, '\0', sizeof(char) * size);
    }

    bool Empty() {
        return size == 0 ? true:false;
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
        for (size_t ch_number = 0; ch_number < size; ++ch_number) {
            if (islower(string[ch_number])) {
                string[ch_number] = toupper(string[ch_number]);
            }
        }
    }

    void ToLower() {
        for (size_t ch_number = 0; ch_number < size; ++ch_number) {
            if (isupper(string[ch_number])) {
                string[ch_number] = tolower(string[ch_number]);
            }
        }
    }

    int IsEqual(const String & tocomp) {

        if (size != tocomp.size) {
            return 0;
        }

        for (size_t ch_number = 0; ch_number < size; ++ch_number) {
            if (string[ch_number] != tocomp.string[ch_number]) {
                return string[ch_number] - tocomp.string[ch_number];
            }
        }

        return 1;
    }

    void Print() {
        std::cout << string << std::endl;
    }

    size_t Size() {
        return size;
    }

    ~String() {
        std::cout << "\nCalled destructor:  " << this << std::endl;
        delete [] string;
    }
};
///$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$///
