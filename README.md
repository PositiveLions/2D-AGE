2D-AGE
======

2D Allegro Game Engine

This project aims to be a complete set of building blocks to create
2D games independent of genre.  So far 2D-AGE only supports tilemaps.




Project built with TDM-GCC version of MinGW


Configure Code::Blocks
======================
Project > Build Options

Under project-wide build options click on the "Search directories" tab

Under the "Compiler" tab add the path to the allegro include directory
Under the "Linker" tab add the path to the allegro lib directory

Under Debug build options click on the "Linker settings" tab

Link the following libraries:
	liballegro-5.0.8-mt-debug.a
	liballegro_image-5.0.8-mt-debug.a
	liballegro_font-5.0.8-mt-debug.a
	liballegro_ttf-5.0.8-mt-debug.a

Under Release build options click on the "Linker settings" tab

Link the following libraries:
	liballegro-5.0.8-mt.a
	liballegro_image-5.0.8-mt.a
	liballegro_font-5.0.8-mt.a
	liballegro_ttf-5.0.8-mt.a

Click OK

Project > Properties

For build target "Debug" change the "Execution working dir" to "bin\Debug"
For build target "Release" change the "Execution working dir" to "bin\Release"

Click OK

Copy the following files from the allegro bin directory to your projects
bin\Debug directory:
	allegro-5.0.8-mt-debug.dll
	allegro_image-5.0.8-mt-debug.dll
	allegro_font-5.0.8-mt-debug.dll
	allegro_ttf-5.0.8-mt-debug.dll

Copy the following files from the allegro bin directory to your projects
bin\Release directory:
	allegro-5.0.8-mt.dll
	allegro_image-5.0.8-mt.dll
	allegro_font-5.0.8-mt.dll
	allegro_ttf-5.0.8-mt.dll

The project should now compile and run
====================================================