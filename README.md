# MiniRT
This project is 42 project that aimes to introduce us to the beautiful world of Raytracing

<img src="./images/1337.png" />
<div style="margin: auto">1337 image generated by miniRT<div>

### What is ray tracing
In 3D computer graphics, ray tracing is a technique for modeling light
transport for use in a wide variety of rendering algorithms for
generating digital images.

## Install

Clone this repository:
```
git clone https://github.com/YassineEddyb/miniRT_42 && cd miniRT_42 && make
```
Then run the program with a file as an argument from the scenes folder:
```
./miniRT ./scenes/1337.rt
```

## How to use it:

You can also create your own scene, Just create a file with <b>.rt</b> extention and configure it. <br>
There is three conifg object that are mandatory to have:

- Ambient
<img src="./images/ambient.png" />

- Light
<img src="./images/light.png" />

- Camera
<img src="./images/camera.png" />

And four basic shapes that are (optional, will not entirely cause if you leave it empty you will only see a black window):

- Plane
<img src="./images/plane.png" />

- Sphere
<img src="./images/sphere.png" />

- Cylinder
<img src="./images/cylinder.png" />

- Cube
<img src="./images/cube.png" />

<b>Position: 20,3,0 </b> => x,y,z coordinates <br>
<b>Oreintation: 0,1,0 </b> => 3d normalized orientation vector. In range [-1,1] for each x,y,z axis <br>
<b>Color: 255,0,255 </b> => R,G,B colors in range [0,255] <br>
<b>Shininess: 200</b> => how much the surface shine in range [0,200] <br>
<b>Reflection: 1 </b> => how much the surface reflect in range [0,1] <br>

## Images generated by miniRT
<img src="./images/Screen Shot 2022-09-13 at 11.44.05 AM.png" />
<img src="./images/Screen Shot 2022-09-08 at 12.44.34 PM.png" />
<img src="./images/Screen Shot 2022-09-08 at 2.30.55 PM.png" />
<img src="./images/Screen Shot 2022-09-08 at 3.47.20 PM.png" />
<img src="./images/Screen Shot 2022-09-09 at 12.47.57 PM.png" />
<img src="./images/Screen Shot 2022-09-11 at 3.22.58 PM.png" />
<img src="./images/Screen Shot 2022-09-11 at 5.58.32 PM.png" />
<img src="./images/Screen Shot 2022-09-12 at 10.26.17 AM.png" />
<img src="./images/Screen Shot 2022-09-12 at 11.47.06 AM.png" />

# How it works?

in case you're wondering how all this works? just loop over all pixels and generate a ray for each one, then see if intersects with any object and calculate the color for this pixel, sounds simple isn't it, well it's not.

## Here is some resourses:
<ul>
  <li><a href="https://www.scratchapixel.com/lessons/3d-basic-rendering/introduction-to-ray-tracing/how-does-it-work">Introduction to Ray Tracing: a Simple    Method for Creating 3D Images</a></li>
  <li><a href="https://www.youtube.com/watch?v=gfW1Fhd9u9Q&list=PLlrATfBNZ98edc5GshdBtREv5asFW3yXl">The cherno ray tracing in youtube</a> <br>
  <li><a href="https://raytracing.github.io/">Ray Tracing in One Weekend</a></li>
  <li><a href="https://www.amazon.com/Ray-Tracer-Challenge-Test-Driven-Renderer/dp/1680502719/ref=sr_1_1?   crid=12SJ4LEACDK9I&keywords=the+ray+tracing+challenge&qid=1663158573&sprefix=the+ray+tracing+challenge%2Caps%2C161&sr=8-1">The The Ray Tracer Challenge</a></li>
  <li><a href="https://www.youtube.com/watch?v=RIgc5J_ZGu8&list=PLAqGIYgEAxrUO6ODA0pnLkM2UOijerFPv">Ray Tracer series youtube</a></li>
</ul>

## My explanation

### Some things you have to know
- First of all you should be familiar with matrixes and vectors,
Check this article from scratchapixel <a href="https://www.scratchapixel.com/lessons/mathematics-physics-for-computer-graphics/geometry">geometry.</a> <br>

