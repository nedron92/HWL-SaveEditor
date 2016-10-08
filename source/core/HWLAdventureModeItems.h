#pragma once

//include the parent-class 
#include "HWLSaveEditorCore.h"

//add the class to the project-namespace
namespace HWLSaveEdit
{
	class HWLAdventureModeItems : public HWLSaveEditorCore
	{
		private:
			/* @var s_name		name of the AM-Item */
			string s_name;

			/* @var i_offset	offset of the AM-Item */
			int i_offset;

			/* @var i_type		type of the AM-Item */
			int i_type;

			/* @var i_value		value of the AM-Item */
			int i_value;

			//methods for calculation and saving the AM-Item
			int  calc_value();
			void save_value();

		public:
			//needed public members/constans
			static const vector<string> vs_amItems;
			static const int amItemValueMax;
			static const int amItemPerMapMax;

			//constructor and destructor
			HWLAdventureModeItems(string s_name, int i_offset, int i_type);
			~HWLAdventureModeItems();

			//method(s) for setting
			void set_value(int i_value);

			//methods for getting the members
			string get_name();
			int get_offset();
			int get_type();
			string get_type(bool b_get_string);
			int get_value();

			//method to get a formatted output (for console)
			string get_AMItemForOutput();

			//saving method
			void save_AMItem();

	};

}