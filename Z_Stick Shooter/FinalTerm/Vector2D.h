#pragma once
#include <math.h>

class Vector2D {
public:
	Vector2D(float x, float y)	//Vector2D함수는 두개의 인자를 받아넣고 반환한다.(좌표값)
		:m_x(x),			//받아온 인자x를 멤버변수 m_x에 넣는다 --> this.m_x=x;와 같은 기능
		m_y(y) {}

	float getX() { return m_x; }	//getX()함수의 반환값을 m_x로 놓아 x값을 언제든 가져올 수 있다.
	float getY() { return m_y; }
	void setX(float x) { m_x = x; }
	void setY(float y) { m_y = y; }

	

	void normalize() {		//벡터의 정규화-->벡터의 크기를 1로 조정, 방향은 변경X
		float l = length();
		if (l > 0) {		//0으로 나누지 않겠다는 뜻
			(*this) *= 1 / l;
		}
	}
	float length() { return sqrt(m_x * m_x + m_y * m_y); }	//sqrt--> 숫자에 루트를 씌워줌->제곱근 구하기(벡터의 크기 구하기)

	Vector2D operator+(const Vector2D& v2)const {			//벡터의 덧셈
		return Vector2D(m_x + v2.m_x, m_y + v2.m_y);		//연산자 오버로딩 활용:기존의 연산자를 사용자 클래스에서 재정의
	}
	friend Vector2D& operator +=(Vector2D& v1, const Vector2D& v2) {	//friend함수:접근 지정자를 무시하고 접근 가능
		v1.m_x += v2.m_x;
		v1.m_y += v2.m_y;
		return v1;
	}

	Vector2D operator-(const Vector2D& v2)const {			//벡터의 뺄셈
		return Vector2D(m_x - v2.m_x, m_y - v2.m_y);
	}
	friend Vector2D& operator-=(Vector2D& v1, const Vector2D& v2) {
		v1.m_x -= v2.m_x;
		v1.m_y -= v2.m_y;
		return v1;
	}

	Vector2D operator*(float scalar)const {				//벡터와 스칼라의 곱셈(벡터의 스칼라곱은 다른 의미)	벡터 공간에서 벡터를 곱할 수 있는 값. 벡터가 방향이라면 스칼라는 양,변수
		return Vector2D(m_x * scalar, m_y * scalar);
	}
	Vector2D& operator*=(float scalar) {
		m_x *= scalar;
		m_y *= scalar;
		return *this;
	}

	Vector2D operator/(float scalar)const {				//벡터와 스칼라의 나눗셈
		return Vector2D(m_x / scalar, m_y / scalar);
	}
	Vector2D& operator/=(float scalar) {
		m_x /= scalar;
		m_y /= scalar;
		return *this;
	}

private:
	float m_x;
	float m_y;




};