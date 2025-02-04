#include <iostream>
#include <chrono>
#include <thread>
#include <complex>
#include <SFML/Graphics.hpp>
#include <iomanip>  // For formatted frame numbering

// Function to display a loading bar
void showLoadingBar(int total = 500) {
    std::cout << "Loading: [";
    for (int i = 0; i < total; ++i) {
        std::cout << " ";
    }
    std::cout << "]";

    std::cout.flush();
    std::cout << "\rLoading: [";

    for (int i = 0; i <= total; ++i) {
        std::cout << "|";
        std::cout.flush();
        std::this_thread::sleep_for(std::chrono::milliseconds(50));  // Simulate loading time
    }
    std::cout << "] Done!" << std::endl;
}

// Function to determine the number of iterations before the complex number "escapes"
int mandelbrot(std::complex<double> c, int max_iterations) {
    std::complex<double> z = 0;
    int iterations = 0;

    while (std::abs(z) <= 2 && iterations < max_iterations) {
        z = z * z + c;
        ++iterations;
    }
    return iterations;
}

// Function to map iterations to color (gradient)
sf::Color getColor(int iterations, int max_iterations) {
    if (iterations == max_iterations) {
        return sf::Color::Black;  // Inside the set
    }
    float hue = 360.0f * iterations / max_iterations;
    sf::Uint8 r = static_cast<sf::Uint8>(255 * std::sin(hue));
    sf::Uint8 g = static_cast<sf::Uint8>(255 * std::cos(hue));
    sf::Uint8 b = static_cast<sf::Uint8>(255 * std::sin(2 * hue));

    return sf::Color(r, g, b);
}

int main() {
    showLoadingBar(30);

    const int width = 1920;
    const int height = 1080;
    int max_iterations = 1000;
    const int totalFrames = 900;  // Number of frames to generate
    double zoomFactor = 1.0;

    sf::RenderWindow window(sf::VideoMode(width, height), "Zooming Mandelbrot Fractal");

    // Image to store pixel data
    sf::Image fractalImage;
    fractalImage.create(width, height, sf::Color::Black);

    // Initial Mandelbrot boundaries (start position)
    double minReal = -2.5, maxReal = 1.0, minImaginary = -1.5, maxImaginary = 1.5;

    // Target point to zoom towards (destination)
    //double targetReal = -0.75146952;  // Set desired real part
    //double targetImaginary = -0.03247512;  // Set desired imaginary part

    // Target point to zoom towards (destination)
    double targetReal = -0.751469520085105;  // Set desired real part
    double targetImaginary = -0.0324751200764;  // Set desired imaginary part

    for (int frame = 1; frame <= totalFrames; ++frame) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Interpolate zoom: gradually zoom towards the target area over the total frames
        double zoomStep = 1.04;  // How much zoom increases per frame
        zoomFactor *= zoomStep;  // Increase zoom factor gradually

        // Recalculate the bounds of the complex plane as we zoom in
        double realRange = (maxReal - minReal) / zoomFactor;
        double imaginaryRange = (maxImaginary - minImaginary) / zoomFactor;

        double currentMinReal = targetReal - realRange / 2;
        double currentMaxReal = targetReal + realRange / 2;
        double currentMinImaginary = targetImaginary - imaginaryRange / 2;
        double currentMaxImaginary = targetImaginary + imaginaryRange / 2;

        // Generate the Mandelbrot fractal for the current frame
        for (int x = 0; x < width; ++x) {
            for (int y = 0; y < height; ++y) {
                // Map pixel to complex plane
                double real = currentMinReal + (x * realRange) / width;
                double imaginary = currentMinImaginary + (y * imaginaryRange) / height;
                std::complex<double> c(real, imaginary);
                int iterations = mandelbrot(c, max_iterations);

                sf::Color color = getColor(iterations, max_iterations);
                fractalImage.setPixel(x, y, color);
            }
        }

        // Save each frame as an image
        std::ostringstream filename;
        filename << "frame_" << std::setw(4) << std::setfill('0') << frame << ".png";
        if (!fractalImage.saveToFile(filename.str())) {
            std::cerr << "Error saving frame: " << filename.str() << std::endl;
        }

        // Load the generated fractal image into a texture
        sf::Texture fractalTexture;
        fractalTexture.loadFromImage(fractalImage);

        // Create a sprite to display the texture
        sf::Sprite fractalSprite;
        fractalSprite.setTexture(fractalTexture);

        // Display the fractal
        window.clear();
        window.draw(fractalSprite);
        window.display();
    }

    return 0;
}
