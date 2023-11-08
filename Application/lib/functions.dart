import 'package:flutter/material.dart';
import 'package:flutter/cupertino.dart';
import 'package:flutter_easyloading/flutter_easyloading.dart';
import 'DisplayColors.dart';
import 'Custom.dart';

class functions extends StatefulWidget {
  const functions({super.key});

  @override
  State<functions> createState() => _functionsState();
}

class _functionsState extends State<functions> {
  @override
  Widget build(BuildContext context) {
    return Scaffold(
      resizeToAvoidBottomInset: false,
      backgroundColor: Colors.black87,
      appBar: AppBar(
        iconTheme: const IconThemeData(color: Colors.white),
        backgroundColor: Colors.black,
        centerTitle: true,
        title: const Text(
          'Pattern',
          style: TextStyle(
            color: Colors.white,
          ),
        ),
        // leading: IconButton(
        //   onPressed: () {},
        //   icon: const Icon(
        //     Icons.arrow_back_ios,
        //     color: Colors.red,
        //   ),
        // ),
        actions: [
          IconButton(
            onPressed: () {
              EasyLoading.show(status: 'loading...');
              navigateToCustom(context);
            },
            icon: const Icon(
              Icons.settings,
            ),
          ),
        ],
      ),
      body: GridView.count(
        crossAxisCount: 1,
        childAspectRatio: 1 / .4,
        // crossAxisSpacing: 50,
        // mainAxisSpacing: 50,
        padding: const EdgeInsets.all(10),
        children: List.generate(8, (index) {
          // 5555
          int patterns = index + 1;
          if (patterns == 1) {
            return Card(
              color: const Color.fromARGB(251, 255, 157, 0),
              margin: const EdgeInsets.all(5),
              shape: RoundedRectangleBorder(
                borderRadius: BorderRadius.circular(20),
              ),
              clipBehavior: Clip.hardEdge,
              child: InkWell(
                splashColor: Colors.black.withAlpha(100),
                onTap: () async {
                  EasyLoading.show(status: 'loading...');
                  var select = DisplayColors(1);
                  select.getDataColor();
                },
                child: const SizedBox(
                  width: 100,
                  height: 100,
                  child: Center(
                    child: Column(
                      mainAxisAlignment: MainAxisAlignment.spaceEvenly,
                      children: [
                        Text(
                          'Random Mode',
                          style: TextStyle(
                            color: Colors.white,
                            fontSize: 20,
                            fontWeight: FontWeight.bold,
                          ),
                        ),
                      ],
                    ),
                  ),
                ),
              ),
            );
          }
          if (patterns == 2) {
            return Card(
              color: const Color.fromARGB(180, 38, 255, 0),
              margin: const EdgeInsets.all(5),
              shape: RoundedRectangleBorder(
                borderRadius: BorderRadius.circular(20),
              ),
              clipBehavior: Clip.hardEdge,
              child: InkWell(
                splashColor: Colors.black.withAlpha(100),
                onTap: () async {
                  EasyLoading.show(status: 'loading...');
                  var select = DisplayColors(2);
                  select.getDataColor();
                },
                child: const SizedBox(
                  width: 100,
                  height: 100,
                  child: Center(
                    child: Column(
                      mainAxisAlignment: MainAxisAlignment.spaceEvenly,
                      children: [
                        Text(
                          'Spectrogram Mode',
                          style: TextStyle(
                            color: Colors.white,
                            fontSize: 20,
                            fontWeight: FontWeight.bold,
                          ),
                        ),
                      ],
                    ),
                  ),
                ),
              ),
            );
          }
          if (patterns == 3) {
            return Card(
              color: const Color.fromARGB(255, 85, 0, 255),
              margin: const EdgeInsets.all(5),
              shape: RoundedRectangleBorder(
                borderRadius: BorderRadius.circular(20),
              ),
              clipBehavior: Clip.hardEdge,
              child: InkWell(
                splashColor: Colors.black.withAlpha(100),
                onTap: () async {
                  EasyLoading.show(status: 'loading...');
                  var select = DisplayColors(3);
                  select.getDataColor();
                },
                child: const SizedBox(
                  width: 100,
                  height: 100,
                  child: Center(
                    child: Column(
                      mainAxisAlignment: MainAxisAlignment.spaceEvenly,
                      children: [
                        Text(
                          'Circle Mode',
                          style: TextStyle(
                            color: Colors.white,
                            fontSize: 20,
                            fontWeight: FontWeight.bold,
                          ),
                        ),
                      ],
                    ),
                  ),
                ),
              ),
            );
          }
          return Container();
        }),
      ),
    );
  }
}

navigateToCustom(BuildContext context) {
  Navigator.push(context, CupertinoPageRoute(builder: (context) {
    EasyLoading.show(status: 'loading...');
    return const Custom();
  }));
}
