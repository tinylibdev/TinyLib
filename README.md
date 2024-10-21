# TinyLib

## What is this?
This is a C++ library that I'm working on based off of SFML. The end goal is that it'll match or outperform SFML/SDL in performance, while being much smaller in executable size and RAM usage. Right now it's in very, very early stages and has a long way to go. I'm making this public here as mostly a showcase of what I've been doing, but you can try it out if you're curious. 
TinyLib does not use any 3rd party libraries, nor does it use the standard library. I am redesigning everything from the ground up to be easy to use, and optimized.

## Future Development
For the next 0.1.x updates, I'll only add a few new small features. 0.1.x is mostly going to be focused on cleaning up and further bug fixing.  
For 0.2.0 I hope to have 100% Unix support to showcase the cross compatibility I hope to add with this library. 
Versions beyond this, I am not certain yet, but I do plan on adding features you would need often; Sprites/image support, audio support, network support, I hope to have them all in this library.

## How to use
There are a few basic examples of using the library at [TinyLib/_Info/Examples](https://github.com/tinylibdev/TinyLib/tree/main/TinyLib/_Info/Examples). There is also online documentation available [here](https://tinylibdev.github.io/Docs/0.1.0/).

## Setup
If you'd like to quickly get started with the library on Visual Studio, I have a template for it with optimal project configuration [here](https://github.com/tinylibdev/TinyLib/releases/download/0.1/TinyLibTemplate.zip).
#### Manual setup
If you'd like to set this up manually, you'll just need the TinyLib folder, downloadable [here](https://github.com/tinylibdev/TinyLib/releases/download/0.1/TinyLib.zip). Once unzipped you'll need a new Visual Studio project and you need to put the path to the TinyLib folder in these places:  
C/C++ -> General -> Additional Include Directories  
Linker -> General -> Additional Library Directories  
And you need to put the path to the TinyLib.lib in:  
Linker -> Input -> Additional Dependencies  

## Additional Configuration
TinyLib will use DirectX graphics by default, these use the GPU and will offer the best performance. If you instead want only CPU rendering or for the size to be even smaller, you can use GDI graphics by adding GDI_GRAPHICS to:  
C/C++ -> Preprocessor -> Preprocessor Definitions
