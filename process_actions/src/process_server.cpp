
// version 2 oop

#include <ros/ros.h>
#include <actionlib/server/simple_action_server.h>
#include <process_actions/processAction.h>
#include <unistd.h>

class ProcessAction
{
protected:

	ros::NodeHandle nh_;
	actionlib::SimpleActionServer<process_actions::processAction> as_; // NodeHandle instance must be created before this line. Otherwise strange error occurs.
	std::string station_name_;
	// create messages that are used to published feedback/result
	process_actions::processFeedback feedback_;
	process_actions::processResult result_;

public:
ProcessAction(std::string station_id) :
as_(nh_, station_id, boost::bind(&ProcessAction::executeCB, this, _1), false), station_name_(station_id)
	{
		as_.start();
		ROS_INFO("%s: Activated", station_id.c_str());
	}

~ProcessAction(void)
{
}
void executeCB(const process_actions::processGoalConstPtr &goal)
{
	ros::Rate r(1);
bool success = true;
feedback_.percent_complete = 0;

ROS_INFO("%s: Executing, processing block", goal->station_id.c_str());
 // start executing the action
       for(int i=1; i<=100; i++)
      {
         // check that preempt has not been requested by the client
         if (as_.isPreemptRequested() || !ros::ok())
         {
           ROS_INFO("%s: Preempted", goal->station_id.c_str());
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
	usleep(0.005*microsecond); // sleeps for 0.05 seconds
	}
	if(success)
	{
	result_.complete = true;
	ROS_INFO("%s task completed", goal->station_id.c_str());
	as_.setSucceeded(result_);	
	}

   }
};

 int main(int argc, char** argv)
 {
     ros::init(argc, argv, "process");
   
     ProcessAction process("process");
     ros::spin();
   
     return 0;
   }
