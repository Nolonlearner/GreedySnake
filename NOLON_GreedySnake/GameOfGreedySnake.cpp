#include <iostream>
#include <conio.h>
#include <vector>
#include <string>
#include <fstream>
#include <queue>//�������ȶ���
#include <ctime>
#include <chrono>
#include <graphics.h>  //easyX�������ͷ�ļ�
#include <mmsystem.h> // ����mmsystem.hͷ�ļ�
#pragma comment(lib,"WINMM.LIB")

/*-------------------------��Ϸ���ء����桢֡�ʵȻ���Ҫ��-------------------------*/


#define UNIT            15                                //һ�������Ӧ�����ش�С
#define HIGH            35                               //��Ϸ����ĸ߶�
#define WIDE            45                               //��Ϸ����Ŀ��
#define BasicGame       1
#define SecondGame      2
#define AdvanceGame     3
#define Rating          4
#define SetName         5
#define Withdraw        6
/*--------------------------------------------------------------------------------*/


/*--------------------------��Ϸģʽ��ʼ������ز���------------------------------*/
#define SNAKEBASICBODY   1                               //�ߵĳ�ʼ����
#define FOODNUM          5                               //ʳ�����������ֵ
#define FOODTYPE         5                               //ʳ�����͵����ֵ
#define LifeMAXNUM       5                               //��������

/*--------------------------------------------------------------------------------*/


/*--------------------------��Ϣչʾ�Ĵ�����ز���--------------------------------*/

#define WINDOW_Show_Score_SIZE        20                               //��ʾ�����Ĵ���
#define CHAR_INFOR_SIZE               500                              //����Ĵ�ϸ
#define CHAR_INFOR_HIGH               20                               //����ĸ߶�//���Ϊ�����������
#define CHAR_INFOR_COLOR              RGB(134,144,138)                     //�������ɫ
#define BASIK_COLOR                   RGB(234,220,214)                        //����Ļ������ɫ
#define SHOWBASIK_COLOR               RGB(237,241,187)                       //������ϢĻ������ɫ
#define SHOWBASIKFRAME_COLOR          RGB(255,200,222)                        //�����߿�Ļ������ɫ
#define PIC                           30

/*--------------------------------------------------------------------------------*/


/*-------------------------------�ߡ�ʳ�ǽ����ɫ---------------------------------------*/
#define SnakeBody_COLOR       RGB(239,130,160)                        //�������ɫ
#define SnakeHead_COLOR       RGB(167,83,90)                          //��ͷ����ɫ
#define WALL_COLOR            RGB(128,109,158)                        //ǽ����ɫ
#define BLUEPOSION_COLOR      RGB(81,196,211)                         //��ɫ��ҩ����ɫ
#define PURPLEPOSION_COLOR    RGB(65,28,53)                           //��ɫ��ҩ����ɫ
#define APPLE_COLOR           RGB(237,90,101)                         //ƻ������ɫ
#define BANANA_COLOR          RGB(249,180,0)                          //�㽶����ɫ
#define TREASURECHEST_COLOR   RGB(110,139,116)                        //�������ɫ
//#define BASIK_COLOR           RGB(251,242,227)                        //����Ļ������ɫ


/*--------------------------------------------------------------------------------*/

/*-------------------------------�˵�����-----------------------------------------*/

#define  MenuColor          RGB(95,71,154)//������//
#define  MenuBKColor        RGB(229,223,213)//�����




/*--------------------------------------------------------------------------------*/

/*-------------------------------���а����-----------------------------------------*/
#define scoreRating             1
#define lengthRating            2
#define MaxRatingNumShow        3
#define RatingShowBeginX        70
#define RatingShowBeginY        200
#define RatingShowBeginHigh     50
#define CharRtingHeight         30
#define CHAR_Rating_SIZE         300
#define CHAR_Rating_COLOR  RGB(227,111,113)//���ĺ�
#define CHAR_Rating_BKCOLOR  RGB(255,196,187)//�ۺ�
#define CHAR_HoverCOLOR  RGB(250,199,183)//ʮ���
#define CHAR_HoverBKCOLOR  RGB(93,79,87)//��īɫ

#define CHAR_Rule_SIZE  300
#define CHAR_Rule_High  20
#define CHAR_Rule_BeginX  20
#define CHAR_Rule_BeginY  50
#define CHAR_Rule_COLOR  RGB(164,171,214)//ĺɽ��

/*--------------------------------------------------------------------------------*/


const char Vision1RatingofScoreTxt[] = "Vision1Scoreleaderboard.txt";
const char Vision1RatingofLengthTxt[] = "Vision1Lengthleaderboard.txt";

const char Vision2RatingofScoreTxt[] = "Vision2Scoreleaderboard.txt";
const char Vision2RatingofLengthTxt[] = "Vision2Lengthleaderboard.txt";

const char Vision3RatingofScoreTxt[] = "Vision3Scoreleaderboard.txt";
const char Vision3RatingofLengthTxt[] = "Vision3Lengthleaderboard.txt";

using namespace std;
using namespace chrono;



const double CANSHU = 4500;
double OriFPS = 30.0; // ��ʼ֡��
const double SPEEDUP_INTERVAL = 15; // ���ټ�����룩
const double SPEEDUP_FACTOR = 1.1; // ��������
const double SPEEDDOWN_FACTOR = 0.9; // ��������
double frameDelay = CANSHU / OriFPS; // ��ʼÿ֡���ӳ�ʱ�䣨���룩//������ʱ��仯���仯
steady_clock::time_point prevTime = steady_clock::now();
steady_clock::time_point currTime = steady_clock::now();
double gameTime = 0.0; // ������Ϸʱ������λ���룩   //����ʱ��
double SingTime = 0.0;
double deltaTime = 0.0;//ʱ����

const wchar_t* audioFile = L"TEST.mp3"; // ��Ƶ�ļ�·��

// ������Ϸ������

//������
class Snake;
class Wall;
class Food;
enum class FoodType;
class ShowInformation;
class Menu;
class GameGreedySnake;
class LeaderboardEntry;
struct ScoreComparator;
struct LengthComparator;


//���а�
class LeaderboardEntry {
private:
    wstring playerName;
    int score;
    int length;

public:
    LeaderboardEntry() : score(0), length(0)
    {
        playerName = ' ';
    }

    LeaderboardEntry(const wstring& name, int score, int length)
    {
        playerName = name;
        this->score = score;
        this->length = length;
    }

    // Getters
    wstring getPlayerName() const {
        return playerName;
    }

    int getScore() const {
        return score;
    }

    int getLength() const {
        return length;
    }
    // Setters
    void setPlayerName(wstring name) {
        playerName = name;
    }

    void setScore(int S) {
        score = S;
    }

    void setLength(int L) {
        length = L;
    }
};
struct ScoreComparator {
    bool operator()(const LeaderboardEntry& entry1, const LeaderboardEntry& entry2) {
        return entry1.getScore() > entry2.getScore(); //�Ӵ�С����
    }
};
struct LengthComparator {
    bool operator()(const LeaderboardEntry& entry1, const LeaderboardEntry& entry2) {
        return entry1.getLength() > entry2.getLength(); //�Ӵ�С����
    }
};

//���а�Ҫʵʱ����������Ϊ��Ϊȫ�ֱ���
//�汾1�����а�
vector<LeaderboardEntry> Vision1ScoreEntries;
vector<LeaderboardEntry> Vision1LengthEntries;
//�汾2�����а�
vector<LeaderboardEntry> Vision2ScoreEntries;
vector<LeaderboardEntry> Vision2LengthEntries;
//�汾3�����а�
vector<LeaderboardEntry> Vision3ScoreEntries;
vector<LeaderboardEntry> Vision3LengthEntries;

