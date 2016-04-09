#pragma once
#include "HWLSaveEditorCore.h"

//add the class to the project-namespace
namespace HWLSaveEdit{
	class HWLWeapon : public HWLSaveEditorCore
	{
	private:
		string s_name;
		int i_offset;
		vector<int> vi_skill_slot_kills;
		int i_id;
		int i_damage_base;
		int i_stars;
		vector<int> vi_skill_slots;
		int i_state;
		int i_type;
		int i_lvl;

		static const int weaponSkillSlotKillsLength;
		static const int weaponSkillSlotsLength;

		static const int weaponSkillSlotKillsOffsetLength;
		static const int weaponIDOffsetLength;
		static const int weaponDamageBaseOffsetLength;
		static const int weaponStarsOffsetLength;
		static const int weaponSkillSlotsOffsetLength;
		static const int weaponStateOffsetLength;

		static const int weaponSkillSlotKillsOffsetDiff;
		static const int weaponIDOffsetDiff;
		static const int weaponDamageBaseOffsetDiff;
		static const int weaponStarsOffsetDiff;
		static const int weaponSkillSlotsOffsetDiff;
		static const int weaponStateOffsetDiff;

		//methods calc/save
		vector<int> calc_skill_slot_kills();
		int calc_weapon_id();
		int calc_damage_base();
		int calc_stars();
		vector<int> calc_skill_slots();
		int calc_state();

		void save_skill_slot_kills();
		void save_weapon_id();
		void save_damage_base();
		void save_stars();
		void save_skill_slots();
		void save_state();

	public:

		static const int weaponSkillSlotKillMax;
		static const int weaponDamageBaseMax;
		static const int weaponStarsMax;

		static const string weaponBlankWeaponHex;

		HWLWeapon(int i_offset);
		~HWLWeapon();

		string get_WeaponsForOutput();
		void save_weapon();
	};


}
