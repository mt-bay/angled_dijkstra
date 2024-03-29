ＪＭＣマップについて

１．概要
  ＪＭＣマップは、20万分1相当のベクトル形式の地図データです。データ項目は、行
政界･海岸線、道路、鉄道、河川･湖沼、市区町村名等の記号･注記です。このうち、行
政界･海岸線のデータは、構造化されたデータとなっていて、各自治体（市区町村）を
ポリゴンとして認識することができます。
  データは、１次メッシュ（約80km四方：20万分1地勢図）単位に１つのファイルにま
とめられています。


２．ディレクトリ構成
  以下のようなディレクトリ構成となっています。
   ￥---+-- JMCMAP.EXE  （表示ソフト関係ファイル）
        +-- JMCMAP.CNT  （表示ソフト関係ファイル）
        +-- JMCMAP.FTS  （表示ソフト関係ファイル）
        +-- JMCMAP.GID  （表示ソフト関係ファイル）
        +-- JMCMAP.HLP  （表示ソフトヘルプファイル）
        +-- README.DOC  （JMCマップ説明ファイル；Docファイル）
        +-- README.HTM  （JMCマップ説明ファイル；HTMLファイル）
        +-- README.TXT  （JMCマップ説明ファイル；テキストファイル）
        +-- Data ---+-- KS3026.DAT  
                    +-- KS3622.DAT （データファイルは１次メッシュ単位）
                    |

３．ファイルフォーマット
・１次メッシュ単位にファイルになっています。
・ファイル内のデータは、２次メッシュ番号順に並んでいます。
・２次メッシュ内のデータは、メッシュ･ヘッダー･レコードに続き、必要に応じてノー
ドレコード、ラインレコード、エリアレコード、ポイントレコード、注記テキスト
レコードが続きます。なお、ラインレコードには座標値レコード、エリアレコード
にはのエリア構成レコードが続きます。
・２次メッシュ内の各座標値は、左下を(0,0)、右上を(10000,10000)とする正規化座標
で記録されています。なお、ｘ座標は右（東）方向、ｙ座標は上（北）方向となり
ます。
・各レコードは、復帰･改行コードで区切られています。
・文字コードは、シフトJISコードを使用しています。


  データファイルは１次メッシュ単位になっており、以下のような構造になっています。

データファイル（１次メッシュ単位）-----------------------------+
|                                                              |
|   メッュ・ヘッダー･レコード（２次メッシュ単位）----------+   |
|   |                                                      |   |
|   |   レイヤー･ヘッダー･レコード（行政界･海岸線）----+   |   |
|   |   |   ﾉードレコード                              |   |   |
|   |   |   ラインレコード                             |   |   |
|   |   |         座標値レコード                       |   |   |
|   |   |   エリアレコード                             |   |   |
|   |   |         エリア構成ライン番号レコード         |   |   |
|   |   +----------------------------------------------+   |   |
|   |   レイヤー・ヘッダー・レコード（道路）-----------+   |   |
|   |   |  ラインレコード                              |   |   |
|   |   |         座標値レコード                       |   |   |
|   |   +----------------------------------------------+   |   |
|   |   レイヤー･ヘッダー･レコード（鉄道）-------------+   |   |
|   |   |  ラインレコード                              |   |   |
|   |   |         座標値レコード                       |   |   |
|   |   +----------------------------------------------+   |   |
|   |   レイヤー･ヘッダー･レコード（河川･湖沼）--------+   |   |
|   |   |  ラインレコード                              |   |   |
|   |   |         座標値レコード                       |   |   |
|   |   +----------------------------------------------+   |   |
|   |   レイヤー･ヘッダー･レコード（記号･注記）--------+   |   |
|   |   |  ポイントレコード                            |   |   |
|   |   |         座標値レコード                       |   |   |
|   |   |         注記テキストレコード                 |   |   |
|   |   +----------------------------------------------+   |   |
|   +------------------------------------------------------+   |
|                                                              |
|   メッシュ･ヘッダー･レコード（２次メッシュ単位）---------+   |
|   |                                                      |   |
|   |                                                      |   |
|   |                                                      |   |
+--------------------------------------------------------------+




