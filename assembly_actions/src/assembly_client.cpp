#include <ros/ros.h>
#include <actionlib/client/simple_action_client.h>
#include <assembly_actions/assemblyAction.h>
#include <actionlib/client/terminal_state.h>

int main (int argc, char **argv)
{
ros::init(argc, argv, "test_process");

actionlib::SimpleActionClient<assembly_actions::assemblyAction> ac("assembly", true);

ROS_INFO("Waiting for action server to start.");
ac.waitForServer(); //will wait for infinite time
ROS_INFO("Action server started, sending goal.");
assembly_actions::assemblyGoal goal;
goal.order[0] = "Heating";
ac.sendGoal(goal);
bool finished_before_timeout = ac.waitForResult(ros::Duration(30.0));
if (finished_before_timeout)
{
actionlib::SimpleClientGoalState state = ac.getState();
ROS_INFO("Action finished: %s",state.toString().c_str());
}
else
ROS_INFO("Action did not finish before the time out.");

return 0;
}
