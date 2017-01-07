/*
 * @author: nedron92, 2016
 */
#pragma once

//include the parent-class
#include "HWLSaveEditorCore.h"

//add the class to the project-namespace
namespace HWLSaveEdit
{
	//extend our Core-Class
	class HWLFairyFood : public HWLSaveEditorCore
	{
		private:
			/* @var s_name		name of the fairyFood */
			string s_name;

			/* @var i_offset	offset of the fairyFood */
			int i_offset;

			/* @var i_value		value of the fairyFood */
			int i_value;

			//methods for calculation and saving the fairyFoods
			int  calc_value();
			void save_value();

		public:
			//needed public members/constans
			static const vector<string> vs_fairyFood;
			static const int fairyFoodlValueMax;
			static const int fairyGratitudeCrystalIDBegin;
			static const int fairyGratitudeCrystalIDEnd;

			//constructor and destructor
			HWLFairyFood(string s_name, int i_offset);
			~HWLFairyFood();

			//method(s) for setting
			void set_value(int i_value);

			//methods for getting the members
			string get_name();
			int get_offset();
			int get_value();

			//method to get a formatted output (for console)
			string get_FairyFoodForOutput();

			//saving method
			void save_FairyFood();
	};

}