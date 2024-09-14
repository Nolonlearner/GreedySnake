#include <iostream>
#include <conio.h>
#include <vector>
#include <string>
#include <fstream>
#include <queue>//用于优先队列
#include <ctime>
#include <chrono>
#include <graphics.h>  //easyX函数库的头文件
#include <mmsystem.h> // 包含mmsystem.h头文件
#pragma comment(lib,"WINMM.LIB")

/*-------------------------游戏像素、界面、帧率等基本要素-------------------------*/


#define UNIT            15                                //一个方块对应的像素大小
#define HIGH            35                               //游戏界面的高度
#define WIDE            45                               //游戏界面的宽度
#define BasicGame       1
#define SecondGame      2
#define AdvanceGame     3
#define Rating          4
#define SetName         5
#define Withdraw        6
/*--------------------------------------------------------------------------------*/


/*--------------------------游戏模式初始化的相关参数------------------------------*/
#define SNAKEBASICBODY   1                               //蛇的初始长度
#define FOODNUM          5                               //食物数量的最大值
#define FOODTYPE         5                               //食物类型的最大值
#define LifeMAXNUM       5                               //生命次数

/*--------------------------------------------------------------------------------*/


/*--------------------------信息展示的窗口相关参数--------------------------------*/

#define WINDOW_Show_Score_SIZE        20                               //显示分数的窗口
#define CHAR_INFOR_SIZE               500                              //字体的粗细
#define CHAR_INFOR_HIGH               20                               //字体的高度//最好为方块的整数倍
#define CHAR_INFOR_COLOR              RGB(134,144,138)                     //字体的颜色
#define BASIK_COLOR                   RGB(234,220,214)                        //基础幕布的颜色
#define SHOWBASIK_COLOR               RGB(237,241,187)                       //基础信息幕布的颜色
#define SHOWBASIKFRAME_COLOR          RGB(255,200,222)                        //基础边框幕布的颜色
#define PIC                           30

/*--------------------------------------------------------------------------------*/


/*-------------------------------蛇、食物、墙的颜色---------------------------------------*/
#define SnakeBody_COLOR       RGB(239,130,160)                        //蛇身的颜色
#define SnakeHead_COLOR       RGB(167,83,90)                          //蛇头的颜色
#define WALL_COLOR            RGB(128,109,158)                        //墙的颜色
#define BLUEPOSION_COLOR      RGB(81,196,211)                         //蓝色毒药的颜色
#define PURPLEPOSION_COLOR    RGB(65,28,53)                           //紫色毒药的颜色
#define APPLE_COLOR           RGB(237,90,101)                         //苹果的颜色
#define BANANA_COLOR          RGB(249,180,0)                          //香蕉的颜色
#define TREASURECHEST_COLOR   RGB(110,139,116)                        //宝箱的颜色
//#define BASIK_COLOR           RGB(251,242,227)                        //基础幕布的颜色


/*--------------------------------------------------------------------------------*/

/*-------------------------------菜单界面-----------------------------------------*/

#define  MenuColor          RGB(95,71,154)//紫罗兰//
#define  MenuBKColor        RGB(229,223,213)//珍珠灰




/*--------------------------------------------------------------------------------*/

/*-------------------------------排行榜界面-----------------------------------------*/
#define scoreRating             1
#define lengthRating            2
#define MaxRatingNumShow        3
#define RatingShowBeginX        70
#define RatingShowBeginY        200
#define RatingShowBeginHigh     50
#define CharRtingHeight         30
#define CHAR_Rating_SIZE         300
#define CHAR_Rating_COLOR  RGB(227,111,113)//海棠红
#define CHAR_Rating_BKCOLOR  RGB(255,196,187)//粉红
#define CHAR_HoverCOLOR  RGB(250,199,183)//十祥锦
#define CHAR_HoverBKCOLOR  RGB(93,79,87)//烟墨色

#define CHAR_Rule_SIZE  300
#define CHAR_Rule_High  20
#define CHAR_Rule_BeginX  20
#define CHAR_Rule_BeginY  50
#define CHAR_Rule_COLOR  RGB(164,171,214)//暮山紫

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
double OriFPS = 30.0; // 初始帧率
const double SPEEDUP_INTERVAL = 15; // 加速间隔（秒）
const double SPEEDUP_FACTOR = 1.1; // 加速因子
const double SPEEDDOWN_FACTOR = 0.9; // 减速因子
double frameDelay = CANSHU / OriFPS; // 初始每帧的延迟时间（毫秒）//会随着时间变化而变化
steady_clock::time_point prevTime = steady_clock::now();
steady_clock::time_point currTime = steady_clock::now();
double gameTime = 0.0; // 单局游戏时长（单位：秒）   //设置时间
double SingTime = 0.0;
double deltaTime = 0.0;//时间间隔

const wchar_t* audioFile = L"TEST.mp3"; // 音频文件路径

// 定义游戏对象类

//声明类
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


//排行榜
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
        return entry1.getScore() > entry2.getScore(); //从大到小排序
    }
};
struct LengthComparator {
    bool operator()(const LeaderboardEntry& entry1, const LeaderboardEntry& entry2) {
        return entry1.getLength() > entry2.getLength(); //从大到小排序
    }
};

//排行榜要实时更新所以作为作为全局变量
//版本1的排行榜
vector<LeaderboardEntry> Vision1ScoreEntries;
vector<LeaderboardEntry> Vision1LengthEntries;
//版本2的排行榜
vector<LeaderboardEntry> Vision2ScoreEntries;
vector<LeaderboardEntry> Vision2LengthEntries;
//版本3的排行榜
vector<LeaderboardEntry> Vision3ScoreEntries;
vector<LeaderboardEntry> Vision3LengthEntries;

//菜单类
class Menu {
private:
    bool flag;
    bool LifeFlag;
    int selectedOption;
    wstring userName;
    bool isinputtingUsername;
    wstring inputtedUsername;  // 输入的用户名
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
    void ShowRankingOptions();//建立排行榜窗口
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
    gettextstyle(&f);						// 获取当前字体设置
    f.lfHeight = CHAR_Rule_High;						// 设置字体高度
    f.lfItalic = true;
    _tcscpy_s(f.lfFaceName, _T("隶书"));		// 设置字体
    f.lfQuality = ANTIALIASED_QUALITY;		// 设置输出效果为抗锯齿  
    f.lfWeight = CHAR_Rule_SIZE;//字符粗细
    settextstyle(&f);
    settextcolor(CHAR_Rule_COLOR);
    wstring rule1 = L"入门版的规则：要求玩家控制方向键来控制小蛇的前进方向，以使蛇吃掉面板上随机位置上的食物（位置随机，数量为 1-5 随机）。每次成功吃掉食物后小蛇体长将增加一点，得分增加。食物吃光则再次随机产生。当小蛇撞到边界或者蛇头与蛇身相撞时，蛇将挂掉，游戏结束。";
    int row = 0;
    size_t lineLength = 15;  // 每行的字符数

    size_t remainingChars1 = rule1.size();  // 剩余的字符数

    for (size_t i = 0; remainingChars1 > 0; i += lineLength) {
        TCHAR Ruletext[30];
        wstring line = rule1.substr(i, min(lineLength, remainingChars1));
        _stprintf_s(Ruletext, _T("%s"), line.c_str());
        outtextxy(CHAR_Rule_BeginX, CHAR_Rule_BeginY + row * CHAR_Rule_High - 40, Ruletext);
        row++;
        remainingChars1 -= line.length();
    }

    row++;
    wstring rule2 = L"进阶版的规则：蛇挂掉后，此时蛇尸身改变显示颜色变成边界，再随机产生新的食物和蛇，游戏继续。直到剩余空间不足以生成新的蛇和食物为止。";

    size_t remainingChars2 = rule2.size();  // 剩余的字符数

