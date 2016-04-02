#include <iostream>
#include "../core/HWLSaveEditor.h"

using namespace std;
HWLSaveEdit::HWLSaveEditor *save;
vector<int> vi_ids;

void get_submenu(int i_menu_code);
void get_ruby_menu();

void get_chara_menu();
void change_chara_values(int i_type, int i_chara_id);

void get_materials_menu();
void get_materials_submenu(int i_type);
void change_materials_values(int i_choose, int i_material_id, int i_type, int i_size);

int main()
{
	try
	{
		save = new HWLSaveEdit::HWLSaveEditor();

		char i_choose;

		while (1)
		{
			cout << "Hyrule Warriors Legends - SaveEditor" << endl;
			cout << "____________________________________" << endl << endl;

			cout << "Menue: " << endl;
			cout << "1 - Rubies (Submenu)" << endl;
			cout << "2 - Characters (Submenu)" << endl;
			cout << "3 - Materials (Submenu)" << endl;
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
		cout << "Hyrule Warriors Legends - SaveEditor" << endl;
		cout << "____________________________________" << endl << endl;
		save = nullptr;
		cout << e.what() << endl;
	}
	
	delete save;
	cin.get();

	return 0;
}

void get_submenu(int i_menu_code)
{
	cout << "Hyrule Warriors Legends - SaveEditor" << endl;
	cout << "____________________________________" << endl << endl;

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
				  cout << "Unlock all Charas." << endl;
				  for (int i = 0; i < save->vs_players.size(); i++)
				  {
					  if (save->get_player(i)->get_name() == "???")
						  continue;

					  save->get_player(i)->set_isUnlock(true);
					  save->get_player(i)->save_Player();
				  }
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
					  cout << "Unlock Chara with ID " << i_chara_id << endl;
					  save->get_player(i_chara_id)->set_isUnlock(true);
					  save->get_player(i_chara_id)->save_Player();
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
