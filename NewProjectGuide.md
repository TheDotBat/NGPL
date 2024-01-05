# Welcome To Nebula!

## This Document will act as a guide to getting you started with NDL.

## Pre-requisites: 
- An installation of the minGW32 GCC compiler. One can be downloaded in the NDL development kit via Nebula's (NDL's) github page: https:\\www.github.com\TheDotBat\NDL
- An installation of Windows Powershell. (If you are on Windows 8 > you should be good to go, just type "powershell" into your Windows search bar!)
---
---
---
# NDLore
- NDL was created to offer game developers a smooth, simple, and efficient way of construcing interactive experiences quickly.
- Taking large inspiration from the workflow of pygame-ce, combining that ease of use with the speed and optimization opportunities that come with C.
    - *"As a developer who started with a high-level language first, my first time compiling a program was rather annoying. So i decided to make it easier." - Setoichi*
- Something obvious that sets NDL apart from Pygame is the extensive toolchain. NDL offers a rich ECS with a simple to use Rendering API ontop of SDL2, and a fast effective Physics engine thats just as simple to play with.
- NDL ( as you could tell by the name ) is *Nebula's* Development Library... **Then who/what is Nebula?**

---
---
---
# **Lets Get Started!**

With that *tidbit* of library lore out of the way, lets start by setting up a basic example project that you can build off of!

---
- Configuration:
    - If you are working in VSCode, then i have provided a template c_cpp_properties file to help setup your workspace include path.
    - Simply navigate the ```config``` folder in the project directory generated with NewProject-NDL *projectName*, and drag the ```.vscode``` folder out into the root of your project
        - For example, if your project was named MyNDLProject:
            - The ```.vscode``` folder would be located at ```MyNDLProject\config\.vscode``` 
            - Move it to ```MyNDLProject\.vscode```
---
- First Steps:
    - Explain intial setup of an NDL project.

    - Explain utilizing custom headers and splitting up code.

    - Explain simple event handling with NDL_KEY and PlayerActions.

    - Explain *briefly* what is an ECS?

    - Explain *briefly* what is a PhysicsSystem and PhysicsSpace and how do they work?

    - Create Your First Entity!

    - Add some Tiles!

    - Explain *briefly* what is the RenderSystem and how does it work?

    - Adding sprite components!
