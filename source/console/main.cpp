#include <iostream>
#include "../core/HWLSaveEditor.h"

using namespace std;
HWLSaveEdit::HWLSaveEditor *save;
vector<int> vi_ids;

void get_submenu(int i_menu_code);
void get_ruby_menu();

void get_chara_menu();
void change_chara_values(int i_choose, int i_chara_id);

void get_materials_menu();
void get_materials_submenu(int i_choose);
void change_materials_values(int i_choose, int i_material_id, int i_type, int i_size);

void get_fairyFood_menu();
void change_fairyFood_values(int i_choose, int i_fairyFood_id);

void get_amItem_menu();
void change_amItem_values(int i_choose);

void get_fairy_menu();
void change_fairy_values(int i_choose, int i_fairy_id);

void get_weapons_type(int i_chara_id);
void get_weapons(int i_chara_id, int i_type_id, int i_choose);
void change_weapon_values(int i_chara_id, int i_type_id, int i_current_id, int i_choose);

void get_skills(int i_chara_id, int i_weapon_type_id, int i_weapon_slot_id);
void change_skill_values(int i_chara_id, int i_weapon_type_id, int i_weapon_slot_id, int i_skill_slot_id, int i_skill_id, int i_choose);

int main()
{

	try
	{
		save = new HWLSaveEdit::HWLSaveEditor();

		char i_choose;

		while (1)
		{
			cout << "  Hyrule Warriors Legends - SaveEditor, V" << HWLSaveEdit::HWLSaveEditorCore::version <<endl;
			cout << "________________________________________________" << endl << endl;

			cout << "Menue: " << endl;
			cout << "1 - Rubies (Submenu)" << endl;
			cout << "2 - Characters (Submenu)" << endl;
			cout << "3 - Materials (Submenu)" << endl;
			cout << "4 - FairyFood (Submenu)" << endl;
			cout << "5 - Adventure Mode-Items (Submenu)" << endl;
			cout << "6 - My Fairies (Submenu)" << endl;
			cout << "0 - Quit" << endl;
			cout << "Your choose: ";
			cin >> i_choose;

			if (iswdigit(i_choose))
			{
				if (atoi(&i_choose) == 0) break;
				else
				{
					system("cls");
					get_submenu(atoi(&i_choose));
					i_choose = 0;
				}
			}
			else{
				cout << "Wrong Menu-Number, try again" << endl;
				cin.get();
				cin.get();
				system("cls");
			}
		} 
	}
	catch (HWLSaveEdit::HWLException &e)
	{
		cout << "  Hyrule Warriors Legends - SaveEditor, V" << HWLSaveEdit::HWLSaveEditorCore::version << endl;
		cout << "________________________________________________" << endl << endl;
		save = nullptr;
		cout << e.what() << endl;
	}
	
	delete save;
	cin.get();

	return 0;
}

void get_submenu(int i_menu_code)
{

	switch (i_menu_code)
	{

	case 1:
	{
			  get_ruby_menu();
			  break;
	}

	case 2:
	{
			  get_chara_menu();
			  break;
	}

	case 3:
	{
			  get_materials_menu();
			  break;
	}

	case 4:
	{
			  get_fairyFood_menu();
			  break;
	}

	case 5:
	{
			  get_amItem_menu();
			  break;
	}

	case 6:
	{
			  get_fairy_menu();
			  break;
	}

	}

}


void get_ruby_menu()
{
	char c_choose;

	while (1)
	{
		cout << "You rubies: " << save->get_rubies() << endl;
		cout << "Menue: " << endl;
		cout << "1 - Change Value" << endl;
		cout << "2 - Maximize Rubies" << endl;
		cout << "0 - back" << endl;
		cout << "Your choose: ";
		cin >> c_choose;


		if (iswdigit(c_choose))
		{
			if (atoi(&c_choose) == 0)
			{
				system("cls");
				break;
			}
			else
			{
				if (atoi(&c_choose) == 1)
				{
					string s_ruby_value = "";
					cout << "Enter your new Value (Max: " << save->rubyMax << ") : ";
					cin >> s_ruby_value;

					if (iswdigit(s_ruby_value[0]))
					{
						int i_rubies = atoi(s_ruby_value.c_str());
						if (i_rubies > save->rubyMax)
							i_rubies = save->rubyMax;

						if (i_rubies < 0)
							i_rubies = 0;

						save->set_rubies(i_rubies);
						save->save_file();

						cout << "The new value was saved. :)" << endl;
						cin.get();
						cin.get();

					}
					else
					{
						cout << "Sorry, wrong value, back to the last menu." << endl;
						cin.get();
						cin.get();
					}
				}

				if (atoi(&c_choose) == 2)
				{
					save->set_rubies(save->rubyMax);
					save->save_file();

					cout << "The max value was saved. :)" << endl;
					cin.get();
					cin.get();
				}
			}
		}
		else{
			cout << "Wrong Menu-Number, try again" << endl;
			cin.get();
			cin.get();
			system("cls");
		}
	}
}

void get_chara_menu()
{
	string s_choose;
	
	
	while (1)
	{
		
		for (int i = 0; i < save->vs_players.size(); i++)
		{
			if (save->get_player(i)->get_name() == "???")
				continue;

			vi_ids.push_back(i);
			cout << "ID: " << i << endl << save->get_player(i)->get_playersStatiForOutput() << endl;
		}

		cout << "Menue: " << endl;
		cout << "1    - Maximize EXP of all Charas " << endl;
		cout << "1,ID - Maximize EXP of this Chara" << endl;
		cout << "2    - Maximize ATK of all Charas " << endl;
		cout << "2,ID - Maximize ATK of this Chara" << endl;
		cout << "3    - Unlock all Charas " << endl;
		cout << "3,ID - Unlock this Chara" << endl;
		cout << "4,ID - Edit Weapons of this Chara (Submenu)" << endl;
		cout << "0    - back" << endl;
		cout << "Your choose: ";
		cin >> s_choose;

		int i_current_id = -1;
		int i_find_pos = s_choose.find(",");
		if (i_find_pos != string::npos)
		{
			string s_substr = s_choose.substr(i_find_pos+1, string::npos);
			i_current_id = atoi(&s_substr[0u]);
		}

		if (iswdigit(s_choose[0]))
		{
			if (atoi(&s_choose[0]) == 0)
			{
				system("cls");
				break;
			}
			else
				change_chara_values(atoi(&s_choose[0]), i_current_id);
		}

		save->save_file();
		system("cls");

	}
}

