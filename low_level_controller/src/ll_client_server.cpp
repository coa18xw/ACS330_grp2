
#include <ros/ros.h>
#include <actionlib/server/simple_action_server.h>
#include <actionlib/client/simple_action_client.h>
#include <low_level_controller/ll_client_serverAction.h>
#include <actionlib/client/terminal_state.h>
#include <process_actions/processAction.h>
#include <boost/thread.hpp>
#include <unistd.h>


void spinThread()
{
	ros::spin();
}


class LLController
{
protected:

	ros::NodeHandle nh_;
	actionlib::SimpleActionServer<low_level_controller::ll_client_serverAction> as_; // NodeHandle instance must be created before this line. Otherwise strange error occurs.
	std::string controller_name_;
	// create messages that are used to published feedback/result
	low_level_controller::ll_client_serverFeedback feedback_;
	low_level_controller::ll_client_serverResult result_;

public:
LLController(std::string controller_id, int argc,char** argv) :
as_(nh_, controller_id, boost::bind(&LLController::executeCB, this, _1), false), controller_name_(controller_id)
	{
		as_.start();
		ROS_INFO("Activated");
		ros::init(argc, argv, "process");
	}

~LLController(void)
{
}
void executeCB(const low_level_controller::ll_client_serverGoalConstPtr &goal)
{
	ros::Rate r(1);
bool success = true;
int i =0;
if(goal->task == "Heating")
	{

actionlib::SimpleActionClient<process_actions::processAction> ac("process", true);
boost::thread spin_thread(&spinThread);
		ROS_INFO("Action server started, sending goal : heating");
		process_actions::processGoal goal;
		goal.station_id = "Heating";
		ac.sendGoal(goal);
		bool finished_before_timeout = ac.waitForResult(ros::Duration(30.0)); // 0 = infinite timeout
		if (finished_before_timeout)
		{
		actionlib::SimpleClientGoalState state = ac.getState();
		ROS_INFO("Action finished: %s",state.toString().c_str());
		}
		else
		ROS_INFO("Action did not finish before the time out.");

		ros::shutdown();
		spin_thread.join();
	}

ROS_INFO("Tasks Executing");
 // start executing the action
	if(success)
	{
	result_.complete = true;
	ROS_INFO("Complete");
	as_.setSucceeded(result_);	
	}

   }
};



 int main(int argc, char** argv)
 {
     ros::init(argc, argv, "input");
   
     LLController ll_controller("input",argc,argv);
     ros::spin();
   
     return 0;
   }
