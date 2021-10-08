# Instructions for running tests.

In addition to testing for correct output data, the autotest system will
check your program and its source code for the style:

* **Style tests.** To check how much the beauty of your code matches
  for example, you can test your code using the script ```materials/linters/cpplint.py```. 
  The ```materials/linters``` folder also contains the ```CPPLINT.cfg``` file, which contains 
  the necessary filters-settings for the style test. The script works in such a way that this 
  configuration file extends its action to all files that lie with it in the directory 
  or in the directories below. So in order for these settings to apply to your source code files, 
  copy ```CPPLINT. cfg``` to the ```src``` folder. \
  \
  To run the script, run the following command: \
  ```python3 materials/linters/cpplint.py --extensions=c src/sourcefile_name.c``` \
  \
  Important! To run, you need python version 3. Check the installed version on
  you can download the version using the command ```python3 --version```. 
  To download python3, enter one of the following commands in the terminal: \
  ```brew install python3``` \
  or if you have root rights (for Ubuntu / Linux Mint / Debian) \
  ```sudo apt install python3```

* Also, be very careful with memory leaks! The testing system checks for this as well.