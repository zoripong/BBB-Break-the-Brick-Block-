#ifndef __PLAYER_H__
#define __PLAYER_H__

using namespace std;

class Player{
private:
	string name;
	int score;
	string date;
public:
	Player(string name, int score);
	string getName();
	void setName(string name);

	int getScore();
	void setScore(int score);
	void increaseScore(int blockType);

	string getDate();
	void setDate(string date);
};

#endif