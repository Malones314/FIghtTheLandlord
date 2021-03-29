#include<bits/stdc++.h>
#include<windows.h>
#include"people.h"
using namespace std;
string kindsOfCard[38] = { "None", "1.单张", "2.对子", "3.三张", "4.双飞机", "5.三飞机", "6.四飞机", "7.五飞机", "8.六飞机",
                                        "9.三带一", "10.三带二", "11.双飞带两张", "12.双飞双带", "13.三飞带三张", "14.三飞三带",
                                        "15.四飞带四张", "16.四飞四带", "17.四带二", "18.四带两对", "19.连对（3对）",
                                        "20.连对（4对）", "21.连对（5对）", "22.连对（6对）", "23.连对（7对）", "24.连对（8对）",
                                        "25.连对（9对）", "26.连对（10对）", "27.顺子（5张）", "28.顺子（6张）", "29.顺子（7张）",
                                        "30.顺子（8张）","31.顺子（9张）", "32.顺子（10张）", "33.顺子（11张）", "34.顺子（12张）",
                                        "35.炸弹", "36.王炸", "37.要不起"};   //下标从1开始
void getCards( int [16], int [21]);   //得到牌, 地主手动加三张牌
void firstShow();   //初始界面
bool game( int [], int [], int [], int, int []);   //打牌, 返回地主输赢( 1赢0输)
void kind();   //展示出牌类型
string computerPuts( int card[21], string put, int* cardsKind, int* lastPut, int computer);   //返回电脑选择的出牌, 更改出牌类型, 更改上一次出牌者
string putCardsAtWill( int card[21], int* cardsKind);   //电脑任意出牌, 返回出的牌, 更改出牌类型
void changeCards( int [], string , int);

int main(){
    //freopen("D:\\MyCandCPPspace\\test.txt","r",stdin);
    system("title FightTheLandlord");   //设置cmd窗口名称
    firstShow();   //界面初始化
    int totalCards[16] = {0, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 1};   //设置总牌堆
    bool choice = true;   //是否进行游戏
    bool broken = false;   //玩家是否破产
    srand(time(0));
    cout << "是否准备好游戏?(1/0)" << endl;
    cin >> choice;
    if(choice){
        string CARD = "***34567890JQKA2GR";
        system("cls");
        long long money1, money2;
        people play[3];   //play[0]是玩家, play[1], play[2]是电脑
        play[0].changeMoney(2000);

        //初始化对手的金钱
        cout << "初始化对手的初始资金 : " << endl;
        cin >> money1 >> money2;
        play[1].changeMoney( money1);
        play[2].changeMoney( money2);

        for( ; !broken && choice && play[1].getMoney() > 0 && play[2].getMoney() > 0; cin >> choice){   //如果你还剩钱则继续游戏, 或自己手动退出

            //游戏界面
            system("cls");
            firstShow();
            play[0].show();

            int setMoney;
            cout << "输入这盘的赌金 : \n";
            cin >> setMoney;

            int landlordcard[3];
            landlordcard[0] = rand()%15+1;
            landlordcard[1] = rand()%15+1;
            landlordcard[2] = rand()%15+1;

            //保证地主牌不会出现两张小王或两张大王
            if(landlordcard[0] == 14){
                while( landlordcard[1] == 14)
                    landlordcard[1] = rand()%15+1;
                if( landlordcard[1] == 15)
                    while( landlordcard[2] == 15 || landlordcard[2] == 14)
                        landlordcard[2] = rand()%15+1;
                else
                    while( landlordcard[2] == 14 )
                        landlordcard[2] = rand()%15+1;
            }else if( landlordcard[0] == 15){
                while( landlordcard[1] == 15)
                    landlordcard[1] = rand()%15+1;
                if( landlordcard[1] == 14)
                    while( landlordcard[2] == 15 || landlordcard[2] == 14)
                        landlordcard[2] = rand()%15+1;
                else
                    while( landlordcard[2] == 15 )
                        landlordcard[2] = rand()%15+1;
            }else if( landlordcard[1] == 15){
                while( landlordcard[2] == 15)
                    landlordcard[2] = rand()%16+1;
            }else if( landlordcard[1] == 16)
                while( landlordcard[2] == 16)
                    landlordcard[2] = rand()%16+1;

            totalCards[landlordcard[0]]--;
            totalCards[landlordcard[1]]--;
            totalCards[landlordcard[2]]--;

            //发牌
            getCards( totalCards, play[0].cards);
            getCards( totalCards, play[1].cards);
            getCards( totalCards, play[2].cards);

            //确定地主
            play[0].landlord = false;
            play[1].landlord = false;
            play[2].landlord = false;
            int landlord = rand()%3;

            landlord = 0;

            play[landlord].landlord = true;
            int farmer[2] = {0};
            switch(landlord){
                case 0:
                    play[0].landlordTimes++;
                    farmer[0] = 1;
                    farmer[1] = 2;
                    break;
                case 1:
                    farmer[1] = 2;
                    break;
                case 2:
                    farmer[1] = 1;
            }

            //追加地主牌
            play[landlord].cards[landlordcard[0]]++;
            play[landlord].cards[landlordcard[1]]++;
            play[landlord].cards[landlordcard[2]]++;

            play[landlord].cards[0] = 20;
            play[farmer[0]].cards[0] = 17;
            play[farmer[1]].cards[0] = 17;

            bool t;   //存储地主是否赢了
            t = game( play[0].cards, play[1].cards, play[2].cards, landlord, farmer);

            if(t){
                play[landlord].win(setMoney*2);
                play[farmer[0]].lose(setMoney);
                play[farmer[1]].lose(setMoney);
            }else{
                play[landlord].lose(setMoney*2);
                play[farmer[0]].win(setMoney);
                play[farmer[1]].win(setMoney);
            }

            if(play[0].getMoney() < 0){
                bool buyMoney;
                cout << "是否要充值点钱 ?(1/0)" <<endl;
                cin >> buyMoney;
                if( buyMoney){
                    long long secreat;
                    cout << "写下十个数字的充值密码" << endl;
                    cin >> secreat;
                    if(!play[0].buyMoney(secreat))
                        broken = true;
                }else
                    broken = true;
            }else{
                cout << "你想继续玩吗 ? " << endl;
            }
        }

        //游戏结束
        Sleep(1000);
        system("cls");
        if( broken){
            cout << "you lose " << endl;
            Sleep(1000);
            system("cls");
        }
        cout << endl << "you : " << endl;
        cout << "初始金额 : 2000" << endl;
        play[0].show();
        cout << endl << "enemy1 : " << endl;
        cout << "初始金额 : " << money1 << endl;
        play[1].show();
        cout << endl << "enemy2 : " << endl;
        cout << "初始金额 : " << money2 << endl;
        play[2].show();
    }
    cout << "thanks for your playing " << endl;
    return 0;
}

