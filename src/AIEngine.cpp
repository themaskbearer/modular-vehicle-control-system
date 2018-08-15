/*
 * AIEngine.cpp
 *
 *  Created on: Apr 1, 2012
 *      Author: jpollard
 */

#include "AIEngine.h"
#include "utils/DataLogger.h"
#include "utils/OperatorFunctions.h"
#include <cstdlib>
#include <cmath>

AIEngine::AIEngine(MemoryStorage* memories) :
    MovementController(memories)
{

}


AIEngine::~AIEngine()
{
}


VehicleCommand AIEngine::getCommandToExecute(const State& currentTarget, const State& currentState)
{
    DATA_LOGGER.recordData("\n-----------New iteration---------------");

    _currentMoveInitialState = currentState;
    _currentR = matrix::createRotationMatrix(_currentMoveInitialState._angPosition.yaw,
                                             _currentMoveInitialState._angPosition.roll,
                                             _currentMoveInitialState._angPosition.pitch);
    State poseDifference = currentTarget - currentState;
    logState("current pose: ", currentState);
    logState("target: ", currentTarget);
    logState("diff: ", poseDifference);

    _currentActingMemory = getBestMemory(poseDifference);
    DATA_LOGGER.recordData("chosen memory: " + _currentActingMemory->to_str());

    _currentMovePrediction = _currentActingMemory->_final - _currentActingMemory->_initial;
    correctPosition(_currentMovePrediction._displacement);
    logState("prediction: ", _currentMovePrediction);

    return _currentActingMemory->_command;
}


void AIEngine::processCommandResults(const State& finalState)
{
    State result = finalState - _currentMoveInitialState;
    logState("result", result);

    float movementError = compareStates(result, _currentMovePrediction);

    std::string logstring = "error= ";
    logstring = logstring + movementError;
    DATA_LOGGER.recordData(logstring);

//    if (movementError <= ideal && movementError > (0.5 * ideal))
//    {
//        _currentActingMemory->_confidence += 10;
//        if (_currentActingMemory->_confidence > 100)
//            _currentActingMemory->_confidence = 100;
//
//        DATA_LOGGER.recordData("memory correct");
//    }
//    else
//    {
//        Memory* Replacement = getBestMemory(result);
//        float newopt = compareStates(result, Replacement->_final - Replacement->_initial);
//
//        if (newopt > movementError)
//        {
//            Replacement->_confidence += 10;
//            if (Replacement->_confidence > 100)
//                Replacement->_confidence = 100;
//
//            _currentActingMemory->_confidence -= 10;
//            if (_currentActingMemory->_confidence < 0)
//                _currentActingMemory->_confidence = 0;
//
//            DATA_LOGGER.recordData("found better memory, adjusting");
//        }
//        else if (newopt <= movementError)
//        {
//            _currentActingMemory->_initial = _currentMoveInitialState;
//            _currentActingMemory->_final = finalState;
//            _currentActingMemory->_confidence -= 10;
//
//            if (_currentActingMemory->_confidence < 0)
//                _currentActingMemory->_confidence = 0;
//
//            DATA_LOGGER.recordData("Adjusting memory");
//        }
//    }
}


Memory* AIEngine::getBestMemory(const State& target)
{
    int seed = rand() % 100 / _memories->size();
    auto ReturnedMemory = _memories->begin();
    // TODO: Fix this ridiculousness
    for(int i = 0; i < seed - 1; i++)
        ReturnedMemory++;

    // Set initial pose error and memory
    float maxPoseError = evaluateMemory(*ReturnedMemory, target);

    // TODO: Fix this too
    for(auto iter = _memories->begin(); iter != _memories->end(); ++iter)
    {
        float poseError = evaluateMemory(*iter, target);
        if(poseError < maxPoseError && iter->_confidence >= ReturnedMemory->_confidence)
        {
            maxPoseError = poseError;
            ReturnedMemory = iter;
        }
    }

    return &(*ReturnedMemory);
}


float AIEngine::evaluateMemory(const Memory& memory, const State& target)
{
    State diff = memory._final - memory._initial;
    correctPosition(diff._displacement);

    float poseError = compareStates(diff, target);
    return poseError;
}


void AIEngine::correctPosition(AxesProjection& displacement)
{
    matrix::Matrix position;
    position.push_back(displacement.x);
    position.push_back(displacement.y);
    position.push_back(displacement.z);

    position = matrix::multiplyPosition(_currentR, position);

    displacement.x = position[0];
    displacement.y = position[1];
    displacement.z = position[2];
}


float AIEngine::compareStates(const State& state1, const State& state2)
{
    float error = std::sqrt(std::pow(state1._displacement.x - state2._displacement.x, 2) +
                            std::pow(state1._displacement.y - state2._displacement.y, 2) +
                            std::pow(state1._displacement.z - state2._displacement.z, 2) +
                            std::pow(state1._angPosition.yaw - state2._angPosition.yaw, 2) +
                            std::pow(state1._angPosition.pitch - state2._angPosition.pitch, 2) +
                            std::pow(state1._angPosition.roll - state2._angPosition.roll, 2) );

    return error;
}


void AIEngine::logState(const std::string& title, const State& state)
{
    std::string logstring = title + " ";

    logstring = logstring + state._displacement.x + " " + state._displacement.y + " " + state._displacement.z + " "
            + state._angPosition.roll + " " + state._angPosition.pitch + " " + state._angPosition.yaw;

    DATA_LOGGER.recordData(logstring);
}
