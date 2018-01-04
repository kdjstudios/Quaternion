/*
 * main.cpp
 *
 *  Created on: Dec 16, 2011
 *      Author: kyle
 */

#include "Quaternion.h"
#include <iostream>
using namespace AO::Quaternion;
using namespace std;

int main()
{
// Demonstrates other copy constructor, static member variable usage, and unary operator-
//const Vector3 backward(-Vector3::Forward);
const Quaternion backward(Quaternion::One*3);
// Demonstrates cross product
const Quaternion right(norm(backward));

// Demonstrates constructor
Quaternion testVect(10.0f, 30.0f,10.0f,22.0f);

// Demonstrates operator<<
cout << testVect << '\n';
// Demonstrates clamp/truncate method
//truncate(testVect,3);
cout << "truncated at 3: " << testVect << '\n';

// Demonstrates reflect method
//const Quaternion reflection( reflect(testVect,backward) );
//cout << "Reflected off surface with 'backward' as the normal, " << reflection << '\n';

// Demonstrates operator*, we don't const 'doubleFwd' because we want to use normalize later.
Quaternion doubleFwd(Quaternion::One* 2);

cout << "Double Forward, " << doubleFwd << '\n';
cout << "Double Forward Length: " << mag(doubleFwd) << '\n';
norm(doubleFwd);
cout << "Normalized Double Forward, now what is the length?: " << mag(doubleFwd) << '\n';
//zero(doubleFwd);
cout << "Zero out Double Forward, now what is the length?: " << doubleFwd << '\n';
//My compiler confuses 'distance' with an c iterator
//cout << "Distance from Double Forward to Reflection: " << (float)AO::Quaternion::dist(doubleFwd,reflection) << '\n';
//Quaternion per( perp(backward) );
//cout << "Perpendicular to 'backward':" << per << '\n';
//cout << "Sign of Perpendicular and double(Not Working) " << sign(per,doubleFwd) << '\n';

//Uncomment the next three lines for user input
//cout << "Press any key to quit. ";
//char blah = ' ';
//cin.get(blah);

return 0;
}
