#include "Wave.h"
#include "Enemies/CukzotzEnemy.h"
#include "Enemies/DharuerEnemy.h"
#include "Enemies/EnioneEnemy.h"
#include "Enemies/EzlotlEnemy.h"
#include "Enemies/HudorEnemy.h"
#include "Enemies/KhyemisEnemy.h"
#include "Enemies/KronusEnemy.h"
#include "Enemies/LoldohrEnemy.h"
#include "Enemies/PhihenarEnemy.h"
#include "Enemies/RihrusEnemy.h"
#include "Enemies/UdallEnemy.h"
#include "Enemies/UesisEnemy.h"
#include "Enemies/ZanbrisEnemy.h"
#include "Misc/Utility.h"

Wave::Wave(int level) :
    level(level),
    spawnIntervalMs(0)
{
    generateEnemyList(level);
}

Wave::~Wave()
{
}

// public methods
//std::unordered_set<Enemy*>& Wave::getEnemyList()
//{
//    return enemiesToSpawn;
//}

QVector<Enemy*>& Wave::getEnemyList()
{
    return enemiesToSpawn;
}

int Wave::getSpawnIntervalMs() const
{
    return spawnIntervalMs;
}

// private methods
void Wave::addCukzotz(int amount)
{
    for (int i = 0; i < amount; ++i){
        CukzotzEnemy* enemy = new CukzotzEnemy(level);
        enemiesToSpawn.push_back(enemy);
    }
}
void Wave::addDharuer(int amount)
{
    for (int i = 0; i < amount; ++i){
        DharuerEnemy* enemy = new DharuerEnemy(level);
        enemiesToSpawn.push_back(enemy);
    }
}

void Wave::addEnione(int amount)
{
    for (int i = 0; i < amount; ++i){
        EnioneEnemy* enemy = new EnioneEnemy(level);
        enemiesToSpawn.push_back(enemy);
    }
}

void Wave::addEzlotl(int amount)
{
    for (int i = 0; i < amount; ++i){
        EzlotlEnemy* enemy = new EzlotlEnemy(level);
        enemiesToSpawn.push_back(enemy);
    }
}

void Wave::addHudor(int amount)
{
    for (int i = 0; i < amount; ++i){
        HudorEnemy* enemy = new HudorEnemy(level);
        enemiesToSpawn.push_back(enemy);
    }
}

void Wave::addKhyemis(int amount)
{
    for (int i = 0; i < amount; ++i){
        KhyemisEnemy* enemy = new KhyemisEnemy(level);
        enemiesToSpawn.push_back(enemy);
    }
}

void Wave::addKronus(int amount)
{
    for (int i = 0; i < amount; ++i){
        KronusEnemy* enemy = new KronusEnemy(level);
        enemiesToSpawn.push_back(enemy);
    }
}

void Wave::addLoldohr(int amount)
{
    for (int i = 0; i < amount; ++i){
        LoldohrEnemy* enemy = new LoldohrEnemy(level);
        enemiesToSpawn.push_back(enemy);
    }
}

void Wave::addPhihenar(int amount)
{
    for (int i = 0; i < amount; ++i){
        PhihenarEnemy* enemy = new PhihenarEnemy(level);
        enemiesToSpawn.push_back(enemy);
    }
}

void Wave::addRihrus(int amount)
{
    for (int i = 0; i < amount; ++i){
        RihrusEnemy* enemy = new RihrusEnemy(level);
        enemiesToSpawn.push_back(enemy);
    }
}

void Wave::addUdall(int amount)
{
    for (int i = 0; i < amount; ++i){
        UdallEnemy* enemy = new UdallEnemy(level);
        enemiesToSpawn.push_back(enemy);
    }
}

void Wave::addUesis(int amount)
{
    for (int i = 0; i < amount; ++i){
        UesisEnemy* enemy = new UesisEnemy(level);
        enemiesToSpawn.push_back(enemy);
    }
}

void Wave::addZanbris(int amount)
{
    for (int i = 0; i < amount; ++i){
        ZanbrisEnemy* enemy = new ZanbrisEnemy(level);
        enemiesToSpawn.push_back(enemy);
    }
}

