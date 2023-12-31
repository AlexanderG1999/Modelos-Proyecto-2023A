﻿#pragma once
//---------------------------------------------------------------------------
#ifndef HeaderH
#define HeaderH
//---------------------------------------------------------------------------

#include <stdio.h>
#include <math.h>
#include <iostream>

//---------------------------------------------------------------------------
#define None                    -1
//Projection-----------------------------------------------------------------
#define xy                      0
#define xz                      1
#define yz                      2
//Constants------------------------------------------------------------------
#define PI                      3.1415926535897932384626433832795
#define NUM_COLORS              4
#define V_SON                   340
#define MaxNPoints              200     // maximo numero de puntos
#define MaxNSelectedPlanes      2000    // maximo numero de planos seleccionados
#define MaxNChar                50      // maximo numero de caracteres
#define MAXDOUBLE               1000000
#define N_REC                   27
#define DUR_SIM                 1000
//---------------------------------------------------------------------------


using namespace std;

//---------------------------------------------------------------------------
class Vector {
public:
    double x, y, z;

    Vector operator+(Vector v2) { // suma
        Vector v1;
        v1.x = x + v2.x;
        v1.y = y + v2.y;
        v1.z = z + v2.z;
        return v1;
    };
    Vector operator-(Vector v2) { // resta
        Vector v1;
        v1.x = x - v2.x;
        v1.y = y - v2.y;
        v1.z = z - v2.z;
        return v1;
    };
    Vector operator*(double f) { // multiplicacion por un escalar
        Vector v;
        v.x = x * f;
        v.y = y * f;
        v.z = z * f;
        return v;
    };
    Vector operator/(double f) { // division por un escalar
        Vector v;
        v.x = x / f;
        v.y = y / f;
        v.z = z / f;
        return v;
    };
    double operator*(Vector v) { // producto escalar

        double f;
        f = x * v.x + y * v.y + z * v.z;
        return f;


    };
    Vector operator/(Vector v2) { // producto vectorial
        Vector v1;
        v1.x = y * v2.z - z * v2.y;
        v1.y = -x * v2.z + z * v2.x;
        v1.z = x * v2.y - y * v2.x;
        return v1;
    };
    void operator*=(double f) {
        x *= f;
        y *= f;
        z *= f;
    };
    void operator/=(double f) {
        x /= f;
        y /= f;
        z /= f;
    };
    void operator=(double f) {  // dar un mismo valor a x,y y z
        x = y = z = f;
    };

    bool operator==(Vector v) { // igualdad entre vectores
        if (x == v.x && y == v.y && z == v.z)
            return 1;
        else
            return 0;
    };
    bool operator!=(Vector v) { // desigualdad entre vectores
        if (x == v.x && y == v.y && z == v.z)
            return 0;
        else
            return 1;
    };
    double Angle(Vector v) { // angulo entre dos vectores
        double angle, f;
        f = x * v.x + y * v.y + z * v.z; // producto escalar
        f /= sqrt(x * x + y * y + z * z);
        f /= sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
        angle = acos(f) / PI * 180;
        return angle;
    };
    double Max(void) { // valor maximo entre las coordenadas
        double max;
        if (x > y) {
            max = x;
        }
        else {
            max = y;
        }
        if (z > max) {
            max = z;
        }
        return max;
    };
    double Min(void) { // valor minimo entre las coordenadas
        double min;
        if (x < y) {
            min = x;
        }
        else {
            min = y;
        }
        if (z < min) {
            min = z;
        }
        return min;
    };
    Vector Abs(void) { // valor absoluto de las coordenadas
        Vector v;
        v.x = fabs(x);
        v.y = fabs(y);
        v.z = fabs(z);
        return v;
    };
    double Module(void) { // modulo de un vector
        return sqrt(x * x + y * y + z * z);
    };
};
//---------------------------------------------------------------------------
class point {
public:
    double x, y, z;

    point() {
        x = 0;
        y = 0;
        z = 0;
    };

    point(double X, double Y, double Z) {
        x = X;
        y = Y;
        z = Z;
    };

