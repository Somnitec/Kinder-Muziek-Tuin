void inputUpdate() {
  if (inputUpdateTimer > inputUpdateTime) {
    inputUpdateTimer = 0;

    recalibrateButton.update();
    if ( recalibrateButton.fell() ) {
      Serial.println("RECABRATION TIME");
      calibrateBaseline();
    }


  }
}