    for (size_t i = 0; remainingChars2 > 0; i += lineLength) {
        TCHAR Ruletext[30];
        wstring line = rule2.substr(i, min(lineLength, remainingChars2));
        _stprintf_s(Ruletext, _T("%s"), line.c_str());
        outtextxy(CHAR_Rule_BeginX, CHAR_Rule_BeginY + row * CHAR_Rule_High - 40, Ruletext);
        row++;

        remainingChars2 -= line.length();
    }

    row++;
    wstring rule3 = L"高级版的规则为：蛇挂掉后，此时蛇尸身改变显示颜色变成食物，再随机产生新的食物和蛇，游戏继续。直到撞墙次数>5，或剩余空间不足以生成新的蛇和食物为止。";

    size_t remainingChars3 = rule3.size();  // 剩余的字符数

    for (size_t i = 0; remainingChars3 > 0; i += lineLength) {
        TCHAR Ruletext[30];
        wstring line = rule3.substr(i, min(lineLength, remainingChars3));
        _stprintf_s(Ruletext, _T("%s"), line.c_str());
        outtextxy(CHAR_Rule_BeginX, CHAR_Rule_BeginY + row * CHAR_Rule_High - 40, Ruletext);
        row++;

        remainingChars3 -= line.length();
    }
    row++;
    wstring rule4 = L"更多的游戏细节请查看文档里面的README.TXT，欢迎大家交流和讨论";

    size_t remainingChars4 = rule4.size();  // 剩余的字符数

