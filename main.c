#include <graphics.h>
#include <math.h>
#include <stdio.h>

// circle(x, y, r) r -> yarıçap
// line(x1, y1, x2, y2) x1,y1 ilk noktanın kordinatı x2,y2 inkincinin kordinatı

// nokta verileri bu structa tutulur
typedef struct Daire{
    float x;
    float y;
    float r;
} daire;

typedef struct Nokta{
    float x;
    float y;
} nokta;

// iki nokta arası uzunluğu hesaplar
float uzunluk(nokta a, nokta b){
    return sqrt(pow((a.x-b.x),2)+pow((a.y-b.y),2));
}

daire yeni_daire(nokta a, nokta b, nokta c){
    // http://www.ambrsoft.com/trigocalc/circle3d.htm

    float A = (a.x*(b.y-c.y))-(a.y*(b.x-c.x))+(b.x*c.y)-(c.x*b.y);
    float B = (pow(a.x,2)+pow(a.y,2))*(c.y-b.y)+(pow(b.x,2)+pow(b.y,2))*(a.y-c.y)+(pow(c.x,2)+pow(c.y,2))*(b.y-a.y);
    float C = (pow(a.x,2)+pow(a.y,2))*(b.x-c.x)+(pow(b.x,2)+pow(b.y,2))*(c.x-a.x)+(pow(c.x,2)+pow(c.y,2))*(a.x-b.x);
    //float D = (pow(a.x,2)+pow(a.y,2))*(c.x*b.y)-(b.x*c.y)+(pow(b.x,2)+pow(b.y,2))*((a.x*c.y)-(c.x*a.y))+(pow(c.x,2)+pow(c.y,2))*((b.x*a.y)-(a.x*b.y));
    float x = -B/(2*A);
    float y = -C/(2*A);
    float r = sqrt(pow(x - a.x, 2) + pow(y - a.y, 2));
    daire yeni_daire = {x, y, r};
    return yeni_daire;
}

int isall_inside(int n, nokta *liste, daire c){
    return 0;
}


// daire ciz
void draw_circle(daire c, nokta merkez){
    circle((merkez.x + c.x), (merkez.y - c.y), c.r);
}

void draw_point(nokta p, nokta merkez){
    circle((merkez.x + p.x), (merkez.y - p.y), 3);
}

void hesapla(int n, nokta *liste ,nokta merkez){
    daire daire_merkez = {0, 0, 0};

    if(n<2)
        return;
    
    // dairelerein ikili ikili kontrolü    
    daire tmp;
    float max = 0;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(j==i)
                continue;
            float u = uzunluk(liste[i], liste[j]);
            if(u>max){
                max = u;
                tmp.x = (liste[i].x + liste[j].x)/2;
                tmp.y = (liste[i].y + liste[j].y)/2;
                tmp.r = max/2;
                // if(içindeyse)
                //   daire_merkez = tmp;
            }
        }
    }

    daire_merkez = tmp;
    
    // dairelerin üclü üclü kontrolü
    for(int i=0; i<n; i++){
        for(int j=0;j<n;j++){
            for(int k=0;k<n;k++){
                // eger aynı noktaları kapsıyorsa atla
                if(i==j || i==k || j==k)
                    continue;
                // buraya liste[i] liste[j] liste[k]
            }
        }
    }
    

    printf("Daire kordinatları: %f, %f\n", daire_merkez.x, daire_merkez.y);
    draw_circle(daire_merkez, merkez);    
}



int main() {
    // pencere ayarlanır
    float en = 400,boy=400;
    nokta merkez = {en/2, boy/2};
    initwindow(en, boy, "grafik"); // grafik pencere açıyoruz
    
    line(en/2,0, en/2,en); // (200,0)(200,400)
    line(0,boy/2, en,boy/2); // (0,200)(400,200)

    nokta ornek1 = {10, 10};
    nokta ornek2 = {21, -12};
    nokta ornek3 = {-20, 25}; 
    
    //draw_circle(yeni_daire(ornek1, ornek2, ornek3), merkez);

    nokta liste[3] = {ornek1, ornek2, ornek3};

    int n = sizeof(liste)/sizeof(nokta);
    printf("Liste boyutu:%d\n", n);

    // noktaları çiziyoruz
    for(int i=0;i<n;i++)
        draw_point(liste[i], merkez);

    hesapla(n, liste, merkez);


    while(!kbhit()); //wait for user to press a key 
    return 0;
}