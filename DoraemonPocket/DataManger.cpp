#include "DataManger.h"


void SqliteManager::Open(const string& path)
{
	int ret = sqlite3_open(path.c_str(), &_db);
	if (ret != SQLITE_OK)
	{
		ERROE_LOG("sqlite3_open\n");
	}
	else
	{
		TRACE_LOG("sqlite3_open success!\n")
	}
}

void SqliteManager::Close()
{
	int ret = sqlite3_close(_db);
	if (ret != SQLITE_OK)
	{
		ERROE_LOG("sqlite3_close\n");
	}
	else
	{
		TRACE_LOG("sqlite3_close success!\n")
	}
}
void SqliteManager::ExecuteSql(const string& sql)
{
	char* errmsg;
	int ret = sqlite3_exec(_db, sql.c_str(), nullptr, nullptr, &errmsg);
	if (ret != SQLITE_OK)
	{
		ERROE_LOG("sqlite3_exec(%s) errmsg:%s\n", sql.c_str(),errmsg);
		sqlite3_free(errmsg);
	}
	else
	{
		TRACE_LOG("sqlite3_exec(%s) success!\n", sql.c_str());
	}
}
void  SqliteManager::GetTable(const string& sql, int& row, int& col, char**& ppRet)
{
	assert(_db);
	char* errmsg;
	int ret = sqlite3_get_table(_db, sql.c_str(), &ppRet, &row, &col, &errmsg);
	if (ret != SQLITE_OK)
	{
		ERROE_LOG("sqlite3_get_table(%s) errmsg:%s\n", sql.c_str(), errmsg);
		sqlite3_free(errmsg);
	}
	else
	{
		TRACE_LOG("sqlite3_get_table(%s) success!\n", sql.c_str());
	}
}

////////////////////////////////////////////////////////////////
//数据管理
//建表,打开数据库
void DataManager::Init()
{
	std::unique_lock<std::mutex> lock(_mtx);
	_dbmgr.Open(DB_NAME);
	//执行sql语句 建表
	char sql[256];
	sprintf(sql, "create table if not exists %s(id INTEGER PRIMARY KEY,path text, name text, name_pinyin text, name_initials)", TB_NAME);
	_dbmgr.ExecuteSql(sql);
}


//插入删除
void DataManager::InsertDoc(const string& path, const string& name)
{
	char sql[256];
	string pinyin = ChineseConvertPinYinAllSpell(name);
	string initials = ChineseConvertPinYinInitials(name);
	sprintf(sql,"insert into %s(path, name, name_pinyin,name_initials) values( '%s','%s','%s','%s')",\
		TB_NAME, path.c_str(), name.c_str(),pinyin.c_str(), initials.c_str());
	_dbmgr.ExecuteSql(sql);
}
void DataManager::DeleteDoc(const string& path, const string& name)
{
	char sql[256];
	string pinyin = ChineseConvertPinYinAllSpell(name);
	string initials = ChineseConvertPinYinInitials(name);
	sprintf(sql, "delete from %s where path = '%s' and name = '%s'", TB_NAME, path.c_str(), name.c_str(), pinyin.c_str(),initials.c_str());
	
	_dbmgr.ExecuteSql(sql);

	
	string path_ = path;
	path_ += '\\';
	path_ += name;
	sprintf(sql, "delete from %s where path like '%s'", TB_NAME, path_.c_str());

	std::unique_lock<std::mutex> lock(_mtx);
	_dbmgr.ExecuteSql(sql);
}


//查找path下的所有子文档
void DataManager::GetDocs(const string& path, std::set<string> dbset)
{
	char sql[256];
	sprintf(sql, "select name from %s where path = '%s'", TB_NAME, path.c_str());
	
	int row, col;
	char** ppRet;
	AutoGetTable agt(_dbmgr,sql, row, col, ppRet);
	
	for (int i = 1; i <= row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			dbset.insert(ppRet[i*col + j]);
		}
	}
}

