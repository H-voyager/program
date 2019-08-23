#include "Common.h"
#include "DataManger.h"
#include "ScanManger.h"

void TestDirectoryList()
{
	vector<string> dirs;
	vector<string> files;

	DirectoryList("D:\\yang\\Documents\\bit\\class\\C++\\BIT C++¿Î¼þ-2018-V2", dirs, files);
	for (const auto& f : dirs )
	{
		cout << f << endl;
	}
	for (const auto& f : files)
	{
		cout << f << endl;
	}
}

void TestSqlite()
{
	SqliteManager sq;
	sq.Open("D:\\KuGou\\Temp");

	//sqlÓï¾ä
	//´´½¨
	string createtb_sql = "create table tb_doc(id integer primary key autoincrement, doc_path text, doc_name text)";
	sq.ExecuteSql(createtb_sql);

	//²åÈë
	string insert_sql = "insert into tb_doc(doc_path, doc_name) values( 'stl/','44')";
	sq.ExecuteSql(insert_sql);

	string query_sql = "select * from tb_doc where doc_path = 'stl/'";

	int row, col;
	char** ppRet;
	sq.GetTable(query_sql, row, col, ppRet);
	//for (int i = 0; i < row; i++)
	//{
	//	for (int j = 0; j < col; j++)
	//	{
	//		cout << ppRet[i * col + j] << " ";
	//	}
	//	cout << endl;
	//}
	sqlite3_free_table(ppRet);
	AutoGetTable agt(sq, query_sql, row, col, ppRet);
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			cout << ppRet[i * col + j] << " ";
		}
		cout << endl;
	}
}

void TestScanManager()
{
	ScanManger scanmgr;
	scanmgr.Scan("D:\\KuGou\\Temp");
}

void TestSearch()
{
	ScanManger::CreateInstance();
	DataManager datamgr;
	datamgr.Init();
	vector < std::pair<string, string>> docinfos;
	string key;
	cout << "=====================================================================" << endl;
	cout << "Please enter the key you are looking for" << endl;
	while (std::cin>>key)
	{
		docinfos.clear();
		datamgr.Search(key, docinfos);
		for  (const auto&e : docinfos)
		{
			//printf("%-30s %-30s\n", e.first.c_str(), e.second.c_str());
			
			string  prefix, highlight, suffix;
			const string& name = e.first;
			const string& path = e.second;
			datamgr.SplitHighlight(e.first, key, prefix, highlight, suffix);
			cout << prefix;
			ColourPrintf(highlight.c_str());
			cout << suffix << endl;

			//²¹Æë50¿Õ¸ñ¶ÔÆë
			for (size_t i = name.size(); i <= 40; i++)
			{
				cout << " ";
			}
			printf("%-40s\n", e.second.c_str());
		}
		cout << "=================================================================" << endl;
		cout << "Please enter the key you are looking for" << endl;
	}
}

void TestPinYin()
{
	string allspell = ChineseConvertPinYinAllSpell("Ñî±ø±ø ·û¼ÒºÀ");
	string initials = ChineseConvertPinYinInitials("Ñî±ø±ø ·û¼ÒºÀ");
	cout << allspell << endl;
	cout << initials << endl;
}

void TestHighlight()
{
	{
		//¸ßÁÁËÑË÷key
		string key = "Ñî±ø";
		string str = "·û¼ÑºÀÑî±ø";
		size_t pos = str.find(key);
		string prefix, suffix;//Ç°×ººó×º
		prefix = str.substr(0, pos);
		suffix = str.substr(pos + key.size(), string::npos);

		cout << prefix;
		ColourPrintf(key.c_str());
		cout << suffix << endl;
	}
	{
		//2.keyÊÇÆ´ÒôËù¶ÔÓ¦ºº×Ö
		string key = "yangbing";
		string str = "·û¼ÑºÀÑî±ø»á";
		string prefix, suffix;//Ç°×ººó×º
		string str_py = ChineseConvertPinYinAllSpell(str);
		string key_py = ChineseConvertPinYinInitials(key);
		size_t pos = str_py.find(key_py);
		if (pos == string::npos)
		{
			cout << "ÎÞÆ¥ÅäÆ´Òô" << endl;
		}
		else
		{
			size_t key_start = pos;
			size_t key_end = pos + key_py.size();

			
			size_t str_i = 0, py_i = 0;
			while (py_i < key_start)
			{
				if (str[str_i] < 0 || str[str_i] >127)
				{
					++str_i;
					++py_i;
				}
				else
				{
					char chinese[3] = { '\0' };
					chinese[0] = str[str_i];
					chinese[1] = str[str_i + 1];
					str_i += 2;

					string py_str = ChineseConvertPinYinAllSpell(chinese);
					py_i += py_str.size();
				}

			}

			prefix = str.substr(0, str_i);

			size_t str_j = str_i, py_j = py_i;
			while (py_j < key_end)
			{
				if (str[str_j] < 0 || str[str_j] >127)
				{
					++str_j;
					++py_j;
				}
				else
				{
					char chinese[3] = { '\0' };
					chinese[0] = str[str_j];
					chinese[1] = str[str_j + 1];
					str_j += 2;

					string py_str = ChineseConvertPinYinAllSpell(chinese);
					py_j += py_str.size();
				}
			}
			key = str.substr(str_i, str_j - str_i);
			suffix = str.substr(str_j, string::npos);

			cout << prefix;
			ColourPrintf(key.c_str());
			cout << suffix << endl;
		}

	}
	{
		//3.keyÊÇÆ´ÒôÊ××ÖÄ¸Ëù¶ÔÓ¦ºº×Ö
		string key = "yb";
		string str = "·û¼ÑºÀ Ñî±ø";
		string prefix, suffix;//Ç°×ººó×º

	}
}

int main()
{
	//TestDirectoryList();
	//TestSqlite();
	TestScanManager();
	//TestPinYin();
	//TestSearch();
	//TestHighlight();
	system("pause");
	return 0;
}