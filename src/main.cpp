#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include "vec3.h"
#include "Ray.h"
#include "color.h"

using namespace std;

Vec3 random_in_unit_sphere() {
    Vec3 random_point;

    do {
        random_point = 2.0 * Vec3(static_cast<double>(rand()) / RAND_MAX,
                                  static_cast<double>(rand()) / RAND_MAX,
                                  static_cast<double>(rand()) / RAND_MAX) - Vec3(1, 1, 1);
    } while (random_point.length() >= 1.0);

    return random_point;
}
double disc(const Vec3& center, double radius, const Ray& r) {
    Vec3 oc = r.org() - center;
    auto a = dot(r.dir(), r.dir());
    auto b = 2.0 * dot(oc, r.dir());
    auto c = dot(oc, oc) - radius * radius;
    auto discriminant = b * b - 4 * a * c;
    
    if(discriminant < 0){
        return -1.0;
    }
    else{
        return (-b -sqrt(discriminant))/ (2.0*a);
    }
}
colour lambertian_reflection(const Vec3& normal) {
    // Generate a random point on the unit hemisphere
    Vec3 random_direction = random_in_unit_sphere();

    // Ensure the random point is in the same hemisphere as the normal
    if (dot(random_direction, normal) < 0.0) {
        random_direction = -random_direction;
    }

    // Lambertian reflection formula: attenuation = dot(normal, random_direction)
    return 0.5 * colour(1.0 + random_direction.x(), 1.0 + random_direction.y(), 1.0 + random_direction.z());
}
colour ray_colour(const Ray& r) {
    auto t = disc(Vec3(0, 0, -1), 0.5, r);
    if (t > 0.0) {
        Vec3 normal = unit_vector(r.at(t) - Vec3(0, 0, -1));
        // Lambertian reflection intensity using cosines
        auto intensity = 1.0 - 0.45 * (dot(normal, r.dir()) + 1.0);
        // Use light blue color for Lambertian reflection on the sphere
        return colour(0, 1, 0) * intensity;
    }

    Vec3 unit_dir = unit_vector(r.dir());
    auto f = 0.5 * (unit_dir.y() + 1.0);
    return colour(1.0, 1.0, 1.0) * (1.0 - f) + colour(0.5, 0.7, 1.0) * f;
}




int main() {
    // Setup for width and length of window and viewport
    auto ar = 16.0 / 9.0;
    int wid = 400;
    int hie = static_cast<int>(wid / ar);

    // Camera
    auto focal = 1.0;
    auto viewport_y = 2.0;
    auto viewport_x = viewport_y * (static_cast<double>(wid) / hie);
    auto center = Vec3(0, 0, 0);

    auto viewport_dx = Vec3(viewport_x, 0, 0);
    auto viewport_dy = Vec3(0, -viewport_y, 0);

    auto dx = viewport_dx / wid;
    auto dy = viewport_dy / hie;

    // Location of upper left
    auto viewport_UL = center - viewport_dx / 2 - viewport_dy / 2 - Vec3(0, 0, focal);

    ofstream image;
    image.open("image.ppm");
    image << "P3\n" << wid << ' ' << hie << "\n255\n";

    for (int j = hie - 1; j >= 0; --j) {
        for (int i = 0; i < wid; ++i) {
            auto pix_center = viewport_UL + (dx * i) + (dy * j);

            auto ray_dir = pix_center - center;
            Ray g(center, ray_dir);

            colour pix_color = ray_colour(g);
            writeRgb(image, pix_color);
        }
    }

    image.close();
}
