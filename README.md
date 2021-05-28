# Traffic-Cam-Car-Detector-Demo.cpp
______________________________________________________________________________
_____________________________________________________________________________ |
Author: GÖRKEM TOK							                                             ||
Email: ceng.gorkem.tok@gmail.com					                                   ||
Linkedin: https://www.linkedin.com/in/gorkem-tok33/                          ||
Language: C++                                                                ||
Libraries: OpenCv 3.4                                                        ||
_____________________________________________________________________________||
______________________________________________________________________________|
*/

This project aims to detect cars using subtraction between two frames. 
For the better result I used bgsegm methods like MOG, MOG 2, KNN, GMG. In my experience best method is MOG2 from bgsegm methods. 
But methods result depends on your video file, video clearity and filters like blur, morphologyex etc. 
In my project I used gaussian blur, morphologyex methods( ERODE, CLOSE) for elimate unimportant details.

