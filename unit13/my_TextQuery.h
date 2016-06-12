#ifndef MY_TEXTQUERY_H
#define MY_TEXTQUERY_H
#include <memory>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <fstream>
#include "my_QueryResult.h"

class QueryResult;
class TextQuery {
public:
	using line_no = std::vector<std::string>::size_type;
	TextQuery(std::ifstream &);
	QueryResult query(const std::string &) const;
	void display_map();		//调试辅助函数，打印映射表
private:
	StrBlob file;
	std::map<std::string, std::shared_ptr<std::set<line_no>>> wm;

	//规范文本：删除标点，并转换为小写
	static std::string cleanup_str(const std::string &);
};
#endif
