#include "mathalgorithm.h"
#include <QDebug>
MathAlgorithm::MathAlgorithm() {

}

void MathAlgorithm::exec() {
    if (!_initialized)
        return;
    preProcessing();
    processing();
    postProcessing();
}