void change_chara_values(int i_type, int i_chara_id)
{
	//i_type is number of menu-entry

	switch (i_type)
	{
	case 1:
	{
			  if (i_chara_id == -1)
			  {
				  cout << "Maximize EXP of all Charas." << endl;
				  for (int i = 0; i < save->vs_players.size(); i++)
				  {
					  if (save->get_player(i)->get_name() == "???")
						  continue;

					  save->get_player(i)->set_exp(HWLSaveEdit::HWLPlayer::playerEXPMax);
					  save->get_player(i)->save_Player();
				  }
				  cout << "Finish. All your Charas are now battle master!" << endl;
				  cin.clear();
				  getchar();
				  cin.get();
				  system("cls");
			  }
			  else{
				  bool check_id = false;
				  for (int i = 0; i < vi_ids.size(); i++)
				  {
					  if (vi_ids[i] == i_chara_id)
					  {
						  check_id = true;
						  break;
					  }
				  }

				  if (check_id)
				  {
					  cout << "Maximize EXP of Chara with ID " << i_chara_id << endl;
					  save->get_player(i_chara_id)->set_exp(HWLSaveEdit::HWLPlayer::playerEXPMax);
					  save->get_player(i_chara_id)->save_Player();
					  cout << "Finish. This Chara is now a battle master!" << endl;

				  }
				  else{
					  cout << "Sorry, but this Chara-ID doesn't exist!" << endl;

				  }

				  cin.clear();
				  getchar();
				  cin.get();
				  system("cls");
			  }
			  break;
	}

	case 2:
	{
			  if (i_chara_id == -1)
			  {
				  cout << "Maximize ATK of all Charas." << endl;
				  for (int i = 0; i < save->vs_players.size(); i++)
				  {
					  if (save->get_player(i)->get_name() == "???")
						  continue;

					  save->get_player(i)->set_atk(HWLSaveEdit::HWLPlayer::playerATKMax);
					  save->get_player(i)->save_Player();
				  }
				  cout << "Finish. All your Charas are now very strong!" << endl;
				  cin.clear();
				  getchar();
				  cin.get();
				  system("cls");
			  }
			  else{
				  bool check_id = false;
				  for (int i = 0; i < vi_ids.size(); i++)
				  {
					  if (vi_ids[i] == i_chara_id)
					  {
						  check_id = true;
						  break;
					  }
				  }

				  if (check_id)
				  {
					  cout << "Maximize ATK of Chara with ID " << i_chara_id << endl;
					  save->get_player(i_chara_id)->set_atk(HWLSaveEdit::HWLPlayer::playerATKMax);
					  save->get_player(i_chara_id)->save_Player();
					  cout << "Finish. This Chara is now very strong!" << endl;

				  }
				  else{
					  cout << "Sorry, but this Chara-ID doesn't exist!" << endl;

				  }

				  cin.clear();
				  getchar();
				  cin.get();
				  system("cls");
			  }
			  break;
	}

	case 3:
	{
			  if (i_chara_id == -1)
			  {
				  bool b_no_weapon = false;
				  cout << "Unlock all Charas." << endl;
				  for (int i = 0; i < save->vs_players.size(); i++)
				  {
					  if (save->get_player(i)->get_name() == "???")
						  continue;

					  save->get_player(i)->set_isUnlock(true);

					  //Check if the character hasn't a default weapon
					  if (save->get_player(i)->get_weapon_count(0) == 0)
					  {
						  b_no_weapon = true;
						  save->generate_default_weapon(i, 0, 0);
						  save->get_player(i)->get_weapon_slot(0, 0)->save_weapon();
					  }

					  save->get_player(i)->save_Player();
				  }

				  if (b_no_weapon)
					  cout << "Information: One or more characters haven't a default weapon yet.\nDue to security " <<
					  "reasons, they were set automatically." << endl << endl;
				  cout << "Finish. You can choose every character now!" << endl;

				  cin.clear();
				  getchar();
				  cin.get();
				  system("cls");
			  }
			  else{
				  bool check_id = false;
				  for (int i = 0; i < vi_ids.size(); i++)
				  {
					  if (vi_ids[i] == i_chara_id)
					  {
						  check_id = true;
						  break;
					  }
				  }

				  if (check_id)
				  {
					  bool b_no_weapon = false;

					  cout << "Unlock Chara with ID " << i_chara_id << endl;
					  save->get_player(i_chara_id)->set_isUnlock(true);

					  //Check if the character hasn't a default weapon
					  if (save->get_player(i_chara_id)->get_weapon_count(0) == 0)
					  {
						  b_no_weapon = true;
						  save->generate_default_weapon(i_chara_id, 0, 0);
						  save->get_player(i_chara_id)->get_weapon_slot(0, 0)->save_weapon();
					  }

					  save->get_player(i_chara_id)->save_Player();
					  if (b_no_weapon)
						  cout << "Information: Due to security reasons, this character has \nbecome a default weapon automatically." << endl << endl;
					  cout << "Finish. You can choose this character now!" << endl;
				  }
				  else{
					  cout << "Sorry, but this Chara-ID doesn't exist!" << endl;
				  }

				  cin.clear();
				  getchar();
				  cin.get();
				  system("cls");
			  }
			  break;
	}

	case 4:
	{
			  bool check_id = false;
			  for (int i = 0; i < vi_ids.size(); i++)
			  {
				  if (vi_ids[i] == i_chara_id)
				  {
					  check_id = true;
					  break;
				  }
			  }

			  if (check_id)
			  {
				  get_weapons_type(i_chara_id);
			  }
			  else{
				  cout << "Sorry, but this Chara-ID doesn't exist!" << endl;
				  cin.clear();
				  getchar();
				  cin.get();
				  system("cls");
			  }


			  break;
	}

	default:
		break;
	}
}

void get_weapons_type(int i_chara_id)
{
	string s_choose;
	system("cls");

	while (1)
	{
		int i_weapon_count = 0;
		for (int j = 0; j < i_chara_id; j++)
		{
			i_weapon_count = i_weapon_count + save->vi_playerWeaponTypeCount[j];
		}

		for (int i = 0; i < save->vi_playerWeaponTypeCount[i_chara_id]; i++)
		{
			cout << "Weapon-Type-ID: " << i << endl;
			cout << save->vs_playerWeaponTypeNames[i_weapon_count + i] << endl << endl;
		}

		cout << "Weapon Editing of Chara: " << save->vs_players[i_chara_id] << endl << endl;
		cout << "Menue: " << endl;
		cout << "1,ID - Edit Weapons of this type (Submenu) " << endl;
		cout << "0    - back" << endl;
		cout << "Your choose: ";
		cin >> s_choose;

		int i_current_id = -1;
		int i_find_pos = s_choose.find(",");
		if (i_find_pos != string::npos)
		{
			string s_substr = s_choose.substr(i_find_pos + 1, string::npos);
			i_current_id = atoi(&s_substr[0u]);
		}

		if (iswdigit(s_choose[0]))
		{
			if (atoi(&s_choose[0]) == 0)
			{
				system("cls");
				break;
			}
			else if (i_current_id == -1)
			{
				cout << "You forget to give an Weapon-Type ID- Try again. " << endl;
				cin.clear();
				getchar();
				cin.get();
			}
			else{
				if (i_current_id >= save->vi_playerWeaponTypeCount[i_chara_id])
				{
					cout << "This Weapon-ID doesn't exist. Sorry. " << endl;
					cin.clear();
					getchar();
					cin.get();
				}
				else{
					get_weapons(i_chara_id, i_current_id, atoi(&s_choose[0]));

				}
			}
		}

		save->save_file();
		system("cls");

	}

}

