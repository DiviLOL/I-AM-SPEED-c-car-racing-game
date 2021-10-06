#include <SFML/Graphics.hpp>
#include <math.h> 
#include <iostream>

using namespace sf;
using namespace std;

float lap = 0;


const int num = 8; //checkpoints
int points[num][2] = { 300, 610,
                      1270,430,
                      1380,2380,
                      1900,2460,
                      1970,1700,
                      2550,1680,
                      2560,3150,
                      500, 3300 };


struct Car
{
    float x, y, speed, angle; int n;
    Car() { speed = 2;angle = 0;n = 0; }

    void move() {
        x += sin(angle) * speed;
        y -= cos(angle) * speed;
    }

    void findTarget()
    {
        float tx = points[n][0];
        float ty = points[n][1];
        float beta = angle - atan2(tx - x, -ty + y);
        if (sin(beta) < 0) angle += 0.005 * speed; else angle -= 0.005 * speed;
        if ((x - tx) * (x - tx) + (y - ty) * (y - ty) < 25 * 25) n = (n + 1) % num;
    }

    void Destroy()
    {
        x  = 0;
    }
};

void main_game(){
    RenderWindow window(sf::VideoMode(640, 480), "I AM SPEED");
    window.setFramerateLimit(60);
    sf::RectangleShape collsion(sf::Vector2f(260+70,1234+234*1.7+78+5));
    sf::RectangleShape collsion2(sf::Vector2f(260*7,123*1.2));
    sf::RectangleShape collsion3(sf::Vector2f(260+70,1234+123*2+78+45));
    sf::RectangleShape collsion4(sf::Vector2f(260*2.9,260*1.3));
    sf::RectangleShape collsion5(sf::Vector2f(260*2.9,260*1.3));
    sf::RectangleShape lap_rect(sf::Vector2f(400-200,109*1.6));
    sf::RectangleShape Car_collsion(sf::Vector2f(44,46));
    collsion2.setFillColor(Color::Blue);
    collsion5.setFillColor(Color::Black);
    Car_collsion.setScale(0.7,0.7);
    Texture car_texture, background_texture;
    car_texture.loadFromFile("car.png");
    background_texture.loadFromFile("background.png");
    car_texture.setSmooth(true);
    background_texture.setSmooth(true);

    Sprite sCar(car_texture), sBackground(background_texture);

    float x = 300, y = 300;
    float speed = 0, angle = 0;
    float maxSpeed = 12.f;
    float acc = 0.2f, dec = 0.3f;
    float turnSpeed = 0.08f;
    int OffsetX = 0, OffsetY = 0;
    const float PI = 3.141592;
    sCar.setOrigin(22, 22);
    sf::Font font;
    font.loadFromFile("LeanForeword-MR0x.ttf");

    int R = 22;

    const int N = 5;
    Car car[N];
    for (int i = 0;i < N;i++)
    {
        car[i].x = 300 + i * 50;
        car[i].y = 1700 + i * 80;
        car[i].speed = 7 + i;
    }

    Clock clock;
    Event event;
    sBackground.setScale(2, 2);
    sf::Text text;

    // select the font
    text.setFont(font); // font is a sf::Font

    text.setPosition(100,100);

    // set the string to display
    text.setString("Game Over!");

    // set the character size
    text.setCharacterSize(24+12+12+12+12); // in pixels, not points!

    // set the color
    text.setFillColor(sf::Color::Yellow);

    // set the text style
    text.setStyle(sf::Text::Bold);

    sf::Text text2;

    // select the font
    text2.setFont(font); // font is a sf::Font

    text2.setPosition(100,100);

    // set the string to display
    text2.setString("Game Win!");

    // set the character size
    text2.setCharacterSize(24+12+12+12+12); // in pixels, not points!

    // set the color
    text2.setFillColor(sf::Color::Yellow);

    // set the text style
    text2.setStyle(sf::Text::Bold);

    bool Show_Game_Over = 0;
    bool Show_Game_Win = 0;
    bool lap_can_happen = 0;

    while (window.isOpen())
    {
        
        //cout<<x<<"  "<<y;
        while (window.pollEvent(event))
        {

            if (event.type == sf::Event::Closed)
                window.close();

        }


        bool Up = 0, Down = 0, Right = 0, Left = 0;
        if (Keyboard::isKeyPressed(Keyboard::Right)){
            Right = 1;
            //cout<<" x : "<<sCar.getPosition().x<<" y : "<<sCar.getPosition().y;
        }
        if (Keyboard::isKeyPressed(Keyboard::Left)){
            Left = 1;
            //cout<<" x : "<<sCar.getPosition().x<<" y : "<<sCar.getPosition().y;
        }
        if (Keyboard::isKeyPressed(Keyboard::Up)){
            Up = 1;
            //cout<<" x : "<<sCar.getPosition().x<<" y : "<<sCar.getPosition().y;
        }
        if (Keyboard::isKeyPressed(Keyboard::Down)){
            Down = 1;
            //cout<<" x : "<<sCar.getPosition().x<<" y : "<<sCar.getPosition().y;
        }

        if (Keyboard::isKeyPressed(Keyboard::S)){
            maxSpeed = 12.f;
            Show_Game_Over = 0;
        }

        if(!maxSpeed == 0){

            if (Up && speed < maxSpeed) {
            if (speed < 0) speed += dec;
            else speed += acc;
            }

            if (Down && speed > -maxSpeed) {
                if (speed > 0) speed -= dec;
                else speed -= acc;
            }
        }

        if (!Up && !Down)
            if (speed - dec > 0) speed -= dec;
            else if (speed + dec < 0) speed += dec;
            else speed = 0;

        if(!maxSpeed == 0){
            if (Right && speed != 0) angle += turnSpeed * speed / maxSpeed;
            if (Left && speed != 0) angle -= turnSpeed * speed / maxSpeed;
        }

        
        //collsion
        for(int i=0;i<N;i++)
        for(int j=0;j<N;j++)
        {      
            int dx=0, dy=0;
            while (dx*dx+dy*dy<4*R*R)
            {
            car[i].x+=dx/10.0;
            car[i].x+=dy/10.0;
            car[j].x-=dx/10.0;
            car[j].y-=dy/10.0;
            dx = car[i].x-car[j].x;
            dy = car[i].y-car[j].y;
            if (!dx && !dy) break;
         }
    }

        car[0].speed = speed;
        car[0].angle = angle;



        for (int i = 0;i < N;i++) car[i].move();
        for (int i = 1;i < N;i++) car[i].findTarget();

        if (car[0].x > 320) OffsetX = car[0].x - 320;
        if (car[0].y > 240) OffsetY = car[0].y - 240;

        if(car[0].x < 0+130) Show_Game_Over = 1;
        if(car[0].y < 0+130) Show_Game_Over = 1;

        if(car[0].x > background_texture.getSize().x*2-150){
            maxSpeed -= 12;
            Show_Game_Over = 1; 
        }
        if(car[0].y > background_texture.getSize().y*2-150){
            maxSpeed -= 12;
            Show_Game_Over = 1; 
        }

        if (car[0].x > 1400*1.4){
            if(car[0].y < 0+340*3.9){
                maxSpeed -= 12;
                Show_Game_Over = 1;  
            }
        }

        //sCar.setColor(Color::Blue);
        window.clear(Color::Cyan);
         if (Car_collsion.getGlobalBounds().intersects(collsion3.getGlobalBounds())){
            maxSpeed -= 12;
            Show_Game_Over = 1;     
        }

        if (Car_collsion.getGlobalBounds().intersects(collsion.getGlobalBounds())){
            maxSpeed -= 12;
            Show_Game_Over = 1;     
        }

        if (Car_collsion.getGlobalBounds().intersects(collsion2.getGlobalBounds())){
            maxSpeed -= 12;
            Show_Game_Over = 1;   
        }

        if (Car_collsion.getGlobalBounds().intersects(collsion4.getGlobalBounds())){
            maxSpeed -= 12;  
            Show_Game_Over = 1; 
        }

        if (Car_collsion.getGlobalBounds().intersects(collsion5.getGlobalBounds())){
            maxSpeed -= 12; 
            Show_Game_Over = 1;  
        }
        
        if (car[0].x > 900){
            lap_can_happen = 1;
        }

        if (lap == 3){
            maxSpeed -= 12; 
            Show_Game_Win = 1;  
        }

        if(lap_can_happen == 1)
        {
            if (Car_collsion.getGlobalBounds().intersects(lap_rect.getGlobalBounds()))
            {
                lap += 1;
                lap_can_happen = 0;
                
            }
            
        }
        if (Car_collsion.getGlobalBounds().intersects(collsion5.getGlobalBounds())){
            maxSpeed -= 12; 
            Show_Game_Over = 1;  
        }

        Car_collsion.setPosition(car[0].x - OffsetX, car[0].y - OffsetY);
        window.draw(sBackground);
        sBackground.setPosition(-OffsetX, -OffsetY);
        //window.draw(collsion);
        //window.draw(Car_collsion);
        if (Show_Game_Over == 1){
            window.draw(text);
            maxSpeed = 0;
        }

        if (Show_Game_Win == 1){
            window.draw(text2);
            maxSpeed = 0;
        }

        Color colors[10] = { Color::Red, Color::Green, Color::Magenta, Color::Blue, Color::White };

        for (int i = 0;i < N;i++)
        {
            sCar.setPosition(car[i].x - OffsetX, car[i].y - OffsetY);
            sCar.setRotation(car[i].angle * 180 / 3.141593);
            sCar.setColor(colors[i]);
            window.draw(sCar);
        }
        lap_rect.setPosition(602.48-380-OffsetX,109.596*23.4-OffsetY);
        collsion4.setPosition(950-OffsetX,1500*1.9-OffsetY);
        collsion.setPosition(950-OffsetX,510-OffsetY);
        collsion3.setPosition(1500-25-OffsetX,510-OffsetY);
        collsion2.setPosition(12-OffsetX,12-OffsetY);
        window.draw(lap_rect);
        collsion5.setPosition(950-OffsetX,1500*2.278-OffsetY);
        window.display();
    }
};

