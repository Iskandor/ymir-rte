/* 
 * File:   CGuiManager.cpp
 * Author: Matej Pechac
 * 
 * Created on June 7, 2014, 4:29 PM
 */

#include "CGuiManager.h"

CGuiManager::CGuiManager(SDL_Surface* surface, CFontRender* font_render) {
  screen = surface;
  this->font_render = font_render;
}

CGuiManager::CGuiManager(const CGuiManager& orig) {
  screen = orig.screen;
  font_render = orig.font_render;
}

CGuiManager::~CGuiManager() {
	delete lbv_unit_class;
  delete lbv_race;
  delete lb_hp;
  delete lbv_hp;
  delete lb_st;
  delete lbv_st;
  
	delete font;
	delete top;
	delete gui;

	delete input;
	delete graphics;
	delete imageLoader;  
}

int CGuiManager::OnInit() {
	imageLoader = new SDLImageLoader();
	Image::setImageLoader(imageLoader);
	graphics = new SDLGraphics();
	graphics->setTarget(screen);
	input = new SDLInput();
  
	top = new Container();
	top->setDimension(Rectangle(0, RESOLUTION_H-13*MAP_ELEM, RESOLUTION_W, 13*MAP_ELEM));
  top->setOpaque(false);
  
	gui = new Gui();
	gui->setGraphics(graphics);
	gui->setInput(input);
	gui->setTop(top);
  
	font = new ImageFont("data/image/rpgfont.png", " abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.,!?-+/():;");
	gcn::Widget::setGlobalFont(font);
  
  lb_hp = new gcn::Label("Hit Points");
  lb_st = new gcn::Label("Stamina");
	lbv_unit_class = new gcn::Label("");
  lbv_race = new gcn::Label("");
  lbv_hp = new gcn::Label("");
  lbv_st = new gcn::Label("");
  
	top->add(lbv_unit_class);
  top->add(lbv_race);
  top->add(lb_hp);
  top->add(lbv_hp);
  top->add(lb_st);
  top->add(lbv_st);
  
  lbv_unit_class->setPosition(10, 0*FONT_HEIGHT);
  lbv_race->setPosition(10, 1*FONT_HEIGHT);
  lb_hp->setPosition(10, 2*FONT_HEIGHT);
  lb_st->setPosition(10, 3*FONT_HEIGHT);
  lbv_hp->setPosition(140, 2*FONT_HEIGHT);
  lbv_st->setPosition(140, 3*FONT_HEIGHT);
  
  return 0;
}

void CGuiManager::OnLoop() {
  gui->logic();
}

void CGuiManager::OnRender() {
  gui->draw();
}

void CGuiManager::OnEvent(SDL_Event event) {
  input->pushInput(event);
}

void CGuiManager::OnUnitClick(CUnitEntity* unit_entity) {
  if (unit_entity == NULL) {
    lbv_unit_class->setCaption("");
    lbv_unit_class->adjustSize();
    lbv_race->setCaption("");
    lbv_race->adjustSize();
    lbv_hp->setCaption("");
    lbv_hp->adjustSize();
    lbv_st->setCaption("");
    lbv_st->adjustSize();
  }
  else {
    lbv_unit_class->setCaption(unit_entity->GetRootUnit()->getClass());
    lbv_unit_class->adjustSize();
    lbv_race->setCaption(unit_entity->GetRootUnit()->getRace());
    lbv_race->adjustSize();
    lbv_hp->setCaption(to_string(unit_entity->GetHP()) + "/" + to_string(unit_entity->GetMaxHP()));
    lbv_hp->adjustSize();
    lbv_st->setCaption(to_string((int)unit_entity->GetSP()) + "/" + to_string((int)unit_entity->GetMaxSP()));
    lbv_st->adjustSize();
  }
}