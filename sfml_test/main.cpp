//#include <SFML/Graphics.hpp>
//
//int main()
//{
//    // Create the main window
//    sf::RenderWindow app(sf::VideoMode(800, 600), "SFML window");
//
//    // Load a sprite to display
//    sf::Texture texture;
//    if (!texture.loadFromFile("cb.bmp"))
//        return EXIT_FAILURE;
//    sf::Sprite sprite(texture);
//
//	// Start the game loop
//    while (app.isOpen())
//    {
//        // Process events
//        sf::Event event;
//        while (app.pollEvent(event))
//        {
//            // Close window : exit
//            if (event.type == sf::Event::Closed)
//                app.close();
//        }
//
//        // Clear screen
//        app.clear();
//
//        // Draw the sprite
//        app.draw(sprite);
//
//        // Update the window
//        app.display();
//    }
//
//    return EXIT_SUCCESS;
//}


#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
using namespace sf;

#include "iostream"
#include <vector>
#include <list>
#include "level.hpp"
#include "anim.hpp"


class Entity
{
public:
	float x,y,dx,dy,w,h;
	AnimationManager anim;
	std::vector<Object> obj;
	bool life, dir;
	float timer, timer_end;
	String Name;
	int Health;

	Entity(AnimationManager &A,int X, int Y)
	{
		anim = A;
		x = X;
		y = Y;
		dir = 0;

		life=true;
		timer=0;
		timer_end=0;
		dx=dy=0;
	}

	virtual void update(float time) = 0;

	void draw(RenderWindow &window)
	{
		anim.draw(window,x,y+h);
	}

	FloatRect getRect()
	{
		return FloatRect(x,y,w,h);
	}

	void option(String NAME, float SPEED=0, int HEALTH=10, String FIRST_ANIM="")
	{
		Name = NAME;
		if (FIRST_ANIM!="") anim.set(FIRST_ANIM);
		w = anim.getW();
		h = anim.getH();
		dx = SPEED;
		Health = HEALTH;
	}

};

class Bullet:public Entity
{
public:

	Bullet(AnimationManager &a, Level &lev,int x,int y,bool dir):Entity(a,x,y)
	{
		option("Bullet", 0.3, 10, "move");

		if (dir) dx=-0.3;
   		obj = lev.GetObjects("solid");

	}

	void update(float time)
	{
		x+=dx*time;

		for (int i=0;i<obj.size();i++)
			if (getRect().intersects(obj[i].rect))
		        {Health=0;}

		if (Health<=0) {anim.set("explode");dx=0;
		                if (anim.isPlaying()==false) life=false;
		                }

		anim.tick(time);
	}

};

class PLAYER: public Entity
{
public:
	enum {stay,walk,duck,jump,climb,swim} STATE;
	bool onLadder, shoot, hit;
	std::map<std::string,bool> key;

	PLAYER(AnimationManager &a, Level &lev,int x,int y):Entity(a,x,y)
	{

		option("Player",0,100,"stay");
        STATE=stay; hit=0;
		obj = lev.GetAllObjects();
	}

	void KeyCheck()
	{
		if (key["L"])
		{
			dir=1;
			if (STATE!=duck) dx=-0.1;
			if (STATE==stay) STATE=walk;
		}

		if (key["R"])
		{
			dir=0;
			if (STATE!=duck) dx=0.1;
			if (STATE==stay) STATE=walk;
		}

		if (key["Up"])
		{
			if (onLadder) STATE=climb;
			//if (STATE==stay || STATE==walk) { dy=-0.27; STATE=jump; anim.play("jump");}
			if (STATE==stay || STATE==walk) { dy=-0.5; STATE=jump; anim.play("jump");}
			if (STATE==swim || STATE==climb) dy=-0.05;
		}

		if (key["Down"])
		{
			if (STATE==stay || STATE==walk) { STATE=duck; dx=0;}
			if (STATE==swim || STATE==climb) dy=0.05;
		}

		if (key["Space"])
		{
			shoot=true;
		}

		/////////////////////если клавиша отпущена///////////////////////////
		if (!(key["R"] || key["L"]))
		{
			dx=0;
			if (STATE==walk) STATE=stay;
		}

		if (!(key["Up"] || key["Down"]))
		{
			if (STATE==swim || STATE==climb) dy=0;
		}

		if (!key["Down"])
		{
			if (STATE==duck) { STATE=stay;}
		}

		if (!key["Space"])
		{
			shoot=false;
		}
	}

