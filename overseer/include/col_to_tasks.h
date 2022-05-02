


std::vector<std::string>  col_to_tasks(char colour)
{

	std::vector<std::string> tasks; // Empty on creation
    
	 
	
	if(colour == 'r')
			{
			//tasks.push_back("test0"); // Adds an element
			    tasks.push_back("MM1");
			    tasks.push_back("12.14");
			    tasks.push_back("end");
			    tasks.push_back("Heating");
			    tasks.push_back("MM1");
			    tasks.push_back("12.14");
			    tasks.push_back("end");
			}
	if(colour == 'b')
			{
			//tasks.push_back("test0"); // Adds an element
			    tasks.push_back("MM1");
			    tasks.push_back("12.14");
			    tasks.push_back("end");
			    tasks.push_back("Cleaning");
			    tasks.push_back("MM1");
			    tasks.push_back("17.14");
			    tasks.push_back("end");
			    tasks.push_back("MM1");
			    tasks.push_back("20.14");
			    tasks.push_back("end");
			}
	if(colour == 'o')
			{
			//tasks.push_back("test0"); // Adds an element
			    tasks.push_back("MM2");
			    tasks.push_back("2.19");
			    tasks.push_back("end");
			    tasks.push_back("Assembly");
			    tasks.push_back("MM2");
			    tasks.push_back("12.19");
			    tasks.push_back("end");
			    tasks.push_back("Assembly");
			    tasks.push_back("MM2");
			    tasks.push_back("120.19");
			    tasks.push_back("end");
			    tasks.push_back("Assembly");
			}	



	return tasks;
}