void Wave::generateEnemyList(int level)
{
    switch(level){
        case 1:
            wave1(); break;
        case 2:
            wave2(); break;
        case 3:
            wave3(); break;
        case 4:
            wave4(); break;
        case 5:
            wave5(); break;
        case 6:
            wave6(); break;
        case 7:
            wave7(); break;
        case 8:
            wave8(); break;
        case 9:
            wave9(); break;
        case 10:
            wave10(); break;
        case 11:
            wave11(); break;
        case 12:
            wave12(); break;
        case 13:
            wave13(); break;
        case 14:
            wave14(); break;
        case 15:
            wave15(); break;
        case 16:
            wave16(); break;
        case 17:
            wave17(); break;
        case 18:
            wave18(); break;
        case 19:
            wave19(); break;
        case 20:
            wave20(); break;
        case 21:
            wave21(); break;
        case 22:
            wave22(); break;
        case 23:
            wave23(); break;
        case 24:
            wave24(); break;
        case 25:
            wave25(); break;
        case 26:
            wave26(); break;
        case 27:
            wave27(); break;
        case 28:
            wave28(); break;
        case 29:
            wave29(); break;
        case 30:
            wave30(); break;
        case 31:
            wave31(); break;
        case 32:
            wave32(); break;
        case 33:
            wave33(); break;
        case 34:
            wave34(); break;
        case 35:
            wave35(); break;
        case 36:
            wave36(); break;
        case 37:
            wave37(); break;
        case 38:
            wave38(); break;
        case 39:
            wave39(); break;
        case 40:
            wave40(); break;
        case 41:
            wave41(); break;
        case 42:
            wave42(); break;
        case 43:
            wave43(); break;
        case 44:
            wave44(); break;
        case 45:
            wave45(); break;
        case 46:
            wave46(); break;
        case 47:
            wave47(); break;
        case 48:
            wave48(); break;
        case 49:
            wave49(); break;
        case 50:
            wave50(); break;
        case 51:
            wave51(); break;
        case 52:
            wave52(); break;
        case 53:
            wave53(); break;
        case 54:
            wave54(); break;
        case 55:
            wave55(); break;
        case 56:
            wave56(); break;
        case 57:
            wave57(); break;
        case 58:
            wave58(); break;
        case 59:
            wave59(); break;
        case 60:
            wave60(); break;
        case 61:
            wave61(); break;
        case 62:
            wave62(); break;
        case 63:
            wave63(); break;
        case 64:
            wave64(); break;
        case 65:
            wave65(); break;
        case 66:
            wave66(); break;
        case 67:
            wave67(); break;
        case 68:
            wave68(); break;
        case 69:
            wave69(); break;
        case 70:
            wave70(); break;
        case 71:
            wave71(); break;
        case 72:
            wave72(); break;
        case 73:
            wave73(); break;
        case 74:
            wave74(); break;
        case 75:
            wave75(); break;
        case 76:
            wave76(); break;
        case 77:
            wave77(); break;
        case 78:
            wave78(); break;
        case 79:
            wave79(); break;
        case 80:
            wave80(); break;
        case 81:
            wave81(); break;
        case 82:
            wave82(); break;
        case 83:
            wave83(); break;
        case 84:
            wave84(); break;
        case 85:
            wave85(); break;
        case 86:
            wave86(); break;
        case 87:
            wave87(); break;
        case 88:
            wave88(); break;
        case 89:
            wave89(); break;
        case 90:
            wave90(); break;
        case 91:
            wave91(); break;
        case 92:
            wave92(); break;
        case 93:
            wave93(); break;
        case 94:
            wave94(); break;
        case 95:
            wave95(); break;
        case 96:
            wave96(); break;
        case 97:
            wave97(); break;
        case 98:
            wave98(); break;
        case 99:
            wave99(); break;
        case 100:
            wave100(); break;
        case 101:
            wave101(); break;
        case 102:
            wave102(); break;
        case 103:
            wave103(); break;
        case 104:
            wave104(); break;
        case 105:
            wave105(); break;
        case 106:
            wave106(); break;
        case 107:
            wave107(); break;
        case 108:
            wave108(); break;
        case 109:
            wave109(); break;
        case 110:
            wave110(); break;
        case 111:
            wave111(); break;
        case 112:
            wave112(); break;
        case 113:
            wave113(); break;
        case 114:
            wave114(); break;
        case 115:
            wave115(); break;
        case 116:
            wave116(); break;
        case 117:
            wave117(); break;
        case 118:
            wave118(); break;
        case 119:
            wave119(); break;
        case 120:
            wave120(); break;
        case 121:
            wave121(); break;
        case 122:
            wave122(); break;
        case 123:
            wave123(); break;
        case 124:
            wave124(); break;
        case 125:
            wave125(); break;
        case 126:
            wave126(); break;
        case 127:
            wave127(); break;
        case 128:
            wave128(); break;
        case 129:
            wave129(); break;
        case 130:
            wave130(); break;
        case 131:
            wave131(); break;
        case 132:
            wave132(); break;
        case 133:
            wave133(); break;
        case 134:
            wave134(); break;
        case 135:
            wave135(); break;
        case 136:
            wave136(); break;
        case 137:
            wave137(); break;
        case 138:
            wave138(); break;
        case 139:
            wave139(); break;
        case 140:
            wave140(); break;
        case 141:
            wave141(); break;
        case 142:
            wave142(); break;
        case 143:
            wave143(); break;
        case 144:
            wave144(); break;
        case 145:
            wave145(); break;
        case 146:
            wave146(); break;
        case 147:
            wave147(); break;
        case 148:
            wave148(); break;
        case 149:
            wave149(); break;
        case 150:
            wave150(); break;
        case 151:
            wave151(); break;
        case 152:
            wave152(); break;
        case 153:
            wave153(); break;
        case 154:
            wave154(); break;
        case 155:
            wave155(); break;
        case 156:
            wave156(); break;
        case 157:
            wave157(); break;
        case 158:
            wave158(); break;
        case 159:
            wave159(); break;
        case 160:
            wave160(); break;
        case 161:
            wave161(); break;
        case 162:
            wave162(); break;
        case 163:
            wave163(); break;
        case 164:
            wave164(); break;
        case 165:
            wave165(); break;
        case 166:
            wave166(); break;
        case 167:
            wave167(); break;
        case 168:
            wave168(); break;
        case 169:
            wave169(); break;
        case 170:
            wave170(); break;
        case 171:
            wave171(); break;
        case 172:
            wave172(); break;
        case 173:
            wave173(); break;
        case 174:
            wave174(); break;
        case 175:
            wave175(); break;
        case 176:
            wave176(); break;
        case 177:
            wave177(); break;
        case 178:
            wave178(); break;
        case 179:
            wave179(); break;
        case 180:
            wave180(); break;
        case 181:
            wave181(); break;
        case 182:
            wave182(); break;
        case 183:
            wave183(); break;
        case 184:
            wave184(); break;
        case 185:
            wave185(); break;
        case 186:
            wave186(); break;
        case 187:
            wave187(); break;
        case 188:
            wave188(); break;
        case 189:
            wave189(); break;
        case 190:
            wave190(); break;
        case 191:
            wave191(); break;
        case 192:
            wave192(); break;
        case 193:
            wave193(); break;
        case 194:
            wave194(); break;
        case 195:
            wave195(); break;
        case 196:
            wave196(); break;
        case 197:
            wave197(); break;
        case 198:
            wave198(); break;
        case 199:
            wave199(); break;
        case 200:
            wave200(); break;
        case 201:
            wave201(); break;
        case 202:
            wave202(); break;
        case 203:
            wave203(); break;
        case 204:
            wave204(); break;
        case 205:
            wave205(); break;
        case 206:
            wave206(); break;
        case 207:
            wave207(); break;
        case 208:
            wave208(); break;
        case 209:
            wave209(); break;
        case 210:
            wave210(); break;
        case 211:
            wave211(); break;
        case 212:
            wave212(); break;
        case 213:
            wave213(); break;
        case 214:
            wave214(); break;
        case 215:
            wave215(); break;
        case 216:
            wave216(); break;
        case 217:
            wave217(); break;
        case 218:
            wave218(); break;
        case 219:
            wave219(); break;
        case 220:
            wave220(); break;
        case 221:
            wave221(); break;
        case 222:
            wave222(); break;
        case 223:
            wave223(); break;
        case 224:
            wave224(); break;
        case 225:
            wave225(); break;
        case 226:
            wave226(); break;
        case 227:
            wave227(); break;
        case 228:
            wave228(); break;
        case 229:
            wave229(); break;
        case 230:
            wave230(); break;
        case 231:
            wave231(); break;
        case 232:
            wave232(); break;
        case 233:
            wave233(); break;
        case 234:
            wave234(); break;
        case 235:
            wave235(); break;
        case 236:
            wave236(); break;
        case 237:
            wave237(); break;
        case 238:
            wave238(); break;
        case 239:
            wave239(); break;
        case 240:
            wave240(); break;
        case 241:
            wave241(); break;
        case 242:
            wave242(); break;
        case 243:
            wave243(); break;
        case 244:
            wave244(); break;
        case 245:
            wave245(); break;
        case 246:
            wave246(); break;
        case 247:
            wave247(); break;
        case 248:
            wave248(); break;
        case 249:
            wave249(); break;
        case 250:
            wave250(); break;
        case 251:
            wave251(); break;
        case 252:
            wave252(); break;
        case 253:
            wave253(); break;
        case 254:
            wave254(); break;
        case 255:
            wave255(); break;
        case 256:
            wave256(); break;
        case 257:
            wave257(); break;
        case 258:
            wave258(); break;
        case 259:
            wave259(); break;
        case 260:
            wave260(); break;
        case 261:
            wave261(); break;
        case 262:
            wave262(); break;
        case 263:
            wave263(); break;
        case 264:
            wave264(); break;
        case 265:
            wave265(); break;
        case 266:
            wave266(); break;
        case 267:
            wave267(); break;
        case 268:
            wave268(); break;
        case 269:
            wave269(); break;
        case 270:
            wave270(); break;
        case 271:
            wave271(); break;
        case 272:
            wave272(); break;
        case 273:
            wave273(); break;
        case 274:
            wave274(); break;
        case 275:
            wave275(); break;
        case 276:
            wave276(); break;
        case 277:
            wave277(); break;
        case 278:
            wave278(); break;
        case 279:
            wave279(); break;
        case 280:
            wave280(); break;
        case 281:
            wave281(); break;
        case 282:
            wave282(); break;
        case 283:
            wave283(); break;
        case 284:
            wave284(); break;
        case 285:
            wave285(); break;
        case 286:
            wave286(); break;
        case 287:
            wave287(); break;
        case 288:
            wave288(); break;
        case 289:
            wave289(); break;
        case 290:
            wave290(); break;
        case 291:
            wave291(); break;
        case 292:
            wave292(); break;
        case 293:
            wave293(); break;
        case 294:
            wave294(); break;
        case 295:
            wave295(); break;
        case 296:
            wave296(); break;
        case 297:
            wave297(); break;
        case 298:
            wave298(); break;
        case 299:
            wave299(); break;
        case 300:
            wave300(); break;
        case 301:
            wave301(); break;
        case 302:
            wave302(); break;
        case 303:
            wave303(); break;
        case 304:
            wave304(); break;
        case 305:
            wave305(); break;
        case 306:
            wave306(); break;
        case 307:
            wave307(); break;
        case 308:
            wave308(); break;
        case 309:
            wave309(); break;
        case 310:
            wave310(); break;
        case 311:
            wave311(); break;
        case 312:
            wave312(); break;
        case 313:
            wave313(); break;
        case 314:
            wave314(); break;
        case 315:
            wave315(); break;
        case 316:
            wave316(); break;
        case 317:
            wave317(); break;
        case 318:
            wave318(); break;
        case 319:
            wave319(); break;
        case 320:
            wave320(); break;
        case 321:
            wave321(); break;
        case 322:
            wave322(); break;
        case 323:
            wave323(); break;
        case 324:
            wave324(); break;
        case 325:
            wave325(); break;
        case 326:
            wave326(); break;
        case 327:
            wave327(); break;
        case 328:
            wave328(); break;
        case 329:
            wave329(); break;
        case 330:
            wave330(); break;
        case 331:
            wave331(); break;
        case 332:
            wave332(); break;
        case 333:
            wave333(); break;
        case 334:
            wave334(); break;
        case 335:
            wave335(); break;
        case 336:
            wave336(); break;
        case 337:
            wave337(); break;
        case 338:
            wave338(); break;
        case 339:
            wave339(); break;
        case 340:
            wave340(); break;
        case 341:
            wave341(); break;
        case 342:
            wave342(); break;
        case 343:
            wave343(); break;
        case 344:
            wave344(); break;
        case 345:
            wave345(); break;
        case 346:
            wave346(); break;
        case 347:
            wave347(); break;
        case 348:
            wave348(); break;
        case 349:
            wave349(); break;
        case 350:
            wave350(); break;
        case 351:
            wave351(); break;
        case 352:
            wave352(); break;
        case 353:
            wave353(); break;
        case 354:
            wave354(); break;
        case 355:
            wave355(); break;
        case 356:
            wave356(); break;
        case 357:
            wave357(); break;
        case 358:
            wave358(); break;
        case 359:
            wave359(); break;
        case 360:
            wave360(); break;
        case 361:
            wave361(); break;
        case 362:
            wave362(); break;
        case 363:
            wave363(); break;
        case 364:
            wave364(); break;
        case 365:
            wave365(); break;
        case 366:
            wave366(); break;
        case 367:
            wave367(); break;
        case 368:
            wave368(); break;
        case 369:
            wave369(); break;
        case 370:
            wave370(); break;
        case 371:
            wave371(); break;
        case 372:
            wave372(); break;
        case 373:
            wave373(); break;
        case 374:
            wave374(); break;
        case 375:
            wave375(); break;
        case 376:
            wave376(); break;
        case 377:
            wave377(); break;
        case 378:
            wave378(); break;
        case 379:
            wave379(); break;
        case 380:
            wave380(); break;
        case 381:
            wave381(); break;
        case 382:
            wave382(); break;
        case 383:
            wave383(); break;
        case 384:
            wave384(); break;
        case 385:
            wave385(); break;
        case 386:
            wave386(); break;
        case 387:
            wave387(); break;
        case 388:
            wave388(); break;
        case 389:
            wave389(); break;
        case 390:
            wave390(); break;
        case 391:
            wave391(); break;
        case 392:
            wave392(); break;
        case 393:
            wave393(); break;
        case 394:
            wave394(); break;
        case 395:
            wave395(); break;
        case 396:
            wave396(); break;
        case 397:
            wave397(); break;
        case 398:
            wave398(); break;
        case 399:
            wave399(); break;
        case 400:
            wave400(); break;
        case 401:
            wave401(); break;
        case 402:
            wave402(); break;
        case 403:
            wave403(); break;
        case 404:
            wave404(); break;
        case 405:
            wave405(); break;
        case 406:
            wave406(); break;
        case 407:
            wave407(); break;
        case 408:
            wave408(); break;
        case 409:
            wave409(); break;
        case 410:
            wave410(); break;
        case 411:
            wave411(); break;
        case 412:
            wave412(); break;
        case 413:
            wave413(); break;
        case 414:
            wave414(); break;
        case 415:
            wave415(); break;
        case 416:
            wave416(); break;
        case 417:
            wave417(); break;
        case 418:
            wave418(); break;
        case 419:
            wave419(); break;
        case 420:
            wave420(); break;
        case 421:
            wave421(); break;
        case 422:
            wave422(); break;
        case 423:
            wave423(); break;
        case 424:
            wave424(); break;
        case 425:
            wave425(); break;
        case 426:
            wave426(); break;
        case 427:
            wave427(); break;
        case 428:
            wave428(); break;
        case 429:
            wave429(); break;
        case 430:
            wave430(); break;
        case 431:
            wave431(); break;
        case 432:
            wave432(); break;
        case 433:
            wave433(); break;
        case 434:
            wave434(); break;
        case 435:
            wave435(); break;
        case 436:
            wave436(); break;
        case 437:
            wave437(); break;
        case 438:
            wave438(); break;
        case 439:
            wave439(); break;
        case 440:
            wave440(); break;
        case 441:
            wave441(); break;
        case 442:
            wave442(); break;
        case 443:
            wave443(); break;
        case 444:
            wave444(); break;
        case 445:
            wave445(); break;
        case 446:
            wave446(); break;
        case 447:
            wave447(); break;
        case 448:
            wave448(); break;
        case 449:
            wave449(); break;
        case 450:
            wave450(); break;
        case 451:
            wave451(); break;
        case 452:
            wave452(); break;
        case 453:
            wave453(); break;
        case 454:
            wave454(); break;
        case 455:
            wave455(); break;
        case 456:
            wave456(); break;
        case 457:
            wave457(); break;
        case 458:
            wave458(); break;
        case 459:
            wave459(); break;
        case 460:
            wave460(); break;
        case 461:
            wave461(); break;
        case 462:
            wave462(); break;
        case 463:
            wave463(); break;
        case 464:
            wave464(); break;
        case 465:
            wave465(); break;
        case 466:
            wave466(); break;
        case 467:
            wave467(); break;
        case 468:
            wave468(); break;
        case 469:
            wave469(); break;
        case 470:
            wave470(); break;
        case 471:
            wave471(); break;
        case 472:
            wave472(); break;
        case 473:
            wave473(); break;
        case 474:
            wave474(); break;
        case 475:
            wave475(); break;
        case 476:
            wave476(); break;
        case 477:
            wave477(); break;
        case 478:
            wave478(); break;
        case 479:
            wave479(); break;
        case 480:
            wave480(); break;
        case 481:
            wave481(); break;
        case 482:
            wave482(); break;
        case 483:
            wave483(); break;
        case 484:
            wave484(); break;
        case 485:
            wave485(); break;
        case 486:
            wave486(); break;
        case 487:
            wave487(); break;
        case 488:
            wave488(); break;
        case 489:
            wave489(); break;
        case 490:
            wave490(); break;
        case 491:
            wave491(); break;
        case 492:
            wave492(); break;
        case 493:
            wave493(); break;
        case 494:
            wave494(); break;
        case 495:
            wave495(); break;
        case 496:
            wave496(); break;
        case 497:
            wave497(); break;
        case 498:
            wave498(); break;
        case 499:
            wave499(); break;
    }
//    std::shuffle(enemiesToSpawn.begin(), enemiesToSpawn.end(), RNG::generator);
}

