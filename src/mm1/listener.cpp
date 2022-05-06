   #include "ros/ros.h"
   #include "std_msgs/String.h"
   #include "std_msgs/MultiArrayLayout.h"
   #include "std_msgs/MultiArrayDimension.h"
   #include "std_msgs/Int32MultiArray.h"

  
   
   
   void mm1ResultCallback(const mm_actions::mmResult::ConstPtr& msg)
// msg->detections[i].id to get
	 {
	
	if( msg->complete == true)
		{
		ROS_INFO("mm1 task complete");
		}
					
	}
   
   int main(int argc, char **argv)
   {
     
     ros::init(argc, argv, "listener");
   
     
     ros::NodeHandle n;
   
     
     ros::Subscriber sub = n.subscribe("mm1/result", 1000, mm1ResultCallback);
   
     
     ros::spin();
   
     return 0;
   }


