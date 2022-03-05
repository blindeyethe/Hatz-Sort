#define OLC_PGE_APPLICATION

#include <iostream>
#include <random>
#include <cmath>
#include "olcPixelGameEngine.h"

struct vec2d
{
	int x, y;
};

struct line
{
	int value;
	vec2d startPosition, endPosition;

	void SetPosition(vec2d startPos, vec2d endPos)
	{
		startPosition = startPos;
		endPosition = endPos;
	}
};

class SortingAlgorithm : public olc::PixelGameEngine
{
public:
	SortingAlgorithm(int pUnit) : pixelUnit(pUnit)
	{
		sAppName = "Sorting Algorithm";
	}


private:
	int pixelUnit;
	bool sortingStarted;

	int lengthArray;
	line lineArray[480];

	int iHold = 0;

	int jHit = 1;
	int jMiss = 0;

public:
	bool OnUserCreate() override
	{
		return true;
	}

	bool OnUserUpdate(float elapsedTime) override
	{
		if (!sortingStarted)
		{
			Input();
			DrawGraph();
			sortingStarted = true;
		}
		else
			Sort();

		return true;
	}

private:
	void OldInput()
	{
		std::cin >> lengthArray;
	
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> distr(0, ScreenHeight());

		for (int i = 0; i < lengthArray; i++)
			lineArray[i].value = distr(gen);
	}
	
	void Input()
	{
		std::cout << "Length: ";
		std::cin >> lengthArray;

		for (int i = 1; i <= lengthArray; i++)
			lineArray[i].value = i*2;

		srand(time(0));

		for (int i = lengthArray - 1; i > 0; i--)
		{
			int j = rand() % (i + 1);
			std::swap(lineArray[i], lineArray[j]);
		}
	}

	void DrawGraph()
	{
		FillRect(0, 0, ScreenWidth(), ScreenHeight(), olc::BLACK);

		vec2d startPos{ 5, 0 };

		for (int i = 0; i < lengthArray; i++)
		{
			vec2d endPos{ startPos.x, lineArray[i].value };

			DrawLine(startPos.x, startPos.y, endPos.x, endPos.y);

			lineArray[i].SetPosition(startPos, endPos);

			startPos.x += pixelUnit;
		}
	}

	void Sort()
	{
		if (iHold == lengthArray - 1)
		{
			sortingStarted = false;
			iHold = 0;
			return;
		}

		for (int i = iHold; i < lengthArray - 1; i++)
		{

			for (int j = i + jHit + jMiss; j < lengthArray; j++)
			{

				if (lineArray[i].value > lineArray[j].value)
				{
					std::swap(lineArray[i], lineArray[j]);

					jHit++;
					if (jHit + jMiss == lengthArray - iHold)
						ResetHolders();

					DrawGraph();
					DrawColorLine(lineArray[i], olc::GREEN);
					DrawColorLine(lineArray[j], olc::GREEN);

					return;
				}
				jMiss++;

				if (jHit + jMiss == lengthArray - iHold)
					ResetHolders();
			}
		}
	}

	void DrawColorLine(line line, olc::Pixel color)
	{
		DrawLine(line.startPosition.x, line.startPosition.y, line.endPosition.x, line.endPosition.y, color);
	}

	void ResetHolders()
	{
		iHold++;
		jHit = 1;
		jMiss = 0;
	}
};

int main()
{
	int pixelUnit = 2;
	SortingAlgorithm window(pixelUnit);

	if (window.Construct(480, 400, pixelUnit, pixelUnit))
		window.Start();
}