	void update(float time)
	{
		KeyCheck();

		if (STATE==stay) anim.set("stay");
		if (STATE==walk) anim.set("walk");
		if (STATE==jump) anim.set("jump");
		if (STATE==duck) anim.set("duck");
		if (STATE==climb) {anim.set("climb"); anim.pause(); if (dy!=0) anim.play(); if (!onLadder) STATE=stay;}

       if (shoot) { anim.set("shoot");
		         	if (STATE==walk) anim.set("shootAndWalk");}

		if (hit) { timer+=time;
			       if (timer>1000) {hit=false; timer=0;}
				   anim.set("hit");}

		if (dir) anim.flip();


		x += dx * time;
		Collision(0);

		if (STATE!=climb) dy+=0.0005*time;
		y += dy*time; onLadder=false;
		Collision(1);


		anim.tick(time);

		key["R"]=key["L"]=key["Up"]=key["Down"]=key["Space"]=false;
	}

	void Collision(int num)
	{

		for (int i=0;i<obj.size();i++)
			if (getRect().intersects(obj[i].rect))
			{
				if (obj[i].name=="solid")
				{
					if (dy>0 && num==1)	{ y = obj[i].rect.top -  h;  dy=0;   STATE=stay;}
					if (dy<0 && num==1)	{ y = obj[i].rect.top + obj[i].rect.height ;   dy=0;}
					if (dx>0 && num==0)	{ x =  obj[i].rect.left -  w; }
					if (dx<0 && num==0)	{ x =  obj[i].rect.left + obj[i].rect.width ;}
				}

				if (obj[i].name=="ladder")	{ onLadder=true; }

				if (obj[i].name=="SlopeLeft")
				{  FloatRect r = obj[i].rect;
				   int y0 = (x+w/2-r.left) * r.height/r.width+ r.top - h;
				   if (y>y0)
					  if (x+w/2>r.left)
					   {y =  y0; dy=0; STATE=stay;}
				}

				if (obj[i].name=="SlopeRight")
				{   FloatRect r = obj[i].rect;
					int y0 = - (x+w/2-r.left) * r.height/r.width + r.top+r.height - h;
					if (y > y0)
					  if (x+w/2<r.left+r.width)
					   {y = y0 ; dy=0; STATE=stay;}
				}

			}
	}

};

class ENEMY: public Entity
{
public:

	ENEMY(AnimationManager &a, Level &lev,int x,int y):Entity(a,x,y)
	{
		option("Enemy", 0.01, 15, "move");
	}

	void update(float time)
	{
		x += dx * time;
		timer+=time;
		if (timer>3200) {dx*=-1;timer=0;}

		if (Health<=0) {anim.set("dead"); dx=0;
			           timer_end+=time;
		               if (timer_end>4000) life=false;
		              }

		anim.tick(time);
	}
};

class MovingPlatform: public Entity
{
public:
	MovingPlatform(AnimationManager &a, Level &lev,int x,int y):Entity(a,x,y)
	{
		option("MovingPlatform", 0.05, 0, "move");
	}

	void update(float time)
	{
		x += dx * time;
		timer+=time;
		if (timer>6000) {dx*=-1;timer=0;}
		anim.tick(time);
	}

};

class PlayerScores
{
public:
	Texture t;
	Sprite s;
	int max;
	RectangleShape bar;

	PlayerScores()
	{
		t.loadFromFile("files/megaman_bullets.png");
		s.setTexture(t);
		s.setTextureRect( IntRect(783,2,15,84) );

		bar.setFillColor(Color(0,0,0));
		max = 100;
	}

	void update(int k)

	{
		if (k>0)
			if (k<max)
        		bar.setSize( Vector2f(10, (max-k)*70/max));

	}

   	void draw(RenderWindow &window)
	{
		Vector2f center = window.getView().getCenter();
		Vector2f size = window.getView().getSize();

		s.setPosition(   center.x - size.x/2 + 10, center.y - size.y/2 + 10);
	    bar.setPosition( center.x - size.x/2 + 14, center.y - size.y/2 + 14);

		window.draw(s);
		window.draw(bar);
	}

};

