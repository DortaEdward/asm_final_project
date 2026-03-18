#include "raylib.h"
#include "raymath.h"
#include "stdio.h"

const int screenWidth = 800;
const int screenHeight = 650;
const int paddleWidth = 10;
const int paddleHeight = 80;
const float paddleSpeed = 20;
const int FONTSIZE = 50;

void handleInput(Rectangle *leftPaddle, Rectangle *rightPaddle)
{
  if (IsKeyDown(KEY_W))
  {
    if (leftPaddle->y > 0)
    {
      leftPaddle->y -= paddleSpeed;
    };
  }
  if (IsKeyDown(KEY_S))
  {
    if (leftPaddle->y < screenHeight - paddleHeight)
    {
      leftPaddle->y += paddleSpeed;
    };
  }

  if (IsKeyDown(KEY_UP))
  {
    if (rightPaddle->y > 0)
    {
      rightPaddle->y -= paddleSpeed;
    };
  }
  if (IsKeyDown(KEY_DOWN))
  {
    if (rightPaddle->y < screenHeight - paddleHeight)
    {
      rightPaddle->y += paddleSpeed;
    };
  }
}

void ResetPaddle(Rectangle *leftPaddle, Rectangle *rightPaddle)
{
  leftPaddle->y = (float)screenHeight / 2 - (leftPaddle->height / 2);
  rightPaddle->y = (float)screenHeight / 2 - (rightPaddle->height / 2);
}

void handleCeilingCollision(Vector2 *ballPos, Vector2 *ballVel, float ballCir)
{
  if (ballPos->y <= 0 + ballCir || ballPos->y >= screenHeight - ballCir)
  {
    ballVel->y *= -1;
  }
}

void handlePoints(Vector2 *ballPos, Vector2 *ballVel, Vector2 initalBallPos, int points[], Vector2 *leftPaddle, Vector2 *rightPaddle)
{
  if (ballPos->x >= screenWidth)
  {
    points[0] += 1;
    *ballPos = initalBallPos;
    ballVel->x = 5;
    ballVel->y = 0;
    ResetPaddle(leftPaddle, rightPaddle);
  }
  if (ballPos->x <= 0)
  {
    points[1] += 1;
    *ballPos = initalBallPos;
    ballVel->x = -5;
    ballVel->y = 0;
    ResetPaddle(leftPaddle, rightPaddle);
  }
}

int main(void)
{

  Vector2 ballVel = {
      (float)-5,
      (float)0};
  Vector2 initalBallPos = {(float)screenWidth / 2, (float)screenHeight / 2};

  // player 1 is 0 player two is 1
  int playerSide = GetRandomValue(0, 1);

  int points[2] = {0, 0};
  char pointP1Buffer[10];
  char pointP2Buffer[10];

  InitWindow(screenWidth, screenHeight, "Pong Clone");
  SetTargetFPS(60);

  // Player One Paddle
  Rectangle leftPaddle = {
      0,
      (float)screenHeight / 2 - (paddleHeight / 2),
      paddleWidth,
      paddleHeight};

  // Player Two Paddle
  Rectangle rightPaddle = {
      screenWidth - paddleWidth,
      (float)screenHeight / 2 - (paddleHeight / 2),
      paddleWidth,
      paddleHeight};

  // Ball
  Vector2 ballPos = initalBallPos;
  float ballCir = 10;

  while (!WindowShouldClose())
  {

    handleInput(&leftPaddle, &rightPaddle);

    ballPos = Vector2Add(ballPos, ballVel);

    handleCeilingCollision(&ballPos, &ballVel, ballCir);
    handlePoints(&ballPos, &ballVel, initalBallPos, points, &leftPaddle, &rightPaddle);

    // Check paddle collision
    if (CheckCollisionCircleRec(ballPos, ballCir, leftPaddle) && ballVel.x < 0)
    {
      ballVel.x *= -1;
      float hitPercent = (ballPos.y - (leftPaddle.y + leftPaddle.height / 2)) / (leftPaddle.height / 2);
      ballVel.y = hitPercent * 5.0f;
    }
    if (CheckCollisionCircleRec(ballPos, ballCir, rightPaddle) && ballVel.x > 0)
    {
      ballVel.x *= -1;
      float hitPercent = (ballPos.y - (rightPaddle.y + rightPaddle.height / 2)) / (rightPaddle.height / 2);
      ballVel.y = hitPercent * 5.0f;
    }

    sprintf(pointP1Buffer, "%d", points[0]);
    sprintf(pointP2Buffer, "%d", points[1]);

    BeginDrawing();
    ClearBackground(DARKGRAY);
    // Score
    // player 1 score
    DrawText(pointP1Buffer, ((screenWidth / 2) / 2), 100, FONTSIZE, LIGHTGRAY);
    // player 2 score
    DrawText(pointP2Buffer, ((screenWidth / 2) + ((screenWidth / 2) / 2)), 100, FONTSIZE, LIGHTGRAY);

    DrawLine(screenWidth / 2, 0, screenWidth / 2, screenHeight, WHITE);
    DrawRectangleRec(leftPaddle, WHITE);
    DrawRectangleRec(rightPaddle, WHITE);
    DrawCircleV(ballPos, ballCir, RED);
    EndDrawing();
  }

  CloseWindow();
}
