/*  C++ VIDEO SHOP 관리 프로그램  */

#include <iostream>
#include <conio.h>
#define MAX_VIDEO 100         //최대 비디오 100개로 정의
#define MAX_MEMBER 100        //최대 회원 100명으로 정의

using namespace std;

//날짜를 표현하는 클래스
class Date   
{
	
private:
	int year; //년
	int month; //월
	int day; //일
	
public:
	friend class Video;    //Date클래스의 private변수 사용하기위해 Video 클래스와 friend선언
	friend class Member;   //Date클래스의 private변수 사용하기위해 Member 클래스와 friend선언
	Date(){}; //생성자 함수.
	
	Date(int _year, int _month, int _day) //생성자 함수.
	{
		year=_year;
		month=_month;
		day=_day;
	}
	
	~Date(){}; //소멸자 함수.
	
	void setYear(int _year); //연도 year를 수정한다.
	void setMonth(int _month); //월 month를 수정한다.
	void setDay(int _day); //day를 수정한다.
	
	int getYear(); //연도를 리턴한다.
	int getMonth(); //월을 리턴한다.
	int getDay(); //일을 리턴한다.
};


void Date::setYear(int _year)  //연도 year를 수정한다.
{
	year=_year;
}

void Date::setMonth(int _month)  //월 month를 수정한다.
{
	month=_month;
	
}

void Date::setDay(int _day)   //day를 수정한다.
{
	day=_day;
}


int Date::getYear()     //연도를 리턴한다.
{
	return year;
}

int Date::getMonth()   //월을 리턴한다.
{
	return month;
}

int Date::getDay()    //일을 리턴한다.
{
	return day;
}

//비디오 클래스 
class Video
{
private:
	
	char vname[20]; //비디오이름
	char vID[20]; //비디오번호
	char vactor[20]; //비디오 주연배우
	Date publishDate; //비디오등록일자
	Date rendDate;  //비디오 대여일자
	Date inDate;    //비디오 반납일자
	bool rended;    //비디오 대여를 위한 bool변수
	//int membercheck; //비디오 총대여횟수를 위한 변수
	int price;       //비디오 대여가격을 위한 변수    
	
	
	
public:
	
	friend class Member;  //Member클래스와 friend 선언
	Video(){};  //생성자함수 
	
	Video(char* _vname, char* _vID, char* _vactor, Date& _publishDate)// 생성자 함수
	{
		strcpy(vname,_vname);
		strcpy(vID, _vID);
		strcpy(vactor, _vactor);
		publishDate=_publishDate;
		
	}
	
	~Video(){};  //소멸자함수 
	
	void Addvideo();         // 기능 1 (비디오등록) 
	void Searchvideo();       // 기능 2 (비디오 검색) 
	void displayvideo();      // 기능 3 (비디오 목록 출력) 
	void Rentvideo();         // 기능 4 (비디오 대여)
	void Invideo();           // 기능 5 (비디오 반납)
	void RentedvideoShow();   // 기능 6 (대여중인 비디오목록 출력)
	void blacklist();         // 기능 7 (블랙리스트 관리)
	
};


//Member 클래스 선언 
class Member 
{
	
private : 
	
	char name[20]; //회원 이름
	char personID[20]; //회원 주민등록번호
	char address[20]; //회원 주소
	char phonenumber[20]; //회원 핸드폰번호
	Date initdate; //회원 등록일자
	int rend;	   //회원의 비디오 대여횟수 
	Video index;   //대여된 비디오정보를 저장할 비디오 변수 
	
	
public:
	
	friend class Video; //video 클래스와 프렌드 선언
	
	Member(){};  //생성자함수 
	Member(char *_name, char *_personID , char * _address ,char *_phonenumber,Date& _initdate)//생성자함수
	{
		strcpy(name, _name);
		strcpy(personID ,_personID);
		strcpy(address, _address);
		strcpy(phonenumber,_phonenumber);
		initdate = _initdate;
	}
	
	~Member(){};  //소멸자함수
	
