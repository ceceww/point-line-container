#include <iostream>

#include "Point.h"
#include "Line.h"
#include "PLContainer.h"

using std::ostream;

// Default constructor
PLContainer::PLContainer(){
  parray = nullptr;
  larray = nullptr;
  psize = 0;
  lsize = 0;
}

// Copy constructor
// Initialise a new PLContainer object from an existing one
// Deep copy
PLContainer::PLContainer(const PLContainer& other){
	// Copy psize and lsize
  psize = other.psize;
  lsize = other.lsize;
  // Allocate memory for new point and line arrays
  parray = new Point*[psize];
  larray = new Line*[lsize];
  // Copy contents
  for (int i=0; i<psize; i++){
    parray[i] = other.parray[i];
  }
	for (int i = 0; i < lsize; i++) {
		larray[i] = other.larray[i];
	}
}
  
// Move constructor
// Move resources from an existing PLContainer (other) to this one 
PLContainer::PLContainer(PLContainer&& other){
	// Copy psize and lsize
  psize = other.psize;
	lsize = other.lsize;
  // Allocate memory for new point and line arrays
  parray = new Point*[psize];
  larray = new Line*[lsize];
  // Copy contents
  for (int i=0; i<psize; i++){
		parray[i] = other.parray[i];
    // Get rid of original because resources are being moved
    other.parray[i] = nullptr;
   }
  for (int i=0; i<lsize; i++){
    larray[i] = other.larray[i];
		// Get rid of original because resources are being moved
    other.larray[i] = nullptr;
  } 
}

// Assignment operator (copy)
// Deep copy
PLContainer& PLContainer::operator=(const PLContainer& other){
	// Copy psize and lsize
	this->psize = other.psize;
	this->lsize = other.lsize;
	// Allocate memory for new point and line arrays
	this->parray = new Point*[this->psize];
	this->larray = new Line*[this->lsize];
	// Copy contents
	for (int i=0; i<this->psize; i++){
	this->parray[i] = other.parray[i];
	}
	for (int i=0; i<this->lsize; i++){
	this->larray[i] = other.larray[i];
	}
	return *this;
}

// Assignment operator (move)
// Deep copy
PLContainer& PLContainer::operator=(PLContainer&& other){
  // Copy psize and lsize
  this->psize = other.psize;
  this->lsize = other.lsize;
  // Allocate memory for new point and line arrays
  this->parray = new Point*[this->psize];
  this->larray = new Line*[this->lsize];
  // Copy contents
  for (int i=0; i<this->psize; i++){
		this->parray[i] = other.parray[i];
    // Get rid of original because resources are being moved
    other.parray[i] = nullptr;
   }
   for (int i=0; i<this->lsize; i++){
     this->larray[i] = other.larray[i];
     // Get rid of original because resources are being moved
     other.larray[i] = nullptr;
   }
  return *this;
}

// Destructor
PLContainer::~PLContainer(){
	delete[] parray;
  delete[] larray;
 }

// Test two containers for equality
bool PLContainer::operator==(const PLContainer& other) const{
  bool equal=false;
  // If both parray and larray for both PLContainer objects are empty
  if ((this->parray == nullptr) && (other.parray == nullptr) && (this->larray == nullptr) && (other.larray == nullptr)) {
		// They are equal
	  equal = true;
	  return equal;
  }
	// If psize and lsize are the same for both PLContainer objects
  if ((this->psize == other.psize) && (this->lsize == other.lsize)){
		// Assume they are equal for now - keep checking
	  equal = true;
		// (1) Check equality of parrays
		// For each element in this->parray
    for (int i=0; i<psize; i++){
			// Store whether the same value has been found in other array or not
      bool found = false;
      // See if it's in the other array
      for (int j=0; j<psize; j++) {
			  // If same point object has been found
        if (*this->parray[i] == *other.parray[j]){
          // This point is in both arrays, so set found=true
          found = true;
					// Move on to next element in this->parray
          break;
        }
        // If end is reached
        if ((j==(psize-1)) && (found == false)){
          // This point is missing from the other's parray so set equal=false
          equal = false;
          return equal;
        }
      }
    }
		// (2) Check equality of larrays
		// For each element in this->larray
		for (int i = 0; i<lsize; i++) {
			// Store whether the same value has been found in other array or not
			bool found = false;
			// See if it's in the other array
			for (int j = 0; j<lsize; j++) {
				if (*this->larray[i] == *other.larray[j]) {
					// This line is in both arrays, so set found=true
					found = true;
					// Move on to next element in this->larray
					break;
				}
				// If the end is reached
				if ((j == (lsize - 1)) && (found == false)) {
					// This line is missing from the other's larray so set equal=false
					equal = false;
					return equal;
				}
			}
		}
  }
  // Returns false if psize and lsize are not the same for both PLContainer objects.
  return equal; 
}

