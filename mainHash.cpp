/*
 * mainHash.cpp
 *
 *  Created on: May 4, 2020
 *      Author: 13027
 */


#include <iostream>
#include "makeSeuss.hpp"
#include <time.h>
#include <stdlib.h>

using namespace std;
int main() {
	srand(time(NULL));

	hashNode* me = new hashNode("bleh","bleh2");
	me->printArray();
	cout<<("Printed array")<<endl;
	//testing conversion to ascii
	//string me2 = "Hello";
	//cout<<(int)me2[0]<<endl;
	hashMap* me3 = new hashMap(true,true);
	makeSeuss k("DrSeuss.txt","Seussout.txt",true,true);
	makeSeuss m("GEChap1a.txt","GEChap1out.txt",false,true);
	makeSeuss n("DrSeuss.txt","Seussout2.txt",true,false);
	makeSeuss v("GEChap1a.txt","GEChap1out2.txt",false,false);


	return 0;

}
