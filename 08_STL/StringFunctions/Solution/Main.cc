#include <cassert>
#include <iostream>
#include <string>

#include "lib.h"

void test_cases();

int main()
{
    std::string str1 = "anna";
    std::cout << std::boolalpha << str1
              << " is_palindrom: " << mystd::is_palindrom(str1) << '\n';

    std::string str2 = "JanIstHier";
    std::cout << std::boolalpha << str2
              << " starts w/ Jan = " << mystd::starts_with(str2, "Jan") << '\n';
    std::cout << std::boolalpha << str2
              << " starts w/  Ja = " << mystd::starts_with(str2, "Ja") << '\n';
    std::cout << std::boolalpha << str2
              << " starts w/  ja = " << mystd::starts_with(str2, "ja") << '\n';

    std::string str3 = "JanWarHier";
    std::cout << std::boolalpha << str3
              << " ends w/ Hier = " << mystd::ends_with(str3, "Hier") << '\n';
    std::cout << std::boolalpha << str3
              << " ends w/ Hie = " << mystd::ends_with(str3, "Hie") << '\n';
    std::cout << std::boolalpha << str3
              << " ends w/ Hir = " << mystd::ends_with(str3, "Hir") << '\n';

    std::string str4 = "JanWarHier";
    std::cout << std::boolalpha << str4
              << " contains: Hier = " << mystd::contains(str4, "Hier") << '\n';
    std::cout << std::boolalpha << str4
              << " contains: War = " << mystd::contains(str4, "War") << '\n';
    std::cout << std::boolalpha << str4
              << " contains: jan = " << mystd::contains(str4, "jan") << '\n';

    std::string str5 = "HalloHallohaHallo";
    std::cout << "occurences: " << mystd::num_occurences(str5, "Hallo") << '\n';

    test_cases();

    return 0;
}

void test_cases()
{
    assert(mystd::is_palindrom("anna") == true);
    assert(mystd::is_palindrom("aNna") == false);

    assert(mystd::ends_with("anna", "a") == true);
    assert(mystd::ends_with("anna", "na") == true);
    assert(mystd::ends_with("anna", "ann") == false);

    assert(mystd::starts_with("anna", "a") == true);
    assert(mystd::starts_with("anna", "na") == false);
    assert(mystd::starts_with("anna", "ann") == true);

    assert(mystd::contains("anna", "ann") == true);
    assert(mystd::contains("anna", "nn") == true);
    assert(mystd::contains("anna", "nna") == true);
    assert(mystd::contains("anna", "ana") == false);

    assert(mystd::num_occurences("anna", "a") == 2);
    assert(mystd::num_occurences("anna", "n") == 2);
    assert(mystd::num_occurences("anna", "nn") == 1);
    assert(mystd::num_occurences("anna", "anna") == 1);
    assert(mystd::num_occurences("anna", "annaa") == 0);
}
