#include <ros/ros.h>
#include <actionlib/client/simple_action_client.h>
#include <low_level_controller/ll_client_serverAction.h>
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
ros::init(argc, argv, "ll_controller");

actionlib::SimpleActionClient<low_level_controller::ll_client_serverAction> ac("input", true);
boost::thread spin_thread(&spinThread);


//getting tasks from colour
char colour = 'r';
std::vector<std::string> tasks = col_to_tasks(colour);
//

//goal

ROS_INFO("Waiting for action server to start.");
ac.waitForServer(); //will wait for infinite time

ROS_INFO("Action server started, sending goal.");
low_level_controller::ll_client_serverGoal goal;

goal.task = tasks; //{"Heating","Cleaning","Cutting","MM1","MM2","Assembly"};
ac.sendGoal(goal);
bool finished_before_timeout = ac.waitForResult(ros::Duration(40.0));
if (finished_before_timeout)
{
actionlib::SimpleClientGoalState state = ac.getState();
ROS_INFO("Action finished: %s",state.toString().c_str());
}
else
ROS_INFO("Action did not finish before the time out.");

ros::spin();
return 0;
}
