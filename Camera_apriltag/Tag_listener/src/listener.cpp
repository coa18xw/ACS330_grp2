   #include "ros/ros.h"
   #include "std_msgs/String.h"
   #include "std_msgs/MultiArrayLayout.h"
   #include "std_msgs/MultiArrayDimension.h"
   #include "std_msgs/Int32MultiArray.h"
   #include "lookup.h"
  
  int Id[2];
  
   void tag_detectionsCallback(const std_msgs::Int32MultiArray::ConstPtr& id)
   {
	
	for(int i = 0; i>=sizeof(Id); i++)
	{
		Id[i] = *id[i];
		const char* Tag_IP = lookup(Id[i]);
		ROS_INFO("Tag id: [%d]", &Id[i]);
        	ROS_INFO("Tag ip: [%S]", &Tag_IP);
		i++;
	}
	return;
   }
   
   int main(int argc, char **argv)
   {
     
     ros::init(argc, argv, "listener");
   
     
     ros::NodeHandle n;
   
     
     ros::Subscriber sub = n.subscribe("tag_detections", 1000, tag_detectionsCallback);
   
     
     ros::spin();
   
     return 0;
   }


