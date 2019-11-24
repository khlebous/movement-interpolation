#pragma once

class WindowConstants
{
public:
	static float WIDTH;
	static float HEIGHT;

	static float UI_WIDTH;
	static float UI_HEIGHT() { return HEIGHT / 2.0f; }

	static float EULER_UI_X() { return WIDTH - UI_WIDTH; }
	static float EULER_UI_Y() { return 0; }
	static float QUATERNION_UI_X() { return EULER_UI_X(); }
	static float QUATERNION_UI_Y() { return HEIGHT / 2.0f;}
};
