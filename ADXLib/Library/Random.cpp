#include "Random.h"
#include<Windows.h>

bool Random::GetHit(int all, int win) {

	return ((rand() % all) < win);
}

float Random::GetProb(int all, int win) {

	return win / all;
}
