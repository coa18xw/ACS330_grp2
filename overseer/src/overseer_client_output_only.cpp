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


	//getting tasks from colour
	char colour = 'r';
	std::vector<std::string> tasks = col_to_tasks(colour);
	//

	//goal

	ROS_INFO("Waiting for action server to start.");
	acI.waitForServer(); //will wait for infinite time

	ROS_INFO("Action server started, sending goal.");
	low_level_controller::ll_client_serverGoal goal;

	goal.task = tasks; //{"Heating","Cleaning","Cutting","MM1","MM2","Assembly"};
	acI.sendGoal(goal);
	bool finished_before_timeout = acI.waitForResult(ros::Duration(1000000.0));
	if (finished_before_timeout)
	{
	actionlib::SimpleClientGoalState state = acI.getState();
	ROS_INFO("Action finished: %s",state.toString().c_str());
	}
	else
	ROS_INFO("Action did not finish before the time out.");



	//getting tasks from colour
	colour = 'b';
	tasks = col_to_tasks(colour);
	//
/*
	//goal2

	ROS_INFO("Waiting for action server to start.");
	acO.waitForServer(); //will wait for infinite time

	ROS_INFO("Action server started, sending goal.");
	//low_level_controller::ll_client_serverGoal goal;

	goal.task = tasks; //{"Heating","Cleaning","Cutting","MM1","MM2","Assembly"};
	acO.sendGoal(goal);
	finished_before_timeout = acO.waitForResult(ros::Duration(0.0));
	if (finished_before_timeout)
	{
	actionlib::SimpleClientGoalState state = acO.getState();
	ROS_INFO("Action finished: %s",state.toString().c_str());
	}
	else
	ROS_INFO("Action did not finish before the time out.");
*/

		unsigned int microsecond = 1000000;
		usleep(3*microsecond); // sleeps for 3 seconds

	//goal combined
	colour = 'b';
	std::vector<std::string> tasksI = col_to_tasks(colour);
	colour = 'o';
	std::vector<std::string> tasksO = col_to_tasks(colour);


	ROS_INFO("Sending Dual goals.");
	//low_level_controller::ll_client_serverGoal goal;

	goal.task = tasksO; //{"Heating","Cleaning","Cutting","MM1","MM2","Assembly"};
	acO.sendGoal(goal);
	goal.task = tasksI; //{"Heating","Cleaning","Cutting","MM1","MM2","Assembly"};
	acI.sendGoal(goal);

	//may need to double up below
	finished_before_timeout = acO.waitForResult(ros::Duration(0.0));
	if (finished_before_timeout)
	{
	actionlib::SimpleClientGoalState state = acO.getState();
	ROS_INFO("Action finished: %s",state.toString().c_str());
	}
	else
	ROS_INFO("Action did not finish before the time out.");
	//output
	goal.task = tasksO; //{"Heating","Cleaning","Cutting","MM1","MM2","Assembly"};
	acO.sendGoal(goal);

	//may need to double up below
	finished_before_timeout = acO.waitForResult(ros::Duration(0.0));
	if (finished_before_timeout)
	{
	actionlib::SimpleClientGoalState state = acO.getState();
	ROS_INFO("Action finished: %s",state.toString().c_str());
	}
	else
	ROS_INFO("Action did not finish before the time out.");

	//
	usleep(3*microsecond); // sleeps for 3 seconds

	ros::AsyncSpinner spinner(4); // Use 2 threads
	spinner.start();

	//ros::waitForShutdown();
	return 0;
}


