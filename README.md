# DaisyC

Project code for Daisy the Cow in C++

![Daisy the cow game](https://github.com/ch1ru/DaisyC/blob/master/Media/cow_eyes_open.png)

Daisy the Cow is a program originally written in Java to help people learn to code. DaisyC is a revamp of the original Daisy the cow written in java over 20 years ago, ported to C++.

## Adding SDL2 Graphics Dependencies

**1.Add SDL2 include libraries**

In visual studio, navigate to Project > Properties > Configuration Properties > VC++ Directories > Include Directories
Add the location of the include directory (found in [deps](https://github.com/ch1ru/DaisyC/tree/master/deps)).

**2.Add SDL2 x86/x64 library directive**

In a below tab, add the library directory depending on your architecture (x86 seems to run more smoothly). You can find these in the [lib](https://github.com/ch1ru/DaisyC/tree/master/deps/lib) folder.

**3.Add additional SDL2 dependencies**

In Properties > Linker > Input > Additional Dependencies 
edit the tab and add the file names:
```
SDL2.lib
SDL2main.lib
```
