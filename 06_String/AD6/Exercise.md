# Exercise

After this video, we will implement a feature to load in *recorded* data of a test drive of our fictional autonomous car.  
For that, we will read in JSON files.  
To be able to read in the files, update the code from the refactoring video:

- Add the argc, \*\*argv to the main function such that the user can input the data path, inside the data path the following files should be
  - *ego_data* file
  - *vehicle_data* file
- If the user does not provide the data path just assume that these files are relative to the main file
  - *./data/ego_data.json*
  - *./data/vehicle_data.json*

Note:

In this exercise, we will only update the *main.cc* file.  
For the file paths, use the *filesystem* library.