４．レコードフォーマット
4.1メッシュ･ヘッダー･レコード
+-------------------+------+------+--------- +-----------------------------+
|        項目       | 開始 | 終了 | 形式 *1) |            内容             |
+-------------------+------+------+----------+-----------------------------+
|レコードタイプ     |    1 |    2 |       A2 |  "M  "を記録                |
+-------------------+------+------+----------+-----------------------------+
|２次メッシュコード |    3 |    8 |       I6 | ２次メッシュコード          |
+-------------------+------+------+----------+-----------------------------+
|図名               |    9 |   28 |      N10 | 当該2万5千分1地形図名       |
+-------------------+------+------+----------+-----------------------------+
|レイヤー総数       |   29 |   31 |       I3 | 当２次メッシュに含まれる    |
|                   |      |      |          | レイヤー総数                |
+-------------------+------+------+----------+-----------------------------+
|ノード総数         |   32 |   36 |       I5 | 当２次メッシュに含まれる    |
|                   |      |      |          | ノード総数                  |
+-------------------+------+------+----------+-----------------------------+
|ライン総数         |   37 |   41 |       I5 | ２次メッシュに含まれる      |
|                   |      |      |          | ライン総数                  |
+-------------------+------+------+----------+-----------------------------+
|エリア総数         |   42 |   46 |       I5 | 当２次メッシュに含まれる    |
|                   |      |      |          | エリア総数                  |
+-------------------+------+------+----------+-----------------------------+
|ポイント総数       |   47 |   51 |       I5 | 当２次メッシュに含まれる    |
|                   |      |      |          | ポイント総数                |
+-------------------+------+------+----------+-----------------------------+
|レコード総数       |   52 |   56 |       I5 | 当ヘッダー･レコードを除いた |
|                   |      |      |          | 当２次メッシュに含まれる    |
|                   |      |      |          | レコード数                  |
+-------------------+------+------+----------+-----------------------------+
|空白               |   57 |   72 |      16X |                             |
+-------------------+------+------+----------+-----------------------------+

*1) 仕様のA,I,N,Xは、FORTRAN言語の書式仕様のための編集記述子で、それぞれ次のよ
うな意味を持っています。
  A:英数字のデータが左詰めで記録されています。
  I:指定された整数を10進数表示した各数字（1バイト）が右詰めで記録されています。
  N:日本語文字のデータ（１文字２バイト）が左詰めで記録されています。Nに続く数
字は文字数を表し、バイト数はその２倍となります。文字コードはシフトJISです。
  X:空白が埋められています。




4.2レイヤー･ヘッダー･レコード
+-------------------+------+------+------+---------------------------------+
|        項目       | 開始 | 終了 | 形式 |              内容               |
+-------------------+------+------+------+---------------------------------+
|レコードタイプ     |    1 |    2 |   A2 | "H1":構造化が行われていない     |
|                   |      |      |      | レイヤー                        |
|                   |      |      |      | "H2":構造化が行われている       |
|                   |      |      |      | レイヤー                        |
+-------------------+------+------+------+---------------------------------+
|レイヤーコード     |    3 |    4 |   I2 | レイヤーの内容を表す            |
|                   |      |      |      | 1:行政界・海岸線                |
|                   |      |      |      | 2:道路                          |
|                   |      |      |      | 3:鉄道                          |
|                   |      |      |      | 5:河川・湖沼                    |
|                   |      |      |      | 7:記号･注記                     |
+-------------------+------+------+------+---------------------------------+
|ノード総数         |    5 |    9 |   I5 | 当レイヤーに含まれるノード総数  |
+-------------------+------+------+------+---------------------------------+
|ライン総数         |   10 |   14 |   I5 | 当レイヤーに含まれるライン総数  |
+-------------------+------+------+------+---------------------------------+
|エリア総数         |   15 |   19 |   I5 | 当レイヤーに含まれるエリア総数  |
+-------------------+------+------+------+---------------------------------+
|ポイント総数       |   20 |   24 |   I5 | 当レイヤーに含まれるポイント総数|
+-------------------+------+------+------+---------------------------------+
|レコード総数       |   25 |   29 |   I5 | 当ヘッダーレコードを除いた      |
|                   |      |      |      | 当レイヤー内のレコード総数      |
+-------------------+------+------+------+---------------------------------+
|空白               |   30 |   30 |   1X |                                 |
+-------------------+------+------+------+---------------------------------+
|最初の作成年月     |   31 |   34 |   I4 | 当レイヤーの最初の作成年月      |
|                   |      |      |      | 西暦年の下2桁と月2桁            |
+-------------------+------+------+------+---------------------------------+
|空白               |   35 |   35 |   1X |                                 |
+-------------------+------+------+------+---------------------------------+
|最終の更新年月     |   36 |   39 |   I4 | 当レイヤーのデータ更新年月      |
|                   |      |      |      | 西暦年の下2桁と月2桁            |
+-------------------+------+------+------+---------------------------------+
|空白               |  40  |   72 |  33X |                                 |
+-------------------+------+------+------+---------------------------------+

