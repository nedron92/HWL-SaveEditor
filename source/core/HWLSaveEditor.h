#pragma once
#include <vector>
#include <map>
#include <fstream>
#include <memory>

//include the other needed classes
#include "HWLSaveEditorCore.h"
#include "HWLPlayer.h"
#include "HWLMaterial.h"
#include "HWLException.h"

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
			static const int playerOffsetLength;

			static const int bronzeMaterialsOffsetBegin;
			static const int bronzeMaterialsOffsetBeginNew;
			

			static const int silverMaterialsOffsetBegin;
			static const int silverMaterialsOffsetBeginNew;

			static const int goldMaterialsOffsetBegin;
			static const int goldMaterialsOffsetBeginNew;

			/* @var m_players		map for holding all playable characters */
			map< string, shared_ptr<HWLPlayer> > m_players;

			/* @var m_materials		map for holding all foundable materials */
			map< string, shared_ptr<HWLMaterial> > m_materials;

			//calculate methods for player/material
			int  calc_rubies();
			void calc_players();
			void calc_materials();

			//save new ruby-value
			void save_rubies();

		public:
			static const int rubyMax;

			static const vector<string> vs_players;

			static const vector<string> vs_bronzeMaterials;
			static const vector<string> vs_silverMaterials;
			static const vector<string> vs_goldMaterials;

			HWLSaveEditor(string s_filepathname = "zmha.bin");
			~HWLSaveEditor();

			//getter for rubies, players and materials and errors
			int get_error();
			int get_rubies();
			shared_ptr<HWLPlayer> get_player(int i_id);
			shared_ptr<HWLPlayer> get_player(string s_name);
			shared_ptr<HWLMaterial> get_material(int i_id, int i_type);
			shared_ptr<HWLMaterial> get_material(string s_name);

			//setter for rubies
			void set_rubies(int i_rubies);

			//saving file method
			void save_file();

			//method for checking file-header
			bool check_savefile();
	};

}