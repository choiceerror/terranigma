#pragma once
#pragma warning(disable:4996)
#define PI 3.141592f
#define PI2 2 * PI

//프레임 이미지 회전을 위한 각도값
#define PI8		float(PI / 8.0f)
#define PI16	float(PI / 16.0f)
#define PI32	float(PI / 32.0f)
#define PI64	float(PI / 64.0f)
#define PI128	float(PI / 128.0f)

namespace BRAVO_UTIL
{
	float getDistance(float x1, float y1, float x2, float y2);

	float getAngle(float x1, float y1, float x2, float y2);

	inline const string MakeImageName(const char* imageName, const char* folderName = nullptr)
	{
		string str = "";

		if (nullptr != folderName)
		{
			str.append(folderName);
			str.append("/");
		}

		str.append(imageName);
		str.append(".bmp");

		return str;
	}

	inline const string AppendInt(const char* imageName, int value)
	{
		string str = "";
		char num[128];

		itoa(value, num, 10);

		str.append(imageName);
		str.append(num);

		return str;
	}
}