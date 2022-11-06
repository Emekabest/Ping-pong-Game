#include <fstream>;
#include "iostream"
#include "raylib.h";
using namespace std;


int main() {

	
	const char* gameName = "Pong Game";

	int screenHeight = 600;
	int screenWidth = 1400;

	InitWindow(screenWidth,screenHeight, gameName);
	SetWindowState(FLAG_VSYNC_HINT);


	/*Setting and drawing the ball .............*/

	struct Ball
	{
		float x, y;
		float radius;
		float speedX, speedY;

		void Draw() {

			DrawCircle(x, y, radius, WHITE);

		}
		 
	};

	Ball ball;

	ball.x = GetScreenWidth() / 2;
	ball.y = GetScreenHeight() / 2;
	ball.radius = 5;
	ball.speedX = 300;
	ball.speedY = 300;

	/*Setting and drawing of Paddles*.................*/

	struct Paddle
	{
		float x, y;
		float height = 100;
		float width = 5; 
		float speed = 300;
		
		Rectangle GetRect() {

		return Rectangle{ x, y - height / 2	, width, height };

		}															

		void Draw() {

			DrawRectangle((int)x, (int)y - height / 2 , width, height, WHITE);

		}

	};

	Paddle leftPaddle;

	leftPaddle.x = 40;
	leftPaddle.y = screenHeight / 2;

	Paddle rightPaddle;

	rightPaddle.x = screenWidth - 30 - 45;
	rightPaddle.y = screenHeight / 2;

	bool ballDirection_Right = true;

	while (!WindowShouldClose())
	{
	/*Animating the ball.................*/

	ball.x += ball.speedX * GetFrameTime();
	ball.y += ball.speedY * GetFrameTime();
	
	if (ball.y > GetScreenHeight()){

		ball.y = GetScreenHeight();
		ball.speedY *= -1;
	
	}


// 	if (ball.y < 20 ) {
// 		ball.y = 20;
// 		ball.speedX *= -1.0f;
// 	}


	if (ball.y < 0) {
		ball.y = 0;
		ball.speedY *= -1.0f;
	}

	/*Animating the Paddle...................*/

	//When the player moves the left paddle up.

	if (IsKeyDown(KEY_Q)) 
	{
	
	
	leftPaddle.y -= leftPaddle.speed * GetFrameTime();


	if (leftPaddle.y - (leftPaddle.height / 2) < 0) {  // Can't move beyond the top side of the screen......................
			leftPaddle.y = leftPaddle.height / 2;
		}
	

	}

	//When the player moves the Left paddle down.

	if (IsKeyDown(KEY_A)) 
	{

		leftPaddle.y += leftPaddle.speed * GetFrameTime();


		if (leftPaddle.y + (leftPaddle.height / 2 ) > screenHeight) {

			leftPaddle.y = screenHeight - leftPaddle.height / 2;
		}


	}


	//When the player moves the Right paddle up.
	if (IsKeyDown(KEY_P)) {

		rightPaddle.y -= rightPaddle.speed * GetFrameTime();

		if(rightPaddle.y - (rightPaddle.height / 2  ) < 0  ){
		
			rightPaddle.y = rightPaddle.height / 2;
		
		}


	}
	
	//When the player moves the right paddle down.

	if (IsKeyDown(KEY_L)) {
	
		rightPaddle.y += rightPaddle.speed * GetFrameTime();
		if (rightPaddle.y + (rightPaddle.height / 2 ) > screenHeight ){

			rightPaddle.y = screenHeight - rightPaddle.height / 2;

		}


	}

		//Collision (When the ball hits the left paddle)..................................

	if (CheckCollisionCircleRec(Vector2{ ball.x, ball.y }, ball.radius, leftPaddle.GetRect()) && !ballDirection_Right ) {
		 
		ballDirection_Right = true;
		ball.speedX *= -1.1f;
		ball.speedY = (ball.y - leftPaddle.y  ) / (leftPaddle.height / 2 ) * ball.speedX;
		
	}


	//Collision (When the ball hits the right paddle)..................................

	if (CheckCollisionCircleRec(Vector2{ ball.x, ball.y }, ball.radius, rightPaddle.GetRect())  && ballDirection_Right ) {

		ballDirection_Right = false;
		ball.speedY = (ball.y - rightPaddle.y) / (rightPaddle.height / 2) * ball.speedX;
		ball.speedX *= -1.1f;
	}

	/*Printing Winner text to the screen.*/

	const char* winnerText = nullptr;

	if (ball.x > screenWidth) {

		winnerText = "Left Player Wins";
	}

	if (ball.x < 0){
		winnerText = "Right Player Wins";

	}


	/*Restarting the GaME.*/

	if (IsKeyDown(KEY_SPACE) && winnerText) {
		winnerText = nullptr;
		ball.x = screenWidth / 2;
		ball.y = screenHeight / 2;
		ball.speedX = 300;
		ball.speedY = 300;
		ballDirection_Right = true;

				

	}


	//Drawing segment of the game......................
	BeginDrawing();
	ClearBackground(BLACK);

	ball.Draw();
	leftPaddle.Draw();
	rightPaddle.Draw();

	int textWidth = MeasureText(winnerText, 60);

	DrawText(winnerText, (screenWidth - textWidth) / 2   , screenHeight / 2, 60, GREEN);

	EndDrawing();
	}

	 CloseWindow();


}