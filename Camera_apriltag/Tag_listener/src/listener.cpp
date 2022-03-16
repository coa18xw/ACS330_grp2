   #include "ros/ros.h"
   #include "std_msgs/String.h"
   #include "std_msgs/MultiArrayLayout.h"
   #include "std_msgs/MultiArrayDimension.h"
   #include "std_msgs/Int32MultiArray.h"

   #include "apriltag_ros/AprilTagDetectionArray.h"
   #include "lookup.h"
  
   
   
   void tag_detectionsCallback(const apriltag_ros::AprilTagDetectionArray::ConstPtr& msg)
// msg->detections[i].id to get
	 {
	
	std::vector<int> Tag_ID[12];
	int counter =0;
	ROS_INFO("test = %d", msg->detections[0].id);
	ROS_INFO("test = %d", msg->detections[1].id);
	ROS_INFO("test = %d", msg->detections[2].id);
	ROS_INFO("test = %d", msg->detections[3].id);
	
/*
	for(int counter=0; counter>12; counter++)
		{
		
			
		Tag_ID[counter] = msg->detections[counter].id;
		const char* Tag_IP = lookup(Tag_ID[counter]);
		ROS_INFO("Tag id: [%d] ", &Tag_ID[counter]);
		ROS_INFO("Tag ip: [%S]", &Tag_IP);
			
		}
*/
/*
	for(std::vector<apriltag_ros::AprilTagDetectionArray>::const_iterator it = msg->detections.begin(); it != msg->detections.end(); ++it) // iterator that moves memory sizes of<type>
	{
		Tag_ID[counter] = *it.detections[counter].id;
		const char* Tag_IP = lookup(Tag_ID[counter]);
		ROS_INFO("Tag id: [%d] ", &Tag_ID[counter]);
        	ROS_INFO("Tag ip: [%S]", &Tag_IP);
		counter++;
	}
	*/
   	}
   
   int main(int argc, char **argv)
   {
     
     ros::init(argc, argv, "listener");
   
     
     ros::NodeHandle n;
   
     
     ros::Subscriber sub = n.subscribe("tag_detections", 1000, tag_detectionsCallback);
   
     
     ros::spin();
   
     return 0;
   }


