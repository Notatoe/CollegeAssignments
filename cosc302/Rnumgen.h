#ifndef __RNUMGEN_H__
#define __RNUMGEN_H__

#include <stdlib.h>
#include <vector>

class rnumgen {
  public:
    rnumgen(int seedvalue,vector<int> &vec);
    int rand() const;

  private:
	vector<float> v;
};

#endif
