# Instructions for running tests.

In addition to testing for correct output data, the autotest system will check your program and its source code for the
following points:

* **Style tests.** To check how much the beauty of your code meets the standards, for example, you can test your code
  using the _clang-format_ utility. The ```materials/linters``` folder contains the ```.clang-format``` file, which
  contains the necessary settings for the style test. This configuration file extends its action to all files that lie
  with it in the directory or in the directories below. So in order for these settings to apply to your source code
  files, copy ```.clang-format``` to the ```src``` folder. \
  \
  To run the style check, run the following command: \
  ```clang-format -n src/sourcefile_name.c``` \
  \
  To download _clang-format_, enter one of the following commands in the terminal: \
  ```brew install clang-format``` \
  or if you have root rights (for Ubuntu / Linux Mint / Debian) \
  ```sudo apt install clang-format```

  Google Style: https://google.github.io/styleguide/cppguide.html


* **Test for correct operation with memory.** When writing C programs, it is very important to watch for memory leaks.
  To do this the _valgrind_ utility is quite often used in Unix-like operating systems. However, OS X has some troubles
  with _valgrind_ support, so it is possible to use the _leaks_ utility instead. We will not go into the mechanism of
  operation of these utilities now — if you are interested, you can read about it on Google.

  To run your executable file using this utility, type in the terminal: \
  ```leaks -atExit -- ./main.out | grep LEAK:```

  Pay your attention that there is ```| grep LEAK:``` command. We use it to short leaks output to see only lines with
  leaks if they are there. If you want to see the whole output, just remove this command.

  When you run your executable file using _leaks_ you may see an error:
  > dyld: could not load inserted library ‘/usr/local/lib/libLeaksAtExit.dylib’ because image not found

  It’s because _leaks_ did not find _libLeaksAtExit.dylib_ library. \
  You need to type the following commands in this case.
  ```sh
  cd /usr/local/lib  
  sudo ln -s /Applications/Xcode.app/Contents/Developer/usr/lib/libLeaksAtExit.dylib
  ```

  _Additionally:_  \
  Use the ```-exclude``` option of _leaks_ to filter out leaks in functions with known memory leaks. This option helps
  reduce the amount of extra information reported by _leaks_.

* **Build test.** The program can be checked for correct build on a test system environment. This will require _Docker_
  installed. If the system has a docker, then you can go to the `materials/build` directory and run the run.sh script
  from there. The script will wrap your solution in docker and run it along with a typical build script.