    point operator+(Vector v) { // trasladar un punto
        point p;
        p.x = x + v.x;
        p.y = y + v.y;
        p.z = z + v.z;
        return p;
    };
    point operator+(point p2) { // suma de dos puntos
        point p1;
        p1.x = x + p2.x;
        p1.y = y + p2.y;
        p1.z = z + p2.z;
        return p1;
    };
    point operator+(double f) { // suma de dos puntos
        point p1;
        p1.x = x + f;
        p1.y = y + f;
        p1.z = z + f;
        return p1;
    };
    Vector operator-(point p) { // resta dos puntos para obtener un vector
        Vector v;
        v.x = x - p.x;
        v.y = y - p.y;
        v.z = z - p.z;
        return v;
    };
    point operator*(double f) { // multiplicacion por un escalar
        point p;
        p.x = x * f;
        p.y = y * f;
        p.z = z * f;
        return p;
    };
    point operator/(double f) { // division por un escalar
        point p;
        p.x = x / f;
        p.y = y / f;
        p.z = z / f;
        return p;
    };
    void operator=(double f) {  // dar mismo valor a x,y y z
        x = y = z = f;
    };

    bool operator==(point p) {  // igualdad entre puntos
        if (x == p.x && y == p.y && z == p.z)
            return 1;
        else
            return 0;
    };
    bool operator!=(point p) {  // desigualdad entre puntos
        if (x == p.x && y == p.y && z == p.z)
            return 0;
        else
            return 1;
    };

    void Clear() {
        x = 0;
        y = 0;
        z = 0;
    };

    double Max(void) { // valor maximo entre las coordenadas
        double max;
        if (x > y) {
            max = x;
        }
        else {
            max = y;
        }
        if (z > max) {
            max = z;
        }
        return max;
    };
    double Min(void) { // valor minimo entre las coordenadas
        double min;
        if (x < y) {
            min = x;
        }
        else {
            min = y;
        }
        if (z < min) {
            min = z;
        }
        return min;
    };
    point Abs(void) { // valor absoluto de las coordenadas
        point v;
        v.x = fabs(x);
        v.y = fabs(y);
        v.z = fabs(z);
        return v;
    };

    double distancia(point p2) { // distancia entre dos puntos
        return sqrt((p2.x - x) * (p2.x - x) + (p2.y - y) * (p2.y - y) + (p2.z - z) * (p2.z - z));
    };

    Vector restaPuntos(point b) {
        Vector v;
        v.x = x - b.x;
        v.y = y - b.y;
        v.z = z - b.z;
        return v;
    }

    void print() { // imprimir punto
        cout << "(X: " << x << " Y: " << y << " Z: " << z << ")" << endl;
    };

};

//---------------------------------------------------------------------------
class triangle {
public:
    point p0, p1, p2, bc; // triangle Points
    int Projection; // projection
    double a0;      // a0 constante para calculos futuros
    int ID;         // identificador �nico

    triangle() {
        p0 = 0;
        p1 = 0;
        p2 = 0;
        bc = 0;
        Projection = 0;
        a0 = 0;
        ID = 0;
    };

    void operator=(triangle t) {
        p0 = t.p0;
        p1 = t.p1;
        p2 = t.p2;
        bc = t.bc;
        Projection = t.Projection;
        a0 = t.a0;
        ID = t.ID;
    };

    void Clear() {
        p0 = 0;
        p1 = 0;
        p2 = 0;
        bc = 0;
        Projection = 0;
        a0 = 0;
        ID = 0;
    };

    void Centroid() {
        bc = (p0 + p1 + p2) / 3;
    };

    double solidAngle(point b) {
        double area = 0.0, d = 0.2;
        triangle t;
        Vector v0, v1, v2;
        v0 = p0 - b;
        v1 = p1 - b;
        v2 = p2 - b;
        v0 = v0 / v0.Module();
        v1 = v1 / v1.Module();
        v2 = v2 / v2.Module();
        t.p0 = b + (v0 * d);
        t.p1 = b + (v1 * d);
        t.p2 = b + (v2 * d);
        area = t.TriangleArea();
        return area;
    };

    double TriangleArea() {
        double a;
        Vector v = (p1 - p0) / (p2 - p0);
        a = 0.5 * v.Module();
        return a;
    };

