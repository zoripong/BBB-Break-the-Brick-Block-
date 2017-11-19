#ifndef __PLAYER_H__
#define __PLAYER_H__

using namespace std;

class Player{
private:
	string name;
	string password;
	int score;
	string date;
	string filePath;
public:
	Player(string name);
	Player(string name, string password, int score);

	string getName();
	void setName(string name);

	int getScore();
	void setScore(int score);
	void increaseScore(int blockType);

	string getDate();
	void setDate(string date);
	
	string getPassword();

	string getFilePath();
};

#endif