void Wave::randomEnemies(int amount)
{
    for (int i = 0; i < amount; ++i){
        int roll = RNG::randomNum(0,12);
        switch (roll){
            case 0:
                addCukzotz(); break;
            case 1:
                addDharuer(); break;
            case 2:
                addEnione(); break;
            case 3:
                addEzlotl(); break;
            case 4:
                addHudor(); break;
            case 5:
                addKhyemis(); break;
            case 6:
                addKronus(); break;
            case 7:
                addLoldohr(); break;
            case 8:
                addPhihenar(); break;
            case 9:
                addRihrus(); break;
            case 10:
                addUdall(); break;
            case 11:
                addUesis(); break;
            case 12:
                addZanbris(); break;
        }
    }
}

// private methods
void Wave::wave1()
{
    addDharuer(10);
    spawnIntervalMs = 1000;
//    randomEnemies(5000); spawnIntervalMs = 15;
}

void Wave::wave2()
{
    wave1();
    wave1();
    spawnIntervalMs = 700;
}

void Wave::wave3()
{
    addUesis(10);
    spawnIntervalMs = 1000;
}

void Wave::wave4()
{
    wave3();
    wave3();
    spawnIntervalMs = 700;
}

void Wave::wave5()
{
    wave1();
    wave1();
    wave3();
    spawnIntervalMs = 600;
}

