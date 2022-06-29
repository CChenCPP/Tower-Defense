#include "Wave.h"

Wave::Wave(int level) :
    level(level)
{
    generateEnemyList(level);
}

// public methods
QVector<Enemy*> Wave::getEnemyList() const
{
    return enemyList;
}

void Wave::generateEnemyList(int level)
{
    switch(level){
        case 1:
            wave1(); return;
        case 2:
            wave2(); return;
        case 3:
            wave3(); return;
    }
}

// private methods
void Wave::wave1()
{
    for (int i = 0; i < 10; ++i){
        Enemy* enemy = new Enemy(Enemy::defaultHp * level);
        enemyList.push_back(enemy);
    }
}

void Wave::wave2()
{
    wave1();
    wave1();
}

void Wave::wave3()
{
    wave2();
    wave2();
}

void Wave::wave4()
{
    wave2();
    wave2();
    wave2();
}

void Wave::wave5()
{
    wave4();
    wave4();
}

void Wave::wave6()
{
    wave3();
    wave3();
    wave3();
}

void Wave::wave7()
{
    wave5();
    wave5();
}

