#include <iostream>
#include "../color.h"
#include "../vec3.h"
#include "../ray.h"

#include <iostream>
color ray_color(const ray& r){
  vec3 unit_direction = unit_vector(r.direction());
  auto a = 0.5 * (unit_direction.y() + 1.0);
  return (1.0 - a) * color(1.0, 1.0, 1.0) + a*color(0.5, 0.7, 1.0);
}

int main() {

  double aspect_ratio = 16.0 / 9.0;
  int image_width = 400;
  int image_height = static_cast<int>(image_width / aspect_ratio);
  image_height = image_height == 0 ? 1 : image_height;


  // Camera
  double focal_length = 1.0;
  double viewport_height = 2.0;
  double viewport_width = viewport_height * (static_cast<double>(image_width)/image_height);
  point3 camera_center = point3(0, 0, 0);

  // Calculating horizontal and vertical vectors
  vec3 viewport_u = vec3(viewport_width, 0, 0);
  vec3 viewport_v = vec3(0, -viewport_height, 0);

  // Calculating delta vectors
  vec3 delta_u = viewport_u / image_width;
  vec3 delta_v = viewport_v / image_height;

  // Calculate the location of the upper left pixel
  vec3 viewport_upper_left = camera_center - vec3(0, 0, focal_length) - viewport_u/2 - viewport_v/2;
  vec3 pixel00_loc = viewport_upper_left + 0.5 * (delta_u + delta_v);

  std::cout << "P3\n" << image_width << " " << image_height << "\n255\n"; 
  for (int i = 0; i < image_height; ++i){
    std::clog << "\rScanlines remaining: " << (image_height - i) << " " << std::flush;
    for (int j = 0; j < image_width; ++j){
      vec3 pixel_center = pixel00_loc + (i * delta_u) + (j * delta_v);
      vec3 ray_direction = pixel_center - camera_center;
      ray r(camera_center, ray_direction);

      color pixel_color = ray_color(r);
      write_color(std::cout, pixel_color);
    }
  }
}