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
			
			/* @var b_isUnlock			unlock-state of the character */
			bool b_isUnlock;
			
			/* @var m_player_weapon		holding all weapons of that character */
			map<int, vector<shared_ptr<HWLWeapon>> > m_player_weapon;
			//int-key = weapon-type, and via a weapon_slot_id access to a 
			//single weapon

			//offset-const declaration
			static const int playerLVLOffsetLength;
			static const int playerEXPOffsetLength;
			static const int playerATKOffsetLength;
			static const int playerIsUnlockOffsetLength;

			static const int playerLVLOffsetDiff;
			static const int playerEXPOffsetDiff;
			static const int playerATKOffsetDiff;
			static const int playerIsUnlockOffsetDiff;

			//methods for calculation of all (known) stati-values
			int calc_players_lvl();
			int calc_players_exp();
			int calc_players_atk();
			bool calc_players_isUnlockState();

			//methods for saving all current stati-values
			void save_players_lvl();
			void save_players_exp();
			void save_players_atk();
			void save_players_isUnlockState();

		public:
			//needed public members/constans
			static const vector<string> vs_players;
			static const int playerLVLMax;
			static const int playerEXPMax;
			static const int playerATKMax;
			static const int playerWeaponSlotsMax;

			//constructor and destructor
			HWLPlayer(int i_id, string s_name, int i_offset);
			~HWLPlayer();

			//methods to set and get all stati-values and also weapons
			  void set_lvl(int i_lvl);
			  void set_exp(int i_exp);
			  void set_atk(int i_atk);
			  void set_isUnlock(bool b_isUnlock);
			  void set_weapon_slot(int i_weapon_type, shared_ptr<HWLWeapon> hwlw_weapon);
			  void set_weapon_slot(int i_weapon_type, int i_weapon_slot, shared_ptr<HWLWeapon> hwlw_weapon);

			   int get_id();
			string get_name();
			   int get_offset();
			   int get_lvl();
			   int get_exp();
			   int get_atk();
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


