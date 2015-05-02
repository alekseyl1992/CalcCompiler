#ifndef UTIL
#define UTIL

// reverses a string 'str' of length 'len'
void reverse(char *str, int len)
{
    int i=0, j=len-1, temp;
    while (i<j)
    {
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
        i++; j--;
    }
}

 // Converts a given integer x to string str[].  d is the number
 // of digits required in output. If d is more than the number
 // of digits in x, then 0s are added at the beginning.
int intToStr(int x, char str[], int d, int base)
{
    int i = 0;
    while (x)
    {
        int digit = x % base;

        if (digit < 10)
            str[i++] = '0' + digit;
        else
            str[i++] = 'A' + digit - 10;

        x = x/base;
    }

    // If number of digits required is more, then
    // add 0s at the beginning
    while (i < d)
        str[i++] = '0';

    reverse(str, i);
    str[i] = '\0';
    return i;
}

// Converts a floating point number to string.
void ftoa(float n, char *res, int afterpoint, int base)
{
    // Extract integer part
    int ipart = (int)n;

    // Extract floating part
    float fpart = n - (float)ipart;

    // convert integer part to string
    int i = intToStr(ipart, res, 1, base);

    // check for display option after point
    if (afterpoint != 0)
    {
        res[i] = '.';  // add dot

        // Get the value of fraction part upto given no.
        // of points after dot. The third parameter is needed
        // to handle cases like 233.007
        fpart = fpart * pow(base, afterpoint);

        intToStr((int)fpart, res + i + 1, afterpoint, base);
    }
}

std::string to_hex_str(float value) {
    constexpr int MAX_LENGTH = 1024;
    constexpr int PRECISION = 4;
    constexpr int BASE = 16;

    bool negative = value < 0;
    if (negative)
        value = -value;

    char res[MAX_LENGTH] = {0};
    ftoa(value, res, PRECISION, BASE);

    if (!negative)
        return std::string(res);
    else
        return std::string("-") + res;
}

#endif // UTIL