void firstShow(){
    cout << "------------------------------------------------------------" << endl << endl;
    cout << "\t\tFight! The! Landlord!!!\t\t" << endl << endl;
    cout << "------------------------------------------------------------" << endl;
}

/** \brief 发牌
 *
 * \param tota[]为总牌堆
 * \param cards[]为玩家或者对手牌, cards[0]为总手牌数
 */
void getCards( int total[16], int cards[21]){
    int i;
    int card;
    for( i = 0; i < 17; i++){
        do{
            card = rand()%15+1;
        }while( total[card] < 1);
        cards[card]++;
        total[card]--;
    }
    cards[17] = cards[15];
    cards[16] = cards[14];
    cards[14] = cards[1];
    cards[15] = cards[2];
    cards[1] = 0;
    cards[2] = 0;
    for( i = 3; i < 18; i++){
        if( cards[i] == 1)
            cards[1]++;
        else if( cards[i] == 2)
            cards[2]++;
        else if( cards[i] == 3)
            cards[18]++;
        else if( cards[i] == 4)
            cards[19]++;
    }
    if( cards[16]&&cards[17]){
        cards[1] -= 2;
        cards[19]++;
        cards[20]++;
    }
}

/** \brief 打牌
 *
 * \param card[]为手牌
 * \param landlord为地主是谁(0,1,2)
 * \return 地主是否输了
 */
