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

  while(ros::ok())
  {
    ft.SendCommand(&socketHandle, COMMAND_START, SAMPLE_COUNT);
    for (i = 0; i < SAMPLE_COUNT; ++i)
    {
      if (i == SAMPLE_COUNT / 2)
      {
        ft.SendCommand(&socketHandle, COMMAND_BIAS, BIASING_ON);
      }
      r = ft.Receive(&socketHandle);
    }
    ft.ftPublish(r);
    ros::spinOnce();
  }

  ft.Close(&socketHandle);

  return 0;
}








/*


int main(int argc, char **argv)
{
  ros::init(argc, argv, "optoforce_node");
  ros::NodeHandle nh;

  Response r;
  unsigned int i;
  SOCKET_HANDLE socketHandle;

  //optoforce_pub_.init(nh, "/optoforce/ftsensor",3);

  if (Connect(&socketHandle, "192.168.1.1" , PORT) != 0)
  {
    fprintf(stderr, "Could not connect to device...");
    return -1;
  }
  else
  {
    fprintf(stderr, "connect device!!!");

  }

  SendCommand(&socketHandle, COMMAND_SPEED, SPEED);
  SendCommand(&socketHandle, COMMAND_FILTER, FILTER);
  SendCommand(&socketHandle, COMMAND_BIAS, BIASING_OFF);

  while(1)
  {
    SendCommand(&socketHandle, COMMAND_START, SAMPLE_COUNT);
    for (i = 0; i < SAMPLE_COUNT; ++i)
    {
      if (i == SAMPLE_COUNT / 2)
      {
        SendCommand(&socketHandle, COMMAND_BIAS, BIASING_ON);
      }
      r = Receive(&socketHandle);
      ShowResponse(r);
    }
  }
  Close(&socketHandle);


  ros::spin();

  return 0;
}*/