//�˵���
class Menu {
private:
    bool flag;
    bool LifeFlag;
    int selectedOption;
    wstring userName;
    bool isinputtingUsername;
    wstring inputtedUsername;  // ������û���
    bool ischeckRating;
    int  RatingClickOption;


public:
    Menu() {
        LifeFlag = true;
        flag = true;
        isinputtingUsername = false;
        ischeckRating = false;
        selectedOption = 0;
        inputtedUsername = ' ';
        RatingClickOption = -1;
    }
    void resetMenu()
    {
        LifeFlag = true;
        flag = true;
        isinputtingUsername = false;
        ischeckRating = false;
        selectedOption = 0;
        inputtedUsername = ' ';
        RatingClickOption = -1;
    }
    void displayMenu();
    void handleMouseClick(int x, int y);
    void handleKeyPress(char key);
    void setUserName(const wstring& name);
    void displayMenuDecision();
    void handleMouseHover(int x, int y);
    void Creat_InputYourName_Windows();
    int getSelectedOption() { return selectedOption; }
    wstring getUserName() { return userName; }
    bool getLifeFlag() { return LifeFlag; }
    bool getflag() { return flag; }
    void InputNameInWindows(char key);
    void Delete_InputYourName_Windows();
    void ShowRankingOptions();//�������а񴰿�
    void handleRankingMouseClick(int x, int y);
    void handleRankingMouseHover(int x, int y);
    void  displayRatingDecision();
    void ShowRatingList();
    void showRatinglistBasic();
    void showRatinglistSecond();
    void showRatinglistAdvance();
    void Delete_Rating_Windows();
    void drawBackButton();
    void CheckClickReturn();
    void handleMouseClickBackButton(int x, int y);
    void handleRankingMouseBackButtonHover(int x, int y);
    void handleBackButton();
    void drawRule();
};
void Menu::drawRule()
{
    LOGFONT f;
    gettextstyle(&f);						// ��ȡ��ǰ��������
    f.lfHeight = CHAR_Rule_High;						// ��������߶�
    f.lfItalic = true;
    _tcscpy_s(f.lfFaceName, _T("����"));		// ��������
    f.lfQuality = ANTIALIASED_QUALITY;		// �������Ч��Ϊ�����  
    f.lfWeight = CHAR_Rule_SIZE;//�ַ���ϸ
    settextstyle(&f);
    settextcolor(CHAR_Rule_COLOR);
    wstring rule1 = L"���Ű�Ĺ���Ҫ����ҿ��Ʒ����������С�ߵ�ǰ��������ʹ�߳Ե���������λ���ϵ�ʳ�λ�����������Ϊ 1-5 �������ÿ�γɹ��Ե�ʳ���С���峤������һ�㣬�÷����ӡ�ʳ��Թ����ٴ������������С��ײ���߽������ͷ��������ײʱ���߽��ҵ�����Ϸ������";
    int row = 0;
    size_t lineLength = 15;  // ÿ�е��ַ���

    size_t remainingChars1 = rule1.size();  // ʣ����ַ���

    for (size_t i = 0; remainingChars1 > 0; i += lineLength) {
        TCHAR Ruletext[30];
        wstring line = rule1.substr(i, min(lineLength, remainingChars1));
        _stprintf_s(Ruletext, _T("%s"), line.c_str());
        outtextxy(CHAR_Rule_BeginX, CHAR_Rule_BeginY + row * CHAR_Rule_High - 40, Ruletext);
        row++;
        remainingChars1 -= line.length();
    }

    row++;
    wstring rule2 = L"���װ�Ĺ����߹ҵ��󣬴�ʱ��ʬ��ı���ʾ��ɫ��ɱ߽磬����������µ�ʳ����ߣ���Ϸ������ֱ��ʣ��ռ䲻���������µ��ߺ�ʳ��Ϊֹ��";

    size_t remainingChars2 = rule2.size();  // ʣ����ַ���

    for (size_t i = 0; remainingChars2 > 0; i += lineLength) {
        TCHAR Ruletext[30];
        wstring line = rule2.substr(i, min(lineLength, remainingChars2));
        _stprintf_s(Ruletext, _T("%s"), line.c_str());
        outtextxy(CHAR_Rule_BeginX, CHAR_Rule_BeginY + row * CHAR_Rule_High - 40, Ruletext);
        row++;

        remainingChars2 -= line.length();
    }

    row++;
    wstring rule3 = L"�߼���Ĺ���Ϊ���߹ҵ��󣬴�ʱ��ʬ��ı���ʾ��ɫ���ʳ�����������µ�ʳ����ߣ���Ϸ������ֱ��ײǽ����>5����ʣ��ռ䲻���������µ��ߺ�ʳ��Ϊֹ��";

    size_t remainingChars3 = rule3.size();  // ʣ����ַ���

    for (size_t i = 0; remainingChars3 > 0; i += lineLength) {
        TCHAR Ruletext[30];
        wstring line = rule3.substr(i, min(lineLength, remainingChars3));
        _stprintf_s(Ruletext, _T("%s"), line.c_str());
        outtextxy(CHAR_Rule_BeginX, CHAR_Rule_BeginY + row * CHAR_Rule_High - 40, Ruletext);
        row++;

        remainingChars3 -= line.length();
    }
    row++;
    wstring rule4 = L"�������Ϸϸ����鿴�ĵ������README.TXT����ӭ��ҽ���������";

    size_t remainingChars4 = rule4.size();  // ʣ����ַ���

    for (size_t i = 0; remainingChars4 > 0; i += lineLength) {
        TCHAR Ruletext[30];
        wstring line = rule4.substr(i, min(lineLength, remainingChars4));
        _stprintf_s(Ruletext, _T("%s"), line.c_str());
        outtextxy(CHAR_Rule_BeginX, CHAR_Rule_BeginY + row * CHAR_Rule_High - 40, Ruletext);
        row++;

        remainingChars4 -= line.length();
    }
    cout << "��ӡ����" << endl;
}
void Menu::displayRatingDecision()
{
    settextstyle(40, 0, _T("����"));
    settextcolor(MenuColor);
    setbkcolor(MenuBKColor);

    outtextxy(RatingShowBeginX + 30, RatingShowBeginY, _T("���Ű�"));
    outtextxy(RatingShowBeginX + 30, RatingShowBeginY + RatingShowBeginHigh, _T("���װ�"));
    outtextxy(RatingShowBeginX + 30, RatingShowBeginY + RatingShowBeginHigh * 2, _T("�߼���"));
}
void Menu::displayMenuDecision()
{
    // ���Ʋ˵�ѡ��
    settextstyle(40, 0, _T("����"));

    settextcolor(MenuColor);
    setbkcolor(MenuBKColor);

    outtextxy(350, 50, _T("Nolon Greedy Snake"));

    outtextxy(400, 100, _T("By Nolon"));

    TCHAR name[100];
    _stprintf_s(name, _T("[�û���:%s]"), userName.c_str());
    outtextxy(350, 150, name);


    outtextxy(350, 200, _T("������"));
    outtextxy(350, 250, _T("���װ�"));
    outtextxy(350, 300, _T("�߼���"));
    outtextxy(350, 350, _T("���а�"));
    outtextxy(350, 400, _T("�����û���"));
    outtextxy(350, 450, _T("�˳���Ϸ"));
    // ̰����ͼƬ��·��

    // ����̰����ͼƬ
    IMAGE img1;
    IMAGE img2;
    loadimage(&img1, _T("snake.png"));
    loadimage(&img2, _T("LogoSnake.jpg"));

    // �ڻ�������ʾ̰����ͼƬ
    putimage(555, 200, &img1);
    putimage(585, 100, &img2);
}
void Menu::displayMenu() {
    initgraph(800, 600, SHOWCONSOLE);  // ��ʼ������
    settextstyle(40, 0, _T("����"));
    settextcolor(MenuColor);
    setbkcolor(MenuBKColor);

    cleardevice();  // ��մ���

    // ���Ʋ˵�ѡ��
    displayMenuDecision();
    drawRule();

    while (flag) {
        //TCHAR s[20];         // EasyX����������Ҫ���ַ�����������
        if (MouseHit()) {
            MOUSEMSG m = GetMouseMsg();  // ��ȡ�����Ϣ
            switch (m.uMsg) {
            case WM_LBUTTONDOWN:
                // ������£��������λ���ж�ѡ��Ĳ˵���
                if (ischeckRating)
                    handleRankingMouseClick(m.x, m.y);//���������а�����
                else
                    handleMouseClick(m.x, m.y);
                break;
            case WM_LBUTTONDBLCLK://WM_RBUTTONDOWN�Ҽ�
                // ���˫���˳�ѭ��
                flag = false;
                break;
            case WM_MOUSEMOVE:
                // ����ƶ����ڴ������Ͻ���ʾ��ǰ����
                //setfillcolor(BLACK);                  // ��ɫ���θ����ϴ������¼
                //solidrectangle(0, 0, 75, 20);
                //_stprintf_s(s, _T("[%d,%d]"), m.x, m.y); // ��ʽ���ַ���
                //outtextxy(0, 0, s);

                // ���������ͣЧ��
                if (ischeckRating)
                    handleRankingMouseHover(m.x, m.y);
                else if (isinputtingUsername)
                    ;
                else {
                    handleMouseHover(m.x, m.y);
                }
                break;
            default:
                break;
            }
        }
        if (_kbhit()) {
            char key = _getch();
            if (isinputtingUsername)//��ʱ���������û���
            {
                InputNameInWindows(key);//�����û���
            }
            else {//��ʱ�ж��ǲ����˳�
                handleKeyPress(key);
            }
        }
    }

    closegraph();
}
void Menu::handleMouseClick(int x, int y) {


    if (y >= 200 && y < 250 && x >= 350 && x < 450) {
        selectedOption = BasicGame;
        flag = false;
    }
    else if (y >= 250 && y < 300 && x >= 350 && x < 450) {
        selectedOption = SecondGame;
        flag = false;
    }
    else if (y >= 300 && y < 350 && x >= 350 && x < 450) {
        selectedOption = AdvanceGame;
        flag = false;
    }
    else if (y >= 350 && y < 400 && x >= 350 && x < 450) {
        selectedOption = Rating;
        ischeckRating = true;  // ����鿴���а��״̬
        flag = true;
    }
    else if (y >= 400 && y < 450 && x >= 350 && x < 550) {
        // ��������򣬻�ȡ�û���
        selectedOption = SetName;
        isinputtingUsername = true;  // ���������û���״̬
        flag = true;
        Creat_InputYourName_Windows();//�������봰��
    }
    else if (y >= 450 && y < 500 && x >= 350 && x < 450) {
        selectedOption = Withdraw;
        flag = false;
        LifeFlag = false;
    }
    else {
        flag = true;
    }

}
void Menu::handleRankingMouseClick(int x, int y) {
    if (y >= 200 && y < 250 && x >= 100 && x <= 200) {
        RatingClickOption = BasicGame;
    }
    else if (y >= 250 && y < 300 && x >= 100 && x <= 200) {
        RatingClickOption = SecondGame;
    }
    else if (y >= 300 && y < 350 && x >= 100 && x <= 200) {
        RatingClickOption = AdvanceGame;
    }
    else
        RatingClickOption = -1;
    cout << "���" << RatingClickOption << endl;
    if (RatingClickOption >= BasicGame && RatingClickOption <= AdvanceGame)
        ShowRatingList();
}
void Menu::handleMouseHover(int x, int y) {

    // ���Ʋ˵�ѡ��
    displayMenuDecision();

    // �����ͣЧ��
    settextstyle(40, 0, _T("����"));
    settextcolor(CHAR_HoverCOLOR);
    setbkcolor(CHAR_HoverBKCOLOR);

    if (y >= 200 && y < 250 && x >= 350 && x < 450) {
        outtextxy(350, 200, _T("������"));
    }
    else if (y >= 250 && y < 300 && x >= 350 && x < 450) {
        outtextxy(350, 250, _T("���װ�"));
    }
    else if (y >= 300 && y < 350 && x >= 350 && x < 450) {
        outtextxy(350, 300, _T("�߼���"));
    }
    else if (y >= 350 && y < 400 && x >= 350 && x < 450) {
        outtextxy(350, 350, _T("���а�"));
    }
    else if (y >= 400 && y < 450 && x >= 350 && x < 550) {
        outtextxy(350, 400, _T("�����û���"));
    }
    else if (y >= 450 && y < 500 && x >= 350 && x < 450) {
        outtextxy(350, 450, _T("�˳���Ϸ"));
    }
}
void Menu::handleRankingMouseHover(int x, int y) {
    // �����ͣЧ��
    displayRatingDecision();
    settextstyle(40, 0, _T("����"));
    settextcolor(CHAR_HoverCOLOR);
    setbkcolor(CHAR_HoverBKCOLOR);
    if (y >= 200 && y < 250 && x >= 100 && x < 200) {
        outtextxy(100, 200, _T("���Ű�"));
    }
    else if (y >= 250 && y < 300 && x >= 100 && x < 200) {
        outtextxy(100, 250, _T("���װ�"));
    }
    else if (y >= 300 && y < 350 && x >= 100 && x < 200) {
        outtextxy(100, 300, _T("�߼���"));
    }
}
void Menu::handleKeyPress(char key) {
    if (key == 27) {
        selectedOption = Withdraw;  // ESC����Ӧ�˳���Ϸ
        flag = false;
        LifeFlag = false;
    }
}
void Menu::setUserName(const wstring& name) {
    userName = name;
}
void Menu::Creat_InputYourName_Windows()
{
    // �û������"�����û���"ѡ��֮��
    // 
    // ��������û�����ѡ���
    setfillcolor(MenuBKColor);
    solidrectangle(350, 400, 800, 450);

    // ��ʾ�����
    settextstyle(40, 0, _T("����"));
    settextcolor(WHITE);
    setbkcolor(LIGHTGRAY);
    outtextxy(350, 400, _T("�������û���: "));
    //Ȼ��ʼ�����û���
}
void Menu::ShowRankingOptions()
{
    settextstyle(40, 0, _T("����"));
    settextcolor(WHITE);
    setbkcolor(BLACK);

    outtextxy(RatingShowBeginX, RatingShowBeginY, _T("�汾һ"));
    outtextxy(RatingShowBeginX, RatingShowBeginY + 1 * RatingShowBeginHigh, _T("�汾��"));
    outtextxy(RatingShowBeginX, RatingShowBeginY + 2 * RatingShowBeginHigh, _T("�汾��"));
}
void Menu::InputNameInWindows(char key)
{
    if (key == '\r')
    {
        // ���������ǻس���������������û���
        // ��������
        Delete_InputYourName_Windows();
    }
    else if (key == '\b')
    {
        // �˸����ɾ�����һ���ַ�
        if (!inputtedUsername.empty()) {
            inputtedUsername.pop_back();

            // ��������
            setfillcolor(MenuBKColor);
            solidrectangle(350, 400, 800, 450);

            // ��ʾ������û���,����
            settextstyle(40, 0, _T("����"));
            settextcolor(WHITE);
            setbkcolor(LIGHTGRAY);
            TCHAR name[100];
            _stprintf_s(name, _T("[�û���:%s]"), inputtedUsername.c_str());
            outtextxy(350, 400, name);
        }
    }
    else
    {//����ַ�
        // �����ַ���ӵ��û����ַ���ĩβ
        inputtedUsername.push_back(key);

        // ��ʾ������û���
        settextstyle(40, 0, _T("����"));
        settextcolor(WHITE);
        setbkcolor(LIGHTGRAY);
        TCHAR name[100];
        _stprintf_s(name, _T("[�û���:%s]"), inputtedUsername.c_str());
        outtextxy(350, 400, name);
    }
}
void Menu::Delete_InputYourName_Windows()
{
    // ���������û���״̬
    isinputtingUsername = false;
    userName = inputtedUsername;
    // ��������
    setfillcolor(MenuBKColor);;
    solidrectangle(350, 400, 800, 450);
    displayMenuDecision();//���½���
    drawRule();

}
void Menu::showRatinglistBasic()
{
    // ������а��ѡ���
    setfillcolor(CHAR_Rating_BKCOLOR);
    solidrectangle(RatingShowBeginX, RatingShowBeginY - 2 * RatingShowBeginHigh, RatingShowBeginX + 5 * RatingShowBeginHigh, RatingShowBeginY + 6 * RatingShowBeginHigh);

    LOGFONT f;
    gettextstyle(&f);						// ��ȡ��ǰ��������
    f.lfHeight = CharRtingHeight;						// ��������߶�
    f.lfItalic = false;
    _tcscpy_s(f.lfFaceName, _T("Old English"));		// ��������
    f.lfQuality = ANTIALIASED_QUALITY;		// �������Ч��Ϊ�����  
    f.lfWeight = CHAR_Rating_SIZE;//�ַ���ϸ
    settextstyle(&f);
    settextcolor(CHAR_Rating_COLOR);

    setbkcolor(CHAR_Rating_BKCOLOR);

    outtextxy(RatingShowBeginX, RatingShowBeginY - RatingShowBeginHigh, _T("Rating of Score"));
    for (size_t i = 0; (i < MaxRatingNumShow) && (i < Vision1ScoreEntries.size()); i++)
    {
        cout << "���" << endl;
        TCHAR RatingText[100];
        _stprintf_s(RatingText, _T("%d. %s %d"), (i + 1), Vision1ScoreEntries[i].getPlayerName().c_str(), Vision1ScoreEntries[i].getScore());
        outtextxy(RatingShowBeginX, RatingShowBeginY - RatingShowBeginHigh + CharRtingHeight * (i + 1), RatingText);
    }

    outtextxy(RatingShowBeginX, RatingShowBeginY + CharRtingHeight * (MaxRatingNumShow + 1), _T("Rating of Length"));
    for (size_t i = 0; (i < MaxRatingNumShow) && (i < Vision1LengthEntries.size()); i++)
    {
        cout << "���" << endl;
        TCHAR RatingText[100];
        _stprintf_s(RatingText, _T("%d. %s %d"), (i + 1), Vision1LengthEntries[i].getPlayerName().c_str(), Vision1LengthEntries[i].getLength());
        outtextxy(RatingShowBeginX, RatingShowBeginY + CharRtingHeight * (MaxRatingNumShow + 1) + CharRtingHeight * (i + 1), RatingText);
    }
}
void Menu::showRatinglistAdvance()
{
    // ������а��ѡ���
    setfillcolor(CHAR_Rating_BKCOLOR);
    solidrectangle(RatingShowBeginX, RatingShowBeginY - 2 * RatingShowBeginHigh, RatingShowBeginX + 5 * RatingShowBeginHigh, RatingShowBeginY + 6 * RatingShowBeginHigh);

    LOGFONT f;
    gettextstyle(&f);						// ��ȡ��ǰ��������
    f.lfHeight = CharRtingHeight;						// ��������߶�
    f.lfItalic = false;
    _tcscpy_s(f.lfFaceName, _T("Old English"));		// ��������
    f.lfQuality = ANTIALIASED_QUALITY;		// �������Ч��Ϊ�����  
    f.lfWeight = CHAR_Rating_SIZE;//�ַ���ϸ
    settextstyle(&f);
    settextcolor(CHAR_Rating_COLOR);

    setbkcolor(CHAR_Rating_BKCOLOR);

    outtextxy(RatingShowBeginX, RatingShowBeginY - RatingShowBeginHigh, _T("Rating of Score"));
    for (size_t i = 0; (i < MaxRatingNumShow) && (i < Vision3ScoreEntries.size()); i++)
    {
        cout << "���" << endl;
        TCHAR RatingText[100];
        _stprintf_s(RatingText, _T("%d. %s %d"), (i + 1), Vision3ScoreEntries[i].getPlayerName().c_str(), Vision3ScoreEntries[i].getScore());
        outtextxy(RatingShowBeginX, RatingShowBeginY - RatingShowBeginHigh + CharRtingHeight * (i + 1), RatingText);
    }

    outtextxy(RatingShowBeginX, RatingShowBeginY + CharRtingHeight * (MaxRatingNumShow + 1), _T("Rating of Length"));
    for (size_t i = 0; (i < MaxRatingNumShow) && (i < Vision3LengthEntries.size()); i++)
    {
        cout << "���" << endl;
        TCHAR RatingText[100];
        _stprintf_s(RatingText, _T("%d. %s %d"), (i + 1), Vision3LengthEntries[i].getPlayerName().c_str(), Vision3LengthEntries[i].getLength());
        outtextxy(RatingShowBeginX, RatingShowBeginY + CharRtingHeight * (MaxRatingNumShow + 1) + CharRtingHeight * (i + 1), RatingText);
    }
}
void Menu::showRatinglistSecond()
{
    // ������а��ѡ���
    setfillcolor(CHAR_Rating_BKCOLOR);
    solidrectangle(RatingShowBeginX, RatingShowBeginY - 2 * RatingShowBeginHigh, RatingShowBeginX + 5 * RatingShowBeginHigh, RatingShowBeginY + 6 * RatingShowBeginHigh);

    LOGFONT f;
    gettextstyle(&f);						// ��ȡ��ǰ��������
    f.lfHeight = CharRtingHeight;						// ��������߶�
    f.lfItalic = false;
    _tcscpy_s(f.lfFaceName, _T("Old English"));		// ��������
    f.lfQuality = ANTIALIASED_QUALITY;		// �������Ч��Ϊ�����  
    f.lfWeight = CHAR_Rating_SIZE;//�ַ���ϸ
    settextstyle(&f);
    settextcolor(CHAR_Rating_COLOR);
    setbkcolor(CHAR_Rating_BKCOLOR);
    outtextxy(RatingShowBeginX, RatingShowBeginY - RatingShowBeginHigh, _T("Rating of Score"));
    for (size_t i = 0; (i < MaxRatingNumShow) && (i < Vision2ScoreEntries.size()); i++)
    {
        cout << "���" << endl;
        TCHAR RatingText[100];
        _stprintf_s(RatingText, _T("%d. %s %d"), (i + 1), Vision2ScoreEntries[i].getPlayerName().c_str(), Vision2ScoreEntries[i].getScore());
        outtextxy(RatingShowBeginX, RatingShowBeginY - RatingShowBeginHigh + CharRtingHeight * (i + 1), RatingText);
    }

    outtextxy(RatingShowBeginX, RatingShowBeginY + CharRtingHeight * (MaxRatingNumShow + 1), _T("Rating of Length"));
    for (size_t i = 0; (i < MaxRatingNumShow) && (i < Vision2LengthEntries.size()); i++)
    {
        cout << "���" << endl;
        TCHAR RatingText[100];
        _stprintf_s(RatingText, _T("%d. %s %d"), (i + 1), Vision2LengthEntries[i].getPlayerName().c_str(), Vision2LengthEntries[i].getLength());
        outtextxy(RatingShowBeginX, RatingShowBeginY + CharRtingHeight * (MaxRatingNumShow + 1) + CharRtingHeight * (i + 1), RatingText);
    }
}
void Menu::ShowRatingList()
{
    if (RatingClickOption == BasicGame)
        showRatinglistBasic();
    if (RatingClickOption == SecondGame)
        showRatinglistSecond();
    if (RatingClickOption == AdvanceGame)
        showRatinglistAdvance();
    drawBackButton();
    CheckClickReturn();

}
void Menu::drawBackButton()
{
    // ���Ʒ��ؼ���ͼ��
    settextstyle(CharRtingHeight, 0, _T("����"));
    settextcolor(CHAR_Rating_COLOR);
    setbkcolor(CHAR_Rating_BKCOLOR);
    outtextxy(RatingShowBeginX, RatingShowBeginY - 3 * CharRtingHeight, _T("����"));
}
void Menu::CheckClickReturn()
{
    while (ischeckRating) {
        if (MouseHit()) {
            MOUSEMSG m = GetMouseMsg();  // ��ȡ�����Ϣ
            switch (m.uMsg) {
            case WM_LBUTTONDOWN:
                if (ischeckRating)
                    handleMouseClickBackButton(m.x, m.y);//���������ؼ������
                break;
            case WM_MOUSEMOVE:
                if (ischeckRating)
                    handleRankingMouseBackButtonHover(m.x, m.y);
                break;
            default:
                break;
            }
        }
    }
}
void Menu::handleMouseClickBackButton(int x, int y)
{
    if ((x >= RatingShowBeginX && x <= RatingShowBeginX + CharRtingHeight * 2) && (y >= RatingShowBeginY - 3 * CharRtingHeight && y <= RatingShowBeginY))
    {
        // �����ؼ��ĵ���¼�
        cout << "����˷���" << endl;
        handleBackButton();
    }
}
void Menu::handleRankingMouseBackButtonHover(int x, int y)
{
    // �����ͣЧ��
    drawBackButton();
    settextstyle(CharRtingHeight, 0, _T("����"));
    settextcolor(CHAR_HoverCOLOR);
    setbkcolor(CHAR_HoverBKCOLOR);
    if (y >= RatingShowBeginY - 3 * CharRtingHeight && y < RatingShowBeginY && x >= RatingShowBeginX && x < RatingShowBeginX + 2 * CharRtingHeight) {
        outtextxy(RatingShowBeginX, RatingShowBeginY - 3 * CharRtingHeight, _T("����"));
    }
}
void Menu::handleBackButton()
{
    ischeckRating = false;
    Delete_Rating_Windows();
}
void Menu::Delete_Rating_Windows()
{
    setfillcolor(MenuBKColor);
    setbkcolor(MenuBKColor);
    cleardevice();
    drawRule();
    displayMenuDecision();

}
//������
class ShowInformation
{
private:
    size_t Vision;
    wstring Usersname;
    size_t LifeNum;
    size_t Score;
    size_t Length;
    size_t GameTime;
    size_t HistoryRecord;
    size_t Showsize;
    size_t BeginX = (WIDE + 1) * UNIT;
    size_t BeginY = UNIT;
public:
    ShowInformation(size_t canshu) :Vision(canshu), Showsize(WINDOW_Show_Score_SIZE), Score(0), Length(0), GameTime(0)
    {
        setHistoryRecord();
        setLifeNum();
        Usersname = ' ';
    }
    void setLifeNum();
    void negaLifeNum() { LifeNum--; };
    void setHistoryRecord();
    void setHistoryRecord(int score);
    void setscore(int num)
    {
        Score = num;
    }
    void setUsersName(wstring name)
    {
        Usersname = name;
    }
    void setlength(int length)
    {
        Length = length;
    }
    void drawInformation();
    void drawVision();
    void drawusersName();
    //չ�ֳ���ĵ�ǰ����ֵ
    void drawGameLife();
    void drawinformationFrame();
    void drawGameScoreLength();
    void drawTime();
    void drawRecord();
    void drawexplain();
    void settext();
    void drawHistoryRecord();
    void drawFoodexplain();
    size_t getLifeNum() { return LifeNum; };

};
void ShowInformation::setLifeNum()
{
    switch (Vision) {
    case BasicGame:
        LifeNum = 1;
        break;
    case SecondGame:
        LifeNum = LifeMAXNUM;
        break;
    case AdvanceGame:
        LifeNum = LifeMAXNUM;
        break;
    default:
        LifeNum = 0;
        break;
    }
}
void ShowInformation::drawGameScoreLength() {
    LOGFONT f;
    //��ǰ����
    gettextstyle(&f);						// ��ȡ��ǰ��������
    f.lfHeight = CHAR_INFOR_HIGH * 3 / 2;						// ��������߶�
    f.lfItalic = true;
    f.lfUnderline = false;//�»���
    f.lfQuality = ANTIALIASED_QUALITY;		// �������Ч��Ϊ�����  
    f.lfWeight = CHAR_INFOR_SIZE;//�ַ���ϸ
    settextstyle(&f);
    settextcolor(CHAR_INFOR_COLOR);
    setbkcolor(SHOWBASIK_COLOR);
    outtextxy(BeginX, BeginY + 6 * CHAR_INFOR_HIGH + CHAR_INFOR_HIGH / 2, _T("Score:"));
    outtextxy(BeginX, BeginY + 8 * CHAR_INFOR_HIGH + CHAR_INFOR_HIGH / 2, _T("Length:"));
    outtextxy(BeginX, BeginY + 10 * CHAR_INFOR_HIGH + CHAR_INFOR_HIGH / 2, _T("Time :"));

    TCHAR ScoreText[50];
    _stprintf_s(ScoreText, _T("%d"), Score);
    outtextxy(BeginX + CHAR_INFOR_HIGH * 5 + CHAR_INFOR_HIGH / 2, BeginY + 6 * CHAR_INFOR_HIGH + CHAR_INFOR_HIGH / 2, ScoreText);

    TCHAR LengthText[50];
    _stprintf_s(LengthText, _T("%d"), Length);
    outtextxy(BeginX + CHAR_INFOR_HIGH * 5 + CHAR_INFOR_HIGH / 2, BeginY + 8 * CHAR_INFOR_HIGH + CHAR_INFOR_HIGH / 2, LengthText);
}
void ShowInformation::drawGameLife()
{
    LOGFONT f;
    gettextstyle(&f);						// ��ȡ��ǰ��������
    f.lfHeight = CHAR_INFOR_HIGH * 2;						// ��������߶�
    f.lfItalic = false;
    f.lfUnderline = false;//�»���
    f.lfQuality = ANTIALIASED_QUALITY;		// �������Ч��Ϊ�����  
    f.lfWeight = CHAR_INFOR_SIZE + 100;//�ַ���ϸ
    settextstyle(&f);
    settextcolor(CHAR_INFOR_COLOR);
    setbkcolor(SHOWBASIK_COLOR);
    outtextxy(BeginX, BeginY + 4 * CHAR_INFOR_HIGH + CHAR_INFOR_HIGH / 2, _T("LIFE:     ��"));
    settextcolor(RGB(243, 59, 31));
    setbkcolor(SHOWBASIK_COLOR);

    IMAGE img;
    loadimage(&img, _T("Life.png"));
    // �ڻ�������ʾ����ͼƬ
    putimage(BeginX + CHAR_INFOR_HIGH * 4 + CHAR_INFOR_HIGH / 2, BeginY + 4 * CHAR_INFOR_HIGH + CHAR_INFOR_HIGH * 7 / 10, &img);

    TCHAR GamelifeText[50];
    _stprintf_s(GamelifeText, _T("%d"), LifeNum);
    outtextxy(BeginX + CHAR_INFOR_HIGH * 8, BeginY + 4 * CHAR_INFOR_HIGH + CHAR_INFOR_HIGH / 2, GamelifeText);  // ����û�����

}
void ShowInformation::settext() {
    LOGFONT f;
    gettextstyle(&f);						// ��ȡ��ǰ��������
    f.lfHeight = CHAR_INFOR_HIGH * 2;						// ��������߶�
    f.lfItalic = true;
    _tcscpy_s(f.lfFaceName, _T("Gill Sans Ultra Bold"));		// ��������
    f.lfQuality = ANTIALIASED_QUALITY;		// �������Ч��Ϊ�����  
    f.lfWeight = CHAR_INFOR_SIZE;//�ַ���ϸ
    settextstyle(&f);
    settextcolor(CHAR_INFOR_COLOR);
    setbkcolor(SHOWBASIK_COLOR);
}
void ShowInformation::setHistoryRecord()
{
    switch (Vision) {
    case BasicGame:
        if (!Vision1ScoreEntries.empty()) {
            LeaderboardEntry firstEntry = Vision1ScoreEntries[0];
            HistoryRecord = firstEntry.getScore();
        }
        else {
            HistoryRecord = 0;
        }
        break;
    case SecondGame:
        if (!Vision2ScoreEntries.empty()) {
            LeaderboardEntry firstEntry = Vision2ScoreEntries[0];
            HistoryRecord = firstEntry.getScore();
        }
        else {
            HistoryRecord = 0;
        }
        break;
    case AdvanceGame:
        if (!Vision3ScoreEntries.empty()) {
            LeaderboardEntry firstEntry = Vision3ScoreEntries[0];
            HistoryRecord = firstEntry.getScore();
        }
        else {
            HistoryRecord = 0;
        }
        break;
    default:
        HistoryRecord = 0;
        break;
    }
}
void ShowInformation::drawFoodexplain()
{
    //ʳ������ֽ���
    LOGFONT f;
    IMAGE imgApple;
    IMAGE imgBanana;
    IMAGE imgTreasureChest;
    IMAGE imgBluePosion;
    IMAGE imgPurplePosion;
    loadimage(&imgApple, _T("Apple.png"));
    loadimage(&imgBanana, _T("Banana.png"));
    loadimage(&imgTreasureChest, _T("TreasureChest.png"));
    loadimage(&imgBluePosion, _T("BluePosion.png"));
    loadimage(&imgPurplePosion, _T("PurplePosion.png"));

    // �ڻ�������ʾappleͼƬ
    putimage(BeginX, BeginY + 14 * CHAR_INFOR_HIGH + CHAR_INFOR_HIGH / 2, &imgApple);;
    putimage(BeginX, BeginY + 14 * CHAR_INFOR_HIGH + CHAR_INFOR_HIGH / 2 + PIC * 5 / 4, &imgBanana);
    putimage(BeginX, BeginY + 14 * CHAR_INFOR_HIGH + CHAR_INFOR_HIGH / 2 + PIC * 5 / 4 * 2, &imgTreasureChest);
    putimage(BeginX, BeginY + 14 * CHAR_INFOR_HIGH + CHAR_INFOR_HIGH / 2 + PIC * 5 / 4 * 3, &imgBluePosion);
    putimage(BeginX, BeginY + 14 * CHAR_INFOR_HIGH + CHAR_INFOR_HIGH / 2 + PIC * 5 / 4 * 4, &imgPurplePosion);


    gettextstyle(&f);						// ��ȡ��ǰ��������
    f.lfHeight = CHAR_INFOR_HIGH * 6 / 5;						// ��������߶�
    f.lfItalic = true;
    f.lfUnderline = false;//�»���
    f.lfQuality = ANTIALIASED_QUALITY;		// �������Ч��Ϊ�����  
    f.lfWeight = CHAR_INFOR_SIZE / 2;//�ַ���ϸ
    settextstyle(&f);
    settextcolor(CHAR_INFOR_COLOR);
    setbkcolor(SHOWBASIK_COLOR);

    setfillcolor(APPLE_COLOR);
    fillrectangle(BeginX + PIC + 5, 13 * CHAR_INFOR_HIGH + CHAR_INFOR_HIGH * 3 / 4 + PIC, BeginX + 2 * PIC + 5, 13 * CHAR_INFOR_HIGH + CHAR_INFOR_HIGH * 3 / 4 + 2 * PIC);
    outtextxy(BeginX + 2 * PIC + 6, 13 * CHAR_INFOR_HIGH + CHAR_INFOR_HIGH * 3 / 4 + PIC + 5, _T("Score+1 Length+1"));


    setfillcolor(BANANA_COLOR);
    fillrectangle(BeginX + PIC + 5, 13 * CHAR_INFOR_HIGH + CHAR_INFOR_HIGH * 3 / 4 + 2 * PIC + PIC / 4, BeginX + 2 * PIC + 5, 13 * CHAR_INFOR_HIGH + CHAR_INFOR_HIGH * 3 / 4 + 3 * PIC + PIC / 4);
    outtextxy(BeginX + 2 * PIC + 6, 13 * CHAR_INFOR_HIGH + CHAR_INFOR_HIGH * 3 / 4 + 2 * PIC + PIC / 4 + 5, _T("Score+2 Length+2"));


    setfillcolor(TREASURECHEST_COLOR);
    fillrectangle(BeginX + PIC + 5, 13 * CHAR_INFOR_HIGH + CHAR_INFOR_HIGH * 3 / 4 + 3 * PIC + PIC / 2, BeginX + 2 * PIC + 5, 13 * CHAR_INFOR_HIGH + CHAR_INFOR_HIGH * 3 / 4 + 4 * PIC + PIC / 2);
    outtextxy(BeginX + 2 * PIC + 6, 13 * CHAR_INFOR_HIGH + CHAR_INFOR_HIGH * 3 / 4 + 3 * PIC + PIC / 2 + 5, _T("Slowdown Score*2"));

    setfillcolor(BLUEPOSION_COLOR);
    fillrectangle(BeginX + PIC + 5, 13 * CHAR_INFOR_HIGH + CHAR_INFOR_HIGH * 3 / 4 + 4 * PIC + PIC * 3 / 4, BeginX + 2 * PIC + 5, 13 * CHAR_INFOR_HIGH + CHAR_INFOR_HIGH * 3 / 4 + 5 * PIC + PIC * 3 / 4);
    outtextxy(BeginX + 2 * PIC + 6, 13 * CHAR_INFOR_HIGH + CHAR_INFOR_HIGH * 3 / 4 + 4 * PIC + PIC * 3 / 4 + 5, _T("Score-10 Length-2"));

    setfillcolor(PURPLEPOSION_COLOR);
    fillrectangle(BeginX + PIC + 5, 13 * CHAR_INFOR_HIGH + CHAR_INFOR_HIGH * 3 / 4 + 6 * PIC, BeginX + 2 * PIC + 5, 13 * CHAR_INFOR_HIGH + CHAR_INFOR_HIGH * 3 / 4 + 7 * PIC);
    outtextxy(BeginX + 2 * PIC + 6, 13 * CHAR_INFOR_HIGH + CHAR_INFOR_HIGH * 3 / 4 + 6 * PIC + 5, _T("Score/3 Dead"));

}
void ShowInformation::drawInformation()
{
    settext();
    drawinformationFrame();
    drawVision();
    drawusersName();
    drawGameLife();
    drawGameScoreLength();
    drawTime();
    drawHistoryRecord();
    drawFoodexplain();
}
void ShowInformation::drawHistoryRecord()
{
    //��ʷ��߷�
    LOGFONT f;
    gettextstyle(&f);						// ��ȡ��ǰ��������
    f.lfHeight = CHAR_INFOR_HIGH * 2;						// ��������߶�
    f.lfItalic = false;
    f.lfUnderline = true;//�»���
    f.lfQuality = ANTIALIASED_QUALITY;		// �������Ч��Ϊ�����  
    f.lfWeight = CHAR_INFOR_SIZE;//�ַ���ϸ
    settextstyle(&f);
    settextcolor(RGB(243, 59, 31));
    setbkcolor(SHOWBASIK_COLOR);
    outtextxy(BeginX, BeginY + 12 * CHAR_INFOR_HIGH + CHAR_INFOR_HIGH / 2, _T("RECORD:"));
    TCHAR RECORD[100];
    if (Score >= HistoryRecord)
        _stprintf_s(RECORD, _T(" %d"), Score);
    else
        _stprintf_s(RECORD, _T(" %d"), HistoryRecord);
    outtextxy(BeginX + CHAR_INFOR_HIGH * 7 + CHAR_INFOR_HIGH * 4 / 5, BeginY + 12 * CHAR_INFOR_HIGH + CHAR_INFOR_HIGH / 2, RECORD);
}
void ShowInformation::drawTime()
{
    outtextxy(BeginX + CHAR_INFOR_HIGH * 5 + CHAR_INFOR_HIGH / 2, BeginY + 10 * CHAR_INFOR_HIGH + CHAR_INFOR_HIGH / 2, _T("              S"));
    LOGFONT f;
    gettextstyle(&f);						// ��ȡ��ǰ��������
    f.lfHeight = CHAR_INFOR_HIGH * 2;						// ��������߶�
    f.lfItalic = false;
    f.lfUnderline = true;//�»���
    f.lfQuality = ANTIALIASED_QUALITY;		// �������Ч��Ϊ�����  
    f.lfWeight = CHAR_INFOR_SIZE;//�ַ���ϸ
    settextstyle(&f);
    settextcolor(CHAR_INFOR_COLOR);
    setbkcolor(SHOWBASIK_COLOR);
    TCHAR TIME[100];
    _stprintf_s(TIME, _T(" %s"), to_wstring(static_cast<int>(round(gameTime))).c_str());
    outtextxy(BeginX + CHAR_INFOR_HIGH * 5, BeginY + 10 * CHAR_INFOR_HIGH + CHAR_INFOR_HIGH / 5, TIME);  // ʱ��

}
void ShowInformation::drawVision()
{
    LOGFONT f;
    gettextstyle(&f);						// ��ȡ��ǰ��������
    _tcscpy_s(f.lfFaceName, _T("Gill Sans Ultra Bold"));		// ��������
    f.lfUnderline = false;//�»���
    //��ǰģʽ
    f.lfHeight = CHAR_INFOR_HIGH * 2;						// ��������߶�
    settextstyle(&f);
    if (Vision == BasicGame)
        outtextxy(BeginX, BeginY + CHAR_INFOR_HIGH, _T("Mode:Basic"));
    if (Vision == SecondGame)
        outtextxy(BeginX, BeginY + CHAR_INFOR_HIGH, _T("Mode:Second"));
    if (Vision == AdvanceGame)
        outtextxy(BeginX, BeginY + CHAR_INFOR_HIGH, _T("Mode:Advance"));
}
void ShowInformation::drawinformationFrame()
{
    // ���ñ߿���ɫ�������ɫ
    setcolor(SHOWBASIKFRAME_COLOR);          // 
    setfillcolor(SHOWBASIK_COLOR);   //
    // ���ƾ��α߿�
    roundrect(WIDE * UNIT, UNIT, (WIDE + WINDOW_Show_Score_SIZE - 1) * UNIT, (HIGH - 1) * UNIT, UNIT * 4, UNIT * 4);
    // ������
    floodfill((WIDE + WINDOW_Show_Score_SIZE / 2) * UNIT, HIGH * UNIT / 2, SHOWBASIKFRAME_COLOR);//�߿�
}
void ShowInformation::drawusersName()
{
    LOGFONT f;
    gettextstyle(&f);						// ��ȡ��ǰ��������
    f.lfHeight = CHAR_INFOR_HIGH + 5;						// ��������߶�
    settextstyle(&f);
    outtextxy(BeginX, BeginY + 3 * CHAR_INFOR_HIGH, _T("Player:"));

    settextcolor(CHAR_INFOR_COLOR);
    setbkcolor(WHITE);
    //outtextxy(BeginX + 4 * CHAR_INFOR_HIGH, BeginY + 3 * CHAR_INFOR_HIGH, _T("XXXXXXXXXXX"));
    TCHAR UsersNameText[100];
    _stprintf_s(UsersNameText, _T(" %s"), Usersname.c_str());
    outtextxy(BeginX + 4 * CHAR_INFOR_HIGH, BeginY + 3 * CHAR_INFOR_HIGH, UsersNameText);  // ����û�����
}
// ǽ��
class Wall {
private:
    int length;
    vector<pair<int, int>> blocks;   // ǽ���б�
public:
    //���ڴ�СΪHIGH * UNIT, WIDE * UNIT
    //���ڵĴ�С�������ǽ��λ��
    //���մ�ԭ�㿪ʼ��˳ʱ���˳���ʼ��
    Wall() {
        for (int i = 1; i <= WIDE; i++)
        {
            blocks.push_back(make_pair(i - 1, 0));
        }
        blocks.pop_back();//ɾȥ���һ��
        for (int i = 1; i <= HIGH; i++)
        {
            blocks.push_back(make_pair(WIDE - 1, i - 1));
        }
        blocks.pop_back();//ɾȥ���һ��
        for (int i = WIDE; i >= 1; i--)
        {
            blocks.push_back(make_pair(i - 1, HIGH - 1));
        }
        blocks.pop_back();//ɾȥ���һ��
        for (int i = HIGH; i >= 1; i--)
        {
            blocks.push_back(make_pair(0, i - 1));
        }
        blocks.pop_back();//ɾȥ���һ��

        length = blocks.size();
    }
    void drawBlocks()
    {
        setfillcolor(WALL_COLOR);
        for (int i = 0; i < length; i++)
        {
            fillrectangle(blocks[i].first * UNIT, blocks[i].second * UNIT, (blocks[i].first + 1) * UNIT, (blocks[i].second + 1) * UNIT);
        }
    }
    void show()
    {
        cout << "length=" << length << endl;
        for (int i = 1; i <= length; i++)
        {
            cout << blocks[i - 1].first << " " << blocks[i - 1].second << "||";
            if (i % WIDE == 0)
                cout << endl;
        }
    }
    // ���ǽ��
    void addBlock(int posX, int posY) {
        blocks.push_back(make_pair(posX, posY));
        length++;
    }