//////////////////////////////////////////////////////////////////////////////////////////////////////
bool game( int card0[21], int card1[21], int card2[21], int landlord, int farmer[2]){
    string CARD = "***34567890JQKA2GR";

    int card[3][21];
    int i;
    string put;
    int cardsKind;
    system("cls");

    for( i = 0; i < 21; i++){
        card[0][i] = card0[i];
        card[1][i] = card1[i];
        card[2][i] = card2[i];
    }
    int lastPut = landlord;   //判断最后出牌人是谁，如果到你出牌时上一个出牌人是自己则可以随意出牌
    for( int time = landlord; card[ landlord][0] != 0 && (card[ farmer[0]][0] != 0 && card[ farmer[1]][0] != 0); time++){
        string put_;
        /**/
        cout << "地主是：" << landlord << endl;
        cout << "电脑1剩：" << card[1][0] << endl;
        cout << "剩\t3 4 5 6 7 8 9 10 J Q K A 2 小 大" << endl;
        printf("%d\t%d %d %d %d %d %d %d %d  %d %d %d %d %d %d  %d\n",
                card[1][0], card[1][3], card[1][4], card[1][5], card[1][6], card[1][7], card[1][8], card[1][9],
                card[1][10], card[1][11], card[1][12], card[1][13], card[1][14], card[1][15], card[1][16], card[1][17]);
        cout << "电脑2剩：" << card[2][0] << endl;
        cout << "剩\t3 4 5 6 7 8 9 10 J Q K A 2 小 大" << endl;
        printf("%d\t%d %d %d %d %d %d %d %d  %d %d %d %d %d %d  %d\n",
                card[2][0], card[2][3], card[2][4], card[2][5], card[2][6], card[2][7], card[2][8], card[2][9],
                card[2][10], card[2][11], card[2][12], card[2][13], card[2][14], card[2][15], card[2][16], card[2][17]);
        cout << "你剩：" << card[0][0] << endl;
        cout << "剩\t3 4 5 6 7 8 9 10 J Q K A 2 小 大" << endl;
        printf("%d\t%d %d %d %d %d %d %d %d  %d %d %d %d %d %d  %d\n",
                card[0][0], card[0][3], card[0][4], card[0][5], card[0][6], card[0][7], card[0][8], card[0][9],
                card[0][10], card[0][11], card[0][12], card[0][13], card[0][14], card[0][15], card[0][16], card[0][17]);
        /**/
        kind();
        cout << endl;
        if( time == 0){
            if( lastPut != 0){   //已经有人出过牌，根据出的牌判断出牌与否
                if(  !put.empty() ){
                    cout << "玩家：" << lastPut << "号 出牌类型 ： " << cardsKind << "  出的牌：" << put;
                    cout << endl << "你选择的出牌类型 ：";
                }else
                    cout << "你能随意出牌, 选择你的出牌类型 ：";
            }else
                cout << "你能随意出牌, 选择你的出牌类型 ：";
            cin >> cardsKind ;
            if(cardsKind != 37){
                cout << "输入要出的牌, 0代表10 G代表小王 R代表大王" << endl;
                cout << "示例：\n三个A带只3 A3\n对三对四对五 345\n对十 0\n王炸 GR" << endl;
                cin >> put_;
                lastPut = 0;
            }else
                put_ = "NoCardsCanPut";

        }else if( time == 1)
            put_.assign( computerPuts( card[1], put, &cardsKind, &lastPut, 1) );
        else if( time == 2)
            put_.assign( computerPuts( card[2], put, &cardsKind, &lastPut, 2) );

        if( put_ != "NoCardsCanPut" ){
            put.assign( put_);
            changeCards( card[ lastPut], put, cardsKind);
            if( lastPut == 2 )
                time = -1;
            else
                time = lastPut;
        }else
            time = lastPut - 1;
        system("cls");
    }
    if( card[landlord][0])   //地主有牌剩余
        return 0;
    else
        return 1;
}
void kind(){
    for( int i = 1; i < 37; i+=3)
        cout << kindsOfCard[i] << "\t" << kindsOfCard[i+1] << "\t" << kindsOfCard[i+2] << "\t\n";
    cout << kindsOfCard[37] << endl;
}