    void CalculateProjection() {
        Vector n;
        double x0, y0, z0, x1, y1, z1, x2, y2, z2;
        x0 = p0.x;
        y0 = p0.y;
        z0 = p0.z;
        x1 = p1.x;
        y1 = p1.y;
        z1 = p1.z;
        x2 = p2.x;
        y2 = p2.y;
        z2 = p2.z;
        n = (p1 - p0) / (p2 - p0);
        n.x = n.x * n.x;
        n.y = n.y * n.y;
        n.z = n.z * n.z;
        if ((n.x >= n.y) && (n.x >= n.z)) {                        //proje��o yz
            Projection = yz;
            a0 = 1 / (-y1 * z0 + y2 * z0 + y0 * z1 - y2 * z1 - y0 * z2 + y1 * z2 + 0.000001);
        }
        if ((n.y >= n.x) && (n.y >= n.z)) {                        //proje��o xz
            Projection = xz;
            a0 = 1 / (-x1 * z0 + x2 * z0 + x0 * z1 - x2 * z1 - x0 * z2 + x1 * z2 + 0.000001);
        }
        if ((n.z >= n.x) && (n.z >= n.y)) {                        //proje��o xy
            Projection = xy;
            a0 = 1 / (-x1 * y0 + x2 * y0 + x0 * y1 - x2 * y1 - x0 * y2 + x1 * y2 + 0.000001);
        }
    };
};
//---------------------------------------------------------------------------
class source {
public:
    point p;                // Posicion
    Vector* Rays;           // Direcciones de partida de los rayos
    int NRAYS;              // Numero de rayos
    double eF;              // Energia inicial de la fuente
    triangle IcoFace[20];   // Representacion grafica de la fuente
    double VisualRadius;    // Tamaño de la fuente (radio visual)
    //color Color;            // Color de la fuente

    source() {   // Inicializo las variables de la clase.
        p = 0.0;
        eF = 0.0;
        NRAYS = 0;
        Rays = NULL;

        //Color.R = 1;
        //Color.G = 0.5;
        //Color.B = 0.5;

        VisualRadius = 0.3;

        // create icosaedron
        double S, R;
        point IcoVertex[12];

        // create vertexes
        S = 2 / sqrt(5);
        R = (5 - sqrt(5)) / 5;
        IcoVertex[0].x = 0;
        IcoVertex[0].y = 0;
        IcoVertex[0].z = 1;
        for (int i = 1; i < 6; i++) {
            IcoVertex[i].x = S * cos((PI * i * 72) / 180);
            IcoVertex[i].y = S * sin((PI * i * 72) / 180);
            IcoVertex[i].z = 1 - R;
            IcoVertex[i + 5].x = S * cos((72 * PI * i) / 180 + (36 * PI) / 180);
            IcoVertex[i + 5].y = S * sin((72 * PI * i) / 180 + (36 * PI) / 180);
            IcoVertex[i + 5].z = R - 1;
        }
        IcoVertex[11].x = 0;
        IcoVertex[11].y = 0;
        IcoVertex[11].z = -1;

        // create faces
        IcoFace[0].p0 = IcoVertex[0];   IcoFace[0].p1 = IcoVertex[1];   IcoFace[0].p2 = IcoVertex[2];
        IcoFace[1].p0 = IcoVertex[0];   IcoFace[1].p1 = IcoVertex[2];   IcoFace[1].p2 = IcoVertex[3];
        IcoFace[2].p0 = IcoVertex[0];   IcoFace[2].p1 = IcoVertex[3];   IcoFace[2].p2 = IcoVertex[4];
        IcoFace[3].p0 = IcoVertex[0];   IcoFace[3].p1 = IcoVertex[4];   IcoFace[3].p2 = IcoVertex[5];
        IcoFace[4].p0 = IcoVertex[0];   IcoFace[4].p1 = IcoVertex[5];   IcoFace[4].p2 = IcoVertex[1];
        IcoFace[5].p0 = IcoVertex[1];   IcoFace[5].p1 = IcoVertex[6];   IcoFace[5].p2 = IcoVertex[2];
        IcoFace[6].p0 = IcoVertex[2];   IcoFace[6].p1 = IcoVertex[6];   IcoFace[6].p2 = IcoVertex[7];
        IcoFace[7].p0 = IcoVertex[2];   IcoFace[7].p1 = IcoVertex[7];   IcoFace[7].p2 = IcoVertex[3];
        IcoFace[8].p0 = IcoVertex[3];   IcoFace[8].p1 = IcoVertex[7];   IcoFace[8].p2 = IcoVertex[8];
        IcoFace[9].p0 = IcoVertex[3];   IcoFace[9].p1 = IcoVertex[8];   IcoFace[9].p2 = IcoVertex[4];
        IcoFace[10].p0 = IcoVertex[4];  IcoFace[10].p1 = IcoVertex[8];  IcoFace[10].p2 = IcoVertex[9];
        IcoFace[11].p0 = IcoVertex[4];  IcoFace[11].p1 = IcoVertex[9];  IcoFace[11].p2 = IcoVertex[5];
        IcoFace[12].p0 = IcoVertex[5];  IcoFace[12].p1 = IcoVertex[9];  IcoFace[12].p2 = IcoVertex[10];
        IcoFace[13].p0 = IcoVertex[5];  IcoFace[13].p1 = IcoVertex[10]; IcoFace[13].p2 = IcoVertex[1];
        IcoFace[14].p0 = IcoVertex[1];  IcoFace[14].p1 = IcoVertex[10]; IcoFace[14].p2 = IcoVertex[6];
        IcoFace[15].p0 = IcoVertex[6];  IcoFace[15].p1 = IcoVertex[11]; IcoFace[15].p2 = IcoVertex[7];
        IcoFace[16].p0 = IcoVertex[7];  IcoFace[16].p1 = IcoVertex[11]; IcoFace[16].p2 = IcoVertex[8];
        IcoFace[17].p0 = IcoVertex[8];  IcoFace[17].p1 = IcoVertex[11]; IcoFace[17].p2 = IcoVertex[9];
        IcoFace[18].p0 = IcoVertex[9];  IcoFace[18].p1 = IcoVertex[11]; IcoFace[18].p2 = IcoVertex[10];
        IcoFace[19].p0 = IcoVertex[10]; IcoFace[19].p1 = IcoVertex[11]; IcoFace[19].p2 = IcoVertex[6];
    };