    // ��ȡǽ���б�
    vector<pair<int, int>> getBlocks() const {
        return blocks;
    }

    int getlength()const {
        return length;
    }
};
// ʳ����
enum class FoodType {
    Apple = 1,          // ƻ�������ȼ�1��������1
    Banana = 2,         // �㽶�����ȼ�2��������2
    PurplePoison = 3,   // ��ɫ��ҩ��ֱ�ӹҵ�
    BluePoison = 4,     // ��ɫ��ҩ������-2������-5
    TreasureChests = 5, // ����
};
struct FoodItem {
public:
    pair<int, int> position;  // ʳ���λ������
    FoodType type;            // ʳ������
    FoodItem()
    {
        type = FoodType::Apple;
    }
};
class Food {
private:
    size_t Food_num;              // ʳ�������
    size_t score;
    vector<FoodItem> foods;    // ʳ���б�
public:


    // ���캯��

    Food(int Vision)//:type(FoodType::Apple)  // Ĭ��ʳ������Ϊƻ��
    {
        srand((unsigned)time(NULL));
        Food_num = rand() % FOODNUM + 1 + (Vision - 1) * FOODNUM;
        score = 0;
        createFood();
    }

    void createFood();
    void createFood(Snake& snake, Wall& wall);
    // ��ȡʳ���λ��
    vector<FoodItem> getfoods() const { return foods; };

