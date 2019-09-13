class Vector3
{
public:

	float x, y, z;//Vector parameters

	//Constructor given the three parameters of the vector.
	 Vector3(float X, float Y, float Z);

	 //Constructor given no parameters, will initialize all parameters to 0.
	 Vector3();

	 //Ads a given vector to this one.
	 Vector3 Add(Vector3 Vector);

	 //Subtracts a given vector from this one.
	 Vector3 Subtract(Vector3 Vector);

	 //Multiplies this vector by a scalar.
	 Vector3 Multiply(float Multiplier);

	 //Gets the vectors magnitude (or length).
	 float Magnitude();
};