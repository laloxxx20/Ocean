#include <string>
using namespace std;

struct Point
{
    float x;
    float y;
    float z;
};

struct Normal
{
    float nx;
    float ny;
    float nz;
};

/*class WPoint
{
    public:
        Point point;
        Normal normal;
        string orientation;
        float fase;

        WPoint();
        virtual ~WPoint();

    protected:
};*/

struct WPoint
{
    Normal normal; // Coordenadas de la normal
    Point point; // posición del vértice
    float s, t; 
};