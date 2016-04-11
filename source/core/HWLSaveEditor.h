#pragma once
#include <fstream>

//include the other needed classes
#include "HWLSaveEditorCore.h"
#include "HWLException.h"
#include "HWLPlayer.h"
#include "HWLMaterial.h"
#include "HWLFairyFood.h"
#include "HWLAdventureModeItems.h"
#include "HWLFairy.h"
#include "HWLWeapon.h"

//add the class to the project-namespace
namespace HWLSaveEdit{
	
	//extend our Core-Class
	class HWLSaveEditor : public HWLSaveEditorCore
	{

		private:
			/* @var s_filepathname  the path/name of the file*/
			string s_filepathname;

			/* @var fs_filehandler  stream-handler for file-operations*/
			fstream fs_filehandler;

			/* @var i_filelength	hold the file-length*/
			int i_filelength;

			/* @var i_error			for indicate specific errors*/
			int i_error = 0;

			/* @var i_rubies		hold the rubies-value */
			int i_rubies = 0;

			//offset-const declaration
			static const int fileHeaderOffsetBegin;

			static const int rubyOffset;
			static const int rubyOffsetLength;

			static const int playerOffsetBegin;

			static const int bronzeMaterialsOffsetBegin;
			static const int bronzeMaterialsOffsetBeginNew;
			

			static const int silverMaterialsOffsetBegin;
			static const int silverMaterialsOffsetBeginNew;

			static const int goldMaterialsOffsetBegin;
			static const int goldMaterialsOffsetBeginNew;

			static const int fairyFoodOffsetBegin;

			static const vector<int> amItemOffsetBegin;
			static const vector<int> amItemOffsetBeginSpecial;

			static const int fairyOffsetBegin;

			static const int weaponOffsetBegin;

			/* @var m_players		map for holding all playable characters */
			map< string, shared_ptr<HWLPlayer> > m_players;

			/* @var m_materials		map for holding all foundable materials */
			map< string, shared_ptr<HWLMaterial> > m_materials;

			/* @var m_fairyfood		map for holding all foundable fairyfood items */
			map< string, shared_ptr<HWLFairyFood> > m_fairyfood;

			/* @var m_amItem		map for holding all foundable Adventure-Mode items */
			map< int, shared_ptr<HWLAdventureModeItems> > m_amItem;

			/* @var m_fairy			map for holding all myFairies */
			map< int, shared_ptr<HWLFairy> > m_fairy;

			/* @var v_weapon		map for holding all used weapons */
			vector< shared_ptr<HWLWeapon> > v_weapon;

			//other members
			/* @var vi_blank_weapons	vector, which hold all free weapon offsets */
			vector<int> vi_blank_weapons;

			//calculate methods for rubies, weapons, player, material, fairyFood, 
			//am-items and fairies, also for setting an weapon to its player
			int  calc_rubies();
			void calc_weapons();
			void calc_players();
			bool calc_players_weapons(int i_player_id, int i_weapon_id, string &s_weapon_name, int &i_weapon_type, int &i_weapon_lvl, vector<int> &vi_lvl_hexValues);
			void calc_materials();
			void calc_fairyFood();
			void calc_amItems();
			void calc_myFairies();

			//save new ruby-value
			void save_rubies();

		public:
			static const int rubyMax;
			static const int fairiesMax;

			static const vector<string> vs_players;

			static const vector<string> vs_bronzeMaterials;
			static const vector<string> vs_silverMaterials;
			static const vector<string> vs_goldMaterials;
			static const vector<string> vs_fairyFood;
			static const vector<string> vs_amItems;

			static const vector<int> vi_playerWeaponTypeCount;
			static const vector<string> vs_playerWeaponTypeNames;
			static const vector<int> vi_playerWeaponTypeHexValues;
			static const vector<int> vi_playerWeaponTypeHexValuesLVL4;

			HWLSaveEditor(string s_filepathname = "zmha.bin");
			~HWLSaveEditor();

			//getter for rubies, players and materials and errors
			int get_error();
			int get_rubies();
			shared_ptr<HWLPlayer> get_player(int i_id);
			shared_ptr<HWLPlayer> get_player(string s_name);
			shared_ptr<HWLMaterial> get_material(int i_id, int i_type);
			shared_ptr<HWLMaterial> get_material(string s_name);
			shared_ptr<HWLFairyFood> get_fairyFood(int i_id);
			shared_ptr<HWLFairyFood> get_fairyFood(string s_name);
			shared_ptr<HWLAdventureModeItems> get_amItem(int i_id);
			shared_ptr<HWLAdventureModeItems> get_amItem(int i_id, int i_type);
			shared_ptr<HWLFairy> get_fairy(int i_id);

			//method to generate a new default weapon at a default character with
			//its weapon type and slot
			void generate_default_weapon(int i_player_id, int i_weapon_type, int i_weapon_slot);

			//special getter for the size of current adventure-mode-offsets vector
			//todo: delete if we have all offsets
			int get_adventureMode_maxItemCount();

			//setter for rubies
			void set_rubies(int i_rubies);

			//saving file method
			void save_file();

			//method for checking file-header
			bool check_savefile();
	};

}