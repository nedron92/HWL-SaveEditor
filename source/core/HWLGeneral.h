#pragma once

//include the parent-class
#include "HWLSaveEditorCore.h"

//add the class to the project-namespace
namespace HWLSaveEdit
{
	//extend our Core-Class
	class HWLGeneral : public HWLSaveEditorCore
	{
		private:
			/* @var i_rubies			hold the rubies-value */
			int i_rubies = 0;

			/* @var b_unlocked_smithy	hold unlock-state of the ingame smithy  */
			bool b_unlocked_smithy = false;

			/* @var b_unlocked_all_normal_weapons		state, if all normal-weapons are found (MW-Skill 1)*/
			bool b_unlocked_all_normal_weapons = false;

			/* @var b_unlocked_all_plus_weapons			state, if all plus-weapons are found (MW-Skill 2)*/
			bool b_unlocked_all_plus_weapons = false;

			/* @var b_unlocked_all_materials			state, if all materials where found */
			bool b_unlocked_all_materials = false;

			//offset-const declaration
			static const int rubyOffset;
			static const int rubyOffsetLength;

			static const int unlockIngameSmithyOffset;
			static const int unlockIngameSmithyOffsetLength;
			static const int unlockIngameSmithyOffsetPart;

			static const int unlockAllNormalWeaponsOffset;
			static const int unlockAllNormalWeaponsOffsetLength;

			static const int unlockAllPlusWeaponsOffset;
			static const int unlockAllPlusWeaponsOffsetLength;
			static const int unlockAllPlusWeaponsOffsetPart;

			static const vector<int> unlockAllMaterialsOffsets;
			static const int unlockAllMaterialsOffsetsLength;

			static const int unlockIngameSmithyValue;
			static const int unlockAllPlusWeaponsValue;
			static const int unlockAllPlusWeaponsValueMin;

			static const unsigned int unlockAllMaterialsMinValue;
			static const unsigned int unlockAllMaterialsMaxValue;
			static const int unlockAllMaterialsMinValueLastOffset;
			static const int unlockAllMaterialsMaxValueLastOffset;

			//methods for calculation of all (known) general-things
			int  calc_rubies();
			bool calc_unlocked_smithy_state();
			bool calc_unlocked_normal_weapons_state();
			bool calc_unlocked_plus_weapons_state();
			bool calc_unlock_all_materials_state();

			//methods for saving all (known) general-things
			void save_rubies();
			void save_unlocked_smithy_state();
			void save_unlocked_normal_weapons_state();
			void save_unlocked_plus_weapons_state();
			void save_unlock_all_materials_state();

		public:
			//needed public members/constants
			static const int rubyMax;
			static const int fairiesMax;

			//constructor and destructor
			HWLGeneral();
			~HWLGeneral();

			//methods to set and get all (known) general-things
			int get_rubies();
			bool get_unlocked_smithy_state();
			bool get_unlocked_normal_weapons_state();
			bool get_unlocked_plus_weapons_state();
			bool get_unlocked_all_materials_state();

			void set_rubies(int i_rubies);
			void set_unlocked_smithy_state(bool b_unlocked_smithy);
			void set_unlocked_normal_weapons_state(bool b_unlocked_all_normal_weapons);
			void set_unlocked_plus_weapons_state(bool b_unlocked_all_plus_weapons);
			void set_unlocked_all_materials_state(bool b_unlocked_all_materials);

			//method to get a formatted output (for console)
			string get_GeneralThingsForOutput();

			//saving method
			void save_General();
	};

}


