#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glx.h>

#include <GL/glut.h>
#include <iostream>
#include <vector>
#include <math.h>
#include <fstream>
#include <sstream>
#include <string>
#include <list>
#include "wave.h"
#include "wpoint.h"

using namespace std;

#define PI 3.1416


class Ocean
{
    public:
        /*int quantity_waves;
        list<Waves> waves;
        vector<WPoint> wpoints;
        
        string orientation;
        float fase;*/
        int nb_pt_x, nb_pt_z; // quantidad de punto en X y Z
        int nb_olas;
        float dist_x, dist_z; // distancia entre dos puntos segun X y Z
        WPoint* list_points; // Tabla que contiene los puntos del terreno
        //int* list_index ; // Tabla que contiene los indicess
        Wave* list_waves; //Tabla que contiene los puntos de las olas

        bool load(char *filename) ; // carga de un archivo de modelo 
        void display(); // Visualizacion del terreno
        float computeHeight(float x , float z, float t);

        Ocean();
        ~Ocean();

    protected:
};

Ocean::Ocean(){
    nb_pt_x = 200;
    nb_pt_z = 200;
    nb_olas = 20;
    dist_x = 1;
    dist_z = 1;
    list_points = new WPoint [nb_pt_x * nb_pt_z];
    list_waves = new Wave [4* nb_olas];
    //lista_indices = new int [200*200*6]; // 200*200*6
}

bool Ocean::load(char * filename)
{    
    int fas=0;
    int i=0;

    ifstream file(filename);
    string line;
    if(file.is_open()) {
        while(!file.eof()) {
           getline(file, line);
           cout<<"linea: "<<line<<endl;
           stringstream iss(line);
           vector<string> values;
           string buff;
           while (iss >> buff)
                values.push_back(buff);           

           while(iss)
           {
                list_waves[i].amplitude = atoi(values[0].c_str());
                list_waves[i].frecuency = atoi(values[1].c_str());
                list_waves[i].orientation = atoi(values[2].c_str());
                list_waves[i].fase=fas;
           }
           i++;
        }
    }
    else
    {
        cout<<"Can't read file."<<endl;
    }
}

float Ocean::computeHeight(float x , float z, float t)
{
    float height=0.0;
    float k;
    for(int i=0;i<20;i++)
    {
        k=4.0* PI* PI* list_waves[i].frecuency * list_waves[i].frecuency/9.81;
        height += list_waves[i].amplitude* cos(k*(x*cos(list_waves[i].orientation)+z*sin(list_waves[i].orientation))-2.0* PI* list_waves[i].frecuency*t+list_waves[i].fase);
    }
    return height;
}

void Oceano::generade_coordenades()
{
    float x_i =-50;
    float z_i =-30;
    float y_i =0;
    float t=0;
    int tam = 200*200;
    
    for(int i =0;i<tam;i++)
    {
        list_points[i].point.x = x_i;
        list_points[i].s = 1/200;
        list_points[i].t = 1/200;

        list_points[i].normal.nx = 0;
        list_points[i].normal.ny = 0;
        list_points[i].normal.nz = 0;

        x_i += dist_x;
        list_points[i].point.z=z_i;
        z_i += dist_z;


        y_i= computeHeight(lista_puntos[i].point.x,lista_puntos[i].point.y, t);
        t++;
    }
}


void Ocean::display()
{
    //int tam = 200*200*6;
    //gluPerspective(40.0f, 1.0f, 0.01f, 1000.0f);
    //gluLookAt(-50,0,-300,-30,1,-50, 0,1,0);
    gluPerspective(45, 1, 0.1, 300);
    gluLookAt(50, 100, 50,    60,70,0,   0, 1, 0);
    //gluPerspective(45.0f, 1.0f, 0.01f, 100.0f);
    //gluLookAt(0.0f, 0.0f, -50.0f, 10 * cos(3*3.1416 / 180.0), 10 * sin(3*3.1416 / 180.0), 0.0f, 0.0f, 1.0f, 0.0f);
    //glBindTexture(GL_TEXTURE_3D, name);
    //glInterleavedArrays(GL_T2F_N3F_V3F, sizeof(WPoint), &list_ppoints[0].s);
    //glDrawElements(GL_TRIANGLES,tam, GL_UNSIGNED_INT, (void*)list_index);
}
