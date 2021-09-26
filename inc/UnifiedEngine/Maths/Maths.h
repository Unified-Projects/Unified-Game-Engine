#pragma once

//Includes
#include <algorithm>
#include <vector>
#include <map>
#include <string>

#include <GLM/glm.hpp>
#include <GLM/vec2.hpp>
#include <GLM/vec3.hpp>
#include <GLM/vec4.hpp>
#include <GLM/mat4x4.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>

#include "../Object/Components/Transforms.h"

using namespace glm;
using namespace std;

#ifndef MATH_DEFENITION
#define MATH_DEFENITION
namespace UnifiedEngine {
	//Calculate Matrix
	mat4 CalculateModelMatrix(Transform transform, vec3 origin){
		//Intialiser
		mat4 Matrix(1.f);

		//Translations
		//Matrix = translate(Matrix, transform.Position);
		Matrix = translate(Matrix, origin);
		Matrix = rotate(Matrix, radians(transform.Rotation.x), vec3(1.f, 0.f, 0.f));
		Matrix = rotate(Matrix, radians(transform.Rotation.y), vec3(0.f, 1.f, 0.f));
		Matrix = rotate(Matrix, radians(transform.Rotation.z), vec3(0.f, 0.f, 1.f));
		Matrix = translate(Matrix, transform.Position - origin);
		Matrix = scale(Matrix, transform.Scale);

		//Return
		return Matrix;
	}
	
	//Reutn Matrix
	mat4 CalculateViewMatrix(Transform transform, vec3 Front, vec3 Up) {
		return lookAt(transform.Position, transform.Position + Front, Up);
	}

	//Half Model Matrix
	mat4 CalculateRotationMatrix(Transform transform) {
		//Init
		mat4 Matrix(1.f);

		//Translation
		Matrix = rotate(Matrix, radians(transform.Rotation.x), vec3(1.f, 0.f, 0.f));
		Matrix = rotate(Matrix, radians(transform.Rotation.y), vec3(0.f, 1.f, 0.f));
		Matrix = rotate(Matrix, radians(transform.Rotation.z), vec3(0.f, 0.f, 1.f));

		//Return
		return Matrix;
	}
	
	//Calc Dist
	float CalculateVec3Dist(vec3 Offset) {
		return sqrtf(powf(Offset.x, 2) + powf(Offset.y, 2) + powf(Offset.z, 2));
	}

	//Calc Dir
	vec3 CalculateVec3Dir(vec3 vector) {
		float total = vector.x + vector.y + vector.z;
		return vec3(vector.x / total, vector.y / total, vector.z / total);
	}

	//Int To Byte(string)
	const char* IntToByte(int i){
		if (i < 256 && i > -1){
			string Out;
			int Check = 128;
			//Loop Wile still holds numerical value
			while(Check > 0){
				if (i-Check > -1){
					Out = Out + "1";
					i -= Check;
				}
				else
					Out = Out + "0";

				Check/=2;

				if (Check == 1){
					Check -= 1;
				}
			}

			return Out.c_str();
		}
		else
			return "";
	}

	//Byte To Hex(string)
	const char* ByteToHex(string byte){
		vector<char> convert = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

		int index = 1;

		bool OtherHalf = false;

		int num1 = 0;
		int num2 = 0;

		//Look over each byte char
		for(char c : byte){
			int value = 16;

			for (int i = 1; i < index; i++){
				value /= 2;
			}

			if (index == 4){
				OtherHalf = true;
			}

			if(c == '1'){
				if(!OtherHalf){
					num1+= value;
				}
				else
					num2+=value;
			}

			index ++;
		}

		//Convert Num to hex
		char c1 = convert[num1];
		char c2 = convert[num2];

		//add to out
		string Out;
		Out.append(&c1);
		Out.append(&c2);

		//Return
		return Out.c_str();
	}
	
	//Vec 3 to Color Data
	vector<int> Vec3ToData(vec3 Color){
		int RI = roundf(Color.x * 255);
		int GI = roundf(Color.y * 255);
		int BI = roundf(Color.z * 255);

		return vector<int>{RI, GI, BI};
	}

	//Vec 3 Comparitor >=
	bool operator>=(vec3 x, vec3 y) {
		return(x.x >= y.x && x.y >= y.y && x.z >= y.z);
	}

	//Vec 2 Comparitor >=
	bool operator>=(vec2 x, vec2 y) {
		return(x.x >= y.x && x.y >= y.y);
	}

	//Vec 3 Comparitor <=
	bool operator<=(vec3 x, vec3 y) {
		return(x.x <= y.x && x.y <= y.y && x.z <= y.z);
	}

	//Vec 2 Comparitor <=
	bool operator<=(vec2 x, vec2 y) {
		return(x.x <= y.x && x.y <= y.y);
	}

	//Vec 3 Comparitor >
	bool operator>(vec3 x, vec3 y) {
		return(x.x > y.x && x.y > y.y && x.z > y.z);
	}

	//Vec 2 Comparitor >
	bool operator>(vec2 x, vec2 y) {
		return(x.x > y.x && x.y > y.y);
	}

	//Vec 3 Comparitor <
	bool operator<(vec3 x, vec3 y) {
		return(x.x < y.x && x.y < y.y && x.z < y.z);
	}

	//Vec 2 Comparitor <
	bool operator<(vec2 x, vec2 y) {
		return(x.x < y.x && x.y < y.y);
	}
}
#endif