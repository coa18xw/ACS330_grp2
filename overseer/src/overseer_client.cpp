#include <ros/ros.h>
#include <iostream>
#include <string>
#include <actionlib/client/simple_action_client.h>
#include <low_level_controller/ll_client_serverAction.h>
#include <low_level_controller/ll_client_server_outputAction.h>
#include <low_level_controller/ll_client_server_inputAction.h>
#include <actionlib/client/terminal_state.h>
#include <boost/thread.hpp>
#include <unistd.h>
#include <col_to_tasks.h>
#include <assembly_tasks.h>

void spinThread()
{
	ros::AsyncSpinner spinner(4); // Use 4 threads
	spinner.start();
	ros::waitForShutdown();
}

int main (int argc, char **argv)
{
	ros::init(argc, argv, "Overseer");

	actionlib::SimpleActionClient<low_level_controller::ll_client_serverAction> acI("input", true);
	actionlib::SimpleActionClient<low_level_controller::ll_client_serverAction> acO("output", true);
	char storageStr[16]={'.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.'};
	std::string location;
	int dot_pos;
	
while(ros::ok()){

	boost::thread spin_thread(&spinThread);
	low_level_controller::ll_client_serverGoal goal;

	bool finished_before_timeout_I;
	bool finished_before_timeout_O;
	char colour;
	bool full = true;
	std::string XY;


	unsigned int microsecond = 1000000;
	usleep(3*microsecond); // sleeps for 3 seconds

	//goal combined
	colour = 'r';

	for(int i = 0; i <=16;i++){
	if(storageStr[i] == '.')
	{
	dot_pos = i;
	full = false;
	i = 16;
	}
	else
	ROS_INFO("checking position %d", i+1);
	}
	if(full ==true)
	{
		std::string location = {"Full"};
		ROS_INFO("Storgae full");
		break;
	}
	storageStr[dot_pos]=colour;
	int temp = dot_pos*5;
	XY=std::to_string(temp) += ".14";
	location = {XY};
	
	

	std::vector<std::string> tasksI = col_to_tasks(colour,location);

	
	std::vector<std::string> tasksO = assembly_tasks("12.19");


	ROS_INFO("Sending Dual goals.");
	
	goal.task = tasksO; //{"Heating","Cleaning","Cutting","MM1","MM2","Assembly"};
	acO.sendGoal(goal);
	goal.task = tasksI; //{"Heating","Cleaning","Cutting","MM1","MM2","Assembly"};
	acI.sendGoal(goal);

	//may need to double up below
	finished_before_timeout_O = acO.waitForResult(ros::Duration(0.0));
	finished_before_timeout_I = acI.waitForResult(ros::Duration(0.0));
	if (finished_before_timeout_I&&finished_before_timeout_O)
	{
	actionlib::SimpleClientGoalState state_I = acI.getState();
	ROS_INFO("Action finished: %s",state_I.toString().c_str());
	actionlib::SimpleClientGoalState state_O = acO.getState();
	ROS_INFO("Action finished: %s",state_O.toString().c_str());
	}
	else
	ROS_INFO("Actions did not finish before the time out.");



	ros::AsyncSpinner spinner(4); // Use 2 threads
	spinner.start();
}
	//ros::waitForShutdown();
	
	return 0;
}


