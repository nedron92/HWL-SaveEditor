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
	class HWLWeapon : public HWLSaveEditorCore
	{
		private:
			/* @var s_name						name of the weapon */
			string s_name;

			/* @var i_offset					offset of the weapon */
			int i_offset;

			/* @var i_id						id of the weapon */
			int i_id;

			/* @var i_lvl						lvl of the weapon */
			int i_lvl;

			/* @var vi_lvl_hex					lvl-hex of all lvl of the weapon */
			vector<int> vi_lvl_hex;

			/* @var i_damage_base				damage-base of the weapon */
			int i_damage_base;

			/* @var i_stars						stars of the weapon */
			int i_stars;

			/* @var i_damage					real-damage of the weapon */
			int i_damage;

			/* @var i_state						legendary-state of the weapon */
			int i_state;

			/* @var vi_skill_slot_kills			needed-kills for the skills of the weapon */
			vector<int> vi_skill_slot_kills;

			/* @var vi_skill_slots				skills of the weapon */
			vector<int> vi_skill_slots;

			/* @var i_character_id				character-id of the weapon */
			int i_character_id;

			/* @var i_type						type of the weapon (depend on current character.id) */
			int i_type;

			/* @var b_is_unsued_weapon			state, if the weapon is unused */
			bool b_is_unsued_weapon;

			/* @var b_is_multi_element_weapon	state, if the weapon is a multi-element one */
			bool b_is_multi_element_weapon;

			/* @var i_multi_element_weapon_hex	hex of the weapons-multi-element type */
			int i_multi_element_weapon_hex;
                
					/* @var b_weapon_has_changed	state, if a weapon-state was changed */
					bool b_weapon_has_changed;

			/* @var vi_disabledweaponSkillIDs	vector, which holds disabled WeaponSkill-IDs */
			static vector<int> vi_disabledweaponSkillIDs;

			//offset-const declaration
			static const int weaponIDOffsetLength;
			static const int weaponDamageBaseOffsetLength;
			static const int weaponStarsOffsetLength;
			static const int weaponStateOffsetLength;
			static const int weaponSkillSlotKillsOffsetLength;
			static const int weaponSkillSlotsOffsetLength;

			static const int weaponIDOffsetDiff;
			static const int weaponDamageBaseOffsetDiff;
			static const int weaponStarsOffsetDiff;
			static const int weaponStateOffsetDiff;
			static const int weaponSkillSlotKillsOffsetDiff;
			static const int weaponSkillSlotsOffsetDiff;

			static const int weaponSkillSlotKillsLength;
			static const int weaponSkillSlotsLength;

			//methods for calculation of all stati-values
			int calc_weapon_id();
			int calc_damage_base();
			int calc_stars();
			int calc_damage();
			int calc_state();
			vector<int> calc_skill_slot_kills();
			vector<int> calc_skill_slots();

			//methods for saving all current stati-values
			void save_weapon_id();
			void save_damage_base();
			void save_stars();
			void save_state();
			void save_skill_slot_kills();
			void save_skill_slots();

		public:
			//needed public members/constans
			static const vector<int> vi_playerWeaponTypeCount;
			static const vector<string> vs_playerWeaponTypeNames;
			static const vector<int> vi_playerWeaponTypeHexValues;
			static const vector<int> vi_playerWeaponTypeHexValuesLVL4;
			static const vector<int> vi_playerWeaponTypeHexValuesMultiElement;

			static const vector<int>    vi_damage_base_defaults;
			static const vector<int>    weaponStateValuesHex;
			static const vector<string> weaponStateValuesNames;
			static const vector<string> weaponSkillNames;

			static const int weaponLVLMax;
			static const int weaponDamageBaseMax;
			static const int weaponStarsMax;
			static const int weaponSkillSlotKillMax;

			static const int weaponSkillValueNoSkill;
			static const string weaponBlankWeaponHex;

			//constructor and destructor
			HWLWeapon(int i_offset, int i_character_id = -1, bool b_is_unsued_weapon = false, bool b_will_copied = false);
			~HWLWeapon();

			//methods to set and get all stati-values
			void set_name(string s_name);
			void set_id(int i_id);
			void set_lvl(int i_lvl);
			void set_lvl_hex(vector<int> vi_lvl_hex);
			void set_damage_base(int i_damage_base);
			void set_stars(int i_stars);
			void set_state(int i_state);
			void set_skill_slot_kill(int i_slot_id, int i_kill_value);
			void set_skill_kills(vector<int> vi_skill_slot_kills);
			void set_skill_slot(int i_slot_id, int i_skill_id);
			void set_skills(vector<int> vi_skill_slots);
			void set_character_id(int i_character_id);
			void set_type(int i_type);
			void set_IsUnused(bool b_is_unsued_weapon);
			void set_IsMultiElement(bool b_is_multi_element_weapon);
			void set_multi_element_hex(int i_multi_element_weapon_hex);
			static void set_isWeaponSkillDisabled(int i_skill_id);


			string get_name();
			int get_id();
			int get_lvl();
			vector<int> get_lvl_hex();
			int get_damage_base();
			int get_stars();
			int get_damage();
			bool get_state();
			string get_state(bool b_return_as_string);
			int get_skill_slot_kill(int i_slot_id);
			vector<int> get_skill_kills();
			int get_skill_slot(int i_slot_id);
			string get_skill_slot(int i_slot_id, bool b_get_string);
			vector<int> get_skills();
			int get_character_id();
			int get_type();
			bool get_IsUnused();
			bool get_IsMultiElement();
			int get_multi_element_hex();
					bool get_HasWeaponChanged();
			static bool get_isWeaponSkillDisabled(int i_skill_id);
			static int get_WeaponSkillDisabledCounter();

			//method to change the damage-base and re-calculate the damage
			void change_damage_base(int i_damage_base);

			//method to change current level and set coresspondding damage-base 
			//re-calculate the damage
			void change_lvl(int i_lvl);

			//method to change stars and re-calculate the damage
			void change_stars(int i_stars);

			//method to change the legendary-state
			void change_legendary_state(int b_is_legendary);

			//method to change multi-element state and do needed re-calculation
			void change_multi_element_state(bool b_is_multi_element_weapon);

			//method to generate a default weapon 
			void generate_default_weapon(bool b_is_first_weapon = false);

			//method to delete a weapon
			void delete_weapon();

			//methods to get a formatted output (for console)
			string get_WeaponsSkillsForOutput();
			string get_WeaponsForOutput();

			//saving method
			void save_weapon();
	};


}