注）レコードタイプが"H1"の場合、ノード及びエリアレコードは記録されない。ノード
総数とエリア総数は、０となっている。




4.3ノードレコード
+-------------------+------+------+------+---------------------------------+
|        項目       | 開始 | 終了 | 形式 |              内容               |
+-------------------+------+------+------+---------------------------------+
|レコードタイプ     |    1 |    2 |   A2 | "N  "を記録                     |
+-------------------+------+------+------+---------------------------------+
|レイヤーコード     |    3 |    4 |   I2 | 1:行政界・海岸線                |
|                   |      |      |      | 2:道路                          |
|                   |      |      |      | 3:鉄道                          |
|                   |      |      |      | 5:河川・湖沼                    |
+-------------------+------+------+------+---------------------------------+
|データ項目コード   |    5 |    6 |   I2 | ノード項目コード表参照          |
+-------------------+------+------+------+---------------------------------+
|ノード一連番号     |    7 |   11 |   I5 | 当レイヤー内で当ノードが何番目  |
|                   |      |      |      | に位置するかを示す一連番号      |
+-------------------+------+------+------+---------------------------------+
|ノード座標値（X)   |   12 |   16 |   I5 | 当ノードのX座標値               |
+-------------------+------+------+------+---------------------------------+
|ノード座標値（Y)   |   17 |   21 |   I5 | 当ノードのY座標値               |
+-------------------+------+------+------+---------------------------------+
|図郭情報           |   22 |   23 |   I2 | 当ノードの位置を示す            |
|                   |      |      |      | 0:図郭内    1:図郭線上          |
+-------------------+------+------+------+---------------------------------+
|接続するライン数   |   24 |   25 |   I2 | 当ノードに接続するラインの数    |
+-------------------+------+------+------+---------------------------------+
|接続ライン番号 1   |   26 |   30 |   I5 | 接続するすべてのライン番号を記  |
+-------------------+------+------+------+ 録（残った欄は0で埋める)        |
|接続ライン番号 2   |   31 |   36 |   I5 |                                 |
+-------------------+------+------+------+                                 |
|       ・          |      |      |      |                                 |
|       ・          |      |      |      |                                 |
|       ・          |      |      |      |                                 |
+-------------------+------+------+------+---------------------------------+
|接続ライン番号 9   |   66 |   70 |   I5 |                                 |
+-------------------+------+------+------+---------------------------------+
|空白               |   71 |   72 |   2X |                                 |
+-------------------+------+------+------+---------------------------------+

注)接続するラインは、当ノードを始点または終点とするラインのことである。接続ラ
インの番号欄には、始点である場合はライン番号はそのまま、終点である場合には
番号の頭にマイナス記号をつけた負数が記録されている。




4.4ノード項目コード
+-------------------+--------+----------------------------------+
|     レイヤー      | コード |         データ項目               |
+-------------------+--------+----------------------------------+
|行政界･海岸線      |  1     | 図郭線上の点 *1)                 |
|        1          +--------+----------------------------------+
|                   |  2     | ラインとラインの交点             |
|                   +--------+----------------------------------+
|                   |  3     | 閉じたラインの始終点             |
|                   +--------+----------------------------------+
|                   |  4     | ライン種別の変化点               |
+-------------------+--------+----------------------------------+

