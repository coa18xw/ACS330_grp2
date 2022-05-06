   #include "ros/ros.h"
   #include "std_msgs/String.h"
   #include "std_msgs/MultiArrayLayout.h"
   #include "std_msgs/MultiArrayDimension.h"
   #include "std_msgs/Int32MultiArray.h"

  
   
   
   void outputResultCallback(const output_actions::outputResult::ConstPtr& msg)
// msg->detections[i].id to get
	 {
	
	if( msg->complete == true)
		{
		ROS_INFO("output task complete");
		}
					
	}
   
   int main(int argc, char **argv)
   {
     
     ros::init(argc, argv, "listener");
   
     
     ros::NodeHandle n;
   
     
     ros::Subscriber sub = n.subscribe("output/result", 1000, outputResultCallback);
   
     
     ros::spin();
   
     return 0;
   }