    void createRays(double NumberOfRays) {
        // matriz das Arestas {1o ponto da aresta, 2o ponto da aresta, Posi��o dos pontos da aresta na matriz Rays}
        int A[30][3] = { {0,1,0}, {0,2,0}, {0,3,0}, {0,4,0}, {0,5,0},
                        {1,6,0}, {2,6,0}, {2,7,0}, {3,7,0}, {3,8,0},
                        {4,8,0}, {4,9,0}, {5,9,0}, {5,10,0},{1,10,0},
                        {6,11,0},{7,11,0},{8,11,0},{9,11,0},{10,11,0},
                        {1,2,0}, {2,3,0}, {3,4,0}, {4,5,0}, {5,1,0},
                        {6,7,0}, {7,8,0}, {8,9,0}, {9,10,0},{10,6,0}
        };
        // matriz dos triangulos {1a aresta, 2a aresta, [0] V em p� [-1] V de cabe�a pra baixo}
        int T[20][3] = { {0,1,0},   {1,2,0},   {2,3,0},   {3,4,0},   {4,0,0},
                        {5,6,-1},  {6,7,0},   {7,8,-1},  {8,9,0},   {9,10,-1},
                        {10,11,0}, {11,12,-1},{12,13,0}, {13,14,-1},{14,5,0},
                        {15,16,-1},{16,17,-1},{17,18,-1},{18,19,-1},{19,15,-1}
        };
        int i, j, k, n, m, RAY;
        double S, R, xB, yB, zB, xC, yC, zC, c[8];
        // create Rays matrix
        if (NRAYS > 0)
            delete[] Rays;
        n = int(floor(sqrt((NumberOfRays - 2) / 10) + 0.5));
        NRAYS = int(2 + 10 * pow(n, 2));
        Rays = new Vector[NRAYS];
        // calculating the icosaedron vertives
        S = 2 / sqrt(5);
        R = (5 - sqrt(5)) / 5;
        Rays[0].x = 0;
        Rays[0].y = 0;
        Rays[0].z = 1;
        for (i = 1; i < 6; i++) {
            Rays[i].x = S * cos((PI * i * 72) / 180);
            Rays[i].y = S * sin((PI * i * 72) / 180);
            Rays[i].z = 1 - R;
            Rays[i + 5].x = S * cos((72 * PI * i) / 180 + (36 * PI) / 180);
            Rays[i + 5].y = S * sin((72 * PI * i) / 180 + (36 * PI) / 180);
            Rays[i + 5].z = R - 1;
        }
        Rays[11].x = 0;
        Rays[11].y = 0;
        Rays[11].z = -1;
        RAY = 12;
        // calculating the rays on the icosaedron edges
        for (j = 0; j < 30; j++) {
            A[j][2] = RAY;
            xB = Rays[A[j][0]].x;
            yB = Rays[A[j][0]].y;
            zB = Rays[A[j][0]].z;
            xC = Rays[A[j][1]].x;
            yC = Rays[A[j][1]].y;
            zC = Rays[A[j][1]].z;
            c[0] = pow(xC, 2) * (pow(yB, 2) + pow(zB, 2)) + pow(yC * zB - yB * zC, 2) - 2 * xB * xC * (yB * yC + zB * zC) + pow(xB, 2) * (pow(yC, 2) + pow(zC, 2));
            c[1] = acos(xB * xC + yB * yC + zB * zC);
            c[2] = -xC * (yB * yC + zB * zC) + xB * (pow(yC, 2) + pow(zC, 2));
            c[3] = xC * (pow(yB, 2) + pow(zB, 2)) - xB * (yB * yC + zB * zC);
            c[4] = pow(xC, 2) * yB - xB * xC * yC + zC * (-yC * zB + yB * zC);
            c[5] = -xB * xC * yB + pow(xB, 2) * yC + zB * (yC * zB - yB * zC);
            c[6] = pow(xC, 2) * zB - xB * xC * zC + yC * (yC * zB - yB * zC);
            c[7] = -xB * xC * zB + pow(xB, 2) * zC + yB * (-yC * zB + yB * zC);
            for (i = 1; i < n; i++) {
                Rays[RAY].x = (c[2] * cos(i * c[1] / n) + c[3] * cos((n - i) * c[1] / n)) / c[0];
                Rays[RAY].y = (c[4] * cos(i * c[1] / n) + c[5] * cos((n - i) * c[1] / n)) / c[0];
                Rays[RAY].z = (c[6] * cos(i * c[1] / n) + c[7] * cos((n - i) * c[1] / n)) / c[0];
                RAY++;
            }
        }
        // calculating the rays on the icosaedron faces
        for (k = 0; k < 20; k++)
            for (j = 1; j < n; j++) {
                xB = Rays[A[T[k][0]][2] + j - 1].x;
                yB = Rays[A[T[k][0]][2] + j - 1].y;
                zB = Rays[A[T[k][0]][2] + j - 1].z;
                xC = Rays[A[T[k][1]][2] + j - 1].x;
                yC = Rays[A[T[k][1]][2] + j - 1].y;
                zC = Rays[A[T[k][1]][2] + j - 1].z;
                c[0] = pow(xC, 2) * (pow(yB, 2) + pow(zB, 2)) + pow(yC * zB - yB * zC, 2) - 2 * xB * xC * (yB * yC + zB * zC) + pow(xB, 2) * (pow(yC, 2) + pow(zC, 2));
                c[1] = acos(xB * xC + yB * yC + zB * zC);
                c[2] = -xC * (yB * yC + zB * zC) + xB * (pow(yC, 2) + pow(zC, 2));
                c[3] = xC * (pow(yB, 2) + pow(zB, 2)) - xB * (yB * yC + zB * zC);
                c[4] = pow(xC, 2) * yB - xB * xC * yC + zC * (-yC * zB + yB * zC);
                c[5] = -xB * xC * yB + pow(xB, 2) * yC + zB * (yC * zB - yB * zC);
                c[6] = pow(xC, 2) * zB - xB * xC * zC + yC * (yC * zB - yB * zC);
                c[7] = -xB * xC * zB + pow(xB, 2) * zC + yB * (-yC * zB + yB * zC);
                if (T[k][2] == 0)m = j;
                else m = n - j;
                for (i = 1; i < m; i++) {
                    Rays[RAY].x = (c[2] * cos(i * c[1] / m) + c[3] * cos((m - i) * c[1] / m)) / c[0];
                    Rays[RAY].y = (c[4] * cos(i * c[1] / m) + c[5] * cos((m - i) * c[1] / m)) / c[0];
                    Rays[RAY].z = (c[6] * cos(i * c[1] / m) + c[7] * cos((m - i) * c[1] / m)) / c[0];
                    RAY++;
                }
            }
    };
};

