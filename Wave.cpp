#include "Wave.h"
#include "CukzotzEnemy.h"
#include "DharuerEnemy.h"
#include "EnioneEnemy.h"
#include "EzlotlEnemy.h"
#include "HudorEnemy.h"
#include "KhyemisEnemy.h"
#include "KronusEnemy.h"
#include "LoldohrEnemy.h"
#include "PhihenarEnemy.h"
#include "RihrusEnemy.h"
#include "UdallEnemy.h"
#include "UesisEnemy.h"
#include "ZanbrisEnemy.h"

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
std::unordered_set<Enemy*> Wave::getEnemyList() const
{
    return enemiesToSpawn;
}

int Wave::getSpawnIntervalMs() const
{
    return spawnIntervalMs;
}

//void Wave::popBackEnemy()
//{
//    enemiesToSpawn.pop_back();
//}

// private methods
void Wave::addCukzotz(int amount)
{
    for (int i = 0; i < amount; ++i){
        CukzotzEnemy* enemy = new CukzotzEnemy(level);
        enemiesToSpawn.insert(enemy);
    }
}
void Wave::addDharuer(int amount)
{
    for (int i = 0; i < amount; ++i){
        DharuerEnemy* enemy = new DharuerEnemy(level);
        enemiesToSpawn.insert(enemy);
    }
}

void Wave::addEnione(int amount)
{
    for (int i = 0; i < amount; ++i){
        EnioneEnemy* enemy = new EnioneEnemy(level);
        enemiesToSpawn.insert(enemy);
    }
}

void Wave::addEzlotl(int amount)
{
    for (int i = 0; i < amount; ++i){
        EzlotlEnemy* enemy = new EzlotlEnemy(level);
        enemiesToSpawn.insert(enemy);
    }
}

void Wave::addHudor(int amount)
{
    for (int i = 0; i < amount; ++i){
        HudorEnemy* enemy = new HudorEnemy(level);
        enemiesToSpawn.insert(enemy);
    }
}

void Wave::addKhyemis(int amount)
{
    for (int i = 0; i < amount; ++i){
        KhyemisEnemy* enemy = new KhyemisEnemy(level);
        enemiesToSpawn.insert(enemy);
    }
}

void Wave::addKronus(int amount)
{
    for (int i = 0; i < amount; ++i){
        KronusEnemy* enemy = new KronusEnemy(level);
        enemiesToSpawn.insert(enemy);
    }
}

void Wave::addLoldohr(int amount)
{
    for (int i = 0; i < amount; ++i){
        LoldohrEnemy* enemy = new LoldohrEnemy(level);
        enemiesToSpawn.insert(enemy);
    }
}

void Wave::addPhihenar(int amount)
{
    for (int i = 0; i < amount; ++i){
        PhihenarEnemy* enemy = new PhihenarEnemy(level);
        enemiesToSpawn.insert(enemy);
    }
}

void Wave::addRihrus(int amount)
{
    for (int i = 0; i < amount; ++i){
        RihrusEnemy* enemy = new RihrusEnemy(level);
        enemiesToSpawn.insert(enemy);
    }
}

void Wave::addUdall(int amount)
{
    for (int i = 0; i < amount; ++i){
        UdallEnemy* enemy = new UdallEnemy(level);
        enemiesToSpawn.insert(enemy);
    }
}

void Wave::addUesis(int amount)
{
    for (int i = 0; i < amount; ++i){
        UesisEnemy* enemy = new UesisEnemy(level);
        enemiesToSpawn.insert(enemy);
    }
}

