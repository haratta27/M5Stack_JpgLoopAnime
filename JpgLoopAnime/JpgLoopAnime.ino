//==================================================================================
// 2020/03/08 M5Stack_JpgLoopAnime Simple.ver
// Arranger:haratta27
// Orignal: lovyan03 / https://github.com/lovyan03/M5Stack_JpgLoopAnime
//==================================================================================
#pragma GCC optimize ("O3")

#include <M5Stack.h>
//#include <M5StackUpdater.h>     // https://github.com/tobozo/M5Stack-SD-Updater/
#include <esp_heap_alloc_caps.h>
#include <vector>
#include "src/MainClass.h"
#include "src/DMADrawer.h"

MainClass main;

// ここで画像ファイルのディレクトリ名を指定する
std::vector<String> imageDirs = {"/image_dirname1", "/image_dirname2"};

uint8_t dirIndex = 0;
std::vector<const uint8_t*> fbuf;  //画像情報
std::vector<int32_t> fbufsize;     //サイズ情報
uint32_t fpsCount = 0, fpsSec = 0;

// SD Card 中の Jpg data を fbuf,fbufsize にコピーする。
bool loadImages(const String& path)
{
  bool res = false;
  if (!fbuf.empty()) {
    for (int i = 0; i < fbuf.size(); i++) free(const_cast<uint8_t*>(fbuf[i]));
  }
  fbuf.clear();
  fbufsize.clear();
  Serial.println(path);
  File root = SD.open(path);
  File file = root.openNextFile();
  uint8_t* tmp;
  while (file) {
    tmp = (uint8_t*)pvPortMallocCaps(file.size(), MALLOC_CAP_DEFAULT);
    if (tmp > 0) {
      file.read(tmp, file.size());
      fbufsize.push_back(file.size());
      fbuf.push_back(tmp);
      res = true;
    }
    file = root.openNextFile();
  }
  return res;
}

void setup() {

  M5.begin();
  dacWrite(25,0); //Speaker OFF

#ifdef __M5STACKUPDATER_H
  if(digitalRead(BUTTON_A_PIN) == 0) {
     Serial.println("Will Load menu binary");
     updateFromFS(SD);
     ESP.restart();
  }
#endif

  main.setup(&M5.Lcd);

  fbuf.clear();
  fbufsize.clear();
  loadImages(imageDirs[dirIndex]);

}

void loop() {
  for (int i = 0; i < fbuf.size(); i++) {

    M5.update();

    //Directory Select by Button
    if (M5.BtnB.wasPressed() || M5.BtnC.wasPressed()) {
      main.wait();
      do {
        dirIndex = (dirIndex + (M5.BtnC.wasPressed() ? 1 : M5.BtnB.wasPressed() ? imageDirs.size() - 1 : 0)) % imageDirs.size();
      } while (!loadImages(imageDirs[dirIndex]));
      M5.Lcd.fillRect(0,0,M5.Lcd.width(),M5.Lcd.height(),0);
      break;
    }

    //Drawing Image
    //M5.Lcd.drawJpg(fbuf[i], fbufsize[i]);     //<= drawJpg (normal) 
    main.drawJpg(fbuf[i], fbufsize[i]);       // <= drawJpg (DMA transfer)

    //Count Frame rate
    fpsCount++;
    if (fpsSec != millis() / 1000) {
      fpsSec = millis() / 1000;
      Serial.printf("fps:%d\r\n",fpsCount);
      fpsCount = 0;
    }
  }

}