//---------------------------------------------------------------------------
class plane {
public:

    //color       Color;                  //color RGB
    int         NP;                     //Number of Points
    point* p;                     //plane Points
    int         NT;                     //Number of Triangles
    triangle* t;                     //plane Triangles
    Vector      n;                      //Normal Vector
    //material    m;                      //Material del plano

    plane() {
        int P, T;
        //Color.R = 0.5;
        //Color.G = 0.5;
        //Color.B = 1;
        NP = 0;
        p = NULL;
        NT = 0;
        t = NULL;
        n = 0;
        //m.alfa = 0.2;
        //m.delta = 0.15;
    }

    void NewPoints(int N) {
        int P;
        point* tp;
        tp = new point[NP + N];
        for (P = 0; P < NP; P++) {
            tp[P] = p[P];
        }
        for (P = NP; P < NP + N; P++) {
            tp[P].Clear();
        }
        if (NP > 0) {
            delete[] p;
            p = NULL;
        }
        p = tp;
        NP += N;
    };

    void DeletePoint(int IP) {
        int P, j = 0;
        if (IP >= 0 && IP < NP) {
            point* tp;
            tp = new point[NP - 1];
            for (P = 0; P < NP; P++) {
                if (P != IP) {
                    tp[j] = p[P];
                    j++;
                }
            }
            delete[] p;
            p = tp;
            NP -= 1;
        }
    };