string computerPuts( int card[21], string put, int* cardsKind, int* lastPut, int computer){
//如果没有可出的牌返回NoCardsCanPut, 主程序针对此做出处理

    string CARD = "***34567890JQKA2GR";
    string put_ = "*";
    if( *lastPut == computer){   //上次出牌的是这次要出的, 可以任意出牌
        put_.assign( putCardsAtWill( card, cardsKind) );
    }else{   //根据上次的出牌选择跟牌
        bool follow = false;
        int kind_ = *cardsKind;
        int i, j, k;
        if( kind_ == 1){   //单张
            if( card[1] > 0)
                for( i = CARD.find(put[0])+1; i < 18; i++)
                    if( card[i]==1){
                        put_[0] = CARD[i];
                        follow = true;
                        break;
                    }
        }else if( kind_ == 2){   //对子
            if( card[2] > 0)
                for( i = put[0]-'0'+1; i < 18; i++)
                    if( card[i]==2){
                        put_[0] = CARD[i];
                        follow = true;
                        break;
                    }
        }else if( kind_ > 2 && kind_ < 17){   //飞机

            int Length = 0;
            if( kind_ < 9){   //单独飞机
                Length = kind_ - 2;   //飞机个数
                put_.assign( Length, '*');
            }else{
                if( kind_%2 == 1)
                    Length = (kind_ - 7) / 2;
                else
                    Length = (kind_ - 8) / 2;
                put_.assign( Length*2, '*');
            }
            if( card[18] > Length){   //三张的个数大于飞机的个数
                for( i = CARD.find(put[0])+1; i < 16; i++){
                    for( j = 0; j < Length;j++)
                        if( card[i+j] < 3)
                            break;
                    if( j == Length){
                        for( k = 0; k < Length; k++)
                            put_[k] = CARD[i+k];
                        follow = true;
                        break;
                    }
                }
                if( follow && kind_ > 8){
                    if( kind_ %2 == 1){   //飞机带单张
                        if( card[1] < Length){   //飞机数大于单张数
                            follow = false;
                        }else{
                            for( i = 3; i < 16; i++ )
                                if( card[i] == 1)
                                    put_[k++] = CARD[i];
                            if( k < Length * 2 - 1)
                                follow = false;
                        }
                    }else{   //飞机带对子
                        if( card[2] < Length){   //飞机数大于对子数
                            follow = false;
                        }else{
                            for( i = 3; i < 16; i++ )
                                if( card[i] == 2)
                                    put_[k++] = CARD[i];
                            if( k < Length * 2 - 1)
                                follow = false;
                        }
                    }
                }
            }
        }else if( kind_ == 17){   //四带二
            if( card[19] > 0){
                follow = true;
                if( card[19] == 1 && card[20])
                    follow = false;
                else{
                    if( card[1] > 0){
                        for( i = CARD.find(put[0])+1; i < 15; i++)
                            if(card[i] == 4){
                                put_[0] = CARD[i];
                                break;
                            }
                        for( i = 3; i < 15; i++)
                            if( card[i] == 1){
                                put_[1] = CARD[i];
                                break;
                            }
                    }else
                        follow = false;
                }
            }
        }else if( kind_ == 18){   //四带两对
            if( card[19] > 0){
                follow = true;
                if( card[19] == 1 && card[20])
                    follow = false;
                else{
                    if( card[2] > 0){
                        for( i = CARD.find(put[0])+1; i < 15; i++)
                            if( card[i] == 4){
                                put_[0] = CARD[i];
                                break;
                            }
                        for( i = 3; i < 15; i++)
                            if( card[i] == 2){
                                put_[1] = CARD[i];
                                break;
                            }
                    }
                    else
                        follow = false;
                }
            }
        }else if( kind_ > 18 && kind_ < 27){   //连对
            int Length = 0;
            if( card[2] > 2){
                Length = put.length();
                for( i = CARD.find(put[0])+1; i < 15; i++){
                    if( card[i] > 1 && card[i] != 4)
                        for( j = 0; j < Length; j++)
                            if( card[i+j] < 2)
                                break;
                    if( j == Length){
                        follow = true;
                        break;
                    }
                }
                if( follow){
                    for( j = 0; j < Length; j++)
                        put_[j] = CARD[i+j];
                }
            }
        }else if( kind_ > 26 && kind_ < 35){   //顺子
            if( card[1] > 4){
                int Length = 0;
                Length = put.length();
                for( i = CARD.find(put[0])+1; i < 15; i++){
                    if( card[i] > 0 && card[i] != 4)
                        for( j = 0; j < Length; j++)
                            if( card[i+j] < 1)
                                break;
                    if( j == Length){
                        follow = true;
                        break;
                    }
                }
                if( follow){
                    for( j = 0; j < Length; j++)
                        put_[j] = CARD[i+j];
                }
            }
        }else if( kind_ == 35 ){   //炸弹
            if(card[19] > 0){
                for( i = CARD.find(put[0])+1; i < 15; i++)
                    if( card[i] == 4){
                        follow = true;
                        break;
                    }
            }
            if( follow )
                put_[0] = CARD[i];

        }else if( kind_ == 36){   //王炸
            follow = false;
        }
        if( follow ){   //要的起
            *lastPut = computer;
        }else{   //要不起
            put_.assign("NoCardsCanPut");
        }
    }
    return put_;
}