void Wave::wave6()
{
    addKhyemis(25);
    spawnIntervalMs = 750;
}

void Wave::wave7()
{
    wave6();
    wave6();
    spawnIntervalMs = 600;
}

void Wave::wave8()
{
    addUdall(30);
    spawnIntervalMs = 750;
}

void Wave::wave9()
{
    wave6();
    wave8();
    spawnIntervalMs = 700;
}

void Wave::wave10()
{
    addEzlotl(50);
    spawnIntervalMs = 750;
}

void Wave::wave11()
{
    wave10();
    wave10();
    spawnIntervalMs = 600;
}

void Wave::wave12()
{
    addKronus(50);
    spawnIntervalMs = 500;
}

void Wave::wave13()
{
    wave12();
    wave12();
    spawnIntervalMs = 400;
}

void Wave::wave14()
{
    addLoldohr(50);
    addKronus(25);
    spawnIntervalMs = 500;
}

void Wave::wave15()
{
    addPhihenar(50);
    wave14();
    spawnIntervalMs = 500;
}

void Wave::wave16()
{
    addZanbris(75);
    spawnIntervalMs = 500;
}

void Wave::wave17()
{
    wave16();
    wave16();
    spawnIntervalMs = 300;
}

void Wave::wave18()
{
    addRihrus(25);
    spawnIntervalMs = 500;
}

