#include"PictureInfoList.h"

#include <time.h>
#include <Windows.h>



void instruction()
{
	cout<<"【1】: insert"<<endl
	    <<"【2】: remove"<<endl
		<<"【3】: replace"<<endl
		<<"【4】: search (by Title)"<<endl
		<<"【5】: search (by Location)"<<endl
		<<"【6】: print"<<endl
	    <<"【7】: FootMark"<<endl;
}

void main()
{
	cout<<"Picture managment:"<<endl;
		

	PictureInfoList picLibrary;
	if(picLibrary.initialization()==success){
	    cout<<"PictureInfoList is initialized."<<endl<<"sorting..."<<endl;
	    picLibrary.sort();
	}
    
	picLibrary.print();



	string picName,titleEn, location;
	OthersType ot;
	//int position;
   
	cout<<"Do you want to do some operation? (please input \"yes\" or \"no\")"<<endl;
	string yes_or_no;
	cin>>yes_or_no;
	while(yes_or_no!="no") {
		if(yes_or_no=="yes") {
			system("cls");
			instruction();
			cout<<"So, what do you want to do ?"<<endl;
			char demand;
			cin>>demand;

			if(demand=='1') {
				//Insert
			}
			else if(demand=='2') {
				cout<<"picFilename: ";
				cin>>picName;
				
				PictureRecord  item2(picName,ot);
				if(picLibrary.remove(item2)==success)
					cout<<"deleted:"<<item2<<endl;
			}
			else if(demand=='3') {
				//Replace
				/*cout<<"title is?"<<endl;
				cin>>titleEn;
				cin.get();
				cout<<"meaning is?"<<endl;
				getline(cin,meaning);
                PictureRecord  item2(key,0.0,meaning);
				if(picLibrary.replace(item2)==success)
					cout<<"replace:"<<item2<<endl;*/
			}
			else if(demand=='4') {
				cout<<"titleEn: ";
				cin>>titleEn;
				cout<<endl;

				int n;
				const Node<PictureRecord >*   items[10];

				//searchByTitle(string title, int& n , Node<PictureRecord >*   items[]);
				
				if( picLibrary.searchByTitle(titleEn,n, items)==success ){
					for (int k=0; k<n; k++){
						PictureRecord pr = items[k]->entry;
						cout<<pr;
					}
					cout<<endl;
				}	
				else
					cout<<"not present"<<endl;
			}
			else if(demand=='5') {
			     //searchByLocation
				cout<<"location: ";
				cin>>location;
				cout<<endl;

				int n;
				const Node<PictureRecord >*   items[25];
				
				if( picLibrary.searchByLocation(location,n, items)==success ){
					for (int k=0; k<n; k++){
						PictureRecord pr = items[k]->entry;
						cout<<pr;
					}
					cout<<endl;
				}	
				else
					cout<<"not present"<<endl;
			}
			else if(demand=='6')
				picLibrary.print();
			else if(demand=='7'){
				 string mapname,mappath;
				 LocationGraph<200> ecnuMap;
				 cout<<"which map:";
				 cin>>mapname;
				 cout<<endl<<"path:";
				 cin>>mappath;
			     ecnuMap.Initialize(mapname,mappath);
				 //ecnuMap.set_name("华师大");
				 picLibrary.searchByFootmark(ecnuMap);
				 ecnuMap.Print();
                 
				 //===测试positionToNum函数，测试从界面坐标到编号的查找及显示
				 cout<<endl;
				 int index,no;
				 ecnuMap.positionToNum(940,400,index,no);//940,400,为界面上用户点击的位置

				 const List <const Node<PictureRecord >  *>* trackListPtr1=NULL;
				 VertexRecord vr;
				ecnuMap.get_trackByIndex(index,vr,trackListPtr1);
				cout<<vr.the_no()<<" "<<vr.the_x()<<"  "<<vr.the_y()<<" "<<vr.the_location()<<"  "<<trackListPtr1->size()<<" ";
				const Node<PictureRecord >* cptr;
				for(int j=0; j<trackListPtr1->size();j++){
					trackListPtr1->retrieve(j,cptr);
					 cout<<cptr->entry.the_key()<<"  ";
				}

               cout<<endl;
			   //==========================================================
			}
			else 
				cout<<"The damand number you input is invalid !"<<endl;

			cout<<"Do you want to do some operation? (please input \"yes\" or \"no\")"<<endl;
		}
		else {
			cout<<"Please input a valid operation!"<<endl
				<<"Do you want to do some operation? (please input \"yes\" or \"no\")"<<endl;
		}
		cin>>yes_or_no;
	}
	picLibrary.clear();
}