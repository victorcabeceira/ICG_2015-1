all:

	g++ -o prog main1.cpp camera.cpp math_3d.cpp ogldev_util.cpp pipeline.cpp ogldev_texture.cpp technique.cpp lighting_technique.cpp mesh.cpp -W -Wall -pedantic -ansi -lGL -lGLU -lSDL2 -lGLEW -lSDL2_image 
