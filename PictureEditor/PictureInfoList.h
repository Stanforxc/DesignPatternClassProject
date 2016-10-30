#pragma once

#include"LocationGraph.cpp"

class PictureInfoList: public List<PictureRecord > {
public:
	PictureInfoList();
	Error_code initialization();
	Error_code insert(const PictureRecord  &data);
	Error_code remove(PictureRecord & data);
	Error_code replace(const PictureRecord  &data);    // the meaning is changed only
	Error_code searchByTitle(string title, int& n /*查找到的数量*/, const Node<PictureRecord >*   items[]/*对应空间的指针地址*/);
	Error_code searchByLocation(string location,  int& n /*查找到的数量*/, const Node<PictureRecord >  *   items[]/*对应记录的指针地址*/);
	Error_code searchByFootmark(LocationGraph<200> &map/*inout*/);
    Error_code integrationCheck(string filename);
	Error_code searchByKey(string filename, PictureRecord &item);
	void sort();
	void print();
private:
	//查找辅助函数
	Error_code searchByKey(string filename,PictureRecord  & item/*out*/, int& pos/*out*/);
};
