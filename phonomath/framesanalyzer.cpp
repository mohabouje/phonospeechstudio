#include "framesanalyzer.h"
#include <QDebug>
FramesAnalyzer::FramesAnalyzer()
{

}

Frame FramesAnalyzer::applyForFrame(const FrameCollection &input, MathAlgorithm *algorithm)
{
    const int size = input.size();
    Frame outputData(size);
    for (int i=0; i<size; i++) {
        algorithm->setInputData(input[i]);
        algorithm->exec();
        outputData[i] = algorithm->outputSample();
    }
    return outputData;
}

FrameCollection FramesAnalyzer::applyForFrameCollection(const FrameCollection &input, MathAlgorithm *algorithm) {

    const int size = input.size();
    FrameCollection outputData(size, Frame(input[0].size()));
    for (int i=0; i<size; i++) {
        algorithm->setInputData(input[i]);
        algorithm->exec();
        outputData[i] = algorithm->outputFrame();
        for (int j=0; j<input[i].size(); j++) {
            //qDebug() << j << outputData[i][j];
        }
    }
    return outputData;
}
