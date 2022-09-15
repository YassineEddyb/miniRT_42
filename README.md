# MiniRT
This project is 42 project that aimes to introduce us to the beautiful world of Raytracing

<img src="./images/1337.png" />
1337 image generated by miniRT

### What is ray tracing
In 3D computer graphics, ray tracing is a technique for modeling light 
transport for use in a wide variety of rendering algorithms for
generating digital images.

## install

Clone this repo:
```
git clone https://github.com/YassineEddyb/miniRT_42 && cd miniRT_42 && make
```
Then run the program with a file as an argument from the scenes folder:
```
./miniRT ./scenes/1337.rt
```

## How to use it

You can also create your own scene, just create a file with <b>.rt</b> extention and add configure it. <br>
There is three conifg object that are mandate to have:

Ambient
<img src="./images/ambient.png" />

Light
<img src="./images/light.png" />

Camera
<img src="./images/camera.png" />

And foor basic shapes that are (optional, will not entirely cause if you leave it empty you will only see a black window):

Plane
<img src="./images/plane.png" />

Sphere
<img src="./images/sphere.png" />

Cylinder
<img src="./images/cylinder.png" />

Cube
<img src="./images/cube.png" />

<b>Position: 20,3,0 </b> => x,y,z coordinates <br>
<b>Oreintation: 0,1,0 </b> => 3d normalized orientation vector. In range [-1,1] for each x,y,z axis <br>
<b>Color: 255,0,255 </b> => R,G,B colors in range [0,255] <br>
<b>Shininess: 200</b> => how much the surface shine in range [0,200] <br>
<b>Reflection: 1 </b> => how much the surface reflect in range [0,1] <br>

<!-- ## images generated by miniRT
<img src="./images/Screen Shot 2022-09-13 at 11.44.05 AM.png" />
<img src="./images/Screen Shot 2022-09-08 at 12.44.34 PM.png" />
<img src="./images/Screen Shot 2022-09-08 at 2.30.55 PM.png" />
<img src="./images/Screen Shot 2022-09-08 at 3.47.20 PM.png" />
<img src="./images/Screen Shot 2022-09-09 at 12.47.57 PM.png" />
<img src="./images/Screen Shot 2022-09-11 at 3.22.58 PM.png" />
<img src="./images/Screen Shot 2022-09-11 at 5.58.32 PM.png" />
<img src="./images/Screen Shot 2022-09-12 at 10.26.17 AM.png" />
<img src="./images/Screen Shot 2022-09-12 at 11.47.06 AM.png" /> -->

# How it works?

in case you're wondering how all this works? just loop over all pixels and generate a ray for each one, then see if intersects with any object and calculate the color for this pixel, sounds simple isn't it, well it's not at least for me.

## Here is some resourses
<ul>
  <li><a href="https://www.scratchapixel.com/lessons/3d-basic-rendering/introduction-to-ray-tracing/how-does-it-work">Introduction to Ray Tracing: a Simple    Method for Creating 3D Images</a></li>s
  <li><a href="https://www.youtube.com/watch?v=gfW1Fhd9u9Q&list=PLlrATfBNZ98edc5GshdBtREv5asFW3yXl">The cherno ray tracing in youtube</a> <br>
  <li><a href="https://raytracing.github.io/">Ray Tracing in One Weekend</a></li>
  <li><a href="https://www.amazon.com/Ray-Tracer-Challenge-Test-Driven-Renderer/dp/1680502719/ref=sr_1_1?   crid=12SJ4LEACDK9I&keywords=the+ray+tracing+challenge&qid=1663158573&sprefix=the+ray+tracing+challenge%2Caps%2C161&sr=8-1">The The Ray Tracer Challenge</a></li>
  <li><a href="https://www.youtube.com/watch?v=RIgc5J_ZGu8&list=PLAqGIYgEAxrUO6ODA0pnLkM2UOijerFPv">Ray Tracer series youtube</a></li>
</ul>

## My explanation
First of all you should be familiar with matrixes and vectors,
check this article from scratchapixel <a href="https://www.scratchapixel.com/lessons/mathematics-physics-for-computer-graphics/geometry">geometry.</a> <br>

in this lesson well draw a sphere and the same method go for other basic shapes.

### generating rays
In orther to generate rays in real life you would have to implement a camera but we'll keep thing simple here.

First we'll have to deside how large our window will be:
```
Width = 100
Height = 100
```

We'll assume the ray starts from z -5.
```
vector ray_origin = point(0, 0, -5)
```

```
# assuming Width > Height
AspectRatio = Width / Height;

# for each row of pixels in the canvas
for y = 0 to Width - 1

  # compute the world y coordinate
  world_x = (2 * ((x + 0.5) / Width) - 1) * tan(fov / 2 * M_PI / 180) * AspectRatio; 

  # for each pixel in the row
  for x = 0 to Height - 1
 
    # compute the world x coordinate
    world_y = (1 - 2 * ((y + 0.5) / Height) * tan(fov / 2 * M_PI / 180);

    # describe the point that the ray will target
    vector position = point(world_x, world_y, 1)

    # get ray direction
    vector ray_dir = normalize(ray_dir - ray_origin);

  end for
end for
```

### ray intresetion
After generating rays we'll see if they intersect with a sphere.

We know the equation of a line:
```
P = O + tD
```
Where :
<ul>
  <li><b>P</b>: a point on the line</li>
  <li><b>O</b>: the origin on the line</li>
  <li><b>t</b>: the scaler just think of it a number</li>
  <li><b>D</b>: the direction of the line</li>
</ul>

We also know the equation of a sphere:

<pre>(x - a)<sup>2</sup> + (y - b)<sup>2</sup> + (z - c)<sup>2</sup> = r<sup>2</sup></pre>

Where:
<ul>
  <li><b>a,b,c</b>: the position of the sphere</li>
  <li><b>x,y,z</b>: a point from the sphere</li>
</ul>

Assuming that the sphere postion is on 0,0,0.
<pre>
(x - 0)<sup>2</sup> + (y - 0)<sup>2</sup> + (z - 0)<sup>2</sup> = r<sup>2</sup>
x<sup>2</sup> + y<sup>2</sup> + z<sup>2</sup> = r<sup>2</sup>
x<sup>2</sup> + y<sup>2</sup> + z<sup>2</sup> - r<sup>2</sup> = 0
</pre>

Remember that x,y,z are the cordinates of a point in the sphere so we can write it as
<pre>P<sup>2</sup> - r<sup>2</sup> = 0</pre>

If we replace P with it's value from the equation of a line we get:
<pre>|O + tD|<sup>2</sup> - r<sup>2</sup> = 0</pre>

With the origin of the sphere on 0,0,0 we get
<pre>(tD)<sup>2</sup> - r<sup>2</sup> = 0</pre>

When we expand this equation we get
<pre>(Dt)<sup>2</sup> + 2Dt − R<sup>2</sup> = D<sup>2</sup>t<sup>2</sup> + 2Dt − r<sup>2</sup> = 0</pre>

It looks like:
<pre>ax<sup>2</sup> + bx + c = 0</pre>
Where
<ul>
  <li><b>a</b> => D</li>
  <li><b>b</b> => 2D</li>
  <li><b>c</b> => r<sup>2<sup></li>
</ul>

so we can solve it using the <a href="https://en.wikipedia.org/wiki/Quadratic_formula">Quadratic Formula</a>