	void Addmember();  // 기능 1 (회원등록)
	void modifymember();// 기능 2 (회원정보수정)
	void displaymember();// 기능 3 (회원목록출력)
};

int Video_Num = 0;            // 현재까지 입력된 비디오 수 
int member_Num = 0;           // 현재까지 입력된 회원 수
Video vList[MAX_VIDEO];       // Video 저장을 위한 배열
Member mList[MAX_MEMBER];     // Member 저장을 위한 배열
FILE *f;                      //파일 I/O를 위한 포인터 변수 선언

//비디오추가 함수 ------> vList[MAX_VIDEO] 배열에 비디오정보저장
void Video::Addvideo()
{
	cout<<"비디오 정보를 입력하세요"<<endl;
	
	cout<<"제목: ";
	cin>>vList[Video_Num].vname;
	
	cout<<"비디오번호: ";
	cin>>vList[Video_Num].vID;
	
	cout<<"출연배우: ";
	cin>>vList[Video_Num].vactor;
    
	cout<<"등록일자: 년 월 일(예, 2005 05 05)";
	cin>>vList[Video_Num].publishDate.year>>vList[Video_Num].publishDate.month>>vList[Video_Num].publishDate.day;
	
	vList[Video_Num].rended = false;    //bool 변수인 rended 변수를 통해 이 비디오가 현재 대여가능한지
	                                    //대여 중(대여불가)인지 판단 false 면 대여가능 , true 면 대여불가
	cout<<"대여가격: " ;
	cin>>vList[Video_Num].price;
	
    Video_Num++; // 비디오 인덱스 1 증가 
}
//비디오 검색 함수 ->비디오이름을 입력받아 vList[MAX_VIDEO] 배열에 저장된 비디오이름을 출력
void Video::Searchvideo()
{
	int i;
	
	int Search_Result = 0;  // 0:  검색실패,  1: 검색성공
	char name[20];          // 검색하기를 원하는 비디오이름 저장변수
    
	cout<<"검색할 비디오 제목을 입력하세요. >> "<<endl;
	
	cin>>name;       // 검색하기를 원하는 비디오이름 입력
	
	for(i=0 ; i < Video_Num ; i++){
		if(strcmp(vList[i].vname,name)==0){
			
			cout<<" ** 검색한 비디오정보 **"<<endl;  //검색한 비디오 정보 출력
			
			cout<<"[ 등록 번호 ] ["<<i+1<<"]"<<endl;  
			cout<<"[비디오 제목] " <<vList[i].vname<<endl;
			cout<<"[비디오 번호] " <<vList[i].vID<<endl;   
			cout<<"[ 출연 배우 ] " <<vList[i].vactor<<endl;
			cout<<"[ 등록 일자 ] " <<vList[i].publishDate.year<<"년"<<vList[i].publishDate.month<<"월"<<vList[i].publishDate.day<<"일"<<endl;; 
			cout<<"[ 대여 가격 ] " <<vList[i].price<<"원"<<endl;
			if(!vList[i].rended) {  
				cout<<"대여 가능한 비디오 입니다. "<<endl;
			}
			
			else 
				cout<<"이 비디오는 현재 대여중입니다. "<<endl;
			
			cout<<"------------------------------------"<<endl;
			
			Search_Result = 1; //검색 성공
			
		}
		
		
	}
	if(Search_Result == 0)	 cout<<" 입력한 비디오가 없습니다. "<<endl; // 비디오검색 실패
}
//비디오 목록 출력함수 --->vList[MAX_VIDEO]에 있는 모든비디오의 정보출력
void Video::displayvideo()
{
	
	
	int i;
	cout<<"--------등록된 비디오 출력--------"<<endl;
	f=fopen("VIDEO SHOP.txt", "a+"); //파일을 열기 위한 함수 선언
    fprintf(f, "\n\n<비디오 등록 정보>\n\n");//파일 출력함수
	fclose(f);//파일 닫기함수
	for(i=0 ; i < Video_Num ; i++){
		cout<<"[ 등록 번호 ] ["<<i+1<<"]"<<endl;  
		cout<<"[비디오 제목] " <<vList[i].vname<<endl;
		cout<<"[비디오 번호] " <<vList[i].vID<<endl;   
		cout<<"[ 출연 배우 ] " <<vList[i].vactor<<endl;
		cout<<"[ 등록 일자 ] " <<vList[i].publishDate.year<<"년"<<vList[i].publishDate.month<<"월"<<vList[i].publishDate.day<<"일"<<endl;; 
		cout<<"[ 대여 가격 ] " <<vList[i].price<<"원"<<endl;
		if(!vList[i].rended) 
		{
			cout<<"대여 가능한 비디오 입니다. "<<endl;
		}
		
		else 
			cout<<"이 비디오는 현재 대여중입니다. "<<endl;
		
		cout<<"------------------------------------"<<endl;
	        f=fopen("VIDEO SHOP.txt", "a+");//파일을 열기 위한 함수 선언(a+는 읽기/추가를 의미)
		//파일 출력 함수
		fprintf(f, "-----------------------------------------\n");
		fprintf(f, " [등록번호]:%d번\n [비디오제목]:%s\n [비디오번호]:%s번\n [출연배우]:%s\n [등록일자]:%d년 %d월 %d일\n [대여가격]:%d원\n", i+1, vList[i].vname, vList[i].vID, vList[i].vactor, vList[i].publishDate.year, vList[i].publishDate.month, vList[i].publishDate.day, vList[i].price);
	    fprintf(f, "-----------------------------------------\n");
		fclose(f);//파일 닫기 함수
	}
}



