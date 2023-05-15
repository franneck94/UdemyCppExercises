#ifndef STR_UTILS_H
#define STR_UTILS_H

bool is_upper_case(char character)
{
    if ((character >= 'A') && (character <= 'Z'))
    {
        return true;
    }

    return false;
}

bool is_lower_case(char character)
{
    if ((character >= 'a') && (character <= 'z'))
    {
        return true;
    }

    return false;
}

bool is_numeric(char character)
{
    if ((character >= '0') && (character <= '9'))
    {
        return true;
    }

    return false;
}

bool is_alpha(char character)
{
    if (is_upper_case(character) || is_lower_case(character))
    {
        return true;
    }

    return false;
}

bool is_alpha_numeric(char character)
{
    return is_numeric(character) || is_alpha(character);
}

char to_upper_case(char character)
{
    if (is_lower_case(character))
    {
        return character - 32;
    }

    return character;
}

char to_upper_case_(char character)
{
    if (is_lower_case(character))
    {
        return character - 32;
    }

    return character;
}

char to_lower_case(char character)
{
    if (is_upper_case(character))
    {
        return character + 32;
    }

    return character;
}

char to_lower_case_(char character)
{
    if (is_upper_case(character))
    {
        return character + 32;
    }

    return character;
}

#endif
