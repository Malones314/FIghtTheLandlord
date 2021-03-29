#ifndef PEOPLE_H
#define PEOPLE_H
class people{
    public:
        bool landlord;
        int cards[21];
        //cards[0]为总牌数, 1为单张个数, 2为对子个数, 18为三张个数, 19为炸个数, 20为是否有王炸

        people();
        people(long long );
        long long getMoney();
        int getWins();
        int getLoses();
        bool buyMoney(long long secret_);
        void show();
        void changeMoney(long long);
        void win( int );
        int landlordTimes;
        int gameTimes;
        void lose( int);
    private:
        long long money;
        int wins;
        int loses;
        int secret;

};

#endif // PEOPLE_H