string putCardsAtWill( int card[21], int* cardsKind){   //任意出牌, 保证出牌数量最多, 有单张3或对3先出, 返回put
    string CARD = "***34567890JQKA2GR";
    string put = "0";
    string danzhi = "*";
    string duizi = "*";
    string threeOrFour[2] = { "4", "3" };
    int liandui_ = 0;
    int liandui_Begin = 0;
    int liandui_1 = 0;   //用于记录新发现的连对, 比较两者哪个更长, 保存更长的
    int liandui_Begin1 = 0;
    string liandui = "*";
    int shunzi_ = 0;
    int shunzi_Begin = 0;
    int shunzi_1 = 0;   //用于记录新发现的顺子, 比较两者哪个更长, 保存更长的
    int shunzi_Begin1 = 0;
    string shunzi = "*";
    int feiji_ = 0;
    string feiji = "*";
    int feiji_Begin = 0;
    int feiji_1 = 0;
    int feiji_Begin1 = 0;
    int l;
    string sidaier = "***";
    string sidailiangdui = "***";
    int dan[2] = {0};
    int shuang[2] = {0};

    int j , i;
    int mostCard = 0;   //记录最多出牌数量
    int bestChoice = 0;   //记录最佳方案


    if( card[0] == 4 && card[19] && card[20] == 0 ){
        bestChoice = 35;
        mostCard = 4;
        for( i = 3; i < 16; i++)
            if( card[i] == 4){
                put[0] = CARD[i];
                break;
            }
    }else if( card[0] == 2 && card[20] ){
        bestChoice = 36;
        mostCard = 2;
        put = "GR" ;
    }else{
        //连对

        if(card[2] > 2){   //对子数大于2时才可能有连对
            for( i = 3; i < 15; i++)
                if( card[i] > 1 && card[i]!=4){
                    if( liandui_Begin + liandui_ == i)
                        liandui_++;
                    else
                        if( liandui_Begin == 0){
                            liandui_Begin = i;
                            liandui_ = 1;
                        }else{
                            if( liandui_Begin1 == 0){
                                liandui_1 = 1;
                                liandui_Begin1 = i;
                            }else if( liandui_Begin1 + liandui_1 == i){
                                liandui_1++;
                            }else{
                                liandui_1 = 0;
                                liandui_Begin1 = 0;
                            }
                        }
                    if( liandui_1 > liandui_){   //当新发现的连对更长时, 更新
                        liandui_ = liandui_1;
                        liandui_Begin = liandui_Begin1;
                        liandui_1 = 0;
                        liandui_Begin1 = 0;
                    }
                }

            if( liandui_ > 2){
                liandui.assign( liandui_, '*');
                for( j = liandui_Begin; j < liandui_Begin+liandui_; j++)
                    liandui[ j - liandui_Begin] = CARD[j];
            }
            bestChoice = liandui_+16;
            mostCard = liandui_*2;
        }

        //飞机

        if(card[18] > 0){   //三张数大于0才可能有飞机或是三张带一张或者对子
            for( i = 3; i < 15; i++){
                if( card[i] == 3){
                    if( feiji_ + feiji_Begin == i)
                        feiji_++;
                    else{
                        if( feiji_ + feiji_Begin == 0){
                            feiji_ = 1;
                            feiji_Begin = i;
                        }else
                            if( feiji_Begin1 == 0){
                                feiji_Begin1 = i;
                                feiji_1 = 1;
                            }else if( feiji_Begin1 + feiji_1 == i)
                                feiji_1++;
                    }
                }
                if( feiji_1 > feiji_){
                    feiji_ = feiji_1;
                    feiji_Begin = feiji_Begin1;
                    feiji_1 = 0;
                    feiji_Begin1 = 0;
                }
            }
            if( feiji_ > 0){   //当飞机数大于0时
                feiji.assign( feiji_,'*');
                for( j = feiji_Begin; j < feiji_Begin+feiji_; j++)
                    feiji[j-feiji_Begin] = CARD[j];
                if( feiji_ <= card[2]){   //飞机数<=对子数, 才能出3张带2张
                    int duizi_[feiji_];
                    for( j = 3, l = 0; j < feiji_Begin && l < feiji_; j++)
                        if( card[j] == 2){
                            duizi_[l] = j;
                            l++;
                        }
                    for( j = feiji_Begin+feiji_; j < 16 && l < feiji_; j++)
                        if( card[j] == 2){
                            duizi_[l] = j;
                            l++;
                        }
                    if( feiji_*5 > mostCard){
                        mostCard = feiji_*5;
                        bestChoice = 8 + feiji_*2;
                        feiji.insert( feiji_, feiji);
                        for( j = feiji_, i = 0; j < feiji_*2; j++, i++)
                            feiji[j] = CARD[duizi_[i]];
                    }
                }else if(feiji_ <= card[1]){   //飞机数<=单张数, 才能出3张带1张
                    int danzhang_[feiji_];
                    for( j = 3, l = 0; j < feiji_Begin && l < feiji_; j++)
                        if( card[j] == 1){
                            danzhang_[l] = j;
                            l++;
                        }
                    for( j = feiji_Begin+feiji_; j < 18 && l < feiji_; j++)
                        if( card[j] == 1){
                            danzhang_[l] = j;
                            l++;
                        }
                    if( feiji_*4 > mostCard){
                        mostCard = feiji_*4;
                        bestChoice = 7 + feiji_*2;
                        feiji.insert( feiji_, feiji);
                        for( j = feiji_, i = 0; j < feiji_*2; j++, i++)
                            feiji[j] = CARD[danzhang_[i]];
                    }
                }else   //只能出寡的飞机
                    if( feiji_*3 > mostCard){
                        mostCard = feiji_*3;
                        bestChoice = feiji_+2;
                    }
            }
        }

        if(card[1] > 4){   //对子数大于4时才可能有顺子
            for( i = 3; i < 15; i++)
                if( card[i] > 0 && card[i]!=4){
                    if( shunzi_Begin + shunzi_ == i)
                        shunzi_++;
                    else
                        if( shunzi_Begin == 0){
                            shunzi_Begin = i;
                            shunzi_ = 1;
                        }else{
                            if( shunzi_Begin1 == 0){
                                shunzi_1 = 1;
                                shunzi_Begin1 = i;
                            }else if( shunzi_Begin1 + shunzi_1 == i){
                                shunzi_1++;
                            }
                        }
                    if( shunzi_1 > shunzi_){   //当新发现的顺子更长时, 更新
                        shunzi_ = shunzi_1;
                        shunzi_Begin = shunzi_Begin1;
                        shunzi_1 = 0;
                        shunzi_Begin1 = 0;
                    }
                }

            if( shunzi_ > 4){
                shunzi.assign( shunzi_, '*');
                for( j = shunzi_Begin; j < shunzi_Begin+shunzi_; j++)
                    shunzi[ j - shunzi_Begin] = CARD[j];
            }
            if( mostCard < shunzi_){
                bestChoice = shunzi_+22;
                mostCard = shunzi_;
            }
        }

        if( ( mostCard == 0) && ( ( card[3] == 1 || card[4] == 1 ) || ( card[3] == 2 || card[4] == 2 ) ) ){   //当前面的方式都不行,且有 3 4
            if(card[3] == 1 || card[4] == 1){
                danzhi = threeOrFour[ card[3] ];
                bestChoice = 1;
            }else if( card[3] == 2 || card[4] == 2){
                duizi = threeOrFour[ card[3] ];
                bestChoice = 2;
            }
        }else{

            //四带二(对)

            if( card[19] - card[20] > 0){   //有炸弹
                if( card[2] > 1)
                    for( i = 3, j = 0; i < 16 && j < 2; i++){
                        if( card[i] == 2){
                            shuang[j] = i;
                            j++;
                        }
                    }
                else if( card[1] > 1)
                    for( i = 3, j = 0, l = 0; i < 18 && j < 2 ; i++){
                        if( card[i] == 1){
                            dan[j] = i;
                            j++;
                        }
                    }
                if( shuang[1]){   //有两个对子
                    for( i = 3; i < 18; i++)
                        if( card[i] == 4)
                            break;
                    sidailiangdui[0] = CARD[i];
                    sidailiangdui[1] = CARD[shuang[0]];
                    sidailiangdui[2] = CARD[shuang[1]];
                    if( mostCard < 8){
                        mostCard = 8;
                        bestChoice = 18;
                    }
                }else if( dan[1]){   //有两个单张
                    for( i = 3; i < 18; i++)
                        if( card[i] == 4)
                            break;
                    sidaier[0] = CARD[i];
                    sidaier[1] = CARD[dan[0]];
                    sidaier[2] = CARD[dan[1]];
                    if( mostCard < 6){
                        mostCard = 6;
                        bestChoice = 17;
                    }
                }
            }

        }

        if( card[2] > 0){
            for( i = 4; i < 16; i++)
                if( card[i] == 2 && bestChoice < 2){
                    duizi = CARD[i];
                    bestChoice = 2;
                    break;
                }
        }

        if( card[1] > 0){
            for( i = 4; i < 16; i++)
                if( card[i] == 1 && bestChoice < 1){
                    danzhi = CARD[i];
                    bestChoice = 1;
                    break;
                }
        }

    }

    //寻找出牌个数最多的返回
    if( bestChoice == 1){
        put = danzhi;
    }else if( bestChoice == 2){
        put = duizi;
    }else if( bestChoice > 18 && bestChoice < 27){   //最多是连对
        put.assign( liandui);
    }else if( bestChoice > 26 && bestChoice < 35){   //最多是顺子
        put.assign( shunzi);
    }else if( bestChoice > 2 && bestChoice < 17 ){   //最多是飞机
        put.assign( feiji);
    }else if( bestChoice == 17  ){   //最多是四带二
        put.assign( sidaier);
    }else if( bestChoice == 18){   //最多是四带两对
        put.assign( sidailiangdui);
    }

    *cardsKind = bestChoice;
    return put;
}