void get_weapons(int i_chara_id, int i_type_id, int i_choose)
{
	switch (i_choose)
	{

	case 1:
	{
			  string s_choose;
			  system("cls");

			  while (1)
			  {
				  int i_weapon_count = 0;
				  for (int j = 0; j < i_chara_id; j++)
				  {
					  i_weapon_count = i_weapon_count + save->vi_playerWeaponTypeCount[j];
				  }
				 
				  cout << "Weapon Editing of Chara: " << save->vs_players[i_chara_id] << " and Weapon-Type: " << save->vs_playerWeaponTypeNames[i_weapon_count + i_type_id] << endl << endl;
				  cout << "Menue: " << endl;
				  cout << "1    - List all Weapons of this type (only used Slots)" << endl;
				  cout << "2    - Max LVL of all Weapons (Info: Damage-Base set auto to LVL-Default)" << endl;
				  cout << "2,ID - Max LVL of that Weapon (Info: Damage-Base set auto to LVL-Default)" << endl;
				  cout << "3    - Max Damage-Base of all Weapons (useless for legendary-ones)" << endl;
				  cout << "3,ID - Max Damage-Base of that Weapon (useless for legendary-ones)" << endl;
				  cout << "4    - Max Stars of all Weapons" << endl;
				  cout << "4,ID - Max Stars of that Weapon" << endl;
				  cout << "5    - Make all Weapons to a Legendary One" << endl;
				  cout << "5,ID - Make that Weapon to a Legendary One" << endl;
				  cout << "6,ID - Edit Skills of that Weapon (Submenu)" << endl;
				  cout << "7    - Unlock Skills for all Weapons(Set needed Kills of all to 0)" << endl;
				  cout << "7,ID - Unlock Skills for this Weapon(Set needed Kills of all to 0)" << endl;
				  cout << "8    - Generate and add a new Default Weapon of that type" << endl;
				  cout << "9    - Delete the last weapon (get a free slot)" << endl;
				  cout << "0    - back" << endl;
				  cout << "Your choose: ";
				  cin >> s_choose;

				  int i_current_id = -1;
				  int i_find_pos = s_choose.find(",");
				  if (i_find_pos != string::npos)
				  {
					  string s_substr = s_choose.substr(i_find_pos + 1, string::npos);
					  i_current_id = atoi(&s_substr[0u]);
				  }

				  if (iswdigit(s_choose[0]))
				  {
					  if (atoi(&s_choose[0]) == 0)
					  {
						  system("cls");
						  break;
					  }
					  else{
						  if (i_current_id >= save->get_player(i_chara_id)->get_weapon_count(i_type_id) || i_current_id < -1)
						  {
							  cout << "This Weapon-ID doesn't exist. Sorry. " << endl;
							  cin.clear();
							  getchar();
							  cin.get();
						  }
						  else{
							  change_weapon_values(i_chara_id, i_type_id, i_current_id, atoi(&s_choose[0]));

						  }
					  }
				  }

				  save->save_file();
				  system("cls");

			  }
	}

	default:
		break;
	}

}
void change_weapon_values(int i_chara_id, int i_type_id, int i_current_id, int i_choose)
{
	switch (i_choose)
	{

	case 1:
	{
			  system("cls");

			  int i_used_slot_count = save->get_player(i_chara_id)->get_weapon_count(i_type_id);
			  if (i_used_slot_count != 0)
			  {
				  for (int i = 0; i < i_used_slot_count; i++)
				  {
					  cout << "ID: " << i << endl << save->get_player(i_chara_id)->get_weapon_slot(i_type_id, i)->get_WeaponsForOutput() << endl;
				  }
			  }else
			  {
				  cout << "There is no weapon of this type" << endl;
			  }

			  cin.clear();
			  getchar();
			  cin.get();
			  break;
	}

	case 2:
	{
			  if (i_type_id == 4 && i_chara_id == 0)
			  {
				  system("cls");
				  cout << "Sorry, you can't max the Lvl of the Master Sword, \ndue to there is only this ONE Sword." << endl;
				  cin.clear();
				  getchar();
				  cin.get();
			  }else
			  {
				  if (i_current_id == -1)
				  {
					  cout << "Maximize LVL of all Weapons" << endl;
					  int i_used_slot_count = save->get_player(i_chara_id)->get_weapon_count(i_type_id);
					  if (i_used_slot_count != 0)
					  {
						  for (int i = 0; i < i_used_slot_count; i++)
						  {
							  save->get_player(i_chara_id)->get_weapon_slot(i_type_id, i)->change_lvl(HWLSaveEdit::HWLWeapon::weaponLVLMax);
							  save->get_player(i_chara_id)->get_weapon_slot(i_type_id, i)->save_weapon();
						  }
						  cout << "Finish. You now have the strongest weapons." << endl;
					  }
					  else
					  {
						  cout << "There is no weapon of this type" << endl;
					  }

				  }else
				  {
					  cout << "Maximize LVL of Weapon with ID: " << i_current_id << endl;
					  save->get_player(i_chara_id)->get_weapon_slot(i_type_id, i_current_id)->change_lvl(HWLSaveEdit::HWLWeapon::weaponLVLMax);
					  save->get_player(i_chara_id)->get_weapon_slot(i_type_id, i_current_id)->save_weapon();
					  cout << "Finish. You now have a very strong weapons." << endl;
				  }

				  cin.clear();
				  getchar();
				  cin.get();
			  }

			  break;
	}

	case 3:
	{
			  if (i_type_id == 4 && i_chara_id == 0)
			  {
				  system("cls");
				  cout << "Sorry, you can't max the Damage-Base of the Master Sword, \ndue to it's a unique legendary Weapon." << endl;
				  cin.clear();
				  getchar();
				  cin.get();
			  }
			  else
			  {
				  if (i_current_id == -1)
				  {
					  cout << "Maximize Damage-Base of all Weapons" << endl;
					  int i_used_slot_count = save->get_player(i_chara_id)->get_weapon_count(i_type_id);
					  if (i_used_slot_count != 0)
					  {
						  for (int i = 0; i < i_used_slot_count; i++)
						  {
							  save->get_player(i_chara_id)->get_weapon_slot(i_type_id, i)->change_damage_base(HWLSaveEdit::HWLWeapon::weaponDamageBaseMax);
							  save->get_player(i_chara_id)->get_weapon_slot(i_type_id, i)->save_weapon();
						  }
						  cout << "Finish. You now enough Base-Damage of all your Wapons of this type." << endl;
					  }
					  else
					  {
						  cout << "There is no weapon of this type" << endl;
					  }

				  }
				  else
				  {
					  cout << "Maximize Damage-Base of Weapon with ID: " << i_current_id << endl;
					  save->get_player(i_chara_id)->get_weapon_slot(i_type_id, i_current_id)->change_damage_base(HWLSaveEdit::HWLWeapon::weaponDamageBaseMax);
					  save->get_player(i_chara_id)->get_weapon_slot(i_type_id, i_current_id)->save_weapon();
					  cout << "Finish. You now enough Base-Damage" << endl;
				  }

				  cin.clear();
				  getchar();
				  cin.get();
			  }

			  break;
	}

	case 4:
	{
			  if (i_current_id == -1)
			  {
				  cout << "Maximize Stars of all Weapons" << endl;
				  int i_used_slot_count = save->get_player(i_chara_id)->get_weapon_count(i_type_id);
				  if (i_used_slot_count != 0)
				  {
					  for (int i = 0; i < i_used_slot_count; i++)
					  {
						  save->get_player(i_chara_id)->get_weapon_slot(i_type_id, i)->change_stars(HWLSaveEdit::HWLWeapon::weaponStarsMax);
						  save->get_player(i_chara_id)->get_weapon_slot(i_type_id, i)->save_weapon();
					  }
					  cout << "Finish. You now all 5 Stars Weapons." << endl;
				  }
				  else
				  {
					  cout << "There is no weapon of this type" << endl;
				  }

			  }
			  else
			  {
				  cout << "Maximize Stars of Weapon with ID: " << i_current_id << endl;
				  save->get_player(i_chara_id)->get_weapon_slot(i_type_id, i_current_id)->change_stars(HWLSaveEdit::HWLWeapon::weaponStarsMax);
				  save->get_player(i_chara_id)->get_weapon_slot(i_type_id, i_current_id)->save_weapon();
				  cout << "Finish. You now a 5 Stars Weapon." << endl;
			  }

			  cin.clear();
			  getchar();
			  cin.get();

			  break;
	}

	case 5:
	{
			  if (i_type_id == 4 && i_chara_id == 0)
			  {
				  system("cls");
				  cout << "Sorry, you can't change the legendary-state of the Master Sword, \ndue to it's a unique legendary Weapon." << endl;
				  cin.clear();
				  getchar();
				  cin.get();
			  }
			  else
			  {
				  if (i_current_id == -1)
				  {
					  cout << "Make all Weapons to Legendary ones." << endl;
					  int i_used_slot_count = save->get_player(i_chara_id)->get_weapon_count(i_type_id);
					  if (i_used_slot_count != 0)
					  {
						  for (int i = 0; i < i_used_slot_count; i++)
						  {
							  save->get_player(i_chara_id)->get_weapon_slot(i_type_id, i)->set_state(HWLSaveEdit::HWLWeapon::weaponStateValuesHex[1]);
							  save->get_player(i_chara_id)->get_weapon_slot(i_type_id, i)->set_skill_slot(0, 0x2A);
							  save->get_player(i_chara_id)->get_weapon_slot(i_type_id, i)->save_weapon();
						  }
						  cout << "Finish. You now have legendary-weapons \n(and the legendary Skill at Skill-Slot 1)" << endl;
					  }
					  else
					  {
						  cout << "There is no weapon of this type" << endl;
					  }

				  }
				  else
				  {
					  cout << "Make weapon with ID: " << i_current_id << " to a legendary one" <<  endl;
					  save->get_player(i_chara_id)->get_weapon_slot(i_type_id, i_current_id)->set_state(HWLSaveEdit::HWLWeapon::weaponStateValuesHex[1]);
					  save->get_player(i_chara_id)->get_weapon_slot(i_type_id, i_current_id)->set_skill_slot(0, 0x2A);
					  save->get_player(i_chara_id)->get_weapon_slot(i_type_id, i_current_id)->save_weapon();
					  cout << "Finish. You now have a legendary-weapon \n(and the legendary Skill at Skill-Slot 1)" << endl;
				  }

				  cin.clear();
				  getchar();
				  cin.get();
			  }

			  break;
	}

	case 6:
	{
			  if (i_current_id == -1)
			  {
				  cout << "You forgot the Weapon-ID, please try again." << endl;
				  cin.clear();
				  getchar();
				  cin.get();
			  }
			  else
			  {
				  get_skills(i_chara_id, i_type_id, i_current_id);
			  }

			  break;
	}

	case 7:
	{
			  if (i_current_id == -1)
			  {
				  cout << "Unlocking Skills for all Weapons" << endl;
				  int i_used_slot_count = save->get_player(i_chara_id)->get_weapon_count(i_type_id);
				  if (i_used_slot_count != 0)
				  {
					  for (int i = 0; i < i_used_slot_count; i++)
					  {
						  for (int j = 0; j < 8; j++)
						  {
							  save->get_player(i_chara_id)->get_weapon_slot(i_type_id, i)->set_skill_slot_kill(j, 0);
						  }

						  save->get_player(i_chara_id)->get_weapon_slot(i_type_id, i)->save_weapon();
					  }
					  cout << "Finish. You now have unlocked all Skills of all Weapons." << endl;
				  }
				  else
				  {
					  cout << "There is no weapon of this type" << endl;
				  }

			  }
			  else
			  {
				  cout << "Maximize Stars of Weapon with ID: " << i_current_id << endl;

				  for (int i = 0; i < 8; i++)
				  {
					  save->get_player(i_chara_id)->get_weapon_slot(i_type_id, i_current_id)->set_skill_slot_kill(i, 0);
				  }
				  save->get_player(i_chara_id)->get_weapon_slot(i_type_id, i_current_id)->save_weapon();

				  cout << "Finish. You now have unlocked all Skills of this Weapon." << endl;
			  }

			  cin.clear();
			  getchar();
			  cin.get();

			  break;
	}

	case 8:
	{
			  system("cls");

			  cout << "Generate a new Weapon " << endl;

			  int i_used_slot_count = save->get_player(i_chara_id)->get_weapon_count(i_type_id);
			  int i_max_used_slots = 0;

			  if (i_type_id == 4 && i_chara_id == 0)
				  i_max_used_slots = 1;
			  else
				  i_max_used_slots = HWLSaveEdit::HWLPlayer::playerWeaponSlotsMax;

			  if (i_used_slot_count < i_max_used_slots)
			  {
				  save->generate_default_weapon(i_chara_id, i_type_id, i_used_slot_count);
				  save->get_player(i_chara_id)->get_weapon_slot(i_type_id, i_used_slot_count)->save_weapon();
				  cout << "Finish. You now have a new Default Weapon." << endl;
			  }
			  else
			  {
				  cout << "You can't take anymore weapons of this type" << endl;
			  }

			  cin.clear();
			  getchar();
			  cin.get();
			  break;
	}

	case 9:
	{
			  cout << "Delete last weapon of that type. " << endl;

			  int i_used_slot_count = save->get_player(i_chara_id)->get_weapon_count(i_type_id);
			  int i_max_used_slots = 0;

			  if (i_used_slot_count > 0)
			  {
				  if (i_type_id == 4 && i_chara_id == 0)
					  i_max_used_slots = 1;
				  else
					  i_max_used_slots = HWLSaveEdit::HWLPlayer::playerWeaponSlotsMax;

				  int i_current_last_weapon_id = (i_max_used_slots - 1) - (i_max_used_slots - i_used_slot_count);

				  if (i_type_id == 0)
				  {
					  if (save->get_player(i_chara_id)->get_weapon_count(i_type_id) != 1)
					  {
						  save->get_player(i_chara_id)->get_weapon_slot(i_type_id, i_current_last_weapon_id)->delete_weapon();
						  save->get_player(i_chara_id)->get_weapon_slot(i_type_id, i_current_last_weapon_id)->save_weapon();
						  cout << "Finish. You deleted it." << endl;
					  }
					  else{
						  cout << "You are going to delete the last weapon of the first weapon-type \nof this character.\n"
							  << "This can be a dangerous operation for your save and can result in a \nunstable state"
							  << "of your savegame. \nDue to security reasons you can't delete it per console-variant\n"
							  << "of that programm. Sorry! \nPlease use the GUI-Version for that." << endl;
						  //<< "Make sure, that you lock this character after that to avoid such problems. \n"
						  //<< "Do you really want to delete this last weapon?" << endl;
						  //save->get_player(i_chara_id)->get_weapon_slot(i_type_id, i_current_id)->delete_weapon();
						  //save->get_player(i_chara_id)->get_weapon_slot(i_type_id, i_current_id)->save_weapon();
						  //cout << "Finish. You deleted it." << endl;
					  }
				  }
				  else{
					  save->get_player(i_chara_id)->get_weapon_slot(i_type_id, i_current_last_weapon_id)->delete_weapon();
					  save->get_player(i_chara_id)->get_weapon_slot(i_type_id, i_current_last_weapon_id)->save_weapon();
					  cout << "Finish. You deleted it." << endl;
				  }
			  }
			  else{
				  cout << "Sorry. You don't have any weapons." << endl;

			  }


			  cin.clear();
			  getchar();
			  cin.get();

			  break;
	}

	default:
		break;
	}
}

