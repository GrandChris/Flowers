///////////////////////////////////////////////////////////////////////////////
// File: Flower.h
// Date: 06.03.2020
// Version: 1
// Author: Christian Steinbrecher
// Description: Rules which leads to the evolvement of a flower.
///////////////////////////////////////////////////////////////////////////////


#pragma once


class Flower
{
public:
	using TEnergy = char;

	struct Neighbours
	{
		Flower* front;
		Flower* back;
		Flower* right;
		Flower* left;
		Flower* up;
		Flower* down;
	};


	void changeState(Neighbours const& neighbours, float const randomNumber);

	void setAlive(bool const isAlive);
	void setEnergy(TEnergy const energy);
	TEnergy getEnergy() const;

	unsigned char getColor() const;
		
private:
	TEnergy mEnergy = 0;

	bool mIsAlive = false;
	bool mHasSunlight = false;

	int getExchangedEnergy(Flower const& neighbour);
};


// #######+++++++ Implementation +++++++#######

#include <compare>
#include <cmath>

void Flower::changeState(Neighbours const & neighbours, float const randomNumber)
{
	int energy = 0; ;
	energy += getExchangedEnergy(*neighbours.front);
	energy += getExchangedEnergy(*neighbours.back);
	energy += getExchangedEnergy(*neighbours.left);
	energy += getExchangedEnergy(*neighbours.right);
	energy += getExchangedEnergy(*neighbours.up);
	energy += getExchangedEnergy(*neighbours.down);

	mEnergy += mIsAlive * static_cast<TEnergy>(energy);;
}

inline void Flower::setAlive(bool const isAlive)
{
	mIsAlive = isAlive;
}

inline void Flower::setEnergy(TEnergy const energy)
{
	mEnergy = energy;
}

inline Flower::TEnergy Flower::getEnergy() const
{
	return mEnergy;
}

inline unsigned char Flower::getColor() const
{
	return static_cast<unsigned char>(mEnergy);
}

//inline float Flower::getExchangedEnergy(Flower const& neighbour)
//{
//	if (neighbour.mIsAlive)
//	{
//		float const energy = static_cast<float>(mEnergy);
//		float const otherEnergy = static_cast<float>(neighbour.mEnergy);
//		float const energyDiff = otherEnergy - energy;
//
//
//		float const exchangeRate = 1/5.0f;
//
//		float const additionalEnergy = energyDiff * exchangeRate;
//
//		return additionalEnergy;
//	}
//
//	return 0;
//}


//template<typename T>
//constexpr int signum(T const& left, T const& right)
//{
//	auto const order = left <=> right;
//	return ((order > 0) - (order < 0));
//}


inline int Flower::getExchangedEnergy(Flower const& neighbour)
{
	int order = (neighbour.mEnergy > 0) - (mEnergy > 0);

	return neighbour.mIsAlive * order;
	//return neighbour.mIsAlive * signum(neighbour.mEnergy, mEnergy);
}


//inline size_t Flower::Neighbours::getEnergySum() const
//{
//	return size_t() + front.mEnergy + back.mEnergy + left.mEnergy + right.mEnergy + up.mEnergy + down.mEnergy;
//}