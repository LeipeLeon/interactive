class SensorDataBuffer {
  private int _maxSamples;
  private int _bufferIndex;
  private int[] _xBuffer;
  private int[] _yBuffer;
  private int[] _zBuffer;
  
  public SensorDataBuffer(final int maxSamples) { // <label id="code.nunchuk.sdb_constructor"/>
    _maxSamples = maxSamples;
    _bufferIndex = 0;
    _xBuffer = new int[_maxSamples];
    _yBuffer = new int[_maxSamples];
    _zBuffer = new int[_maxSamples];
  }
  
  public void addData(final int x, final int y, final int z) {
    if (_bufferIndex >= _maxSamples)
      _bufferIndex = 0;
    
    _xBuffer[_bufferIndex] = x;
    _yBuffer[_bufferIndex] = y;
    _zBuffer[_bufferIndex] = z;
    _bufferIndex++;
  }
  
  public int getX() {
    return getAverageValue(_xBuffer);
  }
  
  public int getY() {
    return getAverageValue(_yBuffer);
  }
  
  public int getZ() {
    return getAverageValue(_zBuffer);
  }
  
  private int getAverageValue(final int[] buffer) {
    int sum = 0;
    for (int i = 0; i < _maxSamples; i++)
      sum += buffer[i];
    return (int)(sum / _maxSamples);
  }
}