    // ��ȡʳ�������
    int  getFoodnum() const {
        return Food_num;
    }
    int  getscore() const {
        return score;
    }
    //ɾ��������ָ��λ�õ�ʳ��
    void deleteFood(int pos)//, Snake& snake)
    {
        foods.erase(foods.begin() + pos);
        Food_num = foods.size();
    }

    // �����³��ֵ�ʳ���λ��
    void setNEWPosition(int posX, int posY, FoodType foodType)
    {
        FoodItem newFood;
        newFood.position = make_pair(posX, posY);
        newFood.type = foodType;
        foods.push_back(newFood);
        Food_num = foods.size();
    }
    void makeNewFood(Snake& snake, Wall& wall, int vision);
    //����ʳ��
    void drawFood() {
        for (size_t i = 0; i < Food_num; i++) {
            COLORREF color = getcolor(i);
            setfillcolor(color);
            fillrectangle(foods[i].position.first * UNIT, foods[i].position.second * UNIT, (foods[i].position.first + 1) * UNIT, (foods[i].position.second + 1) * UNIT);

        }
    }
    COLORREF getcolor(int pos)
    {
        switch (foods[pos].type) {
        case FoodType::Apple:
            return APPLE_COLOR;
            break;
        case FoodType::Banana:
            return BANANA_COLOR;
            break;
        case FoodType::PurplePoison:
            return PURPLEPOSION_COLOR;
            break;
        case FoodType::TreasureChests:
            return TREASURECHEST_COLOR;
            break;
        case FoodType::BluePoison:
            return BLUEPOSION_COLOR;
            break;
        default:
            cout << "WARNNING!!!�����˲�ͬ��ɫ��ʳ��" << endl;
            Sleep(5000);
            return BLACK;
            break;
        }
    }
    //���ʳ��
    void deleteFood()
    {
        foods.clear();
        Food_num = 0;
    }
    FoodType generateRandomFoodType()//�����������
    {
        int random = rand() % 30 + 1; // ����1��30֮��������
        if (random == 1) {
            return FoodType::TreasureChests; // ����Treasureʳ������//treasure�ĸ���Ϊ1/30
        }
        else {
            // �����������������������͵�ʳ��
            int foodType = rand() % (FOODTYPE - 1) + 1; // ����1��FOODTYPE-1֮��������
            return static_cast<FoodType>(foodType);
        }
    }

