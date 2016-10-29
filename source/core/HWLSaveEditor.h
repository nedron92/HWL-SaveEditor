#pragma once
#include <fstream>

//include the other needed classes
#include "HWLSaveEditorCore.h"
#include "HWLException.h"
#include "HWLGeneral.h"
#include "HWLPlayer.h"
#include "HWLMaterial.h"
#include "HWLFairyFood.h"
#include "HWLAdventureModeItems.h"
#include "HWLFairy.h"
#include "HWLWeapon.h"

//including needed third-party libraries (HWL-Wrappers)
#include "HWLHttp.h"

//add the class to the project-namespace
namespace HWLSaveEdit
{
	//extend our Core-Class
	class HWLSaveEditor : public HWLSaveEditorCore
	{

		private:
			/* @var s_filepathname  the path/name of the file */
			string s_filepathname;

			/* @var fs_filehandler  stream-handler for file-operations */
			fstream fs_filehandler;

			/* @var i_filelength	hold the file-length */
			int i_filelength;

			/* @var i_error			for indicate specific errors */
			int i_error = 0;

			/* @var b_auto_trim		TRUE, if auto-trim for too large savefiles are enabled, FALSE if not
			Default: TRUE: */
			static bool b_auto_trim;

			//offset-const declaration
			static const int fileHeaderOffsetBegin;
			static const int fileNormalLength;

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

			//other const declaration
			static shared_ptr<HWLHttp> http_request;

			// member declarations
			/* @var sp_general		pointer for holding all general things */
			shared_ptr<HWLGeneral> sp_general;

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

			/* @var v_weapon		vector for holding all used weapons */
			vector< shared_ptr<HWLWeapon> > v_weapon;

			/* @var vi_blank_weapons	vector, which hold all free weapon offsets */
			vector<int> vi_blank_weapons;

			//calculate methods for generals, weapons, player, material, fairyFood, 
			//am-items and fairies, also for setting an weapon to the correct player	
			void calc_general();
			void calc_weapons();
			void calc_players();
			bool calc_players_weapons(int i_player_id, int i_weapon_id, string &s_weapon_name, int &i_weapon_type, int &i_weapon_lvl, vector<int> &vi_lvl_hexValues, bool &b_is_multi_element_weapon, int &i_multi_element_weapon_hex);
			void calc_materials();
			void calc_fairyFood();
			void calc_amItems();
			void calc_myFairies();
			void calc_game_versions_restrictions();

		public:
			HWLSaveEditor(string s_filepathname = "zmha.bin");
			~HWLSaveEditor();

			//getter for errors, general things, players(with weapons), materials, fairyFoods, 
			//am-items and fairies
			int get_error();
			shared_ptr<HWLHttp> get_http_object();
			shared_ptr<HWLGeneral> get_general_things();
			shared_ptr<HWLPlayer> get_player(int i_id);
			shared_ptr<HWLPlayer> get_player(string s_name);
			shared_ptr<HWLMaterial> get_material(int i_id, int i_type);
			shared_ptr<HWLMaterial> get_material(string s_name);
			shared_ptr<HWLFairyFood> get_fairyFood(int i_id);
			shared_ptr<HWLFairyFood> get_fairyFood(string s_name);
			shared_ptr<HWLAdventureModeItems> get_amItem(int i_id);
			shared_ptr<HWLAdventureModeItems> get_amItem(int i_id, int i_type);
			shared_ptr<HWLFairy> get_fairy(int i_id);

			//special getter for the size of current adventure-mode-offsets vector,
			//better how many maps we have
			int get_adventureMode_maxItemCount();

			//method for checking file-header and file-length
			int check_savefile_length();
			bool check_savefile();

			//method for setting the automatic trim
			static void enable_auto_trim(bool b_auto_trim = true);

			//saving file method
			void save_file();
	};

}