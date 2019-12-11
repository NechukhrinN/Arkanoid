#include "highscore.h"

/*Method loads actual highscore from the file, 
check it with new score and save it if (new > old), return actual/new highscore*/
int get_highscore(int score)
{
	int highScore = 0;
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
