#include <ros/ros.h>
#include <actionlib/client/simple_action_client.h>
#include <mm_actions/mmAction.h>
#include <actionlib/client/terminal_state.h>

int main (int argc, char **argv)
{
ros::init(argc, argv, "test_mm");

actionlib::SimpleActionClient<mm_actions::mmAction> ac("mm1", true);

ROS_INFO("Waiting for action server to start.");
ac.waitForServer(); //will wait for infinite time
ROS_INFO("Action server started, sending goal.");
mm_actions::mmGoal goal;
goal.location = {12,14};
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
