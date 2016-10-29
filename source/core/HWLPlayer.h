#pragma once

//include the parent-class and the weapon-class
#include "HWLSaveEditorCore.h"
#include "HWLWeapon.h"

//add the class to the project-namespace
namespace HWLSaveEdit
{
	//extend our Core-Class
	class HWLPlayer : public HWLSaveEditorCore
	{
		private:
			/* @var i_id				id of the character */
			int i_id;

			/* @var s_name				name of the character */
			string s_name;

			/* @var i_offset			offset of the character */
			int i_offset;

			/* @var i_weapon_type_count		number of weapon-types of the character */
			int i_weapon_type_count;

			/* @var i_lvl				lvl of the character */
			int i_lvl;

			/* @var i_exp				experience of the character */
			int i_exp;

			/* @var i_atk				attack-value of the character */
			int i_atk;

			/* @var i_hearts			heart-value of the character */
			int i_hearts;

			/* @var b_isUnlock			unlock-state of the character */
			bool b_isUnlock;

			/* @var b_canUseAttackBadges		state, if character can use Attack-Badges */
			bool b_canUseAttackBadges;

			/* @var b_isDisabled		state, if character is complety disabled (not editable) */
			bool b_isDisabled;

			/* @var b_isDisabled		vector, which hold weapon-type-IDs of chara, which are complety disabled (not editable) */
			vector<int> vi_weapon_disabled_ids;

			/* @var m_player_weapon		holding all weapons of that character */
			map<int, vector<shared_ptr<HWLWeapon>> > m_player_weapon;
			//int-key = weapon-type, and via a weapon_slot_id access to a 
			//single weapon

			//offset-const declaration
			static const int playerLVLOffsetLength;
			static const int playerEXPOffsetLength;
			static const int playerATKOffsetLength;
			static const int playerHeartsOffsetLength;
			static const int playerIsUnlockOffsetLength;
			static const int playerCanUseAttackBadgesOffsetLength;

			static const int playerLVLOffsetDiff;
			static const int playerEXPOffsetDiff;
			static const int playerATKOffsetDiff;
			static const int playerHeartsOffsetDiff;
			static const int playerIsUnlockOffsetDiff;
			static const int playerCanUseAttackBadgesOffsetDiff;

			//max const declaration for stati
			static const vector<int> playerLVLMax;
			static const vector<int> playerEXPMax;
			static const vector<int> playerATKMax;
			static const vector<int> playerHeartsMax;

			//methods for calculation of all (known) stati-values
			int calc_players_lvl();
			int calc_players_exp();
			int calc_players_atk();
			int calc_players_hearts();
			bool calc_players_isUnlockState();
			bool calc_players_canUseAttackBadgesState();

			//methods for saving all current stati-values
			void save_players_lvl();
			void save_players_exp();
			void save_players_atk();
			void save_players_hearts();
			void save_players_isUnlockState();
			void save_players_canUseAttackBadgesState();

		public:
			//needed public members/constans
			static const vector<string> vs_players;
			static const int playerIsUnlockMax;
			static const int playerWeaponSlotsMax;

			//constructor and destructor
			HWLPlayer(int i_id, string s_name, int i_offset, int i_weapon_type_count);
			~HWLPlayer();

			//methods to set and get all stati-values and also weapons
			void set_lvl(int i_lvl);
			void set_exp(int i_exp);
			void set_atk(int i_atk);
			void set_hearts(int i_hearts);
			void set_isUnlock(bool b_isUnlock);
			void set_isDisabled(bool b_isDisabled);
			void set_disabled_weaponTypeID(int i_weapon_type);
			void set_weapon_slot(int i_weapon_type, shared_ptr<HWLWeapon> hwlw_weapon);
			void set_weapon_slot(int i_weapon_type, int i_weapon_slot, shared_ptr<HWLWeapon> hwlw_weapon);

			int get_id();
			string get_name();
			int get_offset();
			int get_weapon_type_count();
			int get_lvl();
			int get_exp();
			int get_atk();
			int get_hearts();
			bool get_isUnlock();
			bool get_isDisabled();
			bool get_isWeaponTypeDisabled(int i_weapon_type);
			shared_ptr<HWLWeapon> get_weapon_slot(int i_weapon_type, int i_weapon_slot);

			//methods to get current weapon-count and a formatted output (for console)
			int get_weapon_count(int i_weapon_type);
			string get_playersStatiForOutput();

			//methods to get the current max-values for stati
			static int get_max_stati_value(int i_stati_id);
			static int get_max_stati_value(string s_stati_id);

			//saving method
			void save_Player();

			//string get_sizes();
	};
}