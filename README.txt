Sign Detection Project

The Sign Detection project is a real-time video processing application that alerts users of nearby traffic signs as they operate their vehicle.
This computer vision based sign detection technology is a very critical integral part in a self-driving car.
A cluster of Raspberry Pi devices operated in MPI (Message Passing Interface) is used to process the video feed from an camera.
Each node is specialized in one component of the sign detection process, so that the entire detection process can be run in parallel and output can be returned in real time. 

The master node receives the video feed from the camera and assigns work to analyzer nodes. These nodes receive individual frames, apply different color masks to the frames, and use pattern recognition and classifying algorithms to determine which regions, if any, contain signs. For the regions found to have a sign on them, if the area is clear enough, any meaningful text is extracted from it using the tesseract-ocr library and displayed on the top-left corner of the output frame. If text could not be extracted, a generic but informative message is shown, such as "Stop" for stop signs, "Yield" for yield signs, and so on.

Once each analyzer node has completed its job, the results are sent to a rendering node, which draws bounding boxes around street signs and displays informative text at the top-left corner of the screen. The renderer also saves the output stream to a file for later viewing.

Features implemented:
  1. Nodes can communicate and pass data via MPICH
  2. Master node extracts frames from a camera, or a video file from local storage
  3. Master node can send frames to multiple Analyzer notes
  4. Analyzer can differentiate between areas of red, white, yellow, and orange
  5. Analyzer can differentiate between triangles, rectangles, diamonds, and octagons
  6. Analyzer can detect and extract text in potential sign areas
  7. Detect stop signs in a still image
  8. Detect yield signs in a still image
  9. Detect generic warning signs in a still image
  10. Detect speed limit signs in a still image
  11. Analyzer can send frame results to Renderer
  12. Renderer can reorder received frame results
  13. Renderer can render frames to output video file or screen
  14. Renderer can display bounding boxes and labels around detected signs 
  15. Real time data extraction from a video feed

Known bugs in this release:
  * Text extractor occasionally returns gibberish, working on applying a "sanity test" in order to exclude such results
  * Video processing is too slow when using a webcam as a source; many frames via webcam feed are dropped
  * Webcam video output cannot save to a file
  * Text output region leaves artifacts after a detected sign has left the viewport
  * Diamond-shaped signs, and signs tilted away from the camera have a lower-than-acceptable detection rate

Build instructions:

 1. Software dependencies
      * CMake
      * MPICH
      * opencv
      * libtesseract3
      * tesseract-ocr and tesseract data files for english language
      * leptonica
 2. Build procedure
      a. Download repository with command: git pull https://github.com/emilmoham/SignDetectionSystemCIS4398.git
      b. From root repository folder, execute command "mkdir build && cd build && cmake .."
      c. Execute command "make"
      d. Execute command "mkdir ../bin && cp ./cpp/SignDetection ../bin && cp ./cpp/Config.ini ../bin"
 3. Running sign detection application
      * Note: It is up to the user to properly configure their cluster with MPICH
      a. Enter the aforementioned directory, using command "cd (sign detection folder)/bin"
      b. Modify Config.ini according to your needs. The configuration file is commented in order to explain each setting
      c. Execute the SignDetection binary using mpiexec, with a minimum of five nodes. Example: "mpiexec -n 5 -f (your host file) ./SignDetection"
      d. Output will appear on the screen of the rendering node, or the calling node if "-enable-x" flag is passed to mpiexec
      e. Output will also be saved to a file named "output.avi" if program used a saved video file as input
