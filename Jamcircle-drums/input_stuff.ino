void inputUpdate() {
  if (inputUpdateTimer > inputUpdateTime) {
    inputUpdateTimer = 0;

    recalibrateButton.update();
    if ( recalibrateButton.fell() ) {
      Serial.println("RECABRATION TIME");
      calibrateBaseline();
    }

    for (int i = 0; i < 3; i++) {
      int faderValue = analogRead(faderPin[i]);
      if (faderValue > faderCalibration[0])faderPos[i] = 0;
      else if (faderValue > faderCalibration[1])faderPos[i] = 1;
      else if (faderValue > faderCalibration[2])faderPos[i] = 2;
      else if (faderValue > faderCalibration[3])faderPos[i] = 3;
      else faderPos[i] = 4;
    }

    int volumeValue = analogRead(volumepot);
    if (volumeValue - volumeThreshold > lastVolume || volumeValue + volumeThreshold < lastVolume) {
      lastVolume = volumeValue;
      overalVolume = fmap(volumeValue, 0, 4096, 0, 1);
      Serial.println("VOLUMECHANGED");
    }


    mod1value[0] = !digitalRead(mod1_0);
    mod1value[1] = !digitalRead(mod1_1);
    mod1value[2] = !digitalRead(mod1_2);
    mod1value[3] = !digitalRead(mod1_3);

    mod2value = map(analogRead(mod2 ), mod2calibration[0], mod2calibration[1], mod2range[0], mod2range[1]);

    mod3value[0] = !digitalRead(mod3_0);
    mod3value[1] = !digitalRead(mod3_1);

  }
}
