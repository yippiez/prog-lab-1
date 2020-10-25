#include <graphics.h>
#include <math.h>
#include <stdio.h>
#include <time.h>

/*
#define EN 400
#sdefine BOY 400
#define BASLIK "test"
*/

// nokta verileri bu structa tutulur
typedef struct Nokta
{
    float x;
    float y;
} point;


typedef struct Daire
{
    nokta merkez;
    float r;
} daire;

// iki nokta arası uzunluğu hesaplar
float uzunluk(nokta a, nokta b)
{
    return sqrt(pow((a.x - b.x), 2) + pow((a.y - b.y), 2));
}

daire yeni_daire(nokta a, nokta b, nokta c)
{
    // http://www.ambrsoft.com/trigocalc/circle3d.htm

    float A = (a.x * (b.y - c.y)) - (a.y * (b.x - c.x)) + (b.x * c.y) - (c.x * b.y);
    float B = (pow(a.x, 2) + pow(a.y, 2)) * (c.y - b.y) + (pow(b.x, 2) + pow(b.y, 2)) * (a.y - c.y) + (pow(c.x, 2) + pow(c.y, 2)) * (b.y - a.y);
    float C = (pow(a.x, 2) + pow(a.y, 2)) * (b.x - c.x) + (pow(b.x, 2) + pow(b.y, 2)) * (c.x - a.x) + (pow(c.x, 2) + pow(c.y, 2)) * (a.x - b.x);
    //float D = (pow(a.x,2)+pow(a.y,2))*(c.x*b.y)-(b.x*c.y)+(pow(b.x,2)+pow(b.y,2))*((a.x*c.y)-(c.x*a.y))+(pow(c.x,2)+pow(c.y,2))*((b.x*a.y)-(a.x*b.y));
    float x = -B / (2 * A);
    float y = -C / (2 * A);
    float r = sqrt(pow(x - a.x, 2) + pow(y - a.y, 2));
    daire yeni_daire = {{x, y}, r};
    return yeni_daire;
}

int isall_inside(int n, nokta *liste, daire c)
{

    for (int i = 0; i < n; i++)
    {
        if (uzunluk(c.merkez, liste[i]) > c.r)
            return 0;
    }
    return 1;
}

// daire ciz
void draw_circle(daire c, nokta merkez)
{
    setcolor(15);
    circle((merkez.x + c.merkez.x), (merkez.y - c.merkez.y), c.r);
}

void draw_point(nokta p, nokta merkez)
{
    float x = merkez.x + p.x, y = merkez.y - p.y;
    setcolor(15);

    char kord[20];
    sprintf(kord, "(%0.f,%0.f)", x, y);
    settextstyle(SMALL_FONT, 0, 5);
    outtextxy(x + 10, y + 10, kord);

    setcolor(4);
    setfillstyle(rand() % 12, 4);
    fillellipse(x, y, 10, 10);
}

void hesapla(int n, nokta *liste, nokta merkez)
{
    daire big_circle = {{0, 0}, 0};

    if (n < 2)
        return;

    // dairelerein ikili ikili kontrolü
    daire tmp = {{0, 0}, 0};
    float max = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (j == i)
                continue;
            float u = uzunluk(liste[i], liste[j]);
            if (u > max)
            { // cap kontrolu
                max = u;
                tmp.merkez.x = (liste[i].x + liste[j].x) / 2;
                tmp.merkez.y = (liste[i].y + liste[j].y) / 2;
                tmp.r = max / 2;
                if (isall_inside(n, liste, tmp))
                    big_circle = tmp;
            }
        }
    }

    // dairelerin üclü üclü kontrolü
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            for (int k = 0; k < n; k++)
            {
                // eger aynı noktaları kapsıyorsa atla
                if (i == j || i == k || j == k)
                    continue;
                tmp = yeni_daire(liste[i], liste[j], liste[k]);

                if (isall_inside(n, liste, tmp) && (big_circle.r > tmp.r || big_circle.r == 0))
                    big_circle = tmp;
            }
        }
    }

    printf("Daire kordinatları: %f, %f\n", big_circle.merkez.x, big_circle.merkez.y);
    draw_circle(big_circle, merkez);
}

int main()
{
    srand(time(NULL));
    // pencere ayarlanır
    const char *title = "test";
    float en = 1000, boy = 1000;
    nokta merkez = {en / 2, boy / 2};

    initwindow(en, boy, title); // grafik pencere açıyoruz

    line(en / 2, 0, en / 2, en);   // (200,0)(200,400)
    line(0, boy / 2, en, boy / 2); // (0,200)(400,200)

    int n = 5 + (rand() % 15);
    nokta liste[n];
    for (int i = 0; i < n; i++)
    {
        liste[i].x = -400 + (rand() % 800);
        liste[i].y = -400 + (rand() % 800);
    }

    /*
    nokta ornek1 = {45, 10};
    nokta ornek2 = {-66, 55};
    nokta ornek3 = {100, -30};
    nokta liste[3] = {ornek1, ornek2, ornek3};
    int n = sizeof(liste) / sizeof(nokta);
    */

    printf("Liste boyutu:%d\n", n);
    hesapla(n, liste, merkez);
    // noktaları çiziyoruz
    for (int i = 0; i < n; i++)
        draw_point(liste[i], merkez);

    while (!kbhit()); //wait for user to press a key

    return 0;
}