void Wave::addZanbris(int amount)
{
    for (int i = 0; i < amount; ++i){
        ZanbrisEnemy* enemy = new ZanbrisEnemy(level);
        enemiesToSpawn.insert(enemy);
    }
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
        case 4:
            wave4(); return;
        case 5:
            wave5(); return;
        case 6:
            wave6(); return;
        case 7:
            wave7(); return;
        case 8:
            wave8(); return;
        case 9:
            wave9(); return;
        case 10:
            wave10(); return;
        case 11:
            wave11(); return;
        case 12:
            wave12(); return;
        case 13:
            wave13(); return;
        case 14:
            wave14(); return;
        case 15:
            wave15(); return;
        case 16:
            wave16(); return;
        case 17:
            wave17(); return;
        case 18:
            wave18(); return;
        case 19:
            wave19(); return;
        case 20:
            wave20(); return;
        case 21:
            wave21(); return;
        case 22:
            wave22(); return;
        case 23:
            wave23(); return;
        case 24:
            wave24(); return;
        case 25:
            wave25(); return;
        case 26:
            wave26(); return;
        case 27:
            wave27(); return;
        case 28:
            wave28(); return;
        case 29:
            wave29(); return;
        case 30:
            wave30(); return;
        case 31:
            wave31(); return;
        case 32:
            wave32(); return;
        case 33:
            wave33(); return;
        case 34:
            wave34(); return;
        case 35:
            wave35(); return;
        case 36:
            wave36(); return;
        case 37:
            wave37(); return;
        case 38:
            wave38(); return;
        case 39:
            wave39(); return;
        case 40:
            wave40(); return;
        case 41:
            wave41(); return;
        case 42:
            wave42(); return;
        case 43:
            wave43(); return;
        case 44:
            wave44(); return;
        case 45:
            wave45(); return;
        case 46:
            wave46(); return;
        case 47:
            wave47(); return;
        case 48:
            wave48(); return;
        case 49:
            wave49(); return;
        case 50:
            wave50(); return;
        case 51:
            wave51(); return;
        case 52:
            wave52(); return;
        case 53:
            wave53(); return;
        case 54:
            wave54(); return;
        case 55:
            wave55(); return;
        case 56:
            wave56(); return;
        case 57:
            wave57(); return;
        case 58:
            wave58(); return;
        case 59:
            wave59(); return;
        case 60:
            wave60(); return;
        case 61:
            wave61(); return;
        case 62:
            wave62(); return;
        case 63:
            wave63(); return;
        case 64:
            wave64(); return;
        case 65:
            wave65(); return;
        case 66:
            wave66(); return;
        case 67:
            wave67(); return;
        case 68:
            wave68(); return;
        case 69:
            wave69(); return;
        case 70:
            wave70(); return;
        case 71:
            wave71(); return;
        case 72:
            wave72(); return;
        case 73:
            wave73(); return;
        case 74:
            wave74(); return;
        case 75:
            wave75(); return;
        case 76:
            wave76(); return;
        case 77:
            wave77(); return;
        case 78:
            wave78(); return;
        case 79:
            wave79(); return;
        case 80:
            wave80(); return;
        case 81:
            wave81(); return;
        case 82:
            wave82(); return;
        case 83:
            wave83(); return;
        case 84:
            wave84(); return;
        case 85:
            wave85(); return;
        case 86:
            wave86(); return;
        case 87:
            wave87(); return;
        case 88:
            wave88(); return;
        case 89:
            wave89(); return;
        case 90:
            wave90(); return;
        case 91:
            wave91(); return;
        case 92:
            wave92(); return;
        case 93:
            wave93(); return;
        case 94:
            wave94(); return;
        case 95:
            wave95(); return;
        case 96:
            wave96(); return;
        case 97:
            wave97(); return;
        case 98:
            wave98(); return;
        case 99:
            wave99(); return;
        case 100:
            wave100(); return;
        case 101:
            wave101(); return;
        case 102:
            wave102(); return;
        case 103:
            wave103(); return;
        case 104:
            wave104(); return;
        case 105:
            wave105(); return;
        case 106:
            wave106(); return;
        case 107:
            wave107(); return;
        case 108:
            wave108(); return;
        case 109:
            wave109(); return;
        case 110:
            wave110(); return;
        case 111:
            wave111(); return;
        case 112:
            wave112(); return;
        case 113:
            wave113(); return;
        case 114:
            wave114(); return;
        case 115:
            wave115(); return;
        case 116:
            wave116(); return;
        case 117:
            wave117(); return;
        case 118:
            wave118(); return;
        case 119:
            wave119(); return;
        case 120:
            wave120(); return;
        case 121:
            wave121(); return;
        case 122:
            wave122(); return;
        case 123:
            wave123(); return;
        case 124:
            wave124(); return;
        case 125:
            wave125(); return;
        case 126:
            wave126(); return;
        case 127:
            wave127(); return;
        case 128:
            wave128(); return;
        case 129:
            wave129(); return;
        case 130:
            wave130(); return;
        case 131:
            wave131(); return;
        case 132:
            wave132(); return;
        case 133:
            wave133(); return;
        case 134:
            wave134(); return;
        case 135:
            wave135(); return;
        case 136:
            wave136(); return;
        case 137:
            wave137(); return;
        case 138:
            wave138(); return;
        case 139:
            wave139(); return;
        case 140:
            wave140(); return;
        case 141:
            wave141(); return;
        case 142:
            wave142(); return;
        case 143:
            wave143(); return;
        case 144:
            wave144(); return;
        case 145:
            wave145(); return;
        case 146:
            wave146(); return;
        case 147:
            wave147(); return;
        case 148:
            wave148(); return;
        case 149:
            wave149(); return;
        case 150:
            wave150(); return;
        case 151:
            wave151(); return;
        case 152:
            wave152(); return;
        case 153:
            wave153(); return;
        case 154:
            wave154(); return;
        case 155:
            wave155(); return;
        case 156:
            wave156(); return;
        case 157:
            wave157(); return;
        case 158:
            wave158(); return;
        case 159:
            wave159(); return;
        case 160:
            wave160(); return;
        case 161:
            wave161(); return;
        case 162:
            wave162(); return;
        case 163:
            wave163(); return;
        case 164:
            wave164(); return;
        case 165:
            wave165(); return;
        case 166:
            wave166(); return;
        case 167:
            wave167(); return;
        case 168:
            wave168(); return;
        case 169:
            wave169(); return;
        case 170:
            wave170(); return;
        case 171:
            wave171(); return;
        case 172:
            wave172(); return;
        case 173:
            wave173(); return;
        case 174:
            wave174(); return;
        case 175:
            wave175(); return;
        case 176:
            wave176(); return;
        case 177:
            wave177(); return;
        case 178:
            wave178(); return;
        case 179:
            wave179(); return;
        case 180:
            wave180(); return;
        case 181:
            wave181(); return;
        case 182:
            wave182(); return;
        case 183:
            wave183(); return;
        case 184:
            wave184(); return;
        case 185:
            wave185(); return;
        case 186:
            wave186(); return;
        case 187:
            wave187(); return;
        case 188:
            wave188(); return;
        case 189:
            wave189(); return;
        case 190:
            wave190(); return;
        case 191:
            wave191(); return;
        case 192:
            wave192(); return;
        case 193:
            wave193(); return;
        case 194:
            wave194(); return;
        case 195:
            wave195(); return;
        case 196:
            wave196(); return;
        case 197:
            wave197(); return;
        case 198:
            wave198(); return;
        case 199:
            wave199(); return;
        case 200:
            wave200(); return;
        case 201:
            wave201(); return;
        case 202:
            wave202(); return;
        case 203:
            wave203(); return;
        case 204:
            wave204(); return;
        case 205:
            wave205(); return;
        case 206:
            wave206(); return;
        case 207:
            wave207(); return;
        case 208:
            wave208(); return;
        case 209:
            wave209(); return;
        case 210:
            wave210(); return;
        case 211:
            wave211(); return;
        case 212:
            wave212(); return;
        case 213:
            wave213(); return;
        case 214:
            wave214(); return;
        case 215:
            wave215(); return;
        case 216:
            wave216(); return;
        case 217:
            wave217(); return;
        case 218:
            wave218(); return;
        case 219:
            wave219(); return;
        case 220:
            wave220(); return;
        case 221:
            wave221(); return;
        case 222:
            wave222(); return;
        case 223:
            wave223(); return;
        case 224:
            wave224(); return;
        case 225:
            wave225(); return;
        case 226:
            wave226(); return;
        case 227:
            wave227(); return;
        case 228:
            wave228(); return;
        case 229:
            wave229(); return;
        case 230:
            wave230(); return;
        case 231:
            wave231(); return;
        case 232:
            wave232(); return;
        case 233:
            wave233(); return;
        case 234:
            wave234(); return;
        case 235:
            wave235(); return;
        case 236:
            wave236(); return;
        case 237:
            wave237(); return;
        case 238:
            wave238(); return;
        case 239:
            wave239(); return;
        case 240:
            wave240(); return;
        case 241:
            wave241(); return;
        case 242:
            wave242(); return;
        case 243:
            wave243(); return;
        case 244:
            wave244(); return;
        case 245:
            wave245(); return;
        case 246:
            wave246(); return;
        case 247:
            wave247(); return;
        case 248:
            wave248(); return;
        case 249:
            wave249(); return;
        case 250:
            wave250(); return;
        case 251:
            wave251(); return;
        case 252:
            wave252(); return;
        case 253:
            wave253(); return;
        case 254:
            wave254(); return;
        case 255:
            wave255(); return;
        case 256:
            wave256(); return;
        case 257:
            wave257(); return;
        case 258:
            wave258(); return;
        case 259:
            wave259(); return;
        case 260:
            wave260(); return;
        case 261:
            wave261(); return;
        case 262:
            wave262(); return;
        case 263:
            wave263(); return;
        case 264:
            wave264(); return;
        case 265:
            wave265(); return;
        case 266:
            wave266(); return;
        case 267:
            wave267(); return;
        case 268:
            wave268(); return;
        case 269:
            wave269(); return;
        case 270:
            wave270(); return;
        case 271:
            wave271(); return;
        case 272:
            wave272(); return;
        case 273:
            wave273(); return;
        case 274:
            wave274(); return;
        case 275:
            wave275(); return;
        case 276:
            wave276(); return;
        case 277:
            wave277(); return;
        case 278:
            wave278(); return;
        case 279:
            wave279(); return;
        case 280:
            wave280(); return;
        case 281:
            wave281(); return;
        case 282:
            wave282(); return;
        case 283:
            wave283(); return;
        case 284:
            wave284(); return;
        case 285:
            wave285(); return;
        case 286:
            wave286(); return;
        case 287:
            wave287(); return;
        case 288:
            wave288(); return;
        case 289:
            wave289(); return;
        case 290:
            wave290(); return;
        case 291:
            wave291(); return;
        case 292:
            wave292(); return;
        case 293:
            wave293(); return;
        case 294:
            wave294(); return;
        case 295:
            wave295(); return;
        case 296:
            wave296(); return;
        case 297:
            wave297(); return;
        case 298:
            wave298(); return;
        case 299:
            wave299(); return;
        case 300:
            wave300(); return;
        case 301:
            wave301(); return;
        case 302:
            wave302(); return;
        case 303:
            wave303(); return;
        case 304:
            wave304(); return;
        case 305:
            wave305(); return;
        case 306:
            wave306(); return;
        case 307:
            wave307(); return;
        case 308:
            wave308(); return;
        case 309:
            wave309(); return;
        case 310:
            wave310(); return;
        case 311:
            wave311(); return;
        case 312:
            wave312(); return;
        case 313:
            wave313(); return;
        case 314:
            wave314(); return;
        case 315:
            wave315(); return;
        case 316:
            wave316(); return;
        case 317:
            wave317(); return;
        case 318:
            wave318(); return;
        case 319:
            wave319(); return;
        case 320:
            wave320(); return;
        case 321:
            wave321(); return;
        case 322:
            wave322(); return;
        case 323:
            wave323(); return;
        case 324:
            wave324(); return;
        case 325:
            wave325(); return;
        case 326:
            wave326(); return;
        case 327:
            wave327(); return;
        case 328:
            wave328(); return;
        case 329:
            wave329(); return;
        case 330:
            wave330(); return;
        case 331:
            wave331(); return;
        case 332:
            wave332(); return;
        case 333:
            wave333(); return;
        case 334:
            wave334(); return;
        case 335:
            wave335(); return;
        case 336:
            wave336(); return;
        case 337:
            wave337(); return;
        case 338:
            wave338(); return;
        case 339:
            wave339(); return;
        case 340:
            wave340(); return;
        case 341:
            wave341(); return;
        case 342:
            wave342(); return;
        case 343:
            wave343(); return;
        case 344:
            wave344(); return;
        case 345:
            wave345(); return;
        case 346:
            wave346(); return;
        case 347:
            wave347(); return;
        case 348:
            wave348(); return;
        case 349:
            wave349(); return;
        case 350:
            wave350(); return;
        case 351:
            wave351(); return;
        case 352:
            wave352(); return;
        case 353:
            wave353(); return;
        case 354:
            wave354(); return;
        case 355:
            wave355(); return;
        case 356:
            wave356(); return;
        case 357:
            wave357(); return;
        case 358:
            wave358(); return;
        case 359:
            wave359(); return;
        case 360:
            wave360(); return;
        case 361:
            wave361(); return;
        case 362:
            wave362(); return;
        case 363:
            wave363(); return;
        case 364:
            wave364(); return;
        case 365:
            wave365(); return;
        case 366:
            wave366(); return;
        case 367:
            wave367(); return;
        case 368:
            wave368(); return;
        case 369:
            wave369(); return;
        case 370:
            wave370(); return;
        case 371:
            wave371(); return;
        case 372:
            wave372(); return;
        case 373:
            wave373(); return;
        case 374:
            wave374(); return;
        case 375:
            wave375(); return;
        case 376:
            wave376(); return;
        case 377:
            wave377(); return;
        case 378:
            wave378(); return;
        case 379:
            wave379(); return;
        case 380:
            wave380(); return;
        case 381:
            wave381(); return;
        case 382:
            wave382(); return;
        case 383:
            wave383(); return;
        case 384:
            wave384(); return;
        case 385:
            wave385(); return;
        case 386:
            wave386(); return;
        case 387:
            wave387(); return;
        case 388:
            wave388(); return;
        case 389:
            wave389(); return;
        case 390:
            wave390(); return;
        case 391:
            wave391(); return;
        case 392:
            wave392(); return;
        case 393:
            wave393(); return;
        case 394:
            wave394(); return;
        case 395:
            wave395(); return;
        case 396:
            wave396(); return;
        case 397:
            wave397(); return;
        case 398:
            wave398(); return;
        case 399:
            wave399(); return;
        case 400:
            wave400(); return;
        case 401:
            wave401(); return;
        case 402:
            wave402(); return;
        case 403:
            wave403(); return;
        case 404:
            wave404(); return;
        case 405:
            wave405(); return;
        case 406:
            wave406(); return;
        case 407:
            wave407(); return;
        case 408:
            wave408(); return;
        case 409:
            wave409(); return;
        case 410:
            wave410(); return;
        case 411:
            wave411(); return;
        case 412:
            wave412(); return;
        case 413:
            wave413(); return;
        case 414:
            wave414(); return;
        case 415:
            wave415(); return;
        case 416:
            wave416(); return;
        case 417:
            wave417(); return;
        case 418:
            wave418(); return;
        case 419:
            wave419(); return;
        case 420:
            wave420(); return;
        case 421:
            wave421(); return;
        case 422:
            wave422(); return;
        case 423:
            wave423(); return;
        case 424:
            wave424(); return;
        case 425:
            wave425(); return;
        case 426:
            wave426(); return;
        case 427:
            wave427(); return;
        case 428:
            wave428(); return;
        case 429:
            wave429(); return;
        case 430:
            wave430(); return;
        case 431:
            wave431(); return;
        case 432:
            wave432(); return;
        case 433:
            wave433(); return;
        case 434:
            wave434(); return;
        case 435:
            wave435(); return;
        case 436:
            wave436(); return;
        case 437:
            wave437(); return;
        case 438:
            wave438(); return;
        case 439:
            wave439(); return;
        case 440:
            wave440(); return;
        case 441:
            wave441(); return;
        case 442:
            wave442(); return;
        case 443:
            wave443(); return;
        case 444:
            wave444(); return;
        case 445:
            wave445(); return;
        case 446:
            wave446(); return;
        case 447:
            wave447(); return;
        case 448:
            wave448(); return;
        case 449:
            wave449(); return;
        case 450:
            wave450(); return;
        case 451:
            wave451(); return;
        case 452:
            wave452(); return;
        case 453:
            wave453(); return;
        case 454:
            wave454(); return;
        case 455:
            wave455(); return;
        case 456:
            wave456(); return;
        case 457:
            wave457(); return;
        case 458:
            wave458(); return;
        case 459:
            wave459(); return;
        case 460:
            wave460(); return;
        case 461:
            wave461(); return;
        case 462:
            wave462(); return;
        case 463:
            wave463(); return;
        case 464:
            wave464(); return;
        case 465:
            wave465(); return;
        case 466:
            wave466(); return;
        case 467:
            wave467(); return;
        case 468:
            wave468(); return;
        case 469:
            wave469(); return;
        case 470:
            wave470(); return;
        case 471:
            wave471(); return;
        case 472:
            wave472(); return;
        case 473:
            wave473(); return;
        case 474:
            wave474(); return;
        case 475:
            wave475(); return;
        case 476:
            wave476(); return;
        case 477:
            wave477(); return;
        case 478:
            wave478(); return;
        case 479:
            wave479(); return;
        case 480:
            wave480(); return;
        case 481:
            wave481(); return;
        case 482:
            wave482(); return;
        case 483:
            wave483(); return;
        case 484:
            wave484(); return;
        case 485:
            wave485(); return;
        case 486:
            wave486(); return;
        case 487:
            wave487(); return;
        case 488:
            wave488(); return;
        case 489:
            wave489(); return;
        case 490:
            wave490(); return;
        case 491:
            wave491(); return;
        case 492:
            wave492(); return;
        case 493:
            wave493(); return;
        case 494:
            wave494(); return;
        case 495:
            wave495(); return;
        case 496:
            wave496(); return;
        case 497:
            wave497(); return;
        case 498:
            wave498(); return;
        case 499:
            wave499(); return;
    }
}

