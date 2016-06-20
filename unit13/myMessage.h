#ifndef MYMESSAGE_H
#define MYMESSAGE_H
#include <string>
#include <set>
class Message {
	friend class Folder;
	friend void swap(Message &, Message &);
public:
	explicit Message(const std::string &str = "") :contents(str) {  }
	//�������Ƴ�Ա����������ָ��Message��ָ��
	Message(const Message &);
	Message &operator=(const Message &);
	~Message();

	//�Ӹ���Folder���������/ɾ����Message
	void save(Folder &);
	void remove(Folder &);
	void addFldr(Folder *f) { folders.insert(f); }
	void remFldr(Folder *f) { folders.erase(f); }
private:
	std::string contents;		//ʵ����Ϣ�ı�
	std::set<Folder*> folders;	//������Message��Folder
	//�������캯����������ֵ���������������ʹ�õĹ��ߺ���
	//����Message��ӵ�ָ�������Folder��
	void add_to_Folders(const Message &);
	//��folders�е�ÿ��Folder��ɾ����Message

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
	folders.insert(&f);		//��������Folder��ӵ����ǵ�Folder�б���
	f.addMsg(this);			//����Message��ӵ�f��Message������
}

void Message::remove(Folder &f)
{
	folders.erase(&f);			//��������Folder�����ǵ�Folder�б���ɾ��
	f.remMsg(this);				//����Message��f��Message������ɾ��
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
//����Message��ӵ�ָ��m��Folder��
#endif // !MYMESSAGE_H