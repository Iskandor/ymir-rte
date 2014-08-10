/* 
 * File:   CGuiManager.cpp
 * Author: Matej Pechac
 * 
 * Created on June 7, 2014, 4:29 PM
 */

#include "CGuiManager.h"

CGuiManager::CGuiManager(SDL_Surface* surface) {
  screen = surface;
}

CGuiManager::CGuiManager(const CGuiManager& orig) {
  screen = orig.screen;
}

CGuiManager::~CGuiManager() {
  /*
	delete label;
	delete font;
	delete top;
	delete gui;

	delete input;
	delete graphics;
	delete imageLoader;  
   * */
}

int CGuiManager::OnInit() {
  /*
	imageLoader = new SDLImageLoader();
	Image::setImageLoader(imageLoader);
	graphics = new SDLGraphics();
	graphics->setTarget(screen);
  
	input = new SDLInput();
	top = new Container();
	top->setDimension(Rectangle(100, 100, 240, 240));
  top->setOpaque(false);
	gui = new Gui();
	gui->setGraphics(graphics);
	gui->setInput(input);
	gui->setTop(top);
	font = new ImageFont("data/image/rpgfont.png", " abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789");
	gcn::Widget::setGlobalFont(font);

	label = new gcn::Label("Hello World");
	label->setPosition(10, 10);
	top->add(label);  */
  
  return 0;
}

void CGuiManager::OnRender() {
  //gui->draw();
}
