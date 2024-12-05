*****************
* 3D rasterizer *
*****************

Building:
	$ make

Running:
	$ dtekv-run build/dtekv/rast.bin

Usage:
	* Use button to cycle models
	* Use switches to rotate/scale and change the lighting

Profiling (requires python):
	* Build with PROFILE_ENABLE=1:
		$ make PROFILE_ENABLE=1
	* Make sure jtagd is running
	* Run
		$ scripts/run-with-profiling.sh
