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
	//testing hashNodes
	hashNode* me = new hashNode("bleh","bleh2");
	//me->printArray();
	//cout<<("Printed array")<<endl;
	//me->addValue("Becky");
	//me->printArray();
	//cout<<"currSize is :"<<me->getRandValue()<<endl;
	/*for(int i =0;i<80;i++){
		me->addValue("Becky");
	}
	me->dblArray();
	me->printArray();
	*/

	//testing conversion to ascii
	//string me2 = "Hello";
	//cout<<(int)me2[0]<<endl;
	hashMap* me3 = new hashMap(false,true);
	//testing addkey value
	me3->addKeyValue("A_key", "A_value");
	//me3->addKeyValue("A_kez", "A_value");
	//me3->addKeyValue("dfgfgg","Boo");

	//me3->printMap();
	//me3->calcHash1("A_key");
	me3->calcHash1("A_kez");
	//me3->calcHash2("dfgfgg");
	//me3->reHash();
	//me3->coll1(89, 1, "Sweets");
	//me3->printMap();
	me3->findKey("A_key");
	//makeSeuss k("DrSeuss.txt","Seussout.txt",true,true);
	//makeSeuss m("GEChap1a.txt","GEChap1out.txt",false,true);
	//makeSeuss n("DrSeuss.txt","Seussout2.txt",true,false);
	//makeSeuss v("GEChap1a.txt","GEChap1out2.txt",false,false);


	return 0;

}
