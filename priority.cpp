/*
* File:        priority.cpp
* Description: Implements a priority ordering structure specially made for determining the
*              order of neighbours visited in PA2's filler::fill function.
*              Note that this does NOT serve the same purpose as the stack/queue
*              ordering structure which you have also been asked to implement.
*
*              Ignoring resize costs, any single insertion or removal operation
*              should cost at most O(n), where n is the number of PixelPoints
*              stored in the collection.
*
* Date:        2022-02-10 02:04
*
*/

#include "priority.h"
#include <assert.h>

using namespace cs221util;
using namespace std;

/*
*  Default constructor
*  Initializes refcolor to the default color according to the HSLAPixel implementation.
*/
PriorityNeighbours::PriorityNeighbours() {
  // complete your implementation below
  refcolor = HSLAPixel();
}

/*
*  Parameterized constructor
*  Initializes refcolor to the supplied value.
*/
PriorityNeighbours::PriorityNeighbours(HSLAPixel ref) {
  // complete your implementation below
  refcolor = ref;
}

/*
*  Inserts an item into the collection
*  PARAM: p - item to be inserted
*  POST:  the collection contains p, along with all previously existing items.
*/
void PriorityNeighbours::Insert(PixelPoint p) {
  // complete your implementation below
  points.push_back(p);
}

/*
*  Removes and returns an item from the collection satisfying the priority condition
*  PRE:    the collection is not empty (but it would be good to check anyway!).
*  POST:   the item satisfying the priority condition is removed from the collection.
*  RETURN: the item satisfying the priority condition
*
*  Priority condition:
*    The PixelPoint in the collection whose color is the minimum distance away
*    from the reference color is the priority item to be returned.
*
*    In case of multiple items with the same priority value (i.e. minimal distance
*    away from the reference color), the one with the minimal y-coordinate will be
*    selected.
*    In case of multiple items with the same priority value and the same y-coordinate,
*    the one with the minimal x-coordinate will be selected.
*
*    ***ATTENTION*** The dist() function in HSLAPixel.h will be very helpful!
*
*  Combined with Insert(), think about the time complexity of maintaining the
*  priority order and/or accessing the priority element in this specific application!
*/
PixelPoint PriorityNeighbours::Remove(){
  // complete your implementation below

  // distance of the ref HSPX
  double refdistance = refcolor.dist(refcolor);
  
  double potentialDistance = refcolor.dist(points[0].color); // points[0].color.dist(points[0].color);
  double gap = abs(refdistance - potentialDistance);
  int index=0;
  
  for(int i=1; i < points.size(); i++){
    double potentialDistance = refcolor.dist(points[i].color);
    double newGap = abs(refdistance - potentialDistance);
    if(gap > newGap){
      index = i;
    }
    //store the min abs potentialDistance - refdistance value  and then mark i and use another for loop to kill the element using erase
  }

  // creating a new vector to store these
  vector<PixelPoint> v2;
  for(int i=0; i < points.size(); i++){
    if(points[index].color.dist(points[index].color) == points[i].color.dist(points[i].color)){
      v2.push_back(points[index]);
    }
  }
  // now v2 has all the possible candidate and ready for y dimension comparison
  
  unsigned int tempy = v2[0].y;
  // unsigned int tempx = v2[0].x;
  
  int index2 =0;
  for(int i = 0; i < v2.size(); i++){
    if(v2[i].y < tempy){
      index2 = i;
      tempy = v2[i].y;
    }
  }

  vector<PixelPoint> v3;
  for(int i=0; i < v2.size(); i++){
    if( v2[i].y == tempy){
      v3.push_back(v2[i]);
    }
  }
  // now v3 has all the canadidate
 
  // unsigned int tempy = v3[0].y;
  unsigned int tempx = v3[0].x;
  
  int index3 = 0;
  for(int i=0; i < v2.size(); i++){
    if( v2[i].x < tempx ){
      index3 = i;
      tempx = v2[i].x;
    }
  }

  // remove the element from the collection
  for(int i=0; i < points.size(); i++){
    if(v3[index3] == points[i]){
      if(v3[index3].y == points[i].y && v3[index3].x == points[i].x){
        points.erase(points.begin()+i);
        break;
      }
    }
  }

  // return the element
  return v3[index3];
  
  // now v2 has all the potential candidates
  // index would be the smallest index
}

/*
*  Checks if the collection is empty
*  RETURN: true, if the collection is empty
*          false, otherwise
*/
bool PriorityNeighbours::IsEmpty() const {
  // complete your implementation below
  return points.empty();
}

/*
*  Returns the value of the reference color
*/
HSLAPixel PriorityNeighbours::GetReferenceColor() const {
  // complete your implementation below
  
}

/*
*  Sets the reference color attribute
*  POST: refcolor is set to the supplied value
*/
void PriorityNeighbours::SetReferenceColor(HSLAPixel ref) {
  // complete your implementation below
  refcolor = ref;
  
}