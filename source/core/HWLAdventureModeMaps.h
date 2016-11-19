#pragma once

//include the parent-class 
#include "HWLSaveEditorCore.h"
#include "HWLAdventureModeItems.h"

//add the class to the project-namespace
namespace HWLSaveEdit
{
	class HWLAdventureModeMaps : public HWLSaveEditorCore
	{
		private:
			/* @var i_id		ID of the AM-Map */
			int i_id;

			/* @var s_name		name of the AM-Map */
			string s_name;

			/* @var b_isDisabled		state, if map is complety disabled (not editable) */
			bool b_isDisabled;

			/* @var vsp_ami_items		vector to hold the current items (of current map) as coressponding object */
			vector<shared_ptr<HWLAdventureModeItems>> vsp_hwlami_items;

			//needed private static members/constans
			static const vector<int> amItemOffsetBegin;
			static const vector<int> amItemOffsetBeginSpecial;
			static int si_disabledMapCounter;

			//methods for calculation of the AM-Map-Items
			vector<shared_ptr<HWLAdventureModeItems>> calc_amiItems();

		public:
			//needed public members/constans
			static const vector<string> vs_map_names;
			static const int amm_MaxItemsPerMap;

			//constructor and destructor
			HWLAdventureModeMaps(int i_id);
			~HWLAdventureModeMaps();

			//method(s) for setting
			void set_isDisabled(bool b_isDisabled);
			void set_amItem(int i_item_id, shared_ptr<HWLAdventureModeItems> sp_hwlami_item);
			void set_all_amItems(vector<shared_ptr<HWLAdventureModeItems>> vsp_hwlami_item);

			//methods for getting the members
			int get_id();
			string get_name();
			bool get_isDisabled();
			shared_ptr<HWLAdventureModeItems> get_amItem(int i_item_id);
			vector<shared_ptr<HWLAdventureModeItems>> get_all_amItems();
			static int get_disabledMapCounter();

			//method to get a formatted output (for console)
			string get_AllAMItemsForOutput();
			string get_AMMapForOutput(bool b_with_item_output=true);
	};

}