int main()
{
	///////////// инициализация ///////////////////////////
	RenderWindow window(VideoMode(800, 640), "SFML works!");

	View view( FloatRect(0, 0, 800, 640) );

	Level lvl;
	lvl.LoadFromFile("plat_test.tmx");
	//lvl.LoadFromFile("Level_megaman.tmx");


	Texture tileSet, moveplatform, megaman, fang;
	tileSet.loadFromFile("files/Mario_Tileset.png");
	moveplatform.loadFromFile("files/movingPlatform.png");
	megaman.loadFromFile("files/megaman.png");
	//megaman.loadFromFile("files/cyclops.png");
	fang.loadFromFile("files/fanq.png");


	AnimationManager anim;
	anim.loadFromXML("files/megaman_anim.xml",megaman);
	//anim.loadFromXML("files/cyclop_anim.xml",megaman);
	anim.animList["jump"].loop = 0;

	AnimationManager anim2;
	anim2.create("move",fang,247,582,8,8,1,0);
	anim2.create("explode",fang,323,583,18,18,4,0.01,29,false);

	AnimationManager anim3;
	anim3.create("move",tileSet,0,0,16,16,2,0.002,18);
	anim3.create("dead",tileSet,58,0,16,16,1,0);

	AnimationManager anim4;
	anim4.create("move",moveplatform,0,0,95,22,1,0);


	std::list<Entity*>  entities;
	std::list<Entity*>::iterator it;

	std::vector<Object> e = lvl.GetObjects("enemy");
	for (int i=0;i < e.size();i++)
		entities.push_back(new ENEMY(anim3, lvl, e[i].rect.left, e[i].rect.top) );

	e = lvl.GetObjects("MovingPlatform");
	for (int i=0;i < e.size();i++)
		entities.push_back(new MovingPlatform(anim4, lvl, e[i].rect.left, e[i].rect.top) );

	Object pl = lvl.GetObject("player");
	PLAYER Mario(anim, lvl, pl.rect.left, pl.rect.top);

	PlayerScores plScores;

	Music music;
	music.openFromFile("files/Mario_Theme.ogg");
	music.play();
	music.setLoop(true);

	Clock clock;

	/////////////////// основной цикл  /////////////////////
	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();

		time = time/500;  // здесь регулируем скорость игры

		if (time > 40) time = 40;

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();

			if (event.type == Event::KeyPressed)
				if (event.key.code==Keyboard::Space)
		        	entities.push_back(new Bullet(anim2,lvl,Mario.x+18,Mario.y+18,Mario.dir) );
		}


		if (Keyboard::isKeyPressed(Keyboard::Left)) Mario.key["L"]=true;
		if (Keyboard::isKeyPressed(Keyboard::Right)) Mario.key["R"]=true;
		if (Keyboard::isKeyPressed(Keyboard::Up)) Mario.key["Up"]=true;
		if (Keyboard::isKeyPressed(Keyboard::Down)) Mario.key["Down"]=true;
		if (Keyboard::isKeyPressed(Keyboard::Space)) Mario.key["Space"]=true;


		for(it=entities.begin();it!=entities.end();)
		{
			Entity *b = *it;
			b->update(time);
			if (b->life==false)	{ it  = entities.erase(it); delete b;}
			else it++;
		}


		Mario.update(time);
		plScores.update(Mario.Health);


		for(it=entities.begin();it!=entities.end();it++)
		{
			//1. враги
			if ((*it)->Name=="Enemy")
			{
				Entity *enemy = *it;

				if (enemy->Health<=0) continue;

				if  (Mario.getRect().intersects( enemy->getRect() ))
				    if (Mario.dy>0) { enemy->dx=0; Mario.dy=-0.2; enemy->Health=0;}
				    else if (!Mario.hit) { Mario.Health-=5; Mario.hit=true;
				                         if (Mario.dir) Mario.x+=10; else Mario.x-=10;}


				for (std::list<Entity*>::iterator it2=entities.begin(); it2!=entities.end(); it2++)
				{
					Entity *bullet = *it2;
					if (bullet->Name=="Bullet")
						if ( bullet->Health>0)
							if  (bullet->getRect().intersects( enemy->getRect() ) )
							 { bullet->Health=0; enemy->Health-=5;}
				}
			}

			//2. движущиеся платформы
			if ((*it)->Name=="MovingPlatform")
			{
			    Entity *movPlat = *it;
				if  (Mario.getRect().intersects( movPlat->getRect() ) )
				   if (Mario.dy>0)
					  if (Mario.y+Mario.h<movPlat->y+movPlat->h)
					  {Mario.y=movPlat->y - Mario.h + 3; Mario.x+=movPlat->dx*time; Mario.dy=0; Mario.STATE=PLAYER::stay;}
			}

			//3.. и т.д.
		}


		/////////////////////отображаем на экран/////////////////////

		view.setCenter( Mario.x,Mario.y);
		window.setView(view);

		window.clear(Color(107,140,255));

		lvl.Draw(window);

		for(it=entities.begin();it!=entities.end();it++)
			(*it)->draw(window);

		Mario.draw(window);
		plScores.draw(window);

		window.display();
	}

	return 0;
}




