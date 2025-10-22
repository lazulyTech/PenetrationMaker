# Penetration Maker - 密着状況にするやつ -
## 環境構築
- PlatformIO on VSCode
- Vendor ID, Product IDの変更
  - ~/.platformio/platforms/atmelavr/boards/sparkfun_promicro16.json を編集
  - "hwids"の中に追加する
  変更前
```
"hwids": [
      [
        "0x1B4F",
        "0x9206"
      ],
```
↓
  変更後
```
"hwids": [
      ["0x0f0d", "0x0092"],
      [
        "0x1B4F",
        "0x9206"
      ],
```

