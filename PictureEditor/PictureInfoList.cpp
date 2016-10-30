#include"PictureInfoList.h"
#include<cstring>
#include<fstream>
using namespace std;

PictureInfoList::PictureInfoList()
{
	count = 0;
	head = NULL;
	current_position = 0;
	current = NULL;
}

PictureRecord getOnePicRecorder(ifstream & myFile){

    
 	string picname;
	OthersType ot;
	char ch;
	
	
    //filename;
	picname="";
	myFile.get(ch);
	while(ch!=',') {
		picname=picname+ch;
		myFile.get(ch);
	}

	myFile>>ot.height;
	myFile.get();
	
	myFile>>ot.width;
	myFile.get();

	myFile>>ot.size;
	myFile.get();

	myFile>>ot.time;
	myFile.get();

	//detail;
	ot.detail = "";
	myFile.get(ch);
	while(ch!=',') {
		ot.detail=ot.detail+ch;
		myFile.get(ch);
	}

	//title;
	ot.titleEn = "";
	myFile.get(ch);
	while(ch!=',') {
		ot.titleEn=ot.titleEn+ch;
		myFile.get(ch);
	}
    
	//map;
	ot.map= "";
	myFile.get(ch);
	while(ch!=',') {
		ot.map=ot.map+ch;
		myFile.get(ch);
	}
	
	//location;
	ot.location= "";
	myFile.get(ch);
	while(ch!=',') {
		ot.location=ot.location+ch;
		myFile.get(ch);
	}
	//hmap;
	ot.hmap= "";
	myFile.get(ch);
	while(ch!=',') {
		ot.hmap=ot.hmap+ch;
		myFile.get(ch);
	}
	//hlocation;
	ot.hlocation= "";
	myFile.get(ch);
	while(ch!=',') {
		ot.hlocation=ot.hlocation+ch;
		myFile.get(ch);
	}
	
	getline(myFile,ot.owner);

	PictureRecord item(picname,ot);
    return item;
}

Error_code PictureInfoList::initialization()
{
	ifstream myFile;
	int number;

	//myFile.open("info.txt");
	myFile.open("info.txt");
	
	if(!myFile){
		cout<<"open file failed!"<<endl;
		return notPresent;
	}

	myFile>>number;
	if (myFile){
	    
	}
    int i=0;
	while(myFile) {
		myFile.get();
        PictureRecord  item= getOnePicRecorder(myFile);
		insert(item);

        myFile>>number;	
		//����Ļ�����ʾ��Ϣ
		cout<<'.'; i++;
	}
    cout<<i<<endl;
	//cout<<endl;
	return success;
}

Error_code PictureInfoList::insert(const PictureRecord  &data) 
{
	int len=size();
	int position; //���λ��data�����λ��
	PictureRecord  tmp;
    
	string tmpTest = data.the_key();


	//�ж��Ƿ����ظ��Ĺؼ���
	if(searchByKey(data.the_key(),tmp,position) == success) {
		cout<<data.the_key()<<" has been inserted!"<<endl<<endl;
		return duplicateKey;
	}

	return List<PictureRecord >::insert(position,data);
}

Error_code PictureInfoList::remove(PictureRecord & data)
{
	
	int position;
	PictureRecord  tmp;

	
    
	//�жϹؼ����Ƿ����
	if(searchByKey(data.the_key(),tmp,position) == notPresent) {
		cout<<"This picLibrary is not present!"<<endl<<endl;
		return notPresent;
	}
	
	return List<PictureRecord >::remove(position,data);
}