//비디오 대여 함수 --->
void Video::Rentvideo()
{
	int i;
	int j,k;
	int Search_Result = 0;  // 0:  검색실패,  1: 검색성공
	char name[20];          // 대여하기를 원하는 비디오 제목입력받는 변수 
	
	cout<<"대여할 비디오 제목을 입력하세요. >> "<<endl;
	
	cin>>name;       // 대여하기를 원하는 비디오이름 입력
	
	for(i=0 ; i < Video_Num ; i++){  //비디오 목록에서 대여 가능한 비디오를 찾음 
		if(strcmp(vList[i].vname,name)==0){//비디오목록에서 있으면 비디오정보 출력
			
			cout<<" ** 대여될 비디오정보 **"<<endl; 
			cout<<"[ 등록 번호 ] ["<<i+1<<"]"<<endl;  
			cout<<"[비디오 제목] " <<vList[i].vname<<endl;
			cout<<"[비디오 번호] " <<vList[i].vID<<endl;   
			cout<<"[ 출연 배우 ] " <<vList[i].vactor<<endl;
			cout<<"[ 등록 일자 ] " <<vList[i].publishDate.year<<"년"<<vList[i].publishDate.month<<"월"<<vList[i].publishDate.day<<"일"<<endl;; 
			cout<<"[ 대여 가격 ] " <<vList[i].price<<"원"<<endl;
			if(!vList[i].rended) {  
				cout<<"대여 가능한 비디오 입니다. "<<endl;
			}
			
			else 
				cout<<"이 비디오는 현재 대여중입니다. "<<endl;
			cout<<"------------------------------------"<<endl;
			
			Search_Result = 1;  //검색 성공
			
			
			
			if(!vList[i].rended) {  //대여가 가능한지 검사!! (현재비디오가 대여중일수 있음!)
				
				cout<<" 이 비디오는 대여가능 합니다. "<<endl;
				cout<<" [ 대여 가격 ]  " <<vList[i].price<<"원"<<endl;//대여가격이 출력
				cout<<" 이 비디오를 대여하시겠습니까? 1.예 , 2.아니오  " <<endl;//1: 대여 ,2: 취소
				
				cin>>j;
				if(j==1) {
					
					cout<<" 대여 할 회원 이름을 입력하세요. "<<endl;  //대여할 회원이름입력
					cin>>name;  
					
					for(k=0 ; k < member_Num ; k++){  //대여할 회원을 회원목록에서 검사
						if(strcmp(mList[k].name,name)==0){ //대여할 회원이 있으면 회원정보출력
							
							cout<<" ** 대여할 회원정보 **"<<endl;
							cout<<"[ 회원 번호 ] ["<<k+1<<"]"<<endl;
							cout<<"[   이  름  ] "<<mList[k].name<<endl;  
							cout<<"[ 주민 번호 ] "<<mList[k].personID<<endl;   
							cout<<"[  집 주소  ] "<<mList[k].address<<endl;
							cout<<"[핸드폰 번호] "<<mList[i].phonenumber<<endl;
							cout<<"[ 가입 일자 ] "<<mList[k].initdate.year<<"년"<<mList[i].initdate.month<<"월"<<mList[i].initdate.day<<"일"<<endl;
							cout<<"[최근대여 비디오] "<<mList[k].index.vname<<endl;
							cout<<"[  대여   날짜  ] "<<mList[k].index.rendDate.year<<"년"<<mList[i].index.rendDate.month<<"월"<<mList[i].index.rendDate.day<<"일"<<endl;
							cout<<"[  대여   횟수  ] "<<mList[k].rend<<endl;
							cout<<"------------------------------------------"<<endl;
							
							
							Search_Result = 1;  //검색성공
							
							cout<<" 대여일자: 년 월 일(예, 2007 11 21) "<<endl;  //비디오 대여일자 입력(연체를 따지기위해!)
							cin>>vList[i].rendDate.year>>vList[i].rendDate.month>>vList[i].rendDate.day;
							cout<<"["<<vList[i].vname<<"] 비디오가 "<<mList[k].name<<"회원에게 대여되었습니다. "<<endl;
							
							vList[i].rended = true;   //비디오가 대여瑛많퓐 비디오대여 변수 true 로 변경 
							mList[k].rend++;          //회원의 대여횟수 증가 
							mList[k].index = vList[i];	//Member클래스의 video 변수인 index 에 대여된 비디오정보저장
							           
						}
					}  //회원검색에 실패하였을 경우 
					
					if(Search_Result == 0)	 cout<<" 입력한 회원이 없습니다. "<<endl; // 사원검색 실패
				}
				
				else //비디오 대여기능에서 2번 취소를 선택했을때
					
					cout<<"비디오가 대여 되지 않았습니다. "<<endl;
				
				
				
			}
			else //현재 비디오가 대여중인경우 bool rended 변수 true 일때
				cout<<" 이 비디오는 현재 대여중입니다. "<<endl;
			
		}
		
				
		
	}//비디오 검색에서 실패했을때 	
	
	if(Search_Result == 0)	 cout<<" 등록되지 않은 비디오입니다. "<<endl; // 사원검색 실패
	
	
}


