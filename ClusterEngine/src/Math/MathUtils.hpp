#pragma once

#include "Vector2.hpp"
#include "Vector3.hpp"
#include "Math.h"
#include <algorithm>
#include <time.h>
#include <cstdlib>

#define FLOAT_MIN 1.175494351E-38
#define FLOAT_MAX 3.402823466E+38

class MathUtils
{
public:

    /**
     * Converts the Vector2 to Vector3
     * @param vector: The vector to convert.
     */
	static inline Vector2 ToVec2(Vector3 vector);
    /**
     * Converts the Vector2 to Vector2
     * @param vector: The vector to convert.
     */
    static inline Vector3 ToVec3(Vector2 vector);

    /**
     * Switches X & Y Coordinates
     * @param vector: The vector to modify
     */
    static inline Vector2 SwitchXY(Vector2 vector);

    /**
     * Return the lowest value between the 2
     */
    static inline float min(float a, float b);

    /**
     * Returns the highest value between the 2
     */
    static inline float max(float a, float b);

    /**
     * Returns a random value between a min and max
     *@param min: lowest value (inclused)
     *@param max: highest value (inclused)
     */
    static inline float RandomRange(float min, float max);

    /**
     *  Returns a random value between a min and max
     *@param min: lowest value (inclused)
     *@param max: highest value (inclused)
     */
    static inline int RandomRange(int min, int max);

    /**
     * It limits the value within a min and max
     *@param _value: the value to clamp
     *@param min: lowest value 
     *@param max: highest value 
    */
    static inline float Clamp(float _value, float min, float max);
    
    /**
     * It limits the value from 0 to 1
    */
    static inline float Clamp01(float _value);
}; 

Vector2 MathUtils::ToVec2(Vector3 vector)
{
	return Vector2(vector.X, vector.Y);
}

Vector3 MathUtils::ToVec3(Vector2 vector)
{
    return Vector3(vector.X, vector.Y, 0);
}

Vector2 MathUtils::SwitchXY(Vector2 vector)
{
    return Vector2(vector.Y, vector.X);
}

float MathUtils::min(float a, float b)
{
    if (a > b) return b;
    else return a;
}

float MathUtils::max(float a, float b)
{
    if (a > b) return a;
    else return b;
}

float MathUtils::RandomRange(float min, float max)
{
    return static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * (max - min) + min;
}

int MathUtils::RandomRange(int min, int max)
{
    return rand() %  (max+1 - min) + min;
}

float MathUtils::Clamp(float _value, float min, float max)
{
    if (_value < min) return min;
    else if (_value > max) return max;
    else return _value;
}

float MathUtils::Clamp01(float _value)
{
    if (_value < 0) return 0;
    else if (_value > 1) return 1;
    else return _value;
}