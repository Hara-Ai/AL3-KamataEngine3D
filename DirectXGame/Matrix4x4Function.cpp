#include "Matrix4x4Function.h"

Matrix4x4Function Matrix4x4Function::MakeScaleMatrix(const Vector3& scale) {
	Matrix4x4Function scaleMatrix{};

	scaleMatrix.m[0][0] = scale.x;
	scaleMatrix.m[1][1] = scale.y;
	scaleMatrix.m[2][2] = scale.z;
	scaleMatrix.m[3][3] = 1.0f;
	return scaleMatrix;
}

Matrix4x4Function Matrix4x4Function::MakeRotateXMatrix(float radian) {
	float cosTheta = std::cos(radian);
	float sinTheta = std::sin(radian);
	Matrix4x4Function rotateXMatrix{};
	rotateXMatrix.m[0][0] = 1.0f;
	rotateXMatrix.m[1][1] = cosTheta;
	rotateXMatrix.m[1][2] = sinTheta;
	rotateXMatrix.m[2][1] = -sinTheta;
	rotateXMatrix.m[2][2] = cosTheta;
	rotateXMatrix.m[3][3] = 1.0f;
	return rotateXMatrix;
}

Matrix4x4Function Matrix4x4Function::MakeRotateYMatrix(float radian) {
	float cosTheta = std::cos(radian);
	float sinTheta = std::sin(radian);
	Matrix4x4Function rotateYMatrix{};
	rotateYMatrix.m[0][0] = cosTheta;
	rotateYMatrix.m[0][2] = -sinTheta;
	rotateYMatrix.m[1][1] = 1.0f;
	rotateYMatrix.m[2][0] = sinTheta;
	rotateYMatrix.m[2][2] = cosTheta;
	rotateYMatrix.m[3][3] = 1.0f;
	return rotateYMatrix;
}

Matrix4x4Function Matrix4x4Function::MakeRotateZMatrix(float radian) {
	float cosTheta = std::cos(radian);
	float sinTheta = std::sin(radian);
	Matrix4x4Function rotateZMatrix{};
	rotateZMatrix.m[0][0] = cosTheta;
	rotateZMatrix.m[0][1] = sinTheta;
	rotateZMatrix.m[1][0] = -sinTheta;
	rotateZMatrix.m[1][1] = cosTheta;
	rotateZMatrix.m[2][2] = 1.0f;
	rotateZMatrix.m[3][3] = 1.0f;
	return rotateZMatrix;
}

Matrix4x4Function Matrix4x4Function::Multiply(Matrix4x4Function m1, Matrix4x4Function m2) {
	Matrix4x4Function result{};
	for (int i = 0; i < 4; ++i) 
	{
		for (int j = 0; j < 4; ++j)
		{
			result.m[i][j] = m1.m[i][0] * m2.m[0][j] + m1.m[i][1] * m2.m[1][j] + m1.m[i][2] * m2.m[2][j] + m1.m[i][3] * m2.m[3][j];
		}
	}
	return result;
}

Matrix4x4Function Matrix4x4Function::MakeRotationMatrix(const Vector3& rotate) {
	Matrix4x4Function rotateXMatrix = MakeRotateXMatrix(rotate.x);
	Matrix4x4Function rotateYMatrix = MakeRotateYMatrix(rotate.y);
	Matrix4x4Function rotateZMatrix = MakeRotateZMatrix(rotate.z);
	Matrix4x4Function a = rotateXMatrix * rotateYMatrix * rotateZMatrix;
	return a;
}

Matrix4x4Function Matrix4x4Function::MakeTranslationMatrix(const Vector3& translate) {
	Matrix4x4Function translationMatrix{};
	translationMatrix.m[0][0] = 1.0f;
	translationMatrix.m[1][1] = 1.0f;
	translationMatrix.m[2][2] = 1.0f;
	translationMatrix.m[3][3] = 1.0f;
	translationMatrix.m[3][0] = translate.x;
	translationMatrix.m[3][1] = translate.y;
	translationMatrix.m[3][2] = translate.z;
	return translationMatrix;
}