//비디오 반납 함수 
void Video::Invideo()
{
	
	int i;
	int Search_Result = 0;  // 0: 검색실패,  1: 검색성공
	char name[20];          // 반납하기를 원하는 비디오이름 저장
	
	cout<<"반납할 비디오 제목을 입력하세요. >> "<<endl;
	
	cin>>name;       // 반납하기를 원하는 비디오이름 입력
	
	for(i=0 ; i < Video_Num ; i++){       
		if(strcmp(vList[i].vname,name)==0){   //비디오목록에 있으면 정보출력
			
			cout<<" ** 반납할 비디오정보 **"<<endl;
			cout<<"[ 등록 번호 ] ["<<i+1<<"]"<<endl;  
			cout<<"[비디오 제목] " <<vList[i].vname<<endl;
			cout<<"[비디오 번호] " <<vList[i].vID<<endl;   
			cout<<"[ 출연 배우 ] " <<vList[i].vactor<<endl;
			cout<<"[ 등록 일자 ] " <<vList[i].publishDate.year<<"년"<<vList[i].publishDate.month<<"월"<<vList[i].publishDate.day<<"일"<<endl;; 
			cout<<"[ 대여 가격 ] " <<vList[i].price<<"원"<<endl;
			if(!vList[i].rended) {
				cout<<"대여 가능한 비디오 입니다. "<<endl;
			}
			
			else 
				cout<<"이 비디오는 현재 대여중입니다. "<<endl;
			cout<<"------------------------------------"<<endl;
			
			Search_Result = 1;  //검색성공
			
			cout<<"반납일자: 년 월 일(예, 2007 11 21)"<<endl;  //반납일자 입력
			cin>>vList[i].inDate.year>>vList[i].inDate.month>>vList[i].inDate.day;
			
			//연체료를 검사하는 if문 (비디오대여날짜와 반납날짜를 검사해서 2박3일이 지났으면 하루당 500원씩 연체료)
			if((vList[i].rendDate.year < vList[i].inDate.year ) || (vList[i].rendDate.month < vList[i].inDate.month) || ((vList[i].rendDate.day+3) < vList[i].inDate.day))
			{	
				cout<<"연체료가 있습니다. 2박 3일 경과시 하루당 : 500원"<<endl;
				cout<<"[ 연체료 ]  "<<(vList[i].inDate.day - (vList[i].rendDate.day+3))*500<<"원"<<endl;
				vList[i].rended = false;  //비디오 대여가능 변수 rended false 로 바꿈 	
				cout<<"정상적으로 반납처리 되었습니다."<<endl;
			}
			//비디오반납일자가 2박3일경과가 안瑛뻑
			else {  
				cout<<"연체되지 않고 정상적으로 반납처리 되었습니다."<<endl;
				vList[i].rended = false;
			}
					
			
		}
		
		else //반납할 비디오가 등록되어 있지 않을때
			cout<<"등록되어 있지 않은 비디오입니다."<<endl;
	}
		
	
}

