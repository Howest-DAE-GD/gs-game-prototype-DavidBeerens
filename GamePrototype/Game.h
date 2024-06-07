#pragma once
#include "BaseGame.h"
#include "Texture.h"
#include "SoundEffect.h"

class Game : public BaseGame
{
public:
	explicit Game( const Window& window );
	Game(const Game& other) = delete;
	Game& operator=(const Game& other) = delete;
	Game( Game&& other) = delete;
	Game& operator=(Game&& other) = delete;
	// http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Rh-override
	~Game();

	void Update( float elapsedSec ) override;
	void Draw( ) const override;


	void getVector(Point2f& vector, Point2f& bools, Point2f enemyPos);


	// Event handling
	void ProcessKeyDownEvent( const SDL_KeyboardEvent& e ) override;
	void ProcessKeyUpEvent( const SDL_KeyboardEvent& e ) override;
	void ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e ) override;
	void ProcessMouseDownEvent( const SDL_MouseButtonEvent& e ) override;
	void ProcessMouseUpEvent( const SDL_MouseButtonEvent& e ) override;



private:

	// FUNCTIONS
	void Initialize();
	void Cleanup( );
	void ClearBackground( ) const;

	Texture Map = Texture{ "map.png" };
	Texture Player = Texture{ "player.png" };
	Texture Drone = Texture{ "drone.png" };
	Texture Coin = Texture{ "coin.png" };
	Texture NotCoin = Texture{ "notcoin.png" };
	Texture Van = Texture{ "van.png" };
	Texture Start = Texture{ "startScreen.png" };
	SoundEffect* coinSound{ new SoundEffect{ "coin.mp3" } };
};