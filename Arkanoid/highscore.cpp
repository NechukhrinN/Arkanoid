#include "highscore.h"

int get_highscore(int score)
{
	int highScore;
	std::ifstream readFile;
	
	readFile.open("res/highscore.txt");
	if (readFile.is_open())
	{
		while (!readFile.eof())
		{
			readFile >> highScore;
		}		
	}
	readFile.close();

	std::ofstream writeFile("res/highscore.txt");
	if (writeFile.is_open())
	{
		if (score > highScore)
		{
			highScore = score;
			
		}
		writeFile << highScore;
		
	}
	writeFile.close();
	
	return highScore;
}
