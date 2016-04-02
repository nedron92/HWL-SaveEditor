#pragma once
#include "HWLSaveEditorCore.h"

//add the class to the project-namespace
namespace HWLSaveEdit{
	class HWLPlayer : public HWLSaveEditorCore
	{
		private:
			string s_name;
			int i_offset;
			int i_lvl;
			int i_exp;
			int i_atk;
			bool b_isUnlock;

			static const int playerLVLOffsetLength;
			static const int playerEXPOffsetLength;
			static const int playerATKOffsetLength;
			static const int playerIsUnlockOffsetLength;

			static const int playerLVLOffsetDiff;
			static const int playerEXPOffsetDiff;
			static const int playerATKOffsetDiff;
			static const int playerIsUnlockOffsetDiff;

			//stati-calc
			int calc_players_lvl();
			int calc_players_exp();
			int calc_players_atk();
			bool calc_players_isUnlockState();

			//stati-save
			void save_players_lvl();
			void save_players_exp();
			void save_players_atk();
			void save_players_isUnlockState();

		public:
			static const int playerLVLMax;
			static const int playerEXPMax;
			static const int playerATKMax;

			HWLPlayer(string s_name, int i_offset);
			~HWLPlayer();

			//stati-setter/getter
			  void set_lvl(int i_lvl);
			  void set_exp(int i_exp);
			  void set_atk(int i_atk);
			  void set_isUnlock(bool b_isUnlock);

			string get_name();
			   int get_offset();
			   int get_lvl();
			   int get_exp();
			   int get_atk();
			  bool get_isUnlock();

			string get_playersStatiForOutput();
			void save_Player();
		};
}


