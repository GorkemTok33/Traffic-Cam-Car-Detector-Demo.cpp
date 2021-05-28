# Traffic-Cam-Car-Detector-Demo.cpp

Author: GÖRKEM TOK <br>
Preview video link: https://www.youtube.com/watch?v=02lOu2_7KnI <br>
Email: ceng.gorkem.tok@gmail.com	<br>				                                   
Linkedin: https://www.linkedin.com/in/gorkem-tok33/ <br>                         
Language: C++   <br>                                                             
Libraries: OpenCv 3.4     <br>                                                  

![Screenshot (213)](https://user-images.githubusercontent.com/79594881/120048347-81416d80-c01f-11eb-823e-918e30afab07.png)

This project aims to detect cars using subtraction between two frames. 
For the better result I used bgsegm methods like MOG, MOG 2, KNN, GMG. In my experience best method is MOG2 from bgsegm methods. 
But methods result depends on your video file, video clearity and filters like blur, morphologyex etc. 
In my project I used gaussian blur, morphologyex methods( ERODE, CLOSE) for elimate unimportant details.

<b> THE LOGIC </b> <br>
The logic is actually simple. We're reading frame by frame the video with infinity for loop until cannot read frame, and using some gaussian blur and morphologyex methods for clearing unimportant details after all this process I am using findContours for the determining contours. For drawing circle I am using minEnclosingCircle method for find center of min circle and radius from set of dots. Thanks for reading.