void get_skills(int i_chara_id, int i_weapon_type_id, int i_weapon_slot_id)
{
	string s_choose;
	system("cls");

	while (1)
	{
		int i_weapon_count = 0;
		for (int j = 0; j < i_chara_id; j++)
		{
			i_weapon_count = i_weapon_count + save->vi_playerWeaponTypeCount[j];
		}

		cout << "Skill Editing of Weapon: " << i_weapon_slot_id << " from Chara '" << save->vs_players[i_chara_id] << "'\nwith Weapon-Type: "
			<< save->vs_playerWeaponTypeNames[i_weapon_count + i_weapon_type_id] << endl << endl;

		cout << save->get_player(i_chara_id)->get_weapon_slot(i_weapon_type_id, i_weapon_slot_id)->get_WeaponsSkillsForOutput() << endl;

		cout << "Menue: " << endl;
		cout << "1          - List available Skills" << endl;
		cout << "2,ID,ID    - Change Skill (first ID = Slot, second ID = Skill-ID)" << endl;
		cout << "0          - back" << endl;
		cout << "Your choose: ";
		cin >> s_choose;

		int i_slot_id = 0;
		int i_skill_id = -1;
		int i_find_pos = s_choose.find(",");
		if (i_find_pos != string::npos)
		{
			string s_substr = s_choose.substr(i_find_pos + 1, string::npos);
			i_slot_id = atoi(&s_substr[0u]);

			int i_find_pos2 = s_substr.find(",");
			if (i_find_pos2 != string::npos)
			{
				string s_substr2 = s_substr.substr(i_find_pos2 + 1, string::npos);
				i_skill_id = atoi(&s_substr2[0u]);
			}
		

		}

		if (iswdigit(s_choose[0]))
		{
			if (atoi(&s_choose[0]) == 0)
			{
				system("cls");
				break;
			}
			else{
				if (i_slot_id > 8 || i_slot_id < 0 || i_skill_id >= (int)HWLSaveEdit::HWLWeapon::weaponSkillNames.size() || i_skill_id < -1)
				{
					cout << "This Slot-ID or Skill-ID doesn't exist. Try again." << endl;
					cin.clear();
					getchar();
					cin.get();
				}
				else{
					change_skill_values(i_chara_id, i_weapon_type_id, i_weapon_slot_id, i_slot_id, i_skill_id, atoi(&s_choose[0]));

				}
			}
		}

		save->save_file();
		system("cls");

	}
}

