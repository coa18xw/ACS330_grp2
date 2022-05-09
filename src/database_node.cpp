/**
**  ACS330-Group 2 Database Node
**/
#include <ros/ros.h>
#include <iostream>
#include <fstream>
#include <string>
#include <actionlib/server/simple_action_server.h>
#include <actionlib/client/simple_action_client.h>
#include <process_actions/processAction.h>
#include <assembly_actions/assemblyAction.h>
#include <mm_actions/mmAction.h>
#include <std_msgs/Int32.h>
#include <unistd.h>

using namespace std;

//Process Stations
class ProcessAction
{
protected:

	ros::NodeHandle nh_;
	actionlib::SimpleActionServer<process_actions::processAction> as_; // NodeHandle instance must be created before this line. Otherwise strange error occurs.
	std::string station_name_;
	// create messages that are used to published feedback/result
	process_actions::processResult result_;

public:
ProcessAction(std::string station_id) :
as_(nh_, station_id, boost::bind(&ProcessAction::executeCB, this, _1), false), station_name_(station_id)
	{
		as_.start();
		ROS_INFO("%s: Activated", station_id.c_str());
	}


//Assembly Station
class AssemblyAction
{
protected:

	ros::NodeHandle nh_;
	actionlib::SimpleActionServer<assembly_actions::assemblyAction> as_; // NodeHandle instance must be created before this line. Otherwise strange error occurs.
	std::string station_name_;
	// create messages that are used to published feedback/result
	assembly_actions::assemblyFeedback feedback_;
	assembly_actions::assemblyResult result_;

public:
AssemblyAction(std::string station_id) :
as_(nh_, station_id, boost::bind(&AssemblyAction::executeCB, this, _1), false), station_name_(station_id)
	{
		as_.start();
		ROS_INFO("%s: Activated", station_id.c_str());
	}


//Mobile Manupilator
class MMAction
{
protected:

	ros::NodeHandle nh_;
	actionlib::SimpleActionServer<mm_actions::mmAction> as_; // NodeHandle instance must be created before this line. Otherwise strange error occurs.
	std::string mm_name_;
	// create messages that are used to published feedback/result
	mm_actions::mmFeedback feedback_;
	mm_actions::mmResult result_;
	ros::Subscriber feedback; //
	bool completed;

public:
MMAction(std::string mm_id) :
as_(nh_, mm_id, boost::bind(&MMAction::executeCB, this, _1), false), mm_name_(mm_id)
	{
		as_.start();
		ROS_INFO("%s: Activated", mm_id.c_str());
		feedback = nh_.subscribe("feedback", 1000, &MMAction::feedbackCallback,this); //
		bool completed = false;
		
	}

//Overseer
class Overseer{
private:
	
	ros::NodeHandle n;
	bool stop;
	char colour;
	bool finished_before_timeout_I;
	bool finished_before_timeout_O;
	char storageStr[16];
	char combination[3];
	bool full;
	std::string location;
	int dot_pos;
	int block_pos;
	unsigned int microsecond;
	ros::Subscriber detected;
	

public:
	Overseer(std::string overseer_id)
	{
	actionlib::SimpleActionClient<low_level_controller::ll_client_serverAction> acI("input", true);
	actionlib::SimpleActionClient<low_level_controller::ll_client_serverAction> acO("output", true);
	ROS_INFO("%s: Activated", overseer_id.c_str());
	detected = n.subscribe("color_detected", 1000, &Overseer::detectionCallback,this);
		

	char storageStr[16]={'.','.','.','r','.','.','.','.','b','.','.','.','.','.','g','.'};
	std::string location;
	int dot_pos;
	int block_pos;


// Callback functions
void feedbackCallback(const std_msgs::Int32::ConstPtr& feedback)
{
	if(feedback->data ==1)
	{
	completed = true;
	ROS_INFO("Completed = true");
	}
	else 
	completed= false;
}
void executeCB(const assembly_actions::assemblyGoalConstPtr &goal)
	}
	if(success)
	{
	result_.complete = true;
	ROS_INFO("%s task completed", goal->order[0].c_str());
	as_.setSucceeded(result_);	
	}

void detectionCallback(const std_msgs::Char::ConstPtr& detected)
{
	if(detected->data =='r'||detected->data =='b'||detected->data =='g')
	{
	colour = detected->data;
	}
	else{
	colour = NULL;
	}
}


  

//example of .txt output
//ofstream myfile("example.txt", ios::out | ios::binary);
//myfile << "Writing this to a file.\n";
//myfile.close();

// Here to export the subscribed info to a csv file	
	ofstream outputFile;
  	ofstream fs
  	std::string filename = "TaskResult.csv";

int main(int argc, char** argv[])
{
  // This must be called before anything else ROS-related
  ros::init(argc, argv, "database_node");

  // Create a ROS node handle
  ros::NodeHandle nh;
  
	fs.open(outputFile,filename);
	outputFile << "Column A" << "," << "Column B" << "Column C" << std::endl;
	A= processResult result_.complete;
	B= assemblyResult result_.complete;
	C= mmResult result_.complete;	
	
	outputFile << A << "," << B << "," << C << std::endl;
	// close the output file
	outputFile.close();

  // Don't exit the program.
  ros::spin();
  return 0;
}
