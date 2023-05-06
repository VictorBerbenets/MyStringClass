#include <iostream>
#include <cmath>
#include <cstring>
#include <cctype>

///$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$///

class String {
//---------------------------------------------------------------------------------------//
private:
    size_t size;
    char* string;
public:
//-------------------------------------Constructos---------------------------------------//
    String(): size(0), string(nullptr) {}

    //initializer list(1)
    String(size_t size, char symb): size(size), string(new char[size + 1]) {
        memset(string, symb, sizeof(char)*size);
        string[size] = '\0';
    }

    //delegating constructor
    String(const char* string): String(strlen(string), '\0') {   
        std::copy(string, string + strlen(string), this->string);
    }

    //initializer list(2)
    String(std::initializer_list<char> list) {
        size   = list.size();
        string = new char[size + 1];

        std::copy(list.begin(), list.end(), string);
        string[size] = '\0';
    }

    String(const String & copy): String(copy.size, '\0') {
        std::copy(copy.string, copy.string + copy.size, string);
    }
//----------------------------------Ariphmetic operations----------------------------------//

    ///(1) Concatenation:
    String& operator+=(const String & other) {

        String copy = *this;
        delete [] string;

        size   = size + other.size;
        string = new char[size + 1];

        std::copy(copy.string, copy.string + copy.size, string);
        std::copy(other.string, other.string + other.size, string + copy.size);

        string[size] = '\0';

        return *this;
    }

    String& operator+=(const char & symb) {

        String copy = *this;
        delete [] string;

        ++size;
        string = new char[size + 1];

        std::copy(copy.string, copy.string + copy.size, string);

        string[size - 1] = symb;
        string[size]     = '\0';

        return *this;
    }

    String operator+(const char & symb) {
        String result = *this;
        result += symb;
        return result;
    }

    ///(2)Copying:
    String & operator=(String copy) {

        std::cout << "Called operator (=)" << this << std::endl;

        Swap(copy);
        return *this;
    }

    void Swap(String copy) {
        std::swap(size, copy.size);
        std::swap(string, copy.string);
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

    ///Substr (2)
    char* Substr(size_t pos) {

        if (pos >= size) {
            std::cout << "\ninvalid pos = " << pos << "; size = " << size << std::endl;
            return nullptr;
        }

        char* ret_string = nullptr;
        ret_string  = new char[size - pos + 1];

        std::copy(string + pos, string + size, ret_string);
        ret_string[size - pos] = '\0';

        return ret_string;
    }


    size_t Find(const char* str, size_t pos = 0) {

        size_t npos = -1;
        if (!str) {
            return npos;
        }
        
        size_t str_size = strlen(str);

        for (size_t ch_id1 = pos; ch_id1 < size; ++ch_id1) {
            if (string[ch_id1] == str[0]) {
                size_t save_id1 = ch_id1; 
                size_t ch_id2   = 0;
                while(ch_id1 < size && ch_id2 < str_size && string[ch_id1] == str[ch_id2]) {
                    ++ch_id1;
                    ++ch_id2;
                }
                if (str[ch_id2] == '\0') {
                    return save_id1;
                } else {
                    ch_id1 = save_id1;
                }
            } 
            
        }

        return npos;
    }


    const char& operator [] (int index) const {
        if (index < 0 || index >= (int)size) {
            std::cout << "invalid index id: " << index << std::endl;
        }
        return string[index];
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

    size_t Size() const {
        return size;
    }


    void SetSize(size_t size);
    char GetChar(size_t elem_id) const;

    const char* C_str() {
        return this->string;
    }

    ~String() {
        std::cout << "\nCalled destructor:  " << this << std::endl;
        delete [] string;
    }
};
///$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$///



//------------------------------------------------Compare methods realization------------------------------------------------//

String operator+(const String & left_object, const String & right_object) {

    String result = left_object;
    return result += right_object;
}

bool operator==(const String & left_object, const String & right_object) {
    if (left_object.Size() != right_object.Size()) {
        return false;
    }

    size_t max_ch_position = left_object.Size();
    for (size_t ch_position = 0; ch_position < max_ch_position; ++ch_position) {
        if (left_object.GetChar(ch_position) != right_object.GetChar(ch_position)) {
            return false;
        }
    }

    return true;
}

bool operator!=(const String & left_object, const String & right_object) {
    return !(left_object == right_object);
}


bool operator<(const String & left_object, const String & right_object) {

    size_t ch_position = 0;
    for ( ; left_object.GetChar(ch_position) && right_object.GetChar(ch_position); ++ch_position) {
        if (left_object.GetChar(ch_position) < right_object.GetChar(ch_position)) {
            return true;
        }
        else if (left_object.GetChar(ch_position) > right_object.GetChar(ch_position)) {
            return false;
        }
    }

    if(!left_object.GetChar(ch_position)) {
        if (right_object.GetChar(ch_position)) {
            return true;
        }
        return false;
    }

    return false;
}

bool operator>(const String left_object, const String & right_object) {
    return right_object < left_object;
}

bool operator<=(const String left_object, const String & right_object) {

    size_t ch_position = 0;
    for ( ; left_object.GetChar(ch_position) && right_object.GetChar(ch_position); ++ch_position) {
        if (left_object.GetChar(ch_position) <= right_object.GetChar(ch_position)) {
            return true;
        }
        else {
            return false;
        }
    }

    if(!left_object.GetChar(ch_position)) {
        return true;
    }

    return false;
}


bool operator>=(const String left_object, const String & right_object) {
    return right_object <= left_object;
}
//----------------------------------------------------------------------------------------------------------------//

//-----------------------------------------Private methods--------------------------------------------------------//
void String::SetSize(size_t size) {
    this->size = size;
}

char String::GetChar(size_t elem_id) const {
    if (elem_id >= size) {
        std::cout << "invalid elem id: " << elem_id << "size = " << size << std::endl;
    }
    return string[elem_id];
}
//----------------------------------------------------------------------------------------------------------------//