void Wave::wave19()
{
    wave18();
    wave18();
    spawnIntervalMs = 300;
}

void Wave::wave20()
{
    addCukzotz(20);
    addEnione(20);
    addLoldohr(20);
    addKronus(20);
    spawnIntervalMs = 300;
}

void Wave::wave21()
{
    wave20();
    wave20();
    spawnIntervalMs = 150;
}

void Wave::wave22()
{
    addUdall(100);
    spawnIntervalMs = 200;
}

void Wave::wave23()
{
    wave22();
    wave22();
    spawnIntervalMs = 150;
}

void Wave::wave24()
{
    wave20();
    wave22();
    spawnIntervalMs = 150;
}

void Wave::wave25()
{
    addCukzotz(150);
    spawnIntervalMs = 150;
}

void Wave::wave26()
{
    addDharuer(150);
    spawnIntervalMs = 150;
}

void Wave::wave27()
{
    addEnione(150);
    spawnIntervalMs = 150;
}

void Wave::wave28()
{
    addEzlotl(150);
    spawnIntervalMs = 150;
}

void Wave::wave29()
{
    addHudor(150);
    spawnIntervalMs = 150;
}

void Wave::wave30()
{
    addKhyemis(150);
    spawnIntervalMs = 150;
}

void Wave::wave31()
{
    addKronus(150);
    spawnIntervalMs = 150;
}

void Wave::wave32()
{
    addLoldohr(150);
    spawnIntervalMs = 150;
}

void Wave::wave33()
{
    addPhihenar(150);
    spawnIntervalMs = 150;
}

void Wave::wave34()
{
    addRihrus(150);
    spawnIntervalMs = 150;
}

void Wave::wave35()
{
    addUdall(150);
    spawnIntervalMs = 150;
}

void Wave::wave36()
{
    addUesis(150);
    spawnIntervalMs = 150;
}

void Wave::wave37()
{
    addZanbris(150);
    spawnIntervalMs = 150;
}

void Wave::wave38()
{
    wave25();
    wave25();
    spawnIntervalMs = 100;
}

void Wave::wave39()
{
    wave25();
    wave26();
    spawnIntervalMs = 100;
}

void Wave::wave40()
{
    wave27();
    wave28();
    wave29();
    wave30();
    spawnIntervalMs = 75;
}

void Wave::wave41()
{
    wave31();
    wave32();
    wave33();
    wave34();
    spawnIntervalMs = 50;
}

void Wave::wave42()
{
    wave35();
    wave35();
    wave36();
    wave36();
    wave37();
    wave37();
    spawnIntervalMs = 75;
}

void Wave::wave43()
{
    wave38();
    wave39();
    spawnIntervalMs = 100;
}

void Wave::wave44()
{
    wave40();
    wave41();
    wave42();
    spawnIntervalMs = 100;
}

void Wave::wave45()
{
    addKronus(400);
    spawnIntervalMs = 50;
}

void Wave::wave46()
{
    addCukzotz(400);
    spawnIntervalMs = 50;
}

void Wave::wave47()
{
    addPhihenar(400);
    spawnIntervalMs = 50;
}