//대여중인 비디오 출력함수 
void Video::RentedvideoShow()
{
	
	
	int i;
	cout<<"--------대여된 비디오 출력--------"<<endl; 
	f=fopen("VIDEO SHOP.txt", "a+");
    fprintf(f, "\n\n<대여된 비디오 등록 정보>\n\n");
	fclose(f);
	for(i=0 ; i < Video_Num ; i++){
		
		if(vList[i].rended) {  //rended 변수를 검사해서 true인 비디오들 출력
			
			cout<<"[ 등록 번호 ] ["<<i+1<<"]"<<endl;  
			cout<<"[비디오 제목] " <<vList[i].vname<<endl;
			cout<<"[비디오 번호] " <<vList[i].vID<<endl;   
			cout<<"[ 출연 배우 ] " <<vList[i].vactor<<endl;
			cout<<"[ 등록 일자 ] " <<vList[i].publishDate.year<<"년"<<vList[i].publishDate.month<<"월"<<vList[i].publishDate.day<<"일"<<endl;; 
			cout<<"[ 대여 가격 ] " <<vList[i].price<<"원"<<endl;
			cout<<"------------------------------------"<<endl;
			
		}
		f=fopen("VIDEO SHOP.txt", "a+");
		fprintf(f, "-----------------------------------------\n");
		fprintf(f, " [등록번호]:%d번\n [비디오제목]:%s\n [비디오번호]:%s번\n [출연배우]:%s\n [등록일자]:%d년 %d월 %d일\n [대여가격]:%d원\n", i+1, vList[i].vname, vList[i].vID, vList[i].vactor, vList[i].publishDate.year, vList[i].publishDate.month, vList[i].publishDate.day, vList[i].price);
	    fprintf(f, "-----------------------------------------\n");
		fclose(f);
	}
       //cout<<"대여된 비디오가 없습니다. "<<endl;
}

