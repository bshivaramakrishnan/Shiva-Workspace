
#include<iostream>
#include<vector>
using namespace std;

class Vector
{
private:
    vector<int> vobj;
public:
    static Vector* GetVectorObject();
    void InitVectorElements(int arr[5], int length);
    void GetVectorSize();
    int GetVectorElements(int position);
    void ShowVectorElementsByRegularLoop();
    void ShowVectorElementsByIterator();
    int isVectorEmpty();
    int GetVectorFirstElement();
    int GetVectorLastElement();
    int InsertElement(int position, int element);
    void ClearVectorElements();
    //void DeleteSpecificElement();
    void DestructVectorObject();


};

void Vector::GetVectorSize() {
    cout << "vector Size :: " << this->vobj.size() << endl;
}

inline int Vector::GetVectorElements(int position) {
    return this->vobj.at(position);
}

inline void Vector::ShowVectorElementsByRegularLoop() {
    cout << endl << "vector Elements By Regular loop :: ";
    for (auto element : this->vobj) {
        cout << "|" << element;
    }
    cout << "|";
}

inline void Vector::ShowVectorElementsByIterator() {
    cout << endl << "vector Elements By Iterator :: ";
    for (vector<int> ::iterator it = this->vobj.begin(); it < this->vobj.end(); it++) {
        cout << "|" << *it;
    }
    cout << "|";
}

inline int Vector::isVectorEmpty() {
    if (this->vobj.empty()) {
        return 1;
    }
    return 0;
}

inline int Vector::GetVectorFirstElement() {
    if (!(this->isVectorEmpty())) {
        return this->vobj.front();
    }
    return 0;
}

inline int Vector::GetVectorLastElement() {
    if (!this->isVectorEmpty()) {
        return this->vobj.at(this->vobj.size() - 1);
    }
    return -1;
}

inline int Vector::InsertElement(int position, int element) {
    //vector<int> :: iterator it = this->vobj.begin();
    this->vobj.insert(this->vobj.begin() + position, element);
}

Vector* Vector::GetVectorObject() {
    Vector* vobj = new Vector();
    return vobj;
}

inline void Vector::InitVectorElements(int arr[5], int length) {
    for (int i = 0; i < length; i++) {
        this->vobj.push_back(arr[i]);
    }
}

inline void Vector::DestructVectorObject() {
    delete this;
    cout << endl << "vector Object Destructed" << endl;
}

inline void Vector::ClearVectorElements() {
    this->vobj.clear();
}
