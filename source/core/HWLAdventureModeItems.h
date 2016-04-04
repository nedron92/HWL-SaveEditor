#pragma once
#include "HWLSaveEditorCore.h"

namespace HWLSaveEdit
{
	class HWLAdventureModeItems : public HWLSaveEditorCore
	{
	private:
		string s_name;
		int i_offset;
		int i_type;
		int i_value;

		int  calc_value();
		void save_value();
		
	public:
		static const int amItemValueMax;
		static const int amItemPerMapMax;

		HWLAdventureModeItems(string s_name, int i_offset, int i_type);
		~HWLAdventureModeItems();

		void set_value(int i_value);

		string get_name();
		int get_offset();
		int get_type();
		string get_type(bool b_get_string);
		int get_value();


		string get_AMItemForOutput();
		void save_AMItem();

	};

}

