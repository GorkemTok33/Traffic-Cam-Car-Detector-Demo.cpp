# Traffic-Cam-Car-Detector-Demo.cpp

Author: GÖRKEM TOK							                                             
Email: ceng.gorkem.tok@gmail.com					                                   
Linkedin: https://www.linkedin.com/in/gorkem-tok33/                          
Language: C++                                                                
Libraries: OpenCv 3.4                                                       

![Screenshot (213)](https://user-images.githubusercontent.com/79594881/120048347-81416d80-c01f-11eb-823e-918e30afab07.png)

This project aims to detect cars using subtraction between two frames. 
For the better result I used bgsegm methods like MOG, MOG 2, KNN, GMG. In my experience best method is MOG2 from bgsegm methods. 
But methods result depends on your video file, video clearity and filters like blur, morphologyex etc. 
In my project I used gaussian blur, morphologyex methods( ERODE, CLOSE) for elimate unimportant details.