    void NewTriangle(int N) {
        int T;
        triangle* tt;
        tt = new triangle[NT + N];
        for (T = 0; T < NT; T++) {
            tt[T] = t[T];
        }
        for (T = NT; T < NT + N; T++) {
            tt[T].Clear();
        }
        if (NP > 0) {
            delete[] t;
            t = NULL;
        }
        t = tt;
        NT += N;
    };

    void DeleteTriangle(int IT) {
        int T, j = 0;
        if (IT >= 0 && IT < NT) {
            triangle* tt;
            tt = new triangle[NT - 1];
            for (T = 0; T < NT; T++) {
                if (T != IT) {
                    tt[j] = t[T];
                    j++;
                }
            }
            delete[] t;
            t = tt;
            NT -= 1;
        }
    };

    void PointGenTriangle() { //Genera 2 triangulos a partir de los v�rtices de un cuadrado
        NewTriangle(NP - 2);
        int i = 1;
        for (int T = 0; T < NT; T++) {
            i--;
            t[T].p0.x = p[i].x;
            t[T].p0.y = p[i].y;
            t[T].p0.z = p[i].z;
            i++;
            if (i == NP) i = 0;
            t[T].p1.x = p[i].x;
            t[T].p1.y = p[i].y;
            t[T].p1.z = p[i].z;
            i++;
            if (i == NP) i = 0;
            t[T].p2.x = p[i].x;
            t[T].p2.y = p[i].y;
            t[T].p2.z = p[i].z;
            i++;
        }
    };

    void Clear() {
        /*Color.R = 0.5;
        Color.G = 0.5;
        Color.B = 1;*/
        NP = 0;
        delete[] p;
        p = NULL;
        NT = 0;
        delete[] t;
        t = NULL;
        n = 0;
    };

    bool IsConvex() {
        int n;
        Vector u, v;
        double ang;
        for (int n = 1; n < NP - 1; n++) { // ficam faltando 2 pontos (primeiro e ultimo)
            u = p[n - 1] - p[n];
            v = p[n + 1] - p[n];
            ang = u.Angle(v);
            if (ang > 180)return false;
        }
        return true;
    }
};
//---------------------------------------------------------------------------
struct reflection { // respuesta al proceso de trazado de rayos.
    point r[MaxNPoints];                    // puntos de aplicacion
    double d[MaxNPoints];                   // distancia entre punto y punto
    int idTriangle[MaxNPoints];             // id unico del triangulo por cuarto donde se choco
    int Plane[MaxNPoints];                  // nro. del plano por cuarto donde se choco
    int Triangle[MaxNPoints];               // nro. del triangulo por plano donde se choco
    int N;                                  // JFLN: Number of reflections
    bool lost;                              // JFLN: If lost equal true, it's a reflection of a lost ray
    int Ray;                                // JFLN: Number of RAY in preview
};
//---------------------------------------------------------------------------
class room {
public:
    int			NP;		// Number of Planes
    plane* p;		// Planes
    double		maxd;	// Maxima distancia entre dos puntos en la sala.
    //receptor* r;     // Number of receptors (microphones)
    int         NR;     // Number of receptors

    room() {
        NP = 0;
        p = NULL;
        NR = 0;
        //r = NULL;
        maxd = 0.0;
    };

    void Clear() {
        if (NP > 0) {
            for (int i = 0; i < NP; i++) {
                p[i].Clear();
            }
            delete[] p;
            p = NULL;
        }
        NP = 0;

        /*if (NR > 0) {
            for (int i = 0; i < NR; i++) {
                r[i].Clear();
            }
            delete[] r;
            r = NULL;
        }*/
        NR = 0;

        maxd = 0.0;
    };

    void Init() {
        NP = 0;
        p = NULL;
        NR = 0;
        //r = NULL;
        maxd = 0.0;
    };

