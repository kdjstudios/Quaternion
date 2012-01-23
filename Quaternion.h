/*
 * Quaternion.h
 *
 *  Created on: Dec 15, 2011
 *      Author: kyle
 */

#ifndef QUATERNION_H_
#define QUATERNION_H_
#include <ostream>
#include <sstream>
#include <cmath>
namespace AO
{
	namespace Quaternion
	{
		class Quaternion
		{
		public:
			//Members
			float W,X,Y,Z;
			//Constructors
			Quaternion();
			explicit Quaternion(float const&w,float const&x,float const&y,float const&z);
			//Math
			//Vector3 by Vector3 Math
			Quaternion		operator+(const Quaternion& Quat) const;
			Quaternion		operator-(const Quaternion& Quat) const;
			Quaternion		operator*(const Quaternion& Quat) const;
			Quaternion		operator/(const Quaternion& Quat) const;
			Quaternion&		operator+=(const Quaternion& Quat);
			Quaternion&		operator-=(const Quaternion& Quat);
			Quaternion&		operator*=(const Quaternion& Quat);
			Quaternion&		operator/=(const Quaternion& Quat);
			//Vector3 by Float Math
			Quaternion		operator-() const;
			Quaternion		operator+(float const&num) const;
			Quaternion		operator-(float const&num) const;
			Quaternion		operator*(float const&num) const;
			Quaternion		operator/(float const&num) const;
			Quaternion&		operator+=(float const&num);
			Quaternion&		operator-=(float const&num);
			Quaternion&		operator*=(float const&num);
			Quaternion&		operator/=(float const&num);
			//Boolean Equals Operators
			bool		operator==(const Quaternion& Quat) const;
			bool		operator!=(const Quaternion& Quat) const;
			//Static Predefines
			static const Quaternion Zero;
			static const Quaternion One;
			//Print out
			friend std::ostream& operator<< (std::ostream& ofs, const Quaternion& Quat);

		};
	//float mag(Quaternion const &rhs);
	//float dot(Quaternion const &lhs, Quaternion const &rhs);
	//float lsq(Quaternion const&rhs);
	//Quaternion norm(Quaternion const &lhs);
	//Quaternion rotate(float const&lhs,Quaternion const &rhs);

		inline Quaternion::Quaternion():W(0),X(0),Y(0),Z(0){}
		inline Quaternion::Quaternion(float const&w,float const&x,float const&y,float const&z):W(w),X(x),Y(y),Z(z){}
		//
		const Quaternion Quaternion::Zero=Quaternion(0,0,0,0);
		const Quaternion Quaternion::One=Quaternion(1,1,1,1);
		//Vector3 by Vector3 Math
		inline Quaternion Quaternion::operator+(const Quaternion& Quat) const{
			return Quaternion(X+Quat.X,Y+Quat.Y,Z+Quat.Z,W+Quat.W);
		}
		inline Quaternion Quaternion::operator-(const Quaternion& Quat) const{
			return Quaternion(X-Quat.X,Y-Quat.Y,Z-Quat.Z,W-Quat.W);
		}
		inline Quaternion Quaternion::operator*(const Quaternion& Quat) const{
			return Quaternion(
				//---
				(W*Quat.W)-(X*Quat.X)-(Y*Quat.Y)-(Z*Quat.Z),
				//++-
				(W*Quat.W)+(X*Quat.X)+(Y*Quat.Y)-(Z*Quat.Z),
				//-++
				(W*Quat.W)-(X*Quat.X)+(Y*Quat.Y)+(Z*Quat.Z),
				//+-+
				(W*Quat.W)+(X*Quat.X)-(Y*Quat.Y)+(Z*Quat.Z));
		}
		inline Quaternion Quaternion::operator/(const Quaternion& Quat) const{
			return Quaternion();
		}
		//Quanterns (still in testing of functionality)
		inline Quaternion Quaternion::operator/(float const&num) const{
			return Quaternion(W/num,X/num,Y/num,Z/num);
		}
		inline Quaternion Quaternion::operator*(float const&num) const{
			Quaternion result;
			result.X=X * num;
			result.Y=Y * num;
			result.Z=Z * num;
			result.W=W * num;
			return result;
		}
		//
		inline void norm(Quaternion & rhs) {
			double n = sqrt(rhs.X*rhs.X + rhs.Y*rhs.Y + rhs.Z*rhs.Z + rhs.W*rhs.W);
			rhs.X /= n;
			rhs.Y /= n;
			rhs.Z /= n;
			rhs.W /= n;
		}
		//
		inline float dot(Quaternion const&lhs,Quaternion const&rhs){
			return lhs.X*rhs.X+lhs.Y*rhs.Y+lhs.Z*rhs.Z+rhs.W*rhs.W;
		}
		inline float lsq(Quaternion const&rhs){
			return dot(rhs,rhs);
		}
		inline float mag(Quaternion const &rhs){
			return sqrt(dot(rhs, rhs));
		}
		inline Quaternion norm(Quaternion const &lhs){
			return lhs * (1.0f /(mag(lhs)));
		}
		inline Quaternion rot(float const &lhs,Quaternion const &rhs){
			//rotation
			Quaternion temp(
				cos(lhs/2),
				rhs.X * sin( lhs/2 ),
				rhs.Y * sin( lhs/2 ),
				rhs.Z * sin( lhs/2 ));
			//use the overide multiplication
			return temp * rhs;
		}
		//Output display of values
		inline std::ostream& operator<< (std::ostream& os, const Quaternion& quat)
		{
			std::stringstream stream;
			stream << "X: " << quat.X << ", Y: " << quat.Y << ", Z: " << quat.Z << ", W: " << quat.W ;
			os.write(const_cast<char*>(stream.str().c_str()), static_cast<std::streamsize>(stream.str().size() * sizeof(char)) );
			return os;
		}
		/*
		inline Vector3 rotVec(Quaternion const &lhs,Vector3 const&rhs){
			Quaternion qtemp;
			qtemp.W = (-(lhs.X * rhs.X) - (lhs.Y * rhs.Y) - (lhs.Z * rhs.Z));
			qtemp.X = ( (lhs.W * rhs.X) + (lhs.Y * rhs.Z) - (lhs.Z * rhs.Y));
			qtemp.Y = ( (lhs.W * rhs.Y) - (lhs.X * rhs.Z) + (lhs.Z * rhs.X));
			qtemp.Z = ( (lhs.W * rhs.Z) + (lhs.X * rhs.Y) - (lhs.Y * rhs.X));

			return Vector3(((qtemp.Z * rhs.Y) - (qtemp.W * rhs.X) - (qtemp.Y * rhs.Z)),((qtemp.X * rhs.Z) - (qtemp.W * rhs.Y) - (qtemp.Z * rhs.X)), ((qtemp.Y * rhs.X) - (qtemp.W * rhs.Z) - (qtemp.X * rhs.Y)));
		}
		*/
	}
}

#endif /* QUATERNION_H_ */