    for (size_t i = 0; remainingChars4 > 0; i += lineLength) {
        TCHAR Ruletext[30];
        wstring line = rule4.substr(i, min(lineLength, remainingChars4));
        _stprintf_s(Ruletext, _T("%s"), line.c_str());
        outtextxy(CHAR_Rule_BeginX, CHAR_Rule_BeginY + row * CHAR_Rule_High - 40, Ruletext);
        row++;

        remainingChars4 -= line.length();
    }
    cout << "打印规则" << endl;
}
void Menu::displayRatingDecision()
{
    settextstyle(40, 0, _T("隶书"));
    settextcolor(MenuColor);
    setbkcolor(MenuBKColor);

    outtextxy(RatingShowBeginX + 30, RatingShowBeginY, _T("入门版"));
    outtextxy(RatingShowBeginX + 30, RatingShowBeginY + RatingShowBeginHigh, _T("进阶版"));
    outtextxy(RatingShowBeginX + 30, RatingShowBeginY + RatingShowBeginHigh * 2, _T("高级版"));
}
void Menu::displayMenuDecision()
{
    // 绘制菜单选项
    settextstyle(40, 0, _T("隶书"));

    settextcolor(MenuColor);
    setbkcolor(MenuBKColor);

    outtextxy(350, 50, _T("Nolon Greedy Snake"));

    outtextxy(400, 100, _T("By Nolon"));

    TCHAR name[100];
    _stprintf_s(name, _T("[用户名:%s]"), userName.c_str());
    outtextxy(350, 150, name);


    outtextxy(350, 200, _T("基础版"));
    outtextxy(350, 250, _T("进阶版"));
    outtextxy(350, 300, _T("高级版"));
    outtextxy(350, 350, _T("排行榜"));
    outtextxy(350, 400, _T("输入用户名"));
    outtextxy(350, 450, _T("退出游戏"));
    // 贪吃蛇图片的路径

    // 加载贪吃蛇图片
    IMAGE img1;
    IMAGE img2;
    loadimage(&img1, _T("snake.png"));
    loadimage(&img2, _T("LogoSnake.jpg"));

    // 在画布上显示贪吃蛇图片
    putimage(555, 200, &img1);
    putimage(585, 100, &img2);
}
void Menu::displayMenu() {
    initgraph(800, 600, SHOWCONSOLE);  // 初始化窗口
    settextstyle(40, 0, _T("隶书"));
    settextcolor(MenuColor);
    setbkcolor(MenuBKColor);

    cleardevice();  // 清空窗口

    // 绘制菜单选项
    displayMenuDecision();
    drawRule();

    while (flag) {
        //TCHAR s[20];         // EasyX设置文字需要的字符串变量类型
        if (MouseHit()) {
            MOUSEMSG m = GetMouseMsg();  // 获取鼠标信息
            switch (m.uMsg) {
            case WM_LBUTTONDOWN:
                // 左键按下，根据鼠标位置判断选择的菜单项
                if (ischeckRating)
                    handleRankingMouseClick(m.x, m.y);//处理点击排行榜的情况
                else
                    handleMouseClick(m.x, m.y);
                break;
            case WM_LBUTTONDBLCLK://WM_RBUTTONDOWN右键
                // 左键双击退出循环
                flag = false;
                break;
            case WM_MOUSEMOVE:
                // 鼠标移动，在窗口左上角显示当前坐标
                //setfillcolor(BLACK);                  // 黑色矩形覆盖上次坐标记录
                //solidrectangle(0, 0, 75, 20);
                //_stprintf_s(s, _T("[%d,%d]"), m.x, m.y); // 格式化字符串
                //outtextxy(0, 0, s);

                // 处理鼠标悬停效果
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
            if (isinputtingUsername)//此时可以输入用户名
            {
                InputNameInWindows(key);//输入用户名
            }
            else {//此时判断是不是退出
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
        ischeckRating = true;  // 进入查看排行榜的状态
        flag = true;
    }
    else if (y >= 400 && y < 450 && x >= 350 && x < 550) {
        // 弹出输入框，获取用户名
        selectedOption = SetName;
        isinputtingUsername = true;  // 进入输入用户名状态
        flag = true;
        Creat_InputYourName_Windows();//建立输入窗口
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
    cout << "点击" << RatingClickOption << endl;
    if (RatingClickOption >= BasicGame && RatingClickOption <= AdvanceGame)
        ShowRatingList();
}
void Menu::handleMouseHover(int x, int y) {

    // 绘制菜单选项
    displayMenuDecision();

    // 鼠标悬停效果
    settextstyle(40, 0, _T("隶书"));
    settextcolor(CHAR_HoverCOLOR);
    setbkcolor(CHAR_HoverBKCOLOR);

    if (y >= 200 && y < 250 && x >= 350 && x < 450) {
        outtextxy(350, 200, _T("基础版"));
    }
    else if (y >= 250 && y < 300 && x >= 350 && x < 450) {
        outtextxy(350, 250, _T("进阶版"));
    }
    else if (y >= 300 && y < 350 && x >= 350 && x < 450) {
        outtextxy(350, 300, _T("高级版"));
    }
    else if (y >= 350 && y < 400 && x >= 350 && x < 450) {
        outtextxy(350, 350, _T("排行榜"));
    }
    else if (y >= 400 && y < 450 && x >= 350 && x < 550) {
        outtextxy(350, 400, _T("输入用户名"));
    }
    else if (y >= 450 && y < 500 && x >= 350 && x < 450) {
        outtextxy(350, 450, _T("退出游戏"));
    }
}
void Menu::handleRankingMouseHover(int x, int y) {
    // 鼠标悬停效果
    displayRatingDecision();
    settextstyle(40, 0, _T("隶书"));
    settextcolor(CHAR_HoverCOLOR);
    setbkcolor(CHAR_HoverBKCOLOR);
    if (y >= 200 && y < 250 && x >= 100 && x < 200) {
        outtextxy(100, 200, _T("入门版"));
    }
    else if (y >= 250 && y < 300 && x >= 100 && x < 200) {
        outtextxy(100, 250, _T("进阶版"));
    }
    else if (y >= 300 && y < 350 && x >= 100 && x < 200) {
        outtextxy(100, 300, _T("高级版"));
    }
}
void Menu::handleKeyPress(char key) {
    if (key == 27) {
        selectedOption = Withdraw;  // ESC键对应退出游戏
        flag = false;
        LifeFlag = false;
    }
}
void Menu::setUserName(const wstring& name) {
    userName = name;
}
void Menu::Creat_InputYourName_Windows()
{
    // 用户点击了"输入用户名"选项之后
    // 
    // 清空输入用户名的选项框
    setfillcolor(MenuBKColor);
    solidrectangle(350, 400, 800, 450);

    // 显示输入框
    settextstyle(40, 0, _T("隶书"));
    settextcolor(WHITE);
    setbkcolor(LIGHTGRAY);
    outtextxy(350, 400, _T("请输入用户名: "));
    //然后开始输入用户名
}
void Menu::ShowRankingOptions()
{
    settextstyle(40, 0, _T("隶书"));
    settextcolor(WHITE);
    setbkcolor(BLACK);

    outtextxy(RatingShowBeginX, RatingShowBeginY, _T("版本一"));
    outtextxy(RatingShowBeginX, RatingShowBeginY + 1 * RatingShowBeginHigh, _T("版本二"));
    outtextxy(RatingShowBeginX, RatingShowBeginY + 2 * RatingShowBeginHigh, _T("版本三"));
}
void Menu::InputNameInWindows(char key)
{
    if (key == '\r')
    {
        // 如果输入的是回车键，则结束输入用户名
        // 清空输入框
        Delete_InputYourName_Windows();
    }
    else if (key == '\b')
    {
        // 退格键，删除最后一个字符
        if (!inputtedUsername.empty()) {
            inputtedUsername.pop_back();

            // 清空输入框
            setfillcolor(MenuBKColor);
            solidrectangle(350, 400, 800, 450);

            // 显示输入的用户名,更新
            settextstyle(40, 0, _T("隶书"));
            settextcolor(WHITE);
            setbkcolor(LIGHTGRAY);
            TCHAR name[100];
            _stprintf_s(name, _T("[用户名:%s]"), inputtedUsername.c_str());
            outtextxy(350, 400, name);
        }
    }
    else
    {//添加字符
        // 输入字符添加到用户名字符串末尾
        inputtedUsername.push_back(key);

        // 显示输入的用户名
        settextstyle(40, 0, _T("隶书"));
        settextcolor(WHITE);
        setbkcolor(LIGHTGRAY);
        TCHAR name[100];
        _stprintf_s(name, _T("[用户名:%s]"), inputtedUsername.c_str());
        outtextxy(350, 400, name);
    }
}
void Menu::Delete_InputYourName_Windows()
{
    // 结束输入用户名状态
    isinputtingUsername = false;
    userName = inputtedUsername;
    // 清空输入框
    setfillcolor(MenuBKColor);;
    solidrectangle(350, 400, 800, 450);
    displayMenuDecision();//更新界面
    drawRule();

}
void Menu::showRatinglistBasic()
{
    // 清空排行榜的选项框
    setfillcolor(CHAR_Rating_BKCOLOR);
    solidrectangle(RatingShowBeginX, RatingShowBeginY - 2 * RatingShowBeginHigh, RatingShowBeginX + 5 * RatingShowBeginHigh, RatingShowBeginY + 6 * RatingShowBeginHigh);

    LOGFONT f;
    gettextstyle(&f);						// 获取当前字体设置
    f.lfHeight = CharRtingHeight;						// 设置字体高度
    f.lfItalic = false;
    _tcscpy_s(f.lfFaceName, _T("Old English"));		// 设置字体
    f.lfQuality = ANTIALIASED_QUALITY;		// 设置输出效果为抗锯齿  
    f.lfWeight = CHAR_Rating_SIZE;//字符粗细
    settextstyle(&f);
    settextcolor(CHAR_Rating_COLOR);

    setbkcolor(CHAR_Rating_BKCOLOR);

    outtextxy(RatingShowBeginX, RatingShowBeginY - RatingShowBeginHigh, _T("Rating of Score"));
    for (size_t i = 0; (i < MaxRatingNumShow) && (i < Vision1ScoreEntries.size()); i++)
    {
        cout << "输出" << endl;
        TCHAR RatingText[100];
        _stprintf_s(RatingText, _T("%d. %s %d"), (i + 1), Vision1ScoreEntries[i].getPlayerName().c_str(), Vision1ScoreEntries[i].getScore());
        outtextxy(RatingShowBeginX, RatingShowBeginY - RatingShowBeginHigh + CharRtingHeight * (i + 1), RatingText);
    }

    outtextxy(RatingShowBeginX, RatingShowBeginY + CharRtingHeight * (MaxRatingNumShow + 1), _T("Rating of Length"));
    for (size_t i = 0; (i < MaxRatingNumShow) && (i < Vision1LengthEntries.size()); i++)
    {
        cout << "输出" << endl;
        TCHAR RatingText[100];
        _stprintf_s(RatingText, _T("%d. %s %d"), (i + 1), Vision1LengthEntries[i].getPlayerName().c_str(), Vision1LengthEntries[i].getLength());
        outtextxy(RatingShowBeginX, RatingShowBeginY + CharRtingHeight * (MaxRatingNumShow + 1) + CharRtingHeight * (i + 1), RatingText);
    }
}
void Menu::showRatinglistAdvance()
{
    // 清空排行榜的选项框
    setfillcolor(CHAR_Rating_BKCOLOR);
    solidrectangle(RatingShowBeginX, RatingShowBeginY - 2 * RatingShowBeginHigh, RatingShowBeginX + 5 * RatingShowBeginHigh, RatingShowBeginY + 6 * RatingShowBeginHigh);

    LOGFONT f;
    gettextstyle(&f);						// 获取当前字体设置
    f.lfHeight = CharRtingHeight;						// 设置字体高度
    f.lfItalic = false;
    _tcscpy_s(f.lfFaceName, _T("Old English"));		// 设置字体
    f.lfQuality = ANTIALIASED_QUALITY;		// 设置输出效果为抗锯齿  
    f.lfWeight = CHAR_Rating_SIZE;//字符粗细
    settextstyle(&f);
    settextcolor(CHAR_Rating_COLOR);

    setbkcolor(CHAR_Rating_BKCOLOR);

    outtextxy(RatingShowBeginX, RatingShowBeginY - RatingShowBeginHigh, _T("Rating of Score"));
    for (size_t i = 0; (i < MaxRatingNumShow) && (i < Vision3ScoreEntries.size()); i++)
    {
        cout << "输出" << endl;
        TCHAR RatingText[100];
        _stprintf_s(RatingText, _T("%d. %s %d"), (i + 1), Vision3ScoreEntries[i].getPlayerName().c_str(), Vision3ScoreEntries[i].getScore());
        outtextxy(RatingShowBeginX, RatingShowBeginY - RatingShowBeginHigh + CharRtingHeight * (i + 1), RatingText);
    }

    outtextxy(RatingShowBeginX, RatingShowBeginY + CharRtingHeight * (MaxRatingNumShow + 1), _T("Rating of Length"));
    for (size_t i = 0; (i < MaxRatingNumShow) && (i < Vision3LengthEntries.size()); i++)
    {
        cout << "输出" << endl;
        TCHAR RatingText[100];
        _stprintf_s(RatingText, _T("%d. %s %d"), (i + 1), Vision3LengthEntries[i].getPlayerName().c_str(), Vision3LengthEntries[i].getLength());
        outtextxy(RatingShowBeginX, RatingShowBeginY + CharRtingHeight * (MaxRatingNumShow + 1) + CharRtingHeight * (i + 1), RatingText);
    }
}
void Menu::showRatinglistSecond()
{
    // 清空排行榜的选项框
    setfillcolor(CHAR_Rating_BKCOLOR);
    solidrectangle(RatingShowBeginX, RatingShowBeginY - 2 * RatingShowBeginHigh, RatingShowBeginX + 5 * RatingShowBeginHigh, RatingShowBeginY + 6 * RatingShowBeginHigh);

    LOGFONT f;
    gettextstyle(&f);						// 获取当前字体设置
    f.lfHeight = CharRtingHeight;						// 设置字体高度
    f.lfItalic = false;
    _tcscpy_s(f.lfFaceName, _T("Old English"));		// 设置字体
    f.lfQuality = ANTIALIASED_QUALITY;		// 设置输出效果为抗锯齿  
    f.lfWeight = CHAR_Rating_SIZE;//字符粗细
    settextstyle(&f);
    settextcolor(CHAR_Rating_COLOR);
    setbkcolor(CHAR_Rating_BKCOLOR);
    outtextxy(RatingShowBeginX, RatingShowBeginY - RatingShowBeginHigh, _T("Rating of Score"));
    for (size_t i = 0; (i < MaxRatingNumShow) && (i < Vision2ScoreEntries.size()); i++)
    {
        cout << "输出" << endl;
        TCHAR RatingText[100];
        _stprintf_s(RatingText, _T("%d. %s %d"), (i + 1), Vision2ScoreEntries[i].getPlayerName().c_str(), Vision2ScoreEntries[i].getScore());
        outtextxy(RatingShowBeginX, RatingShowBeginY - RatingShowBeginHigh + CharRtingHeight * (i + 1), RatingText);
    }

    outtextxy(RatingShowBeginX, RatingShowBeginY + CharRtingHeight * (MaxRatingNumShow + 1), _T("Rating of Length"));
    for (size_t i = 0; (i < MaxRatingNumShow) && (i < Vision2LengthEntries.size()); i++)
    {
        cout << "输出" << endl;
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
    // 绘制返回键的图标
    settextstyle(CharRtingHeight, 0, _T("隶书"));
    settextcolor(CHAR_Rating_COLOR);
    setbkcolor(CHAR_Rating_BKCOLOR);
    outtextxy(RatingShowBeginX, RatingShowBeginY - 3 * CharRtingHeight, _T("返回"));
}
void Menu::CheckClickReturn()
{
    while (ischeckRating) {
        if (MouseHit()) {
            MOUSEMSG m = GetMouseMsg();  // 获取鼠标信息
            switch (m.uMsg) {
            case WM_LBUTTONDOWN:
                if (ischeckRating)
                    handleMouseClickBackButton(m.x, m.y);//处理点击返回键的情况
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
        // 处理返回键的点击事件
        cout << "点击了返回" << endl;
        handleBackButton();
    }
}
void Menu::handleRankingMouseBackButtonHover(int x, int y)
{
    // 鼠标悬停效果
    drawBackButton();
    settextstyle(CharRtingHeight, 0, _T("隶书"));
    settextcolor(CHAR_HoverCOLOR);
    setbkcolor(CHAR_HoverBKCOLOR);
    if (y >= RatingShowBeginY - 3 * CharRtingHeight && y < RatingShowBeginY && x >= RatingShowBeginX && x < RatingShowBeginX + 2 * CharRtingHeight) {
        outtextxy(RatingShowBeginX, RatingShowBeginY - 3 * CharRtingHeight, _T("返回"));
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
//窗口类
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
    //展现出你的当前生命值
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
    //当前分数
    gettextstyle(&f);						// 获取当前字体设置
    f.lfHeight = CHAR_INFOR_HIGH * 3 / 2;						// 设置字体高度
    f.lfItalic = true;
    f.lfUnderline = false;//下划线
    f.lfQuality = ANTIALIASED_QUALITY;		// 设置输出效果为抗锯齿  
    f.lfWeight = CHAR_INFOR_SIZE;//字符粗细
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
    gettextstyle(&f);						// 获取当前字体设置
    f.lfHeight = CHAR_INFOR_HIGH * 2;						// 设置字体高度
    f.lfItalic = false;
    f.lfUnderline = false;//下划线
    f.lfQuality = ANTIALIASED_QUALITY;		// 设置输出效果为抗锯齿  
    f.lfWeight = CHAR_INFOR_SIZE + 100;//字符粗细
    settextstyle(&f);
    settextcolor(CHAR_INFOR_COLOR);
    setbkcolor(SHOWBASIK_COLOR);
    outtextxy(BeginX, BeginY + 4 * CHAR_INFOR_HIGH + CHAR_INFOR_HIGH / 2, _T("LIFE:     ×"));
    settextcolor(RGB(243, 59, 31));
    setbkcolor(SHOWBASIK_COLOR);

    IMAGE img;
    loadimage(&img, _T("Life.png"));
    // 在画布上显示爱心图片
    putimage(BeginX + CHAR_INFOR_HIGH * 4 + CHAR_INFOR_HIGH / 2, BeginY + 4 * CHAR_INFOR_HIGH + CHAR_INFOR_HIGH * 7 / 10, &img);

    TCHAR GamelifeText[50];
    _stprintf_s(GamelifeText, _T("%d"), LifeNum);
    outtextxy(BeginX + CHAR_INFOR_HIGH * 8, BeginY + 4 * CHAR_INFOR_HIGH + CHAR_INFOR_HIGH / 2, GamelifeText);  // 输出用户名字

}
void ShowInformation::settext() {
    LOGFONT f;
    gettextstyle(&f);						// 获取当前字体设置
    f.lfHeight = CHAR_INFOR_HIGH * 2;						// 设置字体高度
    f.lfItalic = true;
    _tcscpy_s(f.lfFaceName, _T("Gill Sans Ultra Bold"));		// 设置字体
    f.lfQuality = ANTIALIASED_QUALITY;		// 设置输出效果为抗锯齿  
    f.lfWeight = CHAR_INFOR_SIZE;//字符粗细
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
    //食物的文字介绍
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

    // 在画布上显示apple图片
    putimage(BeginX, BeginY + 14 * CHAR_INFOR_HIGH + CHAR_INFOR_HIGH / 2, &imgApple);;
    putimage(BeginX, BeginY + 14 * CHAR_INFOR_HIGH + CHAR_INFOR_HIGH / 2 + PIC * 5 / 4, &imgBanana);
    putimage(BeginX, BeginY + 14 * CHAR_INFOR_HIGH + CHAR_INFOR_HIGH / 2 + PIC * 5 / 4 * 2, &imgTreasureChest);
    putimage(BeginX, BeginY + 14 * CHAR_INFOR_HIGH + CHAR_INFOR_HIGH / 2 + PIC * 5 / 4 * 3, &imgBluePosion);
    putimage(BeginX, BeginY + 14 * CHAR_INFOR_HIGH + CHAR_INFOR_HIGH / 2 + PIC * 5 / 4 * 4, &imgPurplePosion);


    gettextstyle(&f);						// 获取当前字体设置
    f.lfHeight = CHAR_INFOR_HIGH * 6 / 5;						// 设置字体高度
    f.lfItalic = true;
    f.lfUnderline = false;//下划线
    f.lfQuality = ANTIALIASED_QUALITY;		// 设置输出效果为抗锯齿  
    f.lfWeight = CHAR_INFOR_SIZE / 2;//字符粗细
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
    //历史最高分
    LOGFONT f;
    gettextstyle(&f);						// 获取当前字体设置
    f.lfHeight = CHAR_INFOR_HIGH * 2;						// 设置字体高度
    f.lfItalic = false;
    f.lfUnderline = true;//下划线
    f.lfQuality = ANTIALIASED_QUALITY;		// 设置输出效果为抗锯齿  
    f.lfWeight = CHAR_INFOR_SIZE;//字符粗细
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
    gettextstyle(&f);						// 获取当前字体设置
    f.lfHeight = CHAR_INFOR_HIGH * 2;						// 设置字体高度
    f.lfItalic = false;
    f.lfUnderline = true;//下划线
    f.lfQuality = ANTIALIASED_QUALITY;		// 设置输出效果为抗锯齿  
    f.lfWeight = CHAR_INFOR_SIZE;//字符粗细
    settextstyle(&f);
    settextcolor(CHAR_INFOR_COLOR);
    setbkcolor(SHOWBASIK_COLOR);
    TCHAR TIME[100];
    _stprintf_s(TIME, _T(" %s"), to_wstring(static_cast<int>(round(gameTime))).c_str());
    outtextxy(BeginX + CHAR_INFOR_HIGH * 5, BeginY + 10 * CHAR_INFOR_HIGH + CHAR_INFOR_HIGH / 5, TIME);  // 时间

}
void ShowInformation::drawVision()
{
    LOGFONT f;
    gettextstyle(&f);						// 获取当前字体设置
    _tcscpy_s(f.lfFaceName, _T("Gill Sans Ultra Bold"));		// 设置字体
    f.lfUnderline = false;//下划线
    //当前模式
    f.lfHeight = CHAR_INFOR_HIGH * 2;						// 设置字体高度
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
    // 设置边框颜色和填充颜色
    setcolor(SHOWBASIKFRAME_COLOR);          // 
    setfillcolor(SHOWBASIK_COLOR);   //
    // 绘制矩形边框
    roundrect(WIDE * UNIT, UNIT, (WIDE + WINDOW_Show_Score_SIZE - 1) * UNIT, (HIGH - 1) * UNIT, UNIT * 4, UNIT * 4);
    // 填充矩形
    floodfill((WIDE + WINDOW_Show_Score_SIZE / 2) * UNIT, HIGH * UNIT / 2, SHOWBASIKFRAME_COLOR);//边框
}
void ShowInformation::drawusersName()
{
    LOGFONT f;
    gettextstyle(&f);						// 获取当前字体设置
    f.lfHeight = CHAR_INFOR_HIGH + 5;						// 设置字体高度
    settextstyle(&f);
    outtextxy(BeginX, BeginY + 3 * CHAR_INFOR_HIGH, _T("Player:"));

    settextcolor(CHAR_INFOR_COLOR);
    setbkcolor(WHITE);
    //outtextxy(BeginX + 4 * CHAR_INFOR_HIGH, BeginY + 3 * CHAR_INFOR_HIGH, _T("XXXXXXXXXXX"));
    TCHAR UsersNameText[100];
    _stprintf_s(UsersNameText, _T(" %s"), Usersname.c_str());
    outtextxy(BeginX + 4 * CHAR_INFOR_HIGH, BeginY + 3 * CHAR_INFOR_HIGH, UsersNameText);  // 输出用户名字
}
// 墙类
class Wall {
private:
    int length;
    vector<pair<int, int>> blocks;   // 墙块列表
public:
    //窗口大小为HIGH * UNIT, WIDE * UNIT
    //窗口的大小便决定了墙的位置
    //按照从原点开始，顺时针的顺序初始化
    Wall() {
        for (int i = 1; i <= WIDE; i++)
        {
            blocks.push_back(make_pair(i - 1, 0));
        }
        blocks.pop_back();//删去最后一个
        for (int i = 1; i <= HIGH; i++)
        {
            blocks.push_back(make_pair(WIDE - 1, i - 1));
        }
        blocks.pop_back();//删去最后一个
        for (int i = WIDE; i >= 1; i--)
        {
            blocks.push_back(make_pair(i - 1, HIGH - 1));
        }
        blocks.pop_back();//删去最后一个
        for (int i = HIGH; i >= 1; i--)
        {
            blocks.push_back(make_pair(0, i - 1));
        }
        blocks.pop_back();//删去最后一个

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
    // 添加墙块
    void addBlock(int posX, int posY) {
        blocks.push_back(make_pair(posX, posY));
        length++;
    }

    // 获取墙块列表
    vector<pair<int, int>> getBlocks() const {
        return blocks;
    }

    int getlength()const {
        return length;
    }
};
// 食物类
enum class FoodType {
    Apple = 1,          // 苹果，长度加1，分数加1
    Banana = 2,         // 香蕉，长度加2，分数加2
    PurplePoison = 3,   // 紫色毒药，直接挂掉
    BluePoison = 4,     // 蓝色毒药，长度-2，分数-5
    TreasureChests = 5, // 宝箱
};
struct FoodItem {
public:
    pair<int, int> position;  // 食物的位置坐标
    FoodType type;            // 食物类型
    FoodItem()
    {
        type = FoodType::Apple;
    }
};
class Food {
private:
    size_t Food_num;              // 食物的数量
    size_t score;
    vector<FoodItem> foods;    // 食物列表
public:


    // 构造函数

    Food(int Vision)//:type(FoodType::Apple)  // 默认食物类型为苹果
    {
        srand((unsigned)time(NULL));
        Food_num = rand() % FOODNUM + 1 + (Vision - 1) * FOODNUM;
        score = 0;
        createFood();
    }

    void createFood();
    void createFood(Snake& snake, Wall& wall);
    // 获取食物的位置
    vector<FoodItem> getfoods() const { return foods; };

    // 获取食物的数量
    int  getFoodnum() const {
        return Food_num;
    }
    int  getscore() const {
        return score;
    }
    //删除容器中指定位置的食物
    void deleteFood(int pos)//, Snake& snake)
    {
        foods.erase(foods.begin() + pos);
        Food_num = foods.size();
    }

    // 设置新出现的食物的位置
    void setNEWPosition(int posX, int posY, FoodType foodType)
    {
        FoodItem newFood;
        newFood.position = make_pair(posX, posY);
        newFood.type = foodType;
        foods.push_back(newFood);
        Food_num = foods.size();
    }
    void makeNewFood(Snake& snake, Wall& wall, int vision);
    //画出食物
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
            cout << "WARNNING!!!出现了不同颜色的食物" << endl;
            Sleep(5000);
            return BLACK;
            break;
        }
    }
    //清空食物
    void deleteFood()
    {
        foods.clear();
        Food_num = 0;
    }
    FoodType generateRandomFoodType()//产生随机类型
    {
        int random = rand() % 30 + 1; // 生成1到30之间的随机数
        if (random == 1) {
            return FoodType::TreasureChests; // 生成Treasure食物类型//treasure的概率为1/30
        }
        else {
            // 根据其他概率生成其他类型的食物
            int foodType = rand() % (FOODTYPE - 1) + 1; // 生成1到FOODTYPE-1之间的随机数
            return static_cast<FoodType>(foodType);
        }
    }

    void showfoods()
    {
        cout << "食物总数为" << Food_num << endl;
        cout << "容器大小为" << foods.size() << endl;
        for (size_t i = 0; i < foods.size(); i++)
        {
            cout << "当前坐标为:" << foods[i].position.first << " "
                << foods[i].position.second << " 当前种类为:" << int(foods[i].type) << endl;
        }
    }

    // 处理吃到食物的逻辑
    void processFood(int pos, Snake& snake);


};


// 蛇类
class Snake {
public:
    // 蛇的方向
    enum class Direction {
        UP = 1,
        DOWN = 2,
        LEFT = 3,
        RIGHT = 4
    };

    // 构造函数
    //蛇生成在中间
    Snake(int initialSize = SNAKEBASICBODY, int startX = WIDE / 2, int startY = HIGH / 2, Direction initialDirection = Direction::RIGHT)
        : size(initialSize), direction(initialDirection) {//initialSize:初始长度  ,(startX,startY):初始坐标
        // 初始化蛇的身体                                 //initialDirection :初始方向
        for (size_t i = 0; i < size; ++i) {
            body.push_back(make_pair(startX, startY + i));
        }
    }
    // 获取蛇的身体坐标
    vector<pair<int, int>> getBody() const {
        return body;
    }

    // 获取蛇头坐标
    pair<int, int> getHead() const {
        return body.front();
    }

    // 获取蛇的方向
    Direction getDirection() const {
        return direction;
    }
    int getsize()const { ; return size; }
    // 设置蛇的方向
    void setDirection(Direction newDirection) {
        direction = newDirection;
    }
    //画出蛇
    void drawSnake();
    // 移动蛇的身体
    // 从键盘读取方向
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
    void deleteSnake() { body.clear(); };//删除蛇
    void returnBasicLength() { size = SNAKEBASICBODY; }//恢复初始长度
    void REcreateSnake(Food& food, Wall& wall);//再次生成蛇
    void setSnakeBodyIncrease(int change) { SnakeBodyIncrease = change; }
    void setSnakeBodyDecrease(int change) { SnakeBodyDecrease = change; }
    void snakeUpdata(Food& food, Wall& wall);
private:
    size_t SnakeBodyIncrease = 0;
    size_t SnakeBodyDecrease = 0;
    bool iskill = false;
    size_t size;                                // 蛇的长度
    Direction direction;                     // 蛇的方向
    vector<pair<int, int>> body;   // 蛇的身体坐标   body为一个数组，存储的是有序数对，用first和second访问x和y坐标
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
    pair<int, int> head = getHead();  //获得蛇头的坐标
    switch (direction) {
    case Direction::RIGHT:
        body.insert(body.begin(), make_pair(head.first + 1, head.second));//产生新的蛇头
        break;
    case Direction::LEFT:
        body.insert(body.begin(), make_pair(head.first - 1, head.second));//产生新的蛇头
        break;
    case Direction::UP:
        body.insert(body.begin(), make_pair(head.first, head.second - 1));//产生新的蛇头
        break;
    case Direction::DOWN:
        body.insert(body.begin(), make_pair(head.first, head.second + 1));//产生新的蛇头
        break;
    }
    // 如果蛇的长度超过当前大小，则删除尾部，以此来保持长度不变
    if (body.size() > size) {
        body.pop_back();
    }
}
void Snake::readDirectionFromKeyboard() {
    if (_kbhit()) {//只能键盘，判断是不是在键盘上输入了
        char ch = _getch();  // 从键盘读取字符
        switch (ch) {
        case 'w':
        case 'W':
            if (direction != Direction::DOWN) {
                setDirection(Snake::Direction::UP);//设置方向为UP
            }
            break;
        case 's':
        case 'S':
            if (direction != Direction::UP) {
                setDirection(Snake::Direction::DOWN);//设置方向为DOWN
            }
            break;
        case 'a':
        case 'A':
            if (direction != Direction::RIGHT) {
                setDirection(Snake::Direction::LEFT);//设置方向为LEFT
            }
            break;
        case 'd':
        case 'D':
            if (direction != Direction::LEFT) {
                setDirection(Snake::Direction::RIGHT);//设置方向为RIGHT
            }
            break;
        default:
            // 处理其他情况，例如无效输入
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
                body.pop_back();//删除最后一个元素
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
{//清空之后再此生成蛇

    returnBasicLength();//恢复初始长度

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
        if (p) {//该点是有空间的
            body.push_back(make_pair(x, y));
            break;//跳出循环
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


// 处理吃到食物的逻辑
void Food::processFood(int pos, Snake& snake) {
    switch (foods[pos].type) {
    case FoodType::Apple:
        deleteFood(pos);//删除一个地方的食物
        snake.setSnakeBodyIncrease(1);//蛇要增加的长度为1
        score += 1;
        break;
    case FoodType::Banana:
        deleteFood(pos);//删除一个地方的食物
        snake.setSnakeBodyIncrease(2);//蛇的变化
        score += 2;
        break;
    case FoodType::PurplePoison:
        deleteFood(pos);//删除一个地方的食物
        snake.kill(); // 处理玩家挂掉的逻辑
        score /= 3;
        break;
    case FoodType::TreasureChests:
        deleteFood(pos);//删除一个地方的食物
        snake.setSnakeBodyIncrease(3);
        OriFPS *= (SPEEDDOWN_FACTOR * SPEEDDOWN_FACTOR);//时间变慢
        frameDelay = CANSHU / OriFPS;
        score *= 2;//得分×2
        break;
    case FoodType::BluePoison:
        deleteFood(pos);//删除一个地方的食物
        snake.setSnakeBodyDecrease(2);//减少2个单位
        score -= 10;//得分减去10
        break;
    default:
        break;
    }
}
void Food::createFood()//生成的第一次，重载
{
    // 生成食物的位置和类型，并添加到食物列表中
    srand((unsigned)time(NULL));
    for (size_t i = 0; i < Food_num; ) {

        int x = rand() % WIDE;
        int y = rand() % HIGH;
        if ((x == 0 || x == WIDE - 1) || (y == 0 || y == HIGH - 1))//不能在边界
            continue;
        else
        {
            FoodItem food;
            if (i == 0)
                food.type = FoodType::Apple;//至少出现一个可以吃的食物
            else
                food.type = generateRandomFoodType();//储存类型
            food.position = make_pair(x, y);//储存坐标
            foods.push_back(food);
            i++;
        }
    }
}
void Food::createFood(Snake& snake, Wall& wall)//不能出现在墙内和蛇身体内,重载//对于高级版本，可以生成个更多的食物而不是一到五个
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
                food.type = generateRandomFoodType();//储存类型
            food.position = make_pair(x, y);//储存坐标
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
    OriFPS = 30.0; // 初始帧率
    frameDelay = 4000 / OriFPS; // 初始每帧的延迟时间（毫秒）//会随着时间变化而变化
    steady_clock::time_point prevTime = steady_clock::now();
    steady_clock::time_point currTime = steady_clock::now();
    double gameTime = 0.0; // 单局游戏时长（单位：秒）   //设置时间
    double SingTime = 0.0;
    double deltaTime = 0.0;//时间间隔

}
bool GameGreedySnake::GameIsOver()
{
    if (!GameLife)
        return true;//游戏结束了
    else
        return false;//游戏仍在继续
}
void GameGreedySnake::initGameWindow()
{
    initgraph((WIDE + WINDOW_Show_Score_SIZE) * UNIT, HIGH * UNIT, SHOWCONSOLE);           // 初始化绘图窗口
    setbkcolor(BASIK_COLOR);                 // 设置背景颜色
    cleardevice();  // 用背景色清空屏幕
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
    setbkcolor(BLACK);                 //结束界面
    cleardevice();  // 用背景色清空屏幕
    LOGFONT f;
    gettextstyle(&f);						// 获取当前字体设置
    f.lfHeight = 50;						// 设置字体高度
    f.lfItalic = true;
    _tcscpy_s(f.lfFaceName, _T("Old English"));		// 设置字体
    f.lfQuality = ANTIALIASED_QUALITY;		// 设置输出效果为抗锯齿  
    f.lfWeight = 500;//字符粗细
    settextstyle(&f);
    settextcolor(WHITE);

    TCHAR UsersNameText[100];
    _stprintf_s(UsersNameText, _T("玩家: %s"), name.c_str());
    outtextxy((WIDE + WINDOW_Show_Score_SIZE) * UNIT / 3, HIGH * UNIT / 3 - 4 * UNIT, UsersNameText);  // 输出用户名字
    TCHAR s[30];
    _stprintf_s(s, _T("游戏结束，你的分数为[%d]"), score); // 格式化字符串
    outtextxy((WIDE + WINDOW_Show_Score_SIZE) * UNIT / 3, HIGH * UNIT / 3, s);

    _stprintf_s(s, _T("游戏结束，你的长度为[%d]"), size); // 格式化字符串
    outtextxy((WIDE + WINDOW_Show_Score_SIZE) * UNIT / 3, HIGH * UNIT / 3 + 4 * UNIT, s);

    outtextxy((WIDE + WINDOW_Show_Score_SIZE) * UNIT / 3, HIGH * UNIT / 3 + 8 * UNIT, _T("请按回车键返回菜单"));


    wait_for_enter();
}
// 保存游戏结果到文件
void GameGreedySnake::writeLeaderboardToFile(vector<LeaderboardEntry>& entries, const string& filename, int canshu) {
    // Read existing data from file
    //entries是更新后的名单，但是还没有排序

    //开始给entries排序
    // Sort allVision1Entries by score
    if (canshu == 1)//参数为1则给长度排序
        sort(entries.begin(), entries.end(), ScoreComparator());


    // Sort allVision1Entries by length
    if (canshu == 2)//参数为2则给长度排序
        sort(entries.begin(), entries.end(), LengthComparator());


    //排序完成之后写入文件使之覆盖掉之前的排名
    // Write sorted entries to file
    wofstream outputFile(filename, ios::out);//成功打开时覆盖掉
    if (outputFile.is_open()) {
        for (size_t i = 0; i < entries.size(); ++i) {//遍历entries容器，并将每个元素的数据写入到文件中。
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
    // 将游戏结果记录在文件中
    LeaderboardEntry entry(name, score, size);
    if (selectOption == BasicGame) {
        Vision1ScoreEntries.push_back(entry);//要存入存储排行榜数据的名单
        Vision1LengthEntries.push_back(entry);//要存入存储排行榜数据的名单

        //存入到文档中
           // Write updated leaderboard data to a file
        writeLeaderboardToFile(Vision1ScoreEntries, Vision1RatingofScoreTxt, scoreRating);
        //存入到文档中
        // Write updated leaderboard data to a file
        writeLeaderboardToFile(Vision1LengthEntries, Vision1RatingofLengthTxt, lengthRating);
    }
    if (selectOption == SecondGame) {
        Vision2ScoreEntries.push_back(entry);//要存入存储排行榜数据的名单
        Vision2LengthEntries.push_back(entry);//要存入存储排行榜数据的名单

        //存入到文档中
           // Write updated leaderboard data to a file
        writeLeaderboardToFile(Vision2ScoreEntries, Vision2RatingofScoreTxt, scoreRating);


        //存入到文档中
        // Write updated leaderboard data to a file
        writeLeaderboardToFile(Vision2LengthEntries, Vision2RatingofLengthTxt, lengthRating);
    }
    if (selectOption == AdvanceGame) {
        Vision3ScoreEntries.push_back(entry);//要存入存储排行榜数据的名单
        Vision3LengthEntries.push_back(entry);//要存入存储排行榜数据的名单

        //存入到文档中
           // Write updated leaderboard data to a file
        writeLeaderboardToFile(Vision3ScoreEntries, Vision3RatingofScoreTxt, scoreRating);

        //存入到文档中
        // Write updated leaderboard data to a file
        writeLeaderboardToFile(Vision3LengthEntries, Vision3RatingofLengthTxt, lengthRating);
    }

}
// 处理游戏结束
void GameGreedySnake::handleGameOver(Food& food, Snake& snake, Menu& menu, int selectOption) {
    int score = food.getscore();
    int size = snake.getsize();
    wstring name = menu.getUserName();
    // 保存游戏结果到文件
    saveGameResult(score, size, name, selectOption);
    // 显示得分等游戏结果信息
    showGameOver(score, size, name);
    return;
}
bool GameGreedySnake::isFoodOut(Food& food)//指的是能吃的都已经吃完了//或者食物变少到了一定程度
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
    pair<int, int> snake_head = snake.getHead();  //获得蛇头的坐标
    vector<pair<int, int>> wall_points = wall.getBlocks(); //获取墙的坐标
    int length = wall.getlength();
    for (int i = 0; i < length; i++)
        if ((snake_head.first == wall_points[i].first) && (snake_head.second == wall_points[i].second))
            return true;
    return false;
}
bool GameGreedySnake::isAttackSnake(Snake& snake)
{
    pair<int, int> snake_head = snake.getHead();  //获得蛇头的坐标
    vector<pair<int, int>> snake_body = snake.getBody(); //获取蛇的身体坐标
    int length = snake_body.size();
    for (int i = 1; i < length; i++)
        if ((snake_head.first == snake_body[i].first) && (snake_head.second == snake_body[i].second))
            return true;

    return false;
}
/*---------------------------------------------入门版------------------------------------------------------*/
void GameGreedySnake::showFPS()
{
    // 打印当前帧率和单局游戏时长
    double fps = 1.0 / deltaTime;
    cout << "FPS: " << fps << endl;
    cout << "Game Time: " << gameTime << " seconds" << endl;
}
void GameGreedySnake::resetpretime()// 更新上一帧时间戳
{
    // 更新上一帧时间戳
    prevTime = currTime;
}
void  GameGreedySnake::updatedeltaTime()
{
    currTime = steady_clock::now();
    duration<double> elapsedTime = currTime - prevTime;
    deltaTime = elapsedTime.count();//更新时间间隔
}
void GameGreedySnake::updateSingtime()
{
    SingTime += deltaTime;//单次游戏时间也更新

}
void GameGreedySnake::updateGameTime()
{
    gameTime += deltaTime;//游戏时间更新
}
void GameGreedySnake::updatespeed()
{
    if (SingTime >= SPEEDUP_INTERVAL)//如果大于时间间隔30s
    {
        OriFPS *= SPEEDUP_FACTOR;//帧率增加
        frameDelay = 4000 / OriFPS;//对应的时间变小
        SingTime = 0.0;//恢复初始值
    }
}
// 入门版判断游戏结束
bool GameGreedySnake::isGameOverDEMOBASCIK(Snake& snake, Wall& wall) {
    // 蛇撞到边界或自身
    if (isAttackSnake(snake))
        return true;
    if (isAttackWall(snake, wall))
        return true;
    if (snake.is_kill())
        return true;
    // 根据游戏模式选择相应操作（进阶版和高级版）
    return false;
}

//入门版:要求玩家控制方向键来控制小蛇的前进方向，以使蛇吃掉面板上随机位置上的食物（位置随机，数量为 1-5 随机）。
//每次成功吃掉食物后小蛇体长将增加一点，得分增加。食物吃光则再次随机产生。当小蛇撞到边界或者蛇头与蛇身相撞时，蛇将挂掉，游戏结束。
void GameGreedySnake::updateGameDEMOBASCIK(Snake& snake, Food& food, Wall& wall, ShowInformation& information) {
    // 移动蛇
    // 检测碰撞
    // 检测食物吃光
    // 分数变化
    pair<int, int> snake_head = snake.getHead();  //获得蛇头的坐标
    vector<FoodItem> food_points = food.getfoods(); //获取食物的坐标
    int food_num = food.getFoodnum();
    for (int i = 0; i < food_num; i++)
        if ((snake_head.first == food_points[i].position.first) && (snake_head.second == food_points[i].position.second))//如果吃到食物
        {

            food.processFood(i, snake);
            snake.snakeUpdata(food, wall);

            //snake.addSnakebody(food, wall);//要改，根据类型不同处理不同的效果

            if (isFoodOut(food))//要改，如果类型只有毒药了就再次生成
                food.makeNewFood(snake, wall, BasicGame);
        }
    information.setscore(food.getscore());
    information.setlength(snake.getsize());
}
// 入门版的游戏主循环
void GameGreedySnake::gameLoopBASIC(Snake& test_snake, Food& test_food, Wall& test_wall, ShowInformation& test_infor) {

    while (!isGameOverDEMOBASCIK(test_snake, test_wall))
    {


        updatedeltaTime();

        Sleep(DWORD(frameDelay));
        BeginBatchDraw();
        cleardevice(); // 清空绘图窗口
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

        resetpretime();// 更新上一帧时间戳

    }
}



/*----------------------------------------------------------------------------------------------------------*/

/*----------------------------------------进阶版----------------------------------------------------------*/


bool GameGreedySnake::isNoSpace(Snake& snake, Wall& wall, Food& food)
{
    int snakesize = snake.getBody().size();
    int wallsize = wall.getBlocks().size();
    int foodsize = food.getfoods().size();
    int NUMsize = snakesize + wallsize + foodsize;
    if (NUMsize >= (((WIDE * HIGH) * 7) / 10))//粗略估计没有空间了
        return true;
    return false;
}
// 进阶版判断游戏结束
bool GameGreedySnake::isGameOverDEMOSecond(Snake& snake, Wall& wall, Food& food) {
    // 没有空间再生成食物和蛇
    if (isNoSpace(snake, wall, food))//
        return true;
    return false;
}

bool GameGreedySnake::isDEAD(Snake& snake, Wall& wall) {
    // 如果撞到了墙
    if (isAttackSnake(snake))//
        return true;
    if (isAttackWall(snake, wall))
        return true;
    if (snake.is_kill())
        return true;

    return false;
}

//进阶版:蛇挂掉后，此时蛇尸身改变显示颜色变成边界，再随机产生新的食物和蛇，游戏继续。直到剩余空间不足以生成新的蛇和食物为止。
void GameGreedySnake::updateGameDEMOSecond(Snake& snake, Food& food, Wall& wall, ShowInformation& information) {
    // 移动蛇
    // 检测碰撞
    // 检测食物吃光
    // 分数变化
    pair<int, int> snake_head = snake.getHead();  //获得蛇头的坐标
    vector<FoodItem> food_points = food.getfoods(); //获取食物的坐标
    int food_num = food.getFoodnum();
    for (int i = 0; i < food_num; i++)//对是否吃到食物进行循环
        if ((snake_head.first == food_points[i].position.first) && (snake_head.second == food_points[i].position.second))//如果吃到食物
        {
            food.processFood(i, snake);
            snake.snakeUpdata(food, wall);
            if (isFoodOut(food))
                food.makeNewFood(snake, wall, SecondGame);
        }
    information.setscore(food.getscore());
    information.setlength(snake.getsize());
    if (isDEAD(snake, wall))//如果变成了墙
    {//蛇的长度清空，然后再随机处产生蛇
        //原来的肉身变成墙
        //再次随机产生新的食物
        vector<pair<int, int> >snake_Body = snake.getBody(); //获得蛇身体的坐标
        for (size_t g = 0; g < snake_Body.size(); g++)
            wall.addBlock(snake_Body[g].first, snake_Body[g].second);//赋值给墙

        //产生新的食物
        food.deleteFood();
        food.makeNewFood(snake, wall, SecondGame);

        snake.resetkill();
        snake.deleteSnake();//清空
        snake.REcreateSnake(food, wall);//找地方再次生成一条蛇
    }
    information.setscore(food.getscore());
    information.setlength(snake.getsize());
}
// 进阶版的游戏主循环
void GameGreedySnake::gameLoopSECOND(Snake& test_snake, Food& test_food, Wall& test_wall, ShowInformation& test_infor) {

    while (!isGameOverDEMOSecond(test_snake, test_wall, test_food))
    {
        updatedeltaTime();

        Sleep(DWORD(frameDelay));
        BeginBatchDraw();
        cleardevice(); // 清空绘图窗口
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

        resetpretime();// 更新上一帧时间戳


    }
}

/*----------------------------------------------------------------------------------------------------------*/

/*----------------------------------高级版----------------------------------------------------------------*/


/*高级版：蛇挂掉后，此时蛇尸身改变显示颜色变成食物，再随机产生新的食物和蛇，游戏继续。直到撞墙次数>5，或剩余空间不足以生成新的蛇和食物为止。*/


bool GameGreedySnake::isHaveDieTooMuch(ShowInformation& information)
{
    if (information.getLifeNum() > 0)
        return false;
    else
        return true;
}
bool GameGreedySnake::isGameOverDEMOADVANCE(Snake& snake, Wall& wall, Food& food, ShowInformation& information) {
    // 没有空间再生成食物和蛇
    if (isNoSpace(snake, wall, food))//
        return true;
    //死亡超过五次  DIEMAXNUM
    if (isHaveDieTooMuch(information))
        return true;
    return false;
}
//高级版的游戏更新
void GameGreedySnake::updateGameDEMOADVANCE(Snake& snake, Food& food, Wall& wall, ShowInformation& information) {

    pair<int, int> snake_head = snake.getHead();  //获得蛇头的坐标
    vector<FoodItem> food_points = food.getfoods(); //获取食物的坐标
    int food_num = food.getFoodnum();
    for (int i = 0; i < food_num; i++)//对是否吃到食物进行循环
        if ((snake_head.first == food_points[i].position.first) && (snake_head.second == food_points[i].position.second))//如果吃到食物
        {
            food.processFood(i, snake);
            snake.snakeUpdata(food, wall);
            if (isFoodOut(food))
                food.makeNewFood(snake, wall, AdvanceGame);
        }
    information.setscore(food.getscore());
    information.setlength(snake.getsize());
    if (isDEAD(snake, wall))//如果死掉了
    {//蛇的长度清空，然后再随机处产生蛇
        //原来的肉身变成食物
        vector<pair<int, int> >snake_Body = snake.getBody(); //获得蛇身体的坐标

        //食物清空
        food.deleteFood();
        //生成新的食物
        food.makeNewFood(snake, wall, AdvanceGame);


        //肉身也变成食物
        //由于头在墙里，所以吃不到头，所以从一开始给食物
        for (size_t g = 1; g < snake_Body.size(); g++)
            food.setNEWPosition(snake_Body[g].first, snake_Body[g].second, FoodType(g % FOODTYPE + 1));//赋值给食物


        food.showfoods();
        snake.resetkill();
        snake.deleteSnake();//清空
        snake.REcreateSnake(food, wall);//找地方再次生成一条蛇
        information.negaLifeNum();
        //waitfor3();

    }
    //information.setscore(food.getscore());
    //information.setlength(snake.getsize());
}
// 高级版的游戏主循环
void GameGreedySnake::gameLoopADVANCE(Snake& test_snake, Food& test_food, Wall& test_wall, ShowInformation& test_infor) {

    while (!isGameOverDEMOADVANCE(test_snake, test_wall, test_food, test_infor))
    {
        updatedeltaTime();

        Sleep(DWORD(frameDelay));

        BeginBatchDraw();
        cleardevice(); // 清空绘图窗口
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

        resetpretime();// 更新上一帧时间戳
    }
}

/*----------------------------------------------------------------------------------------------------------*/
void readFileToEntries(vector<LeaderboardEntry>& entries, const string& filename)
{
    wifstream inputFile(filename);

    if (inputFile.is_open()) {
        wstring name;
        int score, length;
        while (inputFile >> name >> score >> length) {//循环读取原来的文件
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
    mciSendString(L"play myaudio repeat", NULL, 0, NULL); //重复播放
}
void stopMusic()
{
    mciSendString(L"stop myaudio", NULL, 0, NULL);
    mciSendString(L"close myaudio", NULL, 0, NULL);
}

int main()
{
    //程序开始，读取原来的排行榜
    readFileToEntries(Vision1ScoreEntries, Vision1RatingofScoreTxt);//版本1分数排行榜
    readFileToEntries(Vision1LengthEntries, Vision1RatingofLengthTxt);//版本1长度排行榜

    readFileToEntries(Vision2ScoreEntries, Vision2RatingofScoreTxt);//版本2分数排行榜
    readFileToEntries(Vision2LengthEntries, Vision2RatingofLengthTxt);//版本2长度排行榜

    readFileToEntries(Vision3ScoreEntries, Vision3RatingofScoreTxt);//版本3分数排行榜
    readFileToEntries(Vision3LengthEntries, Vision3RatingofLengthTxt);//版本3长度排行榜


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
                test_game.handleGameOver(test_food, test_snake, test_menu, selectedOption);//单次游戏结束
                closegraph();                            // 关闭绘图窗口
            }
            if (selectedOption == SecondGame)
            {
                Food test_food(SecondGame);
                test_food.drawFood();
                test_game.setVision(SecondGame);
                test_game.gameLoopSECOND(test_snake, test_food, test_wall, test_infor);
                EndBatchDraw();
                test_game.handleGameOver(test_food, test_snake, test_menu, selectedOption);//单次游戏结束
                closegraph();                            // 关闭绘图窗口
            }
            if (selectedOption == AdvanceGame)
            {
                Food test_food(AdvanceGame);
                test_food.drawFood();
                test_game.setVision(AdvanceGame);
                test_game.gameLoopADVANCE(test_snake, test_food, test_wall, test_infor);
                EndBatchDraw();
                test_game.handleGameOver(test_food, test_snake, test_menu, selectedOption);//单次游戏结束
                closegraph();                            // 关闭绘图窗口
            }
        }

        stopMusic();
        prevTime = steady_clock::now();
        test_menu.resetMenu();
        test_menu.displayMenu();
        test_game.setGameLife((test_menu.getLifeFlag()));
    }
    cout << "游戏结束力，期待下一个测试版本" << endl;
    cout << "当前缺少蛇的特殊技能、软硬墙、暂停键盘等功能" << endl;
    return 0;
}

