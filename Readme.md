# Computer Graphics HW2 - Curtis Covington

`bin/hw2.exe` is the make output

Entry point `src/main.cpp`

Shaders are in the shaders folder.

`make` will compile the executable into the bin folder

`make run` should compile and run the program

`make clean` will clean the project structure

# Shaders

fullscreen.frag.glsl - Was used for a bunch of experiments rending on a single quad.

# Experiements

I played with serveral different noise function implementions until I found one I was happy with.

One of the biggest surprises for me was seeing no performance hit at all when looping through setting colors, I assume this was a compiler optimization. The second I added an if statement in I dropped from 160fps to about 5fps.

I was able to improve results by playing with the step function. 

I wanted to play with using the output of the fragment shader to do more cool things that I could benchmark but ran out of time.

Biggest takeaway from this was in utilizing the step function over using an if statement.


# Controls

Space = Toggle Perspective and Orthographic

Tab = Cycle Through Shaders

Arrow Keys or WASD = Movement
QE                 = Move Camera Up/Down

Right Click and Mouse Move = Camera Movement

Escape             = Close Program