//연체된 회원(블랙리스트)에 대한 정보를 출력하는 함수
void Video::blacklist()
{
	int i;
	cout<<"---------블랙리스트 정보 출력----------"<<endl;
	f=fopen("VIDEO SHOP.txt", "a+");
    fprintf(f, "\n\n<블랙리스트 정보>\n\n");
	fclose(f);
	for(i=0 ; i < Video_Num ; i++){
	if((vList[i].rendDate.year < vList[i].inDate.year ) || (vList[i].rendDate.month < vList[i].inDate.month) || ((vList[i].rendDate.day+3) < vList[i].inDate.day))
	{	
	  for(i=0 ; i < member_Num ; i++){
		cout<<"[ 회원 번호 ] ["<<i+1<<"]"<<endl;
		cout<<"[   이  름  ] "<<mList[i].name<<endl;  
		cout<<"[ 주민 번호 ] "<<mList[i].personID<<endl;   
		cout<<"[  집 주소  ] "<<mList[i].address<<endl;
		cout<<"[핸드폰 번호] "<<mList[i].phonenumber<<endl;
		cout<<"[ 가입 일자 ] "<<mList[i].initdate.year<<"년"<<mList[i].initdate.month<<"월"<<mList[i].initdate.day<<"일"<<endl;
		cout<<"[최근대여 비디오] "<<mList[i].index.vname<<endl;
		cout<<"[  대여   날짜  ] "<<mList[i].index.rendDate.year<<"년"<<mList[i].index.rendDate.month<<"월"<<mList[i].index.rendDate.day<<"일"<<endl;
		cout<<"[  대여   횟수  ] "<<mList[i].rend<<endl;
		cout<<"------------------------------------"<<endl;

		f=fopen("VIDEO SHOP.txt", "a+");
		fprintf(f, "-----------------------------------------\n");
		fprintf(f, " [회원번호]:%d번\n [이름]:%s\n [주민번호]:%s\n [집 주소]:%s\n [핸드폰번호]:%s\n [가입일자]:%d년 %d월 %d일\n [최근대여비디오]:%s\n [대여날짜]:%d년 %d월 %d일\n [대여횟수]:%d\n", i+1, mList[i].name, mList[i].personID, mList[i].address, mList[i].phonenumber, mList[i].initdate.year, mList[i].initdate.month, mList[i].initdate.day, mList[i].index.vname, mList[i].index.rendDate.year, mList[i].index.rendDate.month, mList[i].index.rendDate.day, mList[i].rend);
	    fprintf(f, "-----------------------------------------\n");
		fclose(f);
	}
   }
 }
}
//---------------------------------Video클래스 주요기능 끝 ---------------------


// 회원 등록함수 Member mList[member_Num]; 배열에 회원의 정보들을 저장
void Member::Addmember()
{
	cout<<"회원 정보를 입력하세요"<<endl;
	
	cout<<"이름: ";
	cin>>mList[member_Num].name;
	
	cout<<"주민번호: ";
	cin>>mList[member_Num].personID;
	
	cout<<"집 주소: ";
	cin>>mList[member_Num].address;
	
	cout<<"핸드폰 번호: ";
	cin>>mList[member_Num].phonenumber;
	
	cout<<"가입일자: 년 월 일(예, 2007 11 21)";
	cin>>mList[member_Num].initdate.year>>mList[member_Num].initdate.month>>mList[member_Num].initdate.day;
	
	member_Num++; // 회원 인덱스 1 증가 
	
	mList[member_Num].rend = 0; //비디오 대여횟수 0으로 초기화
}