Matrix4x4Function Matrix4x4Function::MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate) {
	Matrix4x4Function scaleMatrix = MakeScaleMatrix(scale);
	Matrix4x4Function rotationMatrix = MakeRotationMatrix(rotate);
	Matrix4x4Function translationMatrix = MakeTranslationMatrix(translate);
	return (scaleMatrix * rotationMatrix * translationMatrix);
}

Matrix4x4Function Matrix4x4Function::operator*(const Matrix4x4Function& other) const { 
	return Multiply(*this, other); 
}

#include "MatrixFunction.h"
#include <cassert>
#include <cmath>

static const int kRowHeight = 20;
static const int kColumnWidth = 60;
// 定数
const float pi = 3.14f;

void MatrixScreenPrintf(int x, int y, const Matrix4x4& matrix) {
	for (int row = 0; row < 4; ++row) {
		for (int column = 0; column < 4; ++column) {
			Novice::ScreenPrintf(x + column * kColumnWidth, y + row * kRowHeight, "%6.02f", matrix.m[row][column]);
		}
	}
}
void VectorScreenPrintf(int x, int y, const Vector3& vector, const char* label) {
	Novice::ScreenPrintf(x, y, "%.02f", vector.x);
	Novice::ScreenPrintf(x + kColumnWidth, y, "%.02f", vector.y);
	Novice::ScreenPrintf(x + kColumnWidth * 2, y, "%.02f", vector.z);
	Novice::ScreenPrintf(x + kColumnWidth * 3, y, "%s", label);
}

////
// 00_01
////

// 加算
Vector3 add(const Vector3& v1, const Vector3& v2) { return {v1.x + v2.x, v1.y + v2.y, v1.z + v2.z}; }
// 減算
Vector3 Subtract(const Vector3& v1, const Vector3& v2) { return {v1.x - v2.x, v1.y - v2.y, v1.z - v2.z}; }
// スカラー倍
Vector3 Multiply(float scalar, const Vector3& v2) { return {scalar * v2.x, scalar * v2.y, scalar * v2.z}; }
float Dot(const Vector3& v1, const Vector3& v2) { return {v1.x * v2.x + v1.y * v2.y + v1.z * v2.z}; }
// 長さ(イルム)
float Length(const Vector3& v) { return {std::sqrt(Dot(v, v))}; }
// 正規化
Vector3 Nirmalize(const Vector3& v) {
	float length = Length(v);
	return {v.x / length, v.y / length, v.z / length};
}

////
// 00_02
////

