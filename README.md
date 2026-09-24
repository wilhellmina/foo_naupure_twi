# ツイッターにブラウザからなうぷれするやつ

行儀の悪すぎるやばコード

PlaybackのPullDownにあるはず

https://wakiga.nl/2021/04/24/foobar2000%e3%81%aenowplaying%e3%82%92%e3%83%84%e3%82%a4%e3%83%83%e3%82%bf%e3%83%bc%e3%81%ab%e6%8a%95%e7%a8%bf%e3%81%97%e3%81%9f%e3%81%84/

## ビルド

1. [foobar2000 SDK](https://www.foobar2000.org/SDK)（動作確認: `SDK-2026-09-17`）をリポジトリ直下の `sdk/` に展開する
   （`sdk/pfc`, `sdk/foobar2000/SDK` … となる配置）
2. `foo_twitter.sln` を Visual Studio 2022 以降で開いてビルド（x64 / x86）
3. `bin/<Platform>/Release/foo_twitter.dll` ができる

SDK 付属プロジェクトは v143 固定だが、v143 が無い環境（VS2026 など）では
`Directory.Build.props` によりインストール済みの既定ツールセットで代用される。
