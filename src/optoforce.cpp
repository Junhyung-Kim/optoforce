#include "optoforce/optoforce.h"

int main(int argc, char **argv)
{
  ros::init(argc, argv, "optoforce_node");
  ros::NodeHandle nh;

  Response r;
  SOCKET_HANDLE socketHandle;

  optoforceROS ft(nh);

  int i;

  if (ft.Connect(&socketHandle, "192.168.1.1" , PORT) != 0)
  {
    fprintf(stderr, "Could not connect to device...");
    return -1;
  }
  else
  {
    fprintf(stderr, "connect device!!!");
  }

  ft.SendCommand(&socketHandle, COMMAND_SPEED, SPEED);
  ft.SendCommand(&socketHandle, COMMAND_FILTER, FILTER);
  ft.SendCommand(&socketHandle, COMMAND_BIAS, BIASING_OFF);

  ft.SendCommand(&socketHandle, COMMAND_START, SAMPLE_COUNT);
  for (i = 0; i < SAMPLE_COUNT; ++i)
  {
    if (i == SAMPLE_COUNT / 2)
    {
      ft.SendCommand(&socketHandle, COMMAND_BIAS, BIASING_ON);
    }
    //r = ft.Receive(&socketHandle);
    ft.ShowResponse(r);
  }

  while(1)
  {
    ft.SendCommand(&socketHandle, COMMAND_START, 1);
    r = ft.Receive(&socketHandle);
    ft.ftPublish(r);
    ros::spinOnce();
  }

  ft.Close(&socketHandle);

  return 0;
}