//회원 목록 출력함수   -->    mList[member_Num]배열에 있는 회원들 정보 출력
void Member::displaymember()
{	
	
	int i;
	cout<<"--------등록된 회원정보 출력--------"<<endl;
	f=fopen("VIDEO SHOP.txt", "a+");
    fprintf(f, "\n\n<회원 정보>\n\n");
	fclose(f);
	for(i=0 ; i < member_Num ; i++){
		cout<<"[ 회원 번호 ] ["<<i+1<<"]"<<endl;
		cout<<"[   이  름  ] "<<mList[i].name<<endl;  
		cout<<"[ 주민 번호 ] "<<mList[i].personID<<endl;   
		cout<<"[  집 주소  ] "<<mList[i].address<<endl;
		cout<<"[핸드폰 번호] "<<mList[i].phonenumber<<endl;
		cout<<"[ 가입 일자 ] "<<mList[i].initdate.year<<"년"<<mList[i].initdate.month<<"월"<<mList[i].initdate.day<<"일"<<endl;
		cout<<"[최근대여 비디오] "<<mList[i].index.vname<<endl;
		cout<<"[  대여   날짜  ] "<<mList[i].index.rendDate.year<<"년"<<mList[i].index.rendDate.month<<"월"<<mList[i].index.rendDate.day<<"일"<<endl;
		cout<<"[  대여   횟수  ] "<<mList[i].rend<<endl;
		cout<<"------------------------------------"<<endl;
	   
		f=fopen("VIDEO SHOP.txt", "a+");
		fprintf(f, "-----------------------------------------\n");
		fprintf(f, " [회원번호]:%d번\n [이름]:%s\n [주민번호]:%s\n [집 주소]:%s\n [핸드폰번호]:%s\n [가입일자]:%d년 %d월 %d일\n [최근대여비디오]:%s\n [대여날짜]:%d년 %d월 %d일\n [대여횟수]:%d\n", i+1, mList[i].name, mList[i].personID, mList[i].address, mList[i].phonenumber, mList[i].initdate.year, mList[i].initdate.month, mList[i].initdate.day, mList[i].index.vname, mList[i].index.rendDate.year, mList[i].index.rendDate.month, mList[i].index.rendDate.day, mList[i].rend);
	    fprintf(f, "-----------------------------------------\n");
		fclose(f);
	}    
}


//회원 정보 수정함수 
void Member::modifymember()
{
	
	int i;
    char name[20];         // 수정할 회원이름 
	int mem_Num;           // 수정할 회원인덱스(구조체 배열 인덱스) 
	int Search_Result = 0;  // 수정전 검색결과, 0: 수정할 회원 검색 실패, 1: 수정할 회원 검색 성공
	char key;
	
	cout<<"수정할 사원이름을 입력하세요 >>"<<endl;
        cin>>name;            // 수정할 회원이름 입력
	
	for(i=0 ; i < member_Num ; i++){
		if(strcmp(mList[i].name,name)==0){  //수정할 회원 검색 성공시 
			mem_Num = i;              // 수정할 회원구조체 변수의 인덱스 값 획득
			Search_Result = 1;     //검색 성공
		}
	}
	
    // 회원검색이 성공하였을 때 
	if(Search_Result == 1){  
		cout<<"※ 다음 중 무엇을 변경하시겠습니까? "<<endl;;
		cout<<" 1. 주소 수정 "<<endl;  //주소수정
		cout<<" 2. 핸드폰 번호 수정  >>"<<endl;//핸드폰번호 수정
		
		fflush(stdin);
		key = getchar();
		
        if(key=='1'){
			cout<<"변경주소 >>"<<endl;
			fflush(stdin);
			cin>>mList[mem_Num].address;  //수정할 회원인덱스 값으로 수정값 입력받음 
			cout<<mList[mem_Num].name<<"회원의 주소가 "<<mList[mem_Num].address<<"(으)로 변경되었습니다."<<endl;
		}
		
		else if(key == '2'){
			printf("변경핸드폰 번호 >>");
			cin>>mList[mem_Num].phonenumber; //수정할 회원인덱스 값으로 수정값 입력받음 
			cout<<mList[mem_Num].name<<"회원의  핸드폰 번호가 "<<mList[mem_Num].phonenumber <<"으로 변경되었습니다."<<endl;
		}
		else{// 1,2 가아닌 다른 것 입력시 
            cout<<"잘못 입력하였습니다. "<<endl;             
		}
	}
	
	// 회원검색이 실패 하였을 때 
	else
		cout<<"입력한 회원이 없습니다. "<<endl;
}


//-----------Member 클래스 기능 끝 -------------------



