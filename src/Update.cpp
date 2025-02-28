#include <thread>
#include "Update.hpp"

Update::Update()
{
}

Update::~Update()
{    
}

static void TaskNetwork(SimulationModel* aModel, Network* aNet, OperatingMode::Mode aMode)
{
  eCmdMsg msgType;
  void* dataCmd = NULL;
  Message inMsg(aModel), outMsg(aModel);

  while(true)
    {
      msgType= E_CMD_MESSAGE_UNKNOWN;
      aNet->WaitMessage(inMsg, msgType, &dataCmd);
      aModel->updateFromNetwork(msgType, dataCmd);	  

      if(OperatingMode::Secondary == aMode)
	{
	  std::string msgCtrlOv = outMsg.ControlOverride();
	  aNet->SendMessage(msgCtrlOv);
	}
      else if(OperatingMode::Multiplayer == aMode)
	{
	  std::string msgMpFeedBack = outMsg.MpFeedBack();
	  aNet->SendMessage(msgMpFeedBack);
	}
      else
	{
	  if(aModel->getLoopNumber() % 100 == 0)
	    {
	      std::string msgKeepAliveScn = aModel->getSerialisedScenario();
	      aNet->SendMessage(msgKeepAliveScn, true);
	    }
	  else if(aModel->getLoopNumber() % 2 == 0)
	    {
	      std::string msgKeepAlive = outMsg.KeepAlive();
	      aNet->SendMessage(msgKeepAlive);
	    }
	  /*else
	    {
	    std::string msgKeepAliveShort = outMsg.KeepAliveShort();      
	    aNet->SendMessage(msgKeepAliveShort);
	    }  */  
	}
    }
}




void Update::UpdateNetwork(SimulationModel* aModel, Network* aNet, OperatingMode::Mode aMode)
{
  std::cout << "Creating thread :: Launch Enet Network" << std::endl;
  std::thread taskNet(TaskNetwork, aModel, aNet, aMode);

  taskNet.detach();
 
}	  
