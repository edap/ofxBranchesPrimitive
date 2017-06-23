# ofxBranchesPrimitive
[![Build status](https://travis-ci.org/edap/ofxBranchesPrimitive.svg?branch=master)](https://travis-ci.org/edap/ofxBranchesPrimitive)
[![Build status](https://ci.appveyor.com/api/projects/status/ksje98gfpdn5knu9?svg=true)](https://ci.appveyor.com/project/edap/ofxbranchesprimitive)

This openFrameworks addon can be used to compose geometries that are made out of branches. As "branch" I mean a data structure defined by a starting point and an end point, a quaternion that define the current orientation and a direction.

The desired geometry for each branch can be specified when merging the branches into the mesh. By default, this addon comes with a cylindric geometry that can be used to create tubular structures, as in the `example-circle-points` app. If you want to create your own geometry for the branches, have a look at the `example-branch` application, find the `ofxBranchCylinder::putIntoMesh` method and substitute it with your custom one.

### Usage

```cpp
//in your header file
ofxBranchesPrimitive tube;

void ofApp::setup(){
    int tot_points = 200;
    for (int i = 0; i <= tot_points; i++) {
      int radius = 40;
      float theta = 2.0f * 3.1415926f * float(i) / float(tot_points-1);
      float x = radius * cosf(theta);
      float z = radius * sinf(theta);
      point.x = x;
      point.z = z;
      tube.addVertex(point);
    }
    tube.build();
}

void ofApp::draw(){
    tube.draw();
}
```

### Examples

*example-branch*

![example-branch](img/example-branch.png)

*example-circle-points*

![example-circle-points](img/example-circle-points2.png)
![example-circle-points](img/example-circle-points.png)
