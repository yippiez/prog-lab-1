#include <graphics.h>
#include <math.h>
#include <stdio.h>

// circle(x, y, r) r -> yarıçap
// line(x1, y1, x2, y2) x1,y1 ilk noktanın kordinatı x2,y2 inkincinin kordinatı

// nokta verileri bu structa tutulur
typedef struct Nokta{
    float x;
    float y;
} nokta;

// iki nokta arası uzunluğu hesaplar
double uzunluk(nokta a, nokta b){
    return sqrt(pow((a.x-b.x),2)+pow((a.y-b.y),2));
}

// nokta ciz
void draw_point(nokta p, nokta merkez){
    circle((merkez.x + p.x), (merkez.y - p.y), 3);
}

void hesapla(int n, nokta *liste, nokta merkez){
    double max=0;
    nokta tmp;
    nokta tmp2;

    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){

            if(i==j)
                continue;

            double u = uzunluk(liste[i], liste[j]);
            if(u>max){
                max = u;
                tmp = liste[i];
                tmp2 = liste[j];
            }
        }
    }
    printf("%lf maks deger.\n", max);
    nokta daireMerkezi = {(tmp.x+tmp2.x)/2, (tmp.y+tmp2.y)/2};
    printf("Daire kordinatları: %f, %f\n", daireMerkezi.x, daireMerkezi.y);
    circle(merkez.x + daireMerkezi.x, merkez.y - daireMerkezi.y, max/2); 

    
}



int main() {
    // pencere ayarlanır
    float en = 400,boy=400;
    nokta merkez = {en/2, boy/2};
    initwindow(en, boy, "grafik"); // grafik pencere açıyoruz
    
    line(en/2,0, en/2,en); // (200,0)(200,400)
    line(0,boy/2, en,boy/2); // (0,200)(400,200)

    nokta ornek1 = {120, 134};
    nokta ornek2 = {99, 78};
    nokta ornek3 = {58, 126};
    

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