bool PLContainer::addPoint(double x, double y, Point*& point){
	// Whether the point has been added or not
  bool added = false;
  // If point is not already in container
  if (this->getPoint(x, y, point) == false) {
	  // New capacity of array is current psize + 1 to fit one additional pp object
	  unsigned int new_capacity = this->psize + 1;
		// psize of this object is also updated to new_capacity in resizePointsArray
	  this->resizePointsArray_(new_capacity);
		// Create a new point object to store in parray
		point = new Point(x, y);
		// Store point in parray in the new space allocated
	  this->parray[new_capacity - 1] = point;
		// Update point to point to this point object
		point = this->parray[new_capacity - 1];
		// Just added a point, so set to added=true
	  added = true;
  }
  return added; 
}

bool PLContainer::getPoint(double x, double y, Point*& point){
	// If we successfully can get a point, exists will be set to true
  bool exists=false;
  point = new Point(x, y);
	// Iterate over this->parray
  for (int i = 0; i < psize; i++) {
		// If current point in parray is same as point we want to get
	  if (*this->parray[i] == *point) {
			// Point exists, so set exists=true
		  exists = true;
		  // Update point to point to this point object
		  point = this->parray[i];
	  }
  }
  return exists; 
}

bool PLContainer::deletePoint(double x, double y){
  bool deleted=false;
	// Create a point from x and y
  Point* pp = new Point(x, y);
  // Create pointer to psize so we can modify this->psize when point gets deleted
  uint* psize_ptr = &this->psize;
  // Iterate over this->parray
  for (int i = 0; i < *psize_ptr; i++) {
		// If we find a matching point
	  if (*this->parray[i] == *pp) {
		  // Then found a point to delete
		  for (int j = i; j < *psize_ptr; j++) {
			  // If it's the last element in array
			  if (j == (*psize_ptr - 1)) {
				  // .. make it point to nowt
				  parray[j] = nullptr;
					// Finished iterating
				  deleted = true;
				  break;
			  }
			  // Overwrite by shifting left
			  parray[j] = parray[j + 1];
		  }
		  // Every time we delete a point, psize is decremented by 1
		  *psize_ptr = *psize_ptr - 1;
	  }
  }
	// Now delete lines containing (x,y)
  // Store raw points of the line to delete
  double x1, x2, y1, y2;
  // Look in this->larray for lines that contain this point
  // Have to work backwards because lsize is decreased as we delete lines
  for (int i = lsize-1; i >=0; i--) {
		// If the first point is (x,y)
	  if ((*this->larray[i]->getPoint1() == *pp)) {
			// Store the raw points of this line
		  x1 = x;
		  x2 = this->larray[i]->getPoint2()->getX();
		  y1 = y;
		  y2 = this->larray[i]->getPoint2()->getY();
	  }
		// If the second point is (x,y)
	  else if ((*this->larray[i]->getPoint2() == *pp)) {
			// Store the raw points of this line
		  x1 = this->larray[i]->getPoint1()->getX();
		  x2 = x;
		  y1 = this->larray[i]->getPoint1()->getY();
		  y2 = y;
	  }
	  // Delete this line because it contains (x,y) as either first or second point
	  this->deleteLine(x1, y1, x2, y2);
  }
  return deleted; 
}

