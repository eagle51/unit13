#ifndef MYMESSAGE_H
#define MYMESSAGE_H
#include <string>
#include <set>
class Message {
	friend class Folder;
	friend void swap(Message &, Message &);
public:
	explicit Message(const std::string &str = "") :contents(str) {  }
	//拷贝控制成员，用来管理指向本Message的指针
	Message(const Message &);
	Message &operator=(const Message &);
	~Message();

	//从给定Folder集合中添加/删除本Message
	void save(Folder &);
	void remove(Folder &);
	void addFldr(Folder *f) { folders.insert(f); }
	void remFldr(Folder *f) { folders.erase(f); }
private:
	std::string contents;		//实际消息文本
	std::set<Folder*> folders;	//包含本Message的Folder
	//拷贝构造函数、拷贝赋值运算符和析构函数使用的工具函数
	//将本Message添加到指向参数的Folder中
	void add_to_Folders(const Message &);
	//从folders中的每个Folder中删除本Message

	void remove_from_Floders();
};

class Folder {
public:
	Folder(const Folder &f) :msgs(f.msgs) { add_to_Messages(f); }
	~Folder() { remove_from_Msgs(); }
	Folder &operator=(const Folder &f);

	void addMsg(Message *m) { msgs.insert(m); }
	void remMsg(Message *m) { msgs.erase(m); }

	void add_to_Messages(const Folder &f);
	void remove_from_Msgs();
	
private:
	std::set<Message*> msgs;
};

void Message::save(Folder &f)
{
	folders.insert(&f);		//将给定的Folder添加到我们的Folder列表中
	f.addMsg(this);			//将本Message添加到f的Message集合中
}

void Message::remove(Folder &f)
{
	folders.erase(&f);			//将给定的Folder从我们的Folder列表中删除
	f.remMsg(this);				//将本Message从f的Message集合中删除
}

void Message::add_to_Folders(const Message &m)
{
	for (auto f : m.folders)
		f->addMsg(this);
}

Message::Message(const Message &m):contents(m.contents),folders(m.folders)
{
	add_to_Folders(m);
}

void Message::remove_from_Floders()
{
	for (auto f : folders)
		f->remMsg(this);
}

Message::~Message()
{
	remove_from_Floders();
}

Message &Message::operator =(const Message &rhs)
{
	remove_from_Floders();
	contents = rhs.contents;
	folders = rhs.folders;
	add_to_Folders(rhs);
	return *this;
}

void swap(Message &lhs, Message &rhs)
{
	using std::swap;
	for (auto f : lhs.folders)
		f->remMsg(&lhs);
	for (auto f : rhs.folders)
		f->remMsg(&rhs);
	swap(lhs.folders, rhs.folders);
	swap(lhs.contents, rhs.contents);
	for (f : lhs.folders)
		f->addMsg(&lhs);
	for (f : rhs.folders)
		f->addMsg(&rhs);
}

void Folder::add_to_Messages(const Folder &f)
{
	for (auto msg : f.msgs)
		msg->addFldr(this);
}
void Folder::remove_from_Msgs()
{
	while (!msgs.empty())
	{
		(*msgs.begin())->remove(*this);
	}
}
Folder &Folder::operator =(const Folder &f)
{
	remove_from_Msgs();
	msgs = f.msgs;
	add_to_Messages(f);
	return *this;
}
//将本Message添加到指向m的Folder中
#endif // !MYMESSAGE_H