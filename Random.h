#ifndef RANDOMGEN_H
#define RANDOMGEN_H

#define RANDOM_MAX 2147483647

/*
Implementation of Park Miller High efficiency Random Generator. Adapted from 
"http://www.christianpinder.com/articles/pseudo-random-number-generation/"
*/

class RandomGen
{
public:
	RandomGen() {}
	inline static void SetSeed(unsigned int seed_);
	inline static unsigned int getnumber();
private:
	static unsigned int seed;
};

void RandomGen::SetSeed(unsigned int seed_)
{
	seed = seed_;
}

unsigned int RandomGen::getnumber()
{
	unsigned int hi, lo;

	hi = 16807 * (seed >> 16);
	lo = 16807 * (seed & 0xFFFF);
	lo += (hi & 0x7FFF) << 16;
	lo += hi >> 15;
	if (lo > 2147483647)
		lo -= 2147483647;
	seed = lo;

	return seed;
}
#endif