unsigned int PLContainer::numberOfPoints() const{
  return this->psize;
}

bool PLContainer::addLine(double x1, double y1, double x2, double y2, Line*& line){
	Point *pp1 = nullptr;
	Point *pp2 = nullptr;
	bool added = false;
	// If the points are in parray
	if (this->getPoint(x1, y1, pp1) && this->getPoint(x2, y2, pp2)) {
		// And if line is not already in this->larray
		if (this->getLine(x1, y1, x2, y2, line) == false) {
			// Do stuff to add the line
			// new_capacity is lsize+1 to accommodate one additional line
			unsigned int new_capacity = this->lsize + 1;
			// lsize is updated to new_capacity in resizeLinesArray
			this->resizeLinesArray_(new_capacity);
			// Create a new line object to store in larray
			Line* lp = new Line(pp1,pp2);
			// Points to the newly created line object
			line = lp;
			// Finished using lp, just needed it to create new line obj
			lp = nullptr;
			// Store new line object pointer in newly allocated memory of larray
			this->larray[new_capacity - 1] = line;
			// Just added a line so set added = true
			added = true;
		}
	}
  return added; 
}

bool PLContainer::getLine(double x1, double y1, double x2, double y2, Line*& line){
	bool exists = false;
	// Create a point from x1 and y1
	Point* pp1 = new Point(x1, y1);
	// Create a point from x2 and y2
	Point* pp2 = new Point(x2, y2);
	// Create a line from pp1 and pp2 to test equality 
	Line* lp = new Line(pp1,pp2);
	for (int i = 0; i < lsize; i++) {
		// If this line and *lp are the same
		if (*this->larray[i] == *lp) {
			// The line exists in array
			exists = true;
			// Point the line pointer to found line
			line = this->larray[i];
		}
	}
	return exists;
}

bool PLContainer::deleteLine(double x1, double y1, double x2, double y2){
	bool deleted = false;
	// Create a point from x1 and y1
	Point* pp1 = new Point(x1, y1);
	// Create a point from x2 and y2
	Point* pp2 = new Point(x2, y2);
	// Create a line from pp1 and pp2
	Line* lp = new Line(pp1, pp2);
	// Create a pointer to update lsize
	uint* lsize_ptr = &this->lsize;
	// Iterate over this->larray
	for (int i = 0; i < *lsize_ptr; i++) {
		// If we find a matching line
		if (*this->larray[i] == *lp) {
			// Then found a line to delete
			for (int j = i; j < *lsize_ptr; j++) {
				// If it's the last element in larray
				if (j == (*lsize_ptr - 1)) {
					// .. make it point to nowt
					larray[j] = nullptr;
					deleted = true;
					break;
				}
				// Overwrite current line in array with the next element (shifting left)
				larray[j] = larray[j + 1];
			}
			// Every time we delete a line, lsize is decremented by 1
			*lsize_ptr = *lsize_ptr-1;
		}
	}
  return deleted; 
}

unsigned int PLContainer::numberOfLines() const{
  return lsize;
}

// Returns an array of pointers to lines that are incident to (x,y)
Line** PLContainer::incidentLines(double x, double y, unsigned int& number_lines, unsigned int& capacity){
	// Initialise an empty array to store the incident lines
  Line* *iarray=nullptr;
  // Create point to test incidence with
  Point* p = new Point(x, y);
  // Test incidence for each line in this->larray
  for (int i = 0; i < lsize; i++) {
	  if (this->larray[i]->isIncident(*p)) {
			// resize updates the capacity to capacity + 1 each time
		  resize(iarray, number_lines, capacity, capacity + 1);
			// Copying elements
			// If there's just one element
		  if (i == 0) {
			  iarray[0] = this->larray[0];
		  }
		  else {
				// Copy the identified incident line at larray[i] into the next free space of iarray
			  iarray[number_lines] = this->larray[i];
		  }
			// Just added a line to iarray, so increment by 1
		  number_lines++;
	  }
  }
  return iarray;
}

