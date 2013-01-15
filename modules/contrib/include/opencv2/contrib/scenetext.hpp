#include <iostream>

using namespace std;

namespace cv
{
class RegionBase
{
protected:
    Rect bounds;
    int area;
    int perimeter;
    int euler;
    int imageh;
    int* crossings;

public:
    void CorrectEuler(int);
    Rect Bounds();
    int Area();
    int Perimeter();
    int Euler();
    int Crossings(int);
    int* AllCrossings();
    int CrossingsCount();
    int BoundsArea();
};

class Region : public RegionBase
{
protected:
    Point start;
public:
    Region();
    Region(Point, int);
    Region(Point, Rect, int, int, int, int*, int);
    ~Region();
    void Attach(Region*, int, int, int);
    Point Start();
};

class Region1D : public Region
{
private:
    unsigned start;
public:
    Region1D(unsigned, int, int);
    Region1D(unsigned, Rect, int, int, int, int*, int);
    void Attach(Region1D*, int, int, int);
    unsigned Start();
};

struct RegionComp
{
    bool operator() (Region _one, Region _other)
    {
        if (_one.Bounds().x < _other.Bounds().x) return true;
        if (_one.Bounds().x > _other.Bounds().x) return false;
        if (_one.Bounds().y < _other.Bounds().y) return true;
        if (_one.Bounds().y > _other.Bounds().y) return false;
        if (_one.Area() < _other.Area()) return true;
        if (_one.Area() > _other.Area()) return false;
        if (_one.Perimeter() < _other.Perimeter()) return true;
        if (_one.Perimeter() > _other.Perimeter()) return false;
        return false;
    }
};

class SceneTextLocalizer
{
private:
    Mat _originalImage;
    int threshValue;
    Point* uf_Find(Point*, Point**);
    unsigned* uf_Find1D(unsigned*, unsigned*);
public:
    SceneTextLocalizer();
    SceneTextLocalizer(Mat, int);
    set<Region, RegionComp> GroundTruth();
    set<Region, RegionComp> MatasLike();
};

}