//Main  함수 --->총 10개 기능의 메뉴를 고를 수있음 
int main()
{
	char Menu;
	Video a;   //비디오객체 선언
	Member b;  //멤버 객체 선언	

	
	while(1)
	{
		cout<<" +------------------------------------+"<<endl;
		cout<<" +    C++ VIDEO SHOP 관리 프로그램    +"<<endl;
		cout<<" +      Visual Studio C++ 2010        +"<<endl;     
		cout<<" +       File I/O Text Version        +"<<endl;
		cout<<" +         A911049  김 상 준          +"<<endl;
		cout<<" +------------------------------------+"<<endl;
		cout<<endl;
		cout<<" +-----------------+-------------------+---------------------+-----------------+"<<endl;
		cout<<" +   비디오 관리   +     고객 관리     +      대여 관리      +    종     료    +"<<endl; 
		cout<<" +-----------------+-------------------+---------------------+-----------------+"<<endl;
		cout<<" + 1.비디오 등록   + 4. 회원 등록      + 7. 비디오 대여      + q. 종     료    +"<<endl;
		cout<<" + 2.비디오 검색   + 5. 회원 목록 출력 + 8. 비디오 반납      +                 +"<<endl;
		cout<<" + 3.비디오 목록   + 6. 회원 정보 수정 + 9. 대여중비디오출력 +                 +"<<endl;
		cout<<" +  출력           +                   + 0. 블랙리스트 관리  +                 +"<<endl;
		cout<<" +                 +                   +                     +                 +"<<endl; 
		cout<<" +-----------------+-------------------+---------------------+-----------------+"<<endl;
		cout<<">> "; 
		
	
		fflush(stdin);
		Menu = getchar();
		fflush(stdin);     
		
		switch(Menu)
		{
		case '1':
			a.Addvideo(); //비디오 추가함수 실행
			cout<<"Enter를 입력하세요"<<endl;
			getch();		
			system("cls");
			
			break;
			
		
		case '2':
			a.Searchvideo();  //비디오 검색함수 실행
			cout<<"Enter를 입력하세요"<<endl;
			getch();		
			system("cls");
			
			break;			
					
		
		case '3':	   					
			a.displayvideo(); //비디오 목록 출력 함수 실행
			cout<<"Enter를 입력하세요"<<endl;
			getch();		
			system("cls");
			
			break;
			
		
		case '4':						
			b.Addmember();  //회원추가함수  실생
			cout<<"Enter를 입력하세요"<<endl;
			getch();					
			system("cls");
			
			break;
			
	    
		case '5':						
			b.displaymember();  //회원 목록 출력 함수 실행
			cout<<"Enter를 입력하세요"<<endl;
			getch();			
			system("cls");
			
			break;
			
		
		case '6':						
			b.modifymember();  //회원 정보 수정함수 실행
			cout<<"Enter를 입력하세요"<<endl;
			getch();			
			system("cls");
			
			break;	
		
		
		case '7':						
			a.Rentvideo();   //비디오 대여함수 실행
			cout<<"Enter를 입력하세요"<<endl;
			getch();		
			system("cls");
			
			break;			
			
		
		case '8':
			a.Invideo();  //비디오 반납함수 실행
			cout<<"Enter를 입력하세요"<<endl;
			getch();		
			system("cls");
			
			break;
			
		
		case '9':						
			a.RentedvideoShow();  //대여중인 비디오 출력함수 실행
			cout<<"Enter를 입력하세요"<<endl;
			getch();
			system("cls");
			
			break;
			
		
		case '0':
			a.blacklist();  //블랙리스트 출력함수 실행
			cout<<"Enter를 입력하세요"<<endl;
	        getch();
			system("cls");

		    break;
	    
		
		case 'q':  //프로그램종료
			cout<<"프로그램을 종료합니다. "<<endl;             
			
			return 0;
			
		
		default:  //잘못된 입력
			cout<<"잘못된 입력입니다 -> "<<Menu<<endl;
			
			break;
		
		}//end of switch
	}//end of while
}
