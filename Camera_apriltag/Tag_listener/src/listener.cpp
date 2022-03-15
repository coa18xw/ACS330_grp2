   #include "ros/ros.h"
   #include "std_msgs/String.h"
   #include "std_msgs/MultiArrayLayout.h"
   #include "std_msgs/MultiArrayDimension.h"
   #include "std_msgs/Int32MultiArray.h"

   #include "/home/uos/catkin_ws/devel/include/apriltag_ros/AprilTagDetectionArray.h"
   #include "lookup.h"
  
  
  
   void tag_detectionsCallback(const apriltag_ros::AprilTagDetectionArray::ConstPtr& msg)
// msg->detections[0].id to get

   {
	int counter=0;
	// 
	//ROS_INFO("Tag id:[%ld]" ,msg->detections[0].id);

	/*for(std::vector<apriltag_ros::AprilTagDetectionArray>::const_iterator it = id->detections.begin(); it != id->detections.end(); ++it) // iterator that moves memory sizes of<type>
	{
		Id[counter] = *it.detections.id;
		const char* Tag_IP = lookup(Id[counter]);
		ROS_INFO("Tag id: [%d]", &Id[counter]);
        	ROS_INFO("Tag ip: [%S]", &Tag_IP);
		counter++;
	}*/
	/*
	for(int i = 0; i>=sizeof(Id); i++)
	{
		Id[i] = msg->detections[i].id; //
		//const char* Tag_IP = lookup(Id[i]);
		ROS_INFO("Tag id: [%d]", &Id[i]);
        	//ROS_INFO("Tag ip: [%S]", &Tag_IP);
		i++;
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


