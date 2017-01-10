#include <SFML/Graphics.hpp>
#include <unistd.h>
#include <iostream>

int main()
{
	const int XDIM = 1000;
	const int YDIM = 800;	
	const int N = 8;
	
	const int SLEEPTIME = 250000;

	sf::RenderWindow window(sf::VideoMode(XDIM + 10, YDIM + 10), "Phoenix Demo");
	sf::RectangleShape shape[N][N];
	bool isBlue [N*N];
			 

	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++){
			shape[i][j].setSize(sf::Vector2f(XDIM/N, YDIM/N));
			shape[i][j].setOutlineThickness(5);
			shape[i][j].setOutlineColor(sf::Color(255, 255, 255));
			shape[i][j].setFillColor(sf::Color(200, 0, 0));
			shape[i][j].setPosition(i*XDIM/N + 5, j*YDIM/N + 5);

			isBlue[i*N + j] = false;
		}
	

	

	int itr = -1;

	#pragma PHOENIX_VAR {demo} {itr [isBlue N*N]}
	#pragma PHOENIX_START demo
	#pragma PHOENIX_LOOP demo true
	while (window.isOpen() && itr < N*N)
	{
		
		if (itr >= 0 && itr < N*N)
			isBlue[(itr/N)*N + itr%N] = true;
		

		//Determine which color each shape should be.
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++){
				if (isBlue[i*N + j])
					shape[j][i].setFillColor(sf::Color(
							51 + 2*i*j, 
							153 + 2*i*j, 
							255)
							);
				else 
					shape[j][i].setFillColor(sf::Color(200, 0, 0));
			}


		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();

		//Render
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				window.draw(shape[i][j]);

		window.display();

		usleep(SLEEPTIME);
		itr++;
	}
	
	std::cin.ignore(); //Don't immediately die.
	window.clear();
	#pragma PHOENIX_CLEANUP
	return 0;
}
