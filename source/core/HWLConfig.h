/*
* @author: nedron92, 2016
*/
#pragma once
#include <cstring> //needed for compiling with gcc
#include <string>
#include <map>
#include <fstream>
#include <vector>
#include <algorithm> //needed for sort-function
#include "HWLException.h"

//add the class to the project-namespace
namespace HWLSaveEdit
{
	using namespace std;

	class HWLConfig
	{
	private:
		/* @struct st_config		structure for holding needed param-data */
		struct st_config {
			string s_name; //param-name
			string s_section; //param-section
			int i_id; //param-id (zero-based to each section)
			bool b_isBool; //is this param a boolean one
			bool b_value; //boolean value of param
			string s_value; //string value of param
		};

		/* @var m_config_values         hold all config-params of each section */
		map< string, map< string, st_config> > m_config_values;

		//needed private members/constans
		static const string configFileName;
		static const vector<string> vs_config_section_names;
		static const vector<string> vs_config_param_names;
		static const vector<string> vs_config_param_default_values;

		//getter/setter for the complete structure of an parameter
		st_config get_current_config_object(string s_param_name, int i_section_id);
		st_config get_current_config_object(string s_param_name, string s_section_name);
		void set_current_config_object(string s_param_name, int i_section_id, st_config stc_config_values);
		void set_current_config_object(string s_param_name, string s_section_name, st_config stc_config_values);

		//method to get an internal-ordered list of all params of an section (sort by i_id)
		vector< pair< string, st_config> > get_ordered_section_params(string s_section_name);

	public:
		//constructor and destructor
		HWLConfig(bool b_read_current_config = true);
		~HWLConfig();

		//method to get/calculate the hardcoded default-values
		void calculate_config_defaults();

		//method for read/write the configfile
		void read_config();
		void write_config(bool b_default_config = false);

		//method to get the section-id of given name
		int get_sectionID(string s_section_name);

		//check, getter/setter of an parameter
		bool check_if_param_exist(string s_param_name, int i_section_id);
		int get_param_id(string s_param_name, int i_section_id);
		string get_param_value(string s_param_name, int i_section_id);
		bool get_param_isBool(string s_param_name, int i_section_id);
		void set_param_value(string s_param_name, int i_section_id, string s_param_value);
		void set_param_value(string s_param_name, int i_section_id, bool b_param_value);

		//method to get a formatted output (for console)
		string get_ConfigForOutput();
	};


}