    void showfoods()
    {
        cout << "ʳ������Ϊ" << Food_num << endl;
        cout << "������СΪ" << foods.size() << endl;
        for (size_t i = 0; i < foods.size(); i++)
        {
            cout << "��ǰ����Ϊ:" << foods[i].position.first << " "
                << foods[i].position.second << " ��ǰ����Ϊ:" << int(foods[i].type) << endl;
        }
    }

    // ����Ե�ʳ����߼�
    void processFood(int pos, Snake& snake);


};


// ����
class Snake {
public:
    // �ߵķ���
    enum class Direction {
        UP = 1,
        DOWN = 2,
        LEFT = 3,
        RIGHT = 4
    };

    // ���캯��
    //���������м�
    Snake(int initialSize = SNAKEBASICBODY, int startX = WIDE / 2, int startY = HIGH / 2, Direction initialDirection = Direction::RIGHT)
        : size(initialSize), direction(initialDirection) {//initialSize:��ʼ����  ,(startX,startY):��ʼ����
        // ��ʼ���ߵ�����                                 //initialDirection :��ʼ����
        for (size_t i = 0; i < size; ++i) {
            body.push_back(make_pair(startX, startY + i));
        }
    }
    // ��ȡ�ߵ���������
    vector<pair<int, int>> getBody() const {
        return body;
    }

    // ��ȡ��ͷ����
    pair<int, int> getHead() const {
        return body.front();
    }

    // ��ȡ�ߵķ���
    Direction getDirection() const {
        return direction;
    }
    int getsize()const { ; return size; }
    // �����ߵķ���
    void setDirection(Direction newDirection) {
        direction = newDirection;
    }
    //������
    void drawSnake();
    // �ƶ��ߵ�����
    // �Ӽ��̶�ȡ����
    void MoveSnake();
    void readDirectionFromKeyboard();

