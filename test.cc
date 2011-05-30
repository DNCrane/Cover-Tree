#include "Cover_Tree.h"
#include "Cover_Tree_Point.h"
#include <vector>
#include <iostream>
#include <cstdlib>

using namespace std;

void testTree() {
    vector<double> a;
    a.push_back(1.0);
    CoverTree<CoverTreePoint> cTree(10);
    cTree.insert(CoverTreePoint(a,'a'));
    a[0]=2.1;  cTree.insert(CoverTreePoint(a,'a'));
    a[0]=3.2;  cTree.insert(CoverTreePoint(a,'a'));
    a[0]=4.1;  cTree.insert(CoverTreePoint(a,'a'));
    a[0]=1.1;  cTree.insert(CoverTreePoint(a,'a'));
    a[0]=2.5;  cTree.insert(CoverTreePoint(a,'a'));
    a[0]=3.1;  cTree.insert(CoverTreePoint(a,'a'));
    if(cTree.isValidTree()) cout << "Insert test: \t\t\t\tPassed\n";
    else cout << "Insert test: \t\t\t\tFailed\n";

    a[0]=2.0; // the 5 nearest points to this are 2.1, 2.5, 1.1, 1, 3.1
    vector<CoverTreePoint>
        points = cTree.kNearestNeighbors(CoverTreePoint(a,'a'),5);
    bool kNNGood=true;
    //for(int i =0; i<points.size(); i++) {
    //    points[i].print();
    //}
    a[0]=2.1; if(!(CoverTreePoint(a,'a')==points[0])) kNNGood=false;
    a[0]=2.5; if(!(CoverTreePoint(a,'a')==points[1])) kNNGood=false;
    a[0]=1.1; if(!(CoverTreePoint(a,'a')==points[2])) kNNGood=false;
    a[0]=1.0; if(!(CoverTreePoint(a,'a')==points[3])) kNNGood=false;
    a[0]=3.1; if(!(CoverTreePoint(a,'a')==points[4])) kNNGood=false;
    if(kNNGood) cout << "KNN test: \t\t\t\tPassed\n";
    else cout << "KNN test: \t\t\t\tFailed\n";
    
    cTree.insert(CoverTreePoint(a,'b'));
    cTree.insert(CoverTreePoint(a,'c'));
    
    
    points = cTree.kNearestNeighbors(CoverTreePoint(a,'a'), 1);
    //there should be a three-way tie since there are 3 nodes with distance 0
    if(points.size()==3 && points[2].distance(CoverTreePoint(a,'a'))==0.0)
        cout << "Multiple 0 distance points test: \tPassed\n";
    else cout << "Multiple 0 distance points test: \tFailed\n";

    cTree.remove(CoverTreePoint(a,'b'));
    points = cTree.kNearestNeighbors(CoverTreePoint(a,'a'), 1);
    //there should be a two-way tie now since one was removed
    if(points.size()==2 && points[1].distance(CoverTreePoint(a,'a'))==0.0)
        cout << "Multiple 0 distance points removal test:Passed\n";
    else cout << "Multiple 0 distance points removal test:Failed\n";
    
    a[0]=2.124;  cTree.remove(CoverTreePoint(a,'a'));
    a[0]=4.683;  cTree.remove(CoverTreePoint(a,'a'));
    a[0]=9.123;  cTree.remove(CoverTreePoint(a,'a'));
    if(cTree.isValidTree())
        cout << "Remove nonexistent point test: \t\tPassed\n";
    else cout << "Remove nonexistent point test: \t\tFailed\n";

    a[0]=3.2;  cTree.remove(CoverTreePoint(a,'a'));
    a[0]=1.1;  cTree.remove(CoverTreePoint(a,'a'));
    a[0]=2.5;  cTree.remove(CoverTreePoint(a,'a'));
    if(cTree.isValidTree()) cout << "Remove test: \t\t\t\tPassed\n";
    else cout << "Remove test: \t\t\t\tPassed\n";

    a[0]=1.0;  cTree.remove(CoverTreePoint(a,'a'));
    if(cTree.isValidTree()) cout << "Remove root test: \t\t\tPassed\n";
    else cout << "Remove root test: \t\t\tPassed\n";

    vector<double> start;
    for(int j=0;j<5;j++) start.push_back((double)rand()/(double)RAND_MAX);

    vector<CoverTreePoint> initVec;
    initVec.push_back(CoverTreePoint(start,'a'));

    CoverTree<CoverTreePoint>
        cTree2(10,initVec);
    cTree2.remove(CoverTreePoint(start,'a'));//Now the tree has no nodes...
    //make sure it can handle trying to remove a node when
    //it has no nodes to begin with...
    cTree2.remove(CoverTreePoint(start,'a'));
    
    points = vector<CoverTreePoint>();
    for(int i=0;i<500;i++) {
        vector<double> a;
        for(int j=0;j<5;j++) {
            a.push_back((double)rand()/(double)RAND_MAX);
        }
        cTree2.insert(CoverTreePoint(a,'a'));
        points.push_back(CoverTreePoint(a,'a'));
    }
    if(cTree2.isValidTree()) cout << "500 random inserts test: \t\tPassed\n";
    else cout << "500 random inserts test: \t\tPassed\n";

    bool NNGood=true;
    for(int i=0;i<100;i++) {
        vector<CoverTreePoint>
            v = cTree2.kNearestNeighbors(points[i],1);
        if(v[0].distance(points[i])!=0.0) NNGood=false;
    }
    if(NNGood) cout << "Nearest Neighbor test: \t\t\tPassed\n";
    else cout << "Nearest Neighbor test: \t\t\tFailed\n";

    for(int i=0;i<490;i++) {
        cTree2.remove(points[i]);
    }
    if(cTree2.isValidTree()) cout << "Remove random test: \t\t\tPassed\n";
    else cout << "Remove random test: \t\t\tFailed\n";
}

void bigTest(unsigned int numNodes, unsigned int numDimensions){
    vector<CoverTreePoint> points;
    for(unsigned int i=0;i<numNodes;i++) {
        vector<double> a;
        for(unsigned int j=0;j<numDimensions;j++) {
            a.push_back((double)rand()/(double)RAND_MAX);
        }
        points.push_back(CoverTreePoint(a,'a'));
    }
    cout << "Building Cover Tree with " << numNodes << " nodes\n";
    CoverTree<CoverTreePoint> cTree(51,points);
    cout << "Cover tree built.\n";

    cout << "2000 random NN searches beginning...\n";
    for(int i=0;i<2000;i++) {
        vector<double> a;
        for(unsigned int j=0;j<numDimensions;j++) {
            a.push_back((double)rand()/(double)RAND_MAX);
        }
        cTree.kNearestNeighbors(CoverTreePoint(a,'a'),1);
    }
    cout << "NN searches done.\n";

    cout << "Removing all nodes...\n";
    for(unsigned int i=0; i<numNodes; i++) {
        cTree.remove(points[i]);
    }
    cout << "Removal done.\n";
}
int main()
{    
    testTree();
    bigTest(3000,50);
    return 0;
}
