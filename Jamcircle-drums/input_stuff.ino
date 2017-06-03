void inputUpdate() {
  if (inputUpdateTimer > inputUpdateTime) {
    inputUpdateTimer = 0;

    recalibrateButton.update();
    if ( recalibrateButton.fell() ) {
      Serial.println("RECABRATION TIME");
      calibrateBaseline();
    }

    for (int i = 0; i < 3; i++) {
      int value = analogRead(faderPin[i]);
      if(value>faderCalibration[0])faderPos[i]=0;
      else if(value>faderCalibration[1])faderPos[i]=1;
      else if(value>faderCalibration[2])faderPos[i]=2;
      else if(value>faderCalibration[3])faderPos[i]=3;
      else faderPos[i]=4;
    }

  }
}
