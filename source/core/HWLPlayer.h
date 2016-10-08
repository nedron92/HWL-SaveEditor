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
			static const int playerLVLMax;
			static const int playerEXPMax;
			static const int playerATKMax;
			static const int playerHeartsMax;
			static const int playerIsUnlockMax;
			static const int playerWeaponSlotsMax;

			//constructor and destructor
			HWLPlayer(int i_id, string s_name, int i_offset);
			~HWLPlayer();

			//methods to set and get all stati-values and also weapons
			void set_lvl(int i_lvl);
			void set_exp(int i_exp);
			void set_atk(int i_atk);
			void set_hearts(int i_hearts);
			void set_isUnlock(bool b_isUnlock);
			void set_weapon_slot(int i_weapon_type, shared_ptr<HWLWeapon> hwlw_weapon);
			void set_weapon_slot(int i_weapon_type, int i_weapon_slot, shared_ptr<HWLWeapon> hwlw_weapon);

			int get_id();
			string get_name();
			int get_offset();
			int get_lvl();
			int get_exp();
			int get_atk();
			int get_hearts();
			bool get_isUnlock();
			shared_ptr<HWLWeapon> get_weapon_slot(int i_weapon_type, int i_weapon_slot);

			//methods to get current weapon-count and a formatted output (for console)
			int get_weapon_count(int i_weapon_type);
			string get_playersStatiForOutput();

			//saving method
			void save_Player();

			//string get_sizes();
	};
}