    void IncreaseSnakebody(Food& food, Wall& wall);
    void DecreaseSnakebody();
    bool is_inBody(int x, int y);
    bool is_inFood(int x, int y, Food& food);
    bool is_inWall(int x, int y, Wall& wall);
    bool is_kill();
    void resetkill() { iskill = false; }
    void kill() { iskill = true; };
    void deleteSnake() { body.clear(); };//ɾ����
    void returnBasicLength() { size = SNAKEBASICBODY; }//�ָ���ʼ����
    void REcreateSnake(Food& food, Wall& wall);//�ٴ�������
    void setSnakeBodyIncrease(int change) { SnakeBodyIncrease = change; }
    void setSnakeBodyDecrease(int change) { SnakeBodyDecrease = change; }
    void snakeUpdata(Food& food, Wall& wall);
private:
    size_t SnakeBodyIncrease = 0;
    size_t SnakeBodyDecrease = 0;
    bool iskill = false;
    size_t size;                                // �ߵĳ���
    Direction direction;                     // �ߵķ���
    vector<pair<int, int>> body;   // �ߵ���������   bodyΪһ�����飬�洢�����������ԣ���first��second����x��y����
};
void Snake::drawSnake() {
    for (size_t i = 0; i < body.size(); i++)
    {
        setfillcolor(i == 0 ? SnakeHead_COLOR : SnakeBody_COLOR);
        if (i == 0)
            solidroundrect(body[i].first * UNIT, body[i].second * UNIT, (body[i].first + 1) * UNIT, (body[i].second + 1) * UNIT, 20, 20);
        else
            fillrectangle(body[i].first * UNIT, body[i].second * UNIT, (body[i].first + 1) * UNIT, (body[i].second + 1) * UNIT);

    }
}
void Snake::MoveSnake()
{
    pair<int, int> head = getHead();  //�����ͷ������
    switch (direction) {
    case Direction::RIGHT:
        body.insert(body.begin(), make_pair(head.first + 1, head.second));//�����µ���ͷ
        break;
    case Direction::LEFT:
        body.insert(body.begin(), make_pair(head.first - 1, head.second));//�����µ���ͷ
        break;
    case Direction::UP:
        body.insert(body.begin(), make_pair(head.first, head.second - 1));//�����µ���ͷ
        break;
    case Direction::DOWN:
        body.insert(body.begin(), make_pair(head.first, head.second + 1));//�����µ���ͷ
        break;
    }
    // ����ߵĳ��ȳ�����ǰ��С����ɾ��β�����Դ������ֳ��Ȳ���
    if (body.size() > size) {
        body.pop_back();
    }
}
void Snake::readDirectionFromKeyboard() {
    if (_kbhit()) {//ֻ�ܼ��̣��ж��ǲ����ڼ�����������
        char ch = _getch();  // �Ӽ��̶�ȡ�ַ�
        switch (ch) {
        case 'w':
        case 'W':
            if (direction != Direction::DOWN) {
                setDirection(Snake::Direction::UP);//���÷���ΪUP
            }
            break;
        case 's':
        case 'S':
            if (direction != Direction::UP) {
                setDirection(Snake::Direction::DOWN);//���÷���ΪDOWN
            }
            break;
        case 'a':
        case 'A':
            if (direction != Direction::RIGHT) {
                setDirection(Snake::Direction::LEFT);//���÷���ΪLEFT
            }
            break;
        case 'd':
        case 'D':
            if (direction != Direction::LEFT) {
                setDirection(Snake::Direction::RIGHT);//���÷���ΪRIGHT
            }
            break;
        default:
            // �������������������Ч����
            break;
        }
    }
}
void Snake::IncreaseSnakebody(Food& food, Wall& wall)
{
    for (size_t i = 0; i < SnakeBodyIncrease; i++) {
        int end_x = body[body.size() - 1].first, end_y = body[body.size() - 1].second;
        vector<pair<int, int>> newbody;
        newbody = { {end_x,end_y - 1 }, { end_x + 1,end_y }, { end_x,end_y + 1 }, { end_x - 1,end_y } };

        for (size_t i = 0; i < newbody.size(); i++)
        {
            bool havespace = true;

            if (is_inFood(newbody[i].first, newbody[i].second, food))
            {
                havespace = false;
                continue;
            }
            if (is_inWall(newbody[i].first, newbody[i].second, wall))
            {
                havespace = false;
                continue;
            }
            if (is_inBody(newbody[i].first, newbody[i].second))
            {
                havespace = false;
                continue;
            }
            if (havespace)
            {
                body.push_back(make_pair(newbody[i].first, newbody[i].second));
                break;
            }
        }
        size = body.size();
    }
    size = body.size();
    SnakeBodyIncrease = 0;
}
void Snake::DecreaseSnakebody()
{

    if (size > SnakeBodyDecrease) {
        for (size_t i = 0; i < SnakeBodyDecrease; i++)
        {
            if (!body.empty())
                body.pop_back();//ɾ�����һ��Ԫ��
        }
        SnakeBodyDecrease = 0;
    }
    else
        kill();
    size = body.size();
}
bool Snake::is_inBody(int x, int y)
{
    bool isinbody = false;
    vector<pair<int, int>> bodypoints = this->getBody();
    int bodysize = bodypoints.size();
    for (int i = 0; i < bodysize; i++)
    {
        if ((x == bodypoints[i].first) && (y == bodypoints[i].second))
        {
            isinbody = true;
            break;
        }
        else
            isinbody = false;
    }
    return isinbody;
}
bool Snake::is_inFood(int x, int y, Food& food)
{
    bool isinfood = false;
    vector<FoodItem> foodpoints = food.getfoods();
    int foodsize = foodpoints.size();
    for (int i = 0; i < foodsize; i++)
    {
        if ((x == foodpoints[i].position.first) && (y == foodpoints[i].position.second))
        {
            isinfood = true;
            break;
        }
        else
            isinfood = false;
    }
    return isinfood;
}
bool Snake::is_inWall(int x, int y, Wall& wall)
{
    bool isinwall = false;
    vector<pair<int, int>> wallpoints = wall.getBlocks();
    int wallsize = wallpoints.size();
    for (int i = 0; i < wallsize; i++)
    {
        if ((x == wallpoints[i].first) && (y == wallpoints[i].second))
        {
            isinwall = true;
            break;
        }
        else
            isinwall = false;
    }
    return isinwall;
}
bool Snake::is_kill()
{
    if (iskill)
        return true;
    else
        return false;
}
void Snake::REcreateSnake(Food& food, Wall& wall)
{//���֮���ٴ�������

    returnBasicLength();//�ָ���ʼ����

    vector<FoodItem> foodpoints = food.getfoods();
    int foodnum = foodpoints.size();

    vector<pair<int, int>> wallpoints = wall.getBlocks();
    int wallsize = wallpoints.size();

    bool p = true;

    srand((unsigned)time(NULL));
    while (true) {
        int x = rand() % WIDE;
        int y = rand() % HIGH;

        for (int j = 0; j < foodnum; j++)
        {
            if ((x == foodpoints[j].position.first) && (y == foodpoints[j].position.second)) {
                p = false;
                break;
            }
            else
                p = true;
        }
        if (p) {
            for (int k = 0; k < wallsize; k++)
            {
                if ((x == wallpoints[k].first) && (y == wallpoints[k].second)) {
                    p = false;
                    break;
                }
                else
                    p = true;
            }
        }
        if (p) {//�õ����пռ��
            body.push_back(make_pair(x, y));
            break;//����ѭ��
        }
    }
}
void Snake::snakeUpdata(Food& food, Wall& wall)
{
    if (SnakeBodyIncrease != 0)
        IncreaseSnakebody(food, wall);
    if (SnakeBodyDecrease != 0)
        DecreaseSnakebody();
}


// ����Ե�ʳ����߼�
void Food::processFood(int pos, Snake& snake) {
    switch (foods[pos].type) {
    case FoodType::Apple:
        deleteFood(pos);//ɾ��һ���ط���ʳ��
        snake.setSnakeBodyIncrease(1);//��Ҫ���ӵĳ���Ϊ1
        score += 1;
        break;
    case FoodType::Banana:
        deleteFood(pos);//ɾ��һ���ط���ʳ��
        snake.setSnakeBodyIncrease(2);//�ߵı仯
        score += 2;
        break;
    case FoodType::PurplePoison:
        deleteFood(pos);//ɾ��һ���ط���ʳ��
        snake.kill(); // ������ҹҵ����߼�
        score /= 3;
        break;
    case FoodType::TreasureChests:
        deleteFood(pos);//ɾ��һ���ط���ʳ��
        snake.setSnakeBodyIncrease(3);
        OriFPS *= (SPEEDDOWN_FACTOR * SPEEDDOWN_FACTOR);//ʱ�����
        frameDelay = CANSHU / OriFPS;
        score *= 2;//�÷֡�2
        break;
    case FoodType::BluePoison:
        deleteFood(pos);//ɾ��һ���ط���ʳ��
        snake.setSnakeBodyDecrease(2);//����2����λ
        score -= 10;//�÷ּ�ȥ10
        break;
    default:
        break;
    }
}
void Food::createFood()//���ɵĵ�һ�Σ�����
{
    // ����ʳ���λ�ú����ͣ�����ӵ�ʳ���б���
    srand((unsigned)time(NULL));
    for (size_t i = 0; i < Food_num; ) {

        int x = rand() % WIDE;
        int y = rand() % HIGH;
        if ((x == 0 || x == WIDE - 1) || (y == 0 || y == HIGH - 1))//�����ڱ߽�
            continue;
        else
        {
            FoodItem food;
            if (i == 0)
                food.type = FoodType::Apple;//���ٳ���һ�����ԳԵ�ʳ��
            else
                food.type = generateRandomFoodType();//��������
            food.position = make_pair(x, y);//��������
            foods.push_back(food);
            i++;
        }
    }
}
void Food::createFood(Snake& snake, Wall& wall)//���ܳ�����ǽ�ں���������,����//���ڸ߼��汾���������ɸ������ʳ�������һ�����
{
    srand((unsigned)time(NULL));

    vector<pair<int, int>> snakepoints = snake.getBody();
    int snakesize = snakepoints.size();

    vector<pair<int, int>> wallpoints = wall.getBlocks();
    int wallsize = wallpoints.size();

    bool p = true;

    for (size_t i = 0; i < Food_num;)
    {
        int x = rand() % WIDE;
        int y = rand() % HIGH;

        for (int j = 0; j < snakesize; j++)
        {
            if ((x == snakepoints[j].first) && (y == snakepoints[j].second)) {
                p = false;
                break;
            }
            else
                p = true;
        }
        if (p) {
            for (int k = 0; k < wallsize; k++)
            {
                if ((x == wallpoints[k].first) && (y == wallpoints[k].second)) {
                    p = false;
                    break;
                }
                else
                    p = true;
            }
        }
        if (p) {
            FoodItem food;
            if (i == 0)
                food.type = FoodType::Apple;
            else
                food.type = generateRandomFoodType();//��������
            food.position = make_pair(x, y);//��������
            foods.push_back(food);
            i++;
        }
    }
}
void Food::makeNewFood(Snake& snake, Wall& wall, int vision)
{
    deleteFood();
    if (vision == BasicGame)
        Food_num = rand() % FOODNUM + 1;
    else if (vision == SecondGame)
        Food_num = rand() % FOODNUM + SecondGame * SecondGame * FOODNUM;
    else if (vision == AdvanceGame)
        Food_num = rand() % FOODNUM + AdvanceGame * AdvanceGame * FOODNUM;
    createFood(snake, wall);
}
class GameGreedySnake
{
private:
    bool GameLife;
    size_t Vision;
public:
    GameGreedySnake() :GameLife(true), Vision(BasicGame) {};
    void setVision(int vision) { Vision = vision; };
    void initGameWindow();
    void setGameLife(bool pos) { GameLife = pos; }
    bool GameIsOver();
    void wait_for_enter();
    void showGameOver(int score, int size, wstring name);
    void saveGameResult(int score, int size, wstring name, int selectOption);
    void handleGameOver(Food& food, Snake& snake, Menu& menu, int selectOption);
    void writeLeaderboardToFile(vector<LeaderboardEntry>& entries, const string& filename, int canshu);
    bool isFoodOut(Food& food);
    bool isAttackWall(Snake& snake, Wall& wall);
    bool isAttackSnake(Snake& snake);

