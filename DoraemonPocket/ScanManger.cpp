#include "ScanManger.h"

void ScanManger::Scan(const string& path)
{
	//比对文件系统和数据库
	//文件系统数据
	vector<string> localdirs;
	vector<string> localfiles;
	DirectoryList(path, localdirs, localfiles);

	//dbset与localset对比
	std::set<string> localset;
	localset.insert(localfiles.begin(), localfiles.end());
	localset.insert(localdirs.begin(), localdirs.end());

	//datamanger
	std::set<string> dbset;
	DataManager::GetInstance()->GetDocs(path, dbset);

	auto localit = localset.begin();
	auto dbit = dbset.cbegin();
	while (localit != localset.end() && dbit != dbset.end())
	{
		//数据库中没有,本地文件中有,新增数据
		if (*localit < *dbit)
		{
			DataManager::GetInstance()->InsertDoc(path, *localit);
			++localit;
		}
		else if (*localit < *dbit)//本地没有,数据库中有,删除数据
		{
			DataManager::GetInstance()->DeleteDoc(path, *localit);
			++dbit;
		}
		else//无改变
		{
			++dbit;
			++localit;
		}
	}

	while (localit != localset.end())
	{
		//新增数据
		DataManager::GetInstance()->InsertDoc(path, *localit);
		++localit;
	}
	while (dbit != dbset.end())
	{
		//删除数据
		DataManager::GetInstance()->DeleteDoc(path, *localit);
		++dbit;
	}

	//递归比对子目录
	for (const auto& subdirs : localdirs)
	{
		string subpath = path;
		subpath += '\\';
		subpath += subdirs;

		Scan(subdirs);
	}
}