# gate-alarm

Gate alarm is the device that can help you to warn if a thief breaking the gates chain. So when the thief can open the gate, the alarm will ringing as a sign of danger.

## System Architecture

> Sensor (Encoder) --> Controller (Arduino Uno) --> Alarm (Buzzer)

For detect the gates movement is opened or closed, I use rotary encoder linked with belt. Rotary encoder will count the generated pulse as the gate movement while open. When the gates opened 45 degree, alarm will start ringing as warning. After going through calculations, if gate opened 45 degree, the encoder generates 20 pulse.

```cpp
// Gate movement, encoder is counting the pulse generated
int gate_mv = encoder_pulse();

// Turn ON alarm if gate opened (generated pulses is more than 20 or less than -20)
if (gate_mv > 20 || gate_mv < -20)
{
    Serial.println("OPEN");
    digitalWrite(ALARM, HIGH);
}
```
