import 'package:flutter/material.dart';
import 'package:animated_splash_screen/animated_splash_screen.dart';
import 'package:page_transition/page_transition.dart';
import 'functions.dart';

class SplashScreen extends StatefulWidget {
  const SplashScreen({super.key});

  @override
  State<SplashScreen> createState() => _SplashScreenState();
}

class _SplashScreenState extends State<SplashScreen> {
  @override
  Widget build(BuildContext context) {
    return AnimatedSplashScreen(
      splash: Image.asset('assets/logo_MakerClub.png'),
      backgroundColor: Colors.black,
      nextScreen: const functions(),
      splashIconSize: 400,
      duration: 3000,
      pageTransitionType: PageTransitionType.rightToLeftWithFade,
    );
  }
}
