#ifndef SCOREHPP
#define SCOREHPP

#include <cmath>

const int BETTER = 1;
const int EQUIVALENT = 0;
const int WORSE = -1;

class score_t
{
private:
  double p;
  double r;
  double ratio() { return r == 0 ? DBL_MAX : std::abs(p / r - 1); }

public:
  score_t(double p, double r)
  {
    this->p = p;
    this->r = r;
  }
  double precision() { return p; }
  double recall() { return r; }
  int compare(score_t score) { return (ratio() < score.ratio()) ? BETTER : (ratio() > score.ratio()) ? WORSE : EQUIVALENT; }
};

#endif