void Wave::wave48()
{
    addHudor(1000);
    spawnIntervalMs = 50;
}

void Wave::wave49()
{
    addRihrus(750);
    spawnIntervalMs = 50;
}

void Wave::wave50()
{
    addUdall(500);
    spawnIntervalMs = 50;
}

void Wave::wave51()
{
    addUesis(300);
    spawnIntervalMs = 50;
}

void Wave::wave52()
{
    addEzlotl(1000);
    spawnIntervalMs = 50;
}

void Wave::wave53()
{
    addDharuer(500);
    spawnIntervalMs = 50;
}

void Wave::wave54()
{
    addZanbris(500);
    spawnIntervalMs = 50;
}

void Wave::wave55()
{
    addLoldohr(1000);
    spawnIntervalMs = 50;
}

void Wave::wave56()
{
    addKhyemis(500);
    spawnIntervalMs = 50;
}

void Wave::wave57()
{
    addEnione(1500);
    spawnIntervalMs = 50;
}

void Wave::wave58()
{
    randomEnemies(2000);
    spawnIntervalMs = 50;
}

void Wave::wave59()
{
    randomEnemies(2000);
    spawnIntervalMs = 30;
}

void Wave::wave60()
{
    addKronus(2000);
    spawnIntervalMs = 30;
}

void Wave::wave61()
{
    addKronus(3000);
    spawnIntervalMs = 20;
}

void Wave::wave62()
{
    addPhihenar(1500);
    addKhyemis(1500);
    spawnIntervalMs = 20;
}

void Wave::wave63()
{
    addPhihenar(1500);
    addKhyemis(1500);
    spawnIntervalMs = 20;
}

void Wave::wave64()
{
    addEnione(1500);
    addDharuer(1500);
    spawnIntervalMs = 20;
}

void Wave::wave65()
{
    addHudor(2000);
    spawnIntervalMs = 20;
}

void Wave::wave66()
{
    addUdall(3000);
    spawnIntervalMs = 20;
}

void Wave::wave67()
{
    randomEnemies(3000);
    spawnIntervalMs = 20;
}

void Wave::wave68()
{
    addKronus(2000);
    randomEnemies(1000);
    spawnIntervalMs = 20;
}

void Wave::wave69()
{
}

void Wave::wave70()
{
}

void Wave::wave71()
{
}

void Wave::wave72()
{
}

void Wave::wave73()
{
}

void Wave::wave74()
{
}

void Wave::wave75()
{
}

void Wave::wave76()
{
}

void Wave::wave77()
{
}

void Wave::wave78()
{
}

void Wave::wave79()
{
}

void Wave::wave80()
{
}

void Wave::wave81()
{
}

void Wave::wave82()
{
}

void Wave::wave83()
{
}

void Wave::wave84()
{
}

void Wave::wave85()
{
}

void Wave::wave86()
{
}

void Wave::wave87()
{
}

void Wave::wave88()
{
}

void Wave::wave89()
{
}

void Wave::wave90()
{
}

void Wave::wave91()
{
}

void Wave::wave92()
{
}

void Wave::wave93()
{
}

void Wave::wave94()
{
}

void Wave::wave95()
{
}

void Wave::wave96()
{
}

void Wave::wave97()
{
}

void Wave::wave98()
{
}

void Wave::wave99()
{
}

void Wave::wave100()
{
}

void Wave::wave101()
{
}

void Wave::wave102()
{
}

void Wave::wave103()
{
}

void Wave::wave104()
{
}

void Wave::wave105()
{
}

void Wave::wave106()
{
}

void Wave::wave107()
{
}

void Wave::wave108()
{
}

void Wave::wave109()
{
}

void Wave::wave110()
{
}

void Wave::wave111()
{
}

void Wave::wave112()
{
}

void Wave::wave113()
{
}

void Wave::wave114()
{
}

void Wave::wave115()
{
}

void Wave::wave116()
{
}

void Wave::wave117()
{
}

void Wave::wave118()
{
}

void Wave::wave119()
{
}

void Wave::wave120()
{
}

void Wave::wave121()
{
}

void Wave::wave122()
{
}

void Wave::wave123()
{
}

void Wave::wave124()
{
}

void Wave::wave125()
{
}

void Wave::wave126()
{
}

void Wave::wave127()
{
}

void Wave::wave128()
{
}

void Wave::wave129()
{
}

void Wave::wave130()
{
}

void Wave::wave131()
{
}

void Wave::wave132()
{
}

void Wave::wave133()
{
}

void Wave::wave134()
{
}

void Wave::wave135()
{
}

void Wave::wave136()
{
}

void Wave::wave137()
{
}

void Wave::wave138()
{
}

void Wave::wave139()
{
}

void Wave::wave140()
{
}

void Wave::wave141()
{
}

void Wave::wave142()
{
}

void Wave::wave143()
{
}

void Wave::wave144()
{
}

void Wave::wave145()
{
}

void Wave::wave146()
{
}

void Wave::wave147()
{
}

void Wave::wave148()
{
}

void Wave::wave149()
{
}

void Wave::wave150()
{
}

void Wave::wave151()
{
}

void Wave::wave152()
{
}

void Wave::wave153()
{
}

void Wave::wave154()
{
}

void Wave::wave155()
{
}

void Wave::wave156()
{
}

void Wave::wave157()
{
}

void Wave::wave158()
{
}

void Wave::wave159()
{
}

void Wave::wave160()
{
}

void Wave::wave161()
{
}

void Wave::wave162()
{
}

void Wave::wave163()
{
}

void Wave::wave164()
{
}

void Wave::wave165()
{
}

void Wave::wave166()
{
}

void Wave::wave167()
{
}

void Wave::wave168()
{
}

void Wave::wave169()
{
}

void Wave::wave170()
{
}

