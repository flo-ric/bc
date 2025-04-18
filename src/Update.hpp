#ifndef UPDATE_HPP
#define UPDATE_HPP

#include <iostream>
#include <vector>
#include <string>
#include "Message.hpp"
#include "Network.hpp"
#include "SimulationModel.hpp"

class Update
{
 public:
  
  Update();
  ~Update();
  static void UpdateNetwork(SimulationModel* aModel, Network* aNet, OperatingMode::Mode aMode);
  static void WaitingScenario(Network* aNet, bool* abEnd);
  
private:
  
};

#endif