Matrix4x4 Inverse(const Matrix4x4& m) {
	Matrix4x4 result;
	float det;

	// 行列式の計算
	det =
	    m.m[0][0] *
	        (m.m[1][1] * (m.m[2][2] * m.m[3][3] - m.m[3][2] * m.m[2][3]) - m.m[1][2] * (m.m[2][1] * m.m[3][3] - m.m[3][1] * m.m[2][3]) + m.m[1][3] * (m.m[2][1] * m.m[3][2] - m.m[3][1] * m.m[2][2])) -
	    m.m[0][1] *
	        (m.m[1][0] * (m.m[2][2] * m.m[3][3] - m.m[3][2] * m.m[2][3]) - m.m[1][2] * (m.m[2][0] * m.m[3][3] - m.m[3][0] * m.m[2][3]) + m.m[1][3] * (m.m[2][0] * m.m[3][2] - m.m[3][0] * m.m[2][2])) +
	    m.m[0][2] *
	        (m.m[1][0] * (m.m[2][1] * m.m[3][3] - m.m[3][1] * m.m[2][3]) - m.m[1][1] * (m.m[2][0] * m.m[3][3] - m.m[3][0] * m.m[2][3]) + m.m[1][3] * (m.m[2][0] * m.m[3][1] - m.m[3][0] * m.m[2][1])) -
	    m.m[0][3] *
	        (m.m[1][0] * (m.m[2][1] * m.m[3][2] - m.m[3][1] * m.m[2][2]) - m.m[1][1] * (m.m[2][0] * m.m[3][2] - m.m[3][0] * m.m[2][2]) + m.m[1][2] * (m.m[2][0] * m.m[3][1] - m.m[3][0] * m.m[2][1]));

	// 行列式が0の場合は逆行列が存在しない
	if (fabs(det) < 1e-9) {
		// 適切なエラーハンドリングを行う
		return result;
	}

	float invDet = 1.0f / det;

	// アジョイント行列を計算し、行列式で割る
	result.m[0][0] =
	    (m.m[1][1] * (m.m[2][2] * m.m[3][3] - m.m[3][2] * m.m[2][3]) - m.m[1][2] * (m.m[2][1] * m.m[3][3] - m.m[2][3] * m.m[3][1]) + m.m[1][3] * (m.m[2][1] * m.m[3][2] - m.m[2][2] * m.m[3][1])) *
	    invDet;
	result.m[0][1] =
	    (-m.m[0][1] * (m.m[2][2] * m.m[3][3] - m.m[2][3] * m.m[3][2]) + m.m[0][2] * (m.m[2][1] * m.m[3][3] - m.m[2][3] * m.m[3][1]) - m.m[0][3] * (m.m[2][1] * m.m[3][2] - m.m[2][2] * m.m[3][1])) *
	    invDet;
	result.m[0][2] =
	    (m.m[0][1] * (m.m[1][2] * m.m[3][3] - m.m[1][3] * m.m[3][2]) - m.m[0][2] * (m.m[1][1] * m.m[3][3] - m.m[1][3] * m.m[3][1]) + m.m[0][3] * (m.m[1][1] * m.m[3][2] - m.m[1][2] * m.m[3][1])) *
	    invDet;
	result.m[0][3] =
	    (-m.m[0][1] * (m.m[1][2] * m.m[2][3] - m.m[1][3] * m.m[2][2]) + m.m[0][2] * (m.m[1][1] * m.m[2][3] - m.m[1][3] * m.m[2][1]) - m.m[0][3] * (m.m[1][1] * m.m[2][2] - m.m[1][2] * m.m[2][1])) *
	    invDet;
	result.m[1][0] =
	    (-m.m[1][0] * (m.m[2][2] * m.m[3][3] - m.m[2][3] * m.m[3][2]) + m.m[1][2] * (m.m[2][0] * m.m[3][3] - m.m[2][3] * m.m[3][0]) - m.m[1][3] * (m.m[2][0] * m.m[3][2] - m.m[2][2] * m.m[3][0])) *
	    invDet;
	result.m[1][1] =
	    (m.m[0][0] * (m.m[2][2] * m.m[3][3] - m.m[2][3] * m.m[3][2]) - m.m[0][2] * (m.m[2][0] * m.m[3][3] - m.m[2][3] * m.m[3][0]) + m.m[0][3] * (m.m[2][0] * m.m[3][2] - m.m[2][2] * m.m[3][0])) *
	    invDet;
	result.m[1][2] =
	    (-m.m[0][0] * (m.m[1][2] * m.m[3][3] - m.m[1][3] * m.m[3][2]) + m.m[0][2] * (m.m[1][0] * m.m[3][3] - m.m[1][3] * m.m[3][0]) - m.m[0][3] * (m.m[1][0] * m.m[3][2] - m.m[1][2] * m.m[3][0])) *
	    invDet;
	result.m[1][3] =
	    (m.m[0][0] * (m.m[1][2] * m.m[2][3] - m.m[1][3] * m.m[2][2]) - m.m[0][2] * (m.m[1][0] * m.m[2][3] - m.m[1][3] * m.m[2][0]) + m.m[0][3] * (m.m[1][0] * m.m[2][2] - m.m[1][2] * m.m[2][0])) *
	    invDet;
	result.m[2][0] =
	    (m.m[1][0] * (m.m[2][1] * m.m[3][3] - m.m[2][3] * m.m[3][1]) - m.m[1][1] * (m.m[2][0] * m.m[3][3] - m.m[2][3] * m.m[3][0]) + m.m[1][3] * (m.m[2][0] * m.m[3][1] - m.m[2][1] * m.m[3][0])) *
	    invDet;
	result.m[2][1] =
	    (-m.m[0][0] * (m.m[2][1] * m.m[3][3] - m.m[2][3] * m.m[3][1]) + m.m[0][1] * (m.m[2][0] * m.m[3][3] - m.m[2][3] * m.m[3][0]) - m.m[0][3] * (m.m[2][0] * m.m[3][1] - m.m[2][1] * m.m[3][0])) *
	    invDet;
	result.m[2][2] =
	    (m.m[0][0] * (m.m[1][1] * m.m[3][3] - m.m[1][3] * m.m[3][1]) - m.m[0][1] * (m.m[1][0] * m.m[3][3] - m.m[1][3] * m.m[3][0]) + m.m[0][3] * (m.m[1][0] * m.m[3][1] - m.m[1][1] * m.m[3][0])) *
	    invDet;
	result.m[2][3] =
	    (-m.m[0][0] * (m.m[1][1] * m.m[2][3] - m.m[1][3] * m.m[2][1]) + m.m[0][1] * (m.m[1][0] * m.m[2][3] - m.m[1][3] * m.m[2][0]) - m.m[0][3] * (m.m[1][0] * m.m[2][1] - m.m[1][1] * m.m[2][0])) *
	    invDet;
	result.m[3][0] =
	    (-m.m[1][0] * (m.m[2][1] * m.m[3][2] - m.m[3][1] * m.m[2][2]) + m.m[1][1] * (m.m[2][0] * m.m[3][2] - m.m[3][0] * m.m[2][2]) - m.m[1][2] * (m.m[2][0] * m.m[3][1] - m.m[3][0] * m.m[2][1])) *
	    invDet;
	result.m[3][1] =
	    (m.m[0][0] * (m.m[2][1] * m.m[3][2] - m.m[3][1] * m.m[2][2]) - m.m[0][1] * (m.m[2][0] * m.m[3][2] - m.m[3][0] * m.m[2][2]) + m.m[0][2] * (m.m[2][0] * m.m[3][1] - m.m[3][0] * m.m[2][1])) *
	    invDet;
	result.m[3][2] =
	    (-m.m[0][0] * (m.m[1][1] * m.m[3][2] - m.m[3][1] * m.m[1][2]) + m.m[0][1] * (m.m[1][0] * m.m[3][2] - m.m[3][0] * m.m[1][2]) - m.m[0][2] * (m.m[1][0] * m.m[3][1] - m.m[3][0] * m.m[1][1])) *
	    invDet;
	result.m[3][3] =
	    (m.m[0][0] * (m.m[1][1] * m.m[2][2] - m.m[2][1] * m.m[1][2]) - m.m[0][1] * (m.m[1][0] * m.m[2][2] - m.m[2][0] * m.m[1][2]) + m.m[0][2] * (m.m[1][0] * m.m[2][1] - m.m[2][0] * m.m[1][1])) *
	    invDet;

	return result;
}
Matrix4x4 Transpose(const Matrix4x4& m) {
	Matrix4x4 result;
	result.m[0][0] = m.m[0][0];
	result.m[0][1] = m.m[1][0];
	result.m[0][2] = m.m[2][0];
	result.m[0][3] = m.m[3][0];
	result.m[1][0] = m.m[0][1];
	result.m[1][1] = m.m[1][1];
	result.m[1][2] = m.m[2][1];
	result.m[1][3] = m.m[3][1];
	result.m[2][0] = m.m[0][2];
	result.m[2][1] = m.m[1][2];
	result.m[2][2] = m.m[2][2];
	result.m[2][3] = m.m[3][2];
	result.m[3][0] = m.m[0][3];
	result.m[3][1] = m.m[1][3];
	result.m[3][2] = m.m[2][3];
	result.m[3][3] = m.m[3][3];
	return result;
}
Matrix4x4 MakeIdentity4x4() {

	Matrix4x4 identity;
	identity.m[0][0] = 1.0f;
	identity.m[0][1] = 0.0f;
	identity.m[0][2] = 0.0f;
	identity.m[0][3] = 0.0f;
	identity.m[1][0] = 0.0f;
	identity.m[1][1] = 1.0f;
	identity.m[1][2] = 0.0f;
	identity.m[1][3] = 0.0f;
	identity.m[2][0] = 0.0f;
	identity.m[2][1] = 0.0f;
	identity.m[2][2] = 1.0f;
	identity.m[2][3] = 0.0f;
	identity.m[3][0] = 0.0f;
	identity.m[3][1] = 0.0f;
	identity.m[3][2] = 0.0f;
	identity.m[3][3] = 1.0f;
	return identity;
}