void Wave::wave171()
{
}

void Wave::wave172()
{
}

void Wave::wave173()
{
}

void Wave::wave174()
{
}

void Wave::wave175()
{
}

void Wave::wave176()
{
}

void Wave::wave177()
{
}

void Wave::wave178()
{
}

void Wave::wave179()
{
}

void Wave::wave180()
{
}

void Wave::wave181()
{
}

void Wave::wave182()
{
}

void Wave::wave183()
{
}

void Wave::wave184()
{
}

void Wave::wave185()
{
}

void Wave::wave186()
{
}

void Wave::wave187()
{
}

void Wave::wave188()
{
}

void Wave::wave189()
{
}

void Wave::wave190()
{
}

void Wave::wave191()
{
}

void Wave::wave192()
{
}

void Wave::wave193()
{
}

void Wave::wave194()
{
}

void Wave::wave195()
{
}

void Wave::wave196()
{
}

void Wave::wave197()
{
}

void Wave::wave198()
{
}

void Wave::wave199()
{
}

void Wave::wave200()
{
}

void Wave::wave201()
{
}

void Wave::wave202()
{
}

void Wave::wave203()
{
}

void Wave::wave204()
{
}

void Wave::wave205()
{
}

void Wave::wave206()
{
}

void Wave::wave207()
{
}

void Wave::wave208()
{
}

void Wave::wave209()
{
}

void Wave::wave210()
{
}

void Wave::wave211()
{
}

void Wave::wave212()
{
}

void Wave::wave213()
{
}

void Wave::wave214()
{
}

void Wave::wave215()
{
}

void Wave::wave216()
{
}

void Wave::wave217()
{
}

void Wave::wave218()
{
}

void Wave::wave219()
{
}

void Wave::wave220()
{
}

void Wave::wave221()
{
}

void Wave::wave222()
{
}

void Wave::wave223()
{
}

void Wave::wave224()
{
}

void Wave::wave225()
{
}

void Wave::wave226()
{
}

void Wave::wave227()
{
}

void Wave::wave228()
{
}

void Wave::wave229()
{
}

void Wave::wave230()
{
}

void Wave::wave231()
{
}

void Wave::wave232()
{
}

void Wave::wave233()
{
}

void Wave::wave234()
{
}

void Wave::wave235()
{
}

void Wave::wave236()
{
}

void Wave::wave237()
{
}

void Wave::wave238()
{
}

void Wave::wave239()
{
}

void Wave::wave240()
{
}

void Wave::wave241()
{
}

void Wave::wave242()
{
}

void Wave::wave243()
{
}

void Wave::wave244()
{
}

void Wave::wave245()
{
}

void Wave::wave246()
{
}

void Wave::wave247()
{
}

void Wave::wave248()
{
}

void Wave::wave249()
{
}

void Wave::wave250()
{
}

void Wave::wave251()
{
}

void Wave::wave252()
{
}

void Wave::wave253()
{
}

void Wave::wave254()
{
}

void Wave::wave255()
{
}

void Wave::wave256()
{
}

void Wave::wave257()
{
}

void Wave::wave258()
{
}

void Wave::wave259()
{
}

void Wave::wave260()
{
}

void Wave::wave261()
{
}

void Wave::wave262()
{
}

void Wave::wave263()
{
}

void Wave::wave264()
{
}

void Wave::wave265()
{
}

void Wave::wave266()
{
}

void Wave::wave267()
{
}

void Wave::wave268()
{
}

void Wave::wave269()
{
}

void Wave::wave270()
{
}

void Wave::wave271()
{
}

void Wave::wave272()
{
}

void Wave::wave273()
{
}

void Wave::wave274()
{
}

void Wave::wave275()
{
}

void Wave::wave276()
{
}

void Wave::wave277()
{
}

void Wave::wave278()
{
}

void Wave::wave279()
{
}

void Wave::wave280()
{
}

void Wave::wave281()
{
}

void Wave::wave282()
{
}

void Wave::wave283()
{
}

void Wave::wave284()
{
}

void Wave::wave285()
{
}

void Wave::wave286()
{
}

void Wave::wave287()
{
}

void Wave::wave288()
{
}

void Wave::wave289()
{
}

void Wave::wave290()
{
}

void Wave::wave291()
{
}

void Wave::wave292()
{
}

void Wave::wave293()
{
}

void Wave::wave294()
{
}

void Wave::wave295()
{
}

void Wave::wave296()
{
}

void Wave::wave297()
{
}

void Wave::wave298()
{
}

void Wave::wave299()
{
}

void Wave::wave300()
{
}

void Wave::wave301()
{
}

void Wave::wave302()
{
}

void Wave::wave303()
{
}

void Wave::wave304()
{
}

void Wave::wave305()
{
}

void Wave::wave306()
{
}

void Wave::wave307()
{
}

void Wave::wave308()
{
}

void Wave::wave309()
{
}

void Wave::wave310()
{
}

void Wave::wave311()
{
}

void Wave::wave312()
{
}

void Wave::wave313()
{
}

void Wave::wave314()
{
}

void Wave::wave315()
{
}

void Wave::wave316()
{
}

void Wave::wave317()
{
}

void Wave::wave318()
{
}

void Wave::wave319()
{
}

void Wave::wave320()
{
}

void Wave::wave321()
{
}

void Wave::wave322()
{
}

void Wave::wave323()
{
}

void Wave::wave324()
{
}

void Wave::wave325()
{
}

void Wave::wave326()
{
}

void Wave::wave327()
{
}

void Wave::wave328()
{
}

void Wave::wave329()
{
}

void Wave::wave330()
{
}

void Wave::wave331()
{
}

void Wave::wave332()
{
}

void Wave::wave333()
{
}

void Wave::wave334()
{
}

