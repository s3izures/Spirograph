#pragma once
#include <raylib.h>
#include <vector>

class Spirograph
{
public:
	int width = 800;
	int height = 800;
	Vector2 center;

	//Circles
	float outerRadius = 250;
	float innerRadius;
	
	float drawRingRadius = 90;
	Vector2 drawRingCenter;

	float angle = 0;
	float speed = 1;

	//Tip
	Vector2 drawHead;
	float headAngle;
	float outerInnerRatio = 1;
	float headToCenter = 50;

	//Curve
	Color lineColor = RED;
	std::vector<Color> pointColor;
	std::vector<Vector2> points;

	//UI
	Vector2 buttonSize = { 20,20 };
	Vector2 buttonBarStart = { 10, 10 };

		//colors
		Rectangle btnRed = { buttonBarStart.x, buttonBarStart.y, buttonSize.x, buttonSize.y };
		Rectangle btnOrange = { buttonBarStart.x + buttonSize.x + 5, buttonBarStart.y, buttonSize.x, buttonSize.y };
		Rectangle btnYellow = { buttonBarStart.x + (buttonSize.x * 2) + 10, buttonBarStart.y, buttonSize.x, buttonSize.y };
		Rectangle btnGreen = { buttonBarStart.x, buttonBarStart.y + 25, buttonSize.x, buttonSize.y };
		Rectangle btnBlue = { buttonBarStart.x + buttonSize.x + 5, buttonBarStart.y + 25, buttonSize.x, buttonSize.y };
		Rectangle btnPurple = { buttonBarStart.x + (buttonSize.x * 2) + 10, buttonBarStart.y + 25, buttonSize.x, buttonSize.y };
		
		//size
		Rectangle btnAddInner = { buttonBarStart.x + 100, buttonBarStart.y, 70, 20 };
		Rectangle btnMinInner = { buttonBarStart.x + 100, buttonBarStart.y + 25, 70, 20 };
		
		//length
		Rectangle btnAddLine = { buttonBarStart.x + 200, buttonBarStart.y, 70, 20 };
		Rectangle btnMinLine = { buttonBarStart.x + 200, buttonBarStart.y + 25, 70, 20 };
		
		//speed
		Rectangle btnAddSpeed = { buttonBarStart.x + 300, buttonBarStart.y, 70, 20 };
		Rectangle btnMinSpeed = { buttonBarStart.x + 300, buttonBarStart.y + 25, 70, 20 };

	//Functions
	void Main();
	void Start();
	void InteractionLayer();
	void EvalCurFrame();
	void DrawCurFrame();
	void DrawCurve();
	void DrawUI();
	void Update();
};