Error_code PictureInfoList::replace(const PictureRecord  &data)  
{
    int position;
	PictureRecord  tmp;
    
	//�жϹؼ����Ƿ����
	if(searchByKey(data.the_key(),tmp,position) == notPresent) {
		cout<<"This picLibrary is not present!"<<endl<<endl;
		return notPresent;
	}
    
	//����������������޸�detail��title����ͼ��λ�ã���������Ϣ������ô����
	

	return List<PictureRecord >::replace(position,data);
}

 
Error_code PictureInfoList::searchByTitle(string title, int& n /*���ҵ�������*/, const Node<PictureRecord >*   items[]/*��Ӧ�ռ��ָ���ַ*/)
{
	if(head==NULL) {
		//cout<<"Not present."<<endl;
		return notPresent;
	}

	Node<PictureRecord > * ptr=head;
	
	//�����������Ĳ���
	n=0;
	
	while(ptr!=NULL ){
		
		//�ж�ptrָ���¼��titleEn�Ƿ���title��ʼ���ܼ򵥵��жϷ���
		//�����ģ�������㷨���ԸĽ�
		int cr = strncmp(ptr->entry.the_titleEn().c_str(), title.c_str() ,title.length());

        //titleEn��title��ʼ
		if(cr == 0){
		     items[n] = ptr;
			 n++;
		}
		ptr=ptr->next;
	}

	if(n> 0){		
		return success;
	}
	else {
		//cout<<"Not present."<<endl;
		return notPresent;
	}
}

Error_code PictureInfoList::searchByLocation(string location,  int& n /*���ҵ�������*/, const Node<PictureRecord >  *   items[]/*��Ӧ��¼��ָ���ַ*/)
{
	if(head==NULL) {
		//cout<<"Not present."<<endl;
		
		return notPresent;
	}

	Node<PictureRecord > * ptr=head;
	
	
	//���� 
	n=0;
	while(ptr!=NULL ){
		
		if (ptr->entry.the_location()==location || ptr->entry.the_hlocation()==location){
             items[n] = ptr;
			 n++;
		}
		
		ptr=ptr->next;
		
	}

	if(n> 0){
		return success;
	}
	else {
		//cout<<"Not present."<<endl;
		return notPresent;
	}
}


Error_code PictureInfoList::searchByKey(string  picname, PictureRecord  & item, int& pos)  
{

	if(head==NULL) {
		//cout<<"Not present."<<endl;
		pos=0;
		return notPresent;
	}

	Node<PictureRecord > * ptr=head;
	pos = 0;
	
	//�����������Ĳ���
	while(ptr!=NULL && ptr->entry.the_key() <picname){
		ptr=ptr->next;
		pos++;
	}

	if(ptr!=NULL && ptr->entry.the_key()==picname){
		item=ptr->entry;
		return success;
	}
	else {
		//cout<<"Not present."<<endl;
		return notPresent;
	}
}

//�㼣ͳ��
Error_code PictureInfoList::searchByFootmark(LocationGraph<200> &map){
   if(head==NULL) {
		return notPresent;
	}
    
    map.ClearPicPtr();//����ͼ������ԭ�еĽڵ���ͼƬ�Ĺ�ϵ��գ�Ȼ���ٽ����µĵ�ַ��Ӧ��ϵ��

	Node<PictureRecord > * ptr=head;
    	
	//���� 
	int n=0;
	while(ptr!=NULL ){
		
		if (ptr->entry.the_map()==map.the_name()) {
             if(map.InserPicPtr(ptr->entry.the_location(),ptr) == notPresent)
				 cout<<ptr->entry.the_key()<<"foot mark fail!"<<endl; //˵��ͼƬ�ϼ�¼�ĵص��ڵ�ͼ�ڵ��в����ڣ��ʱ���
			 else
				 n++;
			       		
		}else if(ptr->entry.the_hmap()==map.the_name()){
			 if(map.InserPicPtr(ptr->entry.the_hlocation(),ptr)==notPresent) //˵��ͼƬ�ϼ�¼�ĵص��ڵ�ͼ�ڵ��в����ڣ��ʱ���
				 cout<<ptr->entry.the_key()<<"foot mark fail!"<<endl; 
			 else
				 n++;
		}
		
		ptr=ptr->next;
		
	}

	if(n>0 ) return success;
	else return notPresent;
}