void Wave::wave335()
{
}

void Wave::wave336()
{
}

void Wave::wave337()
{
}

void Wave::wave338()
{
}

void Wave::wave339()
{
}

void Wave::wave340()
{
}

void Wave::wave341()
{
}

void Wave::wave342()
{
}

void Wave::wave343()
{
}

void Wave::wave344()
{
}

void Wave::wave345()
{
}

void Wave::wave346()
{
}

void Wave::wave347()
{
}

void Wave::wave348()
{
}

void Wave::wave349()
{
}

void Wave::wave350()
{
}

void Wave::wave351()
{
}

void Wave::wave352()
{
}

void Wave::wave353()
{
}

void Wave::wave354()
{
}

void Wave::wave355()
{
}

void Wave::wave356()
{
}

void Wave::wave357()
{
}

void Wave::wave358()
{
}

void Wave::wave359()
{
}

void Wave::wave360()
{
}

void Wave::wave361()
{
}

void Wave::wave362()
{
}

void Wave::wave363()
{
}

void Wave::wave364()
{
}

void Wave::wave365()
{
}

void Wave::wave366()
{
}

void Wave::wave367()
{
}

void Wave::wave368()
{
}

void Wave::wave369()
{
}

void Wave::wave370()
{
}

void Wave::wave371()
{
}

void Wave::wave372()
{
}

void Wave::wave373()
{
}

void Wave::wave374()
{
}

void Wave::wave375()
{
}

void Wave::wave376()
{
}

void Wave::wave377()
{
}

void Wave::wave378()
{
}

void Wave::wave379()
{
}

void Wave::wave380()
{
}

void Wave::wave381()
{
}

void Wave::wave382()
{
}

void Wave::wave383()
{
}

void Wave::wave384()
{
}

void Wave::wave385()
{
}

void Wave::wave386()
{
}

void Wave::wave387()
{
}

void Wave::wave388()
{
}

void Wave::wave389()
{
}

void Wave::wave390()
{
}

void Wave::wave391()
{
}

void Wave::wave392()
{
}

void Wave::wave393()
{
}

void Wave::wave394()
{
}

void Wave::wave395()
{
}

void Wave::wave396()
{
}

void Wave::wave397()
{
}

void Wave::wave398()
{
}

void Wave::wave399()
{
}

void Wave::wave400()
{
}

void Wave::wave401()
{
}

void Wave::wave402()
{
}

void Wave::wave403()
{
}

void Wave::wave404()
{
}

void Wave::wave405()
{
}

void Wave::wave406()
{
}

void Wave::wave407()
{
}

void Wave::wave408()
{
}

void Wave::wave409()
{
}

void Wave::wave410()
{
}

void Wave::wave411()
{
}

void Wave::wave412()
{
}

void Wave::wave413()
{
}

void Wave::wave414()
{
}

void Wave::wave415()
{
}

void Wave::wave416()
{
}

void Wave::wave417()
{
}

void Wave::wave418()
{
}

void Wave::wave419()
{
}

void Wave::wave420()
{
}

void Wave::wave421()
{
}

void Wave::wave422()
{
}

void Wave::wave423()
{
}

void Wave::wave424()
{
}

void Wave::wave425()
{
}

void Wave::wave426()
{
}

void Wave::wave427()
{
}

void Wave::wave428()
{
}

void Wave::wave429()
{
}

void Wave::wave430()
{
}

void Wave::wave431()
{
}

void Wave::wave432()
{
}

void Wave::wave433()
{
}

void Wave::wave434()
{
}

void Wave::wave435()
{
}

void Wave::wave436()
{
}

void Wave::wave437()
{
}

void Wave::wave438()
{
}

void Wave::wave439()
{
}

void Wave::wave440()
{
}

void Wave::wave441()
{
}

void Wave::wave442()
{
}

void Wave::wave443()
{
}

void Wave::wave444()
{
}

void Wave::wave445()
{
}

void Wave::wave446()
{
}

void Wave::wave447()
{
}

void Wave::wave448()
{
}

void Wave::wave449()
{
}

void Wave::wave450()
{
}

void Wave::wave451()
{
}

void Wave::wave452()
{
}

void Wave::wave453()
{
}

void Wave::wave454()
{
}

void Wave::wave455()
{
}

void Wave::wave456()
{
}

void Wave::wave457()
{
}

void Wave::wave458()
{
}

void Wave::wave459()
{
}

void Wave::wave460()
{
}

void Wave::wave461()
{
}

void Wave::wave462()
{
}

void Wave::wave463()
{
}

void Wave::wave464()
{
}

void Wave::wave465()
{
}

void Wave::wave466()
{
}

void Wave::wave467()
{
}

void Wave::wave468()
{
}

void Wave::wave469()
{
}

void Wave::wave470()
{
}

void Wave::wave471()
{
}

void Wave::wave472()
{
}

void Wave::wave473()
{
}

void Wave::wave474()
{
}

void Wave::wave475()
{
}

void Wave::wave476()
{
}

void Wave::wave477()
{
}

void Wave::wave478()
{
}

void Wave::wave479()
{
}

void Wave::wave480()
{
}

void Wave::wave481()
{
}

void Wave::wave482()
{
}

void Wave::wave483()
{
}

void Wave::wave484()
{
}

void Wave::wave485()
{
}

void Wave::wave486()
{
}

void Wave::wave487()
{
}

void Wave::wave488()
{
}

void Wave::wave489()
{
}

void Wave::wave490()
{
}

void Wave::wave491()
{
}

void Wave::wave492()
{
}

void Wave::wave493()
{
}

void Wave::wave494()
{
}

void Wave::wave495()
{
}

void Wave::wave496()
{
}

void Wave::wave497()
{
}

void Wave::wave498()
{
}

void Wave::wave499()
{
}