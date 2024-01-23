#include "Spirograph.h"
#include "raymath.h"
#include "raylib.h"

void Spirograph::Main()
{
	Start();

	InitWindow(width, height, "Spirograph");
	SetTargetFPS(120);

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(RAYWHITE);
		Update();
		EndDrawing();
	}
	CloseWindow();
}

void Spirograph::Start()
{
	center.x = width / 2;
	center.y = height / 2;

	innerRadius = outerRadius - drawRingRadius;
}

void Spirograph::InteractionLayer()
{
	if (IsKeyDown(KEY_UP) && innerRadius <= outerRadius)
	{
		points.clear();
		pointColor.clear();
		innerRadius++;
	}
	else if (IsKeyDown(KEY_DOWN) && innerRadius > 0)
	{
		points.clear();
		pointColor.clear();
		innerRadius--;
	}
	else if (IsKeyDown(KEY_RIGHT))
	{
		points.clear();
		pointColor.clear();
		headToCenter++;
	}
	else if (IsKeyDown(KEY_LEFT) && headToCenter >= 0)
	{
		points.clear();
		pointColor.clear();
		headToCenter--;
	}
	else if (IsKeyDown(KEY_W))
	{
		points.clear();
		pointColor.clear();
		speed += 0.01;
	}
	else if (IsKeyDown(KEY_S) && speed >= 0)
	{
		points.clear();
		pointColor.clear();
		speed -= 0.01;
	}

	//Button Input
	Vector2 mousePoint = GetMousePosition();
	if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
	{
		//COLORS
		if (CheckCollisionPointRec(mousePoint, btnRed))
		{
			lineColor = RED;
		}
		else if (CheckCollisionPointRec(mousePoint, btnOrange))
		{
			lineColor = ORANGE;
		}
		else if (CheckCollisionPointRec(mousePoint, btnYellow))
		{
			lineColor = YELLOW;
		}
		else if (CheckCollisionPointRec(mousePoint, btnGreen))
		{
			lineColor = GREEN;
		}
		else if (CheckCollisionPointRec(mousePoint, btnBlue))
		{
			lineColor = BLUE;
		}
		else if (CheckCollisionPointRec(mousePoint, btnPurple))
		{
			lineColor = PURPLE;
		}
		//Size
		else if (CheckCollisionPointRec(mousePoint, btnAddInner) && innerRadius <= outerRadius)
		{
			points.clear();
			pointColor.clear();
			innerRadius++;
		}
		else if (CheckCollisionPointRec(mousePoint, btnMinInner) && innerRadius > 0)
		{
			points.clear();
			pointColor.clear();
			innerRadius--;
		}
		//Length
		else if (CheckCollisionPointRec(mousePoint, btnAddLine))
		{
			points.clear();
			pointColor.clear();
			headToCenter++;
		}
		else if (CheckCollisionPointRec(mousePoint, btnMinLine) && headToCenter > 0)
		{
			points.clear();
			pointColor.clear();
			headToCenter--;
		}
		//Speed
		else if (CheckCollisionPointRec(mousePoint, btnAddSpeed))
		{
			points.clear();
			pointColor.clear();
			speed += 0.01;
		}
		else if (CheckCollisionPointRec(mousePoint, btnMinSpeed) && speed >= 0)
		{
			points.clear();
			pointColor.clear();
			speed -= 0.01;
		}
	}
}

void Spirograph::EvalCurFrame()
{
	angle += speed;
	drawRingCenter.x = center.x + sin(angle * DEG2RAD) * innerRadius;
	drawRingCenter.y = center.y + cos(angle * DEG2RAD) * innerRadius;

	outerInnerRatio = outerRadius / (drawRingRadius - headToCenter);
	headAngle = angle * outerInnerRatio;
	drawHead.x = drawRingCenter.x + sin(headAngle * DEG2RAD) * headToCenter;
	drawHead.y = drawRingCenter.y + cos(headAngle * DEG2RAD) * headToCenter;

	points.push_back(drawHead);
	pointColor.push_back(lineColor);
}

void Spirograph::DrawCurFrame()
{
	//UI
	DrawUI();

	//Outer Circle
	DrawCircleLines(center.x, center.y, outerRadius, BLUE);

	//Inner Circle
	DrawCircleLines(center.x, center.y, innerRadius, GRAY);

	//Spinny Circle
	DrawCircleLines(drawRingCenter.x, drawRingCenter.y, drawRingRadius, BLACK);

	//Head
	DrawLine(drawRingCenter.x, drawRingCenter.y, drawHead.x, drawHead.y, BLACK);
	DrawCircle(drawHead.x, drawHead.y, 10, lineColor);
	DrawCircle(drawRingCenter.x, drawRingCenter.y, 5, BLACK);

	DrawCurve();
}

void Spirograph::DrawCurve()
{
	if (points.size() < 2)
		return;
	for (int i = 1; i < points.size(); i++)
	{
		Vector2 curPoint = points[i];
		Vector2 prevPoint = points[i - 1];

		DrawLine(curPoint.x, curPoint.y, prevPoint.x, prevPoint.y, pointColor[i]);
	}
}

void Spirograph::DrawUI()
{
	//Colors
	DrawRectanglePro(btnRed, Vector2{ 0,0 }, 0, RED);
	DrawRectanglePro(btnOrange, Vector2{ 0,0 }, 0, ORANGE);
	DrawRectanglePro(btnYellow, Vector2{ 0,0 }, 0, YELLOW);
	DrawRectanglePro(btnGreen, Vector2{ 0,0 }, 0, GREEN);
	DrawRectanglePro(btnBlue, Vector2{ 0,0 }, 0, BLUE);
	DrawRectanglePro(btnPurple, Vector2{ 0,0 }, 0, PURPLE);
	DrawText("Colors", 10, 60, 11, BLACK);
	//Size
	DrawRectanglePro(btnAddInner, Vector2{ 0,0 }, 0, RED);
	DrawRectanglePro(btnMinInner, Vector2{ 0,0 }, 0, BLUE);
	DrawText("Inner Radius", 110, 60, 11, BLACK);
	DrawText("+ ADD", buttonBarStart.x + 110, buttonBarStart.y + 5, 11, WHITE);
	DrawText("- MIN", buttonBarStart.x + 110, buttonBarStart.y + 30, 11, WHITE);
	//Length
	DrawRectanglePro(btnAddLine, Vector2{ 0,0 }, 0, RED);
	DrawRectanglePro(btnMinLine, Vector2{ 0,0 }, 0, BLUE);
	DrawText("Line Length", 210, 60, 11, BLACK);
	DrawText("+ ADD", buttonBarStart.x + 210, buttonBarStart.y + 5, 11, WHITE);
	DrawText("- MIN", buttonBarStart.x + 210, buttonBarStart.y + 30, 11, WHITE);
	//Speed
	DrawRectanglePro(btnAddSpeed, Vector2{ 0,0 }, 0, RED);
	DrawRectanglePro(btnMinSpeed, Vector2{ 0,0 }, 0, BLUE);
	DrawText("Speed", 310, 60, 11, BLACK);
	DrawText("+ ADD", buttonBarStart.x + 310, buttonBarStart.y + 5, 11, WHITE);
	DrawText("- MIN", buttonBarStart.x + 310, buttonBarStart.y + 30, 11, WHITE);
}

void Spirograph::Update()
{
	InteractionLayer();
	EvalCurFrame();
	DrawCurFrame();
}
