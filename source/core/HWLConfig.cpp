/*
 * @author: nedron92, 2016
 */
//needed for including in a MFC-App
#ifdef __MFC__
#include "../gui/stdafx.h" 
#endif // __MFC__

//include the correct header-file
#include "HWLConfig.h"

//use the project-namespace
using namespace HWLSaveEdit;

/* @var configFileName				the filename of the needed config-file */
const string HWLConfig::configFileName = "settings.cfg";

/* @var vs_config_section_names			vector, which hold all current section-names */
const vector<string> HWLConfig::vs_config_section_names =
{
	"General",
	"HTTP",
};

/* @var vs_config_param_names			vector, which hold all current param-names */
const vector<string> HWLConfig::vs_config_param_names =
{
	"autoUpdateCheck", //General-Section
	"autoTrim",
	"DlcSafetyCheck",
	"createBackupFileOnOpening",
	"openLastSaveFileOnStart",
	"LastSaveFile",
	//"language",
	"useHTTPProxy",
	"", //empty-string, need as a indicator for a new section
	"ProxyHost", //HTTP-Section
	"ProxyPort",
};

/* @var vs_config_param_default_values			vector, which hold all current param-default-values */
const vector<string> HWLConfig::vs_config_param_default_values =
{
	"false", //General-Section
	"true",
	"true",
	"true",
	"false",
	"zmha.bin",
	//"en",
	"false",
	"", //empty-string, need as a indicator for a new section
	"127.0.0.1", //HTTP-Section
	"8080"
};


/**
* Only the initialization of the normal-constructor
*/
HWLConfig::HWLConfig(bool b_read_current_config)
{
	this->calculate_config_defaults();

	if (b_read_current_config)
		this->read_config();
}

/**
* Only the initialization of the normal-destructor
*/
HWLConfig::~HWLConfig()
{
}



/**
* Getter for the structure of an parameter by its given name and its section-id
*
*	@var string	s_param_name		given parameter-name
*	@var int	i_section_id		given section-id of parameter
*
*	@return st_config                       structure of the given parameter,
*                                               empty s_name if it not exist
*
*/
HWLConfig::st_config HWLConfig::get_current_config_object(string s_param_name, int i_section_id)
{
	//try to return the needed param-structure and catch the out-of-range exception
	//return new structure with an empty name if exception is thrown
	try
	{
		return this->m_config_values[this->vs_config_section_names[i_section_id]].at(s_param_name);
	}
	catch (std::out_of_range &e)
	{
		st_config stc_tmp;
		stc_tmp.s_name = "";

		return stc_tmp;
	}


}

/**
* Getter for the structure of an parameter by its given name and its section-name
*
*	@var string	s_param_name		given parameter-name
*	@var string	s_section_name		given section-name of parameter
*
*	@return st_config                       structure of the given parameter,
*                                               empty s_name if it not exist
*
*/
HWLConfig::st_config HWLConfig::get_current_config_object(string s_param_name, string s_section_name)
{
	//try to return the needed param-structure and catch the out-of-range exception
	//return new structure with an empty name if exception is thrown
	try
	{
		return this->m_config_values.at(s_section_name).at(s_param_name);
	}
	catch (std::out_of_range &e)
	{
		st_config stc_tmp;
		stc_tmp.s_name = "";

		return stc_tmp;
	}
}

/**
* Setter for the structure of an parameter by its given name, its section-id
*  and it new structure-data
*
*	@var string	s_param_name		given parameter-name
*	@var int	i_section_id		given section-name of parameter
*       @var st_config  stc_config_values       new structure-data of parameter
*
*/
void HWLConfig::set_current_config_object(string s_param_name, int i_section_id, st_config stc_config_values)
{
	this->m_config_values[this->vs_config_section_names[i_section_id]][s_param_name] = stc_config_values;
}

/**
* Setter for the structure of an parameter by its given name, its section-name
*  and it new structure-data
*
*	@var string	s_param_name		given parameter-name
*	@var string	s_section_name		given section-name of parameter
*       @var st_config  stc_config_values       new structure-data of parameter
*
*/
void HWLConfig::set_current_config_object(string s_param_name, string s_section_name, st_config stc_config_values)
{
	this->m_config_values[s_section_name][s_param_name] = stc_config_values;
}



