docker login bestforyouregistryxuhongl.azurecr.io -u bestforyouregistryxuhongl

dBVIejp4/uLvusMcg2X0N1pGUWeFnoqn







---------------------------------------------------------------------------------------------------
The whole project is compiled successfully in visual studio express 2013, windows 8.1

This project use two different kinds of additional libraries: OpenGL and GLFW;

1)The GLFW library has already been put in this project folder so don't need other setting;

2)The OpenGL should be set up to your laptop:
--decompress the glutdlls37beta.zip

--Copy  glut.h to:
  C:\Program Files (x86)\Windows Kits\8.1\Include\um\gl

--Copy glut32.dll and glut.dll to:
   C:\Windows\SysWOW64

--Copy glut32.lib and glut.lib to:
   C:\Program Files (x86)\Microsoft Visual Studio 12.0\VC\lib
   
   P.S: if your visual studio is vs2013, the name in above path is Microsoft Visual Studio 12.0
        if your visual studio is vs2012, the name in above path is Microsoft Visual Studio 11.0
    
