#include<iostream>
#include<string>
#include<conio.h>
#include <ctime>
#include "Player.h"

#define _CRT_SECURE_NO_WARNINGS
using namespace std;

extern void gotoxy(int x, int y);


//http://code.i-harness.com/ko/q/f3a3a


Player::Player(string name, int score){
	this->name = name;
	this->score = score;
	
	time_t t = time(0);
	struct tm * now = localtime(&t);
	date = (now->tm_year + 1900) + "-" + (now->tm_mon + 1);
	date += "-" + now->tm_mday;
	cout << date;
}

string Player::getName(){
	return this->name;
}
void Player::setName(string name){
	this->name = name;
}

int Player::getScore(){
	return this->score;
}
void Player::setScore(int score){
	this->score = score;
}
void Player::increaseScore(int blockType){
	switch (blockType){
	case 1:
		this->score += 50;
		break;
	case 2:
		this->score += 300;
		break;
	case 4:
		this->score += 100;
		break;
	case 5:
		this->score += 150;
		break;
	case 6:
		this->score += 30;
		break;
	case 7:
		this->score += 75;
		break;
	}
}

string Player::getDate(){
	return this->date;
}
void Player::setDate(string date){
	this->date = date;
}