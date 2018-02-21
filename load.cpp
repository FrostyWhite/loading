//
//  main.cpp
//  Spinning balls
//
//  Created by Kuura Parkkola on 21/02/2018.
//  Copyright © 2018 Kuura Parkkola. All rights reserved.
//

#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <utility>
#include <unistd.h>

class circle {
public:
	circle(std::pair<int, int> p_center, short p_phase, int p_distance = 20){
		sf::CircleShape circle(20);
		phase = p_phase;
		distance = p_distance;
		center = p_center;
		r = 255;
		g = 255;
		b = 255;
		circle.setFillColor(sf::Color(r, g, b, 255));
		object = circle;
	}
	
	void increment(int pulse){
		phase++;
		if(phase >= 180) phase = 0;
		object.setPosition(center.first - 20 + distance * sin((-2*phase*M_PI)/180), center.second - 20 + distance * cos((-2*phase*M_PI)/180));
		object.setFillColor(sf::Color(255, 255, 255, pulse));
	}
	
	sf::CircleShape getObject(){
		return object;
	}
	
	friend std::ostream& operator << (std::ostream& os, const circle &circle){
		os << "Center: " << circle.center.first << "," << circle.center.second << " phase: " << circle.phase << " distance: " << circle.distance;
		return os;
	}
	
private:
	sf::CircleShape object;
	short phase;
	int distance;
	std::pair<int, int> center;
	int r, g, b;
};

int main(int argc, const char * argv[]) {
	sf::RenderWindow window(sf::VideoMode(100,100), "Spinning");
	
	std::cout << window.getSize().x / 2 << "," << window.getSize().y / 2 << std::endl;
	
	std::pair<int, int> center = std::make_pair((int) (window.getSize().x / 2), (int) (window.getSize().y / 2));
	
	std::cout << center.first << std::endl;
	
	circle cir1(center, 0);
	circle cir2(center, 30);
	circle cir3(center, 60);
	circle cir4(center, 90);
	circle cir5(center, 120);
	circle cir6(center, 150);
	
	int alphavalue = 0;
	int alphaphase = 0;
	
	while (window.isOpen()) {
		
		alphaphase += 1;
		if(alphaphase >= 180) alphaphase = 0;
		alphavalue = (sin((alphaphase * M_PI) / 180) + 1) * 127;
		
		sf::Event event;
		while (window.pollEvent(event))
		{
			// Close window: exit
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			
			// Escape pressed: exit
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
				window.close();
			}
		}
		
		//std::cout << cir1 << std::endl;
		std::cout << cir1.getObject().getPosition().x << std::endl;
		
		cir1.increment(alphavalue);
		cir2.increment(alphavalue);
		cir3.increment(alphavalue);
		cir4.increment(alphavalue);
		cir5.increment(alphavalue);
		cir6.increment(alphavalue);
		
		window.clear();
		
		window.draw(cir1.getObject());
		window.draw(cir2.getObject());
		window.draw(cir3.getObject());
		window.draw(cir4.getObject());
		window.draw(cir5.getObject());
		window.draw(cir6.getObject());
		
		window.display();
		usleep(10000);
		
	}
	return 0;
}