    void gameLoopBASIC(Snake& test_snake, Food& test_food, Wall& test_wall, ShowInformation& test_infor);
    void updateGameDEMOBASCIK(Snake& snake, Food& food, Wall& wall, ShowInformation& information);
    bool isGameOverDEMOBASCIK(Snake& snake, Wall& wall);
    bool isNoSpace(Snake& snake, Wall& wall, Food& food);
    bool isGameOverDEMOSecond(Snake& snake, Wall& wall, Food& food);
    bool isDEAD(Snake& snake, Wall& wall);
    void updateGameDEMOSecond(Snake& snake, Food& food, Wall& wall, ShowInformation& information);
    void gameLoopSECOND(Snake& test_snake, Food& test_food, Wall& test_wall, ShowInformation& test_infor);
    bool isHaveDieTooMuch(ShowInformation& information);
    bool isGameOverDEMOADVANCE(Snake& snake, Wall& wall, Food& food, ShowInformation& information);
    void gameLoopADVANCE(Snake& test_snake, Food& test_food, Wall& test_wall, ShowInformation& test_infor);
    void updateGameDEMOADVANCE(Snake& snake, Food& food, Wall& wall, ShowInformation& information);
    void updateSingtime();
    void updateGameTime();
    void updatespeed();
    void updatedeltaTime();
    void showFPS();
    void resetpretime();
    void RestOriTime();

};
void GameGreedySnake::RestOriTime()
{
    OriFPS = 30.0; // ��ʼ֡��
    frameDelay = 4000 / OriFPS; // ��ʼÿ֡���ӳ�ʱ�䣨���룩//������ʱ��仯���仯
    steady_clock::time_point prevTime = steady_clock::now();
    steady_clock::time_point currTime = steady_clock::now();
    double gameTime = 0.0; // ������Ϸʱ������λ���룩   //����ʱ��
    double SingTime = 0.0;
    double deltaTime = 0.0;//ʱ����

}
bool GameGreedySnake::GameIsOver()
{
    if (!GameLife)
        return true;//��Ϸ������
    else
        return false;//��Ϸ���ڼ���
}
void GameGreedySnake::initGameWindow()
{
    initgraph((WIDE + WINDOW_Show_Score_SIZE) * UNIT, HIGH * UNIT, SHOWCONSOLE);           // ��ʼ����ͼ����
    setbkcolor(BASIK_COLOR);                 // ���ñ�����ɫ
    cleardevice();  // �ñ���ɫ�����Ļ
}
void  GameGreedySnake::wait_for_enter()
{
    while (true)
    {
        if (_kbhit()) {
            char c = _getch();
            if (c == 13)
                break;
            else
                continue;
        }
    }
    return;
}
void  GameGreedySnake::showGameOver(int score, int size, wstring name)
{
    setbkcolor(BLACK);                 //��������
    cleardevice();  // �ñ���ɫ�����Ļ
    LOGFONT f;
    gettextstyle(&f);						// ��ȡ��ǰ��������
    f.lfHeight = 50;						// ��������߶�
    f.lfItalic = true;
    _tcscpy_s(f.lfFaceName, _T("Old English"));		// ��������
    f.lfQuality = ANTIALIASED_QUALITY;		// �������Ч��Ϊ�����  
    f.lfWeight = 500;//�ַ���ϸ
    settextstyle(&f);
    settextcolor(WHITE);

    TCHAR UsersNameText[100];
    _stprintf_s(UsersNameText, _T("���: %s"), name.c_str());
    outtextxy((WIDE + WINDOW_Show_Score_SIZE) * UNIT / 3, HIGH * UNIT / 3 - 4 * UNIT, UsersNameText);  // ����û�����
    TCHAR s[30];
    _stprintf_s(s, _T("��Ϸ��������ķ���Ϊ[%d]"), score); // ��ʽ���ַ���
    outtextxy((WIDE + WINDOW_Show_Score_SIZE) * UNIT / 3, HIGH * UNIT / 3, s);

    _stprintf_s(s, _T("��Ϸ��������ĳ���Ϊ[%d]"), size); // ��ʽ���ַ���
    outtextxy((WIDE + WINDOW_Show_Score_SIZE) * UNIT / 3, HIGH * UNIT / 3 + 4 * UNIT, s);

    outtextxy((WIDE + WINDOW_Show_Score_SIZE) * UNIT / 3, HIGH * UNIT / 3 + 8 * UNIT, _T("�밴�س������ز˵�"));


    wait_for_enter();
}
// ������Ϸ������ļ�
void GameGreedySnake::writeLeaderboardToFile(vector<LeaderboardEntry>& entries, const string& filename, int canshu) {
    // Read existing data from file
    //entries�Ǹ��º�����������ǻ�û������

    //��ʼ��entries����
    // Sort allVision1Entries by score
    if (canshu == 1)//����Ϊ1�����������
        sort(entries.begin(), entries.end(), ScoreComparator());


    // Sort allVision1Entries by length
    if (canshu == 2)//����Ϊ2�����������
        sort(entries.begin(), entries.end(), LengthComparator());


    //�������֮��д���ļ�ʹ֮���ǵ�֮ǰ������
    // Write sorted entries to file
    wofstream outputFile(filename, ios::out);//�ɹ���ʱ���ǵ�
    if (outputFile.is_open()) {
        for (size_t i = 0; i < entries.size(); ++i) {//����entries����������ÿ��Ԫ�ص�����д�뵽�ļ��С�
            outputFile << entries[i].getPlayerName() << " " << entries[i].getScore() << " " << entries[i].getLength() << endl;
        }
        outputFile.close();
        cout << "Leaderboard Score data written to file: " << filename << endl;
    }
    else {
        cout << "Error opening file: " << filename << endl;
    }
}
void GameGreedySnake::saveGameResult(int score, int size, wstring name, int selectOption) {
    // ����Ϸ�����¼���ļ���
    LeaderboardEntry entry(name, score, size);
    if (selectOption == BasicGame) {
        Vision1ScoreEntries.push_back(entry);//Ҫ����洢���а����ݵ�����
        Vision1LengthEntries.push_back(entry);//Ҫ����洢���а����ݵ�����

        //���뵽�ĵ���
           // Write updated leaderboard data to a file
        writeLeaderboardToFile(Vision1ScoreEntries, Vision1RatingofScoreTxt, scoreRating);
        //���뵽�ĵ���
        // Write updated leaderboard data to a file
        writeLeaderboardToFile(Vision1LengthEntries, Vision1RatingofLengthTxt, lengthRating);
    }
    if (selectOption == SecondGame) {
        Vision2ScoreEntries.push_back(entry);//Ҫ����洢���а����ݵ�����
        Vision2LengthEntries.push_back(entry);//Ҫ����洢���а����ݵ�����

        //���뵽�ĵ���
           // Write updated leaderboard data to a file
        writeLeaderboardToFile(Vision2ScoreEntries, Vision2RatingofScoreTxt, scoreRating);


        //���뵽�ĵ���
        // Write updated leaderboard data to a file
        writeLeaderboardToFile(Vision2LengthEntries, Vision2RatingofLengthTxt, lengthRating);
    }
    if (selectOption == AdvanceGame) {
        Vision3ScoreEntries.push_back(entry);//Ҫ����洢���а����ݵ�����
        Vision3LengthEntries.push_back(entry);//Ҫ����洢���а����ݵ�����

        //���뵽�ĵ���
           // Write updated leaderboard data to a file
        writeLeaderboardToFile(Vision3ScoreEntries, Vision3RatingofScoreTxt, scoreRating);

        //���뵽�ĵ���
        // Write updated leaderboard data to a file
        writeLeaderboardToFile(Vision3LengthEntries, Vision3RatingofLengthTxt, lengthRating);
    }

}
// ������Ϸ����
void GameGreedySnake::handleGameOver(Food& food, Snake& snake, Menu& menu, int selectOption) {
    int score = food.getscore();
    int size = snake.getsize();
    wstring name = menu.getUserName();
    // ������Ϸ������ļ�
    saveGameResult(score, size, name, selectOption);
    // ��ʾ�÷ֵ���Ϸ�����Ϣ
    showGameOver(score, size, name);
    return;
}
bool GameGreedySnake::isFoodOut(Food& food)//ָ�����ܳԵĶ��Ѿ�������//����ʳ����ٵ���һ���̶�
{
    size_t food_num = food.getFoodnum();
    vector<FoodItem> foods = food.getfoods();
    int FoodCanBeEatedNum = 0;
    int FoodCanNotBeEatedNum = 0;
    switch (Vision) {
    case BasicGame:
        for (size_t i = 0; i < food_num; i++)
            if ((foods[i].type == FoodType::Apple) || (foods[i].type == FoodType::Banana) || (foods[i].type == FoodType::TreasureChests))
                FoodCanBeEatedNum++;
        if (FoodCanBeEatedNum == 0)
            return true;
        return false;
        break;
    case SecondGame:
        for (size_t i = 0; i < food_num; i++)
        {
            if ((foods[i].type == FoodType::Apple) || (foods[i].type == FoodType::Banana) || (foods[i].type == FoodType::TreasureChests))
                FoodCanBeEatedNum++;
            else
                FoodCanNotBeEatedNum++;
        }
        if (FoodCanBeEatedNum == 0 || (FoodCanNotBeEatedNum / 2) > FoodCanBeEatedNum)
            return true;
        return false;
        break;
    case AdvanceGame:
        for (size_t i = 0; i < food_num; i++)
        {
            if ((foods[i].type == FoodType::Apple) || (foods[i].type == FoodType::Banana) || (foods[i].type == FoodType::TreasureChests))
                FoodCanBeEatedNum++;
            else
                FoodCanNotBeEatedNum++;
        }
        if (FoodCanBeEatedNum == 0 || (FoodCanNotBeEatedNum / 2) > FoodCanBeEatedNum)
            return true;
        return false;
        break;
    default:
        return true;
    }
}
bool GameGreedySnake::isAttackWall(Snake& snake, Wall& wall)
{
    pair<int, int> snake_head = snake.getHead();  //�����ͷ������
    vector<pair<int, int>> wall_points = wall.getBlocks(); //��ȡǽ������
    int length = wall.getlength();
    for (int i = 0; i < length; i++)
        if ((snake_head.first == wall_points[i].first) && (snake_head.second == wall_points[i].second))
            return true;
    return false;
}
bool GameGreedySnake::isAttackSnake(Snake& snake)
{
    pair<int, int> snake_head = snake.getHead();  //�����ͷ������
    vector<pair<int, int>> snake_body = snake.getBody(); //��ȡ�ߵ���������
    int length = snake_body.size();
    for (int i = 1; i < length; i++)
        if ((snake_head.first == snake_body[i].first) && (snake_head.second == snake_body[i].second))
            return true;

    return false;
}
/*---------------------------------------------���Ű�------------------------------------------------------*/
void GameGreedySnake::showFPS()
{
    // ��ӡ��ǰ֡�ʺ͵�����Ϸʱ��
    double fps = 1.0 / deltaTime;
    cout << "FPS: " << fps << endl;
    cout << "Game Time: " << gameTime << " seconds" << endl;
}
void GameGreedySnake::resetpretime()// ������һ֡ʱ���
{
    // ������һ֡ʱ���
    prevTime = currTime;
}
void  GameGreedySnake::updatedeltaTime()
{
    currTime = steady_clock::now();
    duration<double> elapsedTime = currTime - prevTime;
    deltaTime = elapsedTime.count();//����ʱ����
}
void GameGreedySnake::updateSingtime()
{
    SingTime += deltaTime;//������Ϸʱ��Ҳ����

}
void GameGreedySnake::updateGameTime()
{
    gameTime += deltaTime;//��Ϸʱ�����
}
void GameGreedySnake::updatespeed()
{
    if (SingTime >= SPEEDUP_INTERVAL)//�������ʱ����30s
    {
        OriFPS *= SPEEDUP_FACTOR;//֡������
        frameDelay = 4000 / OriFPS;//��Ӧ��ʱ���С
        SingTime = 0.0;//�ָ���ʼֵ
    }
}
// ���Ű��ж���Ϸ����
bool GameGreedySnake::isGameOverDEMOBASCIK(Snake& snake, Wall& wall) {
    // ��ײ���߽������
    if (isAttackSnake(snake))
        return true;
    if (isAttackWall(snake, wall))
        return true;
    if (snake.is_kill())
        return true;
    // ������Ϸģʽѡ����Ӧ���������װ�͸߼��棩
    return false;
}

//���Ű�:Ҫ����ҿ��Ʒ����������С�ߵ�ǰ��������ʹ�߳Ե���������λ���ϵ�ʳ�λ�����������Ϊ 1-5 �������
//ÿ�γɹ��Ե�ʳ���С���峤������һ�㣬�÷����ӡ�ʳ��Թ����ٴ������������С��ײ���߽������ͷ��������ײʱ���߽��ҵ�����Ϸ������
void GameGreedySnake::updateGameDEMOBASCIK(Snake& snake, Food& food, Wall& wall, ShowInformation& information) {
    // �ƶ���
    // �����ײ
    // ���ʳ��Թ�
    // �����仯
    pair<int, int> snake_head = snake.getHead();  //�����ͷ������
    vector<FoodItem> food_points = food.getfoods(); //��ȡʳ�������
    int food_num = food.getFoodnum();
    for (int i = 0; i < food_num; i++)
        if ((snake_head.first == food_points[i].position.first) && (snake_head.second == food_points[i].position.second))//����Ե�ʳ��
        {

            food.processFood(i, snake);
            snake.snakeUpdata(food, wall);

            //snake.addSnakebody(food, wall);//Ҫ�ģ��������Ͳ�ͬ����ͬ��Ч��

            if (isFoodOut(food))//Ҫ�ģ��������ֻ�ж�ҩ�˾��ٴ�����
                food.makeNewFood(snake, wall, BasicGame);
        }
    information.setscore(food.getscore());
    information.setlength(snake.getsize());
}
// ���Ű����Ϸ��ѭ��
void GameGreedySnake::gameLoopBASIC(Snake& test_snake, Food& test_food, Wall& test_wall, ShowInformation& test_infor) {

    while (!isGameOverDEMOBASCIK(test_snake, test_wall))
    {


        updatedeltaTime();

        Sleep(DWORD(frameDelay));
        BeginBatchDraw();
        cleardevice(); // ��ջ�ͼ����
        test_snake.readDirectionFromKeyboard();
        test_snake.MoveSnake();

        updateGameDEMOBASCIK(test_snake, test_food, test_wall, test_infor);

        updateGameTime();
        updateSingtime();

        updatespeed();


        test_snake.drawSnake();
        test_food.drawFood();
        test_wall.drawBlocks();
        test_infor.drawInformation();
        FlushBatchDraw();

        showFPS();

        resetpretime();// ������һ֡ʱ���

    }
}



