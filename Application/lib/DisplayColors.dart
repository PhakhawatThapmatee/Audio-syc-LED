import 'package:firebase_database/firebase_database.dart';
import 'package:flutter/material.dart';
import 'package:flutter_easyloading/flutter_easyloading.dart';
import 'SendToESP.dart';

class DisplayColors {
  final dataBase = FirebaseDatabase.instance.reference();

  int? pattern_number;

  List<Color> Volume = [
    Color(0),
    Color(0),
    Color(0),
    Color(0),
    Color(0),
    Color(0),
    Color(0),
    Color(0)
  ];
  List<Color> Volume_display = [
    Color(0),
    Color(0),
    Color(0),
    Color(0),
    Color(0),
    Color(0),
    Color(0),
    Color(0)
  ];

  DisplayColors(this.pattern_number);

  Future<void> getColor() async {
    var reset = await dataBase
        .child('Functions/reset_pattern/reset_P$pattern_number/')
        .get();
    int resetNumber = reset.value;
    if (resetNumber == 0) {
      int num = 1;
      for (int i = 0; i < 8; i++) {
        var color = await dataBase
            .child(
                'Functions/Set_Colors_Pattern$pattern_number/Volume$num/ColorCode/')
            .get();
        Volume[i] = Color(color.value);
        Volume_display[i] = Color(color.value);
        num++;
      }
    } else {
      Volume = [
        Color(4294902015),
        Color(4286578943),
        Color(4278190335),
        Color(4278255615),
        Color(4278255360),
        Color(4294967040),
        Color(4294934528),
        Color(4294901760)
      ];

      Volume_display = [
        Color(1660944383),
        Color(1660944383),
        Color(1660944383),
        Color(1660944383),
        Color(1660944383),
        Color(1660944383),
        Color(1660944383),
        Color(1660944383)
      ];
    }
  }

  Future<void> updateColor(List<Color> ColorCode) async {
    for (int i = 1; i <= 8; i++) {
      var up_color = await dataBase
          .child('Functions/Set_Colors_Pattern$pattern_number/Volume$i/');
      up_color.update({'ColorCode': ColorCode[i - 1].value});
    }
  }

  Future<void> updateResetState(int reset_State) async {
    var up_reset = await dataBase.child('Functions/reset_pattern/');
    if (reset_State == 1) {
      up_reset.update({'reset_P$pattern_number': 1});
    } else {
      up_reset.update({'reset_P$pattern_number': 0});
    }
  }

  Future<void> getDataColor() async {
    await getColor();
    String colorData = "$pattern_number";

    for (int i = 0; i < 8; i++) {
      for (int y = 0; y < 3; y++) {
        int Value_color = 0;
        if (y % 3 == 0) {
          Value_color = Volume[i].red;
        } else if (y % 3 == 1) {
          Value_color = Volume[i].green;
        } else if (y % 3 == 2) {
          Value_color = Volume[i].blue;
        }
        colorData += ",$Value_color";
      }
    }

    var data = SendToESP(colorData);
    data.sendDataToESP32();

    EasyLoading.dismiss();
    EasyLoading.showSuccess('Success!');
  }

  Future<List<Color>> getColorDisplay() async {
    await getColor();
    return Volume_display;
  }
}
