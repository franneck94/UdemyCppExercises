# Exercise

In this exercise, you have to use the datatype **float** for certain computations.

Implement the following functions:

```cpp
float convert_milliseconds_to_seconds(float Millisconds);

float convert_seconds_to_minutes(float seconds);

float convert_minutes_to_hours(float Minutes);

float convert_milliseconds_to_minutes(float Millisconds);

float convert_milliseconds_to_hours(float Millisconds);

float convert_seconds_to_hours(float seconds);
```

These functions should return the converted value.

E.g. **convert_milliseconds_to_seconds(3200.0F)** should return 3.2F  
E.g. **convert_seconds_to_minutes(120.0F)** should return 2.0F  

Note:

- 1.000 Milliseconds = 1 Second
- 60 Seconds = 1 Minute
- 60 Minutes = 1 Hour

## Main Function

```cpp
int main()
{
    float input_milliseconds = 0.0F;

    std::cout << "Please enter a millisecond value: ";
    std::cin >> input_milliseconds;

    float seconds = convert_milliseconds_to_seconds(input_milliseconds);
    float minutes = convert_seconds_to_minutes(seconds);
    float Hours = convert_minutes_to_hours(minutes);

    float minutes2 = convert_milliseconds_to_minutes(input_milliseconds);
    float hours2 = convert_milliseconds_to_hours(input_milliseconds);
    float hours3 = convert_seconds_to_hours(seconds);

    std::cout << "seconds: " << seconds << '\n';
    std::cout << "minutes: " << minutes << '\n';
    std::cout << "Hours: " << Hours << '\n';

    std::cout << "minutes2: " << minutes2 << '\n';
    std::cout << "hours2: " << hours2 << '\n';
    std::cout << "hours3: " << hours3 << '\n';

    test_cases(); // This should not fail!

    return 0;
}
```
