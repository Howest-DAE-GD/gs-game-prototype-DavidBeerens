#include "pch.h"
#include "Game.h"
#include "utils.h"
#include <SVGParser.h>

#include <iostream>
//#include <opencv2/opencv.hpp>


float playerRad{ 15 };
Point2f playerPos{ 1500, 436 };
float enemyRad{ 32 };
Point2f enemyPos1{ 100, 100 };
Point2f enemyPos2{100, 780};
Point2f enemyPos3{1360, 100};
Point2f enemyPos4{1360, 780};
Point2f enemyPos5{600, 420};

float playerSpeed{ 1.f };

Game::Game( const Window& window ) 
	:BaseGame{ window }
{

	Initialize();
}

Game::~Game( )
{
	Cleanup( );
}

void Game::Initialize( )
{
	SVGParser::GetVerticesFromSvgFile("map.svg", svg);



	//// Read the PNG file
	//Mat image = imread("map.png", IMREAD_COLOR);

	//if (image.empty()) {
	//	std::cerr << "Error: Unable to read image file" << std::endl;
	//}

	//// Define the position (x, y) you want to check
	//int x = 100;
	//int y = 50;

	//// Get the color at the specified position
	//Color4f color = Map.at<color4f>(y, x);

	//// Print the color values
	//std::cout << "Color at position (" << x << ", " << y << "): ";
	//std::cout << "B: " << static_cast<int>(color[0]) << " ";
	//std::cout << "G: " << static_cast<int>(color[1]) << " ";
	//std::cout << "R: " << static_cast<int>(color[2]) << std::endl;
}

void Game::Cleanup( )
{
}

void Game::Update( float elapsedSec )
{

	for (int i = 0; i < svg.size(); i++)
	{
		for (int j = 0; j < (svg[i].size()-1); j++)
		{
			
		}
	}

	 //Check keyboard state
	const Uint8 *pStates = SDL_GetKeyboardState( nullptr );
	if ( pStates[SDL_SCANCODE_RIGHT] )
	{
		playerPos.x += playerSpeed;
	}
	if (pStates[SDL_SCANCODE_LEFT])
	{
		playerPos.x -= playerSpeed;
	}
	if (pStates[SDL_SCANCODE_UP])
	{
		playerPos.y += playerSpeed;
	}
	if (pStates[SDL_SCANCODE_DOWN])
	{
		playerPos.y -= playerSpeed;
	}

}

void Game::Draw( ) const
{
	ClearBackground( );

	Map.Draw(Point2f(0, 0), Rectf(0, 0, 1550, 872));

	utils::SetColor(Color4f(1, 0, 0, 0.8f));
	utils::FillEllipse(playerPos, playerRad, playerRad);

	utils::SetColor(Color4f(0, 1, 0, 0.8f));
	utils::FillEllipse(enemyPos1, enemyRad, enemyRad);
	utils::FillEllipse(enemyPos2, enemyRad, enemyRad);
	utils::FillEllipse(enemyPos3, enemyRad, enemyRad);
	utils::FillEllipse(enemyPos4, enemyRad, enemyRad);
	utils::FillEllipse(enemyPos5, enemyRad, enemyRad);
}

void Game::ProcessKeyDownEvent( const SDL_KeyboardEvent & e )
{
	//std::cout << "KEYDOWN event: " << e.keysym.sym << std::endl;
}

void Game::ProcessKeyUpEvent( const SDL_KeyboardEvent& e )
{
	//std::cout << "KEYUP event: " << e.keysym.sym << std::endl;
	//switch ( e.keysym.sym )
	//{
	//case SDLK_LEFT:
	//	//std::cout << "Left arrow key released\n";
	//	break;
	//case SDLK_RIGHT:
	//	//std::cout << "`Right arrow key released\n";
	//	break;
	//case SDLK_1:
	//case SDLK_KP_1:
	//	//std::cout << "Key 1 released\n";
	//	break;
	//}
}

void Game::ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e )
{
	//std::cout << "MOUSEMOTION event: " << e.x << ", " << e.y << std::endl;
}

void Game::ProcessMouseDownEvent( const SDL_MouseButtonEvent& e )
{
	//std::cout << "MOUSEBUTTONDOWN event: ";
	//switch ( e.button )
	//{
	//case SDL_BUTTON_LEFT:
	//	std::cout << " left button " << std::endl;
	//	break;
	//case SDL_BUTTON_RIGHT:
	//	std::cout << " right button " << std::endl;
	//	break;
	//case SDL_BUTTON_MIDDLE:
	//	std::cout << " middle button " << std::endl;
	//	break;
	//}
	
}

void Game::ProcessMouseUpEvent( const SDL_MouseButtonEvent& e )
{
	//std::cout << "MOUSEBUTTONUP event: ";
	//switch ( e.button )
	//{
	//case SDL_BUTTON_LEFT:
	//	std::cout << " left button " << std::endl;
	//	break;
	//case SDL_BUTTON_RIGHT:
	//	std::cout << " right button " << std::endl;
	//	break;
	//case SDL_BUTTON_MIDDLE:
	//	std::cout << " middle button " << std::endl;
	//	break;
	//}
}

void Game::ClearBackground( ) const
{
	glClearColor( 0.15f, 0.05f, 0.92f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT );
}
