#pragma once

//include the parent-class 
#include "HWLSaveEditorCore.h"

//add the class to the project-namespace
namespace HWLSaveEdit
{
	//extend our Core-Class
	class HWLMaterial : public HWLSaveEditorCore
	{
		private:
			/* @var s_name		name of the material */
			string s_name;

			/* @var i_offset	offset of the material */
			int i_offset;

			/* @var i_type		type of the material */
			int i_type;

			/* @var i_value		value of the material */
			int i_value;

			//methods for calculation and saving the materials
			int  calc_value();
			void save_value();

		public:
			//needed public members/constans
			static const vector<string> vs_bronzeMaterials;
			static const vector<string> vs_silverMaterials;
			static const vector<string> vs_goldMaterials;
			static const int materialValueMax;

			//constructor and destructor
			HWLMaterial(string s_name, int i_offset, int i_type);
			~HWLMaterial();

			//method(s) for setting
			void set_value(int i_value);

			//methods for getting the members
			string get_name();
			int get_offset();
			int get_type();
			string get_type(bool b_get_string);
			int get_value();

			//method to get a formatted output (for console)
			string get_MaterialForOutput();

			//saving method
			void save_Material();

	};
}