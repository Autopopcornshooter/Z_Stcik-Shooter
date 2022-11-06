#pragma once
#include<string>
class LoaderParams {
public:
	LoaderParams(int x, int y, int width, int height,int angle, std::string textureID)
		:
		m_x(x),
		m_y(y),
		m_width(width),
		m_height(height),
		m_angle(angle),
		m_textureID(textureID) {}
	int getX()const { return m_x; }
	int getY()const { return m_y; }
	int getWidth()const { return m_width; }
	int getHeight()const { return m_height; }
	int getAngle()const { return m_angle; }
	std::string getTextureID()const { return m_textureID; }		//const를 적으면 '이 함수는 멤버 변수의 값을 수정하지 않는다'라는 뜻을 전달한다.

private:
	int m_x, m_y;
	int m_width, m_height;
	int m_angle;
	std::string m_textureID;
};