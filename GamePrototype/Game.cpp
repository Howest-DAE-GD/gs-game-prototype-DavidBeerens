#include "pch.h"
#include "Game.h"
#include "utils.h"

#include <iostream>


//player variables
float playerRad{ 15 };
Point2f playerPos{ 1500, 436 };

//enemy variables
float enemyRad{ 32 };
Point2f enemyPos1{ 100, 100 };
Point2f enemyVector1{};
Point2f enemyBool1{};

Point2f enemyPos2{100, 780};
Point2f enemyVector2{};
Point2f enemyBool2{};

Point2f enemyPos3{1360, 100};
Point2f enemyVector3{};
Point2f enemyBool3{};

Point2f enemyPos4{1360, 780};
Point2f enemyVector4{};
Point2f enemyBool4{};

Point2f enemyPos5{600, 420};
Point2f enemyVector5{};
Point2f enemyBool5{};

//coin variables
Point2f coinsPos[5]{Point2f(275, 110), Point2f(40, 800), Point2f(972, 176), Point2f(1235, 650), Point2f(485, 635)};
float coinRad{ 40 };
bool coinsCollected[5]{};
float coinCollectedTimer{ 3 };
//uncollected coins
Point2f notCoinsPos[5]{};

//speed
float playerSpeed{ 2.f }; //too slow speed was 1.f
float boostSpeed{ 2.9f };
float enemySpeed{ 0.3f };
float boostTimer{};
int boosts{0};

//timer
Point2f timerBounds1{3, 5};
Point2f timerBounds2{ 2, 3 };
float timer1{};
float timer2{};
float timer3{};
float timer4{};
float timer5{};

//status variables
int totalCoins{ 0 };
bool loser{ 0 };
bool start{ true };

//van
Point2f vanPos{1470, 380};
bool newLevel{ true };


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
	//get starting vectors for the enemies
	getVector(enemyVector1, enemyBool1, enemyPos1);
	getVector(enemyVector2, enemyBool2, enemyPos2);
	getVector(enemyVector3, enemyBool3, enemyPos3);
	getVector(enemyVector4, enemyBool4, enemyPos4);
	getVector(enemyVector5, enemyBool5, enemyPos5);

	coinSound->SetVolume(MIX_MAX_VOLUME / 5);
}

void Game::Cleanup( )
{
}

