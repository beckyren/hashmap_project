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
	int i = getIndex(k);
	//insert the node at the null index
	if(map[i]==NULL){
		map[i] = new hashNode(k,v);
		numKeys++;
	}
	//same keyword, add to the values array
	else if(map[i]!=NULL&&map[i]->keyword==k)
		map[i]->addValue(v);

	//collision detected, recalculate index
	else if(map[i]!=NULL&&map[i]->keyword!=k){
		collisions++;
		while(map[i]!=NULL&&map[i]->keyword!=k){
			if(collfn){
				i = coll1(i, collisions, k);
			}
			else{
				i = coll2(i, collisions, k);
			}
			collisions++;
		}
			map[i] = new hashNode(k,v);
			numKeys++;
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
	//if(load_factor>0.7)
		//reHash();
	int index;
	if(hashfn)
		index = calcHash1(k);//
	else
		index = calcHash2(k);
	return index;
}

//each ascii value is raised to a power that is increasing from left to right
//the values are then added together and modded by the map size
int hashMap::calcHash2(string k){
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
	return (int)sum%mapSize;
}

//adds up ascii numbers corresponding to the key then mods by mapsize
int hashMap::calcHash1(string k){
	int sum = 0;
		for(int i = 0;i<k.length();i++){
			sum+=(int)k[i];
		}
		return sum%mapSize;
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
//First collision method: Quadratic probing
int hashMap::coll1(int h, int i, string k) {//
	int tmp = i;
	int index;
	int size = 0;//copy mapsize value
	//cout<<"The h value is"<<h<<" and the i value is "<<i<<endl;
	while(map[(h+(tmp*tmp))%mapSize]!=NULL&&size<mapSize){
			tmp++;
			size++;
		}
	index = (h+(tmp*tmp))%mapSize;
	return index;
}
//Second collision method: Double hashing
int hashMap::coll2(int h, int i, string k) {
	int first_sum = calcHash1(k);
	int second_sum = calcHash2(k);
	int index = (first_sum + i*second_sum)%mapSize;
	return index;

}
int hashMap::findKey(string k) {
//NOTE: THIS METHOD CANNOT LOOP from index 0 to end of hash array looking for the key.  That destroys any efficiency in run-time. 
	int index = 0;
	if(hashfn)
		index = calcHash1(k);
	else
		index = calcHash2(k);
	while(map[index]->keyword!=k){
		if(map[index]==NULL)
					return -1;
		if(collfn)
			index = coll1(calcHash1(k),collisions,k);
		else if(!collfn)
			index = coll2(calcHash2(k),collisions,k);
	}
	cout<<"Key found at "<<index<<endl;
	cout<<map[index]->keyword<<endl;
	return index;
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


