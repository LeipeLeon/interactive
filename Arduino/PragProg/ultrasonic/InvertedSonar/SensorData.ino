class SensorData {
  private float temperature;
  private float distance;

  SensorData(float temperature, float distance) {
    this.temperature = temperature;
    this.distance = distance;
  }
  
  float getTemperature() {
    return this.temperature;
  }
  
  float getDistance() {
    return this.distance;
  }  
}