void change_skill_values(int i_chara_id, int i_weapon_type_id, int i_weapon_slot_id, int i_skill_slot_id, int i_skill_id, int i_choose)
{
	switch (i_choose)
	{
	case 1:
	{
			  system("cls");
			  for (int i = 0; i < HWLSaveEdit::HWLWeapon::weaponSkillNames.size(); i++)
			  {
				  cout << "ID: " << i << "  -  " << HWLSaveEdit::HWLWeapon::weaponSkillNames[i] << endl;
			  }
			  cin.clear();
			  getchar();
			  cin.get();
			  break;
	}

	case 2:
	{
			  if (i_skill_slot_id == 0 || i_skill_id == -1)
			  {
				  cout << endl;
				  cout << "Edit Skills " << endl;
				  cout << "This Slot-ID or Skill-ID doesn't exist. Try again." << endl;
			  }else
			  {
				  cout << endl;
				  cout << "Edit Skill for Slot " << i_skill_slot_id << endl;
				  int i_orignal_skill_id = i_skill_id;

				  if (i_skill_id >= (HWLSaveEdit::HWLWeapon::weaponSkillNames.size() - 1))
					  i_skill_id = HWLSaveEdit::HWLWeapon::weaponSkillValueNoSkill;
				
				  save->get_player(i_chara_id)->get_weapon_slot(i_weapon_type_id, i_weapon_slot_id)->set_skill_slot(i_skill_slot_id - 1, i_skill_id);
				  save->get_player(i_chara_id)->get_weapon_slot(i_weapon_type_id, i_weapon_slot_id)->save_weapon();
				  cout << "Finish. You set to Slot " << i_skill_slot_id << " following Skill: '" << HWLSaveEdit::HWLWeapon::weaponSkillNames[i_orignal_skill_id] << "'" << endl;
			  }

			  cin.clear();
			  getchar();
			  cin.get();
	}

	default:
		break;

	}
}

