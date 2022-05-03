


std::vector<std::string>  assembly_tasks(std::string location)
{

	std::vector<std::string> tasks; // Empty on creation
    
	 
			int Len_coord = location.length();
			int dot_pos = location.find(".");
			std::string x_pos = location.substr(0,dot_pos);
			std::string y_pos = location.substr(dot_pos+1,Len_coord-dot_pos);
			int X = stoi(x_pos,0,10);
			int Y = stoi(y_pos,0,10);


			//tasks.push_back("test0"); // Adds an element
			 tasks.push_back("MM2");
			 tasks.push_back(location);
			 //tasks.push_back("Pickup");
			 tasks.push_back("20.19");
			 //tasks.push_back("Place");
			 tasks.push_back("end");
			 tasks.push_back("Assembly");
				



	return tasks;
}