void DataManager::Search(const string& key, vector<std::pair <string, string>>& docinfos)
{
	//char sql[256];
	//string like_key = "%";
	//like_key += key;
	//like_key += "%";
	//sprintf(sql, "select name, path from %s where name like '%s'", TB_NAME, like_key.c_str());
	//_dbmgr.ExecuteSql(sql);
	//int row, col;
	//char** ppRet;
	//AutoGetTable agt(_dbmgr, sql, row, col, ppRet);

	//for (int i = 1; i <= row; i++)
	//{
	//	docinfos.push_back(std::make_pair(ppRet[i*col + 0],ppRet[i*col + 1]));
	//}
	{
		char sql[256] = { '\0' };
		string pinyin = ChineseConvertPinYinAllSpell(key);

		sprintf(sql, "select name, path from %s where name_pinyin like '%%%s%%'", TB_NAME, pinyin.c_str());
		_dbmgr.ExecuteSql(sql);
		int row, col;
		char** ppRet;
		
		//加锁
		std::unique_lock<std::mutex> lock(_mtx);
		AutoGetTable agt(_dbmgr, sql, row, col, ppRet);
		lock.unlock();

		for (int i = 1; i <= row; i++)
		{
			docinfos.push_back(std::make_pair(ppRet[i*col + 0], ppRet[i*col + 1]));
		}
	}
	{
		char sql[256] = { '\0' };
		string initials = ChineseConvertPinYinInitials(key);

		sprintf(sql, "select name, path from %s where name_initials like '%%%s%%'", TB_NAME, initials.c_str());
		_dbmgr.ExecuteSql(sql);

		int row, col;
		char** ppRet;

		std::unique_lock<std::mutex> lock(_mtx);
		AutoGetTable agt(_dbmgr, sql, row, col, ppRet);
		lock.unlock();
		for (int i = 1; i <= row; i++)
		{
			docinfos.push_back(std::make_pair(ppRet[i*col + 0], ppRet[i*col + 1]));
		}
	}
}

void DataManager::SplitHighlight(const string& str, const string& key, string & prefix, string& highlight, string& suffix)
{
	{
		//通过汉字匹配汉字高亮 key是原串的字串
		size_t highlight_start = str.find(key);
		if (highlight_start != string::npos)
		{
			prefix = str.substr(0, highlight_start);
			highlight = key;
			suffix = str.substr(highlight_start + key.size(), string::npos);

			return ; 
		}

	}
	{
		//通过拼音匹配 key是拼音全拼
		string str_allspell = ChineseConvertPinYinAllSpell(str);
		string key_allspell = ChineseConvertPinYinAllSpell(key);


		size_t highlight_index = 0;
		//allspell全拼
		size_t allspell_index = 0;
		size_t highlight_start, highlight_len = 0;

		size_t allspell_start = str_allspell.find(key_allspell);
		size_t allspell_end = allspell_start + key_allspell.size();
		if (allspell_start != string::npos)
		{
			while (allspell_index < allspell_end)
			{
				if (allspell_index == allspell_start)
				{
					highlight_start = highlight_index;
				}
				//如果是ascll字符,则直接走
				if (str[highlight_index] >= 0 || str[highlight_index] <= 127)
				{
					++highlight_index;
					++allspell_index;
				}
				else//汉字
				{
					char chinese[3] = { '\0' };
					chinese[0] = str[highlight_index];
					chinese[1] = str[highlight_index + 1];
					string allspell_str = ChineseConvertPinYinAllSpell(key);

					//在gbk下跳两字符
					highlight_index += 2;
					//拼音跳汉字的拼音长度个
					allspell_index += allspell_str.size();
				}

			}
			highlight_len = highlight_index - highlight_start;

			prefix = str.substr(0, highlight_start);
			highlight = str.substr(highlight_start, highlight_len);
			suffix = str.substr(highlight_start + highlight_len, string::npos);
			return;
		}
	}
	{
		string Initials_str = ChineseConvertPinYinInitials(str);
		string Initials_key = ChineseConvertPinYinInitials(key);
		size_t Initials_start = Initials_str.find(Initials_key);
		if (Initials_start != string::npos)
		{
			size_t Initials_end = Initials_start + Initials_key.size();
			size_t Initials_index = 0, highlight_index = 0;
			size_t highlight = 0, highlight_len = 0;
			while (Initials_index < Initials_end)
			{
				//ascll同跳1个
				if (str[highlight_index] >= 0 || str[highlight_index] <= 127)
				{
					++highlight_index;
					++Initials_index;
				}
				else
				{
					highlight_index += 2;

				}
			}
		}
	}
	prefix = str;
}
