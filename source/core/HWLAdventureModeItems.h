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

			/* @var i_offset	id of the AM-Item */
			int i_id;

			/* @var i_offset	offset of the AM-Item */
			int i_offset;

			/* @var i_map_id	map-id of the AM-Item */
			int i_map_id;

			/* @var i_value		value of the AM-Item */
			int i_value;

			//needed private members/constans
			static const vector<string> vs_amItems;

			//methods for calculation and saving the AM-Item-Value
			int  calc_value();
			void save_value();



		public:
			//needed public members/constans
			static const int amItemValueMax;

			//constructor and destructor
			HWLAdventureModeItems(int i_id, int i_offset, int i_map_id);
			~HWLAdventureModeItems();

			//method(s) for setting
			void set_value(int i_value);

			//methods for getting the members
			string get_name();
			int get_id();
			int get_offset();
			int get_map_id();
			int get_value();

			//method to get a formatted output (for console)
			string get_AMItemForOutput();

			//saving method
			void save_AMItem();

	};

}