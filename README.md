# Ray tracer in C++

## How to run in Visual Studio

1. Open Raytracer.vcxproj

2. Make sure it's in release + x86

3. Run

4. Comment out spheres and uncomment teapot for a complex object

5. Bools at the top of the main.cpp to change soft/hard shadows and recursive reflection

6. To stop the plane being reflective, change Plane.cpp shininess to 0


## Examples

##### Soft shadows and recursive reflection with a plane, spheres and complex shape consisting of triangles

![SoftShadowsComplexShapes](http://i.imgur.com/dDYYFRo.png)

##### Similar to the above, but with a reflective plane

![ReflectiveComplexShapes](http://i.imgur.com/vgKSWFf.png)
