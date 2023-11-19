# UML Exercise

## Exercise

Implement the following class:

- AirConditioner

![alt](./../../media/uml.png)

Attributes:

- current_temp: float
  - Updated by the method *measure_data*
- target_temp: float
  - Default value is 20-degree celsius

Methods:

- measure: float
  - Updated the current temp, the value range is [-20, 45]
  - You can generate random values for this
- heat(int duration): bool
  - Triggered by the method *activate* if the curr_temp is below target_temp
  - Heating power: 1-degree celsius per 2 minutes
  - Method will print every minute the current temp
  - Returns true if the AC is heating
- cool(int duration): bool
  - Triggered by the method *activate* if the curr_temp is above target_temp
  - Cooling power: 1-degree celsius per 1 minute
  - Method will print every minute the current temp
  - Returns true if the AC is cooling
- activate(int curr_temp): int
  - calls *heat* or *cool* based on the current temp
  - Compute the time amount needed for cooling/heating and returns this value
  - The value range where the AC can work is [-20, 45], otherwise return -1 as an error state

Make sure that all tests in the main function succeed.