void Game::Update( float elapsedSec )
{

	//move enemies
#pragma region movingEnemies
	enemyBool1.x == 0 ? enemyPos1.x -= enemyVector1.x * enemySpeed : enemyPos1.x += enemyVector1.x * enemySpeed;
	enemyBool1.y == 0 ? enemyPos1.y -= enemyVector1.y * enemySpeed : enemyPos1.y += enemyVector1.y * enemySpeed;

	enemyBool2.x == 0 ? enemyPos2.x -= enemyVector2.x * enemySpeed : enemyPos2.x += enemyVector2.x * enemySpeed;
	enemyBool2.y == 0 ? enemyPos2.y -= enemyVector2.y * enemySpeed : enemyPos2.y += enemyVector2.y * enemySpeed;

	enemyBool3.x == 0 ? enemyPos3.x -= enemyVector3.x * enemySpeed : enemyPos3.x += enemyVector3.x * enemySpeed;
	enemyBool3.y == 0 ? enemyPos3.y -= enemyVector3.y * enemySpeed : enemyPos3.y += enemyVector3.y * enemySpeed;

	enemyBool4.x == 0 ? enemyPos4.x -= enemyVector4.x * enemySpeed : enemyPos4.x += enemyVector4.x * enemySpeed;
	enemyBool4.y == 0 ? enemyPos4.y -= enemyVector4.y * enemySpeed : enemyPos4.y += enemyVector4.y * enemySpeed;

	enemyBool5.x == 0 ? enemyPos5.x -= enemyVector5.x * enemySpeed : enemyPos5.x += enemyVector5.x * enemySpeed;
	enemyBool5.y == 0 ? enemyPos5.y -= enemyVector5.y * enemySpeed : enemyPos5.y += enemyVector5.y * enemySpeed;
#pragma endregion

	 //Check keyboard state
	const Uint8 *pStates = SDL_GetKeyboardState( nullptr );
#pragma region exitBoostResetStart
	//press escape to exit game
	if (pStates[SDL_SCANCODE_ESCAPE])	{exit(EXIT_SUCCESS);}

	//press space for boost
	boostTimer += elapsedSec;
	if (pStates[SDL_SCANCODE_SPACE])
	{
		if (boosts > 0 && playerSpeed != boostSpeed)
		{
			boostTimer = 0;
			playerSpeed = boostSpeed;
			
		}	
	}
	if (boostTimer >= 4 && playerSpeed == boostSpeed)
	{
		playerSpeed = 2.f;
		--boosts;
	}

	//press r to reset
	if (pStates [SDL_SCANCODE_R])
	{
		playerPos = Point2f(1500, 436);

		enemyPos1 = Point2f(100, 100);
		enemyPos2 = Point2f(100, 780);
		enemyPos3 = Point2f(1360, 100);
		enemyPos4 = Point2f(1360, 780);
		enemyPos5 = Point2f(600, 420);

		coinsPos[0] = Point2f(275, 110);
		coinsPos[1] = Point2f(40, 800);
		coinsPos[2] = Point2f(972, 176);
		coinsPos[3] = Point2f(1235, 650);
		coinsPos[4] = Point2f(485, 635);

		coinsCollected[0] = 0;
		coinsCollected[1] = 0;
		coinsCollected[2] = 0;
		coinsCollected[3] = 0;
		coinsCollected[4] = 0;

		totalCoins = 0;
		boosts = 0;
	}

	//press enter to start
	if (pStates[SDL_SCANCODE_S])
	{
		start = false;
	}
#pragma endregion
#pragma region right
	if ( pStates[SDL_SCANCODE_RIGHT] )
	{
		if (playerPos.x - playerRad >= 21 && playerPos.x + playerRad <= 1430 && playerPos.y - playerRad >= 21 && playerPos.y + playerRad <= 851 ||
			playerPos.x + playerRad >= 1429 && playerPos.x - playerRad <= 1497 && playerPos.y - playerRad >= 403 && playerPos.y + playerRad <= 471)
		{
			if (playerPos.x + playerRad >= 145 && playerPos.x - playerRad <= 309 && playerPos.y + playerRad >= 725 && playerPos.y - playerRad <= 742 ||
				playerPos.x + playerRad >= 117 && playerPos.x - playerRad <= 137 && playerPos.y + playerRad >= 370 && playerPos.y - playerRad <= 629 ||
				playerPos.x + playerRad >= 209 && playerPos.x - playerRad <= 258 && playerPos.y + playerRad >= 389 && playerPos.y - playerRad <= 407 ||
				playerPos.x + playerRad >= 656 && playerPos.x - playerRad <= 675 && playerPos.y + playerRad >= 797 && playerPos.y - playerRad <= 851 ||
				playerPos.x + playerRad >= 425 && playerPos.x - playerRad <= 537 && playerPos.y + playerRad >= 271 && playerPos.y - playerRad <= 369 ||
				playerPos.x + playerRad >= 694 && playerPos.x - playerRad <= 713 && playerPos.y + playerRad >= 21 && playerPos.y - playerRad <= 88 ||
				playerPos.x + playerRad >= 731 && playerPos.x - playerRad <= 818 && playerPos.y + playerRad >= 264 && playerPos.y - playerRad <= 282 ||
				playerPos.x + playerRad >= 1336 && playerPos.x - playerRad <= 1433 && playerPos.y + playerRad >= 197 && playerPos.y - playerRad <= 214 ||
				playerPos.x + playerRad >= 91 && playerPos.x - playerRad <= 349 && playerPos.y + playerRad >= 161 && playerPos.y - playerRad <= 168 ||
				playerPos.x + playerRad >= 174 && playerPos.x - playerRad <= 194 && playerPos.y + playerRad >= 163 && playerPos.y - playerRad <= 292 ||
				playerPos.x + playerRad >= 655 && playerPos.x - playerRad <= 1139 && playerPos.y + playerRad >= 384 && playerPos.y - playerRad <= 400 ||
				playerPos.x + playerRad >= 330 && playerPos.x - playerRad <= 349 && playerPos.y + playerRad >= 97 && playerPos.y - playerRad <= 176 ||
				playerPos.x + playerRad >= 490 && playerPos.x - playerRad <= 836 && playerPos.y + playerRad >= 154 && playerPos.y - playerRad <= 171 ||
				playerPos.x + playerRad >= 526 && playerPos.x - playerRad <= 545 && playerPos.y + playerRad >= 117 && playerPos.y - playerRad <= 169 ||
				playerPos.x + playerRad >= 629 && playerPos.x - playerRad <= 649 && playerPos.y + playerRad >= 156 && playerPos.y - playerRad <= 304 ||
				playerPos.x + playerRad >= 899 && playerPos.x - playerRad <= 1240 && playerPos.y + playerRad >= 117 && playerPos.y - playerRad <= 134 ||
				playerPos.x + playerRad >= 899 && playerPos.x - playerRad <= 918 && playerPos.y + playerRad >= 117 && playerPos.y - playerRad <= 262 ||
				playerPos.x + playerRad >= 899 && playerPos.x - playerRad <= 1240 && playerPos.y + playerRad >= 245 && playerPos.y - playerRad <= 262 ||
				playerPos.x + playerRad >= 1220 && playerPos.x - playerRad <= 1240 && playerPos.y + playerRad >= 245 && playerPos.y - playerRad <= 403 ||
				playerPos.x + playerRad >= 1220 && playerPos.x - playerRad <= 1433 && playerPos.y + playerRad >= 386 && playerPos.y - playerRad <= 403 ||
				playerPos.x + playerRad >= 754 && playerPos.x - playerRad <= 971 && playerPos.y + playerRad >= 540 && playerPos.y - playerRad <= 556 ||
				playerPos.x + playerRad >= 754 && playerPos.x - playerRad <= 773 && playerPos.y + playerRad >= 540 && playerPos.y - playerRad <= 612 ||
				playerPos.x + playerRad >= 853 && playerPos.x - playerRad <= 872 && playerPos.y + playerRad >= 468 && playerPos.y - playerRad <= 556 ||
				playerPos.x + playerRad >= 1026 && playerPos.x - playerRad <= 1046 && playerPos.y + playerRad >= 471 && playerPos.y - playerRad <= 723 ||
				playerPos.x + playerRad >= 1026 && playerPos.x - playerRad <= 1433 && playerPos.y + playerRad >= 471 && playerPos.y - playerRad <= 487 ||
				playerPos.x + playerRad >= 1026 && playerPos.x - playerRad <= 1319 && playerPos.y + playerRad >= 706 && playerPos.y - playerRad <= 723 ||
				playerPos.x + playerRad >= 1299 && playerPos.x - playerRad <= 1319 && playerPos.y + playerRad >= 593 && playerPos.y - playerRad <= 723 ||
				playerPos.x + playerRad >= 1127 && playerPos.x - playerRad <= 1319 && playerPos.y + playerRad >= 593 && playerPos.y - playerRad <= 610 ||
				playerPos.x + playerRad >= 433 && playerPos.x - playerRad <= 568 && playerPos.y + playerRad >= 691 && playerPos.y - playerRad <= 708 ||
				playerPos.x + playerRad >= 549 && playerPos.x - playerRad <= 568 && playerPos.y + playerRad >= 550 && playerPos.y - playerRad <= 708 ||
				playerPos.x + playerRad >= 455 && playerPos.x - playerRad <= 475 && playerPos.y + playerRad >= 691 && playerPos.y - playerRad <= 773 ||
				playerPos.x + playerRad >= 275 && playerPos.x - playerRad <= 452 && playerPos.y + playerRad >= 576 && playerPos.y - playerRad <= 593 ||
				playerPos.x + playerRad >= 433 && playerPos.x - playerRad <= 452 && playerPos.y + playerRad >= 576 && playerPos.y - playerRad <= 708 ||
				playerPos.x + playerRad >= 321 && playerPos.x - playerRad <= 341 && playerPos.y + playerRad >= 326 && playerPos.y - playerRad <= 496 ||
				playerPos.x + playerRad >= 275 && playerPos.x - playerRad <= 675 && playerPos.y + playerRad >= 477 && playerPos.y - playerRad <= 496 ||
				playerPos.x + playerRad >= 656 && playerPos.x - playerRad <= 675 && playerPos.y + playerRad >= 477 && playerPos.y - playerRad <= 708 ||
				playerPos.x + playerRad >= 656 && playerPos.x - playerRad <= 872 && playerPos.y + playerRad >= 691 && playerPos.y - playerRad <= 708 ||
				playerPos.x + playerRad >= 853 && playerPos.x - playerRad <= 872 && playerPos.y + playerRad >= 691 && playerPos.y - playerRad <= 773)
			{
			}
			else
			{
				playerPos.x += playerSpeed;
			}
		}
	}
#pragma endregion
#pragma region left
	if (pStates[SDL_SCANCODE_LEFT])
	{
		if (playerPos.x - playerRad >= 24 && playerPos.x + playerRad <= 1433 && playerPos.y - playerRad >= 21 && playerPos.y + playerRad <= 851 ||
			playerPos.x + playerRad >= 1429 && playerPos.x - playerRad <= 1500 && playerPos.y - playerRad >= 403 && playerPos.y + playerRad <= 471)
		{
			if (playerPos.x + playerRad >= 148 && playerPos.x - playerRad <= 312 && playerPos.y + playerRad >= 725 && playerPos.y - playerRad <= 742 ||
				playerPos.x + playerRad >= 120 && playerPos.x - playerRad <= 140 && playerPos.y + playerRad >= 370 && playerPos.y - playerRad <= 629 ||
				playerPos.x + playerRad >= 212 && playerPos.x - playerRad <= 261 && playerPos.y + playerRad >= 389 && playerPos.y - playerRad <= 407 ||
				playerPos.x + playerRad >= 659 && playerPos.x - playerRad <= 678 && playerPos.y + playerRad >= 797 && playerPos.y - playerRad <= 851 ||
				playerPos.x + playerRad >= 428 && playerPos.x - playerRad <= 540 && playerPos.y + playerRad >= 271 && playerPos.y - playerRad <= 369 ||
				playerPos.x + playerRad >= 697 && playerPos.x - playerRad <= 716 && playerPos.y + playerRad >= 21 && playerPos.y - playerRad <= 88 ||
				playerPos.x + playerRad >= 734 && playerPos.x - playerRad <= 821 && playerPos.y + playerRad >= 264 && playerPos.y - playerRad <= 282 ||
				playerPos.x + playerRad >= 1339 && playerPos.x - playerRad <= 1436 && playerPos.y + playerRad >= 197 && playerPos.y - playerRad <= 214 ||
				playerPos.x + playerRad >= 94 && playerPos.x - playerRad <= 352 && playerPos.y + playerRad >= 161 && playerPos.y - playerRad <= 168 ||
				playerPos.x + playerRad >= 177 && playerPos.x - playerRad <= 197 && playerPos.y + playerRad >= 163 && playerPos.y - playerRad <= 292 ||
				playerPos.x + playerRad >= 658 && playerPos.x - playerRad <= 1142 && playerPos.y + playerRad >= 384 && playerPos.y - playerRad <= 400 ||
				playerPos.x + playerRad >= 333 && playerPos.x - playerRad <= 352 && playerPos.y + playerRad >= 97 && playerPos.y - playerRad <= 176 ||
				playerPos.x + playerRad >= 493 && playerPos.x - playerRad <= 839 && playerPos.y + playerRad >= 154 && playerPos.y - playerRad <= 171 ||
				playerPos.x + playerRad >= 529 && playerPos.x - playerRad <= 548 && playerPos.y + playerRad >= 117 && playerPos.y - playerRad <= 169 ||
				playerPos.x + playerRad >= 632 && playerPos.x - playerRad <= 652 && playerPos.y + playerRad >= 156 && playerPos.y - playerRad <= 304 ||
				playerPos.x + playerRad >= 902 && playerPos.x - playerRad <= 1243 && playerPos.y + playerRad >= 117 && playerPos.y - playerRad <= 134 ||
				playerPos.x + playerRad >= 902 && playerPos.x - playerRad <= 921 && playerPos.y + playerRad >= 117 && playerPos.y - playerRad <= 262 ||
				playerPos.x + playerRad >= 902 && playerPos.x - playerRad <= 1243 && playerPos.y + playerRad >= 245 && playerPos.y - playerRad <= 262 ||
				playerPos.x + playerRad >= 1223 && playerPos.x - playerRad <= 1243 && playerPos.y + playerRad >= 245 && playerPos.y - playerRad <= 403 ||
				playerPos.x + playerRad >= 1223 && playerPos.x - playerRad <= 1436 && playerPos.y + playerRad >= 386 && playerPos.y - playerRad <= 403 ||
				playerPos.x + playerRad >= 757 && playerPos.x - playerRad <= 974 && playerPos.y + playerRad >= 540 && playerPos.y - playerRad <= 556 ||
				playerPos.x + playerRad >= 757 && playerPos.x - playerRad <= 776 && playerPos.y + playerRad >= 540 && playerPos.y - playerRad <= 612 ||
				playerPos.x + playerRad >= 856 && playerPos.x - playerRad <= 875 && playerPos.y + playerRad >= 468 && playerPos.y - playerRad <= 556 ||
				playerPos.x + playerRad >= 1029 && playerPos.x - playerRad <= 1049 && playerPos.y + playerRad >= 471 && playerPos.y - playerRad <= 723 ||
				playerPos.x + playerRad >= 1029 && playerPos.x - playerRad <= 1436 && playerPos.y + playerRad >= 471 && playerPos.y - playerRad <= 487 ||
				playerPos.x + playerRad >= 1029 && playerPos.x - playerRad <= 1322 && playerPos.y + playerRad >= 706 && playerPos.y - playerRad <= 723 ||
				playerPos.x + playerRad >= 1302 && playerPos.x - playerRad <= 1322 && playerPos.y + playerRad >= 593 && playerPos.y - playerRad <= 723 ||
				playerPos.x + playerRad >= 1130 && playerPos.x - playerRad <= 1322 && playerPos.y + playerRad >= 593 && playerPos.y - playerRad <= 610 ||
				playerPos.x + playerRad >= 436 && playerPos.x - playerRad <= 571 && playerPos.y + playerRad >= 691 && playerPos.y - playerRad <= 708 ||
				playerPos.x + playerRad >= 552 && playerPos.x - playerRad <= 571 && playerPos.y + playerRad >= 550 && playerPos.y - playerRad <= 708 ||
				playerPos.x + playerRad >= 458 && playerPos.x - playerRad <= 478 && playerPos.y + playerRad >= 691 && playerPos.y - playerRad <= 773 ||
				playerPos.x + playerRad >= 278 && playerPos.x - playerRad <= 455 && playerPos.y + playerRad >= 576 && playerPos.y - playerRad <= 593 ||
				playerPos.x + playerRad >= 436 && playerPos.x - playerRad <= 455 && playerPos.y + playerRad >= 576 && playerPos.y - playerRad <= 708 ||
				playerPos.x + playerRad >= 324 && playerPos.x - playerRad <= 344 && playerPos.y + playerRad >= 326 && playerPos.y - playerRad <= 496 ||
				playerPos.x + playerRad >= 278 && playerPos.x - playerRad <= 678 && playerPos.y + playerRad >= 477 && playerPos.y - playerRad <= 496 ||
				playerPos.x + playerRad >= 659 && playerPos.x - playerRad <= 678 && playerPos.y + playerRad >= 477 && playerPos.y - playerRad <= 708 ||
				playerPos.x + playerRad >= 659 && playerPos.x - playerRad <= 875 && playerPos.y + playerRad >= 691 && playerPos.y - playerRad <= 708 ||
				playerPos.x + playerRad >= 856 && playerPos.x - playerRad <= 875 && playerPos.y + playerRad >= 691 && playerPos.y - playerRad <= 773)
			{
			}
			else
			{
				playerPos.x -= playerSpeed;
			}
		}
	}
#pragma endregion
#pragma region up
	if (pStates[SDL_SCANCODE_UP])
	{
		if (playerPos.x - playerRad >= 21 && playerPos.x + playerRad <= 1433 && playerPos.y - playerRad >= 21 && playerPos.y + playerRad <= 848 ||
			playerPos.x + playerRad >= 1429 && playerPos.x - playerRad <= 1500 && playerPos.y - playerRad >= 403 && playerPos.y + playerRad <= 468)
		{
			if (playerPos.x + playerRad >= 148 && playerPos.x - playerRad <= 309 && playerPos.y + playerRad >= 722 && playerPos.y - playerRad <= 742 ||
				playerPos.x + playerRad >= 120 && playerPos.x - playerRad <= 137 && playerPos.y + playerRad >= 367 && playerPos.y - playerRad <= 629 ||
				playerPos.x + playerRad >= 212 && playerPos.x - playerRad <= 258 && playerPos.y + playerRad >= 386 && playerPos.y - playerRad <= 407 ||
				playerPos.x + playerRad >= 659 && playerPos.x - playerRad <= 675 && playerPos.y + playerRad >= 794 && playerPos.y - playerRad <= 851 ||
				playerPos.x + playerRad >= 428 && playerPos.x - playerRad <= 537 && playerPos.y + playerRad >= 268 && playerPos.y - playerRad <= 369 ||
				playerPos.x + playerRad >= 697 && playerPos.x - playerRad <= 713 && playerPos.y + playerRad >= 18 && playerPos.y - playerRad <= 88 ||
				playerPos.x + playerRad >= 734 && playerPos.x - playerRad <= 818 && playerPos.y + playerRad >= 261 && playerPos.y - playerRad <= 282 ||
				playerPos.x + playerRad >= 1339 && playerPos.x - playerRad <= 1433 && playerPos.y + playerRad >= 194 && playerPos.y - playerRad <= 214 ||
				playerPos.x + playerRad >= 94 && playerPos.x - playerRad <= 349 && playerPos.y + playerRad >= 158 && playerPos.y - playerRad <= 168 ||
				playerPos.x + playerRad >= 177 && playerPos.x - playerRad <= 194 && playerPos.y + playerRad >= 160 && playerPos.y - playerRad <= 292 ||
				playerPos.x + playerRad >= 658 && playerPos.x - playerRad <= 1139 && playerPos.y + playerRad >= 381 && playerPos.y - playerRad <= 400 ||
				playerPos.x + playerRad >= 333 && playerPos.x - playerRad <= 349 && playerPos.y + playerRad >= 94 && playerPos.y - playerRad <= 176 ||
				playerPos.x + playerRad >= 493 && playerPos.x - playerRad <= 836 && playerPos.y + playerRad >= 151 && playerPos.y - playerRad <= 171 ||
				playerPos.x + playerRad >= 529 && playerPos.x - playerRad <= 545 && playerPos.y + playerRad >= 114 && playerPos.y - playerRad <= 169 ||
				playerPos.x + playerRad >= 632 && playerPos.x - playerRad <= 649 && playerPos.y + playerRad >= 153 && playerPos.y - playerRad <= 304 ||
				playerPos.x + playerRad >= 902 && playerPos.x - playerRad <= 1240 && playerPos.y + playerRad >= 114 && playerPos.y - playerRad <= 134 ||
				playerPos.x + playerRad >= 902 && playerPos.x - playerRad <= 918 && playerPos.y + playerRad >= 114 && playerPos.y - playerRad <= 262 ||
				playerPos.x + playerRad >= 902 && playerPos.x - playerRad <= 1240 && playerPos.y + playerRad >= 242 && playerPos.y - playerRad <= 262 ||
				playerPos.x + playerRad >= 1223 && playerPos.x - playerRad <= 1240 && playerPos.y + playerRad >= 242 && playerPos.y - playerRad <= 403 ||
				playerPos.x + playerRad >= 1223 && playerPos.x - playerRad <= 1433 && playerPos.y + playerRad >= 383 && playerPos.y - playerRad <= 403 ||
				playerPos.x + playerRad >= 757 && playerPos.x - playerRad <= 971 && playerPos.y + playerRad >= 537 && playerPos.y - playerRad <= 556 ||
				playerPos.x + playerRad >= 757 && playerPos.x - playerRad <= 773 && playerPos.y + playerRad >= 537 && playerPos.y - playerRad <= 612 ||
				playerPos.x + playerRad >= 856 && playerPos.x - playerRad <= 872 && playerPos.y + playerRad >= 465 && playerPos.y - playerRad <= 556 ||
				playerPos.x + playerRad >= 1029 && playerPos.x - playerRad <= 1046 && playerPos.y + playerRad >= 468 && playerPos.y - playerRad <= 723 ||
				playerPos.x + playerRad >= 1029 && playerPos.x - playerRad <= 1433 && playerPos.y + playerRad >= 468 && playerPos.y - playerRad <= 487 ||
				playerPos.x + playerRad >= 1029 && playerPos.x - playerRad <= 1319 && playerPos.y + playerRad >= 703 && playerPos.y - playerRad <= 723 ||
				playerPos.x + playerRad >= 1302 && playerPos.x - playerRad <= 1319 && playerPos.y + playerRad >= 590 && playerPos.y - playerRad <= 723 ||
				playerPos.x + playerRad >= 1130 && playerPos.x - playerRad <= 1319 && playerPos.y + playerRad >= 590 && playerPos.y - playerRad <= 610 ||
				playerPos.x + playerRad >= 436 && playerPos.x - playerRad <= 568 && playerPos.y + playerRad >= 688 && playerPos.y - playerRad <= 708 ||
				playerPos.x + playerRad >= 552 && playerPos.x - playerRad <= 568 && playerPos.y + playerRad >= 547 && playerPos.y - playerRad <= 708 ||
				playerPos.x + playerRad >= 458 && playerPos.x - playerRad <= 475 && playerPos.y + playerRad >= 688 && playerPos.y - playerRad <= 773 ||
				playerPos.x + playerRad >= 278 && playerPos.x - playerRad <= 452 && playerPos.y + playerRad >= 573 && playerPos.y - playerRad <= 593 ||
				playerPos.x + playerRad >= 436 && playerPos.x - playerRad <= 452 && playerPos.y + playerRad >= 573 && playerPos.y - playerRad <= 708 ||
				playerPos.x + playerRad >= 324 && playerPos.x - playerRad <= 341 && playerPos.y + playerRad >= 323 && playerPos.y - playerRad <= 496 ||
				playerPos.x + playerRad >= 278 && playerPos.x - playerRad <= 675 && playerPos.y + playerRad >= 474 && playerPos.y - playerRad <= 496 ||
				playerPos.x + playerRad >= 659 && playerPos.x - playerRad <= 675 && playerPos.y + playerRad >= 474 && playerPos.y - playerRad <= 708 ||
				playerPos.x + playerRad >= 659 && playerPos.x - playerRad <= 872 && playerPos.y + playerRad >= 688 && playerPos.y - playerRad <= 708 ||
				playerPos.x + playerRad >= 856 && playerPos.x - playerRad <= 872 && playerPos.y + playerRad >= 688 && playerPos.y - playerRad <= 773)
			{
			}
			else
			{
				playerPos.y += playerSpeed;
			}
		}
	}
#pragma endregion
#pragma region down
	if (pStates[SDL_SCANCODE_DOWN])
	{
		if (playerPos.x - playerRad >= 21 && playerPos.x + playerRad <= 1433 && playerPos.y - playerRad >= 24 && playerPos.y + playerRad <= 851 ||
			playerPos.x + playerRad >= 1429 && playerPos.x - playerRad <= 1500 && playerPos.y - playerRad >= 406 && playerPos.y + playerRad <= 471)
		{
			if (playerPos.x + playerRad >= 148 && playerPos.x - playerRad <= 309 && playerPos.y + playerRad >= 725 && playerPos.y - playerRad <= 745 ||
				playerPos.x + playerRad >= 120 && playerPos.x - playerRad <= 137 && playerPos.y + playerRad >= 370 && playerPos.y - playerRad <= 632 ||
				playerPos.x + playerRad >= 212 && playerPos.x - playerRad <= 258 && playerPos.y + playerRad >= 389 && playerPos.y - playerRad <= 410 ||
				playerPos.x + playerRad >= 659 && playerPos.x - playerRad <= 675 && playerPos.y + playerRad >= 797 && playerPos.y - playerRad <= 854 ||
				playerPos.x + playerRad >= 428 && playerPos.x - playerRad <= 537 && playerPos.y + playerRad >= 271 && playerPos.y - playerRad <= 372 ||
				playerPos.x + playerRad >= 697 && playerPos.x - playerRad <= 713 && playerPos.y + playerRad >= 21 && playerPos.y - playerRad <= 91 ||
				playerPos.x + playerRad >= 734 && playerPos.x - playerRad <= 818 && playerPos.y + playerRad >= 264 && playerPos.y - playerRad <= 285 ||
				playerPos.x + playerRad >= 1339 && playerPos.x - playerRad <= 1433 && playerPos.y + playerRad >= 197 && playerPos.y - playerRad <= 217 ||
				playerPos.x + playerRad >= 94 && playerPos.x - playerRad <= 349 && playerPos.y + playerRad >= 161 && playerPos.y - playerRad <= 181 ||
				playerPos.x + playerRad >= 177 && playerPos.x - playerRad <= 194 && playerPos.y + playerRad >= 163 && playerPos.y - playerRad <= 295 ||
				playerPos.x + playerRad >= 658 && playerPos.x - playerRad <= 1139 && playerPos.y + playerRad >= 384 && playerPos.y - playerRad <= 403 ||
				playerPos.x + playerRad >= 333 && playerPos.x - playerRad <= 349 && playerPos.y + playerRad >= 97 && playerPos.y - playerRad <= 179 ||
				playerPos.x + playerRad >= 493 && playerPos.x - playerRad <= 836 && playerPos.y + playerRad >= 154 && playerPos.y - playerRad <= 174 ||
				playerPos.x + playerRad >= 529 && playerPos.x - playerRad <= 545 && playerPos.y + playerRad >= 117 && playerPos.y - playerRad <= 172 ||
				playerPos.x + playerRad >= 632 && playerPos.x - playerRad <= 649 && playerPos.y + playerRad >= 156 && playerPos.y - playerRad <= 307 ||
				playerPos.x + playerRad >= 902 && playerPos.x - playerRad <= 1240 && playerPos.y + playerRad >= 117 && playerPos.y - playerRad <= 137 ||
				playerPos.x + playerRad >= 902 && playerPos.x - playerRad <= 918 && playerPos.y + playerRad >= 117 && playerPos.y - playerRad <= 265 ||
				playerPos.x + playerRad >= 902 && playerPos.x - playerRad <= 1240 && playerPos.y + playerRad >= 245 && playerPos.y - playerRad <= 265 ||
				playerPos.x + playerRad >= 1223 && playerPos.x - playerRad <= 1240 && playerPos.y + playerRad >= 245 && playerPos.y - playerRad <= 406 ||
				playerPos.x + playerRad >= 1223 && playerPos.x - playerRad <= 1433 && playerPos.y + playerRad >= 386 && playerPos.y - playerRad <= 406 ||
				playerPos.x + playerRad >= 757 && playerPos.x - playerRad <= 971 && playerPos.y + playerRad >= 540 && playerPos.y - playerRad <= 559 ||
				playerPos.x + playerRad >= 757 && playerPos.x - playerRad <= 773 && playerPos.y + playerRad >= 540 && playerPos.y - playerRad <= 615 ||
				playerPos.x + playerRad >= 856 && playerPos.x - playerRad <= 872 && playerPos.y + playerRad >= 468 && playerPos.y - playerRad <= 559 ||
				playerPos.x + playerRad >= 1029 && playerPos.x - playerRad <= 1046 && playerPos.y + playerRad >= 471 && playerPos.y - playerRad <= 726 ||
				playerPos.x + playerRad >= 1029 && playerPos.x - playerRad <= 1433 && playerPos.y + playerRad >= 471 && playerPos.y - playerRad <= 490 ||
				playerPos.x + playerRad >= 1029 && playerPos.x - playerRad <= 1319 && playerPos.y + playerRad >= 706 && playerPos.y - playerRad <= 726 ||
				playerPos.x + playerRad >= 1302 && playerPos.x - playerRad <= 1319 && playerPos.y + playerRad >= 593 && playerPos.y - playerRad <= 726 ||
				playerPos.x + playerRad >= 1130 && playerPos.x - playerRad <= 1319 && playerPos.y + playerRad >= 593 && playerPos.y - playerRad <= 613 ||
				playerPos.x + playerRad >= 436 && playerPos.x - playerRad <= 568 && playerPos.y + playerRad >= 691 && playerPos.y - playerRad <= 711 ||
				playerPos.x + playerRad >= 552 && playerPos.x - playerRad <= 568 && playerPos.y + playerRad >= 550 && playerPos.y - playerRad <= 711 ||
				playerPos.x + playerRad >= 458 && playerPos.x - playerRad <= 475 && playerPos.y + playerRad >= 691 && playerPos.y - playerRad <= 776 ||
				playerPos.x + playerRad >= 278 && playerPos.x - playerRad <= 452 && playerPos.y + playerRad >= 576 && playerPos.y - playerRad <= 596 ||
				playerPos.x + playerRad >= 436 && playerPos.x - playerRad <= 452 && playerPos.y + playerRad >= 576 && playerPos.y - playerRad <= 711 ||
				playerPos.x + playerRad >= 324 && playerPos.x - playerRad <= 341 && playerPos.y + playerRad >= 326 && playerPos.y - playerRad <= 499 ||
				playerPos.x + playerRad >= 278 && playerPos.x - playerRad <= 675 && playerPos.y + playerRad >= 477 && playerPos.y - playerRad <= 499 ||
				playerPos.x + playerRad >= 659 && playerPos.x - playerRad <= 675 && playerPos.y + playerRad >= 477 && playerPos.y - playerRad <= 711 ||
				playerPos.x + playerRad >= 659 && playerPos.x - playerRad <= 872 && playerPos.y + playerRad >= 691 && playerPos.y - playerRad <= 711 ||
				playerPos.x + playerRad >= 856 && playerPos.x - playerRad <= 872 && playerPos.y + playerRad >= 691 && playerPos.y - playerRad <= 776)
			{
			}
			else
			{
				playerPos.y -= playerSpeed;
			}
		}
	}
#pragma endregion

	//check if enemy vector should change
#pragma region changeEnemyVectorOnWallImpact
	if (enemyPos1.x - enemyRad >= 21 && enemyPos1.x + enemyRad <= 1431 && enemyPos1.y - enemyRad >= 21 && enemyPos1.y + enemyRad <= 851) { }
	else { getVector(enemyVector1, enemyBool1, enemyPos1); }
	
	if (enemyPos2.x - enemyRad >= 21 && enemyPos2.x + enemyRad <= 1431 && enemyPos2.y - enemyRad >= 21 && enemyPos2.y + enemyRad <= 851) {}
	else { getVector(enemyVector2, enemyBool2, enemyPos2); }

	if (enemyPos3.x - enemyRad >= 21 && enemyPos3.x + enemyRad <= 1431 && enemyPos3.y - enemyRad >= 21 && enemyPos3.y + enemyRad <= 851) {}
	else { getVector(enemyVector3, enemyBool3, enemyPos3); }

	if (enemyPos4.x - enemyRad >= 21 && enemyPos4.x + enemyRad <= 1431 && enemyPos4.y - enemyRad >= 21 && enemyPos4.y + enemyRad <= 851) {}
	else { getVector(enemyVector4, enemyBool4, enemyPos4); }

	if (enemyPos5.x - enemyRad >= 21 && enemyPos5.x + enemyRad <= 1431 && enemyPos5.y - enemyRad >= 21 && enemyPos5.y + enemyRad <= 851) {}
	else { getVector(enemyVector5, enemyBool5, enemyPos5); }
#pragma endregion
#pragma region timer
	timer1 += elapsedSec;
	timer2 += elapsedSec;
	timer3 += elapsedSec;
	timer4 += elapsedSec;
	timer5 += elapsedSec;

	if (timer1 >= rand()% int(timerBounds1.y) + int(timerBounds1.x))
	{
		getVector(enemyVector1, enemyBool1, enemyPos1);
		timer1 = 0;
	}

	if (timer2 >= rand() % int(timerBounds2.y) + int(timerBounds2.x))
	{
		getVector(enemyVector2, enemyBool2, enemyPos2);
		timer2 = 0;
	}

	if (timer3 >= rand() % int(timerBounds1.y) + int(timerBounds1.x))
	{
		getVector(enemyVector3, enemyBool3, enemyPos3);
		timer3 = 0;
	}

	if (timer4 >= rand() % int(timerBounds2.y) + int(timerBounds2.x))
	{
		getVector(enemyVector4, enemyBool4, enemyPos4);
		timer4 = 0;
	}

	if (timer5 >= rand() % int(timerBounds1.y) + int(timerBounds1.x))
	{
		getVector(enemyVector5, enemyBool5, enemyPos5);
		timer5 = 0;
	}
#pragma endregion


	//check if a coin is collected
#pragma region coinCollision
	coinCollectedTimer += elapsedSec;

	for (int i{ 0 }; i < 5; ++i)
	{
		if (playerPos.x - playerRad <= coinsPos[i].x + coinRad - 5 &&
			playerPos.x + playerRad >= coinsPos[i].x/* - coinRad*/ + 5 &&
			playerPos.y - playerRad <= coinsPos[i].y + coinRad - 5 &&
			playerPos.y + playerRad >= coinsPos[i].y/* - coinRad*/ + 5)
		{
			coinsCollected[i] = true;
			++totalCoins;
			coinSound->Play(false);
			++boosts;

			coinCollectedTimer = 0;
		}
	}

#pragma endregion
#pragma region changeLocation
	for (int i{ 0 }; i < sizeof(coinsCollected); ++i)
	{
		if (coinsCollected[i] == true)
		{
			coinsPos[i].x = 1480;
			coinsPos[i].y = 870 - (i + 1) * coinRad;

			notCoinsPos[i] = Point2f(-500, -500);
		}
		else
		{
			notCoinsPos[i].x = 1480;
			notCoinsPos[i].y = 870 - (i + 1) * coinRad;
		}
	}
	if (coinCollectedTimer <= 3)
	{
		playerPos.x > enemyPos1.x ? enemyBool1.x = 1 : enemyBool1.x = 0;
		playerPos.x > enemyPos2.x ? enemyBool2.x = 1 : enemyBool2.x = 0;
		playerPos.x > enemyPos3.x ? enemyBool3.x = 1 : enemyBool3.x = 0;
		playerPos.x > enemyPos4.x ? enemyBool4.x = 1 : enemyBool4.x = 0;
		playerPos.x > enemyPos5.x ? enemyBool5.x = 1 : enemyBool5.x = 0;

		playerPos.y > enemyPos1.y ? enemyBool1.y = 1 : enemyBool1.y = 0;
		playerPos.y > enemyPos2.y ? enemyBool2.y = 1 : enemyBool2.y = 0;
		playerPos.y > enemyPos3.y ? enemyBool3.y = 1 : enemyBool3.y = 0;
		playerPos.y > enemyPos4.y ? enemyBool4.y = 1 : enemyBool4.y = 0;
		playerPos.y > enemyPos5.y ? enemyBool5.y = 1 : enemyBool5.y = 0;

		if (playerPos.x == enemyPos1.x)
		{enemyVector1.x = 0;
			enemyVector1.y = 10;}
		if (playerPos.x == enemyPos2.x)
		{enemyVector2.x = 0;
			enemyVector2.y = 10;}
		if (playerPos.x == enemyPos3.x)
		{enemyVector3.x = 0;
			enemyVector3.y = 10;}
		if (playerPos.x == enemyPos4.x)
		{enemyVector4.x = 0;
			enemyVector4.y = 10;}
		if (playerPos.x == enemyPos5.x)
		{enemyVector5.x = 0;
			enemyVector5.y = 10;}
	}
#pragma endregion

	//enemy collision
#pragma region enemyCollision
	if (playerPos.x + playerRad >= enemyPos1.x - enemyRad + 5 &&
		playerPos.x - playerRad <= enemyPos1.x + enemyRad - 5 &&
		playerPos.y + playerRad >= enemyPos1.y - enemyRad + 5 &&
		playerPos.y - playerRad <= enemyPos1.y + enemyRad - 5 ||
		playerPos.x + playerRad >= enemyPos2.x - enemyRad + 5 &&
		playerPos.x - playerRad <= enemyPos2.x + enemyRad - 5 &&
		playerPos.y + playerRad >= enemyPos2.y - enemyRad + 5 &&
		playerPos.y - playerRad <= enemyPos2.y + enemyRad - 5 ||
		playerPos.x + playerRad >= enemyPos3.x - enemyRad + 5 &&
		playerPos.x - playerRad <= enemyPos3.x + enemyRad - 5 &&
		playerPos.y + playerRad >= enemyPos3.y - enemyRad + 5 &&
		playerPos.y - playerRad <= enemyPos3.y + enemyRad - 5 ||
		playerPos.x + playerRad >= enemyPos4.x - enemyRad + 5 &&
		playerPos.x - playerRad <= enemyPos4.x + enemyRad - 5 &&
		playerPos.y + playerRad >= enemyPos4.y - enemyRad + 5 &&
		playerPos.y - playerRad <= enemyPos4.y + enemyRad - 5 ||
		playerPos.x + playerRad >= enemyPos5.x - enemyRad + 5 &&
		playerPos.x - playerRad <= enemyPos5.x + enemyRad - 5 &&
		playerPos.y + playerRad >= enemyPos5.y - enemyRad + 5 &&
		playerPos.y - playerRad <= enemyPos5.y + enemyRad - 5)
	{
		loser = true;
		playerSpeed = 0;
		enemySpeed = 0;
	}
#pragma endregion

	//check if all the coins are collected when entering the van
#pragma region win
	if (playerPos.x >= 1480 && totalCoins % 5 == 0 && totalCoins != 0 && newLevel == true)
	{
		vanPos.y -= 200 * elapsedSec;
		playerPos.y -= 200 * elapsedSec;
	}

#pragma endregion

	//next level
#pragma region nextLevel
	if (vanPos.y < -100)
	{
		playerPos = Point2f(1500, 436);

		enemyPos1 = Point2f(100, 100);
		enemyPos2 = Point2f(100, 780);
		enemyPos3 = Point2f(1360, 100);
		enemyPos4 = Point2f(1360, 780);
		enemyPos5 = Point2f(600, 420);

		coinsPos[0] = Point2f(275, 110);
		coinsPos[1] = Point2f(40, 800);
		coinsPos[2] = Point2f(972, 176);
		coinsPos[3] = Point2f(1235, 650);
		coinsPos[4] = Point2f(485, 635);

		coinsCollected[0] = 0;
		coinsCollected[1] = 0;
		coinsCollected[2] = 0;
		coinsCollected[3] = 0;
		coinsCollected[4] = 0;

		boosts = 0;

		vanPos = Point2f(1470, 380);
		newLevel = false;

		enemyRad += 7;
		enemySpeed += 0.1f;
	}
#pragma endregion
}

