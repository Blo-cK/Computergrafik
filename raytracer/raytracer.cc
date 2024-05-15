#include "math.h"
#include "geometry.h"
#include "color.h"
#include <iostream>
#include <vector>
#include <algorithm>

// Die folgenden Kommentare beschreiben Datenstrukturen und Funktionen
// Die Datenstrukturen und Funktionen die weiter hinten im Text beschrieben sind,
// hängen höchstens von den vorhergehenden Datenstrukturen ab, aber nicht umgekehrt.



// Ein "Bildschirm", der das Setzen eines Pixels kapselt
// Der Bildschirm hat eine Auflösung (Breite x Höhe)
// Kann zur Ausgabe einer PPM-Datei verwendet werden oder
// mit SDL2 implementiert werden.



// Eine "Kamera", die von einem Augenpunkt aus in eine Richtung senkrecht auf ein Rechteck (das Bild) zeigt.
// Für das Rechteck muss die Auflösung oder alternativ die Pixelbreite und -höhe bekannt sein.
// Für ein Pixel mit Bildkoordinate kann ein Sehstrahl erzeugt werden.



// Für die "Farbe" benötigt man nicht unbedingt eine eigene Datenstruktur.
// Sie kann als Vector3df implementiert werden mit Farbanteil von 0 bis 1.
// Vor Setzen eines Pixels auf eine bestimmte Farbe (z.B. 8-Bit-Farbtiefe),
// kann der Farbanteil mit 255 multipliziert  und der Nachkommaanteil verworfen werden.


// Das "Material" der Objektoberfläche mit ambienten, diffusem und reflektiven Farbanteil.



// Ein "Objekt", z.B. eine Kugel oder ein Dreieck, und dem zugehörigen Material der Oberfläche.
// Im Prinzip ein Wrapper-Objekt, das mindestens Material und geometrisches Objekt zusammenfasst.
// Kugel und Dreieck finden Sie in geometry.h/tcc


// verschiedene Materialdefinition, z.B. Mattes Schwarz, Mattes Rot, Reflektierendes Weiss, ...
// im wesentlichen Variablen, die mit Konstruktoraufrufen initialisiert werden.


// Die folgenden Werte zur konkreten Objekten, Lichtquellen und Funktionen, wie Lambertian-Shading
// oder die Suche nach einem Sehstrahl für das dem Augenpunkt am nächsten liegenden Objekte,
// können auch zusammen in eine Datenstruktur für die gesammte zu
// rendernde "Szene" zusammengefasst werden.

// Die Cornelbox aufgebaut aus den Objekten
// Am besten verwendet man hier einen std::vector< ... > von Objekten.

// Punktförmige "Lichtquellen" können einfach als Vector3df implementiert werden mit weisser Farbe,
// bei farbigen Lichtquellen müssen die entsprechenden Daten in Objekt zusammengefaßt werden
// Bei mehreren Lichtquellen können diese in einen std::vector gespeichert werden.

// Sie benötigen eine Implementierung von Lambertian-Shading, z.B. als Funktion
// Benötigte Werte können als Parameter übergeben werden, oder wenn diese Funktion eine Objektmethode eines
// Szene-Objekts ist, dann kann auf die Werte teilweise direkt zugegriffen werden.
// Bei mehreren Lichtquellen muss der resultierende diffuse Farbanteil durch die Anzahl Lichtquellen geteilt werden.

// Für einen Sehstrahl aus allen Objekte, dasjenige finden, das dem Augenpunkt am nächsten liegt.
// Am besten einen Zeiger auf das Objekt zurückgeben. Wenn dieser nullptr ist, dann gibt es kein sichtbares Objekt.

// Die rekursive raytracing-Methode. Am besten ab einer bestimmten Rekursionstiefe (z.B. als Parameter übergeben) abbrechen.

//prüfen ob Sphere getroffen wird
//todo
Intersection_Context<float, 3> hit_sphere(const Vector3df& center, float radius, const Ray3df& r) {
Sphere3df sphere = {center, radius};
Intersection_Context<float, 3> context;
context.t = -INFINITY;
sphere.intersects(r, context);
return context;
}

Vector3df ray_color(const Ray3df& r) {
    Intersection_Context context = hit_sphere(Vector3df({0,0,-1}), 0.5, r);
    if (context.t > 0.0) {
        Vector3df N = context.normal;
        return 0.5f*color({N[0]+1, N[1]+1, N[2]+1});
    }

    Vector3df unit_direction = Vector(r.direction);
    float a = 0.5f*(unit_direction[1] +1);
    return (1.0f-a)*color({1.0,1.0,1.0})+a*color({0.5,0.7,1.0});
}

int main(void) {
    // Bildschirm erstellen
    auto aspect_ratio = 16.0/9.0;
    float image_width = 400.f;
        //image height calc
        float image_height = static_cast<int>(image_width/aspect_ratio);

        image_height = (image_height < 1) ? 1 : image_height;

    //Camera
    auto focal_length = 1.0f;
    auto viewport_height = 2.0f;
    float viewport_width = viewport_height * (static_cast<double>(image_width)/image_height);
    auto camera_center = Vector3df({0,0,0});

    //Calculate Vectors
    auto viewport_u = Vector3df({viewport_width,0,0});
    auto viewport_v = Vector3df({0,-viewport_height,0});
    //Calculate horizontal and vertical delta vectors
    auto pixel_delta_u = (1/image_width)*viewport_u;
    auto pixel_delta_v = (1/image_height)*viewport_v;
    //Calculate the location of the upper left pixel
    auto viewport_upper_left = camera_center - Vector3df({0,0,focal_length}) - (0.5f)*viewport_u - (0.5f)*viewport_v;
    auto pixel00_loc = viewport_upper_left + 0.5f * (pixel_delta_u + pixel_delta_v);
    // Render
    // P3 und 255 ist Kontext für das PPM Format
    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (float j = 0.f; j < image_height; ++j) {
        std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
        for (float i = 0.f; i < image_width; ++i) {
            auto pixel_center = pixel00_loc + (i*pixel_delta_u) + (j*pixel_delta_v);
            auto ray_direction = pixel_center - camera_center;
            Ray3df r(camera_center, ray_direction);
            Vector3df pixel_color = ray_color(r);
            write_color(std::cout, pixel_color);
        }

    }
    std::clog << "\rDone.                        \n";




    // Kamera erstellen
    // Für jede Pixelkoordinate x,y
    //   Sehstrahl für x,y mit Kamera erzeugen
    //   Farbe mit raytracing-Methode bestimmen
    //   Beim Bildschirm die Farbe für Pixel x,y, setzten
    std::cout << "bruh\n";

    return 0;
}

