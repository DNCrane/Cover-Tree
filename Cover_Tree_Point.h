#ifndef _COVER_TREE_POINT_H
#define _COVER_TREE_POINT_H

#include <vector>

/**
 * A simple point class containing a vector of doubles and a single char name.
 */
class CoverTreePoint
{
private:
    std::vector<double> _vec;
    char _name;
public:
    CoverTreePoint(std::vector<double> v, char name) : _vec(v), _name(name) {}
    double distance(const CoverTreePoint& p) const;
    const std::vector<double>& getVec() const;
    const char& getChar() const;
    void print() const;
    bool operator==(const CoverTreePoint&) const;
};

#endif // _COVER_TREE_POINT_H

