/*

//vesion 1 functional

#include <ros/ros.h>
#include <actionlib/server/simple_action_server.h>
#include <process_actions/processAction.h>

typedef actionlib::SimpleActionServer<process_actions::processAction> Server;

void execute(const process_actions::processGoalConstPtr& goal, Server* as)
{
	//insert code for action here
	ROS_INFO("starting %d",&goal->station_id);
	std::this_thread::sleep_for(std::chrono::milliseconds(1500));
	ROS_INFO("completed %d",&goal->station_id);
	as->setSucceded();
}

int main(int argc, argv, "process_station_action")
{
	ros::init(argc, argv, "process_station_action")
	ros::NodeHandle n;
	Server server(n, "process_station_action", boost::bind(&execute, _1, &server), false);
	server.start();
	ros::spin();
	return 0;
}

*/


// version 2 oop

#include <ros/ros.h>
#include <actionlib/server/simple_action_server.h>
#include <process_actions/processAction.h>

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
	}

~ProcessAction(void)
{
}
void executeCB(const process_actions::processGoalConstPtr &goal)
{
	ros::Rate r(1);
bool success = true;
feedback_.percent_complete = 0;

ROS_INFO("%s: Executing, processing block", station_name_);
 // start executing the action
       for(int32_t i=1; i<=100; i++)
       {
         // check that preempt has not been requested by the client
         if (as_.isPreemptRequested() || !ros::ok())
         {
           ROS_INFO("%s: Preempted", station_name_.c_str());
           // set the action state to preempted
           as_.setPreempted();
           success = false;
           break;
        }
	feedback_ = i;
	as_.publishFeedback(feedback_);
	r.sleep();
	}
	if(success)
	{
	result_ = true;
	ROS_INFO("%s task completed");
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
