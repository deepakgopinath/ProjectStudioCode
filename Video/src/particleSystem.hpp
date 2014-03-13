#ifndef __PARTICLE_SYSTEM_HPP
#define __PARTICLE_SYSTEM_HPP
#include<string>
#include "Stringifiable.hpp"
#ifndef EPS 
#define EPS 1e-7
#endif
template<class T>
class VecType: public Stringifiable{
public:
	T x;
	T y;
	T z;
	VecType(){
		x=0;
		y=0;
		z=0;
	}
	VecType(T x, T y, T z=0){
		this->x=x;
		this->y=y;
		this->z=z;
	}
	VecType<T> operator+(const VecType<T> &rhs){
		return	VecType<T>(x+rhs.x, y+rhs.y, z+ rhs.z); 
	}
	VecType<T>& operator+=(const VecType<T> &rhs){
		x+= rhs.x;
		y+= rhs.y;
		z+= rhs.z;
		return *this;
	}
	VecType<T> operator-(const VecType<T> &rhs){
		return VecType<T>(x- rhs.x, y- rhs.y, z-rhs.z);
	}
	VecType<T>& operator-=(const VecType<T> &rhs){
		x-= rhs.x;
		y-= rhs.y;
		z-= rhs.z;
		return *this; 
	}
	VecType<T> operator-(){
		return VecType<T>(-x,-y,-z);
	}
	VecType<T> operator*(const VecType<T> & rhs){
		return VecType<T>(x* rhs.x, y*rhs.y, z*rhs.z);	
	}
	VecType<T>& operator*=(const VecType<T> &rhs){
		x*= rhs.x;
		y*= rhs.y;
		z*= rhs.z;
		return *this;	
	}
	VecType<T> operator/(const VecType<T> &rhs){
		return VecType<T>( x/rhs.x, y/rhs.y, z/rhs.z);
	}
	VecType<T>& operator/=(const VecType<T> &rhs){
		x/= rhs.x;
		y/= rhs.y;
		z/= rhs.z;
	}
	VecType<T> operator*(const T &rhs){
		return VecType<T> ( x*rhs, y*rhs, z* rhs);
	}
	VecType<T>& operator*=(const T &rhs){

		x*=rhs;
		y*=rhs;
		z*=rhs;
		return *this;
	}
	VecType<T> operator/(const T& rhs){
		return VecType<T> (x/rhs, y/rhs, z/rhs);
	}
	VecType<T>& operator/=(const T& rhs){
		x/= rhs;
		y/= rhs;
		z/= rhs;
		return *this;
	}
	T getLength(){
		return sqrt(x*x+ y*y+ z*z);
	}
	T getSquareLength(){
		return x*x+ y*y+ z*z;	
	}
	VecType<T> getNormalized(){
		T length= getLength();
		return (*this)/(length+EPS);
	}
	VecType<T>& normalize(){
		(*this)/= getLength()+EPS;	
	}
	std::string toString() const override{
		return "("+std::to_string(x)+","+std::to_string(y)+","+std::to_string(z)+")";
	}
};
template<class T>
	VecType<T> operator* (const T &lhs, const VecType<T> &rhs){
		return  VecType<T>(lhs* rhs.x, lhs* rhs.y, lhs* rhs.z);
	}

template<class T>
class Particle{
	public: 
		VecType<T> position;
		VecType<T> velocity;
		VecType<T> acceleration;
		VecType<T> force;
		T mass;
		Particle(){
			mass=1;
		}
		void applyForce(const VecType<T> &force){
			this->force+= force;
		}
		
		/*
			update using Verlet Integration
		*/
		void update(unsigned long delta){
			float deltaInSecond= delta/1000.f;	
			position+= velocity* deltaInSecond+ 0.5f* acceleration* deltaInSecond* deltaInSecond;	
			velocity+= acceleration* deltaInSecond*0.5f;
			acceleration= force/mass;
			velocity+= acceleration* deltaInSecond*0.5f;
			force=VecType<T> ();
		}
};

template<class T>
class Spring{
	public:
		T dampling;
		T stiffness;		
		Particle<T> *end1;
		Particle<T> *end2;
		T length;
		Spring(Particle<T> *end1, Particle<T> *end2, T dampling, T stiffness,T length){
			this->end1= end1;
			this->end2= end2;
			this->dampling= dampling;
			this->stiffness=stiffness;
			this->length=length;
		}
		void applyForce(){
				VecType<T> diff= (end1->position -end2->position);
				
				VecType<T> force= stiffness*(diff.getLength()-length)*diff.getNormalized();
				end1->applyForce(-force);
				end2->applyForce(force);
				//damping
				end1->applyForce(-end1->velocity);
				end2->applyForce(-end2->velocity);
		}
};

template<class T>
class ParticleSystem{

};
#endif