////
// 00_03
////

Matrix4x4 MakeTranslateMatrix(const Vector3& translate) {
	return {
	    1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, translate.x, translate.y, translate.z, 1.0f,
	};
}
Matrix4x4 MakeScaleMatrix(const Vector3& scale) {
	return {
	    scale.x, 0.0f, 0.0f, 0.0f, 0.0f, scale.y, 0.0f, 0.0f, 0.0f, 0.0f, scale.z, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
	};
}
Vector3 Transform(const Vector3& vector, const Matrix4x4& matrix) {
	Vector3 result; // w=1がデカルト座標系であるので(x,y,1)のベクトルとしてmatrixとの積をとる
	result.x = vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0] + vector.z * matrix.m[2][0] + 1.0f * matrix.m[3][0];
	result.y = vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1] + vector.z * matrix.m[2][1] + 1.0f * matrix.m[3][1];
	result.z = vector.x * matrix.m[0][2] + vector.y * matrix.m[1][2] + vector.z * matrix.m[2][2] + 1.0f * matrix.m[3][2];
	float w = vector.x * matrix.m[0][3] + vector.y * matrix.m[1][3] + vector.z * matrix.m[2][3] + 1.0f * matrix.m[3][3];
	//assert(w != 0.0f); // ベクトルに対して基本的な操作を行う行列でwが0になることはありえない
	// w=1がデカルト座標系であるので、w除算することで同次座標をデカルト座標に戻す
	result.x /= w;
	result.y /= w;
	result.z /= w;
	return result;
}