int main()
{
    RenderWindow start_up_screen(VideoMode(640,480),"I AM SPEED Menu");
    Texture background_texture;
    background_texture.loadFromFile("background.png");
    Sprite sBackground(background_texture);
    sf::Text text;
    sf::Font font;
    font.loadFromFile("LeanForeword-MR0x.ttf");
    // select the font
    text.setFont(font); // font is a sf::Font

    text.setPosition(100,100);

    // set the string to display
    text.setString("I AM SPEED!");

    // set the character size
    text.setCharacterSize(24+12+12+12+12); // in pixels, not points!

    // set the color
    text.setFillColor(sf::Color::Yellow);

    // set the text style
    text.setStyle(sf::Text::Bold);


    sf::Text text2;

    text2.setPosition(100,160+60);

    // set the string to display
    text2.setString("press s to start");

    // set the character size
    text2.setCharacterSize(24+12+12); // in pixels, not points!

    // set the color
    text2.setFillColor(sf::Color::Yellow);

    text2.setFont(font);

    // set the text style
    text2.setStyle(sf::Text::Bold);

    Event event;

    while (start_up_screen.isOpen())
    {
        while (start_up_screen.pollEvent(event))
        {

            if (event.type == Event::Closed)
                start_up_screen.close();
        }
        if (Keyboard::isKeyPressed(Keyboard::S)){
            main_game();
        
        }
        start_up_screen.clear();
        start_up_screen.draw(sBackground);
        start_up_screen.draw(text2);
        start_up_screen.draw(text);
        start_up_screen.display();
    //main_game();
    }
    return 0;   
}
// if you want code and assets tell me