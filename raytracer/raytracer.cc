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



// Punktförmige "Lichtquellen" können einfach als Vector3df implementiert werden mit weisser Farbe,
// bei farbigen Lichtquellen müssen die entsprechenden Daten in Objekt zusammengefaßt werden
// Bei mehreren Lichtquellen können diese in einen std::vector gespeichert werden.
class light {
public:
    Vector3df center;
    Vector3df color = {0.f, 0.f, 0.f};
    explicit light(const Vector3df &center) : center(center){}
};

// Die Cornelbox aufgebaut aus den Objekten
// Am besten verwendet man hier einen std::vector< ... > von Objekten.
class raytracerObject{
public:
    Sphere3df sphere;
    Vector3df color;
    bool reflective;

    raytracerObject(): sphere({0.f, 0.f, 0.f}, 0.f), color({0.f, 0.f, 0.f}), reflective(false){}
    raytracerObject(const Sphere3df &s, const Vector3df &c, const bool &r ) : sphere(s), color(c), reflective(r){}
};

class allObjects {
public:
    std::vector<raytracerObject> objects;
    std::vector<light> lights;
    allObjects();
    allObjects(raytracerObject object) { add(object); }

    void add(raytracerObject object) { objects.push_back(object); }

//Kollisionsprüfung (hit methode)
    template<class FLOAT, size_t N>
    raytracerObject* hit(const Ray<FLOAT, N> &r, Intersection_Context<FLOAT, N> &rec) {
        raytracerObject nearest;
        Intersection_Context<FLOAT, N> temp_rec;
        float closest_so_far = std::numeric_limits<float>::max();
//nächstes Object finden
        for (const auto &object: objects) {
            if (object.sphere.intersects(r, temp_rec)) {
                if (closest_so_far > temp_rec.t && temp_rec.t > 0) {
                    closest_so_far = temp_rec.t;
                    nearest = object;
                    rec = temp_rec;
                }
            }
        }
//keine kollision
        if(closest_so_far == std::numeric_limits<float>::max())
            return nullptr;
//Treffer melden
        return new raytracerObject(nearest.sphere, nearest.color, nearest.reflective);
    }
};


// Sie benötigen eine Implementierung von Lambertian-Shading, z.B. als Funktion
// Benötigte Werte können als Parameter übergeben werden, oder wenn diese Funktion eine Objektmethode eines
// Szene-Objekts ist, dann kann auf die Werte teilweise direkt zugegriffen werden.
// Bei mehreren Lichtquellen muss der resultierende diffuse Farbanteil durch die Anzahl Lichtquellen geteilt werden.

// Für einen Sehstrahl aus allen Objekte, dasjenige finden, das dem Augenpunkt am nächsten liegt.
// Am besten einen Zeiger auf das Objekt zurückgeben. Wenn dieser nullptr ist, dann gibt es kein sichtbares Objekt.

// Die rekursive raytracing-Methode. Am besten ab einer bestimmten Rekursionstiefe (z.B. als Parameter übergeben) abbrechen.


//Farbe
template<class FLOAT, size_t N>
    Vector<FLOAT, N> ray_color(const Ray<FLOAT, N> &r, allObjects &box, int depth) {
        //Erstertreffer
        Intersection_Context<FLOAT, N> rec;
        //Schattentreffer
        Intersection_Context<FLOAT, N> shader_Rec;
        //Prüfen ob Ray ein Objekt trift.
        raytracerObject *object = box.hit(r, rec);
        //Prüfen ob die Rekursionstiefe nicht überschritten ist
        if (depth > 0 && box.hit(r, rec) != nullptr) {
            //berechnung vom Lambertian Vektor
            Vector3df Lambertian = (box.lights[0].center - rec.intersection);
            //Schattenstrahl erzeugen
            Ray3df shaderRay = {rec.intersection + 0.01f * rec.normal, Lambertian};
            //Schattenstrahl senden
            box.hit(shaderRay, shader_Rec);
            float intensity = 0.f;
            //Schattenstrahl Intensität reduzierten wenn Objekte getroffen werden
            if (shader_Rec.t > 0 && shader_Rec.t < 1) {
                intensity = 0.3f;
            } else {
                //Vektor Normalisieren und Intensität
                Lambertian.normalize();
                intensity = rec.normal * Lambertian;
            }
            //mindestintensität
            if (intensity < 0.3f) {
                intensity = 0.3f;
            }
            //reflektion einbauen
            if (object->reflective) {
                //reflektionsvektor erzeugen
                Vector3df reflective_Vec =  r.direction - 2.f * (r.direction * rec.normal) * rec.normal;

                //get_reflective hat irgendwie nicht geklappt

                //reflektierenden Ray erzeugen
                Ray3df reflective_r = {rec.intersection + 0.1f * rec.normal, reflective_Vec};
                //Rekursiv Farbe der reflektion finden
                return intensity * ray_color(reflective_r, box, depth - 1);
            }
            //rückgabe Farbe + intensität
            return intensity * object->color;
        }
        //wenn nichts getroffen wird schwarz zurückgeben
        return Vector3df{0.f, 0.f, 0.f};
    }


int main(void) {
    // Bildschirm erstellen
    auto aspect_ratio = 1.5/1.0;
    float image_width = 1000.f;
        //image height calc
        float image_height = static_cast<int>(image_width/aspect_ratio);

        image_height = (image_height < 1) ? 1 : image_height;
    //Cornell Box erstellen
    //Rechte Wand
    allObjects box(raytracerObject(Sphere3df({10021.f, 0.0f, 0.f }, 10000.f), Vector3df({0.f, 1.f, 0.f}), false));
    //Linke Wand
    box.add(raytracerObject(Sphere3df({ -10021.f, 0.0f, 0.f }, 10000.f), Vector3df({1.f, 0.f, 0.f}), false));
    //Boden
    box.add(raytracerObject(Sphere3df({0.f, -10012.0f, 0.f}, 10000.f), Vector3df({1.f, 1.f, 1.f}), false));
    //Decke
    box.add(raytracerObject(Sphere3df({0.f, 10012.0f, 0.f}, 10000.f), Vector3df({1.f, 1.f, 1.f}), false));
    //Rückwand
    box.add(raytracerObject(Sphere3df({0.0f, 0.0f, -10030.f}, 10000.f), Vector3df({1.f, 1.f, 1.f}), false));
    //Vordere Wand
    box.add(raytracerObject(Sphere3df({0.0f, 0.0f, 10030.f}, 10000.f), Vector3df({1.f, 1.f, 1.f}), false));

    //Lichtquelle
    light light1(Vector3df {0.f,11.f, -18.f});
    //hinzufügen
    box.lights.push_back(light1);


    //Kugeln
    box.add(raytracerObject(Sphere3df({-9.0f, -8.f, -20.f}, 4.f), Vector3df({0.5f, .5f, .5f}), false));
    box.add(raytracerObject(Sphere3df({9.0f, -8.f, -20.f}, 4.f), Vector3df({0.5f, .5f, .5f}), true));


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
            Vector3df pixel_color = ray_color(r,box,5);
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