// private methods
void Wave::wave1()
{
    addZanbris(5);
    spawnIntervalMs = 500;
}

void Wave::wave2()
{
    wave1();
    wave1();
    spawnIntervalMs = 300;
}

void Wave::wave3()
{
    addUesis(10);
    spawnIntervalMs = 1000;
}

void Wave::wave4()
{
    addUesis(15);
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
    addKhyemis(10);
    spawnIntervalMs = 500;
}

void Wave::wave7()
{
    wave6();
    wave6();
    spawnIntervalMs = 300;;
}

void Wave::wave8()
{
    addUdall(10);
    spawnIntervalMs = 1000;
}

void Wave::wave9()
{
    wave8();
    wave8();
    spawnIntervalMs = 800;
}

void Wave::wave10()
{
    addEzlotl(10);
    spawnIntervalMs = 1000;
}

void Wave::wave11()
{
    wave10();
    wave10();
    spawnIntervalMs = 700;
}

void Wave::wave12()
{
    addKronus(10);
    spawnIntervalMs = 1000;
}

void Wave::wave13()
{
    wave12();
    wave12();
    spawnIntervalMs = 600;
}

void Wave::wave14()
{
    wave13();
    wave13();
    spawnIntervalMs = 500;
}

void Wave::wave15()
{
    wave1();
    wave2();
    wave3();
    wave4();
    spawnIntervalMs = 500;
}

