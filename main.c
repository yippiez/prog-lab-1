#include <graphics.h>
#include <math.h>
#include <stdio.h>

// struct for holding the point value
typedef struct Point{
    float x;
    float y;
} point;


// calculate the distancce between two points
double distance(point a, point b){
    return sqrt(pow((a.x-b.x),2)+pow((a.y-b.y),2));
}


// draw a point with fixed radius (3)
void draw_point(point p, point center_point){
    circle((center_point.x + p.x), (center_point.y - p.y), 3);
}


// this calculates and prints a circle big enough to include all points
void calculate(int n, point *liste, point center_point){
    double max=0; // max distance between any point
    point tmp;
    point tmp2;

    // iterate over every 2 combination of points and check their distances
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){

            if(i==j)
                continue;

            double u = distance(liste[i], liste[j]);
            if(u>max){
                max = u;
                tmp = liste[i];
                tmp2 = liste[j];
            }
        }
    }
    printf("%lf maks deger.\n", max);

    point new_circle = {(tmp.x+tmp2.x)/2, (tmp.y+tmp2.y)/2};
    printf("Center point: x=%f, y=%f\n", new_circle.x, new_circle.y);
    circle(center_point.x + new_circle.x, center_point.y - new_circle.y, max/2); 

}


int main() {
    // pencere ayarlanır
    float width = 400,height=400;
    point center_point = {width/2, height/2};
    initwindow(width, height, "grafik"); // grafik pencere açıyoruz
    
    // draws + shaped lines in the middle of the window useful for reference
    line(width/2,0, width/2,width); 
    line(0,height/2, width,height/2);

    // sample points
    point ornek1 = {120, 134};
    point ornek2 = {99, 78};
    point ornek3 = {58, 126};
    
    // putting all the points in a list so it's easier to manipulate
    point liste[3] = {ornek1, ornek2, ornek3};

    // calculates the length of the list
    int n = sizeof(liste)/sizeof(point);
    printf("Liste boyutu:%d\n", n);

    // draws all the points to the screen
    for(int i=0;i<n;i++)
        draw_point(liste[i], center_point);
    

    calculate(n, liste, center_point);


    while(!kbhit()); //wait for user to press a key 
    return 0;
}