#include <stdbool.h>
#include <string.h>

bool amw_validate_luhn(const char *string)
{
    bool odd_digit = true;
    int i;
    unsigned int digit, sum = 0;

    for (i = (strlen(string) - 1); i >= 0; --i)
    {
        digit = string[i] - '0';
        sum += (odd_digit) ? digit : (digit / 5 + (2 * digit) % 10);
        odd_digit = !odd_digit;
    }

    return sum % 10 ? false : true;
}