/**
* This method sort all parameters of an given-section by its internal integer-value
*  i_id and return an vector of them.
*
*	@var string	s_section_name		given section-name to sort its params
*
*	@return vector< pair< string, st_config>    vector, which hold all params
*                                                    in ordered range.
*/
vector< pair< string, HWLConfig::st_config> > HWLConfig::get_ordered_section_params(string s_section_name)
{
	//get the map of the given section and create a new vector
	map< string, st_config> m_tmp_section = this->m_config_values[s_section_name];
	vector< pair< string, st_config> > vp_tmp_section_params;

	//iterate over the whole map and push every element into the vector
	for (auto it_i = m_tmp_section.begin(); it_i != m_tmp_section.end(); it_i++)
		vp_tmp_section_params.push_back(*it_i);

	//sort function, combined with an lamda-compare function
	// -> check the internal structure interger i_ids
	sort(vp_tmp_section_params.begin(), vp_tmp_section_params.end(), [=](pair< string, st_config>& a, pair< string, st_config>& b)
	{
		return(a.second.i_id < b.second.i_id);
	}
	);

	//return the ordered vector
	return vp_tmp_section_params;
}



/**
* This method calculate and fill the internal map with all hardcoded default-values
*
*/
void HWLConfig::calculate_config_defaults()
{
	//define needed variables_ counter for the sections and internal ids
	int i_section_counter = 0;
	int i_id_counter = 0;

	//Iterate over all known params and 
	// calculate all data of them
	for (int i = 0; i < this->vs_config_param_names.size(); i++)
	{
		//get a new structure to fill with the data
		st_config stc_tmp_values;

		//check if we have an empty string -> identicator
		// for a new section, increment section-counter
		// and set the id-counter back to zero
		if (this->vs_config_param_names[i] == "")
		{
			i_section_counter++;
			i_id_counter = 0;
			continue;
		}

		//get the params-name and set its id
		stc_tmp_values.s_name = this->vs_config_param_names[i];
		stc_tmp_values.i_id = i_id_counter;

		//check if we don't have "false" and "true" as value
		// -> param has a string-value
		//else: param has a boolean-value
		if (this->vs_config_param_default_values[i] != "false" && this->vs_config_param_default_values[i] != "true")
		{
			//set the defaults for a string-based-value
			stc_tmp_values.b_isBool = false;
			stc_tmp_values.b_value = false;
			stc_tmp_values.s_section = this->vs_config_section_names[i_section_counter];
			stc_tmp_values.s_value = this->vs_config_param_default_values[i];
		}
		else{
			//set the defaults for a boolean-based-value
			stc_tmp_values.b_isBool = true;
			stc_tmp_values.s_section = this->vs_config_section_names[i_section_counter];

			//check the value-string and set the boolean and string-value to it
			if (this->vs_config_param_default_values[i] == "false")
			{
				stc_tmp_values.b_value = false;
				stc_tmp_values.s_value = "false";
			}
			else
			{
				stc_tmp_values.b_value = true;
				stc_tmp_values.s_value = "true";
			}
		}

		//increment the id-counter and fill the main-map with the new data
		i_id_counter++;
		this->m_config_values[stc_tmp_values.s_section][stc_tmp_values.s_name] = stc_tmp_values;
	}


	//maybe not needed, don't know
	/*
	//security-check for space-paths
	size_t found = this->m_config_values_general["LastSaveFile"].s_value.find(" ");
	if (found == std::string::npos)
	{
	this->m_config_values_general["LastSaveFile"].s_value.replace(0, 1, "");
	this->m_config_values_general["LastSaveFile"].s_value.replace(this->m_config_values_general["LastSaveFile"].s_value.size()-1, 1, "");

	}
	*/
}