void get_materials_menu()
{
	char c_choose;

	while (1)
	{
		cout << "Menue: " << endl;
		cout << "1 - Edit bronze Materials" << endl;
		cout << "2 - Edit silver Materials" << endl;
		cout << "3 - Edit gold Materials" << endl;
		cout << "0 - back" << endl;
		cout << "Your choose: ";
		cin >> c_choose;


		if (iswdigit(c_choose))
		{
			if (atoi(&c_choose) == 0)
			{
				system("cls");
				break;
			}
			else
				get_materials_submenu(atoi(&c_choose));
		}
		else{
			cout << "Wrong Menu-Number, try again" << endl;
			cin.get();
			cin.get();
			system("cls");
		}
	}
}

void get_materials_submenu(int i_type)
{
	int i_size = -1;

	switch (i_type)
	{
	case 1:
		i_size = save->vs_bronzeMaterials.size();
		break;

	case 2:
		i_size = save->vs_silverMaterials.size();
		break;

	case 3:
		i_size = save->vs_goldMaterials.size();
		break;

	default:
		break;
	}


	if (i_type > 0)
	{
		string s_choose;

		while (1)
		{

			for (int i = 0; i < i_size; i++)
			{
				cout << "ID: " << i << endl << save->get_material(i, i_type - 1)->get_MaterialForOutput() << endl;
			}

			cout << "Menue: " << endl;
			cout << "1,ID - Change Value of this Material" << endl;
			cout << "2    - Maximize Value of all Material " << endl;
			cout << "2,ID - Maximize Value of this Material " << endl;
			cout << "0    - back" << endl;
			cout << "Your choose: ";
			cin >> s_choose;

			int i_current_id = -1;
			int i_find_pos = s_choose.find(",");
			if (i_find_pos != string::npos)
			{
				string s_substr = s_choose.substr(i_find_pos + 1, string::npos);
				i_current_id = atoi(&s_substr[0u]);
			}

			if (iswdigit(s_choose[0]))
			{
				if (atoi(&s_choose[0]) == 0)
				{
					system("cls");
					break;
				}
				else
					change_materials_values(atoi(&s_choose[0]), i_current_id, i_type-1, i_size);
			}

			save->save_file();
		}

	}

}

void change_materials_values(int i_choose, int i_material_id, int i_type, int i_size)
{
	//i_choose is number of menu-entry

	switch (i_choose)
	{
	case 1:
	{
			  if (i_material_id == -1)
			  {
				  cout << "No ID given, please try again with an ID (eq: 1,5)" << endl;
				  cin.clear();
				  getchar();
				  cin.get();
				  system("cls");
			  }
			  else{
				  bool check_id = false;

				  if (i_material_id < i_size && i_material_id > 0)
					  check_id = true;


				  if (check_id)
				  {
					  string s_material_value = "";
					  cout << "Enter your new Value (Max: " << HWLSaveEdit::HWLMaterial::materialValueMax << ") : ";
					  cin >> s_material_value;

					  if (iswdigit(s_material_value[0]))
					  {
						  int i_material_value = atoi(s_material_value.c_str());
						  if (i_material_value > HWLSaveEdit::HWLMaterial::materialValueMax)
							  i_material_value = HWLSaveEdit::HWLMaterial::materialValueMax;

						  if (i_material_value < 0)
							  i_material_value = 0;

						  cout << "Changing Value of Material with ID " << i_material_id << endl;
						  save->get_material(i_material_id, i_type)->set_value(i_material_value);
						  save->get_material(i_material_id, i_type)->save_Material();
						  cout << "Finish. You have now " << i_material_value  << " of this material! "<< endl;

					  }
					  else
					  {
						  cout << "Sorry, wrong value, back to the last menu." << endl;
					  }

				  }
				  else{
					  cout << "Sorry, but this Material-ID doesn't exist!" << endl;

				  }

				  cin.clear();
				  getchar();
				  cin.get();
				  system("cls");
			  }
			  break;
	}

	case 2:
	{
			  if (i_material_id == -1)
			  {
				  cout << "Maximize Value of all Materials" << endl;
				  for (int i = 0; i < i_size; i++)
				  {
					  save->get_material(i, i_type)->set_value(HWLSaveEdit::HWLMaterial::materialValueMax);
					  save->get_material(i, i_type)->save_Material();
				  }
				  cout << "Finish. You have now enough of all material!s" << endl;
				  cin.clear();
				  getchar();
				  cin.get();
				  system("cls");

			  }
			  else{
				  bool check_id = false;

				  if (i_material_id < i_size && i_material_id > 0)
					  check_id = true;

				  if (check_id)
				  {
					  cout << "Maximize Value of Material with ID " << i_material_id << endl;
					  save->get_material(i_material_id, i_type)->set_value(HWLSaveEdit::HWLMaterial::materialValueMax);
					  save->get_material(i_material_id, i_type)->save_Material();
					  cout << "Finish. You have now enough of this material!" << endl;

				  }
				  else{
					  cout << "Sorry, but this Material-ID doesn't exist!" << endl;

				  }

				  cin.clear();
				  getchar();
				  cin.get();
				  system("cls");
			  }
			  break;
	}

	default:
		break;
	}
}



void get_fairyFood_menu()
{
	string s_choose;


	while (1)
	{
		cout << "Menue: " << endl;
		cout << "1    - List Fairy-Foods (0-65) " << endl;
		cout << "2    - List Fairy-Foods (66-" << save->vs_fairyFood.size()-1 << ") " << endl;
		cout << "3,ID - Change Value of this Fairy-Food" << endl;
		cout << "4    - Maximize Value of all Fairy-Foods " << endl;
		cout << "4,ID - Maximize Value of this Fairy-Food " << endl;
		cout << "5    - Maximize Value of all Gratitude Crystals " << endl;
		cout << "0    - back" << endl;
		cout << "Your choose: ";
		cin >> s_choose;

		int i_current_id = -1;
		int i_find_pos = s_choose.find(",");
		if (i_find_pos != string::npos)
		{
			string s_substr = s_choose.substr(i_find_pos + 1, string::npos);
			i_current_id = atoi(&s_substr[0u]);
		}

		if (iswdigit(s_choose[0]))
		{
			if (atoi(&s_choose[0]) == 0)
			{
				system("cls");
				break;
			}
			else
				change_fairyFood_values(atoi(&s_choose[0]), i_current_id);
		}

		save->save_file();

		if(atoi(&s_choose[0]) > 2)
			system("cls");

	}
}


