#ifndef MATHUTIL_H
#define MATHUTIL_H
#include "mathmanager.h"

#define db_spl(_a) 10*log10(_a)
#define db_20(_a)  20*log10(_a)
#define squared(_a) _a*_a


Sample absComplex(const ComplexSample sample);
Sample hz2mel(const Sample f);
Sample mel2Hz(const Sample mel);
void Normalize(Frame& frame);
void Normalize(FrameCollection& frames);
Sample max(const FrameCollection& frames);
void ln(Frame& frame);
void inv(Frame& frame);
void square(Frame& frame);
void db20(Frame& frame);
int minPos(const Frame& frame, const int begin, const int end);
int maxPos(const Frame& frame, const int begin, const int end);
#endif // MATHUTIL_H
