#include <iostream>
#include <cmath>
#include <cstdlib>

#include "uiuc/PNG.h"
#include "uiuc/HSLAPixel.h"
#include "ImageTransform.h"

/* ******************
(Begin multi-line comment...)

Write your name and email address in the comment space here:

Name: Amos Thando Mpofu
Email: amosmpofu321@gmail.com

(...end multi-line comment.)
******************** */

using uiuc::PNG;
using uiuc::HSLAPixel;

/**
 * Returns an image that has been transformed to grayscale.
 *
 * The saturation of every pixel is set to 0, removing any color.
 *
 * @return The grayscale image.
 */
PNG grayscale(PNG image) {
  /// This function is already written for you so you can see how to
  /// interact with our PNG class.
  for (unsigned x = 0; x < image.width(); x++) {
    for (unsigned y = 0; y < image.height(); y++) {
      HSLAPixel & pixel = image.getPixel(x, y);

      // `pixel` is a reference to the memory stored inside of the PNG `image`,
      // which means you're changing the image directly. No need to `set`
      // the pixel since you're directly changing the memory of the image.
      pixel.s = 0;
    }
  }

  return image;
}



/**
 * Returns an image with a spotlight centered at (`centerX`, `centerY`).
 *
 * A spotlight adjusts the luminance of a pixel based on the distance the pixel
 * is away from the center by decreasing the luminance by 0.5% per 1 pixel euclidean
 * distance away from the center.
 *
 * For example, a pixel 3 pixels above and 4 pixels to the right of the center
 * is a total of `sqrt((3 * 3) + (4 * 4)) = sqrt(25) = 5` pixels away and
 * its luminance is decreased by 2.5% (0.975x its original value).  At a
 * distance over 160 pixels away, the luminance will always decreased by 80%.
 * 
 * The modified PNG is then returned.
 *
 * @param image A PNG object which holds the image data to be modified.
 * @param centerX The center x coordinate of the crosshair which is to be drawn.
 * @param centerY The center y coordinate of the crosshair which is to be drawn.
 *
 * @return The image with a spotlight.
 */
PNG createSpotlight(PNG image, int centerX, int centerY) {
  for(unsigned w = 0; w < image.width(); w++) {
    for(unsigned h = 0; h < image.height(); h++) {
      HSLAPixel& pixel = image.getPixel(w, h);
      // calculate distance using the distance formula
      double difference_x = std::abs(centerX - (int)w);
      double difference_y = std::abs(centerY - (int)h);
      double distance = std::sqrt(std::pow(difference_x, 2) + std::pow(difference_y, 2));
      // calculate the percentage = number of pixels away(distance) x 0.5% per pixel
      double percentage = distance * 0.5;
      // for distances over 160 pixels away use 80%
      if(distance > 160.0) {
        pixel.l -= pixel.l * (80.0 / 100.0);
      } else {
        pixel.l -= pixel.l * (percentage / 100.0);
      }
    }
  }
  return image;
}
 

/**
 * Returns a image transformed to Illini colors.
 *
 * The hue of every pixel is set to the a hue value of either orange or
 * blue, based on if the pixel's hue value is closer to orange than blue.
 *
 * @param image A PNG object which holds the image data to be modified.
 *
 * @return The illinify'd image.
**/
PNG illinify(PNG image) {
  for(unsigned int w = 0; w < image.width(); w++) {
    for(unsigned int h = 0; h < image.height(); h++) {
      HSLAPixel& pixel = image.getPixel(w, h);
      // calculate the range 
      double orange = std::abs(pixel.h - 11.0);
      double blue = std::abs(pixel.h - 216.0);

      if(orange > 180.0)
        orange = 360.0 - orange;

      if(blue > 180.0)
        blue = 360.0 - blue;

      // compare the range and change it according to the which number its closer to
      if(orange < blue)
        pixel.h = 11.0;
      else
        pixel.h = 216.0;
    }
  }
  return image;
}
 

/**
* Returns an immge that has been watermarked by another image.
*
* The luminance of every pixel of the second image is checked, if that
* pixel's luminance is 1 (100%), then the pixel at the same location on
* the first image has its luminance increased by 0.2.
*
* @param firstImage  The first of the two PNGs, which is the base image.
* @param secondImage The second of the two PNGs, which acts as the stencil.
*
* @return The watermarked image.
*/
PNG watermark(PNG firstImage, PNG secondImage) {
  // iterate over every pixel
  for(unsigned int w = 0; w < firstImage.width(); w++) {
    for(unsigned int h = 0; h < firstImage.height(); h++) {
      HSLAPixel& pixel = firstImage.getPixel(w, h);
      HSLAPixel& pixel_2 = secondImage.getPixel(w, h);
      if(pixel_2.l == 1.0) {
        // increase the luminance of the base image by 0.2
        pixel.l = pixel.l <= 0.8 ? pixel.l + 0.2 : pixel.l;
      }
    }
  }
  return firstImage;
}