//��������
void PictureInfoList::sort()
{
	Node<PictureRecord > *first_unsorted,        
		 *last_sorted,
		 *cur,             //used to traverse the sorted sublist
		 *trailing;        //one position behind current
	if(head!=NULL) {
		last_sorted=head;
		while(last_sorted->next!=NULL) {
			first_unsorted=last_sorted->next;
			if(first_unsorted->entry < head->entry) {
				last_sorted->next = first_unsorted->next;
				first_unsorted->next=head;
				head=first_unsorted;
			}
			else {
				trailing=head;
				cur=trailing->next;
				while(first_unsorted->entry > cur->entry) {
					trailing=cur;
					cur=trailing->next;
				}
				if(first_unsorted==cur) 
					last_sorted=first_unsorted;
				else {
					last_sorted->next=first_unsorted->next;
					first_unsorted->next=cur;
					trailing->next=first_unsorted;
				}
			}
		}
	}
}

//info�ļ���ͼƬ���е�ͼƬ��Ϣһһ��Ӧ��ϵ����������֤
Error_code  PictureInfoList::integrationCheck(string filename)
{

	ifstream inFile;	
	inFile.open(filename.c_str());
	if(!inFile){
	    cout<<"Open picture name files error!"<<endl;
		return notPresent;
	
	}

	//�����е�ͼƬ�ļ����ƶ��뵽picNames��List��
	List<string> picNamesList;
    PictureRecord tmpPR;
	int pos;

	string picNames;
	getline(inFile,picNames);
	//inFile>>picNames;

	while(inFile){
		picNamesList.insert(picNamesList.size(),picNames);
        getline(inFile,picNames);
	}

	//������е�ͼƬ�ļ��Ƿ���info�д��ڣ�����������������ļ���
	ofstream outFile;	
	outFile.open("pictureNoInfo.txt");
	for(int i=0; i<picNamesList.size();i++){
		picNamesList.retrieve(i,picNames);
        
		if(searchByKey(picNames,tmpPR,pos)==notPresent){
			cout<<picNames<<endl;
			outFile<<picNames<<endl;
		}
	
	}

	outFile.close();

	cout<<"***********************************"<<endl;
	//���info��¼��ͼƬ��Ϣ�Ƿ��ж�Ӧ��ͼƬ�ļ����ڣ�����������������ļ���
   
	outFile.open("infoNoPicture.txt");
    int count =0;
	for(int i=0; i<size();i++){
		retrieve(i,tmpPR);
        int j;
		for( j=0; j<picNamesList.size();j++){
		     picNamesList.retrieve(j,picNames);

			 if (tmpPR.the_key()== picNames) break;
		
		}
        //û�ж�Ӧ��ͼƬ�ļ�
		if (j>=picNamesList.size()){
			count++;
			//cout<<count<<":"<<tmpPR.the_key()<<endl;
			outFile<<i<<":"<<tmpPR.the_key()<<endl;
		}
	
	}  
	outFile.close();

	return success;

}


//������ļ�
void PictureInfoList::print()
{
	ofstream outFile;	
	outFile.open("MyInfo.txt");
	
	Node<PictureRecord > *ptr=head;
	
	int i=1;
	while(ptr) {
		outFile<<i<<'.'<<ptr->entry;
		//outFile<<i<<','<<ptr->entry.the_key()<<','<<ptr->entry.the_frequency()<<','<<ptr->entry.the_meaning()<<endl;
		cout<<i<<","<<ptr->entry;
		i++;
		ptr=ptr->next;
	}

	outFile.close();
}
Error_code PictureInfoList::searchByKey(string filename, PictureRecord &item)
{
	if (head == NULL) return notPresent;

	Node<PictureRecord > * ptr = head;
	int i = 0;
	PictureRecord a;
	for (i; i < size();i++)
	{
		retrieve(i, a);
		if (strncmp(filename.c_str(), a.the_key().c_str(), filename.size()) == 0)
		{
			break;
		}
	}
	if (i==size())
	{
		return notPresent;
	}
	item = a;
	return success;
}