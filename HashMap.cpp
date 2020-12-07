/*
 * HashMap.cpp
 *
 *  Created on: May 4, 2020
 *      Author: 13027
 */


#include "hashMap.hpp"
#include "hashNode.hpp"
#include <iostream>
#include <math.h>
#include <string>
using namespace std;

hashMap::hashMap(bool hash1, bool coll1) {
	hashfn = hash1;
	collfn = coll1;
	map = NULL;
	numKeys = 0;
	mapSize = 100;
	first = "";
	collisions = 0;
	hashcoll = 0;
	map = new hashNode*[mapSize];
	for(int i =0;i<mapSize;i++){
		map[i] = NULL;
	}
}

void hashMap::addKeyValue(string k, string v) {
if(hashfn){
	int i = calcHash1(k);
	//insert the node at the null index
	if(map[i]==NULL){
		map[i] = new hashNode(k,v);
		numKeys++;//update number of keys??
	}
	//same keyword, add to the values array
	else if(map[i]!=NULL&&map[i]->keyword==k)
		map[i]->addValue(v);

	//collision detected, recalculate index
	else if(map[i]!=NULL&&map[i]->keyword!=k){
		int sum =0;
		//calculate h for collision function
		for(int i = 0;i<k.length();i++){
			sum+=(int)k[i];
		}
		//keep track of insertions for collision function
		int insertion_attempts = 0;

		while(map[i]!=NULL&&map[i]->keyword!=k){
			if(collfn){
				i = coll1(sum, insertion_attempts, k);
			}
			else{
				i = coll1(sum, insertion_attempts, k);
			}
			insertion_attempts++;
		}
	}
}
	//calculate load factor
	double load_factor = (double)numKeys/(double)mapSize;
	if(load_factor>0.7)
		reHash();

}
int hashMap::getIndex(string k) {
}

int hashMap::calcHash2(string k){
}
int hashMap::calcHash1(string k){
}
void hashMap::getClosestPrime() {
}
void hashMap::reHash() {
}
int hashMap::coll1(int h, int i, string k) {
}
int hashMap::coll2(int h, int i, string k) {
}
int hashMap::findKey(string k) {
//NOTE: THIS METHOD CANNOT LOOP from index 0 to end of hash array looking for the key.  That destroys any efficiency in run-time. 
}


void hashMap::printMap() {
	cout << "In printMap()" << endl;
	for (int i = 0; i < mapSize; i++) {
		//cout << "In loop" << endl;
		if (map[i] != NULL) {
			cout << map[i]->keyword << ": ";
			for (int j = 0; j < map[i]->currSize;j++) {
				cout << map[i]->values[j] << ", ";
			}
			cout << endl;
		}
	}
}


