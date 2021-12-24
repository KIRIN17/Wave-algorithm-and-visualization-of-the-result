#include <SFML/Graphics.hpp>
#include <math.h>
#include <iostream>

#include "Functions.h"
#include "Tests.h"

int main()
{
    Tests();

    const double PI = 3.141592653589793;
    std::srand(0);

    std::ifstream input1("Graph2.txt");
    Graph graph1(input1);

    int N = graph1.vertices_count;
    int width = 1200;
    int height = 900;
    int R = 30.f;

    sf::RenderWindow window(sf::VideoMode(width, height), "SFML works!");

    sf::CircleShape shape(R);

    DynamicArray<Pair<int,int>> pos(N);
    int R_res_circle = std::sqrt(width*height/(PI * 3));

    double phi = 2 * PI / N;
    double step = 2 * PI / N;
    for (int i = 0; i < N; ++i) {
        pos[i].first = R_res_circle * std::sin(phi) + width/2;
        pos[i].second = R_res_circle * std::cos(phi) + height/2;

        phi += step;
    }


    DynamicArray<Pair<int,Pair<int,int>>> colors(N);
    for (int i = 0; i < N; ++i) {
        shape.setPosition(pos[i].first,pos[i].second);
        shape.setFillColor(sf::Color(219, 35, 35));
        window.draw(shape);
    }

    std::cout << "Select the starting vertex (from 0 to " << graph1.vertices_count - 1 << " )\n";
    int start;
    std::cin >> start;

    std::cout << "Select the end vertex (0 to " << graph1.vertices_count - 1 << " )\n";
    int finish;
    std::cin >> finish;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }



        window.clear(sf::Color(255, 255, 255));
        int corr = 30;
        for (int i = 0; i < graph1.vertices_count; ++i) {
            for (int j = 0; j < graph1.Get(i).GetSize(); ++j) {
                sf::Vertex a(sf::Vector2f(pos[graph1.Get(i).Get(j)].first + corr,pos[graph1.Get(i).Get(j)].second + corr));
                a.color = sf::Color::Black;

                sf::Vertex b(sf::Vector2f(pos[i].first + corr,pos[i].second + corr));
                b.color = sf::Color::Black;
                sf::Vertex line[]{a, b};

                window.draw(line,2,sf::Lines);
            }
        }

        for (int i = 0; i < N; ++i) {
            shape.setPosition(pos[i].first,pos[i].second);
            shape.setFillColor(sf::Color(0,0,0));
            window.draw(shape);
        }


        DynamicArray<int> path = wave_algorithm(graph1,start,finish);

        for (int i = 0; i < path.GetSize() - 1; ++i) {

            sf::Vertex a(sf::Vector2f(pos[path[i]].first + corr,pos[path[i]].second + corr));
            a.color = sf::Color::Green;

            sf::Vertex b(sf::Vector2f(pos[path[i + 1]].first + corr,pos[path[i + 1]].second + corr));
            b.color = sf::Color::Green;
            sf::Vertex line[]{a, b};

            window.draw(line,2,sf::Lines);

        }
        for (int i = 0; i < path.GetSize(); ++i) {
            shape.setPosition(pos[path[i]].first,pos[path[i]].second);
            shape.setFillColor(sf::Color(219, 35, 35));
            window.draw(shape);
        }

        sf::Font font;
        font.loadFromFile("Fonts/FontsFree-Net-Komika.ttf");
        for (int i = 0; i < graph1.vertices_count; ++i) {
            sf::Text text;
            text.setFont(font);
            text.setCharacterSize(50);
            text.setColor(sf::Color::White);
            text.setStyle(sf::Text::Bold);
            text.setString(std::to_string(i));
            text.setPosition(pos[i].first + corr / 2,pos[i].second);
            window.draw(text);
        }
        window.display();
    }

    return 0;
}