////
// 00_04
////

Matrix4x4 MakeRotateXMatrix(float radian) {
	Matrix4x4 result;
	float cosAngle = std::cos(radian);
	float sinAngle = std::sin(radian);

	result.m[1][1] = cosAngle;
	result.m[1][2] = sinAngle;
	result.m[2][1] = -sinAngle;
	result.m[2][2] = cosAngle;

	return result;
}
Matrix4x4 MakeRotateYMatrix(float radian) {
	Matrix4x4 result;
	float cosAngle = std::cos(radian);
	float sinAngle = std::sin(radian);

	result.m[0][0] = cosAngle;
	result.m[0][2] = -sinAngle;
	result.m[2][0] = sinAngle;
	result.m[2][2] = cosAngle;

	return result;
}
Matrix4x4 MakeRotateZMatrix(float radian) {
	Matrix4x4 result;
	float cosAngle = std::cos(radian);
	float sinAngle = std::sin(radian);

	result.m[0][0] = cosAngle;
	result.m[0][1] = sinAngle;
	result.m[1][0] = -sinAngle;
	result.m[1][1] = cosAngle;

	return result;
}
Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2) {
	Matrix4x4 result;

	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			result.m[i][j] = 0;
			for (int k = 0; k < 4; ++k) {
				result.m[i][j] += m1.m[i][k] * m2.m[k][j];
			}
		}
	}

	return result;
}

