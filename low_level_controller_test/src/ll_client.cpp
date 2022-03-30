#include <ros/ros.h>
#include <actionlib/client/simple_action_client.h>
#include <actionlib/client/terminal_state.h>
#include </home/coa19jwr/catkin_ws/devel/include/process_actions/processAction.h>
#include <boost/thread.hpp>

void spinThread()
{
	ros::spin();
}

int main (int argc, char **argv)
{
ros::init(argc, argv, "test_process");

actionlib::SimpleActionClient<process_actions::processAction> ac("process", true);
boost::thread spin_thread(&spinThread);

ROS_INFO("Waiting for action server to start.");
ac.waitForServer(); //will wait for infinite time
ROS_INFO("Action server started, sending goal.");
process_actions::processGoal goal;
goal.station_id = "Heating";
ac.sendGoal(goal);
bool finished_before_timeout = ac.waitForResult(ros::Duration(30.0));
if (finished_before_timeout)
{
actionlib::SimpleClientGoalState state = ac.getState();
ROS_INFO("Action finished: %s",state.toString().c_str());
}
else
ROS_INFO("Action did not finish before the time out.");

// shutdown node and rejoin thread before exit
ros::shutdown();
spin_thread.join();


return 0;
}
