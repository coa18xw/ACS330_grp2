
// version 2 oop

#include <ros/ros.h>
#include <actionlib/server/simple_action_server.h>
#include <mm_actions/mmAction.h>
#include <unistd.h>

class MMAction
{
protected:

	ros::NodeHandle nh_;
	actionlib::SimpleActionServer<mm_actions::mmAction> as_; // NodeHandle instance must be created before this line. Otherwise strange error occurs.
	std::string mm_name_;
	// create messages that are used to published feedback/result
	mm_actions::mmFeedback feedback_;
	mm_actions::mmResult result_;

public:
MMAction(std::string mm_id) :
as_(nh_, mm_id, boost::bind(&MMAction::executeCB, this, _1), false), mm_name_(mm_id)
	{
		as_.start();
		ROS_INFO("%s: Activated", mm_id.c_str());
	}

~MMAction(void)
{
}
void executeCB(const mm_actions::mmGoalConstPtr &goal)
{
	ros::Rate r(1);
bool success = true;
feedback_.percent_complete = 0;

ROS_INFO("%s: Executing, Moving to %d,%d", mm_name_.c_str(), goal->location[0],goal->location[1]);
 // start executing the action
       for(int i=1; i<=100; i++)
      {
         // check that preempt has not been requested by the client
         if (as_.isPreemptRequested() || !ros::ok())
         {
           ROS_INFO("%s: Preempted", mm_name_.c_str());
           // set the action state to preempted
           as_.setPreempted();
           success = false;
           break;
        }
	//add code in here
	feedback_.percent_complete = i;
	ROS_INFO("%d %% ",i);
	as_.publishFeedback(feedback_);
	unsigned int microsecond = 1000000;
	usleep(0.05*microsecond); // sleeps for 0.05 seconds
	}
	if(success)
	{
	result_.complete = true;
	ROS_INFO("%s task completed", mm_name_.c_str());
	as_.setSucceeded(result_);	
	}

   }
};

 int main(int argc, char** argv)
 {
     ros::init(argc, argv, "mm2");
   
     //MMAction mm1("mm1");
     MMAction mm2("mm2");
     ros::spin();
   
     return 0;
   }