    bool Inner(point p, triangle t) { // verificar si un punto pertenece al triangulo
        double a1, a2, x, y, z, x0, y0, z0, x1, y1, z1, x2, y2, z2;

        x = p.x;
        y = p.y;
        z = p.z;

        x0 = t.p0.x;
        y0 = t.p0.y;
        z0 = t.p0.z;
        x1 = t.p1.x;
        y1 = t.p1.y;
        z1 = t.p1.z;
        x2 = t.p2.x;
        y2 = t.p2.y;
        z2 = t.p2.z;

        if (t.Projection == yz) {                              // proyeccion yz
            a1 = -t.a0 * (-y0 * z + y2 * z + y * z0 - y2 * z0 - y * z2 + y0 * z2);
            a2 = -t.a0 * (y0 * z - y1 * z - y * z0 + y1 * z0 + y * z1 - y0 * z1);
        }
        if (t.Projection == xz) {                              // proyeccion xz
            a1 = -t.a0 * (-x0 * z + x2 * z + x * z0 - x2 * z0 - x * z2 + x0 * z2);
            a2 = -t.a0 * (x0 * z - x1 * z - x * z0 + x1 * z0 + x * z1 - x0 * z1);
        }
        if (t.Projection == xy) {                              // proyeccion xy
            a1 = -t.a0 * (-x2 * y0 + x * y0 + x0 * y2 - x * y2 - x0 * y + x2 * y);
            a2 = t.a0 * (-x1 * y0 + x * y0 + x0 * y1 - x * y1 - x0 * y + x1 * y);
        }

        if ((a1 + a2 <= 1) && (a1 >= 0) && (a2 >= 0))
            return true;
        else
            return false;

    };

    double IntersectionDistance(Vector n, point p, Vector u, point o) {
        /*JFLN:
                Vector n is the normal Vector of the plane
                point p is one of the vertex of the plane
                Vector u is the ray
                point o is the initial position of the ray
        */
        double d, m;
        m = n * u;
        //JFLN: Has to have an error tolerance
        if (m == 0)
            return -1;
        d = (n * (p - o)) / m;
        return d;
    };

    void MaxDistance() {
        maxd = 0;
        float tmpd = 0;
        for (int i1 = 0; i1 < NP; i1++) {
            for (int j1 = 0; j1 < p[i1].NP; j1++) {
                for (int i2 = 0; i2 < NP; i2++) {
                    for (int j2 = 0; j2 < p[i2].NP; j2++) {
                        tmpd = p[i1].p[j1].distancia(p[i2].p[j2]);
                        if (maxd < tmpd)
                            maxd = tmpd;
                    }
                }
            }
        }
    };

    void NewPlanes(int N) {
        int P;
        plane* tp;
        tp = new plane[NP + N];
        for (P = 0; P < NP; P++) {
            tp[P] = p[P];
        }
        for (P = NP; P < NP + N; P++) {
            tp[P].Clear();
        }
        if (NP > 0) {
            delete[] p;
            p = NULL;
        }
        p = tp;
        NP += N;
    };

    double Module(Vector v) { //JFLN: Returns the Vector's module
        double m;
        m = sqrt(v * v);
        return m;
    };

    Vector Normal(Vector v1) { //JFLN: Returns the Vector's unitary Vector
        //compare with the function unitario because this funtion is the same in MathFuntions

        double m;
        Vector v2;
        m = Module(v1);
        if (m == 0)
            v2 = 0;
        else
            v2 = v1 / m;
        return v2;

    };

