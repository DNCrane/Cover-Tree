#include "Cover_Tree_Point.h"
#include <vector>
#include <iostream>
#include <cmath>

using namespace std;

double CoverTreePoint::distance(const CoverTreePoint& p) const {
    static int timescalled = 0;
    //if(timescalled%1000000==0) cout << timescalled << "\n";
    timescalled++;
    const vector<double>& vec=p.getVec();
    double dist=0;
    int lim = vec.size();
    for(int i=0; i<lim;i++) {
        double d = vec[i]-_vec[i];
        dist+=d*d;
    }
    dist=sqrt(dist);
    return dist;
}

const vector<double>& CoverTreePoint::getVec() const {
    return _vec;
}

const char& CoverTreePoint::getChar() const {
    return _name;
}

void CoverTreePoint::print() const {
    vector<double>::const_iterator it;
    cout << "point " << _name << ": ";
    for(it=_vec.begin();it!=_vec.end();it++) {
        cout << *it << " ";
    }
    cout << "\n";
}

bool CoverTreePoint::operator==(const CoverTreePoint& p) const {
    return (_vec==p.getVec() && _name==p.getChar());
}
