Overview:
This code generates and animates a Mandelbrot set fractal with increasing zoom level, saving each frame as a PNG image. It uses the SFML (Simple and Fast Multimedia Library) for graphics handling.

Zoom Location: double targetReal = -0.751469520085105;  // Set desired real part
               double targetImaginary = -0.0324751200764;  // Set desired imaginary part

Frame Size: const int width = 1920;
            const int height = 1080;

Iterations: int max_iterations = 1000;

Number Of Frames: const int totalFrames = 900;  // Number of frames to generate

Key Components:
  Libraries Used:
  <iostream> for input/output operations.
  <chrono> and <thread> for timing and simulating loading time.
  <complex> for handling complex numbers in the Mandelbrot calculations.
  <SFML/Graphics.hpp> for graphical operations like rendering and saving images.
  <iomanip> for formatted output (like frame numbering).

Functions:
  showLoadingBar(int total): Displays a loading bar to simulate progress or processing time. It prints and updates the bar character by character to give a visual loading effect.
  mandelbrot(std::complex<double> c, int max_iterations): Determines if a point c in the complex plane belongs to the Mandelbrot set by checking how many iterations are needed before the magnitude exceeds 2 (escape condition). If it doesn't escape within max_iterations, the point is considered part of the set.
  getColor(int iterations, int max_iterations): Maps the number of iterations to a color using a simple color gradient. Points inside the set (iterations == max_iterations) are colored black, while others are given colors based on their hue calculated from iteration count.

Main Function:
  Initialization: Sets up constants for window size, maximum iterations, total frames for animation, and initial zoom. It also initializes the SFML window and an image object to hold the fractal.
  Zooming Mechanism: 
  Defines the initial boundaries of the complex plane (minReal, maxReal, etc.) and a target zoom point (targetReal, targetImaginary).
  Uses a loop to generate each frame, gradually zooming in by adjusting the viewing area based on zoomFactor, which increases each frame.
  Fractal Generation: 
  For each pixel in the image, it computes the corresponding point in the complex plane and uses the mandelbrot function to determine its color. This color is then set to the corresponding pixel in fractalImage.
  Frame Saving & Display:
  Each frame is saved as a PNG file with a sequentially numbered name for later use in creating an animation. 
  The frame is also immediately displayed in the SFML window for real-time feedback.
  Event Handling: Checks for window close events to allow user exit.

Notes for Release 1.0:
  Performance: The code might run slowly due to the nested loops and intensive calculations, especially at higher resolutions or iteration counts. Consider multi-threading or GPU acceleration for future releases.
  Error Handling: There's minimal error handling, particularly around image saving. Enhancing this could improve robustness.
  User Interaction: Currently, there's no interactivity beyond watching the animation. Adding user controls for zoom, pan, or changing color schemes could be beneficial.
  Optimization: Some parts like the color computation could be optimized by pre-calculating or using lookup tables for faster performance.

This code provides a solid foundation for visualizing dynamic fractals, with room for enhancements in performance, user interaction, and error management.