void changeCards( int card[21], string put, int cardsKind){
    string CARD = "***34567890JQKA2GR";
    int n[9] = {0};
    int i = -1;
    if( cardsKind == 1){
        n[0] = CARD.find( put[0]);
        card[n[0]]--;
        card[0]--;
    }else if( cardsKind == 2){
        n[0] = CARD.find( put[0]);
        card[n[0]] -= 2;
        card[0] -= 2;
    }else if( cardsKind >= 3 && cardsKind <= 8){
        n[0] = CARD.find( put[0]);
        for( int i = 0 ; i < cardsKind - 2; i++)
            card[n[0]+i] -= 3;
        card[0] -= ( cardsKind - 2)*3;
    }else if( cardsKind > 8 && cardsKind < 17){
        if( cardsKind % 2){
            int L = ( cardsKind - 7) / 2;
            for( i = 0; i < L; i++){
                n[i] = CARD.find( put[i]);
                card[n[i]] -= 3;
                n[i+L] = CARD.find( put[i+L]);
                card[n[i+L]]--;
            }
            card[0] -= L*4;
        }else{
            int L = ( cardsKind - 8) / 2;
            for( i = 0; i < L; i++){
                n[i] = CARD.find( put[i]);
                card[n[i]] -= 3;
                n[i+L] = CARD.find( put[i+L]);
                card[n[i+L]] -= 2;
            }
            card[0] -= L*4;
        }
    }else if( cardsKind == 17){
        n[0] = CARD.find( put[0]);
        card[n[0]] -= 4;
        n[1] = CARD.find( put[1]);
        card[n[1]] --;
        n[2] = CARD.find( put[2]);
        card[n[2]] --;
        card[0] -= 6;
    }else if( cardsKind == 18){
        n[0] = CARD.find( put[0]);
        card[n[0]] -= 4;
        n[1] = CARD.find( put[1]);
        card[n[1]] -= 2;
        n[2] = CARD.find( put[2]);
        card[n[2]] -= 2;
        card[0] -= 8;
    }else if( cardsKind > 18 && cardsKind < 27){
        n[0] = CARD.find( put[0]);
        for( i = 0; i < cardsKind-16; i++)
            card[n[0]+i] -= 2;
        card[0] -= (cardsKind - 16)*2;
    }else if( cardsKind > 26 && cardsKind < 35){
        n[0] = CARD.find( put[0]);
        for( i = 0; i < cardsKind - 22; i++)
            card[n[0]+i]--;
        card[0] -=  (cardsKind - 22);
    }else if( cardsKind == 35){
        n[0] = CARD.find( put[0]);
        card[n[0]] -= 4;
        card[0] -= 4;
    }else if( cardsKind == 36){
        card[15]--;
        card[16]--;
        card[0] -= 2;
    }
}