void change_fairyFood_values(int i_choose, int i_fairyFood_id)
{
	//i_choose is number of menu-entry

	switch (i_choose)
	{
	case 1:
	{
			  system("cls");

			  for (int i = 0; i <= 65; i++)
			  {
				  cout << "ID: " << i << endl << save->get_fairyFood(i)->get_FairyFoodForOutput() << endl;
			  }
			  break;
	}

	case 2:
	{
			  system("cls");

			  for (int i = 66; i < save->vs_fairyFood.size(); i++)
			  {
				  cout << "ID: " << i << endl << save->get_fairyFood(i)->get_FairyFoodForOutput() << endl;
			  }
			  break;
	}

	case 3:
	{
			  if (i_fairyFood_id == -1)
			  {
				  cout << "No ID given, please try again with an ID (eq: 3,5)" << endl;
				  cin.clear();
				  getchar();
				  cin.get();
				  system("cls");
			  }
			  else{
				  bool check_id = false;

				  if (i_fairyFood_id < save->vs_fairyFood.size() && i_fairyFood_id > 0)
					  check_id = true;


				  if (check_id)
				  {
					  string s_fairyFood_value = "";
					  cout << "Enter your new Value (Max: " << HWLSaveEdit::HWLFairyFood::fairyFoodlValueMax << ") : ";
					  cin >> s_fairyFood_value;

					  if (iswdigit(s_fairyFood_value[0]))
					  {
						  int i_fairyFood_value = atoi(s_fairyFood_value.c_str());
						  if (i_fairyFood_value > HWLSaveEdit::HWLFairyFood::fairyFoodlValueMax)
							  i_fairyFood_value = HWLSaveEdit::HWLFairyFood::fairyFoodlValueMax;

						  if (i_fairyFood_value < 0)
							  i_fairyFood_value = 0;

						  cout << "Changing Value of FairyFood with ID " << i_fairyFood_id << endl;
						  save->get_fairyFood(i_fairyFood_id)->set_value(i_fairyFood_value);
						  save->get_fairyFood(i_fairyFood_id)->save_FairyFood();
						  cout << "Finish. You have now " << i_fairyFood_value << " of this FairyFood! " << endl;

					  }
					  else
					  {
						  cout << "Sorry, wrong value, back to the last menu." << endl;
					  }

				  }
				  else{
					  cout << "Sorry, but this FairyFood-ID doesn't exist!" << endl;

				  }

				  cin.clear();
				  getchar();
				  cin.get();
				  system("cls");
			  }
			  break;
	}

	case 4:
	{
			  if (i_fairyFood_id == -1)
			  {
				  cout << "Maximize Value of all FairyFoods" << endl;
				  for (int i = 0; i < save->vs_fairyFood.size(); i++)
				  {
					  save->get_fairyFood(i)->set_value(HWLSaveEdit::HWLFairyFood::fairyFoodlValueMax);
					  save->get_fairyFood(i)->save_FairyFood();
				  }

				  cout << "Finish. You have now enough of all FairyFoods!" << endl;
				  cin.clear();
				  getchar();
				  cin.get();
				  system("cls");

			  }
			  else{
				  bool check_id = false;

				  if (i_fairyFood_id < save->vs_fairyFood.size() && i_fairyFood_id > 0)
					  check_id = true;

				  if (check_id)
				  {
					  cout << "Maximize Value of FairyFood with ID " << i_fairyFood_id << endl;
					  save->get_fairyFood(i_fairyFood_id)->set_value(HWLSaveEdit::HWLFairyFood::fairyFoodlValueMax);
					  save->get_fairyFood(i_fairyFood_id)->save_FairyFood();
					  cout << "Finish. You have now enough of this FairyFood!" << endl;

				  }
				  else{
					  cout << "Sorry, but this FairyFood-ID doesn't exist!" << endl;

				  }

				  cin.clear();
				  getchar();
				  cin.get();
				  system("cls");
			  }
			  break;
	}

	case 5:
	{
			  cout << "Maximize Value of all Gratitude Crystals" << endl;
			  for (int i = HWLSaveEdit::HWLFairyFood::fairyGratitudeCrystalIDBegin; i <= HWLSaveEdit::HWLFairyFood::fairyGratitudeCrystalIDEnd; i++)
			  {
				  save->get_fairyFood(i)->set_value(HWLSaveEdit::HWLFairyFood::fairyFoodlValueMax);
				  save->get_fairyFood(i)->save_FairyFood();
			  }

			  cout << "Finish. You have now enough of all Gratitude Crystals!" << endl;
			  cin.clear();
			  getchar();
			  cin.get();
			  system("cls");
	}


	default:
		break;

	}
}

void get_amItem_menu()
{
	char c_choose;

	while (1)
	{
		cout << "Menue: " << endl;
		cout << "1 - List all Map-Items" << endl;
		cout << "2 - Maximize Adventure-Map Items" << endl;
		cout << "3 - Maximize GreatSea-Map Items" << endl;
		cout << "4 - Maximize MasterQuest-Map Items" << endl;
		cout << "5 - Maximize Twilight-Map Items" << endl;
		cout << "6 - Maximize Termina-Map Items" << endl;
		cout << "0 - back" << endl;
		cout << "Your choose: ";
		cin >> c_choose;


		if (iswdigit(c_choose))
		{
			if (atoi(&c_choose) == 0)
			{
				system("cls");
				break;
			}
			else
				change_amItem_values(atoi(&c_choose));
		}
		else{
			cout << "Wrong Menu-Number, try again" << endl;
			cin.get();
			cin.get();
			system("cls");
		}

		save->save_file();

	}
}

void change_amItem_values(int i_choose)
{
	//i_choose is number of menu-entry

	switch (i_choose)
	{
	case 1:
	{
			  system("cls");

			  int i_max_ids = HWLSaveEdit::HWLAdventureModeItems::amItemPerMapMax * save->get_adventureMode_maxItemCount();

			  for (int i = 0; i < i_max_ids; i++)
			  {
				  cout << save->get_amItem(i)->get_AMItemForOutput() << endl;
			  }

			  cout << "Finish. Press a key to go back." << endl;
			  cin.clear();
			  getchar();
			  cin.get();
			  system("cls");
			  break;
	}

	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
	{
			  if (i_choose == 2)
				  cout << "Maximize Value of all Adventure-Map Items" << endl;
			  else if (i_choose == 3)
				  cout << "Maximize Value of all GreatSea-Map Items" << endl;
			  else if (i_choose == 4)
				  cout << "Maximize Value of all MasterQuest-Map Items" << endl;
			  else if (i_choose == 5)
				  cout << "Maximize Value of all Twilight-Map Items" << endl;
			  else
				  cout << "Maximize Value of all Termina-Map Items" << endl;

			  for (int i = 0; i < HWLSaveEdit::HWLAdventureModeItems::amItemPerMapMax; i++)
			  {
				  save->get_amItem(i, i_choose - 2)->set_value(HWLSaveEdit::HWLAdventureModeItems::amItemValueMax);
				  save->get_amItem(i, i_choose - 2)->save_AMItem();
			  }

			  cout << "Finish. You have now enough of those Map-Items" << endl;
			  cin.clear();
			  getchar();
			  cin.get();
			  system("cls");
			  break;
	}

	default:
		break;

	}
}



