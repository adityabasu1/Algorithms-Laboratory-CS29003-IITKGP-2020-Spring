#include<iostream>
#include<cmath>

using namespace std;

//structure to store a rectangle
struct rec 
{
    double x; // abscissa of bottom left coordinate
    double y; // ordinate of bottom right coordinate // so (x,y) is the bottom left point
    double lx; // length along x axis
    double ly; // length along y axis

    /* in essence:
    The coordinates of rectangle are:
    
    bottom left: (x,y)
    bottom right: (x+lx,ly)
    top right: (x+lx, y+ly)
    top left: (x,y+ly)
    */

   rec() // default constructor
   {
       x = 0;
       y = 0;
       lx = 0;
       ly = 0;
   }

   void set()
   {
       cin>>x;
       cin>>y;
       cin>>lx;
       cin>>ly;

   }
};

struct point
{
    double x;
    double y;
    //(x,y) is a point

    point()
    {
        x = 0;
        y = 0;
    }
};

struct bdrec    // rectangle as an array of 4 points
{
    point bdr[4];

    void conv(rec A) // conversion function
    {
        bdr[0].x = A.x; 
        bdr[0].y = A.y;
        bdr[1].x = A.x;
        bdr[1].y = A.y + A.ly;
        bdr[2].x = A.x + A.lx;
        bdr[2].y = A.y + A.ly;
        bdr[3].x = A.x + A.lx;
        bdr[3].y = A.y;
    }
};


double find_max_abscissa_of_bottom_left(rec *A, int n);
double find_min_abscissa_of_bottom_right(rec *A, int n);
double pline(rec *A, int n);
point * findb(rec *B, bdrec *A, int n, point *p, int sp, double pl);
void merge(rec *B, point *p1, point *p2, point *p, int sp1, int sp2, double pl);
void print (point *p, int sp);

int main()
{
    int n;
    cout<<"Write n: ";
    cin>>n;

    rec *rec_combo = new rec[n];

    int i;
    for(i=0; i<n; i++)
    {
        rec_combo[i].set(); // to take input
    } 
    cout<<"piercing line is:" <<pline(rec_combo, n)<<endl;



    bdrec *rec_combo2 = new bdrec[n];
    for(i=0; i<n; i++)
    {
        rec_combo2[i].conv(rec_combo[i]);
    }

    point p[10000];
    int sp = 0; // length of the point list
    double pl;
    findb(rec_combo,rec_combo2,n,p,sp,pl);
    print(p,sp);
    return 0;
}

double find_max_abscissa_of_bottom_left(rec *A, int n) // finds maximum x coordinate of bottom left point of all rectangles
{
    double maxi = A[0].x;

    int i;
    for(i=1; i<n; i++)
    {
        if(A[i].x > maxi)
        {
            maxi = A[i].x;
        }
    }
    return maxi;
}

double find_min_abscissa_of_bottom_right(rec *A, int n) // finds minimum x coordinate of bottom right point of all rectangles
{
    double mini = A[0].x + A[0].lx;

    int i;
    for(i=1; i<n; i++)
    {
        if( (A[i].x + A[i].lx) < mini)
        {
            mini = (A[i].x + A[i].lx);
        }
    }
    return mini;
}

/* piercing line is a line parallel to y axis thus of the form y = a
   to find the vertical piercing line we find the maximum abscissa of bottom left points
   and minimum abscissa of bottom right points.
   and then compute the average of these two to get the verticala piercing line
*/

double pline(rec *A, int n)
{
    double maxi = find_max_abscissa_of_bottom_left(A,n);
    double mini = find_min_abscissa_of_bottom_right(A,n);
    double ppoint = (maxi + mini)/2;
    return ppoint; 
}


int sp1 = 0;
int sp2 = 0;

point * findb(rec *B, bdrec *A, int n, point *p, int sp, double pl) // find boundary
{
    pl = pline(B,n);
    if(n == 1)
    {
        
        int i;
        for(i=0; i<4; i++)
        {
            p[i] = A[0].bdr[i];
        }
        sp += 4;

        return p;
    }

    bdrec *B1 = new bdrec[n/2];
    bdrec *C = new bdrec[n-n/2];

    for(int i=0; i<n/2; i++)
	{
		B1[i] = A[i];
		C[i]= A[i+ n/2];
	}
	C[n-n/2-1] = A[n-1]; // problems where n is odd

    point * p1 = findb(B,B1,n/2,p,sp1,pl);
    point * p2 = findb(B,C,n-n/2,p,sp2,pl);

    merge(B,p1,p2,p,sp1,sp2,pl);
}

void merge(rec *B, point *p1, point *p2, point *p, int sp1, int sp2, double pl)
{

}

void print(point *p, int sp)
{
    for(int i=0; i<sp; i++)
    {
        cout<<"{"<<p[i].x<<","<<p[i].y<<" }"<<",";
    }
    cout<<endl;
}