*1) 交差点等が図郭線上にある場合、コードは"１"以外のそれに対応する値となる。




4.5ラインレコード
+-------------------+------+------+-------+--------------------------------+
|        項目       | 開始 | 終了 |  形式 |              内容              |
+-------------------+------+------+-------+--------------------------------+
|レコードタイプ     |    1 |    2 |    A2 | "L  "を記録                    |
+-------------------+------+------+-------+--------------------------------+
|レイヤーコード     |    3 |    4 |    I2 | 1:行政界・海岸線               |
|                   |      |      |       | 2:道路                         |
|                   |      |      |       | 3:鉄道                         |
|                   |      |      |       | 5:河川･湖沼                    |
+-------------------+------+------+-------+--------------------------------+
|データ項目コード   |    5 |    6 |    I2 | ライン項目コード表参照         |
+-------------------+------+------+-------+--------------------------------+
|ライン一連番号     |    7 |   11 |    I5 | レイヤー内で当ラインが何番目   |
|                   |      |      |       | に位置するかを示す一連番号     |
+-------------------+------+------+-------+--------------------------------+
|ライン種別コード   |   12 |   17 |    I6 | ライン種別コード表参照         |
+-------------------+------+------+-------+--------------------------------+
|始点ノード番号     |   18 |   22 |    I5 |                                |
+-------------------+------+------+-------+--------------------------------+
|始点接続情報       |   23 |   23 |    I1 | 0:図葉内ノード                 |
|                   |      |      |       | 1:隣接図葉に接続する図郭線上   |
|                   |      |      |       |  のノード                      |
|                   |      |      |       | 2:隣接図葉に接続しない図郭線   |
|                   |      |      |       |  上のノード                    |
+-------------------+------+------+-------+--------------------------------+
|終点ノード番号     |   24 |   28 |    I5 |                                |
+-------------------+------+------+-------+--------------------------------+
|終点接続情報       |   29 |   29 |    I1 | 始点接続情報と同じコード       |
+-------------------+------+------+-------+--------------------------------+
|左側 行政コード    |   30 |   34 |    I5 | ラインの向きに対して左側の     |
|                   |      |      |       | 行政コード  *1)                |
+-------------------+------+------+-------+--------------------------------+
|右側 行政コード    |   35 |   39 |    I5 | ラインの向きに対して右側の     |
|                   |      |      |       | 行政コード  *1)                |
+-------------------+------+------+-------+--------------------------------+
|座標点の数         |   40 |   45 |    I6 | 当ラインを構成するXY座標点の   |
|                   |      |      |       | 数（始終点ノードを含む）       |
+-------------------+------+------+-------+--------------------------------+
|空白               |   46 |   72 |   X27 |                                |
+-------------------+------+------+-------+--------------------------------+

*1) 例外として、海の場合は"99999"、図郭外の場合は"88888"とする。




4.6ライン項目コード
+-------------------+--------+----------------------------------+
|     レイヤー      | コード |         データ項目               |
+-------------------+--------+----------------------------------+
|行政界・海岸線     |  1     | 都府県界                         |
|                   +--------+----------------------------------+
|         1         |  2     | 北海道の支庁界                   |
|                   +--------+----------------------------------+
|                   |  3     | 郡市･特別区界                    |
|                   +--------+----------------------------------+
|                   |  4     | 町村･指定都市の区界              |
|                   +--------+----------------------------------+
|                   |  5     | 海岸線                           |
|                   +--------+----------------------------------+
|                   |  9     | 図郭線                           |
+-------------------+--------+----------------------------------+
|道路               |  1     | 高速道路及び自動車専用道         |
|                   +--------+----------------------------------+
|         2         |  2     | 一般国道                         |
|                   +--------+----------------------------------+
|                   |  3     | 主要地方道                       |
|                   +--------+----------------------------------+
|                   |  4     | 一般都道府県道                   |
|                   +--------+----------------------------------+
|                   |  5     | その他の道路                     |
+-------------------+--------+----------------------------------+
|鉄道               |  1     | JR                               |
|                   +--------+----------------------------------+
|         3         |  2     | 公営鉄道                         |
|                   +--------+----------------------------------+
|                   |  3     | 民営鉄道                         |
|                   +--------+----------------------------------+
|                   |  9     | 未設                             |
+-------------------+--------+----------------------------------+
|河川･湖沼          |  1     | 河川流路                         |
|                   +--------+----------------------------------+
|         5         |  2     | 湖沼の水涯線                     |
+-------------------+--------+----------------------------------+