/**
* This method reads the current config-file and set the coressponding
*  params to the found values
*
*/
void HWLConfig::read_config()
{
	//open the config-file for reading
	fstream fs_filehandler = fstream(this->configFileName, fstream::in);

	//check if its really open
	// else: File not existent, try to write a new config-file
	if (fs_filehandler.is_open())
	{
		//define needed variables
		size_t pos_end_section; //current position of section-ending
		string s_config_line;
		string section_name = "";

		//do not skip whitespaces
		fs_filehandler >> std::noskipws;

		//iterate till we reach the end-of-file
		while (!fs_filehandler.eof())
		{
			//get line-per-line
			getline(fs_filehandler, s_config_line);

			//if the first-character is '[', we have a section
			// else: check if we don't have a empty-line (\n or \r),
			//  then we have a real parameter
			// else: set section-name to empty-string
			if (s_config_line[0] == '[')
			{
				//get the endof the section-name (before ']')
				pos_end_section = s_config_line.find(']', 0);
				section_name = s_config_line.substr(1, pos_end_section - 1);

				//check if section exist, if not, empty the section-name
				if (this->get_sectionID(section_name) == -1)
				{
					section_name = "";
					continue;
				}
			}
			else if (s_config_line[0] != '\n' && s_config_line[0] != '\r')
			{
				//check if we have a non-valid section
				//continue with next line
				if (section_name == "")
					continue;

				//get position of the delimiter itself ( '=' )
				//check if it wasn't found, then continue with next line
				size_t pos_delimiter_value = s_config_line.find('=', 0);
				if (pos_delimiter_value == string::npos)
					continue;

				//get position of the end of the param-value ('\n' and/or '\r')
				size_t pos_delimiter_value_end = s_config_line.find_first_of("\n\r", pos_delimiter_value + 1);

				//get param-name and value out of the current line, due to the delimiter
				string s_param_name = s_config_line.substr(0, pos_delimiter_value);
				string s_param_value = s_config_line.substr(pos_delimiter_value + 1, pos_delimiter_value_end - pos_delimiter_value - 1);

				//check if param doesn't exist -> continue with next line
				if (!this->check_if_param_exist(s_param_name, this->get_sectionID(section_name)))
					continue;

				//check if we doesn't have have a boolean value
				// -> set the param-value directly
				//else: set the corressponding boolean-value
				if (!this->get_param_isBool(s_param_name, this->get_sectionID(section_name)))
				{
					this->set_param_value(s_param_name, this->get_sectionID(section_name), s_param_value);
				}
				else
				{
					if (s_param_value != "false" && s_param_value != "true")
						continue;

					bool b_value = false;
					if (s_param_value == "true")
						b_value = true;

					this->set_param_value(s_param_name, this->get_sectionID(section_name), b_value);

				}

			}
			else{
				section_name = "";
			}
		}

		//close the filehandler at the end
		fs_filehandler.close();

	}
	else
	{
		//close the filehandler at the end
		fs_filehandler.close();

		//try to write a new config, else do nothing
		try
		{
			this->write_config();
		}
		catch (HWLException &e)
		{
			//nothing todo
		}

	}
}

/**
* This method writes the current config-file with all needed params
*
*	@var bool	b_default_config        state, if a default-config
*                                                should be created.
*                                                Default: false
*
*       @throw  HWLException
*
*/
void HWLConfig::write_config(bool b_default_config)
{
	//For Remembering:: The Standard-Template
	/*
	STANDARD_TEMPLATE!

	[General]
	autoUpdateCheck=false
	autoTrim=true
	DlcSafetyCheck=true
	createBackupFileOnOpening=false
	openLastSaveFileOnStart=false
	LastSaveFile="zmha.bin"
	language=en
	useHTTPProxy=false

	[HTTP]
	ProxyHost="127.0.0.1"
	ProxyPort="8080"
	*/

	//open the config-file for writing
	fstream fs_filehandler = fstream(this->configFileName, fstream::out);

	//check if its really open
	// else: throw exception
	if (fs_filehandler.is_open())
	{
		//check if we have to write a default-config
		// -> get the default-values again
		if (b_default_config)
			this->calculate_config_defaults();

		//set the filehandler to the begin of the file
		fs_filehandler.seekp(0, fs_filehandler.beg);

		//iterate over all sections
		for (int i = 0; i < this->vs_config_section_names.size(); i++)
		{
			//write stream-buffer directly: Get the section-name
			// -> [section_name]
			fs_filehandler << "[" << this->vs_config_section_names[i] << "]\n";

			//get an ordered vector of the params of the current section
			vector< pair< string, st_config> > vp_ordered_section_params = this->get_ordered_section_params(this->vs_config_section_names[i]);

			//iterate over all params of the section
			for (int j = 0; j < vp_ordered_section_params.size(); j++)
			{
				//write stream-buffer directly: Get ParamName and Value
				// -> param_name=param_value
				fs_filehandler << vp_ordered_section_params[j].second.s_name << "=" << vp_ordered_section_params[j].second.s_value << "\n";
			}

			//if section doesn't exist, write a newline
			if (i < this->vs_config_section_names.size() - 1)
				fs_filehandler.put('\n');
		}

		//close the filehandler finally
		fs_filehandler.close();
	}
	else
	{
		//close the filehandler finally
		fs_filehandler.close();

		//set error-code and message
		int i_error = 400;
		string s_tmp = "Configfile '" + this->configFileName + "' isn't writeable. ";
		char *cstr = new char[s_tmp.length() + 1];
		strcpy(cstr, s_tmp.c_str());

		//throw exception and do cleaning
		throw HWLException(cstr, i_error);

		delete[] cstr;
	}
}



/**
* This method return the ID of the given section-name
*
*	@var string	s_section_name        the given section-name
*
*       @return int     id of the given section, -1 if it doesn't exist
*
*/
int HWLConfig::get_sectionID(string s_section_name)
{
	//iterate over the names and get the id (i-value), else 
	// return -1
	for (int i = 0; i < this->vs_config_section_names.size(); i++)
	{
		if (s_section_name == this->vs_config_section_names[i])
			return i;
	}

	return -1;
}



