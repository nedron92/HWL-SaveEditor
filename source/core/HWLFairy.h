#pragma once
#include "HWLSaveEditorCore.h"

namespace HWLSaveEdit
{
	class HWLFairy : public HWLSaveEditorCore
	{
	private:
		string s_name;
		int i_offset;
		int i_lvl;
		int i_trust;
		int i_iterator;
		bool b_isUnlock;

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

		//fairy-calc
		string calc_fairy_name();
		int calc_fairy_lvl();
		int calc_fairy_trust();
		int calc_fairy_iterator();
		bool calc_fairy_isUnlockState();

		//fairy-save
		void save_fairy_name();
		void save_fairy_lvl();
		void save_fairy_trust();
		void save_fairy_iterator();
		void save_fairy_isUnlockState();

	public:
		static const int fairyLVLMax;
		static const int fairyTrustMax;
		static const int fairyIteratorMax;

		static const int fairyNameLength;

		HWLFairy(int i_offset);
		~HWLFairy();

		//fairy-setter/getter
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

		string get_fairyForOutput();
		void save_Fairy();
	};

}
