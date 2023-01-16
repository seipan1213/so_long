# so_long
https://user-images.githubusercontent.com/38822155/212704178-a4cc8b79-3257-4c2d-9268-4aad129d937d.mp4

## 概要
- アイテムを全て集めて、ゴールに向かう簡単な2Dゲーム
- 拡張子が.berの設定ファイルでマップを自由に変更できる

## 操作方法
- 移動: WASD

## 使い方
```
make
./so_long [XXX.ber]

ex
./so_long test.ber
```
## .berファイル
- 0: 道
- 1: 壁
- E: ゴール
- P: プレイヤー初期位置
- C: アイテム

```test.ber
1111111111
1E101P1001
1000000001
100C00C001
1000CC0001
1111111111
```
