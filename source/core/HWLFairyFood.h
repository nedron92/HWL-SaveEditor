#pragma once
#include "HWLSaveEditorCore.h"

//add the class to the project-namespace
namespace HWLSaveEdit
{
	class HWLFairyFood : public HWLSaveEditorCore
	{
	private:
		string s_name;
		int i_offset;
		int i_value;

		int  calc_value();
		void save_value();

	public:
		static const int fairyFoodlValueMax;
		static const int fairyGratitudeCrystalIDBegin;
		static const int fairyGratitudeCrystalIDEnd;

		HWLFairyFood(string s_name, int i_offset);
		~HWLFairyFood();

		void set_value(int i_value);

		string get_name();
		int get_offset();
		int get_value();

		string get_FairyFoodForOutput();
		void save_FairyFood();
	};

}