- Structures needed for this lesson
```
ray {
  vector origin # start of the ray
  vector dir # direction of the ray
}

sphere {
  vector pos # position of the sphere
  matrix transform # transformation matrix of the sphere
}
```

- in this lesson well draw a sphere and the same method go for other basic shapes.
- Intersection of the sphere will be in object space then we will transform it to world space see 
<a href="https://knowledge.autodesk.com/support/maya/learn-explore/caas/CloudHelp/cloudhelp/2018/ENU/Maya-Basics/files/GUID-A63AC5C8-8822-42AC-827E-164B5266DA03-htm.html#:~:text=World%20space%20is%20the%20coordinate,an%20object's%20point%20of%20view.">Object space vs World space</a>.


### 1- Generating rays
In orther to generate rays in real life you would have to implement a camera but we'll keep thing simple here.

General configurations
```
Width = 100
Height = 100

ray.pos = point(0, 0, -5)
sphere.pos = point(0,0,0)
sphere.transform = identity_matrix;
  
fov = PI/2
```

We'll implement a function that calculates the direction of the ray
```
fucntion get_ray_direction(Width, Height, x, y, fov)
  # get the aspect ratio
  if Widht > Height
    AspectRatio = Width / Height;
  else 
    AspectRatio = Width / Height;

  # compute the world y coordinate
  world_x = (2 * ((x + 0.5) / Width) - 1) * tan(fov / 2 * M_PI / 180) * AspectRatio; 

  # compute the world x coordinate
  world_y = (1 - 2 * ((y + 0.5) / Height) * tan(fov / 2 * M_PI / 180);

  # describe the point that the ray will target
  vector position = point(world_x, world_y, 0)

  # get ray direction
  return normalize(ray_dir - ray_origin);
end function
```

### 2- Ray Sphere intersection
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
  <li><b>r</b>: the raduis of the shpere</li>
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

When we expand this equation we get:
<pre>O<sup>2</sup> + (Dt)<sup>2</sup> + 2ODt − r<sup>2</sup> = 0
D<sup>2</sup>t<sup>2</sup> + 2ODt + O<sup>2</sup> - r<sup>2</sup> = 0</pre>

It looks like:
<pre>ax<sup>2</sup> + bx + c = 0</pre>
Where:
<ul>
  <li><b>a</b> => D<sup>2</sup></li>
  <li><b>b</b> => 2OD</li>
  <li><b>c</b> => O<sup>2</sup> - r<sup>2<sup></li>
</ul>

So we can solve it using the <a href="https://en.wikipedia.org/wiki/Quadratic_formula">Quadratic Formula</a>
<pre>t<sub>1,2</sub> = (-b ± √Δ) / 2a</pre>

Where:
<pre>Δ = b<sup>2</sup> - 4ac</pre>

- if `Δ > 0` => the ray intersects the sphere in two points
- if `Δ = 0` => the ray intersects the sphere in one points
- if `Δ < 0` => the ray does not intersects with the sphre

Now we can implement the ray sphere intersection function
In pseudocode
<pre>
function ray_sphere_intersection(sphere, ray)
  # first transform the ray by the inverse of transform matrix
  transformed_ray.origin = ray.pos * sphere.transform
  transformed_ray.dir = ray.dir * sphere.transform
  
  # convert the origin of the ray to a vector
  origin = trasformed_ray.origin - sphere.pos

  # D<sup>2</sup>
  a = dot(transformed_ray.dir, transformed_ray.dir)

  # 2OD
  b = 2 * dot(orgin, transformed_ray.dir)
  
  # O<sup>2</sup> - r<sup>2</sup> // r = 1
  c = dot(origin, origin) - 1
  
  # b<sup>2</sup> - 4ac
  discriminant = b * b - 4 * a * c
  
  if (discriminant < 0)
    return false
  else
    return true
  end if
end function
</pre>

finaly we can draw something by merging what we learnd so far

```
# for each row of pixels in the canvas
for y = 0 to Width - 1
  # for each pixel in the row
  for x = 0 to Height - 1
    ray.dir = get_ray_direction(Width, Hight, x, y, fov)

    if ray_sphere_intersection(sphere, ray)
      put_pixel_to_window(x, y, red)

  end for
end for

```

you will get something like this
<img href="./images/sphere.webp" />