    reflection* RayTracing(point origen, Vector* Rays, int NRAYS) {

        reflection* ry;
        ry = NULL;

        int
            IntersectedPlane,       // indice del plano interesectado
            IntersectedTriangle,    // indice del triangulo intersectado por plano
            IntersectedTriangleId,  // id unico del tri�ngulo intersectado
            NReflections,           // numero actual de reflexion
            TNReflections,          // numero total de reflexiones
            LostRays = 0;             // contador de rayos perdidos

        double      // distancia al punto de intersecci�n
            d1,
            d2;

        point       // puntos para determinar donde existe intersecci�n con el plano
            p1,
            p2,
            p3;

        bool Stop;  // bandera para detener el procedimiento
        Vector v;   // vector incidente
        point o;    // punto de partida (origen del Vector incidente)

        ry = new reflection[NRAYS];

        NReflections = 0;
        TNReflections = 0;

        // inicio del RAY-TRACING
        MaxDistance();
        for (int R = 0; R < NRAYS; R++) {
            v = Rays[R];  // asigno el primer rayo del arreglo original a v
            o = origen;

            // como no existe aun ninguna reflexion, inicializo con el valor -1
            IntersectedPlane = -1;
            IntersectedTriangle = -1;
            IntersectedTriangleId = -1;

            Stop = false;

            ry[R].N = 0;            // numero de reflexion, inincialmente 0
            ry[R].r[0] = o;         // punto de partida, inicialmente el centro de la fuente
            ry[R].d[0] = 0.0;       // distancia recorrida, inicialmente 0
            ry[R].lost = false;     // reflexion perdida? inicialmente falso
            ry[R].Ray = R;          // rayo asociado a la reflexion

            while (!Stop) {   // lazo para realizar varias reflexiones
                d1 = maxd;    // asigno a d1 la m�xima distancia entre puntos de la sala
                for (int P = 0; P < NP; P++) { // recorro todos los planos de la sala
                    if ((p[P].n * v) < 0) { // existe ruta de intersecci�n entre un plano y un Vector //  && (P!=LastIntersectedPlane)
                        d2 = IntersectionDistance(p[P].n, p[P].p[0], v, o);
                        if ((d2 > 0.0) && (d2 < d1)) { // verifico que la distancia de vuelo del rayo no sea cero && que no sea mayor a d1 (m�xima distancia de vuelo o otra ruta de intersecci�n con otro plano)
                            p2 = o + (v * d2); // obtengo el punto de incidencia en el plano
                            for (int T = 0; T < p[P].NT; T++) { // recorro todos los tri�ngulos del plano
                                if (Inner(p2, p[P].t[T])) {// verifica si el punto pertenece al tri�ngulo
                                    // registro la distancia y el punto de intersecci�n
                                    d1 = d2;
                                    p1 = p2;
                                    // registro los identificadores del elemento interesectado
                                    IntersectedPlane = P;
                                    IntersectedTriangle = T;
                                    IntersectedTriangleId = p[P].t[T].ID;
                                    T = p[P].NT; // para forzar la finalizaci�n del recorrido de tri�ngulos
                                }
                            }
                        }
                    }
                }
                if (d1 < maxd && IntersectedPlane != -1) {// si hubo intersecci�n
                    // calculo el Vector reflejo
                    p3 = o;
                    o = p1;// nuevo punto de partida del Vector reflejado
                    v = Normal(v - (p[IntersectedPlane].n * (v * p[IntersectedPlane].n * 2))); // formula del Vector reflejo
                    NReflections++;
                    TNReflections += NReflections;
                    ry[R].r[NReflections] = p1;                                   // puntos de aplicaci�n
                    ry[R].d[NReflections] = Module(p1 - p3);                        // distancia entre punto y punto
                    ry[R].idTriangle[NReflections] = IntersectedTriangleId;       // id unico del tri�ngulo por cuarto donde se choc�
                    ry[R].Plane[NReflections] = IntersectedPlane;                 // nro. del plano por cuarto donde se choc�
                    ry[R].Triangle[NReflections] = IntersectedTriangle;           // nro. del tri�ngulo por plano donde se choc�
                    ry[R].N = NReflections;                                       // JFLN: Number of reflections

                    // maximo 50 reflexiones
                    if (NReflections > 50) {
                        Stop = true;                  // no realizo mas reflexiones con este rayo
                        NReflections = 0;             // reseteo el contador de reflexiones para el siguiente rayo
                        IntersectedPlane = -1;        // reseteo el identificador de plano intersecado
                        IntersectedTriangle = -1;     // reseteo el identificador de triangulo intersecado
                        IntersectedTriangleId = -1;   // reseteo el identificador �nico de triangulo intersecado
                    }
                }
                else {// no hubo intersecci�n
                    NReflections++;
                    ry[R].lost = true;// JFLN: reflexi�n perdida
                    p3 = o + (v * maxd); // define un punto fuera de la sala para ilustrar el rayo perdido
                    ry[R].r[NReflections] = p3;// defino un punto fuera de la sala para ilustrar el rayo perdido
                    ry[R].N = NReflections;// punto fuera de la sala
                    LostRays++;                 // contador de rayos perdidos
                    Stop = true;                  // no realizo m�s reflexiones con el rayo perdido
                    NReflections = 0;             // reseteo el contador de reflexiones para el siguiente rayo
                    IntersectedPlane = -1;        // reseteo el identificador de plano intersecado
                    IntersectedTriangle = -1;     // reseteo el identificador de triangulo intersecado
                    IntersectedTriangleId = -1;   // reseteo el identificador �nico de triangulo intersecado
                }
            }
        }
        return ry;
    };
};
//---------------------------------------------------------------------------
inline double Module(Vector v) { //JFLN: Returns the vector's module
    double m;
    m = sqrt(v * v);
    return m;
};
//---------------------------------------------------------------------------
inline Vector VectorUnitario(Vector v1) { //JFLN: Returns the vector's unitary vector
    double m;
    Vector v2;
    m = Module(v1);
    if (m == 0)
        v2 = 0;
    else
        v2 = v1 / m;
    return v2;
};
inline Vector NormalPlano(plane p) {
    Vector n;
    n = VectorUnitario((p.p[1] - p.p[0]) / (p.p[2] - p.p[0]));
    return n;
};

#endif