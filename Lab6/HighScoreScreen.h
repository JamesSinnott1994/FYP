#ifndef HIGHSCORESCREEN_H
#define HIGHSCORESCREEN_H

#include "Sprite.h"
#include "Text.h"
#include "KeyBoardInput.h"
#include <vector>
#include <map>

class HighScoreScreen
{
private:
	Sprite* m_backGroundImage;

	//Globally used font
	TTF_Font *gFont = NULL;
	TTF_Font *gFont2 = NULL;

	//Rendered texture
	vector<Text> scores;
	vector<Text> names;
	Text highscoreText;

	Text name0;
	Text name1;
	Text name2;
	Text name3;
	Text name4;
	Text name5;
	Text name6;
	Text name7;
	Text name8;
	Text name9;

	map<string, int> highscores;
	std::vector<std::pair<std::string, int> > highscoreVector;

	bool haveScores;
	bool tableLoaded;

	int y = 0;
public:
	HighScoreScreen(int, int);

	void Draw();
	int Update();

	void GetServerData();

	void LoadTable(SDL_Color, TTF_Font*);

	map<string, int> HandleData(std::string data);

	// Used for drawing text
	bool initializeTTF();
	bool loadTTFMedia();
};

#endif