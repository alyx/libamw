#include <stdio.h>
#include <stdbool.h>

extern bool amw_validate_luhn(const char *string);

int main(void)
{
    const char* cc_numbers[] = {
        "49927398716",
        "49927398717",
        "1234567812345678",
        "1234567812345670",
        0
    };

    const char** cc_number;

    for (cc_number = cc_numbers; *cc_number; ++cc_number) {
        printf("%s = %d\n", *cc_number, amw_validate_luhn(*cc_number));
    }

    return 0;
}