注）道路レイヤーのコード５「その他の道路」は、平成11年度刊行データより新規採用




4.7ライン種別コード
+-------------------+--------+----------------------------------+
|     レイヤー      | コード |            データ項目            |
+-------------------+--------+----------------------------------+
|行政界             |  0     | 確定境界線                       |
|                   +--------+----------------------------------+
|         1         |  1     | 仮設境界線（陸部）               |
|                   +--------+----------------------------------+
|                   |  2     | 仮設境界線（水部)                |
|                   +--------+----------------------------------+
|                   |  9     | 図郭線                           |
+-------------------+--------+----------------------------------+
|道路               |  0     | 地上                             |
|                   +--------+----------------------------------+
|         2         |  1     | 地下･トンネル                    |
+-------------------+--------+----------------------------------+
|鉄道               |  0     | 地上                             |
|                   +--------+----------------------------------+
|         3         |  1     | 地下･トンネル                    |
+-------------------+--------+----------------------------------+
|河川･湖沼          |  0     | 通常の河川                       |
|                   +--------+----------------------------------+
|         5         |  1     | 湖沼内の河川                     |
+-------------------+--------+----------------------------------+




4.8座標値レコード
+-------------------+------+------+------+---------------------------------+
|        項目      | 開始 | 終了 | 形式 |              内容                |
+-------------------+------+------+------+---------------------------------+
| 1点目のX座標      |    1 |    5 |   I5 | ラインレコードに続くレコード    |
+-------------------+------+------+------+ で、ラインを構成する座標点の数  |
| 1点目のY座標      |    6 |   10 |   I5 | NだけXY座標値のペアが記録され   |
+-------------------+------+------+------+ る。座標値レコードの数は、      |
| 2点目のX座標      |   11 |   15 |   I5 |                                 |
+-------------------+------+------+------+ (N-1)/7+1                       |
| 2点目のY座標      |   16 |   20 |   I5 |                                 |
+-------------------+------+------+------+ である（余りは切り捨て）。最後  |
|      ・           |      |      |      | のレコードに空きが生じる場合、  |
|      ・           |      |      |      | 0が埋められる。                 |
|      ・           |      |      |      |                                 |
+-------------------+------+------+------+                                 |
| 7点目のX座標      |   61 |   65 |   I5 |                                 |
+-------------------+------+------+------+                                 |
| 7点目のY座標      |   66 |   70 |   I5 |                                 |
+-------------------+------+------+------+---------------------------------+
|空白               |   71 |   72 |   X2 |                                 |
+-------------------+------+------+------+---------------------------------+




4.9エリアレコード
+-------------------+------+------+------+---------------------------------+
|        項目       | 開始 | 終了 | 形式 |             内容                |
+-------------------+------+------+------+---------------------------------+
|レコードタイプ     |    1 |    2 |   I2 | "A "を記録                      |
+-------------------+------+------+------+---------------------------------+
|レイヤーコード     |    3 |    4 |   I2 | 1:行政界・海岸線                |
|                   |      |      |      | 2:道路                          |
|                   |      |      |      | 3:鉄道                          |
|                   |      |      |      | 5:河川・湖沼                    |
+-------------------+------+------+------+---------------------------------+
|データ項目コード   |    5 |    9 |   I5 | 行政界レイヤーの場合は行政コー  |
|                   |      |      |      | ドを記録                        |
+-------------------+------+------+------+---------------------------------+
|エリア一連番号     |   10 |   14 |   I5 | 当レイヤー内で当エリアが何番目  |
|                   |      |      |      | に位置するかを示す一連番号      |
+-------------------+------+------+------+---------------------------------+
|代表点の座標値（X) |   15 |   19 |   I5 | 当エリア内代表点のX座標値       |
+-------------------+------+------+------+---------------------------------+
|代表点の座標値（Y) |   20 |   24 |   I5 | 当エリア内代表点のY座標値       |
+-------------------+------+------+------+---------------------------------+
|ライン数           |   25 |   28 |   I4 | 当エリアを構成するライン数（図  |
|                   |      |      |      | 郭線及びエリア内アイランドの外  |
|                   |      |      |      | 周を含む）にアイランドの数を加  |
|                   |      |      |      | えた数                          |
+-------------------+------+------+------+---------------------------------+
|空白               |   29 |   72 |  44X |                                 |
+-------------------+------+------+------+---------------------------------+




