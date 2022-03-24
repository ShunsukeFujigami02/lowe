retro/loweの使い方
セットアップの方法
cd ~/retro
./setup.sh
cd ~/retro/lowe
./setup.sh
ソースコードはlowe/source内にある

ビルドするとき
cd ~/retro/lowe/build
cmake ../source
make

現在はtequilaサーバに入っています。サーバを変えたときに動くようには出来ていないので、
その場合は適宜ファイル内のpass名を変換するなどして対応してください。また、入れ直す場合は、
root,geant4,WCSim,python,TinyTIFF,fmathをダウンロードしてください。

再構成の順番
WCSim->Goodness->Likelihood->Minimize->Energy
WCSimはGeant4を利用して作られたシミュレーションソフトです。SKやHKなどジオメトリを
変えて走らせることが出来ます。（詳しくはWCSimのドキュメントを見てください）
Goodnessは、荷電粒子の位置と時間を初期段階で再構成するアルゴリズムです。
位置と時間を合わせた4次元の点を格子状に探索し、用意した関数の値が最大となる点を記録しています。
探索範囲や用いる関数は変えることが出来るようになっています。（新しく作るときはソースコードを書き換える必要あり）
Likelihoodは、荷電粒子の方向を初期段階で再構成するアルゴリズムです。
costhetaとphiの2つからなる2次元の点を格子状に探索し、用意した関数の値が最大となる点を記録しています。
Minimizeは、位置、時間、方向の最終段階による再構成のアルゴリズムです。
Minuitと呼ばれる勾配法を用いた最小化を行って、より精密な再構成を行っています。
Energyはエネルギーの再構成です。記録をしているのは実質的なチェレンコフ光の数になっており、これをエネルギーに変換します。
これらの方法は自分の論文（2021,修士,タイトル：水チェレンコフ検出器への再帰反射材の応用研究、久世研のサイトにあるはず）に詳しく載っているのでそっちを参照してください。

WCSimを走らせるときはlowe/WCSimLauncherに入り、Launcher_exe.shやLauncher_exe_1dim.shなどを
走らせる
条件を変えたいときは、それらのファイルの内部の変数を変更する
対応してないものはLauncher_contents.shやwcsim_run_templete.shを適宜書き換える

ファイルはlowe/analizefileに生成される
走らせる条件がwcsim_yyyymmdd_hhmmss.csvに、データファイルが
wcsim_yyyymmdd_hhmmss.rootに保存される

Goodness(Likelihood,Minimize,Energy)を走らせるときにはlowe/processに入り、process_Goodness.shなどを走らせる
条件を変えたいときは、それらのファイルの内部の変数を変更する

ファイルはlowe/analizefileに生成される
走らせる条件がGoodness(Likelihood,Minimize,Energy)_yyyymmdd_hhmmss.csvに、データファイルが
Goodness(Likelihood,Minimize,Energy)_yyyymmdd_hhmmss.rootに保存される

source内の説明
mainメソッドを持つファイルはexeとrootに入っている
rootはrootを用いて図を生成するためのソースコード入れ場
解析の方法：
TRintを起動
解析対象のファイルをまとめるためのオブジェクトであるFileManagerを定義
void FileManager::SetAllFile()でlowe/analizefile内の全てのcsvファイルを読み込み
std::vector<AnalizeTag> FileManager::narrowdowntagに、入れたい条件のタグを追加
void FileManager::reflectNarrowDownTag(std::string s)でタグを反映（引数はファイル名に入っている名前）
AnalizeManagerを定義し、AnalizeManager::cpFileList(FileManager* manager,std::string s)でFileManagerに入った
ファイル群を名前を付けて使える状態にする（複数のファイル群を登録できる）
以降、AnalizeManagerのメソッドを用いてほしい量をゲットしたり、ヒストグラムに値を
詰めたりする
最後にTRint::run()を入れると、実行ファイルを動かしたときにインタプリタが起動し、図をいじったり
図の保存などができる

goodness,likelihood,minimizeはそれぞれGoodness,Likelihood,Minimizeの計算をするためのソースコードが置いてある

funcpartsは様々な計算に用いる関数が、generalにはソースコード全般に用いるクラスが定義されている

macroには、解析をするためのマクロを作成するためのクラスが入っている

撮った写真(.tiff)の解析は、lowe/tiff内で行っている
ソースコードはinclude,src,exe内に入っている
ビルドの方法
cd ~/retro/lowe/tiff/build
cmake ..
make

一人で行き当たりばったりで作ってたのでごちゃごちゃしてるし使わない余計なコードもあると思います。このソースコードを
改造して使ってもいいですし、使いづらいのであれば、中身だけ参考にしてもらって新しく作るのもいいと思います。
アルゴリズムのコアになる部分は、Goodnessはlowe/source/goodness/src/GoodnessEventManager.ccに、
Likelihoodはlowe/source/likelihood/src/LikelihoodEventManager.ccに、
Minimizeはlowe/source/macro/src/MinimizedFunction.ccに、
Energyはlowe/source/macro/src/Energy.ccにそれぞれ記述してあるので参考にしてください。（藤上）
