# Exercise

Implement the following functions by using std::algorithms and lambda functions (except *compute_accelerations*):

```cpp
void compute_velocities(
    const std::array<float, NUM_ITERATIONS> long_velocities_mps,
    const std::array<float, NUM_ITERATIONS> lat_velocities_mps,
    std::array<float, NUM_ITERATIONS> &velocities_mps);

void compute_heading_degrees(
    const std::array<float, NUM_ITERATIONS> long_velocities_mps,
    const std::array<float, NUM_ITERATIONS> lat_velocities_mps,
    std::array<float, NUM_ITERATIONS> &heading_degrees);

void compute_accelerations(
    const std::array<float, NUM_ITERATIONS> &velocities_mps,
    std::array<float, NUM_ITERATIONS> &accelerations_mps2);

void compute_rel_velocities(
    const std::array<float, NUM_ITERATIONS> &velocities_mps,
    const std::array<float, NUM_ITERATIONS> &ego_velocities_mps,
    std::array<float, NUM_ITERATIONS> &rel_velocities_mps);

void compute_rel_accelerations(
    const std::array<float, NUM_ITERATIONS> &accelerations_mps2,
    const std::array<float, NUM_ITERATIONS> &ego_accelerations_mps2,
    std::array<float, NUM_ITERATIONS> &rel_accelerations_mps2);
```

## Velocity

To compute the general velocity we can use the lateral and long. velocity:  
$v = \sqrt{v_{lat}^2 + v_{long}^2}$

## Heading Degree

To compute the heading degree we can use the following formula:  
$d = \frac{\arctan2(v_{lat}, v_{long})}{\pi} * 180$

Here is a small introduction to the vehicle heading: [link](http://street.umn.edu/VehControl/javahelp/HTML/Definition_of_Vehicle_Heading_and_Steeing_Angle.htm)  

## Acceleration

To estimate the acceleration we can use the current and previous velocity:  
$v_f$: Current velocity  
$v_i$: Previous velocity  
$t$: Time span between those two velocities (in our case it is 50ms)  
$a = \frac{v_{f} - v_{i}}{t}$

## Relative Velocity/Acceleration

This should be easy, no tips from my side ;)

## Main Function

```cpp
int main()
{
    const auto ego_velocities_mps = std::array<float, NUM_ENTRIES>{25.0F, 25.6F, 26.2F};
    const auto ego_accelerations_mps2 = std::array<float, NUM_ENTRIES>{0.0F, 0.6F, 0.6F};

    const auto long_velocities_mps = std::array<float, NUM_ENTRIES>{23.0F, 25.0F, 27.0F};
    const auto lat_velocities_mps = std::array<float, NUM_ENTRIES>{1.0F, 1.2F, 1.1F};

    auto velocities_mps = std::array<float, NUM_ENTRIES>{};
    auto heading_degrees = std::array<float, NUM_ENTRIES>{};
    auto accelerations_mps2 = std::array<float, NUM_ENTRIES>{};
    auto rel_velocities_mps = std::array<float, NUM_ENTRIES>{};
    auto rel_accelerations_mps2 = std::array<float, NUM_ENTRIES>{};

    compute_velocities(long_velocities_mps, lat_velocities_mps, velocities_mps);
    compute_heading_degrees(long_velocities_mps, lat_velocities_mps, heading_degrees);
    compute_accelerations(velocities_mps, accelerations_mps2);
    compute_rel_velocities(long_velocities_mps, ego_velocities_mps, rel_velocities_mps);
    compute_rel_accelerations(accelerations_mps2, ego_accelerations_mps2, rel_accelerations_mps2);

    std::cout << "velocities_mps: \n";
    print_array(velocities_mps);
    std::cout << "heading_degrees: \n";
    print_array(heading_degrees);
    std::cout << "accelerations_mps2: \n";
    print_array(accelerations_mps2);
    std::cout << "rel_velocities_mps: \n";
    print_array(rel_velocities_mps);
    std::cout << "rel_accelerations_mps2: \n";
    print_array(rel_accelerations_mps2);
}
```
