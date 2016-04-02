#pragma once
#include "HWLSaveEditorCore.h"

//add the class to the project-namespace
namespace HWLSaveEdit{

	class HWLMaterial : public HWLSaveEditorCore
	{
		private:
			string s_name;
			int i_offset;
			int i_type;
			int i_value;

			int  calc_value();
			void save_value();

		public:
			static const int materialValueMax;

			HWLMaterial(string s_name, int i_offset, int i_type);
			~HWLMaterial();

			void set_value(int i_value);

			string get_name();
			   int get_offset();
			   int get_type();
			string get_type(bool b_get_string);
			   int get_value();
			   

			string get_MaterialForOutput();
			void save_Material();

	};
}


