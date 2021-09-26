#pragma once

//Includes
#include <vector>
#include "../../Maths/Maths.h"

using namespace std;

namespace UnifiedEngine {
	//Gradients
	struct Gradient {
		//All colors
		vector<vec4> colors;

		//Load A Color (vec3 and the w value is position)
		void addColor(vec3 color, float position) {
			this->colors.push_back(vec4(color, position));
		}

		//Get a color from gradient
		vec3 getColor(float position) {
			//Preset Values
			float closest_Low = -1;
			vec3 closest_Low_Color;
			float closest_High = 2;
			vec3 closest_High_Color;

			//Loop over colors
			for (vec4& c : colors) {
				//Positioning check how close to the value
				if (c.w <= position && c.w >= closest_Low) {
					closest_Low = c.w;
					closest_Low_Color = vec3(c.x, c.y, c.z);
				}
				else if (c.w >= position && c.w <= closest_High) {
					closest_High = c.w;
					closest_High_Color = vec3(c.x, c.y, c.z);
				}
			}

			//Get the distances
			float distFromLow = position - closest_Low;
			float distFromHigh = closest_High - position;

			//Using the distances calculate the percentage required of the low or high color to from the new color
			float percentToUseFronLow = 1 - (distFromLow / (distFromLow + distFromHigh));
			float percentToUseFronHigh = 1 - (distFromHigh / (distFromLow + distFromHigh));

			//Form the new color
			vec3 color((closest_Low_Color * percentToUseFronLow) + (closest_High_Color * percentToUseFronHigh));

			//Return the color
			return color;
		}
	};
}