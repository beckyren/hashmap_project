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

void hashMap::addKeyValue(string k, string v){
	int index = getIndex(k);
	if(map[index] == NULL){
		map[index] = new hashNode(k, v);
		numKeys++;
	}
	else if(map[index]->keyword == k)
		map[index]->addValue(v);
		//numKeys++;
	float loadFactor = ((float)numKeys) / ((float)mapSize);
	if(loadFactor > 0.70)
		reHash();
}

int hashMap::getIndex(string k) {
	int index;
	if(hashfn)
		index = calcHash1(k);
	else
		index = calcHash2(k);
	if(map[index] == NULL)
		return index;
	else if(map[index] != NULL && map[index]->keyword == k)
		return index;

	else{
		if(collfn){
			hashcoll++;
			index = coll1(hashcoll, index, k);
			return index;
		}
		else{
			hashcoll++;
			index = coll2(hashcoll, index, k);
			return index;
		}
	}
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
	cout<<"calchash 2 gave "<<sum%mapSize<<endl;
	return (int)sum%mapSize;
}

//adds up ascii numbers corresponding to the key then mods by mapsize
int hashMap::calcHash1(string k){
	int sum = 0;
		for(int i = 0;i<k.length();i++){
			sum+=(int)k[i];
		}
		cout<<"calchash 1 gave "<<sum%mapSize<<endl;
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
	cout<<"The h value is"<<h<<" and the i value is "<<i<<endl;
	while(map[(h+(tmp*tmp))%mapSize]!=NULL&&size<mapSize){
			tmp++;
			collisions++;
		}
	index = (h+(tmp*tmp))%mapSize;
	cout<<"coll1 index is "<<index<<endl;
	return index;
}
//Second collision method: Double hashing
int hashMap::coll2(int h, int i, string k) {
	int first_sum = calcHash1(k);
	int second_sum = calcHash2(k);
	int index = (first_sum + i*second_sum)%mapSize;
	while(map[index]!=NULL){
		index = (index+1)%mapSize;
		collisions++;
	}
	cout<<"coll2 index is "<<index<<endl;
	return index;

}
int hashMap::findKey(string k) {
	int index = getIndex(k);
	if(map[index] == NULL || map[index]->keyword != k){
		return -1;
	}
	else{
		cout<<"Index is "<<index<<endl;
		return index;
	}
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


