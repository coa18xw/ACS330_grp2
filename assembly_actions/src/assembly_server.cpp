
// version 2 oop

#include <ros/ros.h>
#include <actionlib/server/simple_action_server.h>
#include <assembly_actions/assemblyAction.h>
#include <unistd.h>

class AssemblyAction
{
protected:

	ros::NodeHandle nh_;
	actionlib::SimpleActionServer<assembly_actions::assemblyAction> as_; // NodeHandle instance must be created before this line. Otherwise strange error occurs.
	std::string station_name_;
	// create messages that are used to published feedback/result
	assembly_actions::assemblyFeedback feedback_;
	assembly_actions::assemblyResult result_;

public:
AssemblyAction(std::string station_id) :
as_(nh_, station_id, boost::bind(&AssemblyAction::executeCB, this, _1), false), station_name_(station_id)
	{
		as_.start();
		ROS_INFO("%s: Activated", station_id.c_str());
	}

~AssemblyAction(void)
{
}
void executeCB(const assembly_actions::assemblyGoalConstPtr &goal)
{
	ros::Rate r(1);
bool success = true;
feedback_.percent_complete = 0;

ROS_INFO("%s: Executing, processing block", goal->order[0].c_str());
 // start executing the action
       for(int i=1; i<=100; i++)
      {
         // check that preempt has not been requested by the client
         if (as_.isPreemptRequested() || !ros::ok())
         {
           ROS_INFO("%s: Preempted", goal->order[9].c_str());
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
	usleep(0.05*microsecond); // sleeps for 3 seconds
	}
	if(success)
	{
	result_.complete = true;
	ROS_INFO("%s task completed", goal->order[0].c_str());
	as_.setSucceeded(result_);	
	}

   }
};

 int main(int argc, char** argv)
 {
     ros::init(argc, argv, "assembly");
   
     AssemblyAction assembly("assembly");
     ros::spin();
   
     return 0;
}
