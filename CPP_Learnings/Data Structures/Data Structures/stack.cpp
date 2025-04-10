#include<iostream>
#include<map>
using namespace std;
int main()
{
	map<int, string*>map1 =
	{ {1,new string("hello")},{2,new string("World")} };
	cout << *map1[1];

}