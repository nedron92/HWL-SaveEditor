#pragma once

//include the parent-class
#include "HWLSaveEditorCore.h"

//add the class to the project-namespace
namespace HWLSaveEdit
{
	//extend our Core-Class
	class HWLFairy : public HWLSaveEditorCore
	{
		private:
			/* @var s_name			name of the fairy */
			string s_name;

			/* @var i_offset		offset of the fairy */
			int i_offset;

			/* @var i_lvl			lvl of the fairy */
			int i_lvl;

			/* @var i_trust			trust of the fairy */
			int i_trust;

			/* @var i_iterator		iterations/refreshes of the fairy */
			int i_iterator;

			/* @var b_isUnlock		unlock-state of the fairy */
			bool b_isUnlock;

			//offset-const declaration
			static const int fairyNameOffsetLength;
			static const int fairyLVLOffsetLength;
			static const int fairyTrustOffsetLength;
			static const int fairyIteratorOffsetLength;
			static const int fairyIsUnlockOffsetLength;

			static const int fairyNameOffsetDiff;
			static const int fairyLVLOffsetDiff;
			static const int fairyTrustOffsetDiff;
			static const int fairyIteratorOffsetDiff;
			static const int fairyIsUnlockOffsetDiff;

			//methods for calculation of all (known) stati-values of a fairy
			string calc_fairy_name();
			int calc_fairy_lvl();
			int calc_fairy_trust();
			int calc_fairy_iterator();
			bool calc_fairy_isUnlockState();

			//methods for saving all current stati-values of a fairy
			void save_fairy_name();
			void save_fairy_lvl();
			void save_fairy_trust();
			void save_fairy_iterator();
			void save_fairy_isUnlockState();

		public:
			//needed public members/constans
			static const int fairyNameLength;
			static const int fairyLVLMax;
			static const int fairyTrustMax;
			static const int fairyIteratorMax;

			//constructor and destructor
			HWLFairy(int i_offset);
			~HWLFairy();

			//methods to set and get all stati-values of a fairy
			void set_name(string s_name);
			void set_lvl(int i_lvl);
			void set_trust(int i_trust);
			void set_iterator(int i_iterator);
			void set_isUnlock(bool b_isUnlock);

			string get_name();
			int get_offset();
			int get_lvl();
			int get_trust();
			int get_iterator();
			bool get_isUnlock();

			//method to get a formatted output (for console)
			string get_fairyForOutput();

			//saving method
			void save_Fairy();
	};

}