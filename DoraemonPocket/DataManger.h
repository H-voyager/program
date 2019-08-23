#pragma once
#include "Common.h"

// SqliteManager是对Sqlite的接口进行一层简单的封装。
class SqliteManager
{
public:
	SqliteManager()
		:_db(nullptr)
	{}
	~SqliteManager()
	{
		Close();
	}
	void Open(const string& path);
	void Close();
	void ExecuteSql(const string& sql);
	void GetTable(const string& sql, int& row, int& col, char**& ppRet);

	SqliteManager(const SqliteManager&) = delete;
	SqliteManager& operator=(const SqliteManager&) = delete;
private:
	sqlite3* _db; // 数据库对象
};


///////////////////////////////////////////////////////////////
//RAII
class AutoGetTable
{
public:
	AutoGetTable(SqliteManager& sm,const string& sql, int& row, int& col, char**& ppRet)
	{
		sm.GetTable(sql, row, col, ppRet);
		_ppRet = ppRet;
	}
	~AutoGetTable()
	{
		sqlite3_free_table(_ppRet);
	}
	AutoGetTable(const AutoGetTable&) = delete;
	AutoGetTable operator=(const AutoGetTable&) = delete;
private:
	char ** _ppRet;
};


/////////////////////////////////////////////////////////
//数据管理模块

#define TB_NAME "tb_doc"
#define DB_NAME "doc.db"

//为了加锁

class DataManager
{
public:
	static DataManager* GetInstance()
	{
		static DataManager datamgr;
		datamgr.Init();

		return &datamgr;
	}
	//建表,打开数据库
	void Init();

	//查找path下的所有子文档
	void GetDocs(const string& path, std::set<string> dbset);

	//插入删除
	void InsertDoc(const string& path, const string& name);
	void DeleteDoc(const string& path, const string& name);

	//搜索
	void Search(const string& key, vector<std::pair <string,string>>& docinfos);
	//高亮
	void SplitHighlight(const string& str, const string& key, string& prefix, string& highlight, string& suffix);
private:
	DataManager()
	{

	}
	SqliteManager _dbmgr;
	std::mutex _mtx;
};
