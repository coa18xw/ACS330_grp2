#include <ros/ros.h>
#include <actionlib/client/simple_action_client.h>
#include <low_level_controller/ll_client_serverAction.h>
#include <low_level_controller/ll_client_server_outputAction.h>
#include <low_level_controller/ll_client_server_inputAction.h>
#include <actionlib/client/terminal_state.h>
#include <boost/thread.hpp>
#include <unistd.h>
#include <col_to_tasks.h>

void spinThread()
{
	ros::AsyncSpinner spinner(4); // Use 2 threads
	spinner.start();
	ros::waitForShutdown();
}

int main (int argc, char **argv)
{
	ros::init(argc, argv, "Overseer");

	actionlib::SimpleActionClient<low_level_controller::ll_client_serverAction> acI("input", true);
	actionlib::SimpleActionClient<low_level_controller::ll_client_serverAction> acO("output", true);
//while(ros::ok())

	boost::thread spin_thread(&spinThread);
	ROS_INFO("Action server started, sending goal.");
	low_level_controller::ll_client_serverGoal goal;

//stopping by sending null task
	ROS_INFO("Waiting for action server to start.");
	acI.waitForServer(); //will wait for infinite time
        acO.waitForServer(); //will wait for infinite time

	ROS_INFO("Sending Dual goals.");
	//low_level_controller::ll_client_serverGoal goal;

	goal.task = {""};
	acO.sendGoal(goal);
	goal.task = {""};
	acI.sendGoal(goal);

	//may need to double up below
	bool finished_before_timeout = acO.waitForResult(ros::Duration(0.0));
	if (finished_before_timeout)
	{
	actionlib::SimpleClientGoalState state = acO.getState();
	ROS_INFO("Action finished: %s",state.toString().c_str());
	}
	else
	ROS_INFO("Action did not finish before the time out.");
	

	//
	unsigned int microsecond = 1000000;
	usleep(3*microsecond); // sleeps for 3 seconds

	ros::AsyncSpinner spinner(4); // Use 2 threads
	spinner.start();

	//ros::waitForShutdown();
	return 0;
}