void Wave::wave16()
{
    addPhihenar(25);
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
    wave15();
    wave19();
    wave19();
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
    addUdall(50);
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
    wave1();
    wave2();
    wave3();
    wave4();
    wave5();
    spawnIntervalMs = 150;
}

void Wave::wave25()
{
    addCukzotz(100);
    spawnIntervalMs = 150;
}

void Wave::wave26()
{
    addDharuer(100);
    spawnIntervalMs = 150;
}

void Wave::wave27()
{
    addEnione(100);
    spawnIntervalMs = 150;
}

void Wave::wave28()
{
    addEzlotl(100);
    spawnIntervalMs = 150;
}

void Wave::wave29()
{
    addHudor(100);
    spawnIntervalMs = 150;
}

void Wave::wave30()
{
    addKhyemis(100);
    spawnIntervalMs = 150;
}

void Wave::wave31()
{
    addKronus(100);
    spawnIntervalMs = 150;
}

void Wave::wave32()
{
    addLoldohr(100);
    spawnIntervalMs = 150;
}

void Wave::wave33()
{
    addPhihenar(100);
    spawnIntervalMs = 150;
}

void Wave::wave34()
{
    addRihrus(100);
    spawnIntervalMs = 150;
}

void Wave::wave35()
{
    addUdall(100);
    spawnIntervalMs = 150;
}

void Wave::wave36()
{
    addUesis(100);
    spawnIntervalMs = 150;
}

void Wave::wave37()
{
    addZanbris(100);
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
    addKronus(200);
    spawnIntervalMs = 50;
}

void Wave::wave46()
{
    addCukzotz(300);
    spawnIntervalMs = 50;
}

void Wave::wave47()
{
    addPhihenar(350);
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
}

void Wave::wave59()
{
}

void Wave::wave60()
{
}

void Wave::wave61()
{
}

void Wave::wave62()
{
}

void Wave::wave63()
{
}

void Wave::wave64()
{
}

void Wave::wave65()
{
}

void Wave::wave66()
{
}

void Wave::wave67()
{
}

void Wave::wave68()
{
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