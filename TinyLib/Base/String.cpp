#include "String.h"


namespace tl
{
    /// @brief Create a new string from ascii array.
    /// @param newText C-style string.
    String::String(const ascii* newText)
    {
        create(newText);
    }


    /// @brief Create a new string from an unsigned number.
    /// @param num Unsigned number.
    String::String(u32 num)
    {
        create(numberToString(num).cStr());
    }


    /// @brief Create a new string from a signed number.
    /// @param num Signed number.
    String::String(s32 num)
    {
        create(numberToString(num).cStr());
    }


    /// @brief Clean up internal string data.
    String::~String()
    {
        if (text != nullptr)
        {
            delete[] text;
            text = nullptr;
        }
    }


    /// @brief Get length of this string.
    /// @return How many characters string contains.
    u16 String::length() const
    {
        return size;
    }


    /// @brief Get C-style string.
    /// @return Character array of this string.
    const ascii* String::cStr() const
    {
        return text;
    }


    /// @brief String copy method.
    /// @param other String to copy.
    String::String(const String& other)
    {
        size = other.size;
        text = new ascii[size + 1];

        for (u16 i = 0; i < size; i++) {
            text[i] = other.text[i];
        }

        text[size] = '\0';
    }


    /// @brief String assignment operator.
    /// @param other String to assign.
    String& String::operator=(const String& other)
    {
        // Check if this is a self-assignment.
        if (this != &other) {
            delete[] text;

            size = other.size;
            text = new ascii[size + 1];

            for (u16 i = 0; i < size; i++) {
                text[i] = other.text[i];
            }

            text[size] = '\0';
        }
        return *this;
    }


    /// @brief Add two strings together.
    /// @param other This string will go after the current string.
    /// @return Both strings combined into one.
    String String::operator+(String other)
    {
        u16 newSize = size + other.length();
        ascii* newString = new ascii[newSize + 1];

        for (u16 i = 0; i < size; i++) {
            newString[i] = text[i];
        }

        for (u16 i = 0; i < other.length(); i++) {
            newString[size + i] = other.text[i];
        }

        newString[newSize] = '\0';

        String result;
        result.size = newSize;
        result.text = newString;

        return result;
    }

    
    /// @brief Quick way to add another string onto this one.
    /// @param other This string will go after the current string.
    void String::operator+=(String other)
    {
        // Set current string to result of addition.
        *this = operator+(other);
    }


    /// @brief Add number onto string.
    /// @param num This number will go after the current string.
    /// @return New string with number added.
    String String::operator+(s32 num)
    {
        return operator+(numberToString(num));
    }


    /// @brief Quick way to add a number onto this string.
    /// @param num This number will go after the current string.
    void String::operator+=(s32 num)
    {
        *this = operator+(num);
    }


    /// @brief Add number onto string.
    /// @param num This number will go after the current string.
    /// @return New string with number added.
    String String::operator+(u32 num)
    {
        return operator+(numberToString(num));
    }


    /// @brief Quick way to add a number onto this string.
    /// @param num This number will go after the current string.
    void String::operator+=(u32 num)
    {
        *this = operator+(num);
    }


    /// @brief Internal method to convert number to string.
    /// @tparam T This should be a number type.
    /// @param num Number to convert to a string.
    /// @return String of number.
    template <typename T>
    String String::numberToString(T num)
    {
        // Size 12 can hold: -2147483648 and null terminator
        ascii numberStr[12];

        wsprintf(numberStr, "%d", num);

        return String(numberStr);
    }


    /// @brief Create internal string data.
    /// @param newText C-style string to copy into data.
    void String::create(const ascii* newText)
    {
        // Calculate size.
        u16 newSize = 0;
        while (newText[newSize] != '\0' && newSize < 0xFFFF)
            newSize++;

        // +1 for null terminator.
        text = new ascii[newSize + 1];

        // Copy each character over.
        for (u16 i = 0; i < newSize; i++)
            text[i] = newText[i];

        text[newSize] = '\0';
        size = newSize;
    }
}