void PLContainer::resize(Line**& arr, uint length, uint& capacity, uint new_capacity) {
	if (new_capacity > capacity) {
		// Allocate memory for an array of size new_capacity
		Line* * temp = new Line*[new_capacity];
		// Copy the contents of old array into the new one
		for (int i = 0; i<length; i++) {
			temp[i] = arr[i];
		}
		// Free memory
		delete[] arr;
		// Point arr to new memory location where a larger amount of memory was allocated
		arr = temp;
		// Finished with temp so make it point to nothing
		temp = nullptr;
		// Update the capacity of arr to new_capacity
		capacity = new_capacity;
	}
}

// Print the points and lines in this container
// in the form (x1,y1) (x2,y2) ((x1,y1),(x2,y2))
void PLContainer::print(std::ostream& stream) const{
	for (int i = 0; i < this->psize; i++) {
		stream << *this->parray[i] << " ";
	}
	for (int i = 0; i < this->lsize; i++) {
		stream << *this->larray[i] << " ";
	}
}

// Print the points and lines in plc
// in the form (x1,y1) (x2,y2) ((x1,y1),(x2,y2))  
std::ostream& operator<<(std::ostream& stream,const PLContainer& plc){
	for (int i = 0; i < plc.psize; i++) {
		stream << *plc.parray[i] << " ";
  }
	for (int i = 0; i < plc.lsize; i++) {
		stream << *plc.larray[i] << " ";
	}
  return stream; 
}

void PLContainer::resizePointsArray_(unsigned int new_capacity){
	// Difference between original and new capacity
	int diff = new_capacity - (this->psize);
	// If new_capacity == psize
  if (diff == 0) {
		// Do nothing
		return;
	}
  // Allocate memory for a point array with size new_capacity
  Point** temp = new Point*[new_capacity];
	// If new_capacity > psize then we are making a bigger array
  if (diff > 0) {
	  // Copy the contents of old array into the new one
	  for (int i = 0; i < this->psize; i++) {
		  temp[i] = this->parray[i];
	  }
  }
	// If new_capacity < psize then we are making a smaller array
  else {
	  // Copy the contents of old array into the new one
	  for (int i = 0; i < new_capacity; i++) {
		  temp[i] = this->parray[i];
	  }
	}
	// Point parray to new memory location where a different amount of memory was allocated
	this->parray = temp;
	// Finished with temp so make it point to nothing
	temp = nullptr;
	// Create pointer to update psize for this container
	uint* psize_ptr = &this->psize;
	*psize_ptr = this->psize + diff;
}


void PLContainer::resizeLinesArray_(unsigned int new_capacity) {
	// Difference between original and new capacity
	int diff = new_capacity - (this->lsize);
	// If new_capacity == lsize
	if (diff == 0) {
		// Do nothing
		return;
	}
	// Allocate memory for a line array with size new_capacity
	Line** temp = new Line*[new_capacity];
	// If new_capacity > lsize then we are making a bigger array
	if (diff > 0) {
		// Copy the contents of smaller old array into the bigger new one
		for (int i = 0; i < this->lsize; i++) {
			temp[i] = this->larray[i];
		}
	}
	// If new_capacity < lsize then we are making a smaller array
	else {
		// Copy the contents of bigger old array into the smaller new one
		for (int i = 0; i < new_capacity; i++) {
			temp[i] = this->larray[i];
		}
	}
	// Point to new memory location where a different amount of memory was allocated
	this->larray = temp;
	// Finished with temp so make it point to nothing
	temp = nullptr;
	// Create pointer to update lsize for this container
	uint* lsize_ptr = &this->lsize;
	*lsize_ptr = this->lsize + diff;
}