/*----------------------------------------------------------------------------------------------------------*/

/*----------------------------------------���װ�----------------------------------------------------------*/


bool GameGreedySnake::isNoSpace(Snake& snake, Wall& wall, Food& food)
{
    int snakesize = snake.getBody().size();
    int wallsize = wall.getBlocks().size();
    int foodsize = food.getfoods().size();
    int NUMsize = snakesize + wallsize + foodsize;
    if (NUMsize >= (((WIDE * HIGH) * 7) / 10))//���Թ���û�пռ���
        return true;
    return false;
}
// ���װ��ж���Ϸ����
bool GameGreedySnake::isGameOverDEMOSecond(Snake& snake, Wall& wall, Food& food) {
    // û�пռ�������ʳ�����
    if (isNoSpace(snake, wall, food))//
        return true;
    return false;
}

bool GameGreedySnake::isDEAD(Snake& snake, Wall& wall) {
    // ���ײ����ǽ
    if (isAttackSnake(snake))//
        return true;
    if (isAttackWall(snake, wall))
        return true;
    if (snake.is_kill())
        return true;

    return false;
}

//���װ�:�߹ҵ��󣬴�ʱ��ʬ��ı���ʾ��ɫ��ɱ߽磬����������µ�ʳ����ߣ���Ϸ������ֱ��ʣ��ռ䲻���������µ��ߺ�ʳ��Ϊֹ��
void GameGreedySnake::updateGameDEMOSecond(Snake& snake, Food& food, Wall& wall, ShowInformation& information) {
    // �ƶ���
    // �����ײ
    // ���ʳ��Թ�
    // �����仯
    pair<int, int> snake_head = snake.getHead();  //�����ͷ������
    vector<FoodItem> food_points = food.getfoods(); //��ȡʳ�������
    int food_num = food.getFoodnum();
    for (int i = 0; i < food_num; i++)//���Ƿ�Ե�ʳ�����ѭ��
        if ((snake_head.first == food_points[i].position.first) && (snake_head.second == food_points[i].position.second))//����Ե�ʳ��
        {
            food.processFood(i, snake);
            snake.snakeUpdata(food, wall);
            if (isFoodOut(food))
                food.makeNewFood(snake, wall, SecondGame);
        }
    information.setscore(food.getscore());
    information.setlength(snake.getsize());
    if (isDEAD(snake, wall))//��������ǽ
    {//�ߵĳ�����գ�Ȼ���������������
        //ԭ����������ǽ
        //�ٴ���������µ�ʳ��
        vector<pair<int, int> >snake_Body = snake.getBody(); //��������������
        for (size_t g = 0; g < snake_Body.size(); g++)
            wall.addBlock(snake_Body[g].first, snake_Body[g].second);//��ֵ��ǽ

        //�����µ�ʳ��
        food.deleteFood();
        food.makeNewFood(snake, wall, SecondGame);

        snake.resetkill();
        snake.deleteSnake();//���
        snake.REcreateSnake(food, wall);//�ҵط��ٴ�����һ����
    }
    information.setscore(food.getscore());
    information.setlength(snake.getsize());
}
// ���װ����Ϸ��ѭ��
void GameGreedySnake::gameLoopSECOND(Snake& test_snake, Food& test_food, Wall& test_wall, ShowInformation& test_infor) {

    while (!isGameOverDEMOSecond(test_snake, test_wall, test_food))
    {
        updatedeltaTime();

        Sleep(DWORD(frameDelay));
        BeginBatchDraw();
        cleardevice(); // ��ջ�ͼ����
        test_snake.readDirectionFromKeyboard();
        test_snake.MoveSnake();

        updateGameDEMOSecond(test_snake, test_food, test_wall, test_infor);


        updateGameTime();
        updateSingtime();
        updatespeed();

        test_snake.drawSnake();
        test_food.drawFood();
        test_wall.drawBlocks();
        test_infor.drawInformation();
        FlushBatchDraw();
        showFPS();

        resetpretime();// ������һ֡ʱ���


    }
}

/*----------------------------------------------------------------------------------------------------------*/

/*----------------------------------�߼���----------------------------------------------------------------*/


/*�߼��棺�߹ҵ��󣬴�ʱ��ʬ��ı���ʾ��ɫ���ʳ�����������µ�ʳ����ߣ���Ϸ������ֱ��ײǽ����>5����ʣ��ռ䲻���������µ��ߺ�ʳ��Ϊֹ��*/


bool GameGreedySnake::isHaveDieTooMuch(ShowInformation& information)
{
    if (information.getLifeNum() > 0)
        return false;
    else
        return true;
}
bool GameGreedySnake::isGameOverDEMOADVANCE(Snake& snake, Wall& wall, Food& food, ShowInformation& information) {
    // û�пռ�������ʳ�����
    if (isNoSpace(snake, wall, food))//
        return true;
    //�����������  DIEMAXNUM
    if (isHaveDieTooMuch(information))
        return true;
    return false;
}
//�߼������Ϸ����
void GameGreedySnake::updateGameDEMOADVANCE(Snake& snake, Food& food, Wall& wall, ShowInformation& information) {

    pair<int, int> snake_head = snake.getHead();  //�����ͷ������
    vector<FoodItem> food_points = food.getfoods(); //��ȡʳ�������
    int food_num = food.getFoodnum();
    for (int i = 0; i < food_num; i++)//���Ƿ�Ե�ʳ�����ѭ��
        if ((snake_head.first == food_points[i].position.first) && (snake_head.second == food_points[i].position.second))//����Ե�ʳ��
        {
            food.processFood(i, snake);
            snake.snakeUpdata(food, wall);
            if (isFoodOut(food))
                food.makeNewFood(snake, wall, AdvanceGame);
        }
    information.setscore(food.getscore());
    information.setlength(snake.getsize());
    if (isDEAD(snake, wall))//���������
    {//�ߵĳ�����գ�Ȼ���������������
        //ԭ����������ʳ��
        vector<pair<int, int> >snake_Body = snake.getBody(); //��������������

        //ʳ�����
        food.deleteFood();
        //�����µ�ʳ��
        food.makeNewFood(snake, wall, AdvanceGame);


        //����Ҳ���ʳ��
        //����ͷ��ǽ����ԳԲ���ͷ�����Դ�һ��ʼ��ʳ��
        for (size_t g = 1; g < snake_Body.size(); g++)
            food.setNEWPosition(snake_Body[g].first, snake_Body[g].second, FoodType(g % FOODTYPE + 1));//��ֵ��ʳ��


        food.showfoods();
        snake.resetkill();
        snake.deleteSnake();//���
        snake.REcreateSnake(food, wall);//�ҵط��ٴ�����һ����
        information.negaLifeNum();
        //waitfor3();

    }
    //information.setscore(food.getscore());
    //information.setlength(snake.getsize());
}
// �߼������Ϸ��ѭ��
void GameGreedySnake::gameLoopADVANCE(Snake& test_snake, Food& test_food, Wall& test_wall, ShowInformation& test_infor) {

    while (!isGameOverDEMOADVANCE(test_snake, test_wall, test_food, test_infor))
    {
        updatedeltaTime();

        Sleep(DWORD(frameDelay));

        BeginBatchDraw();
        cleardevice(); // ��ջ�ͼ����
        test_snake.readDirectionFromKeyboard();
        test_snake.MoveSnake();

        updateGameDEMOADVANCE(test_snake, test_food, test_wall, test_infor);

        updateGameTime();
        updateSingtime();
        updatespeed();

        test_snake.drawSnake();
        test_food.drawFood();
        test_wall.drawBlocks();
        test_infor.drawInformation();
        FlushBatchDraw();

        showFPS();

        resetpretime();// ������һ֡ʱ���
    }
}

/*----------------------------------------------------------------------------------------------------------*/
void readFileToEntries(vector<LeaderboardEntry>& entries, const string& filename)
{
    wifstream inputFile(filename);

    if (inputFile.is_open()) {
        wstring name;
        int score, length;
        while (inputFile >> name >> score >> length) {//ѭ����ȡԭ�����ļ�
            LeaderboardEntry entry(name, score, length);
            entries.push_back(entry);
        }
        inputFile.close();
    }
}


void makeMusic()
{
    wchar_t command[256];
    wsprintf(command, L"open \"%s\" type mpegvideo alias myaudio", audioFile);
    mciSendString(command, NULL, 0, NULL);

    mciSendString(L"play myaudio", NULL, 0, NULL);
    mciSendString(L"play myaudio repeat", NULL, 0, NULL); //�ظ�����
}
void stopMusic()
{
    mciSendString(L"stop myaudio", NULL, 0, NULL);
    mciSendString(L"close myaudio", NULL, 0, NULL);
}

int main()
{
    //����ʼ����ȡԭ�������а�
    readFileToEntries(Vision1ScoreEntries, Vision1RatingofScoreTxt);//�汾1�������а�
    readFileToEntries(Vision1LengthEntries, Vision1RatingofLengthTxt);//�汾1�������а�

    readFileToEntries(Vision2ScoreEntries, Vision2RatingofScoreTxt);//�汾2�������а�
    readFileToEntries(Vision2LengthEntries, Vision2RatingofLengthTxt);//�汾2�������а�

    readFileToEntries(Vision3ScoreEntries, Vision3RatingofScoreTxt);//�汾3�������а�
    readFileToEntries(Vision3LengthEntries, Vision3RatingofLengthTxt);//�汾3�������а�


    Menu test_menu;
    GameGreedySnake test_game;
    test_menu.displayMenu();
    test_game.setGameLife((test_menu.getLifeFlag()));
    while (!test_game.GameIsOver()) {

        int selectedOption = test_menu.getSelectedOption();
        cout << "Selected Option: " << selectedOption << endl;

        wstring userName = test_menu.getUserName();

        if (selectedOption >= BasicGame && selectedOption <= AdvanceGame) {
            makeMusic();
            test_game.RestOriTime();
            test_game.initGameWindow();
            Wall test_wall;
            Snake test_snake;
            ShowInformation test_infor(selectedOption);
            test_snake.drawSnake();
            test_wall.drawBlocks();
            test_infor.setUsersName(userName);
            test_infor.drawInformation();
            test_infor.drawGameLife();

            if (selectedOption == BasicGame)
            {
                Food test_food(BasicGame);
                test_food.drawFood();
                test_game.setVision(BasicGame);
                test_game.gameLoopBASIC(test_snake, test_food, test_wall, test_infor);
                EndBatchDraw();
                test_game.handleGameOver(test_food, test_snake, test_menu, selectedOption);//������Ϸ����
                closegraph();                            // �رջ�ͼ����
            }
            if (selectedOption == SecondGame)
            {
                Food test_food(SecondGame);
                test_food.drawFood();
                test_game.setVision(SecondGame);
                test_game.gameLoopSECOND(test_snake, test_food, test_wall, test_infor);
                EndBatchDraw();
                test_game.handleGameOver(test_food, test_snake, test_menu, selectedOption);//������Ϸ����
                closegraph();                            // �رջ�ͼ����
            }
            if (selectedOption == AdvanceGame)
            {
                Food test_food(AdvanceGame);
                test_food.drawFood();
                test_game.setVision(AdvanceGame);
                test_game.gameLoopADVANCE(test_snake, test_food, test_wall, test_infor);
                EndBatchDraw();
                test_game.handleGameOver(test_food, test_snake, test_menu, selectedOption);//������Ϸ����
                closegraph();                            // �رջ�ͼ����
            }
        }

        stopMusic();
        prevTime = steady_clock::now();
        test_menu.resetMenu();
        test_menu.displayMenu();
        test_game.setGameLife((test_menu.getLifeFlag()));
    }
    cout << "��Ϸ���������ڴ���һ�����԰汾" << endl;
    cout << "��ǰȱ���ߵ����⼼�ܡ���Ӳǽ����ͣ���̵ȹ���" << endl;
    return 0;
}

