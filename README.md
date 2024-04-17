# <p align='center'>The-Maze-SDL</p>

    The Maze - ALX Portifolio Project

## Table of Contents
- [Introduction](#introduction)
- [Installation](#installation)
- [Usage](#usage)
- [Authors](#authors)
- [Licensing](#licensing)

# Introduction
While I was viewing my ideas for this project I came across The Maze project and at first I was intrigued to know what it talks about, and after further reasearch on it I was completely invested in the idea of implementing a raycaster even though it was a topic vastly beyond my knowledge.

This repository documents my attempts on tackling such a challenge and using all the resources available to finish it on time.

Check the project landing page [here](https://bebo-k-s.github.io/).

# Installation
As for installating and using program you'll first need to compile the program into an executable by using this command:

```
gcc header/* src/* -o maze -lSDL2
```

After compiling the program, now you can just run the executable by using this command & watch the magic happen:

```
./maze
```

Best used on Visual Studio 2022 for better experience!

# Usage
Now we have the program compiled and running what does the program offer? Well let me take you through the controls.

### Change View Direction
Being able to look around is always a blessing. This feature aids the player in being able to look around in the environment they're in. Keybinds:

1. `a`: Look towards the left.
2. `d`: Look towards the right.

<img src="imgs/Keybinds - A D.gif" alt="Show/Unshow Minimap" width="350">

### Movement!
Won't be a movement game without any movement features now would it? This feature allows the player the ability to walk forword or backword according to their preference. Keybinds:

1. `w`: Move forwards.
2. `s`: Move backwards.

<img src="imgs/Keybinds - W S.gif" alt="Show/Unshow Minimap" width="350">

### Show/Unshow Minimap
The maze is vast and navigating through it sometimes proves to be tuff, which is why having this feature eases navigation plus viewing the maze. Keybind:

1. `m`: Show/Unshow the minimap

Helps in viewing the whole maze and checking what lies beyond what the player can see and displays the rays shot from the player showing what is visible and what's not visible to the player. 

<img src="imgs/Keybinds - M.gif" alt="Show/Unshow Minimap" width="350">

### Change FOV
How about changing your field of view; well you can do that by clicking one of 2 buttons:

1. `[`: Increases the FOV.
2. `]`: Decreases the FOV.

How this is implemented is that it basically either increase or decrease the number of rays shot from the player onto the world, which simulates changing the field of view of the player.

<img src="imgs/Keybinds - [ ].gif" alt="Change Field of View" width="350">

<br>

# Authors
Abdulrahman Khaled (AK-Salah@outlook.com)

# MIT Licensing
Anyone is welcome to do as they please with the content of this project, only under the condition of mentioning me when it is used.