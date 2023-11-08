import 'package:mqtt_client/mqtt_client.dart';
import 'package:mqtt_client/mqtt_server_client.dart';

class SendToESP {
  String data;

  final client = MqttServerClient('YOUR_SERVER', '1883');

  SendToESP(this.data);

  void sendDataToESP32() async {
    try {
      await client.connect();
      print('Connected to the MQTT broker');

      const topic = 'YOUR_TOPIC';

      final builder = MqttClientPayloadBuilder();
      builder.addString(data);

      if (builder.payload != null) {
        client.publishMessage(topic, MqttQos.atMostOnce, builder.payload!);
        print('Data sent to ESP32: $data');
      } else {
        print('Payload is null, data not sent.');
      }

      print('Subscribing to the $topic topic');
      client.subscribe(topic, MqttQos.exactlyOnce);
      client.updates!.listen((List<MqttReceivedMessage<MqttMessage?>>? c) {
        final recMess = c![0].payload as MqttPublishMessage;
        final pt =
            MqttPublishPayload.bytesToStringAsString(recMess.payload.message);
        print('Received message: topic is ${c[0].topic}, payload is $pt');
      });
    } catch (e) {
      print('Error: $e');
    }
  }
}
