#pragma once
//
//#include <cmath>
//#include "Vector3.h"
//
//class Matrix4x4Function {
//public:
//	float m[4][4];
//;
//	static Matrix4x4Function MakeScaleMatrix(const Vector3& scale);
//	static Matrix4x4Function MakeRotateXMatrix(float radian);
//	static Matrix4x4Function MakeRotateYMatrix(float radian);
//	static Matrix4x4Function MakeRotateZMatrix(float radian);
//	static Matrix4x4Function Multiply(Matrix4x4Function m1, Matrix4x4Function m2);
//	static Matrix4x4Function MakeRotationMatrix(const Vector3& rotate);
//	static Matrix4x4Function MakeTranslationMatrix(const Vector3& translate);
//	static Matrix4x4Function MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate);
//
//	Matrix4x4Function operator*(const Matrix4x4Function& other) const;
//};

#pragma once
#include "Vector3.h"
#include <cstdint> //uint32_tを使う際にはこれを追加

struct Matrix4x4 {
	float m[4][4];

	Matrix4x4() {
		for (int i = 0; i < 4; ++i) {
			for (int j = 0; j < 4; ++j) {
				m[i][j] = 0.0f;
			}
		}
	}

	Matrix4x4(float m00, float m01, float m02, float m03, float m10, float m11, float m12, float m13, float m20, float m21, float m22, float m23, float m30, float m31, float m32, float m33) {
		m[0][0] = m00;
		m[0][1] = m01;
		m[0][2] = m02;
		m[0][3] = m03;
		m[1][0] = m10;
		m[1][1] = m11;
		m[1][2] = m12;
		m[1][3] = m13;
		m[2][0] = m20;
		m[2][1] = m21;
		m[2][2] = m22;
		m[2][3] = m23;
		m[3][0] = m30;
		m[3][1] = m31;
		m[3][2] = m32;
		m[3][3] = m33;
	}

	static Matrix4x4 Identity() {
		Matrix4x4 mat;
		for (int i = 0; i < 4; ++i) {
			mat.m[i][i] = 1.0f;
		}
		return mat;
	}
};
struct Sphere {
	Vector3 center; //!< 中心点
	float radius;   //!< 半径
};
struct Triangle {
	Vector3 v0, v1, v2; // 三角形の3つの頂点
	Vector3 vertice[3]; // 頂点の配列

	Triangle() : v0(), v1(), v2() {
		vertice[0] = v0;
		vertice[1] = v1;
		vertice[2] = v2;
	}

	Triangle(const Vector3& v0, const Vector3& v1, const Vector3& v2) : v0(v0), v1(v1), v2(v2) {
		vertice[0] = v0;
		vertice[1] = v1;
		vertice[2] = v2;
	}
};


////
// 00_01
////

// 加算
Vector3 add(const Vector3& v1, const Vector3& v2);
// 減算
Vector3 Subtract(const Vector3& v1, const Vector3& v2);
// スカラー倍
Vector3 Multiply(float scalar, const Vector3& v2);
float Dot(const Vector3& v1, const Vector3& v2);
// 長さ(イルム)
float Length(const Vector3& v);
// 正規化
Vector3 Nirmalize(const Vector3& v);

////
// 00_02
////

Matrix4x4 Inverse(const Matrix4x4& m);
Matrix4x4 Transpose(const Matrix4x4& m);
Matrix4x4 MakeIdentity4x4();

////
// 00_03
////

Matrix4x4 MakeTranslateMatrix(const Vector3& translate);
Matrix4x4 MakeScaleMatrix(const Vector3& scale);
Vector3 Transform(const Vector3& vector, const Matrix4x4& matrix);

////
// 00_04
////

Matrix4x4 MakeRotateXMatrix(float radian);
Matrix4x4 MakeRotateYMatrix(float radian);
Matrix4x4 MakeRotateZMatrix(float radian);
Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2);

////
// 00_05
////

Matrix4x4 MakeRotationMatrix(const Vector3& rotate);
Matrix4x4 MakeTranslationMatrix(const Vector3& translate);
Matrix4x4 operator*(const Matrix4x4& a, const Matrix4x4& b);
Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate);

////
// 01_00
////

Matrix4x4 MakePerspectiveFovMatrix(float fovY, float aspectRatio, float nearClip, float farClip);
Matrix4x4 MakeOrthographicMatrix(float left, float top, float right, float bottom, float nearClip, float farClip);
Matrix4x4 MakeViewportMatrix(float left, float top, float width, float height, float minDepth, float maxDepth);

////
// 01_01
////

// ベクトルのクロス積を計算
Vector3 Cross(const Vector3& v1, const Vector3& v2);
// ベクトルを変換
Vector3 Transform_2(const Vector3& v, const Matrix4x4& m);