
ARQUIVOS
--------------------------------------------------

main1.cpp
CG.cpp / CG.h
camera.cpp / camera.h
math_3d.cpp
lighting.fs / lighting.vs
lighting_technique.cpp / lighting_technique.h
math_3d.cpp / math_3d.h
mesh.cpp / mesh.h
ogldev_math_3d.h
ogldev_texture.cpp / ogldev_texture.h
ogldev_types.h
ogldev_util.cpp / ogldev_util.h
pipeline.cpp / pipeline.h
shader.cpp / shader.fs / shader.vs
technique.cpp / technique.h
vec.h

README.txt
Doxyfile

mapa.obj
nave.obj


INSTRU��ES
--------------------------------------------------
AS BIBLIOTECAS NECESS�RIAS S�O (A lib lGLEW deve ser add para utilizar o opengl3.x):
-lGL -lGLU -lSDL2 -lGLEW -lSDL2_image

COMPILANDO O PROJETO (LINUX)
----------------------------------------------------
Ser� gerado um execut�vel do projeto com o nome "prog"

make

EXECUTANDO O PROJETO (LINUX)
-----------------------------------------------------
optirun ./prog nomeArquivoObj
