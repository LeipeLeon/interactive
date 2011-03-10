require 'scroller'

describe Scroller do

  before do
    @scroller = Scroller.new
  end

  it "prints an empty string" do
    @scroller.compose_row(0).should eql(['.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.'])
    @scroller.compose_row(1).should eql(['.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.'])
    @scroller.compose_row(2).should eql(['.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.'])
    @scroller.compose_row(3).should eql(['.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.'])
    @scroller.compose_row(4).should eql(['.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.'])
    @scroller.compose_row(5).should eql(['.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.'])
    @scroller.compose_row(6).should eql(['.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.'])
    @scroller.compose_row(7).should eql(['.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.'])
  end

  it "displays letter E" do
    @scroller.display_bitMapLeft(BITMAP_E)
    @scroller.compose_row(0).should eql(['.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.'])
    @scroller.compose_row(1).should eql(['.','.','.','.','.','.','.','.','X','X','X','X','X','X','X','.'])
    @scroller.compose_row(2).should eql(['.','.','.','.','.','.','.','.','X','X','.','.','.','.','.','.'])
    @scroller.compose_row(3).should eql(['.','.','.','.','.','.','.','.','X','X','X','X','.','.','.','.'])
    @scroller.compose_row(4).should eql(['.','.','.','.','.','.','.','.','X','X','.','.','.','.','.','.'])
    @scroller.compose_row(5).should eql(['.','.','.','.','.','.','.','.','X','X','X','X','X','X','X','.'])
    @scroller.compose_row(6).should eql(['.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.'])
    @scroller.compose_row(7).should eql(['.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.'])
  end

  it "should shift the current buffer to the left" do
    @scroller.pixels[0] = 0b0000000000000000
    @scroller.shift_buffer_left([0b0001] * 8, 0).should eql(["...............X"] * 8)
    @scroller.pixels[0].should eql(0b0000000000000001)
    @scroller.shift_buffer_left([0b0001] * 8, 1).should eql(["..............X."] * 8)
    @scroller.pixels[0].should eql(0b0000000000000010)
    # @scroller.shift_buffer_left([0b0001] * 8, 4).should eql(["...........X...."] * 8)
    # @scroller.pixels[0].should eql(0b0000000000000010)
  end

  it "should shift the current buffer down" do
    @scroller.pixels = Array.new(16, 0b00000000000000000000000000000000)
    @scroller.pixels[0] = 0b00000000000000001111111111111111
    arr1 = Array.new(6, "................")
    arr1 << "XXXXXXXXXXXXXXXX"
    arr1 << ".X.X.X.X.X.X.X.X"
    arr2 = [0b00000000000000000101010101010101]
    (arr2 << 0b00000000000000001111111111111111) * 7
    @scroller.shift_buffer_down(arr2, 0).should eql(arr1)
    @scroller.pixels[0].should eql(0b00000000000000000101010101010101)
    @scroller.pixels[1].should eql(0b00000000000000001111111111111111)
    @scroller.pixels[2].should eql(0b00000000000000000000000000000000)
    @scroller.shift_buffer_down(arr2, 1) #.should eql(arr1)
    @scroller.pixels[0].should eql(0b00000000000000001111111111111111)
    @scroller.pixels[1].should eql(0b00000000000000000101010101010101)
    @scroller.pixels[2].should eql(0b00000000000000001111111111111111)
    @scroller.pixels[3].should eql(0b00000000000000000000000000000000)
  end

  it "display_bitMapLeft" do
    @scroller.display_bitMapDown(BITMAP_E)
  end

end