void get_fairy_menu()
{
	string s_choose;


	while (1)
	{

		for (int i = 0; i < save->fairiesMax; i++)
		{
			cout << "ID: " << i << endl << save->get_fairy(i)->get_fairyForOutput() << endl;
		}

		cout << "Menue: " << endl;
		cout << "1,ID - Change Name of this Fairy" << endl;
		cout << "2    - Maximize Lvl of all Fairies" << endl;
		cout << "2,ID - Maximize Lvl of this Fairy" << endl;
		cout << "3    - Maximize Trust of all Fairies" << endl;
		cout << "3,ID - Maximize Trust of this Fairy" << endl;
		cout << "4    - Unlock all Fairies" << endl;
		cout << "4,ID - Unlock this Fairy" << endl;
		cout << "0    - back" << endl;
		cout << "Your choose: ";
		cin >> s_choose;

		int i_current_id = -1;
		int i_find_pos = s_choose.find(",");
		if (i_find_pos != string::npos)
		{
			string s_substr = s_choose.substr(i_find_pos + 1, string::npos);
			i_current_id = atoi(&s_substr[0u]);
		}

		if (iswdigit(s_choose[0]))
		{
			if (atoi(&s_choose[0]) == 0)
			{
				system("cls");
				break;
			}
			else
				change_fairy_values(atoi(&s_choose[0]), i_current_id);
		}

		save->save_file();

		if (atoi(&s_choose[0]) > 2)
			system("cls");

	}
}

void change_fairy_values(int i_choose, int i_fairy_id)
{
	//i_choose is number of menu-entry

	switch (i_choose)
	{
	case 1:
	{
			  system("cls");

			  if (i_fairy_id == -1)
			  {
				  cout << "No ID given, please try again with an ID (eq: 1,5)" << endl;
				  cin.clear();
				  getchar();
				  cin.get();
				  system("cls");
			  }
			  else{
				  bool check_id = false;

				  if (i_fairy_id < save->fairiesMax && i_fairy_id >= 0)
					  check_id = true;

				  if (check_id)
				  {
					  string s_fairy_name = "";
					  cout << "Enter a new Name (Max: "<< HWLSaveEdit::HWLFairy::fairyNameLength <<" chars) : ";
					  cin >> s_fairy_name;

					  if (s_fairy_name.size() <= HWLSaveEdit::HWLFairy::fairyNameLength)
					  {
						  cout << "Changing Name of Fairy with ID:" << i_fairy_id << endl;
						  cout << " Old name: " << save->get_fairy(i_fairy_id)->get_name() << endl;
						  save->get_fairy(i_fairy_id)->set_name(s_fairy_name);
						  cout << " New name: " << save->get_fairy(i_fairy_id)->get_name() << endl;

						  save->get_fairy(i_fairy_id)->save_Fairy();
						  cout << "Finish. Press a key to go back." << endl;


					  }
					  else
					  {
						  cout << "Sorry. The name is too long, back to the last menu." << endl;
					  }
				  }
				  else{
					  cout << "Sorry, but this Fairy-ID doesn't exist!" << endl;
				  }

				  cin.clear();
				  getchar();
				  cin.get();
				  system("cls");
			  }


			  break;
	}

	case 2:
	{
			  system("cls");

			  if (i_fairy_id == -1)
			  {
				  cout << "Maximize Lvl of all Fairies" << endl;

				  for (int i = 0; i < save->fairiesMax; i++)
				  {
					  save->get_fairy(i)->set_lvl(HWLSaveEdit::HWLFairy::fairyLVLMax);
					  save->get_fairy(i)->save_Fairy();
				  }

				  cout << "Finish. Press a key to go back." << endl;
				  cin.clear();
				  getchar();
				  cin.get();
				  system("cls");
			  }else
			  {
				  bool check_id = false;

				  if (i_fairy_id < save->fairiesMax && i_fairy_id >= 0)
					  check_id = true;

				  if (check_id)
				  {

					  cout << "Maximize Lvl of Fairy with ID: " << i_fairy_id << endl;
					  save->get_fairy(i_fairy_id)->set_lvl(HWLSaveEdit::HWLFairy::fairyLVLMax);
					  save->get_fairy(i_fairy_id)->save_Fairy();
					  cout << "Finish. Press a key to go back." << endl;

				  }
				  else{
					  cout << "Sorry, but this Fairy-ID doesn't exist!" << endl;
				  }

				  cin.clear();
				  getchar();
				  cin.get();
				  system("cls");
			  }

			  break;
	}

	case 3:
	{
			  system("cls");

			  if (i_fairy_id == -1)
			  {
				  cout << "Maximize Trust of all Fairies" << endl;

				  for (int i = 0; i < save->fairiesMax; i++)
				  {
					  save->get_fairy(i)->set_trust(HWLSaveEdit::HWLFairy::fairyTrustMax);
					  save->get_fairy(i)->save_Fairy();
				  }

				  cout << "Finish. Press a key to go back." << endl;
				  cin.clear();
				  getchar();
				  cin.get();
				  system("cls");
			  }
			  else
			  {
				  bool check_id = false;

				  if (i_fairy_id < save->fairiesMax && i_fairy_id >= 0)
					  check_id = true;

				  if (check_id)
				  {

					  cout << "Maximize Trust of Fairy with ID: " << i_fairy_id << endl;
					  save->get_fairy(i_fairy_id)->set_trust(HWLSaveEdit::HWLFairy::fairyTrustMax);
					  save->get_fairy(i_fairy_id)->save_Fairy();
					  cout << "Finish. Press a key to go back." << endl;

				  }
				  else{
					  cout << "Sorry, but this Fairy-ID doesn't exist!" << endl;
				  }

				  cin.clear();
				  getchar();
				  cin.get();
				  system("cls");
			  }

			  break;
	}

	case 4:
	{
			  system("cls");

			  if (i_fairy_id == -1)
			  {
				  cout << "Unlock all Fairies" << endl;

				  for (int i = 0; i < save->fairiesMax; i++)
				  {
					  save->get_fairy(i)->set_isUnlock(true);
					  save->get_fairy(i)->save_Fairy();
				  }

				  cout << "Finish. Press a key to go back." << endl;
				  cin.clear();
				  getchar();
				  cin.get();
				  system("cls");
			  }
			  else
			  {
				  bool check_id = false;

				  if (i_fairy_id < save->fairiesMax && i_fairy_id >= 0)
					  check_id = true;

				  if (check_id)
				  {

					  cout << "Unlock Fairy with ID: " << i_fairy_id << endl;
					  save->get_fairy(i_fairy_id)->set_isUnlock(true);
					  save->get_fairy(i_fairy_id)->save_Fairy();
					  cout << "Finish. Press a key to go back." << endl;

				  }
				  else{
					  cout << "Sorry, but this Fairy-ID doesn't exist!" << endl;
				  }

				  cin.clear();
				  getchar();
				  cin.get();
				  system("cls");
			  }

			  break;
	}

	default:
		break;

	}
}