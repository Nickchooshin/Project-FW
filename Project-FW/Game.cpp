#include "StdAfx.h"
#include "Game.h"

#include "Keyboard.h"
#include "Mouse.h"

Game::Game()
{
}
Game::~Game()
{
}

void Game::Initialize()
{
	Keyboard = new CKeyboard ;
	Keyboard->Initialize() ;

	Mouse = new CMouse ;
	Mouse->Initialize() ;
}

void Game::Terminate()
{
}

void Game::InputUpdate()
{
	Keyboard->Update() ;
	Keyboard->TakeBuffer() ;
}

void Game::Pulse()
{
	InputUpdate() ;
}

void Game::Render()
{
}