void Game::getVector(Point2f& vector, Point2f& enemyBools, Point2f enemyPos)
{
	//change the x and y value for the vector
	vector.x = (2 + (rand() % 7));
	vector.y = 10 - vector.x;

	//get 0 or 1 for - or +
	if (enemyPos.x - enemyRad <= 21) enemyBools.x = 1;
	else if (enemyPos.x + enemyRad >= 1431) enemyBools.x = 0;
	else {enemyBools.x = rand() % 2;}

	if (enemyPos.y - enemyRad <= 21) enemyBools.y = 1;
	else if (enemyPos.y + enemyRad >= 851) enemyBools.y = 0;
	else { enemyBools.y = rand() % 2; }
	
}

void Game::Draw( ) const
{
	ClearBackground( );


	//draw the map
	Map.Draw(Rectf(0, 0, 1550, 872));

	//draw player
	Player.Draw(Rectf(playerPos.x - playerRad, playerPos.y - playerRad, playerRad * 2, playerRad * 2));

	//draw enemies
	Drone.Draw(Rectf(enemyPos1.x - enemyRad, enemyPos1.y - enemyRad, enemyRad * 2, enemyRad * 2));
	Drone.Draw(Rectf(enemyPos2.x - enemyRad, enemyPos2.y - enemyRad, enemyRad * 2, enemyRad * 2));
	Drone.Draw(Rectf(enemyPos3.x - enemyRad, enemyPos3.y - enemyRad, enemyRad * 2, enemyRad * 2));
	Drone.Draw(Rectf(enemyPos4.x - enemyRad, enemyPos4.y - enemyRad, enemyRad * 2, enemyRad * 2));
	Drone.Draw(Rectf(enemyPos5.x - enemyRad, enemyPos5.y - enemyRad, enemyRad * 2, enemyRad * 2));
	

	//draw coins
	for (int i{ 0 }; i < 5; ++i)
	{
		Coin.Draw(coinsPos[i], Rectf(coinsPos[i].x - int(coinsPos[i].x) % int(coinRad), coinsPos[i].y - int(coinsPos[i].y) % int(coinRad), coinRad, coinRad));
		NotCoin.Draw(notCoinsPos[i], Rectf(notCoinsPos[i].x - int(notCoinsPos[i].x) % int(coinRad), notCoinsPos[i].y - int(notCoinsPos[i].y) % int(coinRad), coinRad, coinRad));
	}

	//draw van
	Van.Draw(Rectf(vanPos.x, vanPos.y, 50, 120));

	//draw the startscreen
	if (start == true)
	{
		Start.Draw(Rectf(0, 0, 1550, 872));
	}
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
