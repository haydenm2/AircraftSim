# AircraftSim
AircraftSim is an application designed for simulating the behaviors of aircraft physics for fixed-wing aircraft with standard control surface and throttle inputs under wind conditions in a 3D environment. Features include
- Full gravity, thruster, and aerodynamic physics engine for fixed-wing aircraft
- Live control of actual aircraft control surfaces through keyboard commands
- Selection of 4 different fixed-wing vehicles with different 3D models and associated physics parameters (EMB-312, EMB-314, F-16D, and MQ-9 selectable in GUI toolbar)
- Selection of 3 different 3D terrain models for more exciting exploration options (War Zone, City, and Mountains selectable in GUI toolbar)
- Multi-layer 3D sky dome imported for better user-coordination when pointing toward the sky
- Camera actively follows aircraft during flight with ability to click and drag to a camera offset orientation at any time
- GUI button to play/pause simulation
- GUI button to reset camera to default following position
- GUI button to reset aircraft to starting position
- GUI sliders to actively alter North-East-Down wind components
- 3D wind arrow representing the current direction wind is acting on the aircraft (updates direction and size according to slider positions and combined magnitude)
- GUI checkbox for activating/deactivating wind (also toggles wind arrow visibility)
- GUI button to reset wind back to default zero position
- GUI sliders for altering control surfaces and throttle (sliders also update with keyboard inputs)
- GUI button to reset control inputs to default position for semi-stable flight
- Separate window containing keyboard/GUI instructions for reference

Currently there is no support for collision physics with the available 3D environments.
The software is designed to provide ease in adding additional physics models for simulation of verious other vehicle types to the simulation in the future.

![Alt text](resources/SimImage.png?raw=true "Title")

# Installation Requirements
- Google Test (https://github.com/google/googletest)
- OpenSceneGraph (https://github.com/openscenegraph/OpenSceneGraph)
- osgQt (https://github.com/openscenegraph/osgQt.git)    
- Eigen3 (http://eigen.tuxfamily.org/index.php?title=Main_Page#Download)
