
#include <ros/ros.h>
#include <actionlib/server/simple_action_server.h>
#include <actionlib/client/simple_action_client.h>
#include <low_level_controller/ll_client_server_v2Action.h>
#include <actionlib/client/terminal_state.h>
#include <process_actions/processAction.h>
#include <assembly_actions/assemblyAction.h>
#include <boost/thread.hpp>
#include <unistd.h>



void spinThread()
{
	ros::AsyncSpinner spinner(4); // Use 2 threads
	spinner.start();
	ros::waitForShutdown();
}


class LLController
{
protected:

	ros::NodeHandle nh_;
	actionlib::SimpleActionServer<low_level_controller::ll_client_server_v2Action> as_; // NodeHandle instance must be created before this line. Otherwise strange error occurs.
	std::string controller_name_;
	// create messages that are used to published feedback/result
	low_level_controller::ll_client_server_v2Feedback feedback_;
	low_level_controller::ll_client_server_v2Result result_;

public:
LLController(std::string controller_id, int argc,char** argv) :
as_(nh_, controller_id, boost::bind(&LLController::executeCB, this, _1), false), controller_name_(controller_id)
	{
		as_.start();
		ROS_INFO("%s activated",controller_id.c_str());
		ros::init(argc, argv, "process");
	}

~LLController(void)
{
}
void executeCB(const low_level_controller::ll_client_server_v2GoalConstPtr &goal)
 {
//llserver
	bool success = true;
	
	int32_t size = sizeof(goal->task);
	
	//spin
	boost::thread spin_thread(&spinThread);
	int i = 0;
	while(goal->task[i].c_str() != NULL)
  {
	//temp variables for build
//excecuting called action
	//action client stuff
		
		//process stations
				if(goal->task[i] == "Heating"||goal->task[i]  == "Cleaning"||goal->task[i]  == "Cutting")
				{
					
					actionlib::SimpleActionClient<process_actions::processAction> ac("process", true);
					boost::thread spin_thread(&spinThread);
					ROS_INFO("Waiting for action server to start.");
					ac.waitForServer(); //will wait for infinite time
					//
					ROS_INFO("Action server started, sending goal : %s",goal->task[i].c_str());
					process_actions::processGoal Goal;
					Goal.station_id = goal->task[i].c_str();


					ac.sendGoal(Goal);
					bool finished_before_timeout = ac.waitForResult(ros::Duration(30.0)); // 0 = infinite timeout
					if (finished_before_timeout)
					{
					actionlib::SimpleClientGoalState state = ac.getState();
					ROS_INFO("Action finished: %s",state.toString().c_str());
					}
					else
					ROS_INFO("Action did not finish before the time out.");
				}

				
		//moblie platforms placeholders will do a task per location they need to go to
				else if(goal->task[i]  == "MM1"||goal->task[i]  == "MM2")
				{
					actionlib::SimpleActionClient<process_actions::processAction> ac("process", true);
					boost::thread spin_thread(&spinThread);
					ROS_INFO("Waiting for action server to start.");
					ac.waitForServer(); //will wait for infinite time
					//
					ROS_INFO("Action server started, sending goal : %s",goal->task[i].c_str());
					process_actions::processGoal Goal;


					ac.sendGoal(Goal);
					bool finished_before_timeout = ac.waitForResult(ros::Duration(30.0)); // 0 = infinite timeout
					if (finished_before_timeout)
					{
					actionlib::SimpleClientGoalState state = ac.getState();
					ROS_INFO("Action finished: %s",state.toString().c_str());
					}
					else
					ROS_INFO("Action did not finish before the time out.");
				}
		//Assembly stations
				else if(goal->task[i]  == "Assembly")
				{
					actionlib::SimpleActionClient<assembly_actions::assemblyAction> ac("assembly", true);
					boost::thread spin_thread(&spinThread);
					ROS_INFO("Waiting for action server to start.");
					ac.waitForServer(); //will wait for infinite time
					//
					ROS_INFO("Action server started, sending goal : %s",goal->task[i].c_str());//.c_str()
					assembly_actions::assemblyGoal Goal;
					Goal.order = {"r","g","b"}; // need to add a way to  read and send the ordered arragment


					ac.sendGoal(Goal);
					bool finished_before_timeout = ac.waitForResult(ros::Duration(30.0)); // 0 = infinite timeout
					if (finished_before_timeout)
					{
					actionlib::SimpleClientGoalState state = ac.getState();
					ROS_INFO("Action finished: %s",state.toString().c_str());

					}
					else
					ROS_INFO("Action did not finish before the time out.");
				}
		//checks
					else
					{
					break;
					}
					
//common
					
				

		
		i++;
	}
	//end of action client stuff
  
// closing action_server
	if(true)
	{
	result_.complete = true;
	//ROS_INFO("%s task completed",goal->task[i].c_str());
	as_.setSucceeded(result_);	
	}		
	//closing thread from above
			
  
 }
};



 int main(int argc, char** argv)
 {
     ros::init(argc, argv, "LL_controlller_output");   
     
     LLController ll_controllerO("output",argc,argv);
      //   LLController ll_controllerI("input",argc,argv);

	ros::AsyncSpinner spinner(2); // Use 2 threads
	spinner.start();
	ros::waitForShutdown();


   
 
	   
     return 0;
   }