/**
* This method checks if an given parameter exist. Depend on the givens section-id
*
*	@var string	s_param_name        given parameter-name
*	@var int	i_section_id        given section-id
*
*       @return bool     TRUE if param exist, FALSE otherwise
*
*/
bool HWLConfig::check_if_param_exist(string s_param_name, int i_section_id)
{
	try
	{
		this->m_config_values[this->vs_config_section_names[i_section_id]].at(s_param_name);
		return true;
	}
	catch (const out_of_range &e) {
		return false;
	}

}

/**
* This method return the ID of an given parameter, depend on given section-id
*
*	@var string	s_param_name        given parameter-name
*	@var int	i_section_id        given section-id
*
*       @return int     the id of the given parameter
*
*/
int HWLConfig::get_param_id(string s_param_name, int i_section_id)
{
	st_config st_cfg_tmp = this->get_current_config_object(s_param_name, i_section_id);

	if (st_cfg_tmp.s_name != "")
	{
		return(st_cfg_tmp.i_id);
	}
	else{
		return -1;
	}
}

/**
* This method return the value of an given parameter, depend on given section-id
*  If its a boolean-based-value the method return it as '0' or '1' (false, true)
*
*	@var string	s_param_name        given parameter-name
*	@var int	i_section_id        given section-id
*
*       @return string     the value of the given parameter
*
*/
string HWLConfig::get_param_value(string s_param_name, int i_section_id)
{
	st_config st_cfg_tmp = this->get_current_config_object(s_param_name, i_section_id);

	if (st_cfg_tmp.s_name != "")
	{
		if (st_cfg_tmp.b_isBool)
			return(to_string(st_cfg_tmp.b_value));
		else
			return(st_cfg_tmp.s_value);
	}
	else{
		return "";
	}
}

/**
* This method return if the value of an given parameter is a boolean one,
*  depend on given section-id
*
*	@var string	s_param_name        given parameter-name
*	@var int	i_section_id        given section-id
*
*       @return bool    TRUE, if parameter has a boolean value, FALSE otherwise
*
*/
bool HWLConfig::get_param_isBool(string s_param_name, int i_section_id)
{
	st_config st_cfg_tmp = this->get_current_config_object(s_param_name, i_section_id);

	if (st_cfg_tmp.s_name != "")
	{
		return st_cfg_tmp.b_isBool;
	}
	else{
		return false;
	}
}

/**
* This method set the string-based-value to the given parameter, determine by
*  its given section-id
*
*	@var string	s_param_name        given parameter-name
*	@var int	i_section_id        given section-id
*	@var string	s_param_value       the new string-based-value
*
*/
void HWLConfig::set_param_value(string s_param_name, int i_section_id, string s_param_value)
{
	st_config st_cfg_tmp = this->get_current_config_object(s_param_name, i_section_id);

	if (st_cfg_tmp.s_name != "")
	{
		st_cfg_tmp.s_value = s_param_value;
		this->set_current_config_object(s_param_name, i_section_id, st_cfg_tmp);
	}
}

/**
* This method set the boolean-based-value to the given parameter, determine by
*  its given section-id
*
*	@var string	s_param_name        given parameter-name
*	@var int	i_section_id        given section-id
*	@var bool	b_param_value       the new boolean-based-value
*
*/
void HWLConfig::set_param_value(string s_param_name, int i_section_id, bool b_param_value)
{
	st_config st_cfg_tmp = this->get_current_config_object(s_param_name, i_section_id);

	if (st_cfg_tmp.s_name != "")
	{
		st_cfg_tmp.b_value = b_param_value;
		if (b_param_value)
			st_cfg_tmp.s_value = "true";
		else
			st_cfg_tmp.s_value = "false";

		this->set_current_config_object(s_param_name, i_section_id, st_cfg_tmp);
	}
}


/**
* This method return an formatted output with all needed data
*
*/
string HWLConfig::get_ConfigForOutput()
{
	string s_output = "Config: \n";

	for (int i = 0; i < this->vs_config_section_names.size(); i++)
	{
		vector< pair< string, st_config> > vp_ordered_section_params;
		vp_ordered_section_params = this->get_ordered_section_params(this->vs_config_section_names[i]);

		s_output += " [" + this->vs_config_section_names[i] + "]\n";

		for (int j = 0; j < vp_ordered_section_params.size(); j++)
		{
			s_output += "  " + vp_ordered_section_params[j].second.s_name + "=";
			s_output += vp_ordered_section_params[j].second.s_value + "\n";
		}
		if (i < this->vs_config_section_names.size() - 1)
			s_output += "\n";

	}

	return s_output;
}

