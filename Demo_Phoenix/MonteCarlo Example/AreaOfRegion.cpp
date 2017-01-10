#include <iostream>
#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <fstream>
#include <cmath>
#include <stdlib.h>     
#include <time.h>
#include <vector>
#include <algorithm>

using namespace std;



class rectangle{
	public:
	rectangle(){x1 = x2 = y1 = y2 = 0;}
	int x1, x2, y1, y2;

	bool isInside(int x, int y){
		bool inX = false, inY = false;
				
		if ((x1 <= x && x <= x2) ||
		   (x2 <= x && x <= x1))
			inX = true; 
		    
		if ((y1 <= y && y <= y2) ||
		   (y2 <= y && y <= y1))
			inY = true;

		if (inX && inY)
			return true;
		else
			return false;
	}

	//To back up variables (checkpointing)
	friend ofstream & operator<<(ofstream & ofs, const rectangle & r);

	//To read in variables (checkpointing)
	friend ifstream & operator>>(ifstream & ifs, rectangle & r);

	//To read in variables from stdin
	friend istream & operator>>(istream & is, rectangle & r);

};

ofstream & operator<<(ofstream & ofs, const rectangle & r){
	ofs << r.x1 << " " << r.x2 << " " << r.y1 << " " << r.y2 << endl;
	return ofs;
}

ifstream & operator>>(ifstream & ifs, rectangle & r){
	ifs >> r.x1 >> r.x2 >> r.y1 >> r.y2;
	return ifs;	
}

istream & operator>>(istream & is, rectangle & r){	
	is >> r.x1 >> r.x2 >> r.y1 >> r.y2;
	//cout << "[" << r.x1 << " : " << r.x2 << "]\t[" << r.y1 << " : " << r.y2 << "]" << endl;
	return is;
}



const int WIN_X = 800;
const int WIN_Y = 800;



void RenderWindow_DoMonteCarlo(rectangle * r){
	sf::RenderWindow window(sf::VideoMode(WIN_X, WIN_Y), "Hit or Miss Monte Carlo");
	sf::RectangleShape shape[10];
	vector<sf::RectangleShape> pixels;

	for (int i = 0; i < 10; i++){
		int 	xsize = abs(r[i].x2 - r[i].x1),
			ysize = abs(r[i].y2 - r[i].y1),
			xpos = min(r[i].x1, r[i].x2),
			ypos = min(r[i].y1, r[i].y2);

		shape[i].setSize(sf::Vector2f(xsize, ysize));
		shape[i].setPosition(xpos, ypos);
		shape[i].setFillColor(sf::Color(0, 0, 255 - 10*i, 200));
	}

	//For Monte Carlo
	srand (time(NULL));
	long long numHits = 0;
	long long numThrows = 0;
	
	double currentGuess, prevGuess, err;
	currentGuess = prevGuess = -1000;

	#pragma PHOENIX_VAR {integrate} {numHits numThrows currentGuess prevGuess err}
	#pragma PHOENIX_START integrate
	#pragma PHOENIX_LOOP integrate numThrows % 250 == 0	
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		
		//Pick a random (x, y);
		int x = rand()%801;
		int y = rand()%801;
		numThrows++;

		//Check if hit
		bool inside = false;
		for (int i = 0; i < 10; i++)
			if (r[i].isInside(x, y)){
				inside = true;
			}

		if (inside)
			numHits++;
		
		//Update data
		if (numThrows % 50 == 0){
			prevGuess = currentGuess;
			currentGuess = ((double)numHits/(double)numThrows)*800.0*800.0;
			err = abs(100*(currentGuess - prevGuess)/prevGuess);
			
			printf("Throws = %-8llu\tHits = %-6llu\tCurrent Guess = %-8f\tPercent Changed = %-5f\%\n", numThrows, numHits, currentGuess, err);
		}

		sf::RectangleShape pixel;
		pixel.setSize(sf::Vector2f(3, 3));
		pixel.setPosition(x, y);
		
		if (inside)	pixel.setFillColor(sf::Color(0, 255, 0, 255));
		else 		pixel.setFillColor(sf::Color(255, 0, 0, 255));
		
		pixels.push_back(pixel);

		window.clear(sf::Color(255, 255, 255, 255));
		for (int i = 0; i < 10; i++){
			window.draw(shape[i]);			
		}


		for (int i = 0; i < pixels.size(); i++)
			window.draw(pixels[i]);

		window.display();
	}//*/
}

int main(){
	rectangle rectangles [10];
	
	#pragma PHOENIX_VAR {rects} {[rectangles 10]}
	#pragma PHOENIX_START rects

	printf("Enter 10 rectangles (no larger than 800 on each side):\n");
	for (int i = 0; i < 10; i++)
		cin >> rectangles[i];

	#pragma PHOENIX_CHECKPOINT rects	
	
	RenderWindow_DoMonteCarlo(rectangles);

	
}



