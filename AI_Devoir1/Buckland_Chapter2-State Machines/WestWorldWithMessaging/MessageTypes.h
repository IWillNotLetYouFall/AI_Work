#ifndef MESSAGE_TYPES
#define MESSAGE_TYPES

#include <string>

enum message_type
{
  Msg_HiHoneyImHome,
  Msg_StewReady,
  Msg_Annoyance,
  Msg_Boast,
  Msg_Enter
};


inline std::string MsgToStr(int msg)
{
  switch (msg)
  {
  case 0:
    
    return "HiHoneyImHome"; 

  case 1:
    
    return "StewReady";

  case 2:

	return "ComeDownHereBoy";

  case 3:

	  return "ImTheBest";

  case 4:

	  return "ImHere";

  default:

    return "Not recognized!";
  }
}

#endif