#ifndef __RANDOM_H__
#define __RANDOM_H__

#define RANDOM(X) Random::next()%(int)X
#define RANDOM_SEED(X) Random::setSeed(X)

//USAGE
//RANDOM(100); // random number between 0 and 99
class Random
{
private:
	Random(void);

public:
	static void setSeed(long _seed);
	static int next();
	static long seed;
	static long multiplier;
	static long addend;
	static long mask;
};


#endif //__RANDOM_H__