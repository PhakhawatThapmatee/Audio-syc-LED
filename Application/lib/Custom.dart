import 'package:flutter/material.dart';
import 'package:flutter_circle_color_picker/flutter_circle_color_picker.dart';
import 'package:flutter_easyloading/flutter_easyloading.dart';
import 'DisplayColors.dart';

class Custom extends StatefulWidget {
  const Custom({super.key});

  @override
  State<Custom> createState() => _CustomState();
}

class _CustomState extends State<Custom> {
  Color _PatternColor = Color.fromARGB(251, 255, 157, 0);
  String _patters = "Random Mode";
  int _select_Patterns = 1;
  bool _isShow_default = true;

  // Select Volume
  List<Color> _color_bor = [
    Colors.black,
    Colors.black,
    Colors.black,
    Colors.black,
    Colors.black,
    Colors.black,
    Colors.black,
    Colors.black,
  ];

  void selectbor(int num_bor) {
    for (int i = 0; i < 8; i++) {
      _color_bor[i] = Colors.black;
    }
    _color_bor[num_bor - 1] = Colors.white;
  }

  int _volume_number = 0;

  int _reset_P1 = 0;
  int _reset_P2 = 0;
  int _reset_P3 = 0;

  List<Color> _color = [
    Color(0),
    Color(0),
    Color(0),
    Color(0),
    Color(0),
    Color(0),
    Color(0),
    Color(0)
  ];

  void getDataColorPattern(int Color_volume) async {
    var pattern = DisplayColors(Color_volume);
    var Volume = await pattern.getColorDisplay();
    if (mounted) {
      setState(() {
        for (int i = 0; i < Volume.length; i++) {
          _color[i] = Volume[i];
        }
        _isShow_default = false;
      });
    }
  }

  int num_color = 8;
  showColor(int volume_number) {
    if (_isShow_default == true) {
      num_color = 8;
      getDataColorPattern(_select_Patterns);
    }
    if (num_color == 1) {
      EasyLoading.dismiss();
    }
    num_color--;
    return Color(_color[volume_number - 1].value);
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      resizeToAvoidBottomInset: false,
      backgroundColor: Colors.black87,
      appBar: AppBar(
        iconTheme: IconThemeData(color: Colors.white),
        backgroundColor: Colors.black,
        centerTitle: true,
        title: const Text(
          'Custom',
          style: TextStyle(
            color: Colors.white,
          ),
        ),
      ),
      body: Center(
        child: Column(
          children: [
            Container(
              child: Row(
                mainAxisAlignment: MainAxisAlignment.center,
                children: [
                  SizedBox(
                    width: 140,
                    height: 100,
                    child: Card(
                      color: _PatternColor,
                      shape: RoundedRectangleBorder(
                        borderRadius: BorderRadius.circular(20),
                        side: const BorderSide(
                          color: Colors.black,
                        ),
                      ),
                      child: Center(
                        child: Column(
                          mainAxisAlignment: MainAxisAlignment.spaceEvenly,
                          children: [
                            Text(
                              _patters,
                              style: const TextStyle(
                                color: Colors.white,
                                fontSize: 14,
                                fontWeight: FontWeight.bold,
                              ),
                            ),
                          ],
                        ),
                      ),
                    ),
                  ),
                  ElevatedButton(
                    style: ButtonStyle(
                      backgroundColor:
                          MaterialStatePropertyAll<Color>(Colors.black),
                      shape: MaterialStatePropertyAll(RoundedRectangleBorder(
                        borderRadius: BorderRadius.circular(10),
                      )),
                    ),
                    onPressed: () {
                      showDialog<String>(
                          context: context,
                          builder: (context) => AlertDialog(
                              backgroundColor: Colors.black54,
                              title: const Text(
                                'Choose a pattern',
                                style: TextStyle(
                                  color: Colors.white,
                                ),
                              ),
                              content: Column(
                                children: [
                                  Container(
                                    height: 20,
                                  ),
                                  const Row(
                                    children: [
                                      Text(
                                        'Pattern',
                                        style: TextStyle(
                                          color: Colors.white,
                                          fontSize: 16,
                                          fontWeight: FontWeight.bold,
                                        ),
                                      ),
                                    ],
                                  ),
                                  Container(
                                    height: 10,
                                  ),
                                  Container(
                                    width: 300,
                                    height: 500,
                                    child: GridView.count(
                                        crossAxisCount: 1,
                                        childAspectRatio: (1 / .4),
                                        padding: const EdgeInsets.all(5),
                                        children: List.generate(8, (index) {
                                          int patterns = index + 1;
                                          if (patterns == 1) {
                                            return Card(
                                              color: const Color.fromARGB(
                                                  251, 255, 157, 0),
                                              margin: const EdgeInsets.all(5),
                                              shape: RoundedRectangleBorder(
                                                borderRadius:
                                                    BorderRadius.circular(20),
                                              ),
                                              clipBehavior: Clip.hardEdge,
                                              child: InkWell(
                                                splashColor:
                                                    Colors.black.withAlpha(100),
                                                onTap: () {
                                                  setState(() {
                                                    EasyLoading.show(
                                                        status: 'loading...');
                                                    _PatternColor =
                                                        const Color.fromARGB(
                                                            251, 255, 157, 0);
                                                    _patters = 'Random Mode';
                                                    _select_Patterns = 1;
                                                    _isShow_default = true;
                                                  });
                                                  Navigator.pop(context);
                                                },
                                                child: const Center(
                                                  child: Column(
                                                    mainAxisAlignment:
                                                        MainAxisAlignment
                                                            .spaceEvenly,
                                                    children: [
                                                      Text(
                                                        'Random Mode',
                                                        style: TextStyle(
                                                          color: Colors.white,
                                                          fontSize: 14,
                                                          fontWeight:
                                                              FontWeight.bold,
                                                        ),
                                                      ),
                                                    ],
                                                  ),
                                                ),
                                              ),
                                            );
                                          }
                                          if (patterns == 2) {
                                            return Card(
                                              color: const Color.fromARGB(
                                                  180, 38, 255, 0),
                                              margin: const EdgeInsets.all(5),
                                              shape: RoundedRectangleBorder(
                                                borderRadius:
                                                    BorderRadius.circular(20),
                                              ),
                                              clipBehavior: Clip.hardEdge,
                                              child: InkWell(
                                                splashColor:
                                                    Colors.black.withAlpha(100),
                                                onTap: () {
                                                  setState(() {
                                                    EasyLoading.show(
                                                        status: 'loading...');
                                                    _PatternColor =
                                                        const Color.fromARGB(
                                                            180, 38, 255, 0);
                                                    _patters =
                                                        'Spectrogram \n Mode';

                                                    _select_Patterns = 2;
                                                    _isShow_default = true;
                                                  });
                                                  Navigator.pop(context);
                                                },
                                                child: const Center(
                                                  child: Column(
                                                    mainAxisAlignment:
                                                        MainAxisAlignment
                                                            .spaceEvenly,
                                                    children: [
                                                      Text(
                                                        'Spectrogram \n Mode',
                                                        style: TextStyle(
                                                          color: Colors.white,
                                                          fontSize: 14,
                                                          fontWeight:
                                                              FontWeight.bold,
                                                        ),
                                                      ),
                                                    ],
                                                  ),
                                                ),
                                              ),
                                            );
                                          }
                                          if (patterns == 3) {
                                            return Card(
                                              color: const Color.fromARGB(
                                                  255, 85, 0, 255),
                                              margin: const EdgeInsets.all(5),
                                              shape: RoundedRectangleBorder(
                                                borderRadius:
                                                    BorderRadius.circular(20),
                                              ),
                                              clipBehavior: Clip.hardEdge,
                                              child: InkWell(
                                                splashColor:
                                                    Colors.black.withAlpha(100),
                                                onTap: () {
                                                  setState(() {
                                                    EasyLoading.show(
                                                        status: 'loading...');
                                                    _PatternColor =
                                                        const Color.fromARGB(
                                                            255, 85, 0, 255);
                                                    _patters = 'Circle Mode';
                                                    _select_Patterns = 3;
                                                    _isShow_default = true;
                                                  });
                                                  Navigator.pop(context);
                                                },
                                                child: const Center(
                                                  child: Column(
                                                    mainAxisAlignment:
                                                        MainAxisAlignment
                                                            .spaceEvenly,
                                                    children: [
                                                      Text(
                                                        'Circle Mode',
                                                        style: TextStyle(
                                                          color: Colors.white,
                                                          fontSize: 14,
                                                          fontWeight:
                                                              FontWeight.bold,
                                                        ),
                                                      ),
                                                    ],
                                                  ),
                                                ),
                                              ),
                                            );
                                          }
                                          return Container();
                                        })),
                                  ),
                                ],
                              )));
                    },
                    child: const Center(
                      child: Row(
                        // mainAxisAlignment: MainAxisAlignment.spaceBetween,
                        children: [
                          Text(
                            'Pattern',
                            style: TextStyle(
                              color: Colors.white,
                            ),
                          ),
                          Icon(
                            Icons.arrow_drop_down,
                            color: Colors.white,
                          ),
                        ],
                      ),
                    ),
                  ),
                ],
              ),
            ),
            Container(
              height: 40,
              child: const Center(
                child: Text(
                  'Volume',
                  style: TextStyle(
                    color: Colors.white,
                    fontSize: 16,
                    fontWeight: FontWeight.bold,
                  ),
                ),
              ),
            ),
            Container(
              child: Center(
                child: Column(
                  crossAxisAlignment: CrossAxisAlignment.center,
                  children: [
                    // Volmue 8
                    Row(
                      mainAxisAlignment: MainAxisAlignment.center,
                      children: [
                        const Text(
                          '8',
                          style: TextStyle(
                            color: Colors.white,
                            fontSize: 16,
                            fontWeight: FontWeight.bold,
                          ),
                        ),
                        SizedBox(
                          width: 150,
                          height: 30,
                          child: Card(
                            color: showColor(8),
                            shape: RoundedRectangleBorder(
                              borderRadius: BorderRadius.circular(5),
                              side: BorderSide(
                                color: _color_bor[7],
                                width: 1.3,
                              ),
                            ),
                            child: InkWell(
                                splashColor: Colors.black.withAlpha(100),
                                onTap: () {
                                  setState(() {
                                    _volume_number = 8;
                                    selectbor(8);
                                  });
                                }),
                          ),
                        ),
                        const Text(
                          '8',
                          style: TextStyle(
                            color: Colors.white,
                            fontSize: 16,
                            fontWeight: FontWeight.bold,
                          ),
                        ),
                      ],
                    ),

                    // Volmue 7
                    Row(
                      mainAxisAlignment: MainAxisAlignment.center,
                      children: [
                        const Text(
                          '7',
                          style: TextStyle(
                            color: Colors.white,
                            fontSize: 16,
                            fontWeight: FontWeight.bold,
                          ),
                        ),
                        SizedBox(
                          width: 150,
                          height: 30,
                          child: Card(
                            color: showColor(7),
                            shape: RoundedRectangleBorder(
                              borderRadius: BorderRadius.circular(5),
                              side: BorderSide(
                                color: _color_bor[6],
                                width: 1.3,
                              ),
                            ),
                            child: InkWell(
                                splashColor: Colors.black.withAlpha(100),
                                onTap: () {
                                  setState(() {
                                    _volume_number = 7;
                                    selectbor(7);
                                  });
                                }),
                          ),
                        ),
                        const Text(
                          '7',
                          style: TextStyle(
                            color: Colors.white,
                            fontSize: 16,
                            fontWeight: FontWeight.bold,
                          ),
                        ),
                      ],
                    ),
                    // Volmue 6
                    Row(
                      mainAxisAlignment: MainAxisAlignment.center,
                      children: [
                        const Text(
                          '6',
                          style: TextStyle(
                            color: Colors.white,
                            fontSize: 16,
                            fontWeight: FontWeight.bold,
                          ),
                        ),
                        SizedBox(
                          width: 150,
                          height: 30,
                          child: Card(
                            color: showColor(6),
                            shape: RoundedRectangleBorder(
                              borderRadius: BorderRadius.circular(5),
                              side: BorderSide(
                                color: _color_bor[5],
                                width: 1.3,
                              ),
                            ),
                            child: InkWell(
                                splashColor: Colors.black.withAlpha(100),
                                onTap: () {
                                  setState(() {
                                    _volume_number = 6;
                                    selectbor(6);
                                  });
                                }),
                          ),
                        ),
                        const Text(
                          '6',
                          style: TextStyle(
                            color: Colors.white,
                            fontSize: 16,
                            fontWeight: FontWeight.bold,
                          ),
                        ),
                      ],
                    ),
                    // Volmue 5
                    Row(
                      mainAxisAlignment: MainAxisAlignment.center,
                      children: [
                        const Text(
                          '5',
                          style: TextStyle(
                            color: Colors.white,
                            fontSize: 16,
                            fontWeight: FontWeight.bold,
                          ),
                        ),
                        SizedBox(
                          width: 150,
                          height: 30,
                          child: Card(
                            color: showColor(5),
                            shape: RoundedRectangleBorder(
                              borderRadius: BorderRadius.circular(5),
                              side: BorderSide(
                                color: _color_bor[4],
                                width: 1.3,
                              ),
                            ),
                            child: InkWell(
                                splashColor: Colors.black.withAlpha(100),
                                onTap: () {
                                  setState(() {
                                    _volume_number = 5;
                                    selectbor(5);
                                  });
                                }),
                          ),
                        ),
                        const Text(
                          '5',
                          style: TextStyle(
                            color: Colors.white,
                            fontSize: 16,
                            fontWeight: FontWeight.bold,
                          ),
                        ),
                      ],
                    ),
                    // Volmue 4
                    Row(
                      mainAxisAlignment: MainAxisAlignment.center,
                      children: [
                        const Text(
                          '4',
                          style: TextStyle(
                            color: Colors.white,
                            fontSize: 16,
                            fontWeight: FontWeight.bold,
                          ),
                        ),
                        SizedBox(
                          width: 150,
                          height: 30,
                          child: Card(
                            color: showColor(4),
                            shape: RoundedRectangleBorder(
                              borderRadius: BorderRadius.circular(5),
                              side: BorderSide(
                                color: _color_bor[3],
                                width: 1.3,
                              ),
                            ),
                            child: InkWell(
                                splashColor: Colors.black.withAlpha(100),
                                onTap: () {
                                  setState(() {
                                    _volume_number = 4;
                                    selectbor(4);
                                  });
                                }),
                          ),
                        ),
                        const Text(
                          '4',
                          style: TextStyle(
                            color: Colors.white,
                            fontSize: 16,
                            fontWeight: FontWeight.bold,
                          ),
                        ),
                      ],
                    ),
                    // Volmue 3
                    Row(
                      mainAxisAlignment: MainAxisAlignment.center,
                      children: [
                        const Text(
                          '3',
                          style: TextStyle(
                            color: Colors.white,
                            fontSize: 16,
                            fontWeight: FontWeight.bold,
                          ),
                        ),
                        SizedBox(
                          width: 150,
                          height: 30,
                          child: Card(
                            color: showColor(3),
                            shape: RoundedRectangleBorder(
                              borderRadius: BorderRadius.circular(5),
                              side: BorderSide(
                                color: _color_bor[2],
                                width: 1.3,
                              ),
                            ),
                            child: InkWell(
                                splashColor: Colors.black.withAlpha(100),
                                onTap: () {
                                  setState(() {
                                    _volume_number = 3;
                                    selectbor(3);
                                  });
                                }),
                          ),
                        ),
                        const Text(
                          '3',
                          style: TextStyle(
                            color: Colors.white,
                            fontSize: 16,
                            fontWeight: FontWeight.bold,
                          ),
                        ),
                      ],
                    ),
                    // Volmue 2
                    Row(
                      mainAxisAlignment: MainAxisAlignment.center,
                      children: [
                        const Text(
                          '2',
                          style: TextStyle(
                            color: Colors.white,
                            fontSize: 16,
                            fontWeight: FontWeight.bold,
                          ),
                        ),
                        SizedBox(
                          width: 150,
                          height: 30,
                          child: Card(
                            color: showColor(2),
                            shape: RoundedRectangleBorder(
                              borderRadius: BorderRadius.circular(5),
                              side: BorderSide(
                                color: _color_bor[1],
                                width: 1.3,
                              ),
                            ),
                            child: InkWell(
                                splashColor: Colors.black.withAlpha(100),
                                onTap: () {
                                  setState(() {
                                    _volume_number = 2;
                                    selectbor(2);
                                  });
                                }),
                          ),
                        ),
                        const Text(
                          '2',
                          style: TextStyle(
                            color: Colors.white,
                            fontSize: 16,
                            fontWeight: FontWeight.bold,
                          ),
                        ),
                      ],
                    ),
                    // Volmue 1
                    Row(
                      mainAxisAlignment: MainAxisAlignment.center,
                      children: [
                        const Text(
                          '1',
                          style: TextStyle(
                            color: Colors.white,
                            fontSize: 16,
                            fontWeight: FontWeight.bold,
                          ),
                        ),
                        SizedBox(
                          width: 150,
                          height: 30,
                          child: Card(
                            color: showColor(1),
                            shape: RoundedRectangleBorder(
                              borderRadius: BorderRadius.circular(5),
                              side: BorderSide(
                                color: _color_bor[0],
                                width: 1.3,
                              ),
                            ),
                            child: InkWell(
                                splashColor: Colors.black.withAlpha(100),
                                onTap: () {
                                  setState(() {
                                    _volume_number = 1;
                                    selectbor(1);
                                  });
                                }),
                          ),
                        ),
                        const Text(
                          '1',
                          style: TextStyle(
                            color: Colors.white,
                            fontSize: 16,
                            fontWeight: FontWeight.bold,
                          ),
                        ),
                      ],
                    ),
                  ],
                ),
              ),
            ),
            // Visibility(
            //   visible: _isShow_Pattern1, // _isShow_Pattern1 : true, false
            //   child: Pattern1(),
            // ),
            Container(
              height: 40,
              child: Center(
                child: TextButton(
                  child: const Text(
                    'Reset',
                    style: TextStyle(
                      fontSize: 16,
                      color: Color.fromARGB(255, 0, 229, 255),
                    ),
                  ),
                  onPressed: () {
                    setState(() {
                      if (_select_Patterns == 1) {
                        _reset_P1 = 1;
                      } else if (_select_Patterns == 2) {
                        _reset_P2 = 1;
                      } else if (_select_Patterns == 3) {
                        _reset_P3 = 1;
                      }
                      for (int i = 0; i < 8; i++) {
                        _color[i] = Colors.white38;
                      }
                    });
                  },
                ),
              ),
            ),
            CircleColorPicker(
              size: const Size(220, 220),
              thumbSize: 25,
              onChanged: (Color color) {
                setState(() {
                  // เซตค่าสี
                  if (_select_Patterns == 1) {
                    _reset_P1 = 0;
                  } else if (_select_Patterns == 2) {
                    _reset_P2 = 0;
                  } else if (_select_Patterns == 3) {
                    _reset_P3 = 0;
                  }
                  switch (_volume_number) {
                    case 1:
                      _color[0] = color;
                      break;
                    case 2:
                      _color[1] = color;
                      break;
                    case 3:
                      _color[2] = color;
                      break;
                    case 4:
                      _color[3] = color;
                      break;
                    case 5:
                      _color[4] = color;
                      break;
                    case 6:
                      _color[5] = color;
                      break;
                    case 7:
                      _color[6] = color;
                      break;
                    case 8:
                      _color[7] = color;
                      break;
                  }
                });
              },
              strokeWidth: 6.0,
              colorCodeBuilder: (context, color) {
                return Text(
                  'RGB(${color.red},${color.green},${color.blue})',
                  style: const TextStyle(
                    fontSize: 14,
                    color: Colors.white,
                    fontWeight: FontWeight.bold,
                  ),
                );
              },
            ),
            Expanded(
              child: Align(
                alignment: Alignment.bottomCenter,
                child: Container(
                  margin: const EdgeInsets.all(20),
                  width: 180,
                  height: 50,
                  child: ElevatedButton(
                    onPressed: () {
                      EasyLoading.show(status: 'Uploading Colors...');
                      var DataColor = DisplayColors(_select_Patterns);
                      if (_select_Patterns == 1) {
                        DataColor.updateResetState(_reset_P1);
                      } else if (_select_Patterns == 2) {
                        DataColor.updateResetState(_reset_P2);
                      } else if (_select_Patterns == 3) {
                        DataColor.updateResetState(_reset_P3);
                      }
                      DataColor.updateColor(_color);
                      DataColor.getDataColor();
                    },
                    style: ButtonStyle(
                      backgroundColor:
                          const MaterialStatePropertyAll<Color>(Colors.black),
                      shape: MaterialStatePropertyAll(
                        RoundedRectangleBorder(
                          borderRadius: BorderRadius.circular(20),
                        ),
                      ),
                    ),
                    child: const Text(
                      'Custom',
                      style: TextStyle(
                        fontSize: 20,
                      ),
                    ),
                  ),
                ),
              ),
            ),
          ],
        ),
      ),
    );
  }
}