////
// 00_05
////

Matrix4x4 MakeRotationMatrix(const Vector3& rotate) {
	Matrix4x4 rotateX = MakeRotateXMatrix(rotate.x);
	Matrix4x4 rotateY = MakeRotateYMatrix(rotate.y);
	Matrix4x4 rotateZ = MakeRotateZMatrix(rotate.z);

	Matrix4x4 result = Multiply(Multiply(rotateX, rotateY), rotateZ);
	return result;
}
Matrix4x4 MakeTranslationMatrix(const Vector3& translate) {
	Matrix4x4 translationMatrix{1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1};

	translationMatrix.m[3][0] = translate.x;
	translationMatrix.m[3][1] = translate.y;
	translationMatrix.m[3][2] = translate.z;
	return translationMatrix;
}
Matrix4x4 operator*(const Matrix4x4& a, const Matrix4x4& b) { return Multiply(a, b); }
Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate) {
	Matrix4x4 scaleMatrix = MakeScaleMatrix(scale);
	Matrix4x4 rotationMatrix = MakeRotationMatrix(rotate);
	Matrix4x4 translationMatrix = MakeTranslationMatrix(translate);

	Matrix4x4 affineMatrix = scaleMatrix * rotationMatrix * translationMatrix;
	return affineMatrix;
}

////
// 01_00
////

Matrix4x4 MakePerspectiveFovMatrix(float fovY, float aspectRatio, float nearClip, float farClip) {
	Matrix4x4 matrix = {};
	float tanHalfFovY = tanf(fovY / 2.0f);

	matrix.m[0][0] = 1.0f / (aspectRatio * tanHalfFovY);
	matrix.m[1][1] = 1.0f / tanHalfFovY;
	matrix.m[2][2] = farClip / (farClip - nearClip);
	matrix.m[2][3] = 1.0f;
	matrix.m[3][2] = (-nearClip * farClip) / (farClip - nearClip);

	return matrix;
}
Matrix4x4 MakeOrthographicMatrix(float left, float top, float right, float bottom, float nearClip, float farClip) {
	Matrix4x4 matrix = {};

	matrix.m[0][0] = 2.0f / (right - left);
	matrix.m[1][1] = 2.0f / (top - bottom);
	matrix.m[2][2] = 1.0f / (farClip - nearClip);
	matrix.m[3][0] = -(right + left) / (right - left);
	matrix.m[3][1] = -(top + bottom) / (top - bottom);
	matrix.m[3][2] = -nearClip / (farClip - nearClip);
	matrix.m[3][3] = 1.0f;

	return matrix;
}
Matrix4x4 MakeViewportMatrix(float left, float top, float width, float height, float minDepth, float maxDepth) {
	Matrix4x4 matrix = {};

	matrix.m[0][0] = width / 2.0f;
	matrix.m[1][1] = -height / 2.0f;
	matrix.m[2][2] = maxDepth - minDepth;
	matrix.m[3][0] = left + width / 2.0f;
	matrix.m[3][1] = top + height / 2.0f;
	matrix.m[3][2] = minDepth;
	matrix.m[3][3] = 1.0f;

	return matrix;
}

////
// 01_01
////

// ベクトルのクロス積を計算
Vector3 Cross(const Vector3& v1, const Vector3& v2) { return {v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x}; }
// ベクトルを変換
Vector3 Transform_2(const Vector3& v, const Matrix4x4& m) {
	Vector3 result = {};
	result.x = v.x * m.m[0][0] + v.y * m.m[1][0] + v.z * m.m[2][0] + m.m[3][0];
	result.y = v.x * m.m[0][1] + v.y * m.m[1][1] + v.z * m.m[2][1] + m.m[3][1];
	result.z = v.x * m.m[0][2] + v.y * m.m[1][2] + v.z * m.m[2][2] + m.m[3][2];
	return result;
}