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
	int i = getIndex(k);
	//insert the node at the null index
	if(map[i]==NULL){
		map[i] = new hashNode(k,v);
		cout<<"Successfully found an empty node. 1 attempt"<<endl;
		numKeys++;//update number of keys??
	}
	//same keyword, add to the values array
	else if(map[i]!=NULL&&map[i]->keyword==k)
		map[i]->addValue(v);

	//collision detected, recalculate index
	else if(map[i]!=NULL&&map[i]->keyword!=k){
		hashcoll++;
		int sum =0;
		//calculate h for collision function
		if(hashfn)
			sum = calcHash1(k);
		else
			sum = calcHash2(k);

		//keep track of insertions for collision function
		int insertion_attempts = 0;

		while(map[i]!=NULL&&map[i]->keyword!=k){
			cout<<"Collision detected"<<endl;
			if(collfn){
				cout<<"Using first coll method"<<endl;
				i = coll1(sum, insertion_attempts, k);
				cout<<i<<endl;
			}
			else{
				i = coll2(sum, insertion_attempts, k);
			}
			map[i] = new hashNode(k,v);
			insertion_attempts++;
			if(insertion_attempts>3)
				cout<<"While loop ma dude"<<endl;
		}
	}
}
	//calculate load factor
	double load_factor = (double)numKeys/(double)mapSize;
	if(load_factor>0.7)
		reHash();

}
int hashMap::getIndex(string k) {
	// (6 pts) uses calcHash and reHash to
	// calculate and return the index of where
	// the keyword k should be inserted into the map
	// array
	double load_factor = (double)numKeys/(double)mapSize;
	if(load_factor>0.7)
		reHash();
	int index;
	if(hashfn)
		index = calcHash1(k);
	else if(!hashfn)
		index = calcHash2(k);
	return index;
}

int hashMap::calcHash2(string k){
	int exponent = 1;
	int sum = 0;
	int ascii = 0;
	int count =0;
	for(int i =0;i<k.length();i++){
		ascii+=(int)k[i];
	}
	//find the length of ascii
	int ascii_copy = ascii;
	while(ascii_copy>0){
		ascii_copy/=10;
		count++;
	}
	while(ascii>0){
		int base = ascii%10;
		ascii/=10;
		int add = pow(base, count);
		sum+=add;
		count--;
	}
	//convert to int then mod going backwards
	cout<<"The sum calculated from hash2 is "<<sum<<endl;
	cout<<"The value returned is "<<sum%mapSize<<endl;
	return (int)sum%mapSize;
}
int hashMap::calcHash1(string k){
	int sum = 0;
		int index;
		for(int i = 0;i<k.length();i++){
			sum+=(int)k[i];
			cout<<"Sum is "<<sum<<endl;
		}
		index = sum%mapSize;
		cout<<"calcHash gave "<<index<<endl;
		return index;
}
void hashMap::getClosestPrime() {
	int dbl = mapSize*2;
		bool notprime= true;
		while(notprime){
			int count = 0;
		for(int j =2; j< dbl-1;j++){
			if(dbl%j==0)
				count++;//keep track of numbers it is divisible by
		}
		if(count==0)
			notprime = false;
		else
			dbl++;
		}
		mapSize = dbl;//
		cout<<"The calculated closest prime is "<<dbl<<endl;

}
void hashMap::reHash() {
	int size = mapSize;
	getClosestPrime();
	hashNode** map2 = new hashNode*[mapSize];
	for(int i = 0;i<mapSize;i++){
		map2[i]=NULL;
	}
	for(int i =0;i<size;i++){
		if(map[i]!=NULL){
			int new_index = getIndex(map[i]->keyword);
			map2[new_index]= map[i];
		}
	}
	delete[]map;
	map = map2;

//
}//
int hashMap::coll1(int h, int i, string k) {//
	int tmp = i;
	int index;
	//cout<<"The h value is"<<h<<" and the i value is "<<i<<endl;
	cout<<"Collision1 method calculated"<<(h+(i*i))%mapSize<<endl;
	while(map[(h+(tmp*tmp))%mapSize]!=NULL){
			tmp++;
		}
	index = (h+(tmp*tmp))%mapSize;
	cout<<"index value is "<<index<<endl;
	return index;
}
int hashMap::coll2(int h, int i, string k) {
	//to be modified

}
int hashMap::findKey(string k) {
//NOTE: THIS METHOD CANNOT LOOP from index 0 to end of hash array looking for the key.  That destroys any efficiency in run-time. 
}


void hashMap::printMap() {
	cout << "In printMap()" << endl;
	cout<<mapSize<<endl;
	for (int i = 0; i < mapSize; i++) {
		cout << "In loop" << endl;
		if(map[i] != NULL) {
			cout << map[i]->keyword << ": ";
			for (int j = 0; j < map[i]->currSize;j++) {
				cout << map[i]->values[j] << ", ";
			}
			cout <<"Ended fine"<< endl;
	}
}
}


