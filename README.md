M5Stack JpgLoopAnime Simple.ver
===

M5Stack用 JPEG ループアニメーション(シンプル版)

## Description
  
追記：haratta27  
Simple.Ver では、アニメーションがループ再生される機能だけを残し、できるだけシンプル化しました。  
JpgLoopAnime.inoファイルには、追記として、動作内容を簡単にコメントしました。  
image_Directory内にサンプル画像を置きます。動作確認用にお使いください。  
詳細情報はこちら。 https://harattamouse.hatenablog.com/entry/2020/03/02/m5stack-parapara-manga  
  
M5StackのSDカードで指定フォルダ内にあるJPEGをループ再生します  
描画はデュアルコア使用とDMA転送により高速に実行します。  
  
JpgLoopAnime.ino を開き、imageDirに画像ファイルのあるディレクトリ名を指定してビルドしてください。  
  
なおディレクトリ内の全ての画像をオンメモリしますので、容量にご注意ください。読込中にメモリが足りなくなった場合は読込みをスキップします。  
  
  
## Licence

[MIT](https://github.com/lovyan03/M5Stack_JpgLoopAnime/blob/master/LICENSE)  

## Author

Orignal : [lovyan03](https://twitter.com/lovyan03)  
Arranger: [haratta27](https:/twitter.com/harattaMouse)
