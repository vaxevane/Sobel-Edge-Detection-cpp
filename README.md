# C++ Implementation of Sobel Edge Detection Algorithm  with HLS

 Sobel algorithm is a [Image Processing](https://en.wikipedia.org/wiki/Digital_image_processing "Digital image processing") algorithm that can detect the edges
 of the objects on an image. After developing the algorithm we produce the synthesizable equivalent which is passed through mentor's catapult in order to get the rtl design.


## Sobel Operator
The operator uses two 3×3 kernels which are [convolved](https://en.wikipedia.org/wiki/Kernel_(image_processing)#Convolution
"Kernel (image processing)") with the original image to calculate approximations of the [derivatives](https://en.wikipedia.org/wiki/Image_Derivatives "Image Derivatives") – 
one for horizontal changes, and one for vertical. If we define **A** as the source image, and **G**_x_ and **G**_y_ are two images which at each point 
contain the horizontal and vertical derivative approximations respectively, the computations are as follows.

![Gradients](https://user-images.githubusercontent.com/81081231/126018595-cd8576f5-f4fa-4476-96a4-67cd3b1b8355.png)

At each point in the image, the resulting gradient approximations can be combined to give the gradient magnitude, using:

![Magnitude](https://user-images.githubusercontent.com/81081231/126018652-fdacff81-d4b4-4b79-9ba7-ba0926cbda7f.png)

Using this information, we can also calculate the gradient's direction:

![image](https://user-images.githubusercontent.com/81081231/126018744-1e7a0922-16ea-4546-9868-c94a98b6e37d.png)

## Implementation

The Implemented Code has two header files and one main where the result of the process is tested. 

### yuv_io.h
This header file handles:

 - The reading/writing of the images
 
### Sobel.h
This header file handles:

 - Preprocessing: Initializing Image boundaries with 0
 - Sobel Operator: Running Sobel Algorithm
 - Filtering Result: Removing noise
 
 ### Sobel_testbench.cpp
This cpp file handles:

- Testing Sobel Algorithm: Choosing a random image and produces it's edges then compares the result with the image that we assume has the correct result

## Results
### Original Image
![Original](https://user-images.githubusercontent.com/81081231/126020063-8750ef9a-14a2-46fb-9b19-16f2f1762912.png)

### Edges Produced
![Mag Gradient](https://user-images.githubusercontent.com/81081231/126020129-faf50bdf-a538-4711-b467-a2d50667f27d.png)

### Gradient X
![Gradient x](https://user-images.githubusercontent.com/81081231/126020133-1f58d8ac-e901-4f8b-97f7-e5da926c016d.png)

### Gradient Y
![Gradient y](https://user-images.githubusercontent.com/81081231/126020139-5d9978dd-5e78-4bcf-a4a6-ef19168892bb.png)

### Angle
![Angle](https://user-images.githubusercontent.com/81081231/126020149-560348b0-934f-4cd3-a053-3b6ba2ad04f6.png)
