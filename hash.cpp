#include <unordered_map>
#include <boost/functional/hash.hpp>
#include <iostream>

// Mangled from http://www.boost.org/doc/libs/1_55_0/libs/functional/hash/examples/point.cpp

class Point {
public:
    Point() : x(float(rand())/RAND_MAX), y(float(rand())/RAND_MAX) {}
    Point(int x, int y) : x(x), y(y) {}

    Point & operator=(const Point & other) {
        x = other.getX(); y = other.getY();
    }

    bool operator==(Point const& other) const {
        return x == other.getX() && y == other.getY();
    }

    struct LessThan {
        std::size_t operator()(Point const &p1, Point const &p2) {
            return p1.getX() < p2.getX();
        }
    };

    struct BadHash {
        std::size_t operator()(Point const& p) const {
            return 0;
        }
    };

    struct GoodHash {
        std::size_t operator()(Point const& p) const {
            std::size_t seed = 0;
            boost::hash_combine(seed, p.getX());
            boost::hash_combine(seed, p.getY());
            return seed;
        }
    };

    const float& getX() const {return x;}
    const float& getY() const {return y;}

private:
    float x, y;
};

// Output stream operator for the point
std::ostream& operator<< (std::ostream& os, const Point& pt) {
       os << "[" << pt.getX() << ","<<pt.getY()<<"] ";
       return os;
}

// Try and change GoodHash to BadHash and see what happens
typedef std::unordered_map<Point, float, Point::GoodHash> PointMap;


int main() {
  PointMap pmap;
  for (auto i=0; i<100; ++i)
      pmap[Point()] = float(rand())/RAND_MAX;
  for (auto it = pmap.begin(); it != pmap.end(); ++it) {
      std::cout << (*it).first << ", "<<(*it).second<< " is in bucket #"
                <<  " is in bucket #" << pmap.bucket((*it).first) << std::endl;
  }

  return 0;
}
