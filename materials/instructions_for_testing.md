# Instructions for running tests.

In addition to testing for correct output data, the autotest system will
check your program and its source code for the following points:

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


* **Test for correct operation with memory.** When writing C programs, it is very important to watch for memory leaks. To do this the _valgrind_ utility is quite often used in Unix-like operating systems. However OS X has some troubles with valgrind support, so it is possible to use _leaks_ utility instead. Go into we will not discuss the mechanism of their operation now - if you are interested, you can read about it on Google.

  To run your executable file using this utility, type in the terminal: \
  ```leaks -atExit -- ./main.out | grep LEAK:```  
  
  Pay your attention that there is ```| grep LEAK:``` command. We use it to short leaks output to see only lines with leaks if they are there. If you want to see the whole output, just remove this command.  
  
  When you run your executable file using _leaks_ you may see an error:  
  >dyld: could not load inserted library ‘/usr/local/lib/libLeaksAtExit.dylib’ because image not found
  
  It’s because _leaks_ did not find _libLeaksAtExit.dylib_ library. \
  You need to type the following commands in this case.   
  ```sh
  cd /usr/local/lib  
  sudo ln -s /Applications/Xcode.app/Contents/Developer/usr/lib/libLeaksAtExit.dylib
  ```

  _Additionally:_  \
  Use the ```-exclude``` option of _leaks_ to filter out leaks in functions with known memory leaks. 
  This option helps reduce the amount of extra information reported by _leaks_.
  
