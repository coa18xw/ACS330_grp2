#include <ros/ros.h>
#include <actionlib/server/simple_action_server.h>
#include <process_actions/processAction.h>
#include <actionlib/client/terminal_state.h>

int main (int argc, char **argv)
{
ros::init(argc, argv "test_process");
actionlib::SimpleActionClient<process_actions::processAction> ac("heating", true);

ROS_INFO("Waiting for action server to start.");
ac.waitForServer(); //will wait for infinite time
ROS_INFO("Action server started, sending goal.");
process_actions::processGoal goal;
goal.station_id = Heating;
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