4.10エリア構成ライン番号レコード
+-------------------+------+------+------+---------------------------------+
|        項目       | 開始 | 終了 | 形式 |             内容                |
+-------------------+------+------+------+---------------------------------+
|ライン番号 1       |    1 |    5 |   I5 | エリアレコードに続くレコード    |
+-------------------+------+------+------+ で、エリアを構成するラインの数  |
|ライン番号 2       |    6 |   10 |   I5 | Nにエリア内のアイランドの数Mを  |
+-------------------+------+------+------+ 加えた数だけライン番号が記録さ  |
|ライン番号 3       |   11 |   15 |   I5 | れる。当レコードは、            |
+-------------------+------+------+------+                                 |
|ライン番号 4       |   16 |   20 |   I5 | (N+M-1)/14+1                    |
+-------------------+------+------+------+                                 |
|ライン番号 5       |   21 |   25 |   I5 | である（余りは切り捨て）。最後  |
+-------------------+------+------+------+ のレコードに空きが生じる場合は  |
|ライン番号 6       |   26 |   30 |   I5 | 0が記録される。ただし、当該エ   |
+-------------------+------+------+------+ リア内に飛び地（アイランド）を  |
|ライン番号 7       |   31 |   35 |   I5 |                                 |
+-------------------+------+------+------+                                 |
|ライン番号 8       |   36 |   40 |   I5 |                                 |
+-------------------+------+------+------+                                 |
|ライン番号 9       |   41 |   45 |   I5 |                                 |
+-------------------+------+------+------+                                 |
|ライン番号10       |   46 |   50 |   I5 | 番号の記述は、エリアを右に見な  |
+-------------------+------+------+------+ がら（ラインの方向が逆の場合マ  |
|ライン番号11       |   51 |   55 |   I5 | イナス符号をつけて）連続したエ  |
+-------------------+------+------+------+ リアの外周線、アイランド外周線  |
|ライン番号12       |   56 |   60 |   I5 | の順序で行われる。              |
+-------------------+------+------+------+                                 |
|ライン番号13       |   61 |   65 |   I5 |                                 |
+-------------------+------+------+------+                                 |
|ライン番号14       |   66 |   70 |   I5 |                                 |
+-------------------+------+------+------+---------------------------------+
|空白               |   71 |   72 |   2X |                                 |
+-------------------+------+------+------+---------------------------------+ 



4.11ポイント･レコード
+-------------------+------+------+------+---------------------------------+
|        項目       | 開始 | 終了 | 形式 |             内容                |
+-------------------+------+------+------+---------------------------------+
|レコードタイプ     |    1 |    2 |   A2 | "P  "を記録                     |
+-------------------+------+------+------+---------------------------------+
|レイヤーコード     |    3 |    4 |   I2 | 7:記号･注記                     |
+-------------------+------+------+------+---------------------------------+
|データ項目コード   |    5 |    6 |   I2 | ポイント項目コード表参照        |
+-------------------+------+------+------+---------------------------------+
|ポイント一連番号   |    7 |   11 |   I5 | 当レイヤー内で当ポイントが何番  |
|                   |      |      |      | 目に位置するかを示す一連番号    |
+-------------------+------+------+------+---------------------------------+
|ポイント座標値（X) |   12 |   16 |   I5 | 当ポイントのX座標値             |
+-------------------+------+------+------+---------------------------------+
|ポイント座標値（Y) |   17 |   21 |   I5 | 当ポイントのY座標値             |
+-------------------+------+------+------+---------------------------------+
|ポイント属整数     |   22 |   23 |   I2 |                                 |
+-------------------+------+------+------+---------------------------------+
|注記数             |   24 |   25 |   I2 | 当ポイントに対応する注記テキス  |
|                   |      |      |      | トレコードの数                  |
+-------------------+------+------+------+---------------------------------+
|空白               |   26 |   72 |  47X |                                 |
+-------------------+------+------+------+---------------------------------+




