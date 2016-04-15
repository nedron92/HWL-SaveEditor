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
		int i_damage;
		int i_damage_base;
		int i_stars;
		vector<int> vi_skill_slots;
		int i_state;
		int i_character_id;
		int i_type;
		int i_lvl;
		bool b_is_unsued_weapon;
		vector<int> vi_lvl_hex;

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
		int calc_damage();
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
		static const int weaponLVLMax;
		static const int weaponSkillValueNoSkill;

		static const string weaponBlankWeaponHex;
		static const vector<string> weaponSkillNames;
		static const vector<int>  vi_damage_base_defaults;
		static const vector<int> weaponStateValuesHex;
		static const vector<string> weaponStateValuesNames;

		HWLWeapon(int i_offset, int i_character_id = -1, bool b_is_unsued_weapon = false);
		~HWLWeapon();

		//stats-setter/getter
		void set_name(string s_name);
		void set_skill_slot_kill(int i_slot_id, int i_kill_value);
		void set_id(int i_id);
		void set_damage_base(int i_damage_base);
		void set_stars(int i_stars);
		void set_skill_slot(int i_slot_id, int i_skill_id);
		void set_state(int i_state);
		void set_character_id(int i_character_id);
		void set_type(int i_type);
		void set_lvl(int i_lvl);
		void set_IsUnused(bool b_is_unsued_weapon);
		void set_lvl_hex(vector<int> vi_lvl_hex);

		string get_name();
		int get_skill_slot_kill(int i_slot_id);
		int get_id();
		int get_damage();
		int get_damage_base();
		int get_stars();
		int get_skill_slot(int i_slot_id);
		string get_skill_slot(int i_slot_id, bool b_get_string);
		bool get_state();
		string get_state(bool b_return_as_string);
		int get_character_id();
		int get_type();
		int get_lvl();
		bool get_IsUnused();
		vector<int> get_lvl_hex();
		
		//method to change the damage-base and re-calculate the damage
		void change_damage_base(int i_damage_base);

		//method to change current level and set coresspondding damage-base 
		//re-calculate the damage
		void change_lvl(int i_lvl);

		//method to change stars and re-calculate the damage
		void change_stars(int i_stars);

		//method to delete a weapon
		void delete_weapon();

		string get_WeaponsForOutput();
		string get_WeaponsSkillsForOutput();
		void save_weapon();
	};


}
