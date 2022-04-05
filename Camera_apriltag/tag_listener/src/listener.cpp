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
	if( msg->detections.empty() == false)
		{
			int counter =0;
			int32_t Tag_ID[12];
		
			while(msg->detections[counter].id[0] != NULL)
			{
				Tag_ID[counter] = msg->detections[counter].id[0];
				const char* Tag_IP = lookup(Tag_ID[counter]);
				ROS_INFO("Tag_ID = %ld", msg->detections[counter].id[0]);
				ROS_INFO("Tag_ID = %s",Tag_IP);
				counter++;
			}
		   
			
		}
	if( msg->detections.empty() == true)
		{
		ROS_INFO("No Tags detected");
		}
				/*ROS_INFO("test = %ld", msg->detections[0].id[0]);
				ROS_INFO("test = %ld", msg->detections[1].id[0]);
				ROS_INFO("test = %ld", msg->detections[2].id[0]);	
				ROS_INFO("test = %ld", msg->detections[3].id[0]);		
				ROS_INFO("test = %d",msg->detections[counter].pose.header.seq);
				//const char* Tag_IP = lookup(Tag_ID[counter]);
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