4.12ポイント項目コード
+-------------------+-------+----------------------------------+
|     レイヤー      | コード|           データ項目             |
+-------------------+-------+----------------------------------+
|記号･注記          |  1    | 市区町村名                       |
|                   +-------+----------------------------------+
|                   |  2    | 山岳名                           |
|                   +------------------------------------------+
|                   |  3    | 峠名                             |
|                   +------------------------------------------+
|                   |  4    | 川谷名                           |
|                   +------------------------------------------+
|                   |  5    | 海岸名                           |
|                   +------------------------------------------+
|                   |  6    | 岬名                             |
|                   +------------------------------------------+
|                   |  7    | 島名                             |
|                   +------------------------------------------+
|                   |  8    | 湖沼名                           |
|                   +------------------------------------------+
|                   |  9    | 海域名                           |
|                   +------------------------------------------+
|                   | 51    | 都道府県庁                       |
|                   +------------------------------------------+
|                   | 52    | 市役所及び東京都の区役所         |
|                   +------------------------------------------+
|                   | 53    | 町村役場及び指定都市の区役所     |
+-------------------+-------+----------------------------------+




4.13注記テキストレコード
+-------------------+------+------+-------+--------------------------------+
|        項目       | 開始 | 終了 |  形式 |            内容                |
+-------------------+------+------+-------+--------------------------------+
|レコード区分       |    1 |    1 |    I1 | 0:注記    1:テキスト *1)       |
+-------------------+------+------+-------+--------------------------------+
|文字区分           |    2 |    2 |    I1 | 0:英数字またはカタカナの１バイ |
|                   |      |      |       | ト文字                         |
|                   |      |      |       | 1:漢字等の２バイト文字         |
+-------------------+------+------+-------+--------------------------------+
|文字数             |    3 |    4 |    I2 | 注記文字列に書かれている文字数 |
|                   |      |      |       |                      *2)       |
+-------------------+------+------+-------+--------------------------------+
|代表点の座標値（X) |    5 |    9 |    I5 | 代表点のX座標値                |
+-------------------+------+------+-------+--------------------------------+
|代表点の座標値（Y) |   10 |   14 |    I5 | 代表点のY座標値                |
+-------------------+------+------+-------+--------------------------------+
|空白               |   15 |   28 |   14X |                                |
+-------------------+------+------+-------+--------------------------------+
|書式情報           |   29 |   30 |    I2 | 00:基準位置が中央下            |
|                   |      |      |       | 01:基準位置が左下              |
|                   |      |      |       | 02:基準位置が右下              |
+-------------------+------+------+------+---------------------------------+
|空白               |   31 |   32 |    2X |                                |
+-------------------+------+------+-------+--------------------------------+
|注記文字列         |   33 |   72 |   A40 | 左詰め                         |
|                   |      |      | または|                                |
|                   |      |      |   N20 |                                |
+-------------------+------+------+-------+--------------------------------+

*1) レコード区分が１（テキスト)の場合は、５から72バイトまですべて文字列に使わ
れる。
*2) 2バイト文字の場合、バイト数は文字数の2倍となる。

作成
＊本データの作成にあたっては、国土地理院の国土数値情報を使用しました。
   お客様申込み番号「L5I22014」

  平成１７年　６月１日
  (財)日本地図センター  普及販売部
    Tel 03-3485-5414
    Fax 03-3465-7591
    E-mail : maps@jmc.or.jp
    Homepage URL : http